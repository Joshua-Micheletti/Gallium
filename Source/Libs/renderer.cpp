#include "renderer.h"
#include "entity.h"
#include "camera.h"
#include "shader.h"
#include <vector>
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <SFML\Graphics.hpp>
#include "init.h"
#include <iostream>
#include <string>
using namespace std;

Renderer::Renderer() {
	setupRender();
}


void Renderer::attachUniforms(Entity* entity, std::vector<uniform_t> uniformBuffer) {
	for (int i = 0; i < uniformBuffer.size(); i++) {
		if (strcmp(uniformBuffer[i].name, "modelMatrix") == 0) {
			glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(entity->getModelMatrix()[0][0]));
		}

		else if (strcmp(uniformBuffer[i].name, "viewMatrix") == 0) {
			if (entity->getName().compare("skybox") == 0) {
				glm::mat4 view = glm::mat4(glm::mat3(cameraBuffer[defaultCamera]->getViewMatrix()));
				glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(view[0][0]));
			}
			else {
				glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(cameraBuffer[defaultCamera]->getViewMatrix()[0][0]));
			}
		}

		else if (strcmp(uniformBuffer[i].name, "projectionMatrix") == 0) {
			glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(projectionBuffer[defaultCamera][0][0]));
		}

		else if (strcmp(uniformBuffer[i].name, "lightPosition") == 0) {
			glUniform3f(uniformBuffer[i].id, light->getWorldPosition().x, light->getWorldPosition().y, light->getWorldPosition().z);
		}

		else if (strcmp(uniformBuffer[i].name, "eyePosition") == 0) {
			glUniform3f(uniformBuffer[i].id, cameraBuffer[defaultCamera]->getPosition().x, cameraBuffer[defaultCamera]->getPosition().y, cameraBuffer[defaultCamera]->getPosition().z);
		}
	}
}

void Renderer::linkLayouts(Entity* entity, std::vector<char*> layoutBuffer) {
	for (int i = 0; i < layoutBuffer.size(); i++) {
		if (strcmp(layoutBuffer[i], "vertex") == 0) {
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, entity->getVertexBuffer());
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}

		if (strcmp(layoutBuffer[i], "uv") == 0) {
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, entity->getTexBuffer());
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}

		if (strcmp(layoutBuffer[i], "color") == 0) {
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, entity->getTexBuffer());
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}

		if (strcmp(layoutBuffer[i], "normal") == 0) {
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, entity->getNormalBuffer());
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
	}
}

