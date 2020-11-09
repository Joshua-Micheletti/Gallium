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
		// method to setup the rendering (called by the constructor)
		void setupRender();

	private:
		unsigned int tmpBuffer;
		unsigned int cubemap;
		unsigned int texture;
		unsigned int reflectionRBO;
		unsigned int screenTexture;
		unsigned int screenRBO;
		unsigned int screenBuffer;
		unsigned int uvBuffer;
		GLuint reflectionFBO;
		GLuint screenFBO;
		Shader* screenShader;
		std::vector<float> square;
		std::vector<float> data1;
		int reflectionRes;

		void renderReflectionCubemap();
		void renderScreen();
		void resetRender();
		void renderEntities(bool);
		void attachUniforms(Entity *, std::vector<uniform_t>);
		void linkLayouts(Entity*, std::vector<char *>);

		void displayBoundingBox();
		void drawBoundingBox(bounds_t, glm::vec3);
		void drawBoundingSphere(float, glm::vec3, glm::vec3);
		void createCube(std::vector<float>*, std::vector<glm::vec3>);
		void createSphere(glm::vec3, float, int, std::vector<float>*);
};