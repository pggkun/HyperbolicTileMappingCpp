#include "SubPlane.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

SubdividedPlane::SubdividedPlane()
{
    this->LoadVertex();
    kleinToMinkowski(this->vertexList, 24);
    this->LoadShaders();
    this->GetUniformLocations();
    this->GenerateAndBindBuffers();
}

SubdividedPlane::~SubdividedPlane()
{
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
    glDeleteTextures(1, &this->tex);
}

GLuint SubdividedPlane::CreateAndCompileShader(GLenum type, const char *source)
{
    GLint success;
    GLchar msg[512];

    GLuint handle = glCreateShader(type);
    if (!handle)
    {
        return 0;
    }
    const char *content = ReadFile(source);
    glShaderSource(handle, 1, &content, nullptr);
    glCompileShader(handle);
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(handle, sizeof(msg), nullptr, msg);
        glDeleteShader(handle);
        return 0;
    }
    return handle;
}

void SubdividedPlane::LoadShaders()
{
    GLint vsh = CreateAndCompileShader(GL_VERTEX_SHADER, "Shaders/Shader.vert");
    GLint fsh = CreateAndCompileShader(GL_FRAGMENT_SHADER, "Shaders/Shader.frag");
    this->program = glCreateProgram();
    glAttachShader(this->program, vsh);
    glAttachShader(this->program, fsh);

    glLinkProgram(this->program);

    GLint success;
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        char buf[512];
        glGetProgramInfoLog(this->program, sizeof(buf), nullptr, buf);
    }
    glDeleteShader(vsh);
    glDeleteShader(fsh);
}

void  SubdividedPlane::GetUniformLocations()
{
    this->localMdlvMtx = glGetUniformLocation(this->program, "mdlvMtx");
    this->localProjMtx = glGetUniformLocation(this->program, "projMtx");
    this->localLightPos = glGetUniformLocation(this->program, "lightPos");
    this->localAmbient = glGetUniformLocation(this->program, "ambient");
    this->localDiffuse = glGetUniformLocation(this->program, "diffuse");
    this->localSpecular = glGetUniformLocation(this->program, "specular");
    this->localTexDiffuse = glGetUniformLocation(this->program, "tex_diffuse");
}

void SubdividedPlane::UpdateVertices()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertexList), this->vertexList, GL_DYNAMIC_DRAW);
}

void SubdividedPlane::GenerateAndBindBuffers()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    
    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertexList), this->vertexList, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glGenTextures(1, &this->tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Vertex vertexData[24] = 
{
    {  0.000000, 0.000000, 0.000000, 0.5, 0.5, 0.000000, 1.000000, -0.000000, },
    {  0.000000, 0.000000, 0.487000, 0.5, 1.0, 0.000000, 1.000000, -0.000000, },
    {  0.487000, 0.000000, 0.000000, 1.0, 0.5, 0.000000, 1.000000, -0.000000, },

    {  -0.487000, 0.000000, 0.000000, 0.0, 0.5, 0.000000, 1.000000, -0.000000, },
    {  -0.487000, 0.000000, 0.487000, 0.0, 1.0, 0.000000, 1.000000, -0.000000, },
    {  0.000000, 0.000000, 0.000000, 0.5, 0.5, 0.000000, 1.000000, -0.000000, },

    {  -0.487000, 0.000000, -0.487000, 0.0, 0.0, 0.000000, 1.000000, -0.000000, },
    {  -0.487000, 0.000000, 0.000000, 0.0, 0.5, 0.000000, 1.000000, -0.000000, },
    {  0.000000, 0.000000, -0.487000, 0.5, 0.0, 0.000000, 1.000000, -0.000000, },

    {  0.000000, 0.000000, -0.487000, 0.5, 0.0, 0.000000, 1.000000, -0.000000, },
    {  0.000000, 0.000000, 0.000000, 0.5, 0.5, 0.000000, 1.000000, -0.000000, },
    {  0.487000, 0.000000, -0.487000, 1.0, 0.0, 0.000000, 1.000000, -0.000000, },

    {  0.487000, 0.000000, 0.000000, 1.0, 0.5, 0.000000, 1.000000, -0.000000, },
    {  0.000000, 0.000000, 0.487000, 0.5, 1.0, 0.000000, 1.000000, -0.000000, },
    {  0.487000, 0.000000, 0.487000, 1.0, 1.0, 0.000000, 1.000000, -0.000000, },

    {  0.000000, 0.000000, 0.000000, 0.5, 0.5, 0.000000, 1.000000, -0.000000, },
    {  -0.487000, 0.000000, 0.487000, 0.0, 1.0, 0.000000, 1.000000, -0.000000, },
    {  0.000000, 0.000000, 0.487000, 0.5, 1.0, 0.000000, 1.000000, -0.000000, },

    {  0.000000, 0.000000, -0.487000, 0.5, 0.0, 0.000000, 1.000000, -0.000000, },
    {  -0.487000, 0.000000, 0.000000, 0.0, 0.5, 0.000000, 1.000000, -0.000000, },
    {  0.000000, 0.000000, 0.000000, 0.5, 0.5, 0.000000, 1.000000, -0.000000, },

    {  0.487000, 0.000000, -0.487000, 1.0, 0.0, 0.000000, 1.000000, -0.000000, },
    {  0.000000, 0.000000, 0.000000, 0.5, 0.5, 0.000000, 1.000000, -0.000000, },
    {  0.487000, 0.000000, 0.000000, 1.0, 0.5, 0.000000, 1.000000, -0.000000, },
};

void SubdividedPlane::LoadVertex()
{
    memcpy(this->vertexList, vertexData, sizeof(vertexData));
}

void SubdividedPlane::ApplyTexture(char const * file)
{
    int width, height, nchan;
    unsigned char *img = stbi_load(file, &width, &height, &nchan, 3);
    assert(img);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    stbi_image_free(img);
}

void SubdividedPlane::UpdateUniforms(glm::vec4 cam, glm::vec3 light, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    glUseProgram(this->program);
    auto projMtx = glm::perspective(cam.x, cam.y, cam.z, cam.w);
    
    glUniformMatrix4fv(this->localProjMtx, 1, GL_FALSE, glm::value_ptr(projMtx));
    glUniform4f(this->localLightPos, light.x, light.y, light.z, 10.0f);
    glUniform3f(this->localAmbient, ambient.x, ambient.y, ambient.z);
    glUniform3f(this->localDiffuse, diffuse.x, diffuse.y, diffuse.z);
    glUniform4f(this->localSpecular, specular.x, specular.y, specular.z, 20.0f);
    glUniform1i(this->localTexDiffuse, 0);
}

void SubdividedPlane::Draw()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 24);
}

const char *SubdividedPlane::ReadFile(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open())
    {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content.c_str();
}
