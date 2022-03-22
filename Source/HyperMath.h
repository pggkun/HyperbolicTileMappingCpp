#pragma once
#ifndef _HYPERMATH_H_
#define _HYPERMATH_H_

#include <glm.hpp>
#include <ext/matrix_clip_space.hpp>
#include <gtc/type_ptr.hpp>
#include <vec3.hpp>
#include <vec4.hpp>

#define FUNDAMENTAL_REGION_OFFSET 1.062054

typedef struct
{
    float position[3];
    float texcoord[2];
    float normal[3];
} Vertex;

constexpr auto TAU = glm::two_pi<float>();

void kleinToMinkowski(Vertex *v, int length);

void minkowskiToPoincare(Vertex *v, int length);

glm::mat4 HyperTranslateX(float angle);

glm::mat4 HyperTranslateY(float angle);

glm::mat4 RotateZ(float angle);

void MoveDiscrete(Vertex *mesh, float x, float y, bool xFirst);

void Move(Vertex *mesh, float x, float y);

#endif