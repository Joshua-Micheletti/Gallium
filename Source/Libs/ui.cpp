#include "ui.h"
#include "init.h"
#include "entity.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "renderer.h"
#include "eventHandler.h"
#include "GLFW/glfw3.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <algorithm>

// initialize the fields and formats the texts styles
UI::UI(GLFWwindow *window, Renderer* renderer, EventHandler* eventHandler) {
	// get the window reference
	this->window = window;
	this->renderer = renderer;
	this->eventHandler = eventHandler;

	// setup the update clock
	this->tick = sf::milliseconds(1000 / 10);
	this->time = this->clock.getElapsedTime();

	this->showMetricsWindow = false;
	this->showUserGuide = false;
	this->showAboutWindow = false;
	this->showDemoWindow = false;
	this->showFPS = true;
	this->pauseFlag = false;
	this->showLeftColumn = true;
	this->showRightColumn = true;
	this->showBottomRow = true;

	//ImGui::SFML::Init(*this->window);
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGuiIO& io = ImGui::GetIO();

	io.FontDefault = io.Fonts->AddFontFromFileTTF("../Fonts/OpenSans/OpenSans-Regular.ttf", 18.0f);

	this->setupImGuiStyle();
}

void UI::setReferenceWindow(GLFWwindow *window) {
	this->window = window;
}

void UI::setupImGuiStyle() {
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameRounding = 0.0f;
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.18f, 0.94f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.45f, 1.00f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.61f, 1.00f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.52f, 1.00f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.17f, 0.17f, 0.17f, 0.48f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.62f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.00f, 0.45f, 1.00f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.21f, 0.57f, 1.00f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.34f, 0.64f, 1.00f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.18f, 0.18f, 0.18f, 0.94f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.45f, 1.00f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.18f, 0.61f, 1.00f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.00f, 1.00f, 0.18f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.18f, 0.18f, 0.94f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.18f, 0.61f, 1.00f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.00f, 0.45f, 1.00f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 0.65f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.46f, 1.00f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void UI::drawLeftColumn() {
	static bool firstDraw = true;
	static Entity *selectedEntity;
	static int selected = -1;

	static ImGuiWindowFlags leftColumnWindowFlags = ImGuiWindowFlags_NoMove |
		//ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoTitleBar;

	ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1));

	ImGui::Begin("Left Column", NULL, leftColumnWindowFlags);

	if (ImGui::CollapsingHeader("Entities")) {
		for (int i = 0; i < entityBuffer.size(); i++) {
			if (ImGui::Selectable(entityBuffer[i]->getName().c_str(), selected == i)) {
				if (selected == i) {
					selected = -1;
					selectedEntity = NULL;
				}
				else {
					selectedEntity = entityBuffer[i];
					selected = i;
				}
			}
		}
	}

	ImGui::Separator();

	if (selectedEntity != NULL) {
		ImGui::Text(std::string("Entity: ").append(selectedEntity->getName()).c_str());
		if (ImGui::CollapsingHeader("Properties")) {
			
			if (ImGui::TreeNode("Position")) {
				float x = selectedEntity->getWorldPosition().x;
				ImGui::DragFloat("X", &x, 0.005f);
				float y = selectedEntity->getWorldPosition().y;
				ImGui::DragFloat("Y", &y, 0.005f);
				float z = selectedEntity->getWorldPosition().z;
				ImGui::DragFloat("Z", &z, 0.005f);

				selectedEntity->placeAt(glm::vec3(x, y, z), camera.getViewMatrix());

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Rotation")) {
				float x = selectedEntity->getRotationFactor().x;
				ImGui::DragFloat("X", &x, 0.02f);
				float y = selectedEntity->getRotationFactor().y;
				ImGui::DragFloat("Y", &y, 0.02f);
				float z = selectedEntity->getRotationFactor().z;
				ImGui::DragFloat("Z", &z, 0.02f);

				selectedEntity->setRotation(x, y, z);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Scale")) {
				float x = selectedEntity->getScalingFactor().x;
				if (ImGui::DragFloat("X", &x, 0.005f));
				float y = selectedEntity->getScalingFactor().y;
				if (ImGui::DragFloat("Y", &y, 0.005f));
				float z = selectedEntity->getScalingFactor().z;
				if (ImGui::DragFloat("Z", &z, 0.005f));

				selectedEntity->setScale(glm::vec3(x, y, z));
			}

			ImGui::Separator();

			std::vector<char*> shaderNames;

			for (int i = 0; i < shaderBuffer.size(); i++) {
				shaderNames.push_back(shaderBuffer[i].getName());
			}

			static int item_current;
			char** Carray = shaderNames.data();

			size_t arraySize = shaderNames.size();

			item_current = selectedEntity->getShader();

			ImGui::Text("Shader");
			ImGui::SameLine();
			ImGui::Combo("###ShaderDropdown", &item_current, Carray, arraySize);

			selectedEntity->setShader(item_current);

			std::vector<char*> outlineNames;

			outlineNames.push_back((char*)"Solid");
			outlineNames.push_back((char*)"Alpha");
			outlineNames.push_back((char*)"Wireframe");

			char** outlineCarray = outlineNames.data();

			size_t outlineArraySize = outlineNames.size();

			static int outlineCurrent = outlineType;

			ImGui::Text("Outline");
			ImGui::SameLine();
			ImGui::Combo("###OutlineDropdown", &outlineCurrent, outlineCarray, outlineArraySize);

			outlineType = outlineCurrent;
		}
	}

	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

	if (firstDraw) {
		ImGui::SetWindowSize(ImVec2(250, screenHeight - this->menuBarSize.y));
		firstDraw = false;
	}
	
	if (updateResolution) {
		ImGui::SetWindowSize(ImVec2(ImGui::GetWindowWidth(), screenHeight - this->menuBarSize.y));
	}

	this->leftColumnSize = ImGui::GetWindowSize();

	this->renderer->setHighlightedEntity(selected);
	
	ImGui::SetWindowPos(ImVec2(0, this->menuBarSize.y));

	static ImGuiStyle& leftColumnStyle = ImGui::GetStyle();

	leftColumnStyle.WindowRounding = 0;
	leftColumnStyle.WindowBorderSize = 0;

	ImGui::End();
}

