#ifndef __RENDERER__
#define __RENDERER__

#include <vector>
#include <iostream>
#include <string>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "../../Utils/global.h"
#include "../../Utils/Timer.h"

#include "../../Model/Entity.h"
#include "../Model/Shader/Shader.h"
#include "../Model/Mesh/Mesh.h"
#include "Kernel/Kernel.h"
#include "../Camera/Camera.h"


// class for rendering entities using shaders (mainly openGL)
class Renderer {
	public:
		// constructor method
		Renderer();
		// method for rendering
		void render();

		Kernel* Kernels;

		void setHighlightedEntity(int);

		double getReflectionRenderTime();
		double getForwardRenderTime();
		double getMSPostProcessingPassTime();
		double getPostProcessingPassTime();

		unsigned int getOutlineMaskTexture();
		unsigned int getDepthBufferTexture();

		void setPostProcessingEffect(int);
		void setFilterColor(float, float, float);

	private:
		int m_highlightedEntity;
		unsigned int m_tmpBuffer;

		int m_postProcessingEffect;
		glm::vec3 m_filterColor;

		unsigned int m_reflectionFBO;
		unsigned int m_reflectionRBO;
		unsigned int m_reflectionCubemap;
		int m_reflectionRes;

		unsigned int m_screenFBO;
		unsigned int m_screenTexture;
		unsigned int m_screenDepthTexture;
		unsigned int m_screenStencilTexture;
		unsigned int m_screenRBO;
		unsigned int m_screenVBO;
		unsigned int m_screenUVVBO;
		unsigned int m_outlineTextureMask;
		unsigned int m_postProcessingFBO;
		unsigned int m_postProcessingTexture;
		unsigned int m_postProcessingTexture2;
		unsigned int m_postProcessingDepthTexture;

		Shader* m_postProcessingShader;
		Shader* m_screenShader;
		Shader* m_depthShader;

		std::vector<float> m_data1;

		double m_reflectionRenderTime;
		double m_forwardRenderTime;
		double m_MSPostProcessingPassTime;
		double m_postProcessingPassTime;
		
		void renderReflectionCubemap();
		void renderMultisamplePostProcessing();
		void renderScreen();
		void resetRender();
		// method for updating the render resolution
		void resizeScreen();
		void renderEntities(bool);
		void renderSkybox();
		void renderEntity(std::string);
		void attachUniforms(Model*, Material*, RenderTexture, std::vector<uniform_t>);
		void linkLayouts(Mesh*, std::vector<std::string>);
		void renderOutline();
		void drawBoundingSphere();

		void displayBoundingBox();
		void drawBoundingBox(bounds_t, glm::vec3);
		void drawBoundingSphere(float, glm::vec3, glm::vec3);
		void createCube(std::vector<float>*, std::vector<glm::vec3>);
		void createSphere(glm::vec3, float, int, std::vector<float>*);

		void drawCameraFrustum();
};

#endif