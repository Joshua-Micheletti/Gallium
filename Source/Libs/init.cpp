#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "Model/entity.h"
#include "View/shader.h"
#include "View/camera.h"
#include "init.h"
#include <errno.h>

unsigned int screenWidth = 1280;
unsigned int screenHeight = 720;
unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

int samples = 1;
bool vsync = true;
bool fullscreen = false;

glm::mat4 Projection;
glm::mat4 Projection2;
glm::mat4 world_model;

buttons_t press;
renderMode_t renderMode;

bool displayInfo;
bool freeMouse;
bool drawOBB;
bool drawAABB1;
bool drawAABB2;
bool drawAABB3;
bool drawAABB4;
bool drawBS;
bool drawBS2;
bool drawBS3;
bool doReflection;

bool updateResolution;

bool updated;

bool depthBuffer;

int defaultCamera;

int outlineType;

std::vector<Entity*> entityBuffer;
std::vector<Shader> shaderBuffer;
std::vector<Camera*> cameraBuffer;
std::vector<glm::mat4> projectionBuffer;

Camera camera(glm::vec3(30.0f, 30.0f, 30.0f),   // position
			  glm::vec3(0.0f, 225.0f, -35.0f),  // direction
			  glm::vec3(0.0f, 1.0f, 0.0f));     // up;

Camera camera2(glm::vec3(0.0f, 0.0f, 0.0f),
			   glm::vec3(0.0f, 0.0f, 0.0f),
			   glm::vec3(0.0f, -1.0f, 0.0f));

Entity* light = new Entity("light");

void resizeCallback(GLFWwindow* window, int x, int y) {
	int width;
	int height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	screenWidth = width;
	screenHeight = height;

	if (!fullscreen) {
		windowWidth = screenWidth;
		windowHeight = screenHeight;
	}

	updateResolution = true;
}


GLFWwindow* initGLFW_OpenGL(std::string name) {
	glfwInit();
	
	GLFWwindow* window;
	window = glfwCreateWindow(screenWidth, screenHeight, "3DEngine", NULL, NULL);
	
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	gladLoadGL();
	glEnable(GL_MULTISAMPLE);
	glfwSetWindowSizeCallback(window, resizeCallback);

	return(window);
}

void loadShaders(std::vector<Shader>* shaderBuffer) {
	Shader shader1("shader1");
	Shader shader2("shader2");
	Shader shader3("shader3");
	Shader shader4("light");
	Shader shader5("lightTex");
	Shader shader6("lightSource");
	Shader shader7("skybox");
	Shader shader8("reflection");
	Shader shader9("refraction/glass");
	Shader shader10("refraction/diamond");
	Shader shader11("toon");
	Shader shader12("hightlight");
	Shader shader13("outline");
	Shader shader14("white");
	Shader shader15("outlineAlpha");

	shader1.loadShader("../Shader/shader1/vertex.c", "../Shader/shader1/fragment.c");
	shader2.loadShader("../Shader/shader2/vertex2.c", "../Shader/shader2/fragment2.c");
	shader3.loadShader("../Shader/shader3/vertex3.c", "../Shader/shader3/fragment3.c");
	shader4.loadShader("../Shader/lighting/lightVertex.c", "../Shader/lighting/lightFragment.c");
	shader5.loadShader("../Shader/lightingTex/lightVertexTexture.c", "../Shader/lightingTex/lightFragmentTexture.c");
	shader6.loadShader("../Shader/lightSource/lightSourceVertex.c", "../Shader/lightSource/lightSourceFragment.c");
	shader7.loadShader("../Shader/skybox/vertex.c", "../Shader/skybox/fragment.c");
	shader8.loadShader("../Shader/reflection/vertex.vert", "../Shader/reflection/fragment.frag");
	shader9.loadShader("../Shader/refraction/glass/vertex.c", "../Shader/refraction/glass/fragment.c");
	shader10.loadShader("../Shader/refraction/diamond/vertex.c", "../Shader/refraction/diamond/fragment.c");
	shader11.loadShader("../Shader/toon/vertex.c", "../Shader/toon/fragment.c");
	shader12.loadShader("../Shader/highlight/highlight.vert", "../Shader/highlight/highlight.frag");
	shader13.loadShader("../Shader/outline/outline.vert", "../Shader/outline/outline.frag");
	shader14.loadShader("../Shader/white/white.vert", "../Shader/white/white.frag");
	shader15.loadShader("../Shader/outlineAlpha/outline.vert", "../Shader/outlineAlpha/outline.frag");

	shaderBuffer->push_back(shader1);
	shaderBuffer->push_back(shader2);
	shaderBuffer->push_back(shader3);
	shaderBuffer->push_back(shader4);
	shaderBuffer->push_back(shader5);
	shaderBuffer->push_back(shader6);
	shaderBuffer->push_back(shader7);
	shaderBuffer->push_back(shader8);
	shaderBuffer->push_back(shader9);
	shaderBuffer->push_back(shader10);
	shaderBuffer->push_back(shader11);
	shaderBuffer->push_back(shader12);
	shaderBuffer->push_back(shader13);
	shaderBuffer->push_back(shader14);
	shaderBuffer->push_back(shader15);
}