void UI::drawRightColumn() {
	static bool firstDraw = true;
	static Entity* selectedEntity;

	static ImGuiWindowFlags rightColumnWindowFlags = ImGuiWindowFlags_NoMove |
		//ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoTitleBar;

	ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1));

	ImGui::Begin("Right Column", NULL, rightColumnWindowFlags);
	static bool antialiasing = true;
	static int item_current = 4;
	if (ImGui::CollapsingHeader("Rendering Options")) {
		bool tmp = vsync;
		
		if (ImGui::MenuItem("Pause", NULL, &this->pauseFlag));
		if (ImGui::MenuItem("Render Real Time Reflections", NULL, &doReflection));
		if (ImGui::MenuItem("VSync", NULL, &vsync)) {
			if (tmp != vsync) {
				if (vsync == true) {
					glfwSwapInterval(1);
				}
				else {
					glfwSwapInterval(0);
				}
			}
		}

		tmp = fullscreen;
		if (ImGui::MenuItem("Fullscreen", NULL, &fullscreen)) {
			if (tmp != fullscreen) {
				if (fullscreen == true) {
					GLFWmonitor* monitor = glfwGetPrimaryMonitor();
					const GLFWvidmode* mode = glfwGetVideoMode(monitor);
					glfwSetWindowMonitor(this->window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

					int width;
					int height;
					glfwGetFramebufferSize(window, &width, &height);
					glViewport(0, 0, mode->width, mode->height);
					screenWidth = mode->width;
					screenHeight = mode->height;
					updateResolution = true;
				}
				else {
					glfwSetWindowMonitor(this->window, NULL, 0, 0, windowWidth, windowHeight, 60);
					glfwSetWindowPos(this->window, 40, 40);

					int width;
					int height;
					glfwGetFramebufferSize(window, &width, &height);
					glViewport(0, 0, width, height);
					screenWidth = width;
					screenHeight = height;
					updateResolution = true;
				}
			}

		}

		if (ImGui::MenuItem("Depth Buffer", NULL, &depthBuffer));

		const char* items[] = {"1", "2", "4", "8", "16"};
		
		ImGui::Text("MSAA");
		ImGui::SameLine();
		ImGui::Combo("###MSAADropdown", &item_current, items, IM_ARRAYSIZE(items));
	}

	samples = pow(2, item_current + 1);

	if (ImGui::CollapsingHeader("Bounding Box Display")) {
		if (ImGui::MenuItem("Object Bounding Box", NULL, &drawOBB));
		if (ImGui::MenuItem("External Axis Aligned Bounding Box", NULL, &drawAABB1));
		if (ImGui::MenuItem("Internal Axis Aligned Bounding Box", NULL, &drawAABB2));
		if (ImGui::MenuItem("Average Axis Aligned Bounding Box", NULL, &drawAABB3));
		if (ImGui::MenuItem("True Axis Aligned Bounding Box", NULL, &drawAABB4));
		if (ImGui::MenuItem("Internal Bounding Sphere", NULL, &drawBS));
		if (ImGui::MenuItem("External Bounding Sphere", NULL, &drawBS2));
		if (ImGui::MenuItem("True Bounding Sphere", NULL, &drawBS3));
	}

	if (ImGui::CollapsingHeader("Post Processing Effect")) {
		static int selectedEffect = 0;

		const char* items[] = {"None", "Inverted Colors", "Color Filter", "Black Circle (View)", "Black Circle (screen)", "Black Fade (view)",
							   "Black Fade (screen)", "Fish Eye", "Barrel Distortion", "Kernel Convolution"};

		ImGui::Text("Effect");
		ImGui::SameLine();
		ImGui::Combo("###PostProcessDropdown", &selectedEffect, items, IM_ARRAYSIZE(items));

		/*if (selectedEffect == 0) {
			this->renderer->setPostProcessingEffect(0);
		}

		else if (selectedEffect == 1) {
			this->renderer->setPostProcessingEffect(1);
		}*/

		this->renderer->setPostProcessingEffect(selectedEffect);

		if (selectedEffect == 9) {
			this->renderer->setPostProcessingEffect(9);

			const char* kernels[] = { "Gaussian Blur", "Box Blur", "Edge Detection", "Sharpening" };

			static int selectedKernel;
			ImGui::Text("Kernel");
			ImGui::SameLine();
			ImGui::Combo("###KernelDropdown", &selectedKernel, kernels, IM_ARRAYSIZE(kernels));

			this->renderer->setKernelConvolutionMode(selectedKernel);

			if (selectedKernel == 0 || selectedKernel == 1) {
				static int kernelSize;
				ImGui::InputInt("Kernel Size", &kernelSize);

				this->renderer->setKernelSize(kernelSize);

				if (selectedKernel == 0) {
					static float blurStrength;
					ImGui::InputFloat("Blur Strength", &blurStrength);

					this->renderer->setGaussianBlurStrength(blurStrength);
				}
			}
		}
	}

	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

	if (firstDraw) {
		ImGui::SetWindowSize(ImVec2(250, screenHeight - this->menuBarSize.y));
		firstDraw = false;
	}

	if (updateResolution) {
		ImGui::SetWindowSize(ImVec2(ImGui::GetWindowWidth(), screenHeight - this->menuBarSize.y));
	}

	ImGui::SetWindowPos(ImVec2(screenWidth - ImGui::GetWindowWidth(), this->menuBarSize.y));
	this->rightColumnSize = ImGui::GetWindowSize();

	static ImGuiStyle& rightColumnStyle = ImGui::GetStyle();

	rightColumnStyle.WindowRounding = 0;
	rightColumnStyle.WindowBorderSize = 0;

	ImGui::End();
}

