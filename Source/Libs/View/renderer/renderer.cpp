#include "renderer.h"

// constructor method, sets up the renderer (reflection and post processing)
Renderer::Renderer() {
	this->Kernels = new Kernel();
	this->postProcessingEffect = 0;

	// sets the color to clear the color buffer with
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// enable multisampling
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);

	// enables back-face culling:
	// polygons aren't rendered if the vertices that define the triangle are seen clockwise or counterclockwise,
	// a face with vertices indexed in the opposite order suggest that it's being viewed from the other side,
	// which is usually the inside of the model, which doesn't need to be rendered
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// generate 1 generic buffer and assigns its ID to the variable tmpBuffer
	glGenBuffers(1, &this->tmpBuffer);


	/*--------------------------------------------------------------------------*/
	/*                             REFLECTION SETUP                             */
	/*--------------------------------------------------------------------------*/

	// defines the resolution of the reflection cubemap
	this->reflectionRes = 2048;

	// generate the framebuffer that is gonna store the view from the reflection camera
	glGenFramebuffers(1, &this->reflectionFBO);
	// bind the newly generated framebuffer to the default framebuffer, both in read and write
	glBindFramebuffer(GL_FRAMEBUFFER, this->reflectionFBO);

	/* ACTIVE FRAMEBUFFER: reflectionFBO */

	// generate a generic texture for the cubemap reflection
	glGenTextures(1, &this->reflectionCubemap);
	// actually creates and binds the cubemap placeholder to the actual cubemap
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->reflectionCubemap);

	/* ACTIVE TEXTURE: reflectionCubemap */

	// cycle through the faces of the cubemap
	for (int i = 0; i < 6; i++) {
		// generate an empty (NULL) texture at the target (active texture @ GL_TEXTURE_CUBE_MAP_POSITIVE_X ... GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
		// with no mipmap level, RGB color internal format, reflectionRex x reflectionRes for the resolution, no border, RGB color format,
		// UNSIGNED_BYTE pixel data format
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, this->reflectionRes, this->reflectionRes, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}

	// set texture parameters (GL_TEXTURE_CUBE_MAP = target (in this case it refers to cubemap))
	// set the texture display filter when switching mipmaps (needs more testing and studying)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// set the texture display filter when switching mipmaps (needs more testing and studying)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// set the texture to shrink or stretch to the edge of the texture space in the S, T and R axis
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// generates one render buffer to attach to the framebuffer to store the image data (more optimized than textures for targets)
	glGenRenderbuffers(1, &this->reflectionRBO);
	// bind renderBuffer to the default GL_RENDERBUFFER
	glBindRenderbuffer(GL_RENDERBUFFER, this->reflectionRBO);

	/* ACTIVE RENDERBUFFER: reflectionRBO */

	// define render buffer multisample (needs more study)
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_DEPTH24_STENCIL8, this->reflectionRes, this->reflectionRes);
	// attach renderBuffer to the current framebuffer (frameBuffer)
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->reflectionRBO);

	// set back the renderbuffer to the default renderbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	/* ACTIVE RENDERBUFFER: Default */

	/*-------------------------------------------------------------------------------*/
	/*                             POST PROCESSING SETUP                             */
	/*-------------------------------------------------------------------------------*/
	
	// create an empty texture object for screenTexture, this texture will be bound to the screenFBO
	// and will store the screen view image
	glGenTextures(1, &this->screenTexture);
	// bind the screenTexture texture as the main texture
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->screenTexture);
	
	/* ACTIVE TEXTURE: screenTexture */

	// create the actual texture for image with res: screenWidth x screenHeight
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, RM.samples(), GL_RGB, screenWidth, screenHeight, false);

	// create an empty texture for the depth texture
	glGenTextures(1, &this->screenDepthTexture);
	// bind the screenTexture texture as the main texture
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->screenDepthTexture);

	/* ACTIVE TEXTURE: screenDepthTexture */

	// create the actual texture for image with res: screenWidth x screenHeight
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, RM.samples(), GL_DEPTH_STENCIL, screenWidth, screenHeight, false);
	//glTextureParameteri(this->screenDepthTexture, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);
	// create the screenFBO (used for rendering the screen view to a texture)
	glGenFramebuffers(1, &this->screenFBO);
	// bind the screenFBO to be the default FBO
	glBindFramebuffer(GL_FRAMEBUFFER, this->screenFBO);

	glGenTextures(1, &this->outlineTextureMask);
	glBindTexture(GL_TEXTURE_2D, this->outlineTextureMask);
	//glTexImage2DMultisample(GL_TEXTURE_2D, samples, GL_RGB, screenWidth, screenHeight, false);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	

	/* ACTIVE FRAMEBUFFER: screenFBO */

	// attach the screenTexture to the screenFBO, so that the stuff rendered on the screenFBO can be saved to the screenTexture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->screenTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, this->screenDepthTexture, 0);

	int framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE) {
		printf("framebuffer error: %d\n", framebufferStatus);
	}

	glGenTextures(1, &this->postProcessingTexture);
	glBindTexture(GL_TEXTURE_2D, this->postProcessingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &this->postProcessingDepthTexture);
	glBindTexture(GL_TEXTURE_2D, this->postProcessingDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, screenWidth, screenHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffers(1, &this->postProcessingFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->postProcessingFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->postProcessingTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->postProcessingDepthTexture, 0);

	framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE) {
		printf("framebuffer error: %d\n", framebufferStatus);
	}

	// create a square of vertices for the post processing shader
	std::vector<float> square;
	square.push_back(-1.0f); // bottom-left
	square.push_back(1.0f);

	square.push_back(-1.0f); // top-left
	square.push_back(-1.0f);

	square.push_back(1.0f); //  top-right
	square.push_back(-1.0f);


	square.push_back(-1.0f); // bottom-left
	square.push_back(1.0f);

	square.push_back(1.0f); //  top-right
	square.push_back(-1.0f);

	square.push_back(1.0f); //  bottom-right
	square.push_back(1.0f);

	// create the VBO to store the square vertices
	glGenBuffers(1, &this->screenVBO);
	// set the current active VBO to the screenVBO
	glBindBuffer(GL_ARRAY_BUFFER, this->screenVBO);

	/* ACTIVE BUFFER: screenVBO */

	// pass the vertices to the buffer
	glBufferData(GL_ARRAY_BUFFER, square.size() * sizeof(float), &square[0], GL_STATIC_DRAW);

	// create the UV coordinates to map the screen texture to the screen square
	std::vector<float> uv;
	uv.push_back(0.0f); // bottom-left
	uv.push_back(1.0f);

	uv.push_back(0.0f); // top-left
	uv.push_back(0.0f);

	uv.push_back(1.0f); // top-right
	uv.push_back(0.0f);


	uv.push_back(0.0f); // bottom-left
	uv.push_back(1.0f);

	uv.push_back(1.0f); // top-right
	uv.push_back(0.0f);

	uv.push_back(1.0f); // bottom-right
	uv.push_back(1.0f);

	// create the VBO to store the UV vertices
	glGenBuffers(1, &this->screenUVVBO);
	// set the current active VBO to the screenUVVBO
	glBindBuffer(GL_ARRAY_BUFFER, this->screenUVVBO);

	/* ACTIVE BUFFER: screenUVVBO*/

	// pass the UV coordinates to the buffer
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(float), &uv[0], GL_STATIC_DRAW);

	RM.newShader("RS_ScreenShader");
	RM.shader("RS_ScreenShader")->loadShader("../Shader/screen/screen.vert", "../Shader/screen/screen.frag");

	RM.newShader("RS_DepthShader");
	RM.shader("RS_DepthShader")->loadShader("../Shader/depth/depth.vert", "../Shader/depth/depth.frag");

	RM.newShader("RS_PostProcessingShader");
	RM.shader("RS_PostProcessingShader")->loadShader("../Shader/postProcessing/postProcessing.vert", "../Shader/postProcessing/postProcessing.frag");

	int maxSamples;
	glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
	printf("max samples: %d\n", maxSamples);

	this->highlightedEntity = -1;
}


