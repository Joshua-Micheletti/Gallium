#include "Renderer.h"

// constructor method, sets up the renderer (reflection and post processing)
Renderer::Renderer() {
	Timer rendererSetupTimer;

	debugger.print("DEBUGGING RENDERER", "R");

	this->Kernels = new Kernel();
	this->m_postProcessingEffect = 0;

	debugger.print("CREATED KERNEL OBJECT", "R");

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

	debugger.print("SETUP WORLD VARIABLES", "R");


	// generate 1 generic buffer and assigns its ID to the variable m_tmpBuffer
	glGenBuffers(1, &this->m_tmpBuffer);


	// /*--------------------------------------------------------------------------*/
	// /*                             REFLECTION SETUP                             */
	// /*--------------------------------------------------------------------------*/

	// defines the resolution of the reflection cubemap
	this->m_reflectionRes = 4096;

	// generate the framebuffer that is gonna store the view from the reflection camera
	glGenFramebuffers(1, &this->m_reflectionFBO);
	// bind the newly generated framebuffer to the default framebuffer, both in read and write
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_reflectionFBO);

	/* ACTIVE FRAMEBUFFER: m_reflectionFBO */

	// generate a generic texture for the cubemap reflection
	glGenTextures(1, &this->m_reflectionCubemap);
	// actually creates and binds the cubemap placeholder to the actual cubemap
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_reflectionCubemap);

	/* ACTIVE TEXTURE: m_reflectionCubemap */

	// cycle through the faces of the cubemap
	for (int i = 0; i < 6; i++) {
		// generate an empty (NULL) texture at the target (active texture @ GL_TEXTURE_CUBE_MAP_POSITIVE_X ... GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
		// with no mipmap level, RGB color internal format, reflectionRex x m_reflectionRes for the resolution, no border, RGB color format,
		// UNSIGNED_BYTE pixel data format
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, this->m_reflectionRes, this->m_reflectionRes, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
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
	glGenRenderbuffers(1, &this->m_reflectionRBO);
	// bind renderBuffer to the default GL_RENDERBUFFER
	glBindRenderbuffer(GL_RENDERBUFFER, this->m_reflectionRBO);

	/* ACTIVE RENDERBUFFER: m_reflectionRBO */

	// define render buffer multisample (needs more study)
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_DEPTH24_STENCIL8, this->m_reflectionRes, this->m_reflectionRes);
	// attach renderBuffer to the current framebuffer (frameBuffer)
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->m_reflectionRBO);

	// set back the renderbuffer to the default renderbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	debugger.print("SETUP REFLECTION", "R");

	/* ACTIVE RENDERBUFFER: Default */

	/*-------------------------------------------------------------------------------*/
	/*                             POST PROCESSING SETUP                             */
	/*-------------------------------------------------------------------------------*/
	
	// create an empty texture object for m_screenTexture, this texture will be bound to the m_screenFBO
	// and will store the screen view image
	glGenTextures(1, &this->m_screenTexture);
	// bind the m_screenTexture texture as the main texture
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->m_screenTexture);
	
	/* ACTIVE TEXTURE: m_screenTexture */

	// create the actual texture for image with res: screenWidth x screenHeight
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, RM.samples(), GL_RGB, screenWidth, screenHeight, false);

	// create an empty texture for the depth texture
	glGenTextures(1, &this->m_screenDepthTexture);
	// bind the m_screenTexture texture as the main texture
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->m_screenDepthTexture);

	/* ACTIVE TEXTURE: m_screenDepthTexture */

	// create the actual texture for image with res: screenWidth x screenHeight
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, RM.samples(), GL_DEPTH_STENCIL, screenWidth, screenHeight, false);
	//glTextureParameteri(this->m_screenDepthTexture, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);
	// create the m_screenFBO (used for rendering the screen view to a texture)
	glGenFramebuffers(1, &this->m_screenFBO);
	// bind the m_screenFBO to be the default FBO
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_screenFBO);

	glGenTextures(1, &this->m_outlineTextureMask);
	glBindTexture(GL_TEXTURE_2D, this->m_outlineTextureMask);
	//glTexImage2DMultisample(GL_TEXTURE_2D, samples, GL_RGB, screenWidth, screenHeight, false);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	

	/* ACTIVE FRAMEBUFFER: m_screenFBO */

	// attach the m_screenTexture to the m_screenFBO, so that the stuff rendered on the m_screenFBO can be saved to the m_screenTexture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->m_screenTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, this->m_screenDepthTexture, 0);

	int framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE) {
		printf("framebuffer error: %d\n", framebufferStatus);
	}

	glGenTextures(1, &this->m_postProcessingTexture);
	glBindTexture(GL_TEXTURE_2D, this->m_postProcessingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &this->m_postProcessingDepthTexture);
	glBindTexture(GL_TEXTURE_2D, this->m_postProcessingDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, screenWidth, screenHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffers(1, &this->m_postProcessingFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_postProcessingFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_postProcessingTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->m_postProcessingDepthTexture, 0);

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
	glGenBuffers(1, &this->m_screenVBO);
	// set the current active VBO to the m_screenVBO
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenVBO);

	/* ACTIVE BUFFER: m_screenVBO */

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
	glGenBuffers(1, &this->m_screenUVVBO);
	// set the current active VBO to the m_screenUVVBO
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenUVVBO);

	/* ACTIVE BUFFER: m_screenUVVBO*/

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

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	this->m_highlightedEntity = -1;

	debugger.print("SETUP POST PROCESSING", "R");

	printf("\n%sSetup renderer%s\n", strGreen.c_str(), strNoColor.c_str());
	rendererSetupTimer.print();
}


