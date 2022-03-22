#include "Window.h"
#include "Chunk.h"
#include "HyperMath.h"

#define WINDOW_TITLE "OpenGL SDL2 Hyperbolic Plane"
#define WIDTH 640
#define HEIGHT 360

int main(int ArgCount, char **Args)
{
    Window *window = new Window;

    window->Init(WINDOW_TITLE, WIDTH, HEIGHT);
    glm::vec4 cam(45.0f * TAU / 360.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
    glm::vec3 light(0.0f, 0.5f, 0.0f);
    glm::vec3 ambient(0.2f, 0.2f, 0.2f);
    glm::vec3 diffuse(0.9f, 0.9f, 0.9f);
    glm::vec3 specular(0.1f, 0.1f, 0.1f);
    
    Chunk *chunk = new Chunk(0, 0, cam, light, ambient, diffuse, specular);

    float moveSpeed = 0.01f;
    glViewport(0, 0, WIDTH, HEIGHT);
    while (window->Running)
    {
        glm::mat4 mdlvMtx{1.0};
        mdlvMtx = glm::translate(mdlvMtx, glm::vec3{0.0f, -0.2f + window->yOff, -0.5f + window->zOff});
        mdlvMtx = glm::rotate(mdlvMtx, (90.0f + window->xOff) * TAU / 360.0f, glm::vec3{0.0f, 1.0f, 0.0f});
        glUniformMatrix4fv(chunk->planes[0]->localMdlvMtx, 1, GL_FALSE, glm::value_ptr(mdlvMtx));

        glClearColor(106.0F / 255.0F, 102.0F / 255.0F, 125.0F / 255.0F, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window->Run();
        if (window->horizontal != 0.0f || window->vertical != 0.0f)
        {
            chunk->MoveAll(window->horizontal * moveSpeed, window->vertical * moveSpeed);
        }

        chunk->UpdateVertices();
        chunk->Draw();

        SDL_GL_SwapWindow(window->Window);
    }
    delete chunk;
    delete window;
    return 0;
}