// public method for rendering the scene
void Renderer::render() {
	if (updateResolution) {
		this->resizeScreen();
	}

	// ------------------------------ REFLECTION FRAMEBUFFER RENDERING ------------------------------ //

	this->reflectionRenderTime = glfwGetTime();

	// check if the program should render the reflection cubemap
	if (doReflection) {
		glBindFramebuffer(GL_FRAMEBUFFER, this->reflectionFBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render the reflection cubemap
		this->renderReflectionCubemap();
	}	

	this->reflectionRenderTime = glfwGetTime() - this->reflectionRenderTime;

	// -------------------------------- SCREEN FRAMEBUFFER RENDERING -------------------------------- //

	this->forwardRenderTime = glfwGetTime();

	glBindFramebuffer(GL_FRAMEBUFFER, this->screenFBO);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP,	   // stencil fail
				GL_KEEP,	   // stencil pass, depth fail
				GL_REPLACE);   // stencil pass, depth pass
	
	glStencilMask(255);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilMask(0);
	glStencilFunc(GL_ALWAYS, 1, 255);
	this->renderSkybox();
	this->renderEntities(false);
	
	// draw the bounding box for each entity
	// this->displayBoundingBox();

	this->forwardRenderTime = glfwGetTime() - this->forwardRenderTime;

	// ---------------------------- POST PROCESSING FRAMEBUFFER RENDERING --------------------------- //

	this->MSPostProcessingPassTime = glfwGetTime();

	this->renderMultisamplePostProcessing();

	this->MSPostProcessingPassTime = glfwGetTime() - this->MSPostProcessingPassTime;


	this->postProcessingPassTime = glfwGetTime();

	if (RM.selectedEntity().size() != 0 && (outlineType == 0 || outlineType == 1)) {
		this->renderOutline();
	}

	// ---------------------------------- OUT FRAMEBUFFER RENDERING --------------------------------- //


	this->renderScreen();

	this->postProcessingPassTime = glfwGetTime() - this->postProcessingPassTime;
}


// render the cubemap view from the reflection camera to later calculate reflections on
void Renderer::renderReflectionCubemap() {
	
// 	// set the current camera to the camera inside the reflective object
// 	defaultCamera = 1;

// 	/* ACTIVE CAMERA: camera2 */
// 	// set the viewport to fit the reflection texture resolution
	
// 	glViewport(0, 0, reflectionRes, reflectionRes);

// 	// cycle all the faces of the cubemap
// 	for (int i = 0; i < 6; i++) {
// 		// attach the positive X texture of the reflectionCubemap to the color buffer of the reflectionFBO
// 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->reflectionCubemap, 0);
// 		// aim the camera to face the correct direction
// 		if (i == 0)      // FRONT
// 			camera2.setOrientation(glm::vec3(0.0, 0.0, 0.0));
// 		else if (i == 1) // BACK
// 			camera2.setOrientation(glm::vec3(0.0, 180.0, 0.0));
// 		else if (i == 2) // TOP
// 			camera2.setOrientation(glm::vec3(0.0, -90.0, 90.0));
// 		else if (i == 3) // BOTTOM
// 			camera2.setOrientation(glm::vec3(0.0, -90.0, -90.0));
// 		else if (i == 4) // RIGHT
// 			camera2.setOrientation(glm::vec3(0.0, 90.0, 0.0));
// 		else             // LEFT
// 			camera2.setOrientation(glm::vec3(0.0, 270.0, 0.0));

// 		// render all entities except for the ones that shouldn't be rendered in the reflection
// 		this->renderEntities(true);
// 		// clear the depth buffers from the reflectionFBO
// 		glClear(GL_DEPTH_BUFFER_BIT);
// 	}

// 	// reset the viewport
// 	glViewport(0, 0, screenWidth, screenHeight);

// 	// set the render camera to the default camera
// 	defaultCamera = 0;

// 	/* ACTIVE CAMERA: camera1 */
}