// public method for rendering the scene
void Renderer::render() {
	if (updateResolution) {
		this->resizeScreen();
	}

	glEnable(GL_DEPTH_TEST);


	// ------------------------------ REFLECTION FRAMEBUFFER RENDERING ------------------------------ //

	this->m_reflectionRenderTime = glfwGetTime();

	// check if the program should render the reflection cubemap
	if (doReflection) {
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_reflectionFBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render the reflection cubemap
		this->renderReflectionCubemap();
	}	

	this->m_reflectionRenderTime = glfwGetTime() - this->m_reflectionRenderTime;

	// -------------------------------- SCREEN FRAMEBUFFER RENDERING -------------------------------- //

	this->m_forwardRenderTime = glfwGetTime();

	glBindFramebuffer(GL_FRAMEBUFFER, this->m_screenFBO);
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

	if (debugger.displayBoundingSpheres()) {
		this->drawBoundingSphere();
	}

	this->m_forwardRenderTime = glfwGetTime() - this->m_forwardRenderTime;

	// ---------------------------- POST PROCESSING FRAMEBUFFER RENDERING --------------------------- //

	this->m_MSPostProcessingPassTime = glfwGetTime();

	this->renderMultisamplePostProcessing();

	this->m_MSPostProcessingPassTime = glfwGetTime() - this->m_MSPostProcessingPassTime;

	this->m_postProcessingPassTime = glfwGetTime();

	if (RM.selectedEntity().size() != 0 && (outlineType == 0 || outlineType == 1)) {
		this->renderOutline();
	}

	// ---------------------------------- OUT FRAMEBUFFER RENDERING --------------------------------- //


	this->renderScreen();
	this->m_postProcessingPassTime = glfwGetTime() - this->m_postProcessingPassTime;
}


// render the cubemap view from the reflection camera to later calculate reflections on
void Renderer::renderReflectionCubemap() {
	RM.camera("reflection");

	// set the viewport to fit the reflection texture resolution
	glViewport(0, 0, m_reflectionRes, m_reflectionRes);

	// cycle all the faces of the cubemap
	for (int i = 0; i < 6; i++) {
		// attach the positive X texture of the m_reflectionCubemap to the color buffer of the m_reflectionFBO
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->m_reflectionCubemap, 0);
		// aim the camera to face the correct direction
		if (i == 0)      // FRONT
			RM.camera()->yaw(0)->pitch(0);
		else if (i == 1) // BACK
			RM.camera()->yaw(180)->pitch(0);
		else if (i == 2) // TOP
			RM.camera()->yaw(90)->pitch(90);
		else if (i == 3) // BOTTOM
			RM.camera()->yaw(90)->pitch(-90);
		else if (i == 4) // RIGHT
			RM.camera()->yaw(90)->pitch(0);
		else             // LEFT
			RM.camera()->yaw(270)->pitch(0);

		this->renderSkybox();
		this->renderEntities(true);
		// clear the depth buffers from the m_reflectionFBO
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	// reset the viewport
	glViewport(0, 0, window.width(), window.height());

	// set the render camera to the default camera
	RM.camera("default");
}

