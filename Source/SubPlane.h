#ifndef _SUBPLANE_H_
#define _SUBPLANE_H_

#include <gl/glcorearb.h>
#include <gl/glext.h>
#include "HyperMath.h"
#include <iostream>
#include <fstream>
#include <string>

class SubdividedPlane
{
    private:
        const char *ReadFile(const char *filePath);
        GLuint CreateAndCompileShader(GLenum type, const char *source);

    public:
        SubdividedPlane();
        ~SubdividedPlane();

        Vertex vertexList[24];
        GLuint program;
        GLuint vao, vbo;
        GLuint tex;
        GLint localMdlvMtx, localProjMtx;
        GLint localLightPos, localAmbient, localDiffuse, localSpecular, localTexDiffuse;
        void LoadShaders();
        void GetUniformLocations();
        void GenerateAndBindBuffers();
        void UpdateUniforms(glm::vec4 cam, glm::vec3 light, glm::vec3 ambient,
                            glm::vec3 diffuse, glm::vec3 specular);
        void LoadVertex();
        void ApplyTexture(char const *file);
        void UpdateVertices();
        void Draw();
};
#endif