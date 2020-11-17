#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "entity.h"
#define STB_IMAGE_IMPLEMENTATION  
#include <stb_image.h>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
//
/* CONSTRUCTOR */
/* -----------------------------------------------------------------------------------------------------------------------*/
Entity::Entity(string name) {
	this->name = name;
	this->center = glm::vec3(0.0f);
	this->translation = glm::mat4(1.0f);
	this->rotation = glm::mat4(1.0f);
	this->scaleMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::mat4(1.0f);
	this->worldPosition = glm::vec3(0.0f);
	this->scaleFactor = glm::vec3(1.0f);
	this->rotateFactorX = 0.0f;
	this->rotateFactorY = 0.0f;
	this->rotateFactorZ = 0.0f;
	this->shader = 0;
	this->texture = 0;
	this->maxDistExt = 0;
	this->maxDistInt = 0;
	this->maxDist = 0;
	this->toReflect = true;

	if (this->getName().compare("axis") == 0) {
		this->elements = GL_LINES;
	}

	else {
		this->elements = GL_TRIANGLES;
	}


	if (this->getName().compare("skybox") == 0) {
		this->textureType = GL_TEXTURE_CUBE_MAP;
	}

	else {
		this->textureType = GL_TEXTURE_2D;
	}

	this->localBounds.minX = glm::vec3(0, 0, 0);
	this->localBounds.maxX = glm::vec3(0, 0, 0);
	this->localBounds.minY = glm::vec3(0, 0, 0);
	this->localBounds.maxY = glm::vec3(0, 0, 0);
	this->localBounds.minZ = glm::vec3(0, 0, 0);
	this->localBounds.maxZ = glm::vec3(0, 0, 0);
}

string Entity::getName() {
	return(this->name);
}
//
//
/* VERTICES */
/* -----------------------------------------------------------------------------------------------------------------------*/
void Entity::load3DModel(string model) {
	loadModel(model);
	placeAtCenter();
	createBuffer(this->vertices, &this->vertexBuffer);
	createBuffer(this->uvs, &this->texBuffer);
	createBuffer(this->normals, &this->normalBuffer);
}
//
void Entity::loadVertices(std::vector<float> vertices) {
	this->vertices = vertices;
	placeAtCenter();
	createBuffer(this->vertices, &this->vertexBuffer);
}
//
void Entity::loadModel(string name) {
	FILE* model = fopen(name.c_str(), "r");
	char buffer[255];

	std::vector<float> vertices;
	std::vector<float> tex;
	std::vector<float> normals;
	std::vector<int> faces;
	std::vector<int> facesTex;
	std::vector<int> facesNormals;
	int readingVertex = 0;
	int readingFaces = 0;
	int readingTex = 0;
	int read = 0;
	int verticesNumber = 0;
	int readingNormals = 0;

	if (model == NULL) {
		printf("COULD NOT LOAD MODEL\n");
	}

	while (fscanf(model, "%s", buffer) != EOF) {

		if (!readingVertex && !readingFaces && !readingTex && !readingNormals) {

			if (buffer[0] == 'v' && buffer[1] == '\0') {
				readingVertex = 3;
				verticesNumber++;
			}

			else if (buffer[0] == 'v' && buffer[1] == 't') {
				readingTex = 2;
			}

			else if (buffer[0] == 'v' && buffer[1] == 'n') {
				readingNormals = 3;
			}

			else if (buffer[0] == 'f') {
				readingFaces = 3;
			}
		}

		else if (readingVertex) {
			vertices.push_back(atof(buffer));
			readingVertex--;
		}

		else if (readingTex) {
			tex.push_back(atof(buffer));
			readingTex--;
		}

		else if (readingNormals) {
			normals.push_back(atof(buffer));
			readingNormals--;
		}

		else if (readingFaces) {
			read = 2;
			// vertex
			faces.push_back(atoi(buffer));

			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] == '/' && buffer[i + 1] != '/' && buffer[i + 1] != '\0' && read > 0) {
					// uv
					if (read == 2) {
						facesTex.push_back(atoi(&buffer[i + 1]));
					}
					// normal
					else if (read == 1) {
						facesNormals.push_back(atoi(&buffer[i + 1]));
					}

					read--;
				}

				else if (buffer[i] == '/' && (buffer[i + 1] == '/' || buffer[i + 1] == '\0')) {
					read--;
				}
			}

			readingFaces--;
		}
	}

	for (int i = 0; i < faces.size(); i++) {
		Entity::vertices.push_back(vertices[(faces[i] - 1) * 3]);
		Entity::vertices.push_back(vertices[(faces[i] - 1) * 3 + 1]);
		Entity::vertices.push_back(vertices[(faces[i] - 1) * 3 + 2]);
		Entity::uvs.push_back(tex[(facesTex[i] - 1) * 2]);
		Entity::uvs.push_back(-tex[(facesTex[i] - 1) * 2 + 1]);
		Entity::normals.push_back(normals[(facesNormals[i] - 1) * 3]);
		Entity::normals.push_back(normals[(facesNormals[i] - 1) * 3 + 1]);
		Entity::normals.push_back(normals[(facesNormals[i] - 1) * 3 + 2]);
	}
}
//
std::vector<float> Entity::getVertices() {
	return(this->vertices);
}