// render all entities with their corresponding shader (forward rendering)
void Renderer::renderEntities(bool reflection) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	std::vector<std::string> models = RM.modelNames(); 

	int renders = 0;

	// render entities
	for (int i = 0; i < models.size(); i++) {
		if (models[i] != RM.skybox() && models[i] != RM.selectedEntity() && RM.camera()->frostum()->isOnFrostum(RM.model(models[i])->center() + RM.model(models[i])->position(), RM.model(models[i])->radius())) {
			this->renderEntity(models[i]);
			renders++;
		}
	}
	
	if (RM.selectedEntity().size() != 0 && reflection == false) {
		glStencilFunc(GL_ALWAYS, 1, 255);
		glStencilMask(255);

		this->renderEntity(RM.selectedEntity());

		glStencilMask(0);
		glStencilFunc(GL_NOTEQUAL, 1, 255);

		glDisable(GL_DEPTH_TEST);
		std::vector<std::string> previousShaders;

		previousShaders = RM.model(RM.selectedEntity())->shaders(RM.highlightShader());
		this->renderEntity(RM.selectedEntity());
		RM.model(RM.selectedEntity())->shaders(previousShaders);

		glEnable(GL_DEPTH_TEST);
	}
}


void Renderer::renderEntity(std::string entity) {
	Model* currentM = RM.model(entity);
	std::vector<component_t*> currentComponents = currentM->components();

	for (int i = 0; i < currentComponents.size(); i++) {
		Mesh* currentMesh = RM.mesh(currentComponents[i]->mesh);
		Material* currentMA = RM.material(currentComponents[i]->material);
		Shader* currentS = RM.shader(currentComponents[i]->shader);
		RenderTexture currentT = currentComponents[i]->texture;
		
		glUseProgram(currentS->id());
		glBindTexture(GL_TEXTURE_2D, RM.texture(currentT.general())->id());

		attachUniforms(currentM, currentMA, currentT, currentS->uniformBuffer());
		linkLayouts(currentMesh, currentS->layoutBuffer());
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentMesh->indexBuffer());

		glDrawElements(currentM->drawingMode(), currentMesh->indices().size(), GL_UNSIGNED_INT, (void*)0);

		// glDrawArrays(currentM->drawingMode(), 0, currentMesh->vertices().size() / 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

	}
}


void Renderer::renderSkybox() {
	// disable depth
	glDepthMask(GL_FALSE);
	// disable backface culling
	glDisable(GL_CULL_FACE);

	// extract the skybox components
	Model* skyboxM = RM.model(RM.skybox());
	component_t* skyboxComponents = skyboxM->components()[0];
	Mesh* skyboxMesh = RM.mesh(skyboxComponents->mesh);
	Material* skyboxMA = RM.material(skyboxComponents->material);
	Shader* skyboxS = RM.shader(skyboxComponents->shader);
	RenderTexture skyboxT = skyboxComponents->texture;

	// bind the shader
	glUseProgram(skyboxS->id());
	// attach the shader uniforms
	attachUniforms(skyboxM, skyboxMA, skyboxT, skyboxS->uniformBuffer());
	// link the shader layouts
	linkLayouts(skyboxMesh, skyboxS->layoutBuffer());
	// bind the skybox texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, RM.texture(skyboxT.general())->id());
	// render the skybox

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxMesh->indexBuffer());

	glDrawElements(skyboxM->drawingMode(), skyboxMesh->indices().size(), GL_UNSIGNED_INT, (void*)0);

	glDrawArrays(skyboxM->drawingMode(), 0, skyboxMesh->vertices().size() / 3);

	// re-enable the depth mask (now rendering also affects the depth buffer as well)
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
}


void Renderer::renderOutline() {
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_outlineTextureMask, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_CULL_FACE);
	
	std::vector<std::string> previousShaders;

	previousShaders = RM.model(RM.selectedEntity())->shaders("S_White");
	this->renderEntity(RM.selectedEntity());
	RM.model(RM.selectedEntity())->shaders(previousShaders);
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_postProcessingTexture, 0);

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

	int screenTexUniformID = glGetUniformLocation(RM.shader(RM.outlineShader())->id(), "m_screenTexture");
	int outlineMaskUniformID = glGetUniformLocation(RM.shader(RM.outlineShader())->id(), "outlineMask");

	glUniform1i(screenTexUniformID, 0);
	glUniform1i(outlineMaskUniformID, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->m_postProcessingTexture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->m_outlineTextureMask);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenUVVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
}


