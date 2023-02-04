source = ./Source
modules = $(source)/Modules
view = $(modules)/View
model = $(modules)/Model
controller = $(modules)/Controller
utils = $(modules)/Utils
libs = ./Libs
gladI = $(libs)/GLAD/include
gladL = $(libs)/GLAD/src
glfwI = $(libs)/glfw/include
#glfwL = $(libs)/glfw/lib-mingw
glmI = $(libs)/glm
imgui = $(libs)/imgui-1.88
imguiBE = $(imgui)/backends
stbimage = $(libs)/stb-master
bulletI = $(libs)/bullet3/src

makefile = makefile

ifeq ($(OS),Windows_NT)
	bulletL = -L ./Libs/bullet3/build_windows/lib -lBulletDynamics -lBulletSoftBody -lBulletCollision -lLinearMath
	glfwL = $(libs)/glfw/lib-mingw
	extLibL = $(glfwL) -L $(glmI) -L $(imgui) -L $(stbimage) $(bulletL)
	libraries = -lopengl32 -lglfw3
	runCommand = cd "./bin" && "./launch.exe"
	marks = 
	escape = 
	noColor = $(escape)[0m
	env = 
else
	extLibL = $(glmI) -L $(imgui) -L $(stbimage) $(bulletL)
	libraries = -lGL -lglfw3 -ldl -lm -lGLU -lX11 -lpthread -lGLEW
	marks = "
	escape = \033
	noColor = $(escape)[0m
	env = export LD_LIBRARY_PATH=.$(bulletLibrary)/Bullet3Collision:.$(bulletLibrary)/Bullet3Common:.$(bulletLibrary)/Bullet3Dynamics:.$(bulletLibrary)/Bullet3Geometry:.$(bulletLibrary)/Bullet3OpenCL:.$(bulletLibrary)/Bullet3Serialize:.$(bulletLibrary)/BulletCollision:.$(bulletLibrary)/BulletDynamics:.$(bulletLibrary)/BulletInverseDynamics:.$(bulletLibrary)/BulletSoftBody:.$(bulletLibrary)/LinearMath
	runCommand = (cd ./bin && $(env) && export GALLIUM_HUD=fps && ./launch)

	bulletLibrary = ./Libs/bullet3/build_cmake/src

	COLLISION3 = -L $(bulletLibrary)/Bullet3Collision/ -lBullet3Collision
	COMMON3 = -L $(bulletLibrary)/Bullet3Common/ -lBullet3Common
	DYNAMICS3 = -L $(bulletLibrary)/Bullet3Dynamics/ -lBullet3Dynamics
	GEOMETRY3 = -L $(bulletLibrary)/Bullet3Geometry/ -lBullet3Geometry
	OPENCL3 = -L $(bulletLibrary)/Bullet3OpenCL/ -lBullet3OpenCL_clew
	SERIALIZE2 = -L $(bulletLibrary)/Bullet3Serialize/Bullet2FileLoader/ -lBullet2FileLoader
	COLLISION = -L $(bulletLibrary)/BulletCollision/ -lBulletCollision
	DYNAMICS = -L $(bulletLibrary)/BulletDynamics/ -lBulletDynamics
	INVERSEDYNAMICS = -L $(bulletLibrary)/BulletInverseDynamics/ -lBulletInverseDynamics
	SOFTBODY = -L $(bulletLibrary)/BulletSoftBody/ -lBulletSoftBody
	LINEARMATH = -L $(bulletLibrary)/LinearMath/ -lLinearMath

	bulletL = $(COLLISION3) $(COMMON3) $(DYNAMICS3) $(GEOMETRY3) $(OPENCL3) $(SERIALIZE2) $(COLLISION) $(DYNAMICS) $(INVERSEDYNAMICS) $(SOFTBODY) $(LINEARMATH)
endif





extLibI = $(gladI) -I $(glfwI) -I $(glmI) -I $(imgui) -I $(imguiBE) -I $(stbimage) -I $(bulletI)

flags = -w -std=c++11 -Ofast

objectsPath = ./bin/objects
objects = $(objectsPath)/main.o $(objectsPath)/Engine.o $(objectsPath)/sandbox.o $(objectsPath)/global.o $(objectsPath)/vboindexer.o $(objectsPath)/Timer.o $(objectsPath)/Window.o $(objectsPath)/utils.o $(objectsPath)/glad.o $(objectsPath)/Renderer.o $(objectsPath)/RendererManager.o $(objectsPath)/Model.o $(objectsPath)/Mesh.o $(objectsPath)/Material.o $(objectsPath)/Texture.o $(objectsPath)/RenderTexture.o $(objectsPath)/EventHandler.o $(objectsPath)/Ui.o $(objectsPath)/PhysicsWorld.o $(objectsPath)/PhysicsBody.o $(objectsPath)/Entity.o $(objectsPath)/Shader.o $(objectsPath)/Camera.o $(objectsPath)/Kernel.o $(objectsPath)/imgui.o $(objectsPath)/imgui_impl_glfw.o $(objectsPath)/imgui_impl_opengl3.o $(objectsPath)/imgui_demo.o $(objectsPath)/imgui_draw.o $(objectsPath)/imgui_widgets.o $(objectsPath)/imgui_tables.o

# LINKING

main: $(objects) $(makefile)
	@echo $(marks)$(escape)[31m============= COMPILING MAIN PROGRAM =============$(noColor)$(marks)
	$(env)
	g++ -o ./bin/launch $(objects) -L $(extLibL) -I $(extLibI) $(libraries) $(flags)
	@echo $(marks)$(escape)[32mDone$(noColor)$(marks)


# COMPILING

# MAIN
$(objectsPath)/main.o: $(source)/main.cpp $(makefile)
	@echo $(marks)$(escape)[31m============= main.cpp (source) ============$(noColor) $(marks)
	g++ -c -o $(objectsPath)/main.o $(source)/main.cpp -I $(extLibI) -I $(modules)/ $(flags) $(libraries)

# ENGINE
$(objectsPath)/Engine.o: $(modules)/Engine/Engine.cpp $(modules)/Engine/Engine.h $(makefile)
	@echo $(marks)$(escape)[31m============= Engine.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Engine.o $(modules)/Engine/Engine.cpp -I $(extLibI) $(flags) $(libraries)

# SANDBOX
$(objectsPath)/sandbox.o: $(modules)/Sandbox/sandbox.cpp $(modules)/Sandbox/sandbox.h $(makefile)
	@echo $(marks)$(escape)[31m============= sandbox.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/sandbox.o $(modules)/Sandbox/sandbox.cpp -I $(extLibI) $(flags) $(libraries)

# UTILS
$(objectsPath)/utils.o: $(utils)/utils.cpp $(utils)/utils.h $(makefile)
	@echo $(marks)$(escape)[31m============= utils.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/utils.o $(utils)/utils.cpp -I $(extLibI) $(flags) $(libraries)

# GLOBAL
$(objectsPath)/global.o: $(utils)/global.cpp $(utils)/global.h $(makefile)
	@echo $(marks)$(escape)[31m============= global.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/global.o $(utils)/global.cpp -I $(extLibI) $(flags) $(libraries)

# VBOINDEXER
$(objectsPath)/vboindexer.o: $(utils)/vboindexer.cpp $(utils)/vboindexer.hpp $(makefile)
	@echo $(marks)$(escape)[31m============= vboindexer.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/vboindexer.o $(utils)/vboindexer.cpp -I $(extLibI) $(flags) $(libraries)

# TIMER
$(objectsPath)/Timer.o: $(utils)/Timer.cpp $(utils)/Timer.h $(makefile)
	@echo $(marks)$(escape)[31m============= Timer.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Timer.o $(utils)/Timer.cpp -I $(extLibI) $(flags) $(libraries)

# VIEW

# WINDOW
$(objectsPath)/Window.o: $(view)/Window/Window.cpp $(view)/Window/Window.h $(makefile)
	@echo $(marks)$(escape)[31m============= Window.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Window.o $(view)/Window/Window.cpp -I $(extLibI) $(flags)

# RENDERER
$(objectsPath)/Renderer.o: $(view)/Renderer/Renderer.cpp $(view)/Renderer/Renderer.h $(makefile)
	@echo $(marks)$(escape)[31m============= Renderer.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Renderer.o $(view)/Renderer/Renderer.cpp -I $(extLibI) $(flags)

# RENDERERMANAGER
$(objectsPath)/RendererManager.o: $(view)/Renderer/RendererManager.cpp $(view)/Renderer/RendererManager.h $(makefile)
	@echo $(marks)$(escape)[31m============= RendererManager.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/RendererManager.o $(view)/Renderer/RendererManager.cpp -I $(extLibI) $(flags)

# MODEL
$(objectsPath)/Model.o: $(view)/Model/Model.cpp $(view)/Model/Model.h $(makefile)
	@echo $(marks)$(escape)[31m============= Model.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Model.o $(view)/Model/Model.cpp -I $(extLibI) $(flags)

# MESH
$(objectsPath)/Mesh.o: $(view)/Model/Mesh/Mesh.cpp $(view)/Model/Mesh/Mesh.h $(makefile)
	@echo $(marks)$(escape)[31m============= Mesh.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Mesh.o $(view)/Model/Mesh/Mesh.cpp -I $(extLibI) $(flags)

# MATERIAL
$(objectsPath)/Material.o: $(view)/Model/Material/Material.cpp $(view)/Model/Material/Material.h $(makefile)
	@echo $(marks)$(escape)[31m============= Material.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Material.o $(view)/Model/Material/Material.cpp -I $(extLibI) $(flags)

# TEXTURE
$(objectsPath)/Texture.o: $(view)/Model/Texture/Texture.cpp $(view)/Model/Texture/Texture.h $(makefile)
	@echo $(marks)$(escape)[31m============= Texture.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Texture.o $(view)/Model/Texture/Texture.cpp -I $(extLibI) $(flags)

# RENDER TEXTURE
$(objectsPath)/RenderTexture.o: $(view)/Model/Texture/RenderTexture.cpp $(view)/Model/Texture/RenderTexture.h $(makefile)
	@echo $(marks)$(escape)[31m============= RenderTexture.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/RenderTexture.o $(view)/Model/Texture/RenderTexture.cpp -I $(extLibI) $(flags)

# UI
$(objectsPath)/Ui.o: $(view)/Ui/Ui.cpp $(view)/Ui/Ui.h $(makefile)
	@echo $(marks)$(escape)[31m============= Ui.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Ui.o $(view)/Ui/Ui.cpp -I $(extLibI) $(flags)

# SHADER
$(objectsPath)/Shader.o: $(view)/Model/Shader/Shader.cpp $(view)/Model/Shader/Shader.h $(makefile)
	@echo $(marks)$(escape)[31m============= Shader.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Shader.o $(view)/Model/Shader/Shader.cpp -I $(extLibI) $(flags)

# CAMERA
$(objectsPath)/Camera.o: $(view)/Camera/Camera.cpp $(view)/Camera/Camera.h $(makefile)
	@echo $(marks)$(escape)[31m============= Camera.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Camera.o $(view)/Camera/Camera.cpp -I $(extLibI) $(flags)

# KERNEL
$(objectsPath)/Kernel.o: $(view)/Renderer/Kernel/Kernel.cpp $(view)/Renderer/Kernel/Kernel.h $(makefile)
	@echo $(marks)$(escape)[31m============= Kernel.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Kernel.o $(view)/Renderer/Kernel/Kernel.cpp -I $(extLibI) $(flags)


# CONTROLLER

# EVENT HANDLER
$(objectsPath)/EventHandler.o:  $(controller)/EventHandler.cpp $(controller)/EventHandler.h $(makefile)
	@echo $(marks)$(escape)[31m============= EventHandler.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/EventHandler.o $(controller)/EventHandler.cpp -I $(extLibI) $(flags) $(libraries)


# MODEL

# PHYSICS WORLD
$(objectsPath)/PhysicsWorld.o: $(model)/Physics/PhysicsWorld.cpp $(model)/Physics/PhysicsWorld.h $(makefile)
	@echo $(marks)$(escape)[31m============= PhysicsWorld.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/PhysicsWorld.o $(model)/Physics/PhysicsWorld.cpp -I $(extLibI) $(flags) $(bulletL)

# PHYSICS BODY
$(objectsPath)/PhysicsBody.o: $(model)/Physics/PhysicsBody/PhysicsBody.cpp $(model)/Physics/PhysicsBody/PhysicsBody.h $(makefile)
	@echo $(marks)$(escape)[31m============= PhysicsBody.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/PhysicsBody.o $(model)/Physics/PhysicsBody/PhysicsBody.cpp -I $(extLibI) $(flags) $(bulletL)

# ENTITY
$(objectsPath)/Entity.o: $(model)/Entity.cpp $(model)/Entity.h $(makefile)
	@echo $(marks)$(escape)[31m============= Entity.cpp (source) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/Entity.o $(model)/Entity.cpp -I $(extLibI) $(flags)



# LIBRARIES

# IMGUI
$(objectsPath)/imgui.o: $(imgui)/imgui.cpp
	@echo $(marks)$(escape)[31m============= imgui.cpp (extLib) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/imgui.o $(imgui)/imgui.cpp -I $(extLibI) $(flags)

$(objectsPath)/imgui_impl_glfw.o: $(imguiBE)/imgui_impl_glfw.cpp
	@echo $(marks)$(escape)[31m============= imgui_impl_glfw.cpp (extLib) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/imgui_impl_glfw.o $(imguiBE)/imgui_impl_glfw.cpp -I $(extLibI) $(flags)

$(objectsPath)/imgui_impl_opengl3.o: $(imguiBE)/imgui_impl_opengl3.cpp
	@echo $(marks)$(escape)[31m============= imgui_impl_opengl3.cpp (extLib) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/imgui_impl_opengl3.o $(imguiBE)/imgui_impl_opengl3.cpp -I $(extLibI) $(flags)

$(objectsPath)/imgui_demo.o: $(imgui)/imgui_demo.cpp
	@echo $(marks)$(escape)[31m============= imgui_demo.cpp (extLib) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/imgui_demo.o $(imgui)/imgui_demo.cpp -I $(extLibI) $(flags)

$(objectsPath)/imgui_draw.o: $(imgui)/imgui_draw.cpp
	@echo $(marks)$(escape)[31m============= imgui_draw.cpp (extLib) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/imgui_draw.o $(imgui)/imgui_draw.cpp -I $(extLibI) $(flags)

$(objectsPath)/imgui_widgets.o: $(imgui)/imgui_widgets.cpp
	@echo $(marks)$(escape)[31m============= imgui_widgets.cpp (extLib) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/imgui_widgets.o $(imgui)/imgui_widgets.cpp -I $(extLibI) $(flags)

$(objectsPath)/imgui_tables.o: $(imgui)/imgui_tables.cpp
	@echo $(marks)$(escape)[31m============= imgui_tables.cpp (extLib) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/imgui_tables.o $(imgui)/imgui_tables.cpp -I $(extLibI) $(flags)

# GLAD
$(objectsPath)/glad.o: $(libs)/GLAD/src/glad.c
	@echo $(marks)$(escape)[31m============ glad.c (extLib) =============$(noColor)$(marks)
	g++ -c -o $(objectsPath)/glad.o $(libs)/GLAD/src/glad.c -I $(libs)/GLAD/include $(flags)

run:
	@$(runCommand)

exec: main run

clean:
	rm ./bin/objects/*.o
