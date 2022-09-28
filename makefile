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
objects = ${objectsPath}/main.o ${objectsPath}/global.o ${objectsPath}/window.o ${objectsPath}/utils.o ${objectsPath}/glad.o ${objectsPath}/init.o ${objectsPath}/renderer.o ${objectsPath}/rendererManager.o ${objectsPath}/drawingEntity.o ${objectsPath}/model.o ${objectsPath}/material.o ${objectsPath}/texture.o ${objectsPath}/eventHandler.o ${objectsPath}/ui.o ${objectsPath}/entity.o ${objectsPath}/shader.o ${objectsPath}/camera.o ${objectsPath}/kernel.o ${objectsPath}/imgui.o ${objectsPath}/imgui_impl_glfw.o ${objectsPath}/imgui_impl_opengl3.o ${objectsPath}/imgui_demo.o ${objectsPath}/imgui_draw.o ${objectsPath}/imgui_widgets.o ${objectsPath}/imgui_tables.o

main: ${objects} makefile
	@echo ${marks}${escape}[31m============= COMPILING MAIN PROGRAM =============${noColor}${marks}
	g++ -o ./bin/launch ${objects} -L ${extLibL} -I ${extLibI} ${libraries} ${flags}
	@echo ${marks}${escape}[32mDone${noColor}${marks}

# MAIN
${objectsPath}/main.o: ${source}/Main.cpp makefile
	@echo ${marks}${escape}[31m============= Main.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/main.o ${source}/Main.cpp -I ${extLibI} -I ${source}/Libs/ ${flags} ${libraries}

# INIT
${objectsPath}/init.o: ${source}/Libs/init.cpp ${source}/Libs/init.h makefile
	@echo ${marks}${escape}[31m============= init.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/init.o ${source}/Libs/init.cpp -I ${extLibI} ${flags} ${libraries}

# UTILS
${objectsPath}/utils.o: ${source}/Libs/utils.cpp ${source}/Libs/utils.h makefile
	@echo ${marks}${escape}[31m============= utils.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/utils.o ${source}/Libs/utils.cpp -I ${extLibI} ${flags} ${libraries}

# GLOBAL
${objectsPath}/global.o: ${source}/Libs/global.cpp ${source}/Libs/global.h makefile
	@echo ${marks}${escape}[31m============= global.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/global.o ${source}/Libs/global.cpp -I ${extLibI} ${flags} ${libraries}

# WINDOW
${objectsPath}/window.o: ${view}/window/window.cpp ${view}/window/window.h makefile
	@echo ${marks}${escape}[31m============= window.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/window.o ${view}/window/window.cpp -I ${extLibI} ${flags}

# RENDERER
${objectsPath}/renderer.o: ${view}/renderer/renderer.cpp ${view}/renderer/renderer.h makefile
	@echo ${marks}${escape}[31m============= renderer.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/renderer.o ${view}/renderer/renderer.cpp -I ${extLibI} ${flags}

# RENDERERMANAGER
${objectsPath}/rendererManager.o: ${view}/renderer/rendererManager.cpp ${view}/renderer/rendererManager.h makefile
	@echo ${marks}${escape}[31m============= rendererManager.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/rendererManager.o ${view}/renderer/rendererManager.cpp -I ${extLibI} ${flags}

# DRAWING ENTITY
${objectsPath}/drawingEntity.o: ${view}/drawingEntity/drawingEntity.cpp ${view}/drawingEntity/drawingEntity.h makefile
	@echo ${marks}${escape}[31m============= drawingEntity.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/drawingEntity.o ${view}/drawingEntity/drawingEntity.cpp -I ${extLibI} ${flags}

# MODEL
${objectsPath}/model.o: ${view}/drawingEntity/model/model.cpp ${view}/drawingEntity/model/model.h makefile
	@echo ${marks}${escape}[31m============= model.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/model.o ${view}/drawingEntity/model/model.cpp -I ${extLibI} ${flags}

# MATERIAL
${objectsPath}/material.o: ${view}/drawingEntity/material/material.cpp ${view}/drawingEntity/material/material.h makefile
	@echo ${marks}${escape}[31m============= material.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/material.o ${view}/drawingEntity/material/material.cpp -I ${extLibI} ${flags}

# TEXTURE
${objectsPath}/texture.o: ${view}/drawingEntity/material/texture/texture.cpp ${view}/drawingEntity/material/texture/texture.h makefile
	@echo ${marks}${escape}[31m============= texture.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/texture.o ${view}/drawingEntity/material/texture/texture.cpp -I ${extLibI} ${flags}

# EVENT HANDLER
${objectsPath}/eventHandler.o:  ${controller}/eventHandler.cpp ${controller}/eventHandler.h makefile
	@echo ${marks}${escape}[31m============= eventHandler.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/eventHandler.o ${controller}/eventHandler.cpp -I ${extLibI} ${flags} ${libraries}

# UI
${objectsPath}/ui.o: ${view}/ui/ui.cpp ${view}/ui/ui.h makefile
	@echo ${marks}${escape}[31m============= ui.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/ui.o ${view}/ui/ui.cpp -I ${extLibI} ${flags}

# ENTITY
${objectsPath}/entity.o: ${model}/entity.cpp ${model}/entity.h makefile
	@echo ${marks}${escape}[31m============= entity.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/entity.o ${model}/entity.cpp -I ${extLibI} ${flags}

# MATERIAL
${objectsPath}/shader.o: ${view}/drawingEntity/material/shader/shader.cpp ${view}/drawingEntity/material/shader/shader.h makefile
	@echo ${marks}${escape}[31m============= shader.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/shader.o ${view}/drawingEntity/material/shader/shader.cpp -I ${extLibI} ${flags}

# CAMERA
${objectsPath}/camera.o: ${view}/camera/camera.cpp ${view}/camera/camera.h makefile
	@echo ${marks}${escape}[31m============= camera.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/camera.o ${view}/camera/camera.cpp -I ${extLibI} ${flags}

# KERNEL
${objectsPath}/kernel.o: ${view}/renderer/kernel/kernel.cpp ${view}/renderer/kernel/kernel.h makefile
	@echo ${marks}${escape}[31m============= kernel.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/kernel.o ${view}/renderer/kernel/kernel.cpp -I ${extLibI} ${flags}

# IMGUI
${objectsPath}/imgui.o: ${imgui}/imgui.cpp makefile
	@echo ${marks}${escape}[31m============= imgui.cpp (extLib) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui.o ${imgui}/imgui.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_impl_glfw.o: ${imguiBE}/imgui_impl_glfw.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_impl_glfw.cpp (extLib) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_impl_glfw.o ${imguiBE}/imgui_impl_glfw.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_impl_opengl3.o: ${imguiBE}/imgui_impl_opengl3.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_impl_opengl3.cpp (extLib) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_impl_opengl3.o ${imguiBE}/imgui_impl_opengl3.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_demo.o: ${imgui}/imgui_demo.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_demo.cpp (extLib) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_demo.o ${imgui}/imgui_demo.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_draw.o: ${imgui}/imgui_draw.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_draw.cpp (extLib) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_draw.o ${imgui}/imgui_draw.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_widgets.o: ${imgui}/imgui_widgets.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_widgets.cpp (extLib) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_widgets.o ${imgui}/imgui_widgets.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_tables.o: ${imgui}/imgui_tables.cpp makefile
	@echo ${marks}${escape}[31m============= imgui_tables.cpp (extLib) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/imgui_tables.o ${imgui}/imgui_tables.cpp -I ${extLibI} ${flags}

${objectsPath}/glad.o: ${extLibs}/GLAD/src/glad.c makefile
	@echo ${marks}${escape}[31m============ glad.c (extLib) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/glad.o ${extLibs}/GLAD/src/glad.c -I ${extLibs}/GLAD/include ${flags}

run:
	${runCommand}

build_run: main run
	make
	make run
