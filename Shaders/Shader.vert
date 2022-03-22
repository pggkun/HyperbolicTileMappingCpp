#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 inNormal;

out vec2 vtxTexCoord;
out vec4 vtxNormalQuat;
out vec3 vtxView;

uniform mat4 mdlvMtx;
uniform mat4 projMtx;

vec4 projection()
{
    vec4 Pe = vec4(inPos, 1.0);
    vec4 P0 = vec4(0.0, -1.0, 0.0, 1.0);
    vec4 V = Pe - P0;
    float t = P0.y/V.y;
    float pX = P0.x + (t * V.x);
    float pZ = P0.z + (t * V.z);
    return vec4(pX, 0.0, pZ, 1.0);
}

void main()
{
    vec4 pos = mdlvMtx * projection();
    vtxView = -pos.xyz;
    gl_Position = projMtx * pos;

    vec3 normal = normalize(mat3(mdlvMtx) * inNormal);
    float z = (1.0 + normal.z) / 2.0;
    vtxNormalQuat = vec4(1.0, 0.0, 0.0, 0.0);
    if (z > 0.0)
    {
        vtxNormalQuat.z = sqrt(z);
        vtxNormalQuat.xy = normal.xy / (2.0 * vtxNormalQuat.z);
    }
    vtxTexCoord = inTexCoord;
}