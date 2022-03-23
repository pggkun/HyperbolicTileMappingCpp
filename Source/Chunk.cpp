#include "Chunk.h"
#include <stdio.h>

Chunk::Chunk(float hx, float hy, glm::vec4 cam, glm::vec3 light, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    planes.clear();
    x = hx;
    y = hy;
    SubdividedPlane *plane = new SubdividedPlane;
    plane->ApplyTexture("Textures/center.png");
    plane->UpdateUniforms(cam, light, ambient, diffuse, specular);
    planes.push_back(plane);

    SubdividedPlane *planeLeft = new SubdividedPlane;
    planeLeft->ApplyTexture("Textures/left.png");
    planeLeft->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeLeft->vertexList, x, -FUNDAMENTAL_REGION_OFFSET + y, true);
    planes.push_back(planeLeft);

    SubdividedPlane *planeRight = new SubdividedPlane;
    planeRight->ApplyTexture("Textures/right.png");
    planeRight->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeRight->vertexList, x, FUNDAMENTAL_REGION_OFFSET + y, true);
    planes.push_back(planeRight);

    SubdividedPlane *planeUp = new SubdividedPlane;
    planeUp->ApplyTexture("Textures/up.png");
    planeUp->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeUp->vertexList, -FUNDAMENTAL_REGION_OFFSET + x, y, true);
    planes.push_back(planeUp);

    SubdividedPlane *planeDown = new SubdividedPlane;
    planeDown->ApplyTexture("Textures/down.png");
    planeDown->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeDown->vertexList, FUNDAMENTAL_REGION_OFFSET, 0.0, true);
    planes.push_back(planeDown);

    SubdividedPlane *planeLeftup = new SubdividedPlane;
    planeLeftup->ApplyTexture("Textures/leftup.png");
    planeLeftup->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeLeftup->vertexList, -FUNDAMENTAL_REGION_OFFSET + x, -FUNDAMENTAL_REGION_OFFSET + y, false);
    planes.push_back(planeLeftup);

    SubdividedPlane *planeUpleft = new SubdividedPlane;
    planeUpleft->ApplyTexture("Textures/upleft.png");
    planeUpleft->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeUpleft->vertexList, -FUNDAMENTAL_REGION_OFFSET + x, -FUNDAMENTAL_REGION_OFFSET + y, true);
    planes.push_back(planeUpleft);

    SubdividedPlane *planeUpright = new SubdividedPlane;
    planeUpright->ApplyTexture("Textures/upright.png");
    planeUpright->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeUpright->vertexList, -FUNDAMENTAL_REGION_OFFSET + x, FUNDAMENTAL_REGION_OFFSET + y, true);
    planes.push_back(planeUpright);

    SubdividedPlane *planeRightup = new SubdividedPlane;
    planeRightup->ApplyTexture("Textures/rightup.png");
    planeRightup->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeRightup->vertexList, -FUNDAMENTAL_REGION_OFFSET + x, FUNDAMENTAL_REGION_OFFSET + y, false);
    planes.push_back(planeRightup);

    SubdividedPlane *planeLeftdown = new SubdividedPlane;
    planeLeftdown->ApplyTexture("Textures/leftdown.png");
    planeLeftdown->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeLeftdown->vertexList, FUNDAMENTAL_REGION_OFFSET + x, -FUNDAMENTAL_REGION_OFFSET + y, false);
    planes.push_back(planeLeftdown);

    SubdividedPlane *planeDownleft = new SubdividedPlane;
    planeDownleft->ApplyTexture("Textures/downleft.png");
    planeDownleft->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeDownleft->vertexList, FUNDAMENTAL_REGION_OFFSET + x, -FUNDAMENTAL_REGION_OFFSET + y, true);
    planes.push_back(planeDownleft);

    SubdividedPlane *planeRightdown = new SubdividedPlane;
    planeRightdown->ApplyTexture("Textures/rightdown.png");
    planeRightdown->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeRightdown->vertexList, FUNDAMENTAL_REGION_OFFSET + x, FUNDAMENTAL_REGION_OFFSET + y, false);
    planes.push_back(planeRightdown);

    SubdividedPlane *planeDownright = new SubdividedPlane;
    planeDownright->ApplyTexture("Textures/downright.png");
    planeDownright->UpdateUniforms(cam, light, ambient, diffuse, specular);
    MoveDiscrete(planeDownright->vertexList, FUNDAMENTAL_REGION_OFFSET + x, FUNDAMENTAL_REGION_OFFSET + y, true);
    planes.push_back(planeDownright);
}

Chunk::~Chunk()
{
    for(int i = 0; i<planes.size(); i++)
    {
        delete planes[i];
    }
    planes.clear();
}

void Chunk::UpdateVertices()
{
    for (int i = 0; i < planes.size(); i++)
    {
        planes[i]->UpdateVertices();
    }
}

void Chunk::Draw()
{
    for (int i = 0; i < planes.size(); i++)
    {
        planes[i]->Draw();
    }
}

void Chunk::MoveAll(float x, float y)
{
    for (int i = 0; i < planes.size(); i++)
    {
        Move(planes[i]->vertexList, x, y);
    }
}