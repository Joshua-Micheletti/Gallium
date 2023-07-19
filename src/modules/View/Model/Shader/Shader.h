#ifndef __SHADER__
#define __SHADER__

#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glad/glad.h"

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
		Shader(std::string);
		Shader();
		// public method for loading vertex and fragment shaders
		void loadShader(std::string, std::string);

		// get method for getting the shader id
		unsigned int id();
		// get method for getting the shader name
		std::string name();
		// get method for getting the buffer containing all the uniforms of the shader
		std::vector<uniform_t> uniformBuffer();
		// get method for getting the buffer containing all the layouts of the shader
		std::vector<std::string> layoutBuffer();

		void printFull();
		
	private:
		// shader name
		std::string m_name;

		std::string m_vertexSource;
		std::string m_fragmentSource;

		// shader id
		unsigned int m_id;
		// buffer containing the shader uniforms information
		std::vector<uniform_t> m_uniformBuffer;
		// buffer containing the shader layout information
		std::vector<std::string> m_layoutBuffer;
		
		// method for compiling shader code
		unsigned int compileShader(const char*, const char*);
		// method for reading the shader code and finding uniforms and layouts, to store them in the relative shaders
		void findUniformAndLayouts(const char*);
};

#endif