void createAxis(Entity* axis) {
	std::vector<float> axisColor;
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(0.0f);
	axisColor.push_back(1.0f);

	axis->loadUVs(axisColor);

	std::vector<float> axisVertices;
	axisVertices.push_back(100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(-100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(-100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(100.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(0.0f);
	axisVertices.push_back(-100.0f);

	axis->loadVertices(axisVertices);
}

void loadEntities(std::vector<Entity*>* entityBuffer) {
	Entity* axis = new Entity(std::string("axis"));
	Entity* box = new Entity(std::string("box"));
	Entity* walnut = new Entity("walnut");
	Entity* monkey = new Entity("monkey");
	Entity* man = new Entity("man");
	Entity* skybox = new Entity("skybox");
	Entity* man2 = new Entity("man2");
	Entity* man3 = new Entity("man3");
	Entity* map = new Entity("map");
	Entity* plane = new Entity("plane");
	Entity* jacket = new Entity("jacket");
	Entity* manaya = new Entity("manaya");
	Entity* genshinEnemy = new Entity("genshinEnemy");
	Entity* box2 = new Entity("Box 2");

	createAxis(axis);
	std::vector<float> vex;
	vex.push_back(0);
	vex.push_back(0);
	vex.push_back(0);
	light->loadVertices(vex);
	box->load3DModel("../Models/box2.obj");
	walnut->load3DModel("../Models/walnut.obj");
	monkey->load3DModel("../Models/monkeyTex2.obj");
	man->load3DModel("../Models/sphere7.obj");
	man2->load3DModel("../Models/guy.obj");
	man3->load3DModel("../Models/guy.obj");
	map->load3DModel("../Models/dust2_.obj");
	plane->load3DModel("../Models/plane.obj");
	jacket->load3DModel("../Models/Blj.obj");
	manaya->load3DModel("../Models/manaya6.obj");
	genshinEnemy->load3DModel("../Models/genshinEnemy.obj");
	box2->load3DModel("../Models/box2.obj");

	std::vector<float> skyboxVertices = {
		// positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	skybox->loadVertices(skyboxVertices);

	axis->setShader(2);
	light->setShader(5);
	box->setShader(0);
	walnut->setShader(10);
	monkey->setShader(8);
	man->setShader(7);
	man2->setShader(7);
	man3->setShader(10);
	skybox->setShader(6);
	map->setShader(3);
	plane->setShader(3);
	jacket->setShader(4);
	manaya->setShader(7);
	genshinEnemy->setShader(10);
	box2->setShader(3);

	//manaya->setToReflect(false);
	//monkey->setToReflect(false);
	//map->setToReflect(false);
	man->setToReflect(false);
	//genshinEnemy->setToReflect(false);

	light->setElements(GL_POINTS);

	monkey->move(glm::vec3(0.0f, 0.0f, 10.0f), camera.getViewMatrix());
	// box->move(glm::vec3(-20.0f, 0.0f, 5.0f), camera.getViewMatrix());
	// box->rotate(0.0f, 180.0f, 180.0f);
	// box->scale(0.1f);
	man->scale(1.7f);
	// man->move(glm::vec3(0.0f, 0.0f, 20.0f), camera.getViewMatrix());
	// camera2.setPosition(man->getWorldPosition());
	man2->scale(0.7f);
	man3->scale(0.7f);
	man2->move(man2->getWorldPosition() - man2->getExternalAxisAlignedBoundingBox(true).minY, camera.getViewMatrix());
	man3->move(man3->getWorldPosition() - man3->getExternalAxisAlignedBoundingBox(true).minY, camera.getViewMatrix());
	// man->move(man->getWorldPosition() - man->getExternalAxisAlignedBoundingBox(true).minY, camera.getViewMatrix());
	walnut->move(walnut->getWorldPosition() - walnut->getExternalAxisAlignedBoundingBox(true).minY, camera.getViewMatrix());
	// box->move(glm::vec3(0.0f, box->getBoundingSphere(true), 0.0f), camera.getViewMatrix());
	//monkey->move(monkey->getWorldPosition() - monkey->getExternalAxisAlignedBoundingBox(true).minY, camera.getViewMatrix());
	jacket->move(jacket->getWorldPosition() - jacket->getExternalAxisAlignedBoundingBox(true).minY, camera.getViewMatrix());
	man3->move(glm::vec3(12.0f, 0.0f, 0.0f), camera.getViewMatrix());
	light->move(glm::vec3(60.0f, 10.0f, 0.0f), camera.getViewMatrix());
	walnut->move(glm::vec3(-10.0f, 0.0f, 0.0f), camera.getViewMatrix());
	plane->scale(50.0f);
	jacket->move(glm::vec3(0.0f, 0.0f, 50.0f), camera.getViewMatrix());
	manaya->scale(0.01f);
	manaya->move(glm::vec3(0.0f, 20.0f, 3.0f), camera.getViewMatrix());
	manaya->rotate(0, 270, 0);
	map->move(glm::vec3(0.0f, -20.0f, 0.0f), camera.getViewMatrix());
	box->move(glm::vec3(0.0f, -5.0f, -10.0f), camera.getViewMatrix());
	genshinEnemy->move(glm::vec3(0.0f, -5.0f, 0.0f), camera.getViewMatrix());

	// box->loadTexture("Textures/DefaultMaterial_Base_Color.png");
	box->loadTexture("../Textures/fi_uv_4096__display_grid_8x8_32x32_128x128_by_fisholith-d786zt5.png");
	jacket->loadTexture("../Textures/black leather jacket/Main Texture/[Albedo].jpg");

	std::vector<std::string> faces;
	std::string directory = "Epic_BlueSunset";
	faces.push_back("../Textures/Skybox/" + directory + "/right.png"); //right
	faces.push_back("../Textures/Skybox/" + directory + "/left.png");  //left
	faces.push_back("../Textures/Skybox/" + directory + "/top.png");   //top
	faces.push_back("../Textures/Skybox/" + directory + "/bottom.png");//bottom
	faces.push_back("../Textures/Skybox/" + directory + "/front.png"); //front
	faces.push_back("../Textures/Skybox/" + directory + "/back.png");  //back

	skybox->loadCubemap(faces);

	entityBuffer->push_back(skybox);
	entityBuffer->push_back(axis);
	entityBuffer->push_back(light);
	entityBuffer->push_back(box);
	entityBuffer->push_back(walnut);
	entityBuffer->push_back(monkey);
	entityBuffer->push_back(man);
	entityBuffer->push_back(man2);
	entityBuffer->push_back(man3);
	entityBuffer->push_back(jacket);
	entityBuffer->push_back(map);
	//entityBuffer->push_back(plane);
	entityBuffer->push_back(manaya);
	entityBuffer->push_back(genshinEnemy);
	entityBuffer->push_back(box2);
}

GLFWwindow* setup() {
	GLFWwindow* window = initGLFW_OpenGL("3DEngine");

	Projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 10000.0f);
	Projection2 = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10000.0f);
	world_model = glm::mat4(1.0f);

	renderMode = base;

	displayInfo = true;
	drawOBB = false;
	drawAABB1 = false;
	drawAABB2 = false;
	drawAABB3 = false;
	drawAABB4 = false;
	drawBS = false;
	drawBS2 = false;
	drawBS3 = false;
	doReflection = false;
	updateResolution = false;
	updated = true;
	depthBuffer = false;
	outlineType = 0;

	defaultCamera = 0;
	camera.setPosition(glm::vec3(1.0f, 0.5f, 1.0f));
	cameraBuffer.push_back(&camera);
	cameraBuffer.push_back(&camera2);
	projectionBuffer.push_back(Projection);
	projectionBuffer.push_back(Projection2);

	loadShaders(&shaderBuffer);

	loadEntities(&entityBuffer);

	return(window);
}

void loadEntity(std::vector<Entity*>* entityBuffer, char* path) {
	int i = 0;
	int k = 0;

	char fileName[256];
	while (path[i] != '\n') {
		if (path[i] == '\\') {
			k = 0;
			path[i] = '/';
		}
		else {
			fileName[k] = path[i];
			k++;
		}
		
		i++;
	}
	path[i] = '\0';

	fileName[k + 1] = '\0';

	printf("%s\n", fileName);

	// FIX
	char entityName[256];

	i = 0;
	int tmpIndex = 0;
	while (fileName[i] != '\0') {
		if (fileName[i] == '.') {
			tmpIndex = i;
		}

		entityName[i] = fileName[i];

		i++;
	}

	entityName[tmpIndex] = '\0';

	printf("%s\n", entityName);

	Entity* tmp = new Entity(entityName);

	/*FILE* model;
	errno = 0;
	model = fopen(path, "r");

	if (errno != 0) {
		perror("Error occured while opening file.\n");
	}

	if (model == NULL) {
		printf("model not loaded\n");
	}*/

	tmp->load3DModel(path);

	tmp->setShader(3);

	entityBuffer->push_back(tmp);
}