void Renderer::renderMultisamplePostProcessing() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_postProcessingFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

	if (RM.depth()) {
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->m_screenDepthTexture);
		glUseProgram(RM.shader("RS_DepthShader")->id());
		glUniform1i(glGetUniformLocation(RM.shader("RS_DepthShader")->id(), "samples"), RM.samples());
	}
	else {
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->m_screenTexture);
		glUseProgram(RM.shader("RS_ScreenShader")->id());
		glUniform1i(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "samples"), RM.samples());

		glUniform1i(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "effect"), this->m_postProcessingEffect);

		if (this->m_postProcessingEffect == 2) {
			glUniform3f(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "m_filterColor"), this->m_filterColor.x, this->m_filterColor.y, this->m_filterColor.z);
		}

		else if (this->m_postProcessingEffect == 9) {
			int kernelSize = this->Kernels->getKernelSize();

			glUniform1i(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "kernelSize_f"), kernelSize);
			glUniform1fv(glGetUniformLocation(RM.shader("RS_ScreenShader")->id(), "kernel_f"), kernelSize * kernelSize, this->Kernels->getKernel());
		}
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenUVVBO);
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
	glBindTexture(GL_TEXTURE_2D, this->m_postProcessingTexture);
	// bind the post processing shader
	glUseProgram(RM.shader("RS_PostProcessingShader")->id());

	// bind the VBOs
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenUVVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// bind the uniform
	int screenTexUniformID = glGetUniformLocation(RM.shader("RS_PostProcessingShader")->id(), "m_screenTexture");
	glUniform1i(screenTexUniformID, 0);

	// draw the quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// re-enable depth testing
	glEnable(GL_DEPTH_TEST);
}

void Renderer::resetRender() {
// 	glBufferData(GL_ARRAY_BUFFER, m_data1.size() * sizeof(float), &m_data1[0], GL_STATIC_DRAW);

// 	glUseProgram(shaderBuffer[1].getID());
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
// 	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
// 	glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, 255, 255, 255);

// 	glEnableVertexAttribArray(0);

// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

// 	glDrawArrays(GL_LINES, 0, m_data1.size());

// 	glDisableVertexAttribArray(0);
}

void Renderer::resizeScreen() {
	// create an empty texture object for m_screenTexture, this texture will be bound to the m_screenFBO
	// and will store the screen view image
	glDeleteTextures(1, &this->m_screenTexture);
	glGenTextures(1, &this->m_screenTexture);
	// bind the m_screenTexture texture as the main texture
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->m_screenTexture);

	/* ACTIVE TEXTURE: m_screenTexture */

	// create the actual texture for image with res: screenWidth x screenHeight
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, RM.samples(), GL_RGB, window.framebufferWidth(), window.framebufferHeight(), false);
	printf("%d, %d\n", window.width(), window.height());

	// set the texture filters for mipmaps
	glDeleteTextures(1, &this->m_screenDepthTexture);
	glGenTextures(1, &this->m_screenDepthTexture);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->m_screenDepthTexture);

	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, RM.samples(), GL_DEPTH_STENCIL, window.framebufferWidth(), window.framebufferHeight(), false);

	glDeleteTextures(1, &this->m_outlineTextureMask);
	glGenTextures(1, &this->m_outlineTextureMask);
	glBindTexture(GL_TEXTURE_2D, this->m_outlineTextureMask);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.framebufferWidth(), window.framebufferHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glDeleteTextures(1, &this->m_postProcessingTexture);
	glGenTextures(1, &this->m_postProcessingTexture);
	glBindTexture(GL_TEXTURE_2D, this->m_postProcessingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.framebufferWidth(), window.framebufferHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glDeleteTextures(1, &this->m_postProcessingDepthTexture);
	glGenTextures(1, &this->m_postProcessingDepthTexture);
	glBindTexture(GL_TEXTURE_2D, this->m_postProcessingDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, window.framebufferWidth(), window.framebufferHeight(), 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glDeleteFramebuffers(1, &this->m_postProcessingFBO);
	glGenFramebuffers(1, &this->m_postProcessingFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_postProcessingFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_postProcessingTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->m_postProcessingDepthTexture, 0);

	// create the m_screenFBO (used for rendering the screen view to a texture)
	glDeleteFramebuffers(1, &this->m_screenFBO);
	glGenFramebuffers(1, &this->m_screenFBO);
	// bind the m_screenFBO to be the default FBO
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_screenFBO);

	/* ACTIVE FRAMEBUFFER: m_screenFBO */

	// attach the m_screenTexture to the m_screenFBO, so that the stuff rendered on the m_screenFBO can be saved to the m_screenTexture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->m_screenTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, this->m_screenDepthTexture, 0);

	// glViewport(0, 0, window.width(), window.height());

	// projectionBuffer[0] = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 10000.0f);
	RM.camera()->projection(45.0f, (float)window.framebufferHeight() / (float)window.framebufferWidth(), 0.1f, 10000.0f);
	// RM.setProjection("default", glm::perspective(glm::radians(45.0f), (float)window.framebufferWidth() / (float)window.framebufferHeight(), 0.1f, 10000.0f));
	// RM.setProjection("reflection", glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10000.0f));
	// RM.projection(glm::perspective(glm::radians(45.0f), (float)window.framebufferWidth() / (float)window.framebufferHeight(), 0.1f, 10000.0f));
	updated = true;
	// updateResolution = false;
}

