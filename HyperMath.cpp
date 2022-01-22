#include "HyperMath.h"

void kleinToMinkowski(Vertex *v, int length)
{
    for (int i = 0; i < length; i++)
    {
        float factor = sqrtf(1.0 / (1.0 - ((v[i].position[0] * v[i].position[0]) + (v[i].position[2] * v[i].position[2]))));
        float x1 = v[i].position[0] * factor;
        float z1 = v[i].position[2] * factor;
        v[i].position[0] = x1;
        v[i].position[1] = factor;
        v[i].position[2] = z1;
    }
}

void minkowskiToPoincare(Vertex *v, int length)
{
    for (int i = 0; i < length; i++)
    {
        float vy = v[i].position[1] + 1.0;
        float factor = -1.0 / vy;
        float px = factor * v[i].position[0];
        float pz = factor * v[i].position[2];
        v[i].position[0] = px;
        v[i].position[1] = 0.0;
        v[i].position[2] = pz;
    }
}

glm::mat4 HyperTranslateX(float angle)
{
    glm::mat4 m(1.0f);
    m[1][1] = coshf(angle);
    m[1][2] = sinhf(angle);
    m[2][1] = sinhf(angle);
    m[2][2] = coshf(angle);
    return m;
}

glm::mat4 HyperTranslateY(float angle)
{
    glm::mat4 m(1.0f);
    m[0][0] = coshf(angle);
    m[2][0] = sinhf(angle);
    m[0][2] = sinhf(angle);
    m[2][2] = coshf(angle);
    return m;
}

glm::mat4 RotateZ(float angle)
{
    glm::mat4 m(1.0f);
    m[0][0] = cos(angle);
    m[0][1] = sin(angle);
    m[1][0] = -sin(angle);
    m[1][1] = cos(angle);
    return m;
}

void MoveDiscrete(Vertex *mesh, float x, float y, bool xFirst)
{
    for (int i = 0; i < 24; i++)
    {
        glm::mat4 result;
        if(xFirst)
            result = HyperTranslateX(x) * HyperTranslateY(y);
        else
            result = HyperTranslateY(y) * HyperTranslateX(x);
        glm::vec4 currentPos = glm::vec4(mesh[i].position[0], mesh[i].position[2], mesh[i].position[1], 1.0);
        glm::vec4 resultPos = result * currentPos;
        mesh[i].position[0] = resultPos.x;
        mesh[i].position[1] = resultPos.z;
        mesh[i].position[2] = resultPos.y;
    }
}

void Move(Vertex *mesh, float x, float y)
{
    for (int i = 0; i < 24; i++)
    {
        glm::mat4 result;
        result = RotateZ(x * 2) * HyperTranslateY(y);
        glm::vec4 currentPos = glm::vec4(mesh[i].position[0], mesh[i].position[2], mesh[i].position[1], 1.0);
        glm::vec4 resultPos = result * currentPos;
        mesh[i].position[0] = resultPos.x;
        mesh[i].position[1] = resultPos.z;
        mesh[i].position[2] = resultPos.y;
    }
}