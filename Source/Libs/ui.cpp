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

	char _windowTitle[255] = "ImGui + SFML = <3";
	this->windowTitle = _windowTitle;

	float acolor[3] = { 0.f, 0.f, 0.f };
	color = acolor;

	// setup the update clock
	this->tick = sf::milliseconds(1000 / 10);
	this->time = this->clock.getElapsedTime();

	// load the UI font
	if (!this->font.loadFromFile("../Fonts/segmono_boot.ttf")) {
		printf("COULDN'T LOAD FONT\n");
	}

	// set the UI font
	this->boundingBoxText.setFont(this->font);
	this->debug.setFont(this->font);
	this->fps.setFont(this->font);
	this->frameTime.setFont(this->font);

	// set the entity info style
	this->debug.setCharacterSize(16);
	this->debug.setFillColor(sf::Color::White);
	this->debug.setPosition(5, 5);
	this->debug.setOutlineThickness(1);
	this->debug.setOutlineColor(sf::Color::Black);

	// set the fps and frametime styles
	this->fps.setCharacterSize(16);
	this->fps.setFillColor(sf::Color::White);
	this->fps.setOutlineThickness(1);
	this->fps.setOutlineColor(sf::Color::Black);

	this->frameTime.setCharacterSize(16);
	this->frameTime.setFillColor(sf::Color::White);
	this->frameTime.setOutlineThickness(1);
	this->frameTime.setOutlineColor(sf::Color::Black);

	// set the bounding box text style
	this->boundingBoxText.setCharacterSize(16);
	this->boundingBoxText.setFillColor(sf::Color::Red);
	this->boundingBoxText.setOutlineThickness(1);
	this->boundingBoxText.setOutlineColor(sf::Color::Black);

	// design the crosshair
	this->crosshair.setRadius(2);
	this->crosshair.setFillColor(sf::Color(255, 255, 255));
	sf::FloatRect crosshairBounds = this->crosshair.getLocalBounds();
	this->crosshair.setOrigin(crosshairBounds.left + crosshairBounds.width / 2, crosshairBounds.top + crosshairBounds.height / 2);
	this->crosshair.setPosition(screenWidth / 2, screenHeight / 2);
	this->crosshair.setOutlineThickness(1);
	this->crosshair.setOutlineColor(sf::Color::Black);

	this->showMetricsWindow = false;
	this->showUserGuide = false;
	this->showAboutWindow = false;
	this->showDemoWindow = false;
	this->showFPS = true;
	this->pauseFlag = false;

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



// checks which bounding boxes are being displayed and sets up the text accordingly and draws them
//void UI::drawBoundingBoxText() {
//	sf::FloatRect bbBounds;
//
//	if (drawOBB) {
//		this->boundingBoxText.setString("Object Bounding Box");
//		bbBounds = this->boundingBoxText.getLocalBounds();
//		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
//		this->boundingBoxText.setFillColor(sf::Color(255, 0, 0));
//		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 1 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
//		this->window->draw(this->boundingBoxText);
//	}
//
//	if (drawAABB1) {
//		this->boundingBoxText.setString("External AABB");
//		bbBounds = this->boundingBoxText.getLocalBounds();
//		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
//		this->boundingBoxText.setFillColor(sf::Color(0, 255, 0));
//		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 2 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
//		this->window->draw(this->boundingBoxText);
//	}
//
//	if (drawAABB2) {
//		this->boundingBoxText.setString("Internal AABB");
//		bbBounds = this->boundingBoxText.getLocalBounds();
//		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
//		this->boundingBoxText.setFillColor(sf::Color(0, 0, 255));
//		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 3 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
//		this->window->draw(this->boundingBoxText);
//	}
//
//	if (drawAABB3) {
//		this->boundingBoxText.setString("Average AABB");
//		bbBounds = this->boundingBoxText.getLocalBounds();
//		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
//		this->boundingBoxText.setFillColor(sf::Color(0, 255, 255));
//		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 4 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
//		this->window->draw(this->boundingBoxText);
//	}
//
//	if (drawAABB4) {
//		this->boundingBoxText.setString("True AABB");
//		bbBounds = this->boundingBoxText.getLocalBounds();
//		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
//		this->boundingBoxText.setFillColor(sf::Color(255, 0, 255));
//		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 5 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
//		this->window->draw(this->boundingBoxText);
//	}
//
//	if (drawBS) {
//		this->boundingBoxText.setString("Internal BS");
//		bbBounds = this->boundingBoxText.getLocalBounds();
//		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
//		this->boundingBoxText.setFillColor(sf::Color(255, 255, 0));
//		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 6 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
//		this->window->draw(this->boundingBoxText);
//	}
//
//	if (drawBS2) {
//		this->boundingBoxText.setString("External BS");
//		bbBounds = this->boundingBoxText.getLocalBounds();
//		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
//		this->boundingBoxText.setFillColor(sf::Color(255, 127, 0));
//		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 7 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
//		this->window->draw(this->boundingBoxText);
//	}
//
//	if (drawBS3) {
//		this->boundingBoxText.setString("True BS");
//		bbBounds = this->boundingBoxText.getLocalBounds();
//		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
//		this->boundingBoxText.setFillColor(sf::Color(127, 255, 0));
//		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 8 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
//		this->window->draw(this->boundingBoxText);
//	}
//}



void UI::drawLeftColumn() {
	static ImGuiWindowFlags leftColumnWindowFlags = ImGuiWindowFlags_NoMove |
		//ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoTitleBar;
	ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1));

	ImGui::Begin("Left Column", NULL, leftColumnWindowFlags);

	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);
	ImGui::SetWindowSize(ImVec2(200, screenHeight - this->menuBarSize.y), ImGuiCond_FirstUseEver);
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
				//this->window->close();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")) {
			if (ImGui::MenuItem("Pause", NULL, &this->pauseFlag));
			if (ImGui::MenuItem("Render Real Time Reflections", NULL, &doReflection));
			if (ImGui::MenuItem("VSync", NULL, &vsync));
			if (ImGui::MenuItem("Fullscreen", NULL, &fullscreen)) {
				/*sf::RenderWindow *newWindow = initSFML_OpenGL("test", 8);
				this->window->close();
				this->window = newWindow;
				ImGui::SFML::Init(*newWindow);
				this->eventHandler->setWindowReference(newWindow);*/
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
	//this->window->pushGLStates();
	//this->window->resetGLStates();
	//ImGui::SFML::Update(*this->window, this->deltaClock.restart());
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
	//ImGui::SFML::Render(*this->window);
	//this->window->popGLStates();
}


// utility method for converting a float number to a string with a desired decimal precision
std::string UI::floatToString(float number, int precision) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << number;
	std::string s = stream.str();
	return(s);
}

// just calls all the other methods, this method is public
void UI::drawInfo() {
	this->fpsTime = this->fpsClock.getElapsedTime();

	/*while (this->time.asMilliseconds() + this->tick.asMilliseconds() < this->clock.getElapsedTime().asMilliseconds()) {
		this->time += this->tick;
	}*/

	this->fpsClock.restart().asSeconds();

	//this->window->draw(this->crosshair);


	if (displayInfo) {
		this->drawImGui();
	}
}

