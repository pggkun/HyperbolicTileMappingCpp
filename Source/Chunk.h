#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "SubPlane.h"
#include <vector>
#include <string>

class Chunk
{
    public:
        Chunk(float hx, float hy, glm::vec4 cam, glm::vec3 light, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
        ~Chunk();

        float x, y;
        std::vector<SubdividedPlane *> planes;
        void UpdateVertices();
        void Draw();
        void MoveAll(float x, float y);
};
#endif