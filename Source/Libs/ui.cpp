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

	static ImGuiWindowFlags leftColumnWindowFlags = ImGuiWindowFlags_NoMove |
		//ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoTitleBar;

	ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1));

	ImGui::Begin("Left Column", NULL, leftColumnWindowFlags);

	if (ImGui::CollapsingHeader("Entities")) {
		static int selected = -1;
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
		}
	}

	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

	if (firstDraw) {
		ImGui::SetWindowSize(ImVec2(200, screenHeight - this->menuBarSize.y));
		firstDraw = false;
	}
	
	if (updateResolution) {
		ImGui::SetWindowSize(ImVec2(ImGui::GetWindowWidth(), screenHeight - this->menuBarSize.y));
	}
	
	ImGui::SetWindowPos(ImVec2(0, this->menuBarSize.y));

	static ImGuiStyle& leftColumnStyle = ImGui::GetStyle();

	leftColumnStyle.WindowRounding = 0;
	leftColumnStyle.WindowBorderSize = 0;

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
		static int values_offset = 0;
		static double refresh_time = 0.0;

		if (refresh_time == 0) {
			refresh_time = ImGui::GetTime();
		}

		while (refresh_time < ImGui::GetTime()) {
			fps[values_offset] = 1.0f / this->fpsTime.asSeconds();
			frameTime[values_offset] = this->fpsTime.asMicroseconds() / 1000.0f;
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

		ImGui::SetWindowSize(ImVec2(200.0f, 0.0f));
		ImGui::SetWindowPos(ImVec2(screenWidth - ImGui::GetWindowSize().x, 0 + this->menuBarSize.y));

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
					}
					else {
						glfwSetWindowMonitor(this->window, NULL, 0, 0, windowWidth, windowHeight, 60);
						glfwSetWindowPos(this->window, 40, 40);
					}
				}
				
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			if (ImGui::MenuItem("FPS", NULL, &this->showFPS));
			if (ImGui::MenuItem("Left Column", NULL, &this->showLeftColumn));

			ImGui::Separator();

			if (ImGui::MenuItem("Object Bounding Box", NULL, &drawOBB));
			if (ImGui::MenuItem("External Axis Aligned Bounding Box", NULL, &drawAABB1));
			if (ImGui::MenuItem("Internal Axis Aligned Bounding Box", NULL, &drawAABB2));
			if (ImGui::MenuItem("Average Axis Aligned Bounding Box", NULL, &drawAABB3));
			if (ImGui::MenuItem("True Axis Aligned Bounding Box", NULL, &drawAABB4));
			if (ImGui::MenuItem("Internal Bounding Sphere", NULL, &drawBS));
			if (ImGui::MenuItem("External Bounding Sphere", NULL, &drawBS2));
			if (ImGui::MenuItem("True Bounding Sphere", NULL, &drawBS3));

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

	this->drawFPSWindow();

	if (this->showLeftColumn == true) {
		this->drawLeftColumn();
	}

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

	updateResolution = false;
}

