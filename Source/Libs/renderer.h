#include <vector>
#include "entity.h"
#include "shader.h"

extern unsigned int tmpBuffer;


class Renderer {
	public:
		Renderer();
		void render();
		void setupRender();

	private:
		unsigned int tmpBuffer;
		unsigned int cubemap;
		unsigned int texture;
		unsigned int renderBuffer;
		unsigned int image;
		unsigned int renderBuffer2;
		unsigned int screenBuffer;
		unsigned int uvBuffer;
		GLuint frameBuffer;
		GLuint imageframebuffer;
		Shader* screenShader;
		std::vector<float> square;
		std::vector<float> data1;
		int reflectionRes;

		void renderReflectionCubemap();
		void renderScreen();
		void resetRender();
		void renderEntities();
		void attachUniforms(Entity *, std::vector<uniform_t>);
		void linkLayouts(Entity*, std::vector<char *>);

		void displayBoundingBox();
		void drawBoundingBox(bounds_t, glm::vec3);
		void drawBoundingSphere(float, glm::vec3, glm::vec3);
		void createCube(std::vector<float>*, std::vector<glm::vec3>);
		void createSphere(glm::vec3, float, int, std::vector<float>*);
};