// render all entities with their corresponding shader (forward rendering)
void Renderer::renderEntities(bool reflection) {
	std::vector<DrawingEntity*> drawingEntities = RM.drawingEntities(); 
	// render entities
	for (int i = 0; i < drawingEntities.size(); i++) {
		if (drawingEntities[i] != RM.drawingEntity(RM.skybox()) && drawingEntities[i] != RM.drawingEntity(RM.selectedEntity())) {
			DrawingEntity* currentDE = drawingEntities[i];
			Model* currentM = RM.model(currentDE->model());
			Material* currentMA = RM.material(currentDE->material());
			Shader* currentS = RM.shader(currentMA->shader());
			Texture* currentT = RM.texture(currentMA->texture());

		// if it's rendering entities to be displayed in the reflection:
		// if (reflection) {
		// 	// check what entities are supposed to be rendered in the reflection
		// 	if (entityBuffer[i]->getToReflect() == true) {

		// 		// installs the shader to render the entity (it gets the shader from the entity)
		// 		glUseProgram(shaderBuffer[entityBuffer[i]->getShader()].getID());

		// 		// pass the values for the shader uniforms.
		// 		// shader uniforms are global variables for shaders that can be set by the user.
		// 		// uniforms are global to all shaders, so they don't need to be set by every shader call if the value doesn't change
		// 		// for example matrices for 3D rendering usually don't change between shaders (some optimization is possible)
		// 		this->attachUniforms(entityBuffer[i], shaderBuffer[entityBuffer[i]->getShader()].getUniformBuffer());

		// 		// link the layouts to the data origin.
		// 		// layouts define where the data for a certain variable comes from
		// 		this->linkLayouts(entityBuffer[i], shaderBuffer[entityBuffer[i]->getShader()].getLayoutBuffer());

		// 		// if the entity has a texture attached to it
		// 		if (entityBuffer[i]->getTexture() != 0) {
		// 			// bind it as the current active texture
		// 			glBindTexture(entityBuffer[i]->getTextureType(), entityBuffer[i]->getTexture());
		// 		}

		// 		// check which mode things should be rendered as
		// 		else {
		// 			switch (renderMode) {
		// 				// draw lines
		// 			case wireframe:
		// 				glDrawArrays(GL_LINES, 0, entityBuffer[i]->getVertices().size());
		// 				break;

		// 				// draw points
		// 			case vertices:
		// 				glPointSize(2.0f);
		// 				glDrawArrays(GL_POINTS, 0, entityBuffer[i]->getVertices().size());
		// 				break;

		// 				// draw in the element's primitive (mainly triangles)
		// 			default:
		// 				glDrawArrays(entityBuffer[i]->getElements(), 0, entityBuffer[i]->getVertices().size());
		// 			}
		// 		}
		// 	}
		// }

		// else {
			// if (i != this->highlightedEntity) {
				// printf("got into the highlighted part\n");
				// if (entityBuffer[i]->getName().compare("skybox") == 0) {
				// 	glDepthMask(GL_FALSE);
				// }

				glUseProgram(currentS->id());
				attachUniforms(currentDE, currentS->uniformBuffer());
				linkLayouts(currentM, currentS->layoutBuffer());

				// THINK IF BINDING A PLACEHOLDER TEX EVERY FRAME IS HEAVY
				// if (entityBuffer[i]->getTexture() != 0) {
					// glBindTexture(entityBuffer[i]->getTextureType(), entityBuffer[i]->getTexture());
				glBindTexture(GL_TEXTURE_2D, currentT->id());
				// }

				// if (strcmp(shaderBuffer[entityBuffer[i]->getShader()].getName(), "reflection") == 0 ||
				// 	strcmp(shaderBuffer[entityBuffer[i]->getShader()].getName(), "refraction/glass") == 0 ||
				// 	strcmp(shaderBuffer[entityBuffer[i]->getShader()].getName(), "reflection/diamond") == 0) {
				// 	if (doReflection) {
				// 		glBindTexture(GL_TEXTURE_CUBE_MAP, this->reflectionCubemap);
				// 	}
				// 	else {
				// 		glBindTexture(GL_TEXTURE_CUBE_MAP, entityBuffer[0]->getTexture());
				// 	}
					
				// }

				// check which mode things should be rendered as
				// else {
				// 	switch (renderMode) {
				// 	case wireframe:
				// 		glLineWidth(5.0f);
				// 		glDrawArrays(GL_LINES, 0, entityBuffer[i]->getVertices().size());
				// 		break;

				// 	case vertices:
				// 		glPointSize(2.0f);
				// 		glDrawArrays(GL_POINTS, 0, entityBuffer[i]->getVertices().size());
				// 		break;

				// 	default:
				// 		glDrawArrays(entityBuffer[i]->getElements(), 0, entityBuffer[i]->getVertices().size());
				// 	}
				// }
				glDrawArrays(currentM->drawingMode(), 0, currentM->vertices().size() / 3);
			// }
		// }

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		}
	}
	
	// render highlighted entity
	// printf("%s\n", RM.selectedEntity().c_str());
	if (RM.selectedEntity().size() != 0 && reflection == false) {
		glStencilFunc(GL_ALWAYS, 1, 255);
		glStencilMask(255);
		this->renderEntity(RM.selectedEntity());
		glStencilMask(0);
		glStencilFunc(GL_NOTEQUAL, 1, 255);

		glDisable(GL_DEPTH_TEST);
		std::string previousShader = RM.material(RM.drawingEntity(RM.selectedEntity())->material())->shader();
		RM.material(RM.drawingEntity(RM.selectedEntity())->material())->shader(RM.highlightShader());
		this->renderEntity(RM.selectedEntity());
		RM.material(RM.drawingEntity(RM.selectedEntity())->material())->shader(previousShader);
		glEnable(GL_DEPTH_TEST);

		// wireframe outline implementation
		// if (outlineType == 2) {
		// 	glDisable(GL_DEPTH_TEST);
		// 	glPolygonMode(GL_FRONT, GL_LINE);
		// 	glLineWidth(10.0f);
		// 	int previousShader = entityBuffer[this->highlightedEntity]->getShader();
		// 	entityBuffer[this->highlightedEntity]->setShader(11);
		// 	this->renderEntity(entityBuffer[this->highlightedEntity]);
		// 	entityBuffer[this->highlightedEntity]->setShader(previousShader);
		// 	glLineWidth(1.0f);
		// 	glPolygonMode(GL_FRONT, GL_FILL);
		// 	glEnable(GL_DEPTH_TEST);
		// }
	}
}

