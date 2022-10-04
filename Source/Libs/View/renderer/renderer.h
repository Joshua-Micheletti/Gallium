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
#include "../../Model/entity.h"
#include "../drawingEntity/material/shader/shader.h"
#include "../drawingEntity/model/mesh/mesh.h"
#include "kernel/kernel.h"
#include "../camera/camera.h"
#include "../../init.h"
#include "../../global.h"


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
		int highlightedEntity;
		unsigned int tmpBuffer;

		int postProcessingEffect;
		glm::vec3 filterColor;

		unsigned int reflectionFBO;
		unsigned int reflectionRBO;
		unsigned int reflectionCubemap;
		int reflectionRes;

		unsigned int screenFBO;
		unsigned int screenTexture;
		unsigned int screenDepthTexture;
		unsigned int screenStencilTexture;
		unsigned int screenRBO;
		unsigned int screenVBO;
		unsigned int screenUVVBO;
		unsigned int outlineTextureMask;
		unsigned int postProcessingFBO;
		unsigned int postProcessingTexture;
		unsigned int postProcessingTexture2;
		unsigned int postProcessingDepthTexture;

		Shader* postProcessingShader;
		Shader* screenShader;
		Shader* depthShader;

		std::vector<float> data1;

		double reflectionRenderTime;
		double forwardRenderTime;
		double MSPostProcessingPassTime;
		double postProcessingPassTime;
		
		void renderReflectionCubemap();
		void renderMultisamplePostProcessing();
		void renderScreen();
		void resetRender();
		// method for updating the render resolution
		void resizeScreen();
		void renderEntities(bool);
		void renderSkybox();
		void renderEntity(std::string);
		void attachUniforms(DrawingEntity *, Mesh*, std::vector<uniform_t>);
		void linkLayouts(Mesh*, std::vector<std::string>);
		void renderOutline();

		void displayBoundingBox();
		void drawBoundingBox(bounds_t, glm::vec3);
		void drawBoundingSphere(float, glm::vec3, glm::vec3);
		void createCube(std::vector<float>*, std::vector<glm::vec3>);
		void createSphere(glm::vec3, float, int, std::vector<float>*);
};

#endif