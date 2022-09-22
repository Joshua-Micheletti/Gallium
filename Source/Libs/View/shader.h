#ifndef __SHADER__
#define __SHADER__

#include <vector>

// struct for saving the informations about shader uniforms
typedef struct {
	unsigned int id;
	char* type;
	char* name;
} uniform_t;

// class for loading, storing and dealing with shaders
class Shader {
	public:
		// constructor method
		Shader(char*);
		// public method for loading vertex and fragment shaders
		void loadShader(char*, char*);

		// get method for getting the shader id
		unsigned int getID();
		// get method for getting the shader name
		char* getName();
		// get method for getting the buffer containing all the uniforms of the shader
		std::vector<uniform_t> getUniformBuffer();
		// get method for getting the buffer containing all the layouts of the shader
		std::vector<char*> getLayoutBuffer();
		
	private:
		// shader name
		char* name;
		// shader id
		unsigned int id;
		// buffer containing the shader uniforms information
		std::vector<uniform_t> uniformBuffer;
		// buffer containing the shader layout information
		std::vector<char*> layoutBuffer;
		
		// method for compiling shader code
		unsigned int compileShader(char*, char*);
		// method for reading the shader code and finding uniforms and layouts, to store them in the relative shaders
		void findUniformAndLayouts(char*);
};

#endif