void Renderer::renderEntity(std::string entity) {
	DrawingEntity* currentDE = RM.drawingEntity(entity);
	Model* currentM = RM.model(currentDE->model());
	Material* currentMA = RM.material(currentDE->material());
	Shader* currentS = RM.shader(currentMA->shader());
	Texture* currentT = RM.texture(currentMA->texture());

	glUseProgram(currentS->id());

	attachUniforms(currentDE, currentS->uniformBuffer());

	linkLayouts(currentM, currentS->layoutBuffer());

	// if (entity->getTexture() != 0) {
		glBindTexture(GL_TEXTURE_2D, currentT->id());
	// }

	// if (strcmp(shaderBuffer[entity->getShader()].getName(), "reflection") == 0 ||
	// 	strcmp(shaderBuffer[entity->getShader()].getName(), "refraction/glass") == 0 ||
	// 	strcmp(shaderBuffer[entity->getShader()].getName(), "reflection/diamond") == 0) {
	// 	if (doReflection) {
	// 		glBindTexture(GL_TEXTURE_CUBE_MAP, this->reflectionCubemap);
	// 	}
	// 	else {
	// 		glBindTexture(GL_TEXTURE_CUBE_MAP, entityBuffer[0]->getTexture());
	// 	}
	// }


	// check which mode things should be rendered as
	// if (entity->getName().compare("skybox") == 0) {
	// 	// render the skybox
	// 	glDrawArrays(GL_TRIANGLES, 0, entity->getVertices().size());
	// 	// re-enable the depth mask (now rendering also affects the depth buffer as well)
	// 	glDepthMask(GL_TRUE);
	// }

	// else {
	// 	switch (renderMode) {
	// 	case wireframe:
	// 		glDrawArrays(GL_LINES, 0, entity->getVertices().size());
	// 		break;

	// 	case vertices:
	// 		glPointSize(2.0f);
	// 		glDrawArrays(GL_POINTS, 0, entity->getVertices().size());
	// 		break;

	// 	default:
	// 		glDrawArrays(entity->getElements(), 0, entity->getVertices().size());

	// 	}
	// }

	glDrawArrays(currentM->drawingMode(), 0, currentM->vertices().size() / 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Renderer::renderSkybox() {
	// disable depth
	glDepthMask(GL_FALSE);
	// disable backface culling
	glDisable(GL_CULL_FACE);

	// extract the skybox components
	DrawingEntity* skyboxDE = RM.drawingEntity(RM.skybox());
	Model* skyboxM = RM.model(skyboxDE->model());
	Material* skyboxMA = RM.material(skyboxDE->material());
	Shader* skyboxS = RM.shader(skyboxMA->shader());
	Texture* skyboxT = RM.texture(skyboxMA->texture());

	// bind the shader
	glUseProgram(skyboxS->id());
	// attach the shader uniforms
	attachUniforms(skyboxDE, skyboxS->uniformBuffer());
	// link the shader layouts
	linkLayouts(skyboxM, skyboxS->layoutBuffer());
	// bind the skybox texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxT->id());
	// render the skybox
	glDrawArrays(skyboxM->drawingMode(), 0, skyboxM->vertices().size() / 3);

	// re-enable the depth mask (now rendering also affects the depth buffer as well)
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
}

void Renderer::renderOutline() {
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->outlineTextureMask, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);

	std::string previousShader = RM.material(RM.drawingEntity(RM.selectedEntity())->material())->shader();
	RM.material(RM.drawingEntity(RM.selectedEntity())->material())->shader("S_Light");
	this->renderEntity(RM.selectedEntity());
	RM.material(RM.drawingEntity(RM.selectedEntity())->material())->shader(previousShader);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->postProcessingTexture, 0);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);

	int shaderOutline;
	if (outlineType == 0) {
		shaderOutline = 12;
	}
	else if (outlineType == 1) {
		shaderOutline = 14;
	}

	glUseProgram(RM.shader(RM.outlineShader())->id());

	int screenTexUniformID = glGetUniformLocation(RM.shader(RM.outlineShader())->id(), "screenTexture");
	int outlineMaskUniformID = glGetUniformLocation(RM.shader(RM.outlineShader())->id(), "outlineMask");

	glUniform1i(screenTexUniformID, 0);
	glUniform1i(outlineMaskUniformID, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->postProcessingTexture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->outlineTextureMask);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->screenVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->screenUVVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
}


void Renderer::renderMultisamplePostProcessing() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->postProcessingFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

	if (RM.depth()) {
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->screenDepthTexture);
		glUseProgram(RM.shader("RS_DepthShader")->id());
		glUniform1i(glGetUniformLocation(RM.shader("RS_DepthShader")->id(), "samples"), RM.samples());
	}
	else {
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->screenTexture);
		glUseProgram(RM.shader("RS_ScreenShader")->id());
		glUniform1i(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "samples"), RM.samples());

		glUniform1i(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "effect"), this->postProcessingEffect);

		if (this->postProcessingEffect == 2) {
			glUniform3f(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "filterColor"), this->filterColor.x, this->filterColor.y, this->filterColor.z);
		}

		else if (this->postProcessingEffect == 9) {
			int kernelSize = this->Kernels->getKernelSize();

			glUniform1i(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "kernelSize_f"), kernelSize);
			glUniform1fv(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "kernel_f"), kernelSize * kernelSize, this->Kernels->getKernel());
		}
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->screenVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->screenUVVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_DEPTH_TEST);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

