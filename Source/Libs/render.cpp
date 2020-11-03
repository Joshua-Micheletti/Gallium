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


unsigned int tmpBuffer;
GLuint frameBuffer;
unsigned int cubemap;
unsigned int texture;
unsigned int renderBuffer;
unsigned int image;
GLuint imageframebuffer;
unsigned int renderBuffer2;
unsigned int screenBuffer;
Shader *screenShader;
std::vector<float> square;
unsigned int uvBuffer;

void attachUniforms(Entity *entity, std::vector<uniform_t> uniformBuffer) {
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

void linkLayouts(Entity *entity, std::vector<char *> layoutBuffer) {
  for (int i = 0; i < layoutBuffer.size(); i++) {
    if (strcmp(layoutBuffer[i], "vertex") == 0) {
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, entity->getVertexBuffer());
      glVertexAttribPointer(0, 3,  GL_FLOAT,  GL_FALSE, 0, (void*)0);
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

void renderEntities() {
  for (int i = 0; i < entityBuffer.size(); i++) {
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

void setupRender() {
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
    unsigned int *data;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, res, res, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
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

  glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_DEPTH24_STENCIL8, res, res);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
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

void render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glActiveTexture(GL_TEXTURE0);

  glBindTexture(GL_TEXTURE_2D, texture);

  defaultCamera = 1;
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glViewport(0, 0, res, res);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, cubemap, 0);
  camera2.setOrientation(glm::vec3(0.0, 0.0, 0.0));
  renderEntities();
  glClear(GL_DEPTH_BUFFER_BIT);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, cubemap, 0);
  camera2.setOrientation(glm::vec3(0.0, 180.0, 0.0));
  renderEntities();
  glClear(GL_DEPTH_BUFFER_BIT);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, cubemap, 0);
  camera2.setOrientation(glm::vec3(0.0, -90.0, 90.0));
  renderEntities();
  glClear(GL_DEPTH_BUFFER_BIT);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, cubemap, 0);
  camera2.setOrientation(glm::vec3(0.0, -90.0, -90.0));
  renderEntities();
  glClear(GL_DEPTH_BUFFER_BIT);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, cubemap, 0);
  camera2.setOrientation(glm::vec3(0.0, 90.0, 0.0));
  renderEntities();
  glClear(GL_DEPTH_BUFFER_BIT);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, cubemap, 0);
  camera2.setOrientation(glm::vec3(0.0, 270.0, 0.0));
  renderEntities();
  glClear(GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, screenWidth, screenHeight);
  glBindFramebuffer(GL_FRAMEBUFFER, imageframebuffer);


  defaultCamera = 0;
  renderEntities();
  glClear(GL_DEPTH_BUFFER_BIT);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
  // clear all relevant buffers
  glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(screenShader->getID());

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, screenBuffer);
  glVertexAttribPointer(0, 2,  GL_FLOAT,  GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glVertexAttribPointer(1, 2,  GL_FLOAT,  GL_FALSE, 0, (void*)0);

  glBindTexture(GL_TEXTURE_2D, image);

  glDrawArrays(GL_TRIANGLES, 0, square.size());

  glEnable(GL_DEPTH_TEST);

  glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer);
}