void Renderer::renderEntities(bool reflection) {
	for (int i = 0; i < entityBuffer.size(); i++) {
		if (reflection) {
			if (entityBuffer[i]->getToReflect() == true) {
				// glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

				if (entityBuffer[i]->getName().compare("skybox") == 0) {
					glDepthMask(GL_FALSE);
				}

				glUseProgram(shaderBuffer[entityBuffer[i]->getShader()].getID());

				attachUniforms(entityBuffer[i], shaderBuffer[entityBuffer[i]->getShader()].getUniformBuffer());

				linkLayouts(entityBuffer[i], shaderBuffer[entityBuffer[i]->getShader()].getLayoutBuffer());

				if (entityBuffer[i]->getTexture() != 0) {
					glBindTexture(entityBuffer[i]->getTextureType(), entityBuffer[i]->getTexture());
				}

				switch (renderMode) {
				case wireframe:
					glDrawArrays(GL_LINES, 0, entityBuffer[i]->getVertices().size());
					break;

				case vertices:
					glPointSize(2.0f);
					glDrawArrays(GL_POINTS, 0, entityBuffer[i]->getVertices().size());
					break;

				default:
					glDrawArrays(entityBuffer[i]->getElements(), 0, entityBuffer[i]->getVertices().size());

				}

				glDepthMask(GL_TRUE);
				glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
			}
		}
		else {
			// glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

			if (entityBuffer[i]->getName().compare("skybox") == 0) {
				glDepthMask(GL_FALSE);
			}

			glUseProgram(shaderBuffer[entityBuffer[i]->getShader()].getID());

			attachUniforms(entityBuffer[i], shaderBuffer[entityBuffer[i]->getShader()].getUniformBuffer());

			linkLayouts(entityBuffer[i], shaderBuffer[entityBuffer[i]->getShader()].getLayoutBuffer());

			if (entityBuffer[i]->getTexture() != 0) {
				glBindTexture(entityBuffer[i]->getTextureType(), entityBuffer[i]->getTexture());
			}

			switch (renderMode) {
			case wireframe:
				glDrawArrays(GL_LINES, 0, entityBuffer[i]->getVertices().size());
				break;

			case vertices:
				glPointSize(2.0f);
				glDrawArrays(GL_POINTS, 0, entityBuffer[i]->getVertices().size());
				break;

			default:
				glDrawArrays(entityBuffer[i]->getElements(), 0, entityBuffer[i]->getVertices().size());

			}

			glDepthMask(GL_TRUE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		}
	}
}

void Renderer::setupRender() {
	reflectionRes = 4096;

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glGenBuffers(1, &tmpBuffer);

	frameBuffer = 0;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glGenTextures(1, &cubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
	for (int i = 0; i < 6; i++) {
		unsigned int* data;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, reflectionRes, reflectionRes, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP, cubemap, 0);

	glGenRenderbuffers(1, &renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glEnable(GL_MULTISAMPLE);

	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_DEPTH24_STENCIL8, reflectionRes, reflectionRes);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	glGenTextures(1, &image);
	glBindTexture(GL_TEXTURE_2D, image);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexImage2DMultisample(GL_TEXTURE_2D, 16, GL_RGB, screenWidth, screenHeight, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	imageframebuffer = 0;
	glGenFramebuffers(1, &imageframebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, imageframebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, image, 0);

	glGenRenderbuffers(1, &renderBuffer2);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer2);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer2);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	square.push_back(-1.0f);
	square.push_back(1.0f);

	square.push_back(-1.0f);
	square.push_back(-1.0f);

	square.push_back(1.0f);
	square.push_back(-1.0f);


	square.push_back(-1.0f);
	square.push_back(1.0f);

	square.push_back(1.0f);
	square.push_back(-1.0f);

	square.push_back(1.0f);
	square.push_back(1.0f);

	glGenBuffers(1, &screenBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, screenBuffer);
	glBufferData(GL_ARRAY_BUFFER, square.size() * sizeof(float), &square[0], GL_STATIC_DRAW);

	std::vector<float> uv;
	uv.push_back(0.0f);
	uv.push_back(1.0f);

	uv.push_back(0.0f);
	uv.push_back(0.0f);

	uv.push_back(1.0f);
	uv.push_back(0.0f);


	uv.push_back(0.0f);
	uv.push_back(1.0f);

	uv.push_back(1.0f);
	uv.push_back(0.0f);

	uv.push_back(1.0f);
	uv.push_back(1.0f);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(float), &uv[0], GL_STATIC_DRAW);

	screenShader = new Shader((char*)"screen shader");
	screenShader->loadShader((char*)"../Shader/screen/vertex.c", (char*)"../Shader/screen/fragment.c");
}

void Renderer::resetRender() {
	glBufferData(GL_ARRAY_BUFFER, data1.size() * sizeof(float), &data1[0], GL_STATIC_DRAW);

	glUseProgram(shaderBuffer[1].getID());
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
	glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, 255, 255, 255);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_LINES, 0, data1.size());

	glDisableVertexAttribArray(0);
}

void Renderer::renderReflectionCubemap() {
	defaultCamera = 1;
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, reflectionRes, reflectionRes);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, cubemap, 0);
	camera2.setOrientation(glm::vec3(0.0, 0.0, 0.0));
	renderEntities(true);
	glClear(GL_DEPTH_BUFFER_BIT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, cubemap, 0);
	camera2.setOrientation(glm::vec3(0.0, 180.0, 0.0));
	renderEntities(true);
	glClear(GL_DEPTH_BUFFER_BIT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, cubemap, 0);
	camera2.setOrientation(glm::vec3(0.0, -90.0, 90.0));
	renderEntities(true);
	glClear(GL_DEPTH_BUFFER_BIT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, cubemap, 0);
	camera2.setOrientation(glm::vec3(0.0, -90.0, -90.0));
	renderEntities(true);
	glClear(GL_DEPTH_BUFFER_BIT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, cubemap, 0);
	camera2.setOrientation(glm::vec3(0.0, 90.0, 0.0));
	renderEntities(true);
	glClear(GL_DEPTH_BUFFER_BIT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, cubemap, 0);
	camera2.setOrientation(glm::vec3(0.0, 270.0, 0.0));
	renderEntities(true);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderScreen() {
	glClear(GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(screenShader->getID());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, screenBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindTexture(GL_TEXTURE_2D, image);

	glDrawArrays(GL_TRIANGLES, 0, square.size());

	glEnable(GL_DEPTH_TEST);

	glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer);
}

void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, texture);

	if (doReflection) {
		renderReflectionCubemap();
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, imageframebuffer);

	defaultCamera = 0;

	renderEntities(false);

	displayBoundingBox();

	renderScreen();

	resetRender();
}


