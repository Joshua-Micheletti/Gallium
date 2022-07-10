source = ./Source
extLibs = ./ExtLibs
gladI = ${extLibs}/GLAD/include
gladL = ${extLibs}/GLAD/src
glfwI = ${extLibs}/glfw/include
#glfwL = ${extLibs}/glfw/lib-mingw
glmI = ${extLibs}/glm
#sfmlI = ${extLibs}/SFML-2.5.1-mingw/include
#sfmlL = ${extLibs}/SFML-2.5.1-mingw/lib
imguiI = ${extLibs}/imgui
stbimage = ${extLibs}/stb-master

ifeq ($(OS),Windows_NT)
	sfmlI = ${extLibs}/SFML-2.5.1-mingw/include
	sfmlL = ${extLibs}/SFML-2.5.1-mingw/lib
	glfwL = ${extLibs}/glfw/lib-mingw
	extLibL = ${glfwL} -L ${glmI} -L ${sfmlL} -L ${imguiI} -L ${stbimage}
	libraries = -lopengl32 -lglfw3 -lsfml-graphics -lsfml-window -lsfml-system
	runCommand = cd "./bin" && "./launch.exe"
else
	sfmlI = ${extLibs}/SFML-2.5.1-linux/include
	sfmlL = ${extLibs}/SFML-2.5.1-linux/lib
	extLibL = ${glmI} -L ${sfmlL} -L ${imguiI} -L ${stbimage}
	libraries = -lGL -lglfw3 -ldl -lm -lGLU -lX11 -lpthread -lsfml-graphics -lsfml-window -lsfml-system -lGLEW
	runCommand = export LD_LIBRARY_PATH=./ && cd ./bin && ./launch
endif

extLibI = ${gladI} -I ${glfwI} -I ${glmI} -I ${sfmlI} -I ${imguiI} -I ${stbimage}

flags = -w -std=c++11 -Ofast
#libraries = -lopengl32 -lglfw3 -lsfml-graphics -lsfml-window -lsfml-system

objectsPath = ./bin/objects
objects = ${objectsPath}/Main.o ${objectsPath}/glad.o ${objectsPath}/init.o ${objectsPath}/renderer.o ${objectsPath}/eventHandler.o ${objectsPath}/ui.o ${objectsPath}/entity.o ${objectsPath}/shader.o ${objectsPath}/camera.o ${objectsPath}/kernel.o ${objectsPath}/imgui.o ${objectsPath}/imgui_impl_glfw.o ${objectsPath}/imgui_impl_opengl3.o ${objectsPath}/imgui_demo.o ${objectsPath}/imgui_draw.o ${objectsPath}/imgui_widgets.o 
objectsTarget = ${objectsPath}/main.o glad.o init.o renderer.o eventHandler.o ui.o entity.o shader.o camera.o kernel.o imgui.o imgui_impl_glfw.o imgui_impl_opengl3.o imgui_demo.o imgui_draw.o imgui_widgets.o

main: ${objects} makefile
	echo ============= COMPILING MAIN PROGRAM =============
	g++ -o ./bin/launch ${objects} -L ${extLibL} -I ${extLibI} ${libraries} ${flags}


${objectsPath}/Main.o: ${source}/Main.cpp makefile
	echo "============= Main.cpp (source) ============="
	g++ -c -o ${objectsPath}/main.o ${source}/Main.cpp -I ${extLibI} -I ${source}/Libs/ -L ${extLibL} ${flags} ${libraries}

${objectsPath}/init.o: ${source}/Libs/init.cpp makefile
	echo "============= init.cpp (source) ============="
	g++ -c -o ${objectsPath}/init.o ${source}/Libs/init.cpp -I ${extLibI} -L ${extLibL} ${flags} ${libraries}

${objectsPath}/renderer.o: ${source}/Libs/renderer.cpp makefile
	echo "============= renderer.cpp (source) ============="
	g++ -c -o ${objectsPath}/renderer.o ${source}/Libs/renderer.cpp -I ${extLibI} -L ${extLibL} ${flags}

${objectsPath}/eventHandler.o: ${source}/Libs/eventHandler.cpp makefile
	echo "============= eventHandler.cpp (source) ============="
	g++ -c -o ${objectsPath}/eventHandler.o ${source}/Libs/eventHandler.cpp -I ${extLibI} -L ${extLibL} ${flags} ${libraries}

${objectsPath}/ui.o: ${source}/Libs/ui.cpp makefile
	echo "============= ui.cpp (source) ============="
	g++ -c -o ${objectsPath}/ui.o ${source}/Libs/ui.cpp -I ${extLibI} -L ${extLibL} ${flags}

${objectsPath}/entity.o: ${source}/Libs/entity.cpp makefile
	echo "============= entity.cpp (source) ============="
	g++ -c -o ${objectsPath}/entity.o ${source}/Libs/entity.cpp -I ${extLibI} -L ${extLibL} ${flags}

${objectsPath}/shader.o: ${source}/Libs/shader.cpp makefile
	echo "============= shader.cpp (source) ============="
	g++ -c -o ${objectsPath}/shader.o ${source}/Libs/shader.cpp -I ${extLibI} -L ${extLibL} ${flags}

${objectsPath}/camera.o: ${source}/Libs/camera.cpp makefile
	echo "============= camera.cpp (source) ============="
	g++ -c -o ${objectsPath}/camera.o ${source}/Libs/camera.cpp -I ${extLibI} -L ${extLibL} ${flags}

${objectsPath}/kernel.o: ${source}/Libs/kernel.cpp makefile
	echo "============= kernel.cpp (source) ============="
	g++ -c -o ${objectsPath}/kernel.o ${source}/Libs/kernel.cpp -I ${extLibI} -L ${extLibL} ${flags}

${objectsPath}/imgui.o: ${extLibs}/imgui/imgui.cpp makefile
	echo "============= imgui.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui.o ${extLibs}/imgui/imgui.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_impl_glfw.o: ${extLibs}/imgui/imgui_impl_glfw.cpp makefile
	echo "============= imgui_impl_glfw.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_impl_glfw.o ${extLibs}/imgui/imgui_impl_glfw.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_impl_opengl3.o: ${extLibs}/imgui/imgui_impl_opengl3.cpp makefile
	echo "============= imgui_impl_opengl3.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_impl_opengl3.o ${extLibs}/imgui/imgui_impl_opengl3.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_demo.o: ${extLibs}/imgui/imgui_demo.cpp makefile
	echo "============= imgui_demo.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_demo.o ${extLibs}/imgui/imgui_demo.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_draw.o: ${extLibs}/imgui/imgui_draw.cpp makefile
	echo "============= imgui_draw.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_draw.o ${extLibs}/imgui/imgui_draw.cpp -I ${extLibI} ${flags}

${objectsPath}/imgui_widgets.o: ${extLibs}/imgui/imgui_widgets.cpp makefile
	echo "============= imgui_widgets.cpp (extLib) ============="
	g++ -c -o ${objectsPath}/imgui_widgets.o ${extLibs}/imgui/imgui_widgets.cpp -I ${extLibI} ${flags}

${objectsPath}/glad.o: ${extLibs}/GLAD/src/glad.c makefile
	echo "============= glad.c (extLib) ============="
	g++ -c -o ${objectsPath}/glad.o ${extLibs}/GLAD/src/glad.c -I ${extLibs}/GLAD/include ${flags}

run:
#start /d "./bin" launch.exe
#Start-Process -FilePath launch.exe -WorkingDirectory ./bin
#start launch.exe -wo ./bin
#cd "./bin" && "./launch.exe"
	${runCommand}