unsigned int Entity::getVertexBuffer() {
	return(this->vertexBuffer);
}


void Entity::findCenter() {
	float Mx, mx, My, my, Mz, mz;

	Mx = mx = this->vertices[0];
	My = my = this->vertices[1];
	Mz = mz = this->vertices[2];

	for (int i = 0; i < this->vertices.size(); i++) {
		if (i % 3 == 0) {
			if (this->vertices[i] <= mx) {
				mx = this->vertices[i];
			}

			else if (this->vertices[i] > Mx) {
				Mx = this->vertices[i];
			}
		}

		else if (i % 3 == 1) {
			if (this->vertices[i] <= my) {
				my = this->vertices[i];
			}

			else if (this->vertices[i] > My) {
				My = this->vertices[i];
			}
		}

		else if (i % 3 == 2) {
			if (this->vertices[i] <= mz) {
				mz = this->vertices[i];
			}

			else if (this->vertices[i] > Mz) {
				Mz = this->vertices[i];
			}
		}
	}

	this->center.x = (Mx + mx) / 2;
	this->center.y = (My + my) / 2;
	this->center.z = (Mz + mz) / 2;

	this->originalBounds.minX = glm::vec3(mx, 0, 0);
	this->originalBounds.maxX = glm::vec3(Mx, 0, 0);
	this->originalBounds.minY = glm::vec3(0, my, 0);
	this->originalBounds.maxY = glm::vec3(0, My, 0);
	this->originalBounds.minZ = glm::vec3(0, 0, mz);
	this->originalBounds.maxZ = glm::vec3(0, 0, Mz);

	this->originalBounds.a = glm::vec3((this->originalBounds.minX - this->center) +
		(this->originalBounds.maxY - this->center) +
		(this->originalBounds.maxZ - this->center)) + this->center;

	this->originalBounds.b = glm::vec3((this->originalBounds.maxX - this->center) +
		(this->originalBounds.maxY - this->center) +
		(this->originalBounds.maxZ - this->center)) + this->center;

	this->originalBounds.c = glm::vec3((this->originalBounds.maxX - this->center) +
		(this->originalBounds.minY - this->center) +
		(this->originalBounds.maxZ - this->center)) + this->center;

	this->originalBounds.d = glm::vec3((this->originalBounds.minX - this->center) +
		(this->originalBounds.minY - this->center) +
		(this->originalBounds.maxZ - this->center)) + this->center;

	this->originalBounds.e = glm::vec3((this->originalBounds.minX - this->center) +
		(this->originalBounds.minY - this->center) +
		(this->originalBounds.minZ - this->center)) + this->center;

	this->originalBounds.f = glm::vec3((this->originalBounds.minX - this->center) +
		(this->originalBounds.maxY - this->center) +
		(this->originalBounds.minZ - this->center)) + this->center;

	this->originalBounds.g = glm::vec3((this->originalBounds.maxX - this->center) +
		(this->originalBounds.maxY - this->center) +
		(this->originalBounds.minZ - this->center)) + this->center;

	this->originalBounds.h = glm::vec3((this->originalBounds.maxX - this->center) +
		(this->originalBounds.minY - this->center) +
		(this->originalBounds.minZ - this->center)) + this->center;

	this->originalBounds.xyz = this->originalBounds.e;
	this->originalBounds.XYZ = this->originalBounds.b;
}