void Renderer::createCube(std::vector<float>* array, std::vector<glm::vec3> faces) {
	array->push_back(faces[0].x);
	array->push_back(faces[0].y);
	array->push_back(faces[0].z);
	array->push_back(faces[1].x);
	array->push_back(faces[1].y);
	array->push_back(faces[1].z);

	array->push_back(faces[1].x);
	array->push_back(faces[1].y);
	array->push_back(faces[1].z);
	array->push_back(faces[2].x);
	array->push_back(faces[2].y);
	array->push_back(faces[2].z);

	array->push_back(faces[2].x);
	array->push_back(faces[2].y);
	array->push_back(faces[2].z);
	array->push_back(faces[3].x);
	array->push_back(faces[3].y);
	array->push_back(faces[3].z);

	array->push_back(faces[3].x);
	array->push_back(faces[3].y);
	array->push_back(faces[3].z);
	array->push_back(faces[0].x);
	array->push_back(faces[0].y);
	array->push_back(faces[0].z);

	array->push_back(faces[0].x);
	array->push_back(faces[0].y);
	array->push_back(faces[0].z);
	array->push_back(faces[5].x);
	array->push_back(faces[5].y);
	array->push_back(faces[5].z);

	array->push_back(faces[1].x);
	array->push_back(faces[1].y);
	array->push_back(faces[1].z);
	array->push_back(faces[6].x);
	array->push_back(faces[6].y);
	array->push_back(faces[6].z);

	array->push_back(faces[2].x);
	array->push_back(faces[2].y);
	array->push_back(faces[2].z);
	array->push_back(faces[7].x);
	array->push_back(faces[7].y);
	array->push_back(faces[7].z);

	array->push_back(faces[3].x);
	array->push_back(faces[3].y);
	array->push_back(faces[3].z);
	array->push_back(faces[4].x);
	array->push_back(faces[4].y);
	array->push_back(faces[4].z);

	array->push_back(faces[5].x);
	array->push_back(faces[5].y);
	array->push_back(faces[5].z);
	array->push_back(faces[4].x);
	array->push_back(faces[4].y);
	array->push_back(faces[4].z);

	array->push_back(faces[4].x);
	array->push_back(faces[4].y);
	array->push_back(faces[4].z);
	array->push_back(faces[7].x);
	array->push_back(faces[7].y);
	array->push_back(faces[7].z);

	array->push_back(faces[7].x);
	array->push_back(faces[7].y);
	array->push_back(faces[7].z);
	array->push_back(faces[6].x);
	array->push_back(faces[6].y);
	array->push_back(faces[6].z);

	array->push_back(faces[6].x);
	array->push_back(faces[6].y);
	array->push_back(faces[6].z);
	array->push_back(faces[5].x);
	array->push_back(faces[5].y);
	array->push_back(faces[5].z);
}

void Renderer::createSphere(glm::vec3 center, float dist, int sides, std::vector<float>* data) {

	double pi = 3.1415926535897;

	glm::vec3 tmp;

	glm::vec3 tmp2;

	tmp = glm::vec3(dist, 0, 0) + center;

	for (float i = 0; i < 2 * pi; i += (2 * pi) / (float)sides) {
		tmp2.x = dist * cos(i);
		tmp2.y = dist * sin(i);
		tmp2.z = 0;

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);

		tmp = tmp2 + center;

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);
	}

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);

	tmp = glm::vec3(dist, 0, 0) + center;

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);



	tmp = glm::vec3(0, 0, dist) + center;

	for (float i = 0; i < 2 * pi; i += (2 * pi) / (float)sides) {
		tmp2.x = 0;
		tmp2.y = dist * sin(i);
		tmp2.z = dist * cos(i);

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);

		tmp = tmp2 + center;

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);
	}

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);

	tmp = glm::vec3(0, 0, dist) + center;

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);



	tmp = glm::vec3(0, 0, dist) + center;

	for (float i = 0; i < 2 * pi; i += (2 * pi) / (float)sides) {
		tmp2.x = dist * sin(i);
		tmp2.y = 0;
		tmp2.z = dist * cos(i);

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);

		tmp = tmp2 + center;

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);
	}

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);

	tmp = glm::vec3(0, 0, dist) + center;

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);
}

void Renderer::drawBoundingBox(bounds_t bounds, glm::vec3 color) {
	std::vector<float> data;
	std::vector<glm::vec3> faces;
	faces.push_back(bounds.a);
	faces.push_back(bounds.b);
	faces.push_back(bounds.c);
	faces.push_back(bounds.d);
	faces.push_back(bounds.e);
	faces.push_back(bounds.f);
	faces.push_back(bounds.g);
	faces.push_back(bounds.h);
	createCube(&data, faces);

	glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	glUseProgram(shaderBuffer[1].getID());

	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
	glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, color.x, color.y, color.z);

	glEnableVertexAttribArray(0);
	// glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_LINES, 0, data.size());

	glDisableVertexAttribArray(0);
}

