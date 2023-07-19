#ifndef __PATH_TRACE_RENDERER__
#define __PATH_TRACE_RENDERER__

#include <vector>
#include <iostream>
#include <string>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL

#include "../../Utils/global.h"

class PathTraceRenderer {
    public:
        PathTraceRenderer();
        void render();

    private:
        unsigned int m_screenVBO;
        unsigned int m_screenUVVBO;

        unsigned int m_renderResultTexture;
        unsigned int m_accumulationTexture;

        unsigned int m_computeShader;
        unsigned int m_computeProgram;

        unsigned int m_vertices;
        unsigned int m_modelMatrices;
        unsigned int m_indices;
        unsigned int m_normals;
        unsigned int m_spheres;
        unsigned int m_planes;
        unsigned int m_boxes;
        unsigned int m_boundingBoxes;
        unsigned int m_materials;
        unsigned int m_meshMaterialIndices;

        bool m_firstDraw;
        float m_samples;

        void updateBuffers();
};


#endif