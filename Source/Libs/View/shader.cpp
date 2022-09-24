#include "glad/glad.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.h"

// constructor method, sets the shader name
Shader::Shader(char* name) {
	this->name = name;
}

Shader::Shader() {

}

char* Shader::getName() {
	return(this->name);
}

unsigned int Shader::getID() {
	return(this->id);
}

std::vector<uniform_t> Shader::getUniformBuffer() {
	return(this->uniformBuffer);
}

std::vector<char*> Shader::getLayoutBuffer() {
	return(this->layoutBuffer);
}

void Shader::loadShader(char* vertex, char* fragment) {
	this->id = compileShader(vertex, fragment);
	findUniformAndLayouts(vertex);
}

unsigned int Shader::compileShader(char* vertex_file_path, char* fragment_file_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
	//return(0);
}

void Shader::findUniformAndLayouts(char* shader) {
	FILE* vertexShader = fopen(shader, "r");
	int readingUniform = 0;
	int readingLayouts = 0;
	char buffer[255];
	uniform_t tmpUniform;
	tmpUniform.id = 0;
	tmpUniform.name = (char*)calloc(sizeof(char), 255);
	tmpUniform.type = (char*)calloc(sizeof(char), 255);
	char* tmpLayout = (char*)calloc(sizeof(char), 255);

	if (vertexShader == NULL) {
		printf("COULD NOT LOAD SHADER\n");
	}

	while (fscanf(vertexShader, "%s", buffer) != EOF) {

		if (readingUniform) {
			if (readingUniform == 2) {
				strcpy(tmpUniform.type, buffer);
			}

			else if (readingUniform == 1) {
				strcpy(tmpUniform.name, buffer);
				tmpUniform.id = glGetUniformLocation(this->id, tmpUniform.name);
				this->uniformBuffer.push_back(tmpUniform);
				tmpUniform.name = (char*)calloc(sizeof(char), 255);
				tmpUniform.type = (char*)calloc(sizeof(char), 255);
			}
			readingUniform--;
		}

		if (readingLayouts) {
			if (readingLayouts == 1) {
				strcpy(tmpLayout, buffer);
				this->layoutBuffer.push_back(&tmpLayout[0]);
				tmpLayout = (char*)calloc(sizeof(char), 255);
			}
			readingLayouts--;
		}

		if (!strcmp(buffer, "uniform")) {
			readingUniform = 2;
		}

		if (!strcmp(buffer, "layout")) {
			readingLayouts = 6;
		}
	}
}


void Shader::printFull() {
}