void Renderer::drawBoundingSphere() {
	std::vector<std::string> models = RM.modelNames();

	for (int i = 0; i < models.size(); i++) {
		if (models[i] != RM.skybox()) {
			Model* currentM = RM.model(models[i]);
			std::vector<component_t*> currentComponents = currentM->components();
			RM.model("M_BoundingSphere")->scale(glm::vec3(RM.model(models[i])->radius(), RM.model(models[i])->radius(), RM.model(models[i])->radius()))->position(RM.model(models[i])->center() + RM.model(models[i])->position());
			this->renderEntity("M_BoundingSphere");
		}
	}
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
// 			glBindBuffer(GL_ARRAY_BUFFER, m_tmpBuffer);
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

// pass the correct values to the corresponding uniforms in the shader
void Renderer::attachUniforms(Model* entity, Material* material, RenderTexture texture, std::vector<uniform_t> uniformBuffer) {
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
			if (entity == RM.model(RM.skybox())) {
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
			glUniformMatrix4fv(uniformBuffer[i].id, 1, GL_FALSE, &(RM.camera()->projection()[0][0]));
		}

		// if the uniform is "lightPosition", pass the light position (x, y, z)
		else if (strcmp(uniformBuffer[i].name, "lightPosition") == 0) {
			glm::vec3 lightPosition = RM.model(RM.mainLight())->position();
			glUniform3f(uniformBuffer[i].id, lightPosition.x, lightPosition.y, lightPosition.z);
		}

		// if the uniform is "eyePosition", pass the camera position (x, y, z)
		else if (strcmp(uniformBuffer[i].name, "eyePosition") == 0) {
			glm::vec3 cameraPosition = RM.camera()->position();
			glUniform3f(uniformBuffer[i].id, cameraPosition.x, cameraPosition.y, cameraPosition.z);
		}

		else if (strcmp(uniformBuffer[i].name, "skybox") == 0) {
			glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_reflectionCubemap);
		}

		else if (strcmp(uniformBuffer[i].name, "ambient") == 0) {
			glm::vec3 ambient = material->ambient();
			glUniform3f(uniformBuffer[i].id, ambient.x, ambient.y, ambient.z);
		}

		else if (strcmp(uniformBuffer[i].name, "diffuse") == 0) {
			glm::vec3 diffuse = material->diffuse();
			glUniform3f(uniformBuffer[i].id, diffuse.x, diffuse.y, diffuse.z);
		}

		else if (strcmp(uniformBuffer[i].name, "diffuseTex") == 0) {
			glUniform1i(uniformBuffer[i].id, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, RM.texture(texture.diffuse())->id());
		}

		else if (strcmp(uniformBuffer[i].name, "specular") == 0) {
			glm::vec3 specular = material->specular();
			glUniform3f(uniformBuffer[i].id, specular.x, specular.y, specular.z);
		}

		else if (strcmp(uniformBuffer[i].name, "specularTex") == 0) {
			glUniform1i(uniformBuffer[i].id, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, RM.texture(texture.specular())->id());
			glActiveTexture(GL_TEXTURE0);
		}

		else if (strcmp(uniformBuffer[i].name, "shininess") == 0) {
			glUniform1f(uniformBuffer[i].id, material->shininess());
		}

		else if (strcmp(uniformBuffer[i].name, "lightAmbient") == 0) {
			glm::vec3 ambient = RM.material(RM.model(RM.mainLight())->components()[0]->material)->ambient();
			glUniform3f(uniformBuffer[i].id, ambient.x, ambient.y, ambient.z);
		}

		else if (strcmp(uniformBuffer[i].name, "lightDiffuse") == 0) {
			glm::vec3 diffuse = RM.material(RM.model(RM.mainLight())->components()[0]->material)->diffuse();
			glUniform3f(uniformBuffer[i].id, diffuse.x, diffuse.y, diffuse.z);
		}

		else if (strcmp(uniformBuffer[i].name, "lightSpecular") == 0) {
			glm::vec3 specular = RM.material(RM.model(RM.mainLight())->components()[0]->material)->specular();
			glUniform3f(uniformBuffer[i].id, specular.x, specular.y, specular.z);
		}
	}
}