// render the screen texture applying post processing shaders
void Renderer::renderScreen() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// disable depth test so screen-space quad isn't discarded due to depth test.
	glDisable(GL_DEPTH_TEST); 

	// enable the texture slot 0
	glActiveTexture(GL_TEXTURE0);
	// bind the post processed texture
	glBindTexture(GL_TEXTURE_2D, this->postProcessingTexture);
	// bind the post processing shader
	glUseProgram(RM.shader("RS_PostProcessingShader")->id());

	// bind the VBOs
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->screenVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->screenUVVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// bind the uniform
	int screenTexUniformID = glGetUniformLocation(RM.shader("RS_PostProcessingShader")->id(), "screenTexture");
	glUniform1i(screenTexUniformID, 0);

	// draw the quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// re-enable depth testing
	glEnable(GL_DEPTH_TEST);
}

void Renderer::resetRender() {
// 	glBufferData(GL_ARRAY_BUFFER, data1.size() * sizeof(float), &data1[0], GL_STATIC_DRAW);

// 	glUseProgram(shaderBuffer[1].getID());
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
// 	glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, 255, 255, 255);

// 	glEnableVertexAttribArray(0);

// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

// 	glDrawArrays(GL_LINES, 0, data1.size());

// 	glDisableVertexAttribArray(0);
}

