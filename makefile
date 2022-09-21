source = ./Source
extLibs = ./ExtLibs
gladI = ${extLibs}/GLAD/include
gladL = ${extLibs}/GLAD/src
glfwI = ${extLibs}/glfw/include
#glfwL = ${extLibs}/glfw/lib-mingw
glmI = ${extLibs}/glm
#sfmlI = ${extLibs}/SFML-2.5.1-mingw/include
#sfmlL = ${extLibs}/SFML-2.5.1-mingw/lib
imgui = ${extLibs}/imgui-1.88
imguiBE = ${imgui}/backends
stbimage = ${extLibs}/stb-master

ifeq ($(OS),Windows_NT)
	glfwL = ${extLibs}/glfw/lib-mingw
	extLibL = ${glfwL} -L ${glmI} -L ${imgui} -L ${stbimage}
	libraries = -lopengl32 -lglfw3
	runCommand = cd "./bin" && "./launch.exe"
else
	extLibL = ${glmI} -L ${imgui} -L ${stbimage}
	libraries = -lGL -lglfw3 -ldl -lm -lGLU -lX11 -lpthread -lGLEW
	runCommand = (cd ./bin && ./launch)
endif

extLibI = ${gladI} -I ${glfwI} -I ${glmI} -I ${imgui} -I ${imguiBE} -I ${stbimage}

flags = -w -std=c++11 -Ofast

objectsPath = ./bin/objects
objects = ${objectsPath}/main.o ${objectsPath}/glad.o ${objectsPath}/init.o ${objectsPath}/renderer.o ${objectsPath}/eventHandler.o ${objectsPath}/ui.o ${objectsPath}/entity.o ${objectsPath}/shader.o ${objectsPath}/camera.o ${objectsPath}/kernel.o ${objectsPath}/imgui.o ${objectsPath}/imgui_impl_glfw.o ${objectsPath}/imgui_impl_opengl3.o ${objectsPath}/imgui_demo.o ${objectsPath}/imgui_draw.o ${objectsPath}/imgui_widgets.o ${objectsPath}/imgui_tables.o

main: ${objects} makefile
	echo ============= COMPILING MAIN PROGRAM =============
	g++ -o ./bin/launch ${objects} -L ${extLibL} -I ${extLibI} ${libraries} ${flags}


${objectsPath}/main.o: ${source}/Main.cpp makefile
	echo "============= Main.cpp (source) ============="
	g++ -c -o ${objectsPath}/main.o ${source}/Main.cpp -I ${extLibI} -I ${source}/Libs/ ${flags} ${libraries}

${objectsPath}/init.o: ${source}/Libs/init.cpp makefile
	echo "============= init.cpp (source) ============="
	g++ -c -o ${objectsPath}/init.o ${source}/Libs/init.cpp -I ${extLibI} ${flags} ${libraries}

${objectsPath}/renderer.o: ${source}/Libs/renderer.cpp makefile
	echo "============= renderer.cpp (source) ============="
	g++ -c -o ${objectsPath}/renderer.o ${source}/Libs/renderer.cpp -I ${extLibI} ${flags}

${objectsPath}/eventHandler.o: ${source}/Libs/eventHandler.cpp makefile
	echo "============= eventHandler.cpp (source) ============="
	g++ -c -o ${objectsPath}/eventHandler.o ${source}/Libs/eventHandler.cpp -I ${extLibI} ${flags} ${libraries}

${objectsPath}/ui.o: ${source}/Libs/ui.cpp makefile
	echo "============= ui.cpp (source) ============="
	g++ -c -o ${objectsPath}/ui.o ${source}/Libs/ui.cpp -I ${extLibI} ${flags}

${objectsPath}/entity.o: ${source}/Libs/entity.cpp makefile
	echo "============= entity.cpp (source) ============="
	g++ -c -o ${objectsPath}/entity.o ${source}/Libs/entity.cpp -I ${extLibI} ${flags}

${objectsPath}/shader.o: ${source}/Libs/shader.cpp makefile
	echo "============= shader.cpp (source) ============="
	g++ -c -o ${objectsPath}/shader.o ${source}/Libs/shader.cpp -I ${extLibI} ${flags}

${objectsPath}/camera.o: ${source}/Libs/camera.cpp makefile
	echo "============= camera.cpp (source) ============="
	g++ -c -o ${objectsPath}/camera.o ${source}/Libs/camera.cpp -I ${extLibI} ${flags}

${objectsPath}/kernel.o: ${source}/Libs/kernel.cpp makefile
	echo "============= kernel.cpp (source) ============="
	g++ -c -o ${objectsPath}/kernel.o ${source}/Libs/kernel.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui.o: ${imgui}/imgui.cpp makefile
	echo "============= imgui.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui.o ${imgui}/imgui.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_impl_glfw.o: ${imguiBE}/imgui_impl_glfw.cpp makefile
	echo "============= imgui_impl_glfw.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_impl_glfw.o ${imguiBE}/imgui_impl_glfw.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_impl_opengl3.o: ${imguiBE}/imgui_impl_opengl3.cpp makefile
	echo "============= imgui_impl_opengl3.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_impl_opengl3.o ${imguiBE}/imgui_impl_opengl3.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_demo.o: ${imgui}/imgui_demo.cpp makefile
	echo "============= imgui_demo.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_demo.o ${imgui}/imgui_demo.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_draw.o: ${imgui}/imgui_draw.cpp makefile
	echo "============= imgui_draw.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_draw.o ${imgui}/imgui_draw.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_widgets.o: ${imgui}/imgui_widgets.cpp makefile
	echo "============= imgui_widgets.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_widgets.o ${imgui}/imgui_widgets.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_tables.o: ${imgui}/imgui_tables.cpp makefile
	echo "============= imgui_tables.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_tables.o ${imgui}/imgui_tables.cpp -I ${extLibI} ${flags}

${objectsPath}/glad.o: ${extLibs}/GLAD/src/glad.c makefile
	echo "============= glad.c (extLib) ============="
	g++ -c -o ${objectsPath}/glad.o ${extLibs}/GLAD/src/glad.c -I ${extLibs}/GLAD/include ${flags}

run:
	${runCommand}

build_run: main run
	make
	make run