void Entity::placeAtCenter() {
	findCenter();

	for (int i = 0; i < this->vertices.size(); i++) {
		if ((i % 3) == 0) {
			if (this->center.x >= 0) {
				this->vertices[i] -= this->center.x;
			}

			else if (this->center.x < 0) {
				this->vertices[i] += this->center.x;
			}
		}

		else if ((i % 3) == 1) {
			if (this->center.y >= 0) {
				this->vertices[i] -= this->center.y;
			}

			else if (this->center.y < 0) {
				this->vertices[i] -= this->center.y;
			}
		}

		else if ((i % 3) == 2) {
			if (this->center.z >= 0) {
				this->vertices[i] -= this->center.z;
			}

			else if (this->center.z < 0) {
				this->vertices[i] += this->center.z;
			}
		}
	}

	findCenter();
	calculateInternalBoundingSphere();
	calculateExternalBoundingSphere();
	calculateBoundingSphere();
}



/* TEXTURES */
/* -----------------------------------------------------------------------------------------------------------------------*/
void Entity::loadTexture(string path) {
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("COULD NOT LOAD TEXTURE\n");
	}
	stbi_image_free(data);
}

void Entity::loadCubemap(std::vector<std::string> faces) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

		if (data) {
			GLenum format;
			switch (nrChannels)
			{
			case 1:
				format = GL_LUMINANCE;
				break;
			case 2:
				format = GL_LUMINANCE_ALPHA;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else {
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	this->texture = textureID;
}

unsigned int Entity::getTexture() {
	return(this->texture);
}

void Entity::setTexture(unsigned int texture) {
	this->texture = texture;
}


void Entity::loadUVs(std::vector<float> texCoords) {
	this->uvs = texCoords;
	createBuffer(this->uvs, &this->texBuffer);
}

std::vector<float> Entity::getUVs() {
	return(this->uvs);
}


void Entity::setTextureType(GLenum textureType) {
	this->textureType = textureType;
}

GLenum Entity::getTextureType() {
	return(this->textureType);
}

unsigned int Entity::getTexBuffer() {
	return(this->texBuffer);
}



/* NORMALS */
/* -----------------------------------------------------------------------------------------------------------------------*/
std::vector<float> Entity::getNormals() {
	return(this->normals);
}

unsigned int Entity::getNormalBuffer() {
	return(this->normalBuffer);
}



/* RENDERING */
/* -----------------------------------------------------------------------------------------------------------------------*/
void Entity::setShader(int shader) {
	this->shader = shader;
}

int Entity::getShader() {
	return(this->shader);
}


void Entity::setElements(GLenum elements) {
	this->elements = elements;
}

GLenum Entity::getElements() {
	return(this->elements);
}


glm::mat4 Entity::getModelMatrix() {
	return(this->modelMatrix);
}



/* TRANSFORMATIONS */
/* -----------------------------------------------------------------------------------------------------------------------*/
glm::vec3 Entity::getRotationFactor() {
	return(glm::vec3(this->rotateFactorX, this->rotateFactorY, this->rotateFactorZ));
}

glm::vec3 Entity::getScalingFactor() {
	return(this->scaleFactor);
}

void Entity::placeAt(glm::vec3 position, glm::mat4 viewMatrix) {
	move(glm::vec3(-getWorldPosition().x, -getWorldPosition().y, -getWorldPosition().z), viewMatrix);
	move(position, viewMatrix);
}

void Entity::scale(float scaleFactor) {
	this->scaleMatrix = glm::scale(this->scaleMatrix, glm::vec3(scaleFactor));
	this->scaleFactor *= scaleFactor;
	calculateModel();
}

void Entity::setScale(glm::vec3 scale) {
	this->scaleMatrix = glm::mat4(1.0f);
	this->scaleMatrix = glm::scale(this->scaleMatrix, scale);
	this->scaleFactor = scale;

	calculateModel();
}

void Entity::move(glm::vec3 position, glm::mat4 viewMatrix) {
	this->translation = glm::translate(this->translation, position);

	calculateModel();

	glm::mat4 worldModelMatrix = glm::inverse(viewMatrix) * (viewMatrix * this->modelMatrix);

	this->worldPosition.x = worldModelMatrix[3][0];
	this->worldPosition.y = worldModelMatrix[3][1];
	this->worldPosition.z = worldModelMatrix[3][2];
}

void Entity::rotate(float x, float y, float z) {
	this->rotateFactorX += x;
	this->rotateFactorY += y;
	this->rotateFactorZ += z;

	this->rotation = glm::rotate(this->rotation, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	this->rotation = glm::rotate(this->rotation, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	this->rotation = glm::rotate(this->rotation, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	calculateModel();
}

void Entity::setRotation(float x, float y, float z) {
	this->rotation = glm::rotate(this->rotation, glm::radians(-this->rotateFactorZ), glm::vec3(0.0f, 0.0f, 1.0f));
	this->rotation = glm::rotate(this->rotation, glm::radians(-this->rotateFactorY), glm::vec3(0.0f, 1.0f, 0.0f));
	this->rotation = glm::rotate(this->rotation, glm::radians(-this->rotateFactorX), glm::vec3(1.0f, 0.0f, 0.0f));

	this->rotateFactorX = x;
	this->rotateFactorY = y;
	this->rotateFactorZ = z;

	this->rotation = glm::rotate(this->rotation, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	this->rotation = glm::rotate(this->rotation, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	this->rotation = glm::rotate(this->rotation, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));

	calculateModel();
}

glm::vec3 Entity::getCenter() {
	return(this->center);
}

glm::vec3 Entity::getWorldPosition() {
	return(this->worldPosition);
}



/* BOUNDS */
/* -----------------------------------------------------------------------------------------------------------------------*/
bounds_t Entity::getOriginalBounds() {
	return(this->originalBounds);
}


bounds_t Entity::getObjectBoundingBox(bool calculate) {
	if (calculate) {
		calculateObjectBoundingBox();
	}

	return(this->localBounds);
}

void Entity::calculateObjectBoundingBox() {
	glm::vec4 tmp;

	tmp = this->modelMatrix * glm::vec4(this->originalBounds.minX.x, this->originalBounds.minX.y, this->originalBounds.minX.z, 1);
	this->localBounds.minX = glm::vec3(tmp.x, tmp.y, tmp.z);

	tmp = this->modelMatrix * glm::vec4(this->originalBounds.maxX.x, this->originalBounds.maxX.y, this->originalBounds.maxX.z, 1);
	this->localBounds.maxX = glm::vec3(tmp.x, tmp.y, tmp.z);

	tmp = this->modelMatrix * glm::vec4(this->originalBounds.minY.x, this->originalBounds.minY.y, this->originalBounds.minY.z, 1);
	this->localBounds.minY = glm::vec3(tmp.x, tmp.y, tmp.z);

	tmp = this->modelMatrix * glm::vec4(this->originalBounds.maxY.x, this->originalBounds.maxY.y, this->originalBounds.maxY.z, 1);
	this->localBounds.maxY = glm::vec3(tmp.x, tmp.y, tmp.z);

	tmp = this->modelMatrix * glm::vec4(this->originalBounds.minZ.x, this->originalBounds.minZ.y, this->originalBounds.minZ.z, 1);
	this->localBounds.minZ = glm::vec3(tmp.x, tmp.y, tmp.z);

	tmp = this->modelMatrix * glm::vec4(this->originalBounds.maxZ.x, this->originalBounds.maxZ.y, this->originalBounds.maxZ.z, 1);
	this->localBounds.maxZ = glm::vec3(tmp.x, tmp.y, tmp.z);



	tmp = this->modelMatrix * glm::vec4(this->center.x, this->center.y, this->center.z, 1);
	this->localCenter = glm::vec3(tmp.x, tmp.y, tmp.z);


	this->localBounds.a = glm::vec3((this->localBounds.minX - this->localCenter) +
		(this->localBounds.maxY - this->localCenter) +
		(this->localBounds.maxZ - this->localCenter)) + this->localCenter;

	this->localBounds.b = glm::vec3((this->localBounds.maxX - this->localCenter) +
		(this->localBounds.maxY - this->localCenter) +
		(this->localBounds.maxZ - this->localCenter)) + this->localCenter;

	this->localBounds.c = glm::vec3((this->localBounds.maxX - this->localCenter) +
		(this->localBounds.minY - this->localCenter) +
		(this->localBounds.maxZ - this->localCenter)) + this->localCenter;

	this->localBounds.d = glm::vec3((this->localBounds.minX - this->localCenter) +
		(this->localBounds.minY - this->localCenter) +
		(this->localBounds.maxZ - this->localCenter)) + this->localCenter;

	this->localBounds.e = glm::vec3((this->localBounds.minX - this->localCenter) +
		(this->localBounds.minY - this->localCenter) +
		(this->localBounds.minZ - this->localCenter)) + this->localCenter;

	this->localBounds.f = glm::vec3((this->localBounds.minX - this->localCenter) +
		(this->localBounds.maxY - this->localCenter) +
		(this->localBounds.minZ - this->localCenter)) + this->localCenter;

	this->localBounds.g = glm::vec3((this->localBounds.maxX - this->localCenter) +
		(this->localBounds.maxY - this->localCenter) +
		(this->localBounds.minZ - this->localCenter)) + this->localCenter;

	this->localBounds.h = glm::vec3((this->localBounds.maxX - this->localCenter) +
		(this->localBounds.minY - this->localCenter) +
		(this->localBounds.minZ - this->localCenter)) + this->localCenter;

	this->localBounds.XYZ = this->localBounds.b;
	this->localBounds.xyz = this->localBounds.e;
}


glm::vec3 Entity::getLocalCenter() {
	return(this->localCenter);
}


bounds_t Entity::getExternalAxisAlignedBoundingBox(bool calculate) {
	if (calculate) {
		calculateExternalAxisAlignedBoundingBox();
	}

	return(this->worldBounds);
}

void Entity::calculateExternalAxisAlignedBoundingBox() {
	std::vector<glm::vec3> array;

	this->localBounds = getObjectBoundingBox(true);

	glm::vec3 tmpMinX, tmpMaxX, tmpMinY, tmpMaxY, tmpMinZ, tmpMaxZ;

	tmpMinX = tmpMaxX = tmpMinY = tmpMaxY = tmpMinZ = tmpMaxZ = this->localBounds.a;

	array.push_back(this->localBounds.a);
	array.push_back(this->localBounds.b);
	array.push_back(this->localBounds.c);
	array.push_back(this->localBounds.d);
	array.push_back(this->localBounds.e);
	array.push_back(this->localBounds.f);
	array.push_back(this->localBounds.g);
	array.push_back(this->localBounds.h);

	for (int i = 0; i < array.size(); i++) {
		if (array[i].x <= tmpMinX.x) {
			tmpMinX = array[i];
		}
		else if (array[i].x > tmpMaxX.x) {
			tmpMaxX = array[i];
		}

		if (array[i].y <= tmpMinY.y) {
			tmpMinY = array[i];
		}
		else if (array[i].y > tmpMaxY.y) {
			tmpMaxY = array[i];
		}

		if (array[i].z <= tmpMinZ.z) {
			tmpMinZ = array[i];
		}
		else if (array[i].z > tmpMaxZ.z) {
			tmpMaxZ = array[i];
		}
	}

	this->worldBounds.minX = tmpMinX;
	this->worldBounds.maxX = tmpMaxX;
	this->worldBounds.minY = tmpMinY;
	this->worldBounds.maxY = tmpMaxY;
	this->worldBounds.minZ = tmpMinZ;
	this->worldBounds.maxZ = tmpMaxZ;

	this->worldBounds.a = glm::vec3(this->worldBounds.minX.x, this->worldBounds.maxY.y, this->worldBounds.maxZ.z); // a(x, Y, Z)
	this->worldBounds.b = glm::vec3(this->worldBounds.maxX.x, this->worldBounds.maxY.y, this->worldBounds.maxZ.z); // b(X, Y, Z)
	this->worldBounds.c = glm::vec3(this->worldBounds.maxX.x, this->worldBounds.minY.y, this->worldBounds.maxZ.z); // c(X, y, Z)
	this->worldBounds.d = glm::vec3(this->worldBounds.minX.x, this->worldBounds.minY.y, this->worldBounds.maxZ.z); // d(x, y, Z)
	this->worldBounds.e = glm::vec3(this->worldBounds.minX.x, this->worldBounds.minY.y, this->worldBounds.minZ.z); // e(x, y, z)
	this->worldBounds.f = glm::vec3(this->worldBounds.minX.x, this->worldBounds.maxY.y, this->worldBounds.minZ.z); // f(x, Y, z)
	this->worldBounds.g = glm::vec3(this->worldBounds.maxX.x, this->worldBounds.maxY.y, this->worldBounds.minZ.z); // g(X, Y, z)
	this->worldBounds.h = glm::vec3(this->worldBounds.maxX.x, this->worldBounds.minY.y, this->worldBounds.minZ.z); // h(X, y, z)

	this->worldBounds.XYZ = this->worldBounds.b;
	this->worldBounds.xyz = this->worldBounds.e;
}


bounds_t Entity::getInternalAxisAlignedBoundingBox(bool calculate) {
	if (calculate) {
		calculateInternalAxisAlignedBoundingBox();
	}

	return(this->internalWorldBounds);
}

void Entity::calculateInternalAxisAlignedBoundingBox() {

	this->localBounds = getObjectBoundingBox(true);

	std::vector<glm::vec3> array;
	array.push_back(this->localBounds.minX);
	array.push_back(this->localBounds.maxX);
	array.push_back(this->localBounds.minY);
	array.push_back(this->localBounds.maxY);
	array.push_back(this->localBounds.minZ);
	array.push_back(this->localBounds.maxZ);

	glm::vec3 minX, maxX, minY, maxY, minZ, maxZ;

	minX = maxX = minY = maxY = minZ = maxZ = this->localBounds.minX;

	for (int i = 0; i < array.size(); i++) {
		if (array[i].x <= minX.x) {
			minX = array[i];
		}

		else if (array[i].x > maxX.x) {
			maxX = array[i];
		}

		if (array[i].y <= minY.y) {
			minY = array[i];
		}

		else if (array[i].y > maxY.y) {
			maxY = array[i];
		}

		if (array[i].z <= minZ.z) {
			minZ = array[i];
		}

		else if (array[i].z > maxZ.z) {
			maxZ = array[i];
		}
	}

	this->internalWorldBounds.minX = minX;
	this->internalWorldBounds.maxX = maxX;
	this->internalWorldBounds.minY = minY;
	this->internalWorldBounds.maxY = maxY;
	this->internalWorldBounds.minZ = minZ;
	this->internalWorldBounds.maxZ = maxZ;

	this->internalWorldBounds.a = glm::vec3(this->internalWorldBounds.minX.x, this->internalWorldBounds.maxY.y, this->internalWorldBounds.maxZ.z); // a(x, Y, Z)
	this->internalWorldBounds.b = glm::vec3(this->internalWorldBounds.maxX.x, this->internalWorldBounds.maxY.y, this->internalWorldBounds.maxZ.z); // b(X, Y, Z)
	this->internalWorldBounds.c = glm::vec3(this->internalWorldBounds.maxX.x, this->internalWorldBounds.minY.y, this->internalWorldBounds.maxZ.z); // c(X, y, Z)
	this->internalWorldBounds.d = glm::vec3(this->internalWorldBounds.minX.x, this->internalWorldBounds.minY.y, this->internalWorldBounds.maxZ.z); // d(x, y, Z)
	this->internalWorldBounds.e = glm::vec3(this->internalWorldBounds.minX.x, this->internalWorldBounds.minY.y, this->internalWorldBounds.minZ.z); // e(x, y, z)
	this->internalWorldBounds.f = glm::vec3(this->internalWorldBounds.minX.x, this->internalWorldBounds.maxY.y, this->internalWorldBounds.minZ.z); // f(x, Y, z)
	this->internalWorldBounds.g = glm::vec3(this->internalWorldBounds.maxX.x, this->internalWorldBounds.maxY.y, this->internalWorldBounds.minZ.z); // g(X, Y, z)
	this->internalWorldBounds.h = glm::vec3(this->internalWorldBounds.maxX.x, this->internalWorldBounds.minY.y, this->internalWorldBounds.minZ.z); // h(X, y, z)

	this->internalWorldBounds.XYZ = this->internalWorldBounds.b;
	this->internalWorldBounds.xyz = this->internalWorldBounds.e;
}


bounds_t Entity::getAxisAlignedBoundingBox(bool calculate) {
	if (calculate) {
		calculateAxisAlignedBoundingBox();
	}

	return(this->realBounds);
}

void Entity::calculateAxisAlignedBoundingBox() {
	glm::vec3 minX, maxX, minY, maxY, minZ, maxZ;

	glm::vec4 tmp;

	std::vector<glm::vec3> modeled;

	for (int i = 0; i < this->vertices.size(); i += 3) {
		tmp = glm::vec4(this->vertices[i], this->vertices[i + 1], this->vertices[i + 2], 1);
		tmp = this->modelMatrix * tmp;
		modeled.push_back(glm::vec3(tmp.x, tmp.y, tmp.z));
	}

	minX = maxX = minY = maxY = minZ = maxZ = modeled[0];

	for (int i = 0; i < modeled.size(); i++) {
		if (modeled[i].x <= minX.x) {
			minX = modeled[i];
		}
		else if (modeled[i].x > maxX.x) {
			maxX = modeled[i];
		}

		if (modeled[i].y <= minY.y) {
			minY = modeled[i];
		}
		else if (modeled[i].y > maxY.y) {
			maxY = modeled[i];
		}

		if (modeled[i].z <= minZ.z) {
			minZ = modeled[i];
		}
		else if (modeled[i].z > maxZ.z) {
			maxZ = modeled[i];
		}
	}

	this->realBounds.minX = minX;
	this->realBounds.maxX = maxX;
	this->realBounds.minY = minY;
	this->realBounds.maxY = maxY;
	this->realBounds.minZ = minZ;
	this->realBounds.maxZ = maxZ;

	this->realBounds.a = glm::vec3(this->realBounds.minX.x, this->realBounds.maxY.y, this->realBounds.maxZ.z); // a(x, Y, Z)
	this->realBounds.b = glm::vec3(this->realBounds.maxX.x, this->realBounds.maxY.y, this->realBounds.maxZ.z); // b(X, Y, Z)
	this->realBounds.c = glm::vec3(this->realBounds.maxX.x, this->realBounds.minY.y, this->realBounds.maxZ.z); // c(X, y, Z)
	this->realBounds.d = glm::vec3(this->realBounds.minX.x, this->realBounds.minY.y, this->realBounds.maxZ.z); // d(x, y, Z)
	this->realBounds.e = glm::vec3(this->realBounds.minX.x, this->realBounds.minY.y, this->realBounds.minZ.z); // e(x, y, z)
	this->realBounds.f = glm::vec3(this->realBounds.minX.x, this->realBounds.maxY.y, this->realBounds.minZ.z); // f(x, Y, z)
	this->realBounds.g = glm::vec3(this->realBounds.maxX.x, this->realBounds.maxY.y, this->realBounds.minZ.z); // g(X, Y, z)
	this->realBounds.h = glm::vec3(this->realBounds.maxX.x, this->realBounds.minY.y, this->realBounds.minZ.z); // h(X, y, z)

	this->realBounds.XYZ = this->realBounds.b;
	this->realBounds.xyz = this->realBounds.e;
}


float Entity::getInternalBoundingSphere(bool calculate) {
	if (calculate) {
		calculateInternalBoundingSphere();
	}

	return(this->maxDistInt * this->scaleFactor.x);
}

void Entity::calculateInternalBoundingSphere() {

	if (this->maxDistInt < abs(this->originalBounds.minX.x))
		this->maxDistInt = abs(this->originalBounds.minX.x);

	if (this->maxDistInt < abs(this->originalBounds.maxX.x))
		this->maxDistInt = abs(this->originalBounds.maxX.x);

	if (this->maxDistInt < abs(this->originalBounds.minY.y))
		this->maxDistInt = abs(this->originalBounds.minY.y);

	if (this->maxDistInt < abs(this->originalBounds.maxY.y))
		this->maxDistInt = abs(this->originalBounds.maxY.y);

	if (this->maxDistInt < abs(this->originalBounds.minZ.z))
		this->maxDistInt = abs(this->originalBounds.minZ.z);

	if (this->maxDistInt < abs(this->originalBounds.maxZ.z))
		this->maxDistInt = abs(this->originalBounds.maxZ.z);

	this->maxDistInt;
}


float Entity::getExternalBoundingSphere(bool calculate) {
	if (calculate) {
		calculateExternalBoundingSphere();
	}

	return(this->maxDistExt * this->scaleFactor.x);
}

void Entity::calculateExternalBoundingSphere() {
	std::vector<glm::vec3> array;

	array.push_back(this->originalBounds.a);
	array.push_back(this->originalBounds.b);
	array.push_back(this->originalBounds.c);
	array.push_back(this->originalBounds.d);
	array.push_back(this->originalBounds.e);
	array.push_back(this->originalBounds.f);
	array.push_back(this->originalBounds.g);
	array.push_back(this->originalBounds.h);

	float dist = 0;

	for (int i = 0; i < array.size(); i++) {
		dist = sqrt(pow(array[i].x, 2) + pow(array[i].y, 2) + pow(array[i].z, 2));

		if (dist > this->maxDistExt) {
			this->maxDistExt = dist;
		}
	}
}


float Entity::getBoundingSphere(bool calculate) {
	if (calculate) {
		calculateBoundingSphere();
	}

	return(this->maxDist * this->scaleFactor.x);
}

void Entity::calculateBoundingSphere() {
	glm::vec3 vector;

	float dist = 0;

	float maxDist = 0;

	for (int i = 0; i < this->vertices.size(); i += 3) {
		vector.x = this->vertices[i];
		vector.y = this->vertices[i + 1];
		vector.z = this->vertices[i + 2];

		dist = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));

		if (dist > maxDist) {
			maxDist = dist;
		}
	}

	this->maxDist = maxDist;
}

/* UTILITIES */
/* -----------------------------------------------------------------------------------------------------------------------*/
void Entity::calculateModel() {
	this->modelMatrix = this->translation * this->rotation * this->scaleMatrix;
}

void Entity::createBuffer(std::vector<float> data, unsigned int* buffer) {
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, (*buffer));
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
}


void Entity::setToReflect(bool reflection) {
	this->toReflect = reflection;
}

bool Entity::getToReflect() {
	return(this->toReflect);
}