void Renderer::resizeScreen() {
	// create an empty texture object for screenTexture, this texture will be bound to the screenFBO
	// and will store the screen view image
	glDeleteTextures(1, &this->screenTexture);
	glGenTextures(1, &this->screenTexture);
	// bind the screenTexture texture as the main texture
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->screenTexture);

	/* ACTIVE TEXTURE: screenTexture */

	// create the actual texture for image with res: screenWidth x screenHeight
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, RM.samples(), GL_RGB, window.framebufferWidth(), window.framebufferHeight(), false);
	printf("%d, %d\n", window.width(), window.height());

	// set the texture filters for mipmaps
	glDeleteTextures(1, &this->screenDepthTexture);
	glGenTextures(1, &this->screenDepthTexture);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->screenDepthTexture);

	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, RM.samples(), GL_DEPTH_STENCIL, window.framebufferWidth(), window.framebufferHeight(), false);

	glDeleteTextures(1, &this->outlineTextureMask);
	glGenTextures(1, &this->outlineTextureMask);
	glBindTexture(GL_TEXTURE_2D, this->outlineTextureMask);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.framebufferWidth(), window.framebufferHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glDeleteTextures(1, &this->postProcessingTexture);
	glGenTextures(1, &this->postProcessingTexture);
	glBindTexture(GL_TEXTURE_2D, this->postProcessingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.framebufferWidth(), window.framebufferHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glDeleteTextures(1, &this->postProcessingDepthTexture);
	glGenTextures(1, &this->postProcessingDepthTexture);
	glBindTexture(GL_TEXTURE_2D, this->postProcessingDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, window.framebufferWidth(), window.framebufferHeight(), 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glDeleteFramebuffers(1, &this->postProcessingFBO);
	glGenFramebuffers(1, &this->postProcessingFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->postProcessingFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->postProcessingTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->postProcessingDepthTexture, 0);

	// create the screenFBO (used for rendering the screen view to a texture)
	glDeleteFramebuffers(1, &this->screenFBO);
	glGenFramebuffers(1, &this->screenFBO);
	// bind the screenFBO to be the default FBO
	glBindFramebuffer(GL_FRAMEBUFFER, this->screenFBO);

	/* ACTIVE FRAMEBUFFER: screenFBO */

	// attach the screenTexture to the screenFBO, so that the stuff rendered on the screenFBO can be saved to the screenTexture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->screenTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, this->screenDepthTexture, 0);

	// glViewport(0, 0, window.width(), window.height());

	// projectionBuffer[0] = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 10000.0f);
	RM.projection(glm::perspective(glm::radians(45.0f), (float)window.framebufferWidth() / (float)window.framebufferHeight(), 0.1f, 10000.0f));
	updated = true;
	// updateResolution = false;
}

void Renderer::displayBoundingBox() {
// 	for (int i = 0; i < entityBuffer.size(); i++) {
// 		if (drawOBB) {
// 			drawBoundingBox(entityBuffer[i]->getObjectBoundingBox(true), glm::vec3(1, 0, 0));
// 		}

// 		if (drawAABB1) {
// 			drawBoundingBox(entityBuffer[i]->getExternalAxisAlignedBoundingBox(true), glm::vec3(0, 1, 0));
// 		}

// 		if (drawAABB2) {
// 			drawBoundingBox(entityBuffer[i]->getInternalAxisAlignedBoundingBox(true), glm::vec3(0, 0, 1));
// 		}

// 		if (drawAABB3) {
// 			bounds_t internalWorldBounds;
// 			internalWorldBounds = entityBuffer[i]->getInternalAxisAlignedBoundingBox(true);

// 			bounds_t worldBounds;
// 			worldBounds = entityBuffer[i]->getExternalAxisAlignedBoundingBox(true);

// 			std::vector<float> data5;

// 			glm::vec3 a2 = glm::vec3((worldBounds.a.x + internalWorldBounds.a.x) / 2, (worldBounds.a.y + internalWorldBounds.a.y) / 2, (worldBounds.a.z + internalWorldBounds.a.z) / 2);
// 			glm::vec3 b2 = glm::vec3((worldBounds.b.x + internalWorldBounds.b.x) / 2, (worldBounds.b.y + internalWorldBounds.b.y) / 2, (worldBounds.b.z + internalWorldBounds.b.z) / 2);
// 			glm::vec3 c2 = glm::vec3((worldBounds.c.x + internalWorldBounds.c.x) / 2, (worldBounds.c.y + internalWorldBounds.c.y) / 2, (worldBounds.c.z + internalWorldBounds.c.z) / 2);
// 			glm::vec3 d2 = glm::vec3((worldBounds.d.x + internalWorldBounds.d.x) / 2, (worldBounds.d.y + internalWorldBounds.d.y) / 2, (worldBounds.d.z + internalWorldBounds.d.z) / 2);
// 			glm::vec3 e2 = glm::vec3((worldBounds.e.x + internalWorldBounds.e.x) / 2, (worldBounds.e.y + internalWorldBounds.e.y) / 2, (worldBounds.e.z + internalWorldBounds.e.z) / 2);
// 			glm::vec3 f2 = glm::vec3((worldBounds.f.x + internalWorldBounds.f.x) / 2, (worldBounds.f.y + internalWorldBounds.f.y) / 2, (worldBounds.f.z + internalWorldBounds.f.z) / 2);
// 			glm::vec3 g2 = glm::vec3((worldBounds.g.x + internalWorldBounds.g.x) / 2, (worldBounds.g.y + internalWorldBounds.g.y) / 2, (worldBounds.g.z + internalWorldBounds.g.z) / 2);
// 			glm::vec3 h2 = glm::vec3((worldBounds.h.x + internalWorldBounds.h.x) / 2, (worldBounds.h.y + internalWorldBounds.h.y) / 2, (worldBounds.h.z + internalWorldBounds.h.z) / 2);

// 			std::vector<glm::vec3> faces4;
// 			faces4.push_back(a2);
// 			faces4.push_back(b2);
// 			faces4.push_back(c2);
// 			faces4.push_back(d2);
// 			faces4.push_back(e2);
// 			faces4.push_back(f2);
// 			faces4.push_back(g2);
// 			faces4.push_back(h2);
// 			createCube(&data5, faces4);
// 			glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer);
// 			glBufferData(GL_ARRAY_BUFFER, data5.size() * sizeof(float), &data5[0], GL_STATIC_DRAW);

// 			glUseProgram(shaderBuffer[1].getID());

// 			glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
// 			glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
// 			glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
// 			glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, 0, 1, 1);

// 			glEnableVertexAttribArray(0);
// 			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

// 			glPointSize(10.0f);

// 			glDrawArrays(GL_LINES, 0, data5.size());

// 			glDisableVertexAttribArray(0);
// 		}

// 		if (drawAABB4) {
// 			drawBoundingBox(entityBuffer[i]->getAxisAlignedBoundingBox(true), glm::vec3(1, 0, 1));
// 		}

// 		if (drawBS) {
// 			drawBoundingSphere(entityBuffer[i]->getInternalBoundingSphere(false), entityBuffer[i]->getWorldPosition(), glm::vec3(1, 1, 0));
// 		}

// 		if (drawBS2) {
// 			drawBoundingSphere(entityBuffer[i]->getExternalBoundingSphere(false), entityBuffer[i]->getWorldPosition(), glm::vec3(1, 0.5, 0));
// 		}

// 		if (drawBS3) {
// 			drawBoundingSphere(entityBuffer[i]->getBoundingSphere(false), entityBuffer[i]->getWorldPosition(), glm::vec3(0.5, 1, 0));
// 		}
// 	}
}

// // pass the correct values to the corresponding uniforms in the shader
void Renderer::attachUniforms(DrawingEntity* entity, std::vector<uniform_t> uniformBuffer) {
	// cycle through the uniformBuffer of the shader
	for (int i = 0; i < uniformBuffer.size(); i++) {
		// if the uniform is "modelMatrix", set it to the entity modelMatrix
		if (strcmp(uniformBuffer[i].name, "modelMatrix") == 0) {
			// glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(entity->getModelMatrix()[0][0]));
			glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(entity->modelMatrix()[0][0]));
		}

		// if the uniform is "viewMatrix", set it to the camera viewMatrix
		else if (strcmp(uniformBuffer[i].name, "viewMatrix") == 0) {
			// if the entity we're rendering is the skybox, 
			if (entity == RM.drawingEntity(RM.skybox())) {
			// 	// this process removes all the translations from the camera, this way camera movement is not taken into account
				glm::mat4 staticCameraView = glm::mat4(glm::mat3(RM.camera()->viewMatrix()));
				glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(staticCameraView[0][0]));
			}
			// otherwise pass the camera view matrix, including all translations
			else {
				// glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(cameraBuffer[defaultCamera]->getViewMatrix()[0][0]));
				glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(RM.camera()->viewMatrix()[0][0]));
			}
		}

		// if the uniform is "projectionMatrix", set it to the main camera projection matrix in the projectionBuffer
		else if (strcmp(uniformBuffer[i].name, "projectionMatrix") == 0) {
			glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(RM.projection()[0][0]));
		}

		// if the uniform is "lightPosition", pass the light position (x, y, z)
		else if (strcmp(uniformBuffer[i].name, "lightPosition") == 0) {
			glm::vec3 lightPosition = RM.drawingEntity(RM.mainLight())->position();
			glUniform3f(uniformBuffer[i].id, lightPosition.x, lightPosition.y, lightPosition.z);
		}

		// if the uniform is "eyePosition", pass the camera position (x, y, z)
		else if (strcmp(uniformBuffer[i].name, "eyePosition") == 0) {
			glm::vec3 cameraPosition = RM.camera()->position();
			glUniform3f(uniformBuffer[i].id, cameraPosition.x, cameraPosition.y, cameraPosition.z);
		}

		else if (strcmp(uniformBuffer[i].name, "lightColor") == 0) {
			glm::vec3 lightColor = RM.drawingEntity(RM.mainLight())->lightColor();
			glUniform3f(uniformBuffer[i].id, lightColor.x, lightColor.y, lightColor.z);
		}

		else if (strcmp(uniformBuffer[i].name, "ambient") == 0) {
			glm::vec3 ambient = RM.material(entity->material())->ambient();
			glUniform3f(uniformBuffer[i].id, ambient.x, ambient.y, ambient.z);
		}

		else if (strcmp(uniformBuffer[i].name, "diffuse") == 0) {
			glm::vec3 diffuse = RM.material(entity->material())->diffuse();
			glUniform3f(uniformBuffer[i].id, diffuse.x, diffuse.y, diffuse.z);
		}

		else if (strcmp(uniformBuffer[i].name, "specular") == 0) {
			glm::vec3 specular = RM.material(entity->material())->specular();
			glUniform3f(uniformBuffer[i].id, specular.x, specular.y, specular.z);
		}

		else if (strcmp(uniformBuffer[i].name, "shininess") == 0) {
			glUniform1f(uniformBuffer[i].id, RM.material(entity->material())->shininess());
		}

		else if (strcmp(uniformBuffer[i].name, "lightAmbient") == 0) {
			glm::vec3 ambient = RM.material(RM.drawingEntity(RM.mainLight())->material())->ambient();
			glUniform3f(uniformBuffer[i].id, ambient.x, ambient.y, ambient.z);
		}

		else if (strcmp(uniformBuffer[i].name, "lightDiffuse") == 0) {
			glm::vec3 diffuse = RM.material(RM.drawingEntity(RM.mainLight())->material())->diffuse();
			glUniform3f(uniformBuffer[i].id, diffuse.x, diffuse.y, diffuse.z);
		}

		else if (strcmp(uniformBuffer[i].name, "lightSpecular") == 0) {
			glm::vec3 specular = RM.material(RM.drawingEntity(RM.mainLight())->material())->specular();
			glUniform3f(uniformBuffer[i].id, specular.x, specular.y, specular.z);
		}
	}
}

