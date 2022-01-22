#include "Window.h"
#include "SubPlane.h"
#include "HyperMath.h"

#define WINDOW_TITLE "OpenGL SDL2 Hyperbolic Plane"
#define WIDTH 1280
#define HEIGHT 720

int main(int ArgCount, char **Args)
{
  Window *window = new Window;

  SubdividedPlane *plane = new SubdividedPlane;
  SubdividedPlane *planeLeft = new SubdividedPlane;
  SubdividedPlane *planeRight = new SubdividedPlane;
  SubdividedPlane *planeUp = new SubdividedPlane;
  SubdividedPlane *planeDown = new SubdividedPlane;
  SubdividedPlane *planeLeftup = new SubdividedPlane;
  SubdividedPlane *planeUpleft = new SubdividedPlane;
  SubdividedPlane *planeUpright = new SubdividedPlane;
  SubdividedPlane *planeRightup = new SubdividedPlane;
  SubdividedPlane *planeLeftdown = new SubdividedPlane;
  SubdividedPlane *planeDownleft = new SubdividedPlane;
  SubdividedPlane *planeRightdown = new SubdividedPlane;
  SubdividedPlane *planeDownright = new SubdividedPlane;

  window->init(WINDOW_TITLE, WIDTH, HEIGHT);
  glm::vec4 cam(45.0f * TAU / 360.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);
  glm::vec3 light(0.0f, 0.5f, 0.0f);
  glm::vec3 ambient(0.2f, 0.2f, 0.2f);
  glm::vec3 diffuse(0.9f, 0.9f, 0.9f);
  glm::vec3 specular(0.1f, 0.1f, 0.1f);

  plane->Init();
  plane->ApplyTexture("Textures/center.png");
  plane->UpdateUniforms(cam, light, ambient, diffuse, specular);

  planeLeft->Init();
  planeLeft->ApplyTexture("Textures/left.png");
  planeLeft->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeLeft->vertexList, 0.0, -FUNDAMENTAL_REGION_OFFSET, true);

  planeRight->Init();
  planeRight->ApplyTexture("Textures/right.png");
  planeRight->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeRight->vertexList, 0.0, FUNDAMENTAL_REGION_OFFSET, true);

  planeUp->Init();
  planeUp->ApplyTexture("Textures/up.png");
  planeUp->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeUp->vertexList, -FUNDAMENTAL_REGION_OFFSET, 0.0, true);

  planeDown->Init();
  planeDown->ApplyTexture("Textures/down.png");
  planeDown->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeDown->vertexList, FUNDAMENTAL_REGION_OFFSET, 0.0, true);

  planeUpleft->Init();
  planeUpleft->ApplyTexture("Textures/upleft.png");
  planeUpleft->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeUpleft->vertexList, -FUNDAMENTAL_REGION_OFFSET, -FUNDAMENTAL_REGION_OFFSET, true);

  planeLeftup->Init();
  planeLeftup->ApplyTexture("Textures/leftup.png");
  planeLeftup->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeLeftup->vertexList, -FUNDAMENTAL_REGION_OFFSET, -FUNDAMENTAL_REGION_OFFSET, false);

  planeUpright->Init();
  planeUpright->ApplyTexture("Textures/upright.png");
  planeUpright->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeUpright->vertexList, -FUNDAMENTAL_REGION_OFFSET, FUNDAMENTAL_REGION_OFFSET, true);

  planeRightup->Init();
  planeRightup->ApplyTexture("Textures/rightup.png");
  planeRightup->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeRightup->vertexList, -FUNDAMENTAL_REGION_OFFSET, FUNDAMENTAL_REGION_OFFSET, false);

  planeLeftdown->Init();
  planeLeftdown->ApplyTexture("Textures/leftdown.png");
  planeLeftdown->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeLeftdown->vertexList, FUNDAMENTAL_REGION_OFFSET, -FUNDAMENTAL_REGION_OFFSET, false);

  planeDownleft->Init();
  planeDownleft->ApplyTexture("Textures/downleft.png");
  planeDownleft->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeDownleft->vertexList, FUNDAMENTAL_REGION_OFFSET, -FUNDAMENTAL_REGION_OFFSET, true);

  planeRightdown->Init();
  planeRightdown->ApplyTexture("Textures/rightdown.png");
  planeRightdown->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeRightdown->vertexList, FUNDAMENTAL_REGION_OFFSET, FUNDAMENTAL_REGION_OFFSET, false);

  planeDownright->Init();
  planeDownright->ApplyTexture("Textures/downright.png");
  planeDownright->UpdateUniforms(cam, light, ambient, diffuse, specular);
  MoveDiscrete(planeDownright->vertexList, FUNDAMENTAL_REGION_OFFSET, FUNDAMENTAL_REGION_OFFSET, true);

  float moveSpeed = 0.01f;
  glViewport(0, 0, WIDTH, HEIGHT);
  while (window->Running)
  {
    glm::mat4 mdlvMtx{1.0};
    mdlvMtx = glm::translate(mdlvMtx, glm::vec3{0.0f, -0.2f + window->yOff, -0.5f + window->zOff});
    mdlvMtx = glm::rotate(mdlvMtx, (90.0f + window->xOff) * TAU / 360.0f, glm::vec3{0.0f, 1.0f, 0.0f});
    glUniformMatrix4fv(plane->localMdlvMtx, 1, GL_FALSE, glm::value_ptr(mdlvMtx));

    glClearColor(106.0F/255.0F, 102.0F/255.0F, 125.0F/255.0F, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    window->run();
    if (window->horizontal != 0.0f || window->vertical != 0.0f)
    {
      Move(plane->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeLeft->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeRight->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeUp->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeDown->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeLeftup->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeUpleft->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeUpright->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeRightup->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeLeftdown->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeDownleft->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeRightdown->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
      Move(planeDownright->vertexList, window->horizontal * moveSpeed, window->vertical * moveSpeed);
    }

    plane->UpdateVertices();
    planeLeft->UpdateVertices();
    planeRight->UpdateVertices();
    planeUp->UpdateVertices();
    planeDown->UpdateVertices();
    planeLeftup->UpdateVertices();
    planeUpleft->UpdateVertices();
    planeUpright->UpdateVertices();
    planeRightup->UpdateVertices();
    planeLeftdown->UpdateVertices();
    planeDownleft->UpdateVertices();
    planeRightdown->UpdateVertices();
    planeDownright->UpdateVertices();

    plane->Draw();
    planeLeft->Draw();
    planeRight->Draw();
    planeUp->Draw();
    planeDown->Draw();
    planeUpleft->Draw();
    planeLeftup->Draw();
    planeUpright->Draw();
    planeRightup->Draw();
    planeLeftdown->Draw();
    planeDownleft->Draw();
    planeRightdown->Draw();
    planeDownright->Draw();
    SDL_GL_SwapWindow(window->Window);
  }
  return 0;
}