void Renderer::drawBoundingSphere(float radius, glm::vec3 center, glm::vec3 color) {
	std::vector<float> data;

	createSphere(center, radius, 100, &data);
	glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	glUseProgram(shaderBuffer[1].getID());

	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
	glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, color.x, color.y, color.z);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_LINES, 0, data.size());

	glDisableVertexAttribArray(0);
}

void Renderer::displayBoundingBox() {
	for (int i = 0; i < entityBuffer.size(); i++) {
		if (drawOBB) {
			drawBoundingBox(entityBuffer[i]->getObjectBoundingBox(true), glm::vec3(1, 0, 0));
		}

		if (drawAABB1) {
			drawBoundingBox(entityBuffer[i]->getExternalAxisAlignedBoundingBox(true), glm::vec3(0, 1, 0));
		}

		if (drawAABB2) {
			drawBoundingBox(entityBuffer[i]->getInternalAxisAlignedBoundingBox(true), glm::vec3(0, 0, 1));
		}

		if (drawAABB3) {
			bounds_t internalWorldBounds;
			internalWorldBounds = entityBuffer[i]->getInternalAxisAlignedBoundingBox(true);

			bounds_t worldBounds;
			worldBounds = entityBuffer[i]->getExternalAxisAlignedBoundingBox(true);

			std::vector<float> data5;

			glm::vec3 a2 = glm::vec3((worldBounds.a.x + internalWorldBounds.a.x) / 2, (worldBounds.a.y + internalWorldBounds.a.y) / 2, (worldBounds.a.z + internalWorldBounds.a.z) / 2);
			glm::vec3 b2 = glm::vec3((worldBounds.b.x + internalWorldBounds.b.x) / 2, (worldBounds.b.y + internalWorldBounds.b.y) / 2, (worldBounds.b.z + internalWorldBounds.b.z) / 2);
			glm::vec3 c2 = glm::vec3((worldBounds.c.x + internalWorldBounds.c.x) / 2, (worldBounds.c.y + internalWorldBounds.c.y) / 2, (worldBounds.c.z + internalWorldBounds.c.z) / 2);
			glm::vec3 d2 = glm::vec3((worldBounds.d.x + internalWorldBounds.d.x) / 2, (worldBounds.d.y + internalWorldBounds.d.y) / 2, (worldBounds.d.z + internalWorldBounds.d.z) / 2);
			glm::vec3 e2 = glm::vec3((worldBounds.e.x + internalWorldBounds.e.x) / 2, (worldBounds.e.y + internalWorldBounds.e.y) / 2, (worldBounds.e.z + internalWorldBounds.e.z) / 2);
			glm::vec3 f2 = glm::vec3((worldBounds.f.x + internalWorldBounds.f.x) / 2, (worldBounds.f.y + internalWorldBounds.f.y) / 2, (worldBounds.f.z + internalWorldBounds.f.z) / 2);
			glm::vec3 g2 = glm::vec3((worldBounds.g.x + internalWorldBounds.g.x) / 2, (worldBounds.g.y + internalWorldBounds.g.y) / 2, (worldBounds.g.z + internalWorldBounds.g.z) / 2);
			glm::vec3 h2 = glm::vec3((worldBounds.h.x + internalWorldBounds.h.x) / 2, (worldBounds.h.y + internalWorldBounds.h.y) / 2, (worldBounds.h.z + internalWorldBounds.h.z) / 2);

			std::vector<glm::vec3> faces4;
			faces4.push_back(a2);
			faces4.push_back(b2);
			faces4.push_back(c2);
			faces4.push_back(d2);
			faces4.push_back(e2);
			faces4.push_back(f2);
			faces4.push_back(g2);
			faces4.push_back(h2);
			createCube(&data5, faces4);
			glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer);
			glBufferData(GL_ARRAY_BUFFER, data5.size() * sizeof(float), &data5[0], GL_STATIC_DRAW);

			glUseProgram(shaderBuffer[1].getID());

			glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
			glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
			glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
			glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, 0, 1, 1);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glPointSize(10.0f);

			glDrawArrays(GL_LINES, 0, data5.size());

			glDisableVertexAttribArray(0);
		}

		if (drawAABB4) {
			drawBoundingBox(entityBuffer[i]->getAxisAlignedBoundingBox(true), glm::vec3(1, 0, 1));
		}

		if (drawBS) {
			drawBoundingSphere(entityBuffer[i]->getInternalBoundingSphere(false), entityBuffer[i]->getWorldPosition(), glm::vec3(1, 1, 0));
		}

		if (drawBS2) {
			drawBoundingSphere(entityBuffer[i]->getExternalBoundingSphere(false), entityBuffer[i]->getWorldPosition(), glm::vec3(1, 0.5, 0));
		}

		if (drawBS3) {
			drawBoundingSphere(entityBuffer[i]->getBoundingSphere(false), entityBuffer[i]->getWorldPosition(), glm::vec3(0.5, 1, 0));
		}
	}
}