// // link layouts to the data origin (mainly VAO)
void Renderer::linkLayouts(Model* model, std::vector<std::string> layoutBuffer) {
	// cycle all the layouts in the layout buffer of the shader
	for (int i = 0; i < layoutBuffer.size(); i++) {
		// if the layout is named "vertex" (contains the entity vertices that make the geometry of the entity)
		if (strcmp(layoutBuffer[i].c_str(), "vertex") == 0) {
			// enable the VAO in position 0
			glEnableVertexAttribArray(0);
			// bind the geometry VBO of the entity
			glBindBuffer(GL_ARRAY_BUFFER, model->vertexBuffer());
			// setup the VAO to reference the VBO (needs more study)
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		// if the layout is named "uv" (contains the UV coordinates to map the texture to the geometry)
		else if (strcmp(layoutBuffer[i].c_str(), "uv") == 0) {
			// enable the VAO in position 1
			glEnableVertexAttribArray(1);
			// bind the UV VBO of the entity
			glBindBuffer(GL_ARRAY_BUFFER, model->uvBuffer());
			// setup the VAO to reference the VBO (needs more study)
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		// if the layout is named "color" (contains the color vectors that make the entity color)
		else if (strcmp(layoutBuffer[i].c_str(), "color") == 0) {
			// enable the VAO in position 1
			glEnableVertexAttribArray(1);
			// bind the color VBO of the entity
			glBindBuffer(GL_ARRAY_BUFFER, model->uvBuffer());
			// setup the VAO to reference the VBO (needs more study)
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		// if the layout is named "normal" (contains the normals to the vertices, used for light calculation)
		else if (strcmp(layoutBuffer[i].c_str(), "normal") == 0) {
			// enable the VAO in position 1
			glEnableVertexAttribArray(2);
			// bind the normal VBO of the entity
			glBindBuffer(GL_ARRAY_BUFFER, model->normalBuffer());
			// setup the VAO to reference the VBO (needs more study)
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
	}
}

void Renderer::createCube(std::vector<float>* array, std::vector<glm::vec3> faces) {
// 	array->push_back(faces[0].x);
// 	array->push_back(faces[0].y);
// 	array->push_back(faces[0].z);
// 	array->push_back(faces[1].x);
// 	array->push_back(faces[1].y);
// 	array->push_back(faces[1].z);

// 	array->push_back(faces[1].x);
// 	array->push_back(faces[1].y);
// 	array->push_back(faces[1].z);
// 	array->push_back(faces[2].x);
// 	array->push_back(faces[2].y);
// 	array->push_back(faces[2].z);

// 	array->push_back(faces[2].x);
// 	array->push_back(faces[2].y);
// 	array->push_back(faces[2].z);
// 	array->push_back(faces[3].x);
// 	array->push_back(faces[3].y);
// 	array->push_back(faces[3].z);

// 	array->push_back(faces[3].x);
// 	array->push_back(faces[3].y);
// 	array->push_back(faces[3].z);
// 	array->push_back(faces[0].x);
// 	array->push_back(faces[0].y);
// 	array->push_back(faces[0].z);

// 	array->push_back(faces[0].x);
// 	array->push_back(faces[0].y);
// 	array->push_back(faces[0].z);
// 	array->push_back(faces[5].x);
// 	array->push_back(faces[5].y);
// 	array->push_back(faces[5].z);

// 	array->push_back(faces[1].x);
// 	array->push_back(faces[1].y);
// 	array->push_back(faces[1].z);
// 	array->push_back(faces[6].x);
// 	array->push_back(faces[6].y);
// 	array->push_back(faces[6].z);

// 	array->push_back(faces[2].x);
// 	array->push_back(faces[2].y);
// 	array->push_back(faces[2].z);
// 	array->push_back(faces[7].x);
// 	array->push_back(faces[7].y);
// 	array->push_back(faces[7].z);

// 	array->push_back(faces[3].x);
// 	array->push_back(faces[3].y);
// 	array->push_back(faces[3].z);
// 	array->push_back(faces[4].x);
// 	array->push_back(faces[4].y);
// 	array->push_back(faces[4].z);

// 	array->push_back(faces[5].x);
// 	array->push_back(faces[5].y);
// 	array->push_back(faces[5].z);
// 	array->push_back(faces[4].x);
// 	array->push_back(faces[4].y);
// 	array->push_back(faces[4].z);

// 	array->push_back(faces[4].x);
// 	array->push_back(faces[4].y);
// 	array->push_back(faces[4].z);
// 	array->push_back(faces[7].x);
// 	array->push_back(faces[7].y);
// 	array->push_back(faces[7].z);

// 	array->push_back(faces[7].x);
// 	array->push_back(faces[7].y);
// 	array->push_back(faces[7].z);
// 	array->push_back(faces[6].x);
// 	array->push_back(faces[6].y);
// 	array->push_back(faces[6].z);

// 	array->push_back(faces[6].x);
// 	array->push_back(faces[6].y);
// 	array->push_back(faces[6].z);
// 	array->push_back(faces[5].x);
// 	array->push_back(faces[5].y);
// 	array->push_back(faces[5].z);
}

void Renderer::createSphere(glm::vec3 center, float dist, int sides, std::vector<float>* data) {

// 	double pi = 3.1415926535897;

// 	glm::vec3 tmp;

// 	glm::vec3 tmp2;

// 	tmp = glm::vec3(dist, 0, 0) + center;

// 	for (float i = 0; i < 2 * pi; i += (2 * pi) / (float)sides) {
// 		tmp2.x = dist * cos(i);
// 		tmp2.y = dist * sin(i);
// 		tmp2.z = 0;

// 		data->push_back(tmp.x);
// 		data->push_back(tmp.y);
// 		data->push_back(tmp.z);

// 		tmp = tmp2 + center;

// 		data->push_back(tmp.x);
// 		data->push_back(tmp.y);
// 		data->push_back(tmp.z);
// 	}

// 	data->push_back(tmp.x);
// 	data->push_back(tmp.y);
// 	data->push_back(tmp.z);

// 	tmp = glm::vec3(dist, 0, 0) + center;

// 	data->push_back(tmp.x);
// 	data->push_back(tmp.y);
// 	data->push_back(tmp.z);



// 	tmp = glm::vec3(0, 0, dist) + center;

// 	for (float i = 0; i < 2 * pi; i += (2 * pi) / (float)sides) {
// 		tmp2.x = 0;
// 		tmp2.y = dist * sin(i);
// 		tmp2.z = dist * cos(i);

// 		data->push_back(tmp.x);
// 		data->push_back(tmp.y);
// 		data->push_back(tmp.z);

// 		tmp = tmp2 + center;

// 		data->push_back(tmp.x);
// 		data->push_back(tmp.y);
// 		data->push_back(tmp.z);
// 	}

// 	data->push_back(tmp.x);
// 	data->push_back(tmp.y);
// 	data->push_back(tmp.z);

// 	tmp = glm::vec3(0, 0, dist) + center;

// 	data->push_back(tmp.x);
// 	data->push_back(tmp.y);
// 	data->push_back(tmp.z);



// 	tmp = glm::vec3(0, 0, dist) + center;

// 	for (float i = 0; i < 2 * pi; i += (2 * pi) / (float)sides) {
// 		tmp2.x = dist * sin(i);
// 		tmp2.y = 0;
// 		tmp2.z = dist * cos(i);

// 		data->push_back(tmp.x);
// 		data->push_back(tmp.y);
// 		data->push_back(tmp.z);

// 		tmp = tmp2 + center;

// 		data->push_back(tmp.x);
// 		data->push_back(tmp.y);
// 		data->push_back(tmp.z);
// 	}

// 	data->push_back(tmp.x);
// 	data->push_back(tmp.y);
// 	data->push_back(tmp.z);

// 	tmp = glm::vec3(0, 0, dist) + center;

// 	data->push_back(tmp.x);
// 	data->push_back(tmp.y);
// 	data->push_back(tmp.z);
}

void Renderer::drawBoundingBox(bounds_t bounds, glm::vec3 color) {
// 	std::vector<float> data;
// 	std::vector<glm::vec3> faces;
// 	faces.push_back(bounds.a);
// 	faces.push_back(bounds.b);
// 	faces.push_back(bounds.c);
// 	faces.push_back(bounds.d);
// 	faces.push_back(bounds.e);
// 	faces.push_back(bounds.f);
// 	faces.push_back(bounds.g);
// 	faces.push_back(bounds.h);
// 	createCube(&data, faces);

// 	glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer);
// 	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

// 	glUseProgram(shaderBuffer[1].getID());

// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(projectionBuffer[0][0][0]));
// 	glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, color.x, color.y, color.z);

// 	glEnableVertexAttribArray(0);
// 	// glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer2);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

// 	glDrawArrays(GL_LINES, 0, data.size());

// 	glDisableVertexAttribArray(0);
}

void Renderer::drawBoundingSphere(float radius, glm::vec3 center, glm::vec3 color) {
// 	std::vector<float> data;

// 	createSphere(center, radius, 100, &data);
// 	glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer);
// 	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

// 	glUseProgram(shaderBuffer[1].getID());

// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
// 	glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, color.x, color.y, color.z);

// 	glEnableVertexAttribArray(0);

// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

// 	glDrawArrays(GL_LINES, 0, data.size());

// 	glDisableVertexAttribArray(0);
}



double Renderer::getReflectionRenderTime() {
	return(this->reflectionRenderTime);
}

double Renderer::getForwardRenderTime() {
	return(this->forwardRenderTime);
}

double Renderer::getMSPostProcessingPassTime() {
	return(this->MSPostProcessingPassTime);
}

double Renderer::getPostProcessingPassTime() {
	return(this->postProcessingPassTime);
}

unsigned int Renderer::getOutlineMaskTexture() {
	return(this->outlineTextureMask);
}

unsigned int Renderer::getDepthBufferTexture() {
	bool tmpVar = RM.depth();

	RM.depth(true);
	this->renderMultisamplePostProcessing();
	RM.depth(tmpVar);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return(this->postProcessingTexture);
}

void Renderer::setPostProcessingEffect(int effect) {
	this->postProcessingEffect = effect;
}

void Renderer::setFilterColor(float r, float g, float b) {
	this->filterColor = glm::vec3(r, g, b);
}

// */

