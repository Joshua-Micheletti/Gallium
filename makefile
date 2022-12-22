source = ./Source
view = ${source}/Libs/View
model = ${source}/Libs/Model
controller = ${source}/Libs/Controller
extLibs = ./ExtLibs
gladI = ${extLibs}/GLAD/include
gladL = ${extLibs}/GLAD/src
glfwI = ${extLibs}/glfw/include
#glfwL = ${extLibs}/glfw/lib-mingw
glmI = ${extLibs}/glm
imgui = ${extLibs}/imgui-1.88
imguiBE = ${imgui}/backends
stbimage = ${extLibs}/stb-master

ifeq ($(OS),Windows_NT)
	glfwL = ${extLibs}/glfw/lib-mingw
	extLibL = ${glfwL} -L ${glmI} -L ${imgui} -L ${stbimage}
	libraries = -lopengl32 -lglfw3
	runCommand = cd "./bin" && "./launch.exe"
	marks = 
	escape = 
	noColor = ${escape}[0m
else
	extLibL = ${glmI} -L ${imgui} -L ${stbimage}
	libraries = -lGL -lglfw3 -ldl -lm -lGLU -lX11 -lpthread -lGLEW
	runCommand = (cd ./bin && ./launch)
	marks = "
	escape = \033
	noColor = ${escape}[0m
endif

extLibI = ${gladI} -I ${glfwI} -I ${glmI} -I ${imgui} -I ${imguiBE} -I ${stbimage}

flags = -w -std=c++11 -Ofast

objectsPath = ./bin/objects
objects = ${objectsPath}/main.o ${objectsPath}/engine.o ${objectsPath}/sandbox.o ${objectsPath}/global.o ${objectsPath}/window.o ${objectsPath}/utils.o ${objectsPath}/glad.o ${objectsPath}/renderer.o ${objectsPath}/rendererManager.o ${objectsPath}/model.o ${objectsPath}/mesh.o ${objectsPath}/material.o ${objectsPath}/texture.o ${objectsPath}/renderTexture.o ${objectsPath}/eventHandler.o ${objectsPath}/ui.o ${objectsPath}/physicsWorld.o ${objectsPath}/physicsBody.o ${objectsPath}/entity.o ${objectsPath}/shader.o ${objectsPath}/camera.o ${objectsPath}/kernel.o ${objectsPath}/imgui.o ${objectsPath}/imgui_impl_glfw.o ${objectsPath}/imgui_impl_opengl3.o ${objectsPath}/imgui_demo.o ${objectsPath}/imgui_draw.o ${objectsPath}/imgui_widgets.o ${objectsPath}/imgui_tables.o

main: ${objects} makefile
	@echo ${marks}${escape}[31m============= COMPILING MAIN PROGRAM =============${noColor}${marks}
	g++ -o ./bin/launch ${objects} -L ${extLibL} -I ${extLibI} ${libraries} ${flags}
	@echo ${marks}${escape}[32mDone${noColor}${marks}

# MAIN
${objectsPath}/main.o: ${source}/Main.cpp makefile
	@echo ${marks}${escape}[31m============= main.cpp "(source)" ============${noColor} ${marks}
	g++ -c -o ${objectsPath}/main.o ${source}/Main.cpp -I ${extLibI} -I ${source}/Libs/ ${flags} ${libraries}

# ENGINE
${objectsPath}/engine.o: ${source}/Libs/Engine/engine.cpp ${source}/Libs/Engine/engine.h makefile
	@echo ${marks}${escape}[31m============= engine.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/engine.o ${source}/Libs/Engine/engine.cpp -I ${extLibI} ${flags} ${libraries}

# SANDBOX
${objectsPath}/sandbox.o: ${source}/Libs/Sandbox/sandbox.cpp ${source}/Libs/Sandbox/sandbox.h makefile
	@echo ${marks}${escape}[31m============= sandbox.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/sandbox.o ${source}/Libs/Sandbox/sandbox.cpp -I ${extLibI} ${flags} ${libraries}

# INIT
${objectsPath}/init.o: ${source}/Libs/init.cpp ${source}/Libs/init.h makefile
	@echo ${marks}${escape}[31m============= init.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/init.o ${source}/Libs/init.cpp -I ${extLibI} ${flags} ${libraries}

# UTILS
${objectsPath}/utils.o: ${source}/Libs/utils.cpp ${source}/Libs/utils.h makefile
	@echo ${marks}${escape}[31m============= utils.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/utils.o ${source}/Libs/utils.cpp -I ${extLibI} ${flags} ${libraries}

# GLOBAL
${objectsPath}/global.o: ${source}/Libs/global.cpp ${source}/Libs/global.h makefile
	@echo ${marks}${escape}[31m============= global.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/global.o ${source}/Libs/global.cpp -I ${extLibI} ${flags} ${libraries}

# WINDOW
${objectsPath}/window.o: ${view}/window/window.cpp ${view}/window/window.h makefile
	@echo ${marks}${escape}[31m============= window.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/window.o ${view}/window/window.cpp -I ${extLibI} ${flags}

# RENDERER
${objectsPath}/renderer.o: ${view}/renderer/renderer.cpp ${view}/renderer/renderer.h makefile
	@echo ${marks}${escape}[31m============= renderer.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/renderer.o ${view}/renderer/renderer.cpp -I ${extLibI} ${flags}

# RENDERERMANAGER
${objectsPath}/rendererManager.o: ${view}/renderer/rendererManager.cpp ${view}/renderer/rendererManager.h makefile
	@echo ${marks}${escape}[31m============= rendererManager.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/rendererManager.o ${view}/renderer/rendererManager.cpp -I ${extLibI} ${flags}

# MODEL
${objectsPath}/model.o: ${view}/model/model.cpp ${view}/model/model.h makefile
	@echo ${marks}${escape}[31m============= model.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/model.o ${view}/model/model.cpp -I ${extLibI} ${flags}

# MESH
${objectsPath}/mesh.o: ${view}/model/mesh/mesh.cpp ${view}/model/mesh/mesh.h makefile
	@echo ${marks}${escape}[31m============= mesh.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/mesh.o ${view}/model/mesh/mesh.cpp -I ${extLibI} ${flags}

# MATERIAL
${objectsPath}/material.o: ${view}/model/material/material.cpp ${view}/model/material/material.h makefile
	@echo ${marks}${escape}[31m============= material.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/material.o ${view}/model/material/material.cpp -I ${extLibI} ${flags}

# TEXTURE
${objectsPath}/texture.o: ${view}/model/texture/texture.cpp ${view}/model/texture/texture.h makefile
	@echo ${marks}${escape}[31m============= texture.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/texture.o ${view}/model/texture/texture.cpp -I ${extLibI} ${flags}

# RENDER TEXTURE
${objectsPath}/renderTexture.o: ${view}/model/texture/renderTexture.cpp ${view}/model/texture/renderTexture.h makefile
	@echo ${marks}${escape}[31m============= renderTexture.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/renderTexture.o ${view}/model/texture/renderTexture.cpp -I ${extLibI} ${flags}

# EVENT HANDLER
${objectsPath}/eventHandler.o:  ${controller}/eventHandler.cpp ${controller}/eventHandler.h makefile
	@echo ${marks}${escape}[31m============= eventHandler.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/eventHandler.o ${controller}/eventHandler.cpp -I ${extLibI} ${flags} ${libraries}

# UI
${objectsPath}/ui.o: ${view}/ui/ui.cpp ${view}/ui/ui.h makefile
	@echo ${marks}${escape}[31m============= ui.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/ui.o ${view}/ui/ui.cpp -I ${extLibI} ${flags}

# PHYSICS WORLD
${objectsPath}/physicsWorld.o: ${model}/physics/physicsWorld.cpp ${model}/physics/physicsWorld.h makefile
	@echo ${marks}${escape}[31m============= physicsWorld.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/physicsWorld.o ${model}/physics/physicsWorld.cpp -I ${extLibI} ${flags}

# PHYSICS BODY
${objectsPath}/physicsBody.o: ${model}/physics/physicsBody/physicsBody.cpp ${model}/physics/physicsBody/physicsBody.h makefile
	@echo ${marks}${escape}[31m============= physicsBody.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/physicsBody.o ${model}/physics/physicsBody/physicsBody.cpp -I ${extLibI} ${flags}

# ENTITY
${objectsPath}/entity.o: ${model}/entity.cpp ${model}/entity.h makefile
	@echo ${marks}${escape}[31m============= entity.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/entity.o ${model}/entity.cpp -I ${extLibI} ${flags}

# SHADER
${objectsPath}/shader.o: ${view}/model/shader/shader.cpp ${view}/model/shader/shader.h makefile
	@echo ${marks}${escape}[31m============= shader.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/shader.o ${view}/model/shader/shader.cpp -I ${extLibI} ${flags}

# CAMERA
${objectsPath}/camera.o: ${view}/camera/camera.cpp ${view}/camera/camera.h makefile
	@echo ${marks}${escape}[31m============= camera.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/camera.o ${view}/camera/camera.cpp -I ${extLibI} ${flags}

# KERNEL
${objectsPath}/kernel.o: ${view}/renderer/kernel/kernel.cpp ${view}/renderer/kernel/kernel.h makefile
	@echo ${marks}${escape}[31m============= kernel.cpp "(source)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/kernel.o ${view}/renderer/kernel/kernel.cpp -I ${extLibI} ${flags}

# IMGUI
${objectsPath}/imgui.o: ${imgui}/imgui.cpp makefile
	@echo ${marks}${escape}[31m============= imgui.cpp "(extLib)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui.o ${imgui}/imgui.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_impl_glfw.o: ${imguiBE}/imgui_impl_glfw.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_impl_glfw.cpp "(extLib)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_impl_glfw.o ${imguiBE}/imgui_impl_glfw.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_impl_opengl3.o: ${imguiBE}/imgui_impl_opengl3.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_impl_opengl3.cpp "(extLib)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_impl_opengl3.o ${imguiBE}/imgui_impl_opengl3.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_demo.o: ${imgui}/imgui_demo.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_demo.cpp "(extLib)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_demo.o ${imgui}/imgui_demo.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_draw.o: ${imgui}/imgui_draw.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_draw.cpp "(extLib)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_draw.o ${imgui}/imgui_draw.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_widgets.o: ${imgui}/imgui_widgets.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_widgets.cpp "(extLib)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_widgets.o ${imgui}/imgui_widgets.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_tables.o: ${imgui}/imgui_tables.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_tables.cpp "(extLib)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_tables.o ${imgui}/imgui_tables.cpp -I ${extLibI} ${flags}

${objectsPath}/glad.o: ${extLibs}/GLAD/src/glad.c makefile
	@echo ${marks}${escape}[31m============ glad.c "(extLib)" =============${noColor}${marks}
	g++ -c -o ${objectsPath}/glad.o ${extLibs}/GLAD/src/glad.c -I ${extLibs}/GLAD/include ${flags}

run:
	${runCommand}

build_run: main run
	make
	make run