// link layouts to the data origin (mainly VAO)
void Renderer::linkLayouts(Mesh* mesh, std::vector<std::string> layoutBuffer) {
	// cycle all the layouts in the layout buffer of the shader
	for (int i = 0; i < layoutBuffer.size(); i++) {
		// if the layout is named "vertex" (contains the entity vertices that make the geometry of the entity)
		if (strcmp(layoutBuffer[i].c_str(), "vertex") == 0) {
			// enable the VAO in position 0
			glEnableVertexAttribArray(0);
			// bind the geometry VBO of the entity
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer());
			// setup the VAO to reference the VBO (needs more study)
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		// if the layout is named "uv" (contains the UV coordinates to map the texture to the geometry)
		else if (strcmp(layoutBuffer[i].c_str(), "uv") == 0) {
			// enable the VAO in position 1
			glEnableVertexAttribArray(1);
			// bind the UV VBO of the entity
			glBindBuffer(GL_ARRAY_BUFFER, mesh->uvBuffer());
			// setup the VAO to reference the VBO (needs more study)
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		// if the layout is named "color" (contains the color vectors that make the entity color)
		else if (strcmp(layoutBuffer[i].c_str(), "color") == 0) {
			// enable the VAO in position 1
			glEnableVertexAttribArray(1);
			// bind the color VBO of the entity
			glBindBuffer(GL_ARRAY_BUFFER, mesh->uvBuffer());
			// setup the VAO to reference the VBO (needs more study)
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		// if the layout is named "normal" (contains the normals to the vertices, used for light calculation)
		else if (strcmp(layoutBuffer[i].c_str(), "normal") == 0) {
			// enable the VAO in position 1
			glEnableVertexAttribArray(2);
			// bind the normal VBO of the entity
			glBindBuffer(GL_ARRAY_BUFFER, mesh->normalBuffer());
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

// 	glBindBuffer(GL_ARRAY_BUFFER, m_tmpBuffer);
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
// 	glBindBuffer(GL_ARRAY_BUFFER, m_tmpBuffer);
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
	return(this->m_reflectionRenderTime);
}

double Renderer::getForwardRenderTime() {
	return(this->m_forwardRenderTime);
}

double Renderer::getMSPostProcessingPassTime() {
	return(this->m_MSPostProcessingPassTime);
}

double Renderer::getPostProcessingPassTime() {
	return(this->m_postProcessingPassTime);
}

unsigned int Renderer::getOutlineMaskTexture() {
	return(this->m_outlineTextureMask);
}

unsigned int Renderer::getDepthBufferTexture() {
	bool tmpVar = RM.depth();

	RM.depth(true);
	this->renderMultisamplePostProcessing();
	RM.depth(tmpVar);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return(this->m_postProcessingTexture);
}


void Renderer::setPostProcessingEffect(int effect) {
	this->m_postProcessingEffect = effect;
}

void Renderer::setFilterColor(float r, float g, float b) {
	this->m_filterColor = glm::vec3(r, g, b);
}