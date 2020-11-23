#ifndef __RENDERER__
#define __RENDERER__
#include <vector>
#include "entity.h"
#include "shader.h"

// class for rendering entities using shaders (mainly openGL)
class Renderer {
	public:
		// constructor method
		Renderer();
		// method for rendering
		void render();
		

	private:
		unsigned int tmpBuffer;

		unsigned int reflectionFBO;
		unsigned int reflectionRBO;
		unsigned int reflectionCubemap;
		int reflectionRes;

		unsigned int screenFBO;
		unsigned int screenTexture;
		unsigned int screenDepthTexture;
		unsigned int screenRBO;
		unsigned int screenVBO;
		unsigned int screenUVVBO;
		Shader* screenShader;
		Shader* depthShader;

		std::vector<float> data1;
		
		void renderReflectionCubemap();
		void renderScreen();
		void resetRender();
		// method for updating the render resolution
		void resizeScreen();
		void renderEntities(bool);
		void attachUniforms(Entity *, std::vector<uniform_t>);
		void linkLayouts(Entity*, std::vector<char *>);

		void displayBoundingBox();
		void drawBoundingBox(bounds_t, glm::vec3);
		void drawBoundingSphere(float, glm::vec3, glm::vec3);
		void createCube(std::vector<float>*, std::vector<glm::vec3>);
		void createSphere(glm::vec3, float, int, std::vector<float>*);
};
#endif