void UI::drawBottomRow() {
	static bool firstDraw = true;

	static ImGuiWindowFlags bottomRowFlags = ImGuiWindowFlags_NoMove |
		//ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoTitleBar;

	ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0), ImVec2(-1, FLT_MAX));

	ImGui::Begin("BottomRow", NULL, bottomRowFlags);
	{
		float height;
		if (firstDraw) {
			height = 200.0f;
		}
		else {
			height = std::min(ImGui::GetWindowSize().y - 20.0f, 200.0f);
		}

		ImGui::BeginChild("OutlineMask", ImVec2((float)screenWidth / (float)screenHeight * height, 0));
		ImGui::Image((ImTextureID)this->renderer->getOutlineMaskTexture(), ImVec2((float)screenWidth / (float)screenHeight * height, height), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("Depth", ImVec2((float)screenWidth / (float)screenHeight * height, 0));
		ImGui::Image((ImTextureID)this->renderer->getDepthBufferTexture(), ImVec2((float)screenWidth / (float)screenHeight * height, height), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("Texture", ImVec2((float)screenWidth / (float)screenHeight * height, 0));
		ImGui::Image((ImTextureID)entityBuffer[3]->getTexture(), ImVec2((float)screenWidth / (float)screenHeight * height, height), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
	}

	if (firstDraw) {
		ImGui::SetWindowSize(ImVec2(screenWidth - 500, 220));
		firstDraw = false;
	}
	else {
		ImGui::SetWindowSize(ImVec2(screenWidth - this->leftColumnSize.x - this->rightColumnSize.x, ImGui::GetWindowSize().y));
	}
	
	ImVec2 size = ImGui::GetWindowSize();

	ImGui::SetWindowPos(ImVec2(this->leftColumnSize.x, screenHeight - size.y));

	ImGui::End();
}

void UI::drawFPSWindow() {
	static ImGuiWindowFlags FPSwindowFlags = ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoTitleBar;

	if (this->showFPS == true) {
		ImGui::Begin("Frame Rate", &this->showFPS, FPSwindowFlags);

		static float fps[90] = {};
		static float frameTime[90] = {};
		static float reflectionRenderTime[90] = {};
		static float forwardRenderTime[90] = {};
		static float MSPostProcessRenderTime[90] = {};
		static float postProcessRenderTime[90] = {};
		static int values_offset = 0;
		static double refresh_time = 0.0;

		if (refresh_time == 0) {
			refresh_time = ImGui::GetTime();
		}

		while (refresh_time < ImGui::GetTime()) {
			fps[values_offset] = 1.0f / this->fpsTime.asSeconds();
			frameTime[values_offset] = this->fpsTime.asMicroseconds() / 1000.0f;
			reflectionRenderTime[values_offset] = this->renderer->getReflectionRenderTime() * 1000.0f;
			forwardRenderTime[values_offset] = this->renderer->getForwardRenderTime() * 1000.0f;
			MSPostProcessRenderTime[values_offset] = this->renderer->getMSPostProcessingPassTime() * 1000.0f;
			postProcessRenderTime[values_offset] = this->renderer->getPostProcessingPassTime() * 1000.0f;
			values_offset = (values_offset + 1) % IM_ARRAYSIZE(fps);
			refresh_time += 1.0f / 10.0f;
		}

		char overlay[32];
		sprintf(overlay, "FPS %.0f", fps[(values_offset - 1) % IM_ARRAYSIZE(fps)]);

		ImGui::PushItemWidth(-1);
		ImGui::PlotLines("###fpsGraph", fps, IM_ARRAYSIZE(fps), values_offset, overlay, 0.0f, 300.0f, ImVec2(0, 40.0f));
		ImGui::PopItemWidth();

		sprintf(overlay, "Frame Time %.3f", frameTime[(values_offset - 1) % IM_ARRAYSIZE(frameTime)]);

		ImGui::PushItemWidth(-1);
		ImGui::PlotLines("###frameTimeGraph", frameTime, IM_ARRAYSIZE(frameTime), values_offset, overlay, 0.0f, 60.0f, ImVec2(0, 40.0f));
		ImGui::PopItemWidth();


		ImGui::Separator();

		if (ImGui::CollapsingHeader("More Info")) {

			sprintf(overlay, "Reflection %.3f", reflectionRenderTime[(values_offset - 1) % IM_ARRAYSIZE(reflectionRenderTime)]);

			ImGui::PushItemWidth(-1);
			ImGui::PlotLines("###reflectionGraph", reflectionRenderTime, IM_ARRAYSIZE(reflectionRenderTime), values_offset, overlay, 0.0f, 60.0f, ImVec2(0, 40.0f));
			ImGui::PopItemWidth();

			sprintf(overlay, "Forward %.3f", forwardRenderTime[(values_offset - 1) % IM_ARRAYSIZE(forwardRenderTime)]);

			ImGui::PushItemWidth(-1);
			ImGui::PlotLines("###forwardGraph", forwardRenderTime, IM_ARRAYSIZE(forwardRenderTime), values_offset, overlay, 0.0f, 60.0f, ImVec2(0, 40.0f));
			ImGui::PopItemWidth();

			sprintf(overlay, "MS Post %.3f", MSPostProcessRenderTime[(values_offset - 1) % IM_ARRAYSIZE(MSPostProcessRenderTime)]);

			ImGui::PushItemWidth(-1);
			ImGui::PlotLines("###MSPostGraph", MSPostProcessRenderTime, IM_ARRAYSIZE(MSPostProcessRenderTime), values_offset, overlay, 0.0f, 60.0f, ImVec2(0, 40.0f));
			ImGui::PopItemWidth();

			sprintf(overlay, "Post Process %.3f", postProcessRenderTime[(values_offset - 1) % IM_ARRAYSIZE(postProcessRenderTime)]);

			ImGui::PushItemWidth(-1);
			ImGui::PlotLines("###postProcessGraph", postProcessRenderTime, IM_ARRAYSIZE(postProcessRenderTime), values_offset, overlay, 0.0f, 60.0f, ImVec2(0, 40.0f));
			ImGui::PopItemWidth();
		}


		ImGui::SetWindowSize(ImVec2(200.0f, 0.0f));

		if (this->showRightColumn) {
			ImGui::SetWindowPos(ImVec2(screenWidth - ImGui::GetWindowSize().x - this->rightColumnSize.x, 0 + this->menuBarSize.y));
		}
		else {
			ImGui::SetWindowPos(ImVec2(screenWidth - ImGui::GetWindowSize().x, 0 + this->menuBarSize.y));
		}
		

		static ImGuiStyle& style = ImGui::GetStyle();

		style.WindowRounding = 0;
		style.WindowBorderSize = 0;

		ImGui::End();
	}


}

void UI::drawMenuBar() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Close", "ALT + F4")) {
				glfwSetWindowShouldClose(this->window, GL_TRUE);
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")) {

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			if (ImGui::MenuItem("FPS", NULL, &this->showFPS));
			if (ImGui::MenuItem("Left Column", NULL, &this->showLeftColumn));
			if (ImGui::MenuItem("Right Column", NULL, &this->showRightColumn));

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("ImGui")) {
			if (ImGui::MenuItem("Metrics Window", NULL, &this->showMetricsWindow));

			if (ImGui::MenuItem("User Guide", NULL, &this->showUserGuide));

			if (ImGui::MenuItem("About Window", NULL, &this->showAboutWindow));

			if (ImGui::MenuItem("Demo", NULL, &this->showDemoWindow));

			ImGui::EndMenu();
		}

		this->menuBarSize = ImGui::GetWindowSize();

		ImGui::EndMainMenuBar();
	}

	if (this->showMetricsWindow == true) {
		ImGui::ShowMetricsWindow(&this->showMetricsWindow);
	}

	if (this->showUserGuide == true) {
		ImGui::ShowUserGuide();
	}

	if (this->showAboutWindow == true) {
		ImGui::ShowAboutWindow(&this->showAboutWindow);
	}

	if (this->showDemoWindow == true) {
		ImGui::ShowDemoWindow(&this->showAboutWindow);
	}

	if (this->pauseFlag == true) {
		this->eventHandler->setUpdateFlag(false);
	}
	else {
		this->eventHandler->setUpdateFlag(true);
	}
}

void UI::drawImGui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	this->drawMenuBar();

	if (this->showLeftColumn == true) {
		this->drawLeftColumn();
	}

	if (this->showRightColumn == true) {
		this->drawRightColumn();
	}

	if (this->showBottomRow == true) {
		this->drawBottomRow();
	}

	this->drawFPSWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// just calls all the other methods, this method is public
void UI::drawInfo() {
	this->fpsTime = this->fpsClock.getElapsedTime();
	this->fpsClock.restart().asSeconds();

	if (displayInfo) {
		this->drawImGui();
	}

	if (updated) {
		updateResolution = false;
	}
	
	updated = false;
}

