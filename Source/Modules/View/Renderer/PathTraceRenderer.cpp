#include "PathTraceRenderer.hpp"

PathTraceRenderer::PathTraceRenderer() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glGenBuffers(1, &this->m_vertices);
    glGenBuffers(1, &this->m_modelMatrices);
    glGenBuffers(1, &this->m_indices);
    glGenBuffers(1, &this->m_normals);
    glGenBuffers(1, &this->m_spheres);
    glGenBuffers(1, &this->m_planes);
    glGenBuffers(1, &this->m_boxes);
    glGenBuffers(1, &this->m_boundingBoxes);
    glGenBuffers(1, &this->m_materials);
    glGenBuffers(1, &this->m_meshMaterialIndices);

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


    // create the VBO to store the square vertices
	glGenBuffers(1, &this->m_screenVBO);
	// set the current active VBO to the m_screenVBO
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenVBO);

	/* ACTIVE BUFFER: m_screenVBO */

	// pass the vertices to the buffer
	glBufferData(GL_ARRAY_BUFFER, square.size() * sizeof(float), &square[0], GL_STATIC_DRAW);


    // create the VBO to store the square vertices
	glGenBuffers(1, &this->m_screenUVVBO);
	// set the current active VBO to the m_screenVBO
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenUVVBO);

	/* ACTIVE BUFFER: m_screenUVVBO */

	// pass the vertices to the buffer
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(float), &uv[0], GL_STATIC_DRAW);


    this->m_renderResultTexture = 0;
    glGenTextures(1, &this->m_renderResultTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->m_renderResultTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 1280, 720);
    glBindImageTexture(0, this->m_renderResultTexture, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA32F);

    this->m_accumulationTexture = 0;
    glGenTextures(1, &this->m_accumulationTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->m_accumulationTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 1280, 720);
    glBindImageTexture(0, this->m_accumulationTexture, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA32F);

    this->m_computeShader = glCreateShader(GL_COMPUTE_SHADER);



    std::string VertexShaderCode;
	std::ifstream VertexShaderStream("../Shader/pathTracer/pathTracer.glsl", std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", "../Shader/pathTracer/pathTracer.glsl");
		getchar();
	}

    char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(this->m_computeShader, 1, &VertexSourcePointer, NULL);
    glCompileShader(this->m_computeShader);

    GLint status;
    int logSize;

    glGetShaderiv(this->m_computeShader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        glGetShaderiv(this->m_computeShader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<char> VertexShaderErrorMessage(logSize);
        glGetShaderInfoLog(this->m_computeShader, logSize, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
    }

    this->m_computeProgram = glCreateProgram();
    glAttachShader(this->m_computeProgram, this->m_computeShader);
    glLinkProgram(this->m_computeProgram);

    this->m_firstDraw = true;
    this->m_samples = 0.0;
}



void PathTraceRenderer::render() {
    double start = glfwGetTime();

    // if (this->m_firstDraw) {
    //     this->m_firstDraw = false;
    //     // data = (GLfloat * len(mesh_mat_i))(*mesh_mat_i)
    // }

    this->updateBuffers();


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->m_renderResultTexture);
    glBindImageTexture(0, this->m_renderResultTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

    glUseProgram(this->m_computeProgram);

    // YOU STOPPED HERE, IMPLEMENT INVERSE VIEW PROJECTION MATRIX FOR CAMERA
    glUniformMatrix4fv(glGetUniformLocation(this->m_computeProgram, "inverse_view_projection"), 1, GL_FALSE, &(RM.camera()->inverseViewProjectionMatrix()[0][0]));
    glUniform3f(glGetUniformLocation(this->m_computeProgram, "eye"), RM.camera()->position().x, RM.camera()->position().y, RM.camera()->position().z);
    glUniform1f(glGetUniformLocation(this->m_computeProgram, "time"), glfwGetTime());
    glUniform1f(glGetUniformLocation(this->m_computeProgram, "bounces"), 10);

    glDispatchCompute((int)(1280 / 8), (int)(720 / 4), 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(RM.shader("S_Accum")->id());

    glUniform1i(glGetUniformLocation(RM.shader("S_Accum")->id(), "tex"), 0);
    glUniform1i(glGetUniformLocation(RM.shader("S_Accum")->id(), "old_tex"), 1);
    glUniform1f(glGetUniformLocation(RM.shader("S_Accum")->id(), "frames"), this->m_samples);
    glUniform1f(glGetUniformLocation(RM.shader("S_Accum")->id(), "denoise"), RM.denoise() == true ? 1 : 0);

    glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_screenUVVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    if (!RM.denoise()) {
        this->m_samples++;
        glBindTexture(GL_TEXTURE_2D, this->m_accumulationTexture);
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, 1280, 720);
    }

    

    if (!RM.accumulate()) {
        glCopyImageSubData(this->m_renderResultTexture, GL_TEXTURE_2D, 0, 0, 0, 0, this->m_accumulationTexture, GL_TEXTURE_2D, 0, 0, 0, 0, 1280, 720, 1);
        this->m_samples = 0.0;
    }

    double end = glfwGetTime();

    printf("samples: %lf\n", this->m_samples);
    printf("Render: %lf\n", (end - start) * 1000);

}


void PathTraceRenderer::updateBuffers() {
    glBindBuffer(GL_UNIFORM_BUFFER, this->m_spheres);
    glBufferData(GL_UNIFORM_BUFFER, RM.spheres().size() * sizeof(float), &RM.spheres().front(), GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 5, this->m_spheres);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, this->m_planes);
    glBufferData(GL_UNIFORM_BUFFER, RM.planes().size() * sizeof(float), &RM.planes().front(), GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 6, this->m_planes);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // std::vector<float> materials = {1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0};
    glBindBuffer(GL_UNIFORM_BUFFER, this->m_materials);
    glBufferData(GL_UNIFORM_BUFFER, RM.materialValues().size() * sizeof(float), &RM.materialValues().front(), GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 9, this->m_materials);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // RM.updated();
}