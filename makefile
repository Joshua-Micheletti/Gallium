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
objects = ${objectsPath}/main.o ${objectsPath}/window.o ${objectsPath}/utils.o ${objectsPath}/glad.o ${objectsPath}/init.o ${objectsPath}/renderer.o ${objectsPath}/drawingEntity.o ${objectsPath}/model.o ${objectsPath}/material.o ${objectsPath}/eventHandler.o ${objectsPath}/ui.o ${objectsPath}/entity.o ${objectsPath}/shader.o ${objectsPath}/camera.o ${objectsPath}/kernel.o ${objectsPath}/imgui.o ${objectsPath}/imgui_impl_glfw.o ${objectsPath}/imgui_impl_opengl3.o ${objectsPath}/imgui_demo.o ${objectsPath}/imgui_draw.o ${objectsPath}/imgui_widgets.o ${objectsPath}/imgui_tables.o

main: ${objects} makefile
	@echo ${marks}${escape}[31m============= COMPILING MAIN PROGRAM =============${noColor}${marks}
	g++ -o ./bin/launch ${objects} -L ${extLibL} -I ${extLibI} ${libraries} ${flags}
	@echo ${marks}${escape}[32mDone${noColor}${marks}


${objectsPath}/main.o: ${source}/Main.cpp makefile
	@echo ${marks}${escape}[31m============= Main.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/main.o ${source}/Main.cpp -I ${extLibI} -I ${source}/Libs/ ${flags} ${libraries}

${objectsPath}/init.o: ${source}/Libs/init.cpp makefile
	@echo ${marks}${escape}[31m============= init.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/init.o ${source}/Libs/init.cpp -I ${extLibI} ${flags} ${libraries}

${objectsPath}/utils.o: ${source}/Libs/utils.cpp makefile
	@echo ${marks}${escape}[31m============= utils.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/utils.o ${source}/Libs/utils.cpp -I ${extLibI} ${flags} ${libraries}

${objectsPath}/window.o: ${view}/window.cpp makefile
	@echo ${marks}${escape}[31m============= window.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/window.o ${view}/window.cpp -I ${extLibI} ${flags}

${objectsPath}/renderer.o: ${view}/renderer.cpp makefile
	@echo ${marks}${escape}[31m============= renderer.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/renderer.o ${view}/renderer.cpp -I ${extLibI} ${flags}

${objectsPath}/drawingEntity.o: ${view}/drawingEntity.cpp makefile
	@echo ${marks}${escape}[31m============= drawingEntity.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/drawingEntity.o ${view}/drawingEntity.cpp -I ${extLibI} ${flags}

${objectsPath}/model.o: ${view}/model.cpp makefile
	@echo ${marks}${escape}[31m============= model.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/model.o ${view}/model.cpp -I ${extLibI} ${flags}

${objectsPath}/material.o: ${view}/material.cpp makefile
	@echo ${marks}${escape}[31m============= material.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/material.o ${view}/material.cpp -I ${extLibI} ${flags}

${objectsPath}/eventHandler.o: ${controller}/eventHandler.cpp makefile
	@echo ${marks}${escape}[31m============= eventHandler.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/eventHandler.o ${controller}/eventHandler.cpp -I ${extLibI} ${flags} ${libraries}

${objectsPath}/ui.o: ${view}/ui.cpp makefile
	@echo ${marks}${escape}[31m============= ui.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/ui.o ${view}/ui.cpp -I ${extLibI} ${flags}

${objectsPath}/entity.o: ${model}/entity.cpp makefile
	@echo ${marks}${escape}[31m============= entity.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/entity.o ${model}/entity.cpp -I ${extLibI} ${flags}

${objectsPath}/shader.o: ${view}/shader.cpp makefile
	@echo ${marks}${escape}[31m============= shader.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/shader.o ${view}/shader.cpp -I ${extLibI} ${flags}

${objectsPath}/camera.o: ${view}/camera.cpp makefile
	@echo ${marks}${escape}[31m============= camera.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/camera.o ${view}/camera.cpp -I ${extLibI} ${flags}

${objectsPath}/kernel.o: ${view}/kernel.cpp makefile
	@echo ${marks}${escape}[31m============= kernel.cpp (source) =============${noColor}${marks}
	g++ -c -o ${objectsPath}/kernel.o ${view}/kernel.cpp -I ${extLibI} ${flags}

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
