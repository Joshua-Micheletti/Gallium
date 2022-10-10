#include "ui.h"


// initialize the fields and formats the texts styles
UI::UI(Renderer* renderer, EventHandler* eventHandler) {
	this->renderer = renderer;
	this->eventHandler = eventHandler;

	// setup the update clock
	this->showMetricsWindow = false;
	this->showUserGuide = false;
	this->showAboutWindow = false;
	this->showDemoWindow = false;
	this->showFPS = true;
	this->pauseFlag = false;
	this->showLeftColumn = true;
	this->showRightColumn = true;
	this->showBottomRow = true;

	ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplGlfw_InitForOpenGL(window.window(), true);
	
	ImGuiIO& io = ImGui::GetIO();

	io.FontDefault = io.Fonts->AddFontFromFileTTF("../Fonts/OpenSans/OpenSans-Regular.ttf", 18.0f);

	this->setupImGuiStyle();
}

void UI::HelpMarker(const char* desc) {
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void UI::drawImage(unsigned int texture, float width, float height) {
	float my_tex_w = width;
	float my_tex_h = height;
	{
		ImGuiIO& io = ImGui::GetIO();
		//ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
		ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
		ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
		ImGui::Image((ImTextureID)texture, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 1), ImVec2(1, 0));
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			float region_sz = 32.0f;
			float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
			float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
			float zoom = 4.0f;
			if (region_x < 0.0f) { region_x = 0.0f; }
			else if (region_x > my_tex_w - region_sz) { region_x = my_tex_w - region_sz; }
			if (region_y < 0.0f) { region_y = 0.0f; }
			else if (region_y > my_tex_h - region_sz) { region_y = my_tex_h - region_sz; }
			ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
			ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
			ImVec2 uv0 = ImVec2((region_x) / my_tex_w, (region_y) / my_tex_h);
			ImVec2 uv1 = ImVec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
			ImGui::Image((ImTextureID)texture, ImVec2(region_sz * zoom, region_sz * zoom), ImVec2(uv0.x, fabs(1 - uv0.y)), ImVec2(uv1.x, fabs(1 - uv1.y)), tint_col, border_col);
			ImGui::EndTooltip();
		}
	}
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
	static std::string selectedEntity;
	static int selected = -1;

	static ImGuiWindowFlags leftColumnWindowFlags = ImGuiWindowFlags_NoMove |
		// ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoTitleBar;

	ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1));

	ImGui::Begin("Left Column", NULL, leftColumnWindowFlags);

	if (ImGui::CollapsingHeader("Entities")) {
        std::vector<std::string> entities = RM.modelNames();
		for (int i = 0; i < entities.size(); i++) {
			// if (ImGui::Selectable("test", false));
			if (ImGui::Selectable(entities[i].c_str(), RM.selectedEntity() == entities[i])) {
				if (selected == i) {
					selected = -1;
					RM.selectedEntity("");
				}
				else {
					RM.selectedEntity(entities[i]);
					selected = i;
				}
			}
		}
	}

	ImGui::Separator();

	if (RM.selectedEntity().size() != 0) {
		ImGui::Text(std::string("Entity: ").append(RM.selectedEntity()).c_str());
		if (ImGui::CollapsingHeader("Properties")) {
			
			if (ImGui::TreeNode("Position")) {
				float x = RM.model(RM.selectedEntity())->position().x;
				ImGui::DragFloat("X", &x, 0.005f);
				float y = RM.model(RM.selectedEntity())->position().y;
				ImGui::DragFloat("Y", &y, 0.005f);
				float z = RM.model(RM.selectedEntity())->position().z;
				ImGui::DragFloat("Z", &z, 0.005f);

				RM.model(RM.selectedEntity())->position(glm::vec3(x, y, z));

				ImGui::TreePop();
			}

			// if (ImGui::TreeNode("Rotation")) {
			// 	float x = selectedEntity->getRotationFactor().x;
			// 	ImGui::DragFloat("X", &x, 0.02f);
			// 	float y = selectedEntity->getRotationFactor().y;
			// 	ImGui::DragFloat("Y", &y, 0.02f);
			// 	float z = selectedEntity->getRotationFactor().z;
			// 	ImGui::DragFloat("Z", &z, 0.02f);

			// 	selectedEntity->setRotation(x, y, z);

			// 	ImGui::TreePop();
			// }

			// if (ImGui::TreeNode("Scale")) {
			// 	float x = selectedEntity->getScalingFactor().x;
			// 	if (ImGui::DragFloat("X", &x, 0.005f));
			// 	float y = selectedEntity->getScalingFactor().y;
			// 	if (ImGui::DragFloat("Y", &y, 0.005f));
			// 	float z = selectedEntity->getScalingFactor().z;
			// 	if (ImGui::DragFloat("Z", &z, 0.005f));

			// 	selectedEntity->setScale(glm::vec3(x, y, z));
			// }

			ImGui::Separator();

			

			/*
			std::vector<std::string> materialNames = RM.materialNames();
            std::vector<char*> cMaterialNames;
			for (int i = 0; i < materialNames.size(); i++) {
				cMaterialNames.push_back((char*)materialNames[i].c_str());
			}

			static int item_current;
			char** Carray = cMaterialNames.data();

			size_t arraySize = materialNames.size();

			item_current = find(RM.drawingEntity(RM.selectedEntity())->material(), materialNames);

			ImGui::Text("Material");
			ImGui::SameLine();
			ImGui::Combo("###MaterialDropdown", &item_current, Carray, arraySize);

			RM.drawingEntity(RM.selectedEntity())->material(materialNames[item_current]);

			if (RM.drawingEntity(RM.selectedEntity())->isLight()) {
				ImGui::Separator();

				static float lightColor[3] = { 1.0, 1.0, 1.0 };

				lightColor[0] = RM.drawingEntity(RM.selectedEntity())->lightColor().x;
				lightColor[1] = RM.drawingEntity(RM.selectedEntity())->lightColor().y;
				lightColor[2] = RM.drawingEntity(RM.selectedEntity())->lightColor().z;

				ImGui::ColorEdit3("Light Color", lightColor);

				RM.drawingEntity(RM.selectedEntity())->lightColor(glm::vec3(lightColor[0], lightColor[1], lightColor[2]));
			}

			*/
			

		

			// std::vector<char*> outlineNames;

			// outlineNames.push_back((char*)"Solid");
			// outlineNames.push_back((char*)"Alpha");
			// outlineNames.push_back((char*)"Wireframe");

			// char** outlineCarray = outlineNames.data();

			// size_t outlineArraySize = outlineNames.size();

			// static int outlineCurrent = outlineType;

			// ImGui::Text("Outline");
			// ImGui::SameLine();
			// ImGui::Combo("###OutlineDropdown", &outlineCurrent, outlineCarray, outlineArraySize);

			// outlineType = outlineCurrent;
		}

		static int selectedMesh = -1;

		std::vector<component_t*> components = RM.model(RM.selectedEntity())->components();

		if (ImGui::CollapsingHeader("Meshes")) {
			for (int i = 0; i < components.size(); i++) {
				if (ImGui::Selectable(components[i]->mesh.c_str(), selectedMesh == i)) {
					if (selectedMesh == i) {
						selectedMesh = -1;
					}
					else {
						selectedMesh = i;
					}
				}
			}
		}

		if (selectedMesh != -1) {
			ImGui::Separator();
			ImGui::Text(std::string("Mesh: ").append(components[selectedMesh]->mesh).c_str());
			if (ImGui::CollapsingHeader("Mesh Properties")) {
				std::vector<std::string> materialNames = RM.materialNames();
				std::vector<char*> cMaterialNames;
				for (int i = 0; i < materialNames.size(); i++) {
					cMaterialNames.push_back((char*)materialNames[i].c_str());
				}

				std::vector<std::string> shaderNames = RM.shaderNames();
				std::vector<char*> cShaderNames;
				for (int i = 0; i < shaderNames.size(); i++) {
					cShaderNames.push_back((char*)shaderNames[i].c_str());
				}

				std::vector<std::string> textureNames = RM.textureNames();
				std::vector<char*> cTextureNames;
				for (int i = 0; i < textureNames.size(); i++) {
					cTextureNames.push_back((char*)textureNames[i].c_str());
				}

				static int currentMaterial;
				static int currentShader;
				static int currentTexture;

				currentMaterial = find(components[selectedMesh]->material, materialNames);
				currentShader = find(components[selectedMesh]->shader, shaderNames);
				currentTexture = find(components[selectedMesh]->texture, textureNames);

				char** CArrayMaterial = cMaterialNames.data();
				char** CArrayShader = cShaderNames.data();
				char** CArrayTexture = cTextureNames.data();

				size_t materialArraySize = materialNames.size();
				size_t shaderArraySize = shaderNames.size();
				size_t textureArraySize = textureNames.size();

				ImGui::Text("Material");
				ImGui::SameLine();
				ImGui::Combo("###MaterialDropdown", &currentMaterial, CArrayMaterial, materialArraySize);

				ImGui::Text("Shader");
				ImGui::SameLine();
				ImGui::Combo("###ShaderDropdown", &currentShader, CArrayShader, shaderArraySize);

				ImGui::Text("Texture");
				ImGui::SameLine();
				ImGui::Combo("###TextureDropdown", &currentTexture, CArrayTexture, textureArraySize);

				components[selectedMesh]->material = materialNames[currentMaterial];
				components[selectedMesh]->shader = shaderNames[currentShader];
				components[selectedMesh]->texture = textureNames[currentTexture];

				/*
				if (ImGui::TreeNode("Material")) {
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Shader")) {
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Texture")) {
					ImGui::TreePop();
				}*/
			}

		}
	}

	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

	if (firstDraw) {
		ImGui::SetWindowSize(ImVec2(250, window.height() - this->menuBarSize.y));
		firstDraw = false;
	}
	
	if (updateResolution) {
		ImGui::SetWindowSize(ImVec2(ImGui::GetWindowWidth(), window.height() - this->menuBarSize.y));
	}

	this->leftColumnSize = ImGui::GetWindowSize();

	// this->renderer->setHighlightedEntity(selected);
	
	
	ImGui::SetWindowPos(ImVec2(0, this->menuBarSize.y));

	static ImGuiStyle& leftColumnStyle = ImGui::GetStyle();

	leftColumnStyle.WindowRounding = 0;
	leftColumnStyle.WindowBorderSize = 0;

	ImGui::PopStyleColor();

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
	static int item_current = 0;
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

		tmp = window.fullscreen();
		if (ImGui::MenuItem("Fullscreen", NULL, &tmp));
		window.fullscreen(tmp);

		tmp = RM.depth();
		if (ImGui::MenuItem("Depth Buffer", NULL, &tmp));
		RM.depth(tmp);

		item_current = log2(RM.samples());

		const char* items[] = {"1", "2", "4", "8", "16", "32"};
		
		ImGui::Text("MSAA");
		ImGui::SameLine();
		ImGui::Combo("###MSAADropdown", &item_current, items, IM_ARRAYSIZE(items));

		RM.samples((int)pow(2, item_current));
	}

	// if (ImGui::CollapsingHeader("Bounding Box Display")) {
	// 	if (ImGui::MenuItem("Object Bounding Box", NULL, &drawOBB));
	// 	if (ImGui::MenuItem("External Axis Aligned Bounding Box", NULL, &drawAABB1));
	// 	if (ImGui::MenuItem("Internal Axis Aligned Bounding Box", NULL, &drawAABB2));
	// 	if (ImGui::MenuItem("Average Axis Aligned Bounding Box", NULL, &drawAABB3));
	// 	if (ImGui::MenuItem("True Axis Aligned Bounding Box", NULL, &drawAABB4));
	// 	if (ImGui::MenuItem("Internal Bounding Sphere", NULL, &drawBS));
	// 	if (ImGui::MenuItem("External Bounding Sphere", NULL, &drawBS2));
	// 	if (ImGui::MenuItem("True Bounding Sphere", NULL, &drawBS3));
	// }

	if (ImGui::CollapsingHeader("Post Processing Effect")) {
		static int selectedEffect = 0;

		const char* items[] = {"None", "Inverted Colors", "Color Filter", "Black Circle (View)", "Black Circle (screen)", "Black Fade (view)",
							   "Black Fade (screen)", "Fish Eye", "Barrel Distortion", "Kernel Convolution"};

		ImGui::Text("Effect");
		ImGui::SameLine();
		ImGui::Combo("###PostProcessDropdown", &selectedEffect, items, IM_ARRAYSIZE(items));

		this->renderer->setPostProcessingEffect(selectedEffect);

		ImGui::Separator();

		if (selectedEffect == 2) {
			static float color[3] = { 1.0, 1.0, 1.0 };
			ImGui::ColorEdit3("Color", color);

			this->renderer->setFilterColor(color[0], color[1], color[2]);
		}

		if (selectedEffect == 9) {
			const char* kernels[] = { "Gaussian Blur", "Box Blur", "Edge Detection", "Sharpening", "Emboss", "Horizontal", "Vertical",
									  "Diagonal SX", "Diagonal DX", "Custom" };

			static int selectedKernel = 0;
			ImGui::Text("Kernel");
			ImGui::SameLine();
			ImGui::Combo("###KernelDropdown", &selectedKernel, kernels, IM_ARRAYSIZE(kernels));

			
			//this->renderer->setKernelConvolutionMode(selectedKernel);
			if (selectedKernel == 2) {
				this->renderer->Kernels->setEdgeDetectionKernel();
				ImGui::SameLine();
				this->HelpMarker("|-1|-1|-1|\n|-1| 8|-1|\n|-1|-1|-1|");
			}
			else if (selectedKernel == 3) {
				this->renderer->Kernels->setSharpeningKernel();
				ImGui::SameLine();
				this->HelpMarker("| 0|-1| 0|\n|-1| 5|-1|\n| 0|-1| 0|");
			}
			else if (selectedKernel == 4) {
				this->renderer->Kernels->setEmbossKernel();
				ImGui::SameLine();
				this->HelpMarker("|-2|-1| 0|\n|-1| 1| 1|\n| 0| 1| 2|");
			}
			else if (selectedKernel == 5) {
				this->renderer->Kernels->setHorizontalKernel();
				ImGui::SameLine();
				this->HelpMarker("|-1|-1|-1|\n| 2| 2| 2|\n|-1|-1|-1|");
			}
			else if (selectedKernel == 6) {
				this->renderer->Kernels->setVerticalKernel();
				ImGui::SameLine();
				this->HelpMarker("|-1| 2|-1|\n|-1| 2|-1|\n|-1| 2|-1|");
			}
			else if (selectedKernel == 7) {
				this->renderer->Kernels->setDiagonalSXKernel();
				ImGui::SameLine();
				this->HelpMarker("| 2|-1|-1|\n|-1| 2|-1|\n|-1|-1| 2|");
			}
			else if (selectedKernel == 8) {
				this->renderer->Kernels->setDiagonalDXKernel();
				ImGui::SameLine();
				this->HelpMarker("|-1|-1| 2|\n|-1| 2|-1|\n| 2|-1|-1|");
			}

			ImGui::Separator();

			if (selectedKernel == 0 || selectedKernel == 1) {
				static int kernelSize = 3;
				ImGui::InputInt("Kernel Size", &kernelSize);
				if (kernelSize < 1) {
					kernelSize = 1;
				}
				else if (kernelSize > 21) {
					kernelSize = 21;
				}

				if (selectedKernel == 0) {
					static float blurStrength = 3;
					ImGui::InputFloat("Blur Strength", &blurStrength);
					this->renderer->Kernels->setGaussianKernel(blurStrength, kernelSize);
				}
				else {
					this->renderer->Kernels->setBoxBlurKernel(kernelSize);
				}
			}

			if (selectedKernel == 9) {
				static float a = 0;
				static float b = 0;
				static float c = 0;
				static float d = 0;
				static float e = 1;
				static float f = 0;
				static float g = 0;
				static float h = 0;
				static float i = 0;

				ImGui::PushItemWidth((ImGui::GetWindowSize().x - 30) / 3);
				ImGui::DragFloat("###A", &a, 0.005f);
				ImGui::SameLine();
				ImGui::DragFloat("###B", &b, 0.005f);
				ImGui::SameLine();
				ImGui::DragFloat("###C", &c, 0.005f);

				ImGui::DragFloat("###D", &d, 0.005f);
				ImGui::SameLine();
				ImGui::DragFloat("###E", &e, 0.005f);
				ImGui::SameLine();
				ImGui::DragFloat("###F", &f, 0.005f);

				ImGui::DragFloat("###G", &g, 0.005f);
				ImGui::SameLine();
				ImGui::DragFloat("###H", &h, 0.005f);
				ImGui::SameLine();
				ImGui::DragFloat("###I", &i, 0.005f);

				this->renderer->Kernels->setCustomKernel(a, b, c, d, e, f, g, h, i);
			}
		}
	}

	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

	if (firstDraw) {
		ImGui::SetWindowSize(ImVec2(250, window.height() - this->menuBarSize.y));
		firstDraw = false;
	}

	if (updateResolution) {
		ImGui::SetWindowSize(ImVec2(ImGui::GetWindowWidth(), window.height() - this->menuBarSize.y));
	}

	ImGui::SetWindowPos(ImVec2(window.width() - ImGui::GetWindowWidth(), this->menuBarSize.y));
	this->rightColumnSize = ImGui::GetWindowSize();

	static ImGuiStyle& rightColumnStyle = ImGui::GetStyle();

	rightColumnStyle.WindowRounding = 0;
	rightColumnStyle.WindowBorderSize = 0;

	ImGui::PopStyleColor();

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

		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)) {
			if (ImGui::BeginTabItem("Textures")) {
				float imageWidth = (float)window.width() / (float)window.height() * height;
				float imageHeight = (float)height;

				ImGui::BeginChild("OutlineMask", ImVec2((float)window.width() / (float)window.height() * height, 0));
				this->drawImage(this->renderer->getOutlineMaskTexture(), imageWidth, imageHeight);
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild("Depth", ImVec2((float)window.width() / (float)window.height() * height, 0));
				this->drawImage(this->renderer->getDepthBufferTexture(), imageWidth, imageHeight);
				ImGui::EndChild();

				std::vector<std::string> textureNames = RM.textureNames();

				for (int i = 0; i < textureNames.size(); i++) {
					if (RM.texture(textureNames[i])->type() == GL_TEXTURE_2D) {
						ImGui::SameLine();
						ImGui::BeginChild(textureNames[i].c_str(), ImVec2((float)window.width() / (float)window.height() * height, 0));
						this->drawImage(RM.texture(textureNames[i])->id(), imageWidth, imageHeight);
						ImGui::EndChild();
					}			
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Materials")) {
				ImGui::Separator();

				std::vector<std::string> materialNames = RM.materialNames();
				std::vector<char*> cMaterialNames;
				for (int i = 0; i < materialNames.size(); i++) {
					cMaterialNames.push_back((char*)materialNames[i].c_str());
				}

				static int currentMaterial = 0;
				char** Carray = cMaterialNames.data();

				size_t arraySize = materialNames.size();

				// currentMaterial = find(RM.material(RM.drawingEntity(RM.selectedEntity())->material())->shader(), materialNames);

				ImGui::Text("Material");
				ImGui::SameLine();
				ImGui::Combo("###MaterialDropdown", &currentMaterial, Carray, arraySize);

				float shininess = RM.material(materialNames[currentMaterial])->shininess();
				ImGui::DragFloat("Shininess", &shininess, 0.005f);
				RM.material(materialNames[currentMaterial])->shininess(shininess);


				static float ambient[3] = {1.0, 1.0, 1.0};

				ambient[0] = RM.material(materialNames[currentMaterial])->ambient().x;
				ambient[1] = RM.material(materialNames[currentMaterial])->ambient().y;
				ambient[2] = RM.material(materialNames[currentMaterial])->ambient().z;

				ImGui::ColorEdit3("Ambient", ambient);

				RM.material(materialNames[currentMaterial])->ambient(glm::vec3(ambient[0], ambient[1], ambient[2]));


				static float diffuse[3] = {1.0, 1.0, 1.0};

				diffuse[0] = RM.material(materialNames[currentMaterial])->diffuse().x;
				diffuse[1] = RM.material(materialNames[currentMaterial])->diffuse().y;
				diffuse[2] = RM.material(materialNames[currentMaterial])->diffuse().z;

				ImGui::ColorEdit3("Diffuse", diffuse);

				RM.material(materialNames[currentMaterial])->diffuse(glm::vec3(diffuse[0], diffuse[1], diffuse[2]));


				static float specular[3] = {1.0, 1.0, 1.0};

				specular[0] = RM.material(materialNames[currentMaterial])->specular().x;
				specular[1] = RM.material(materialNames[currentMaterial])->specular().y;
				specular[2] = RM.material(materialNames[currentMaterial])->specular().z;

				ImGui::ColorEdit3("Specular", specular);

				RM.material(materialNames[currentMaterial])->specular(glm::vec3(specular[0], specular[1], specular[2]));


				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Cucumber"))
			{
				ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		

		

		// ImGui::BeginChild("Texture", ImVec2((float)window.width() / (float)window.height() * height, 0));
		// this->drawImage(entityBuffer[3]->getTexture(), imageWidth, imageHeight);
		// ImGui::EndChild();
	}

	if (firstDraw) {
		ImGui::SetWindowSize(ImVec2(window.width() - 500, 220));
		firstDraw = false;
	}
	else {
		float offset = 0;

		if (this->showLeftColumn) {
			offset += this->leftColumnSize.x;
		}

		if (this->showRightColumn) {
			offset += this->rightColumnSize.x;
		}

		ImGui::SetWindowSize(ImVec2(window.width() - offset, ImGui::GetWindowSize().y));
	}
	
	ImVec2 size = ImGui::GetWindowSize();

	if (this->showLeftColumn) {
		ImGui::SetWindowPos(ImVec2(this->leftColumnSize.x, window.height() - size.y));
	}
	else {
		ImGui::SetWindowPos(ImVec2(0, window.height() - size.y));
	}

	
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
			fps[values_offset] = 1.0f / this->fpsTime;
			frameTime[values_offset] = this->fpsTime;
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
			ImGui::SetWindowPos(ImVec2(window.width() - ImGui::GetWindowSize().x - this->rightColumnSize.x, 0 + this->menuBarSize.y));
		}
		else {
			ImGui::SetWindowPos(ImVec2(window.width() - ImGui::GetWindowSize().x, 0 + this->menuBarSize.y));
		}
		

		static ImGuiStyle& style = ImGui::GetStyle();

		style.WindowRounding = 0;
		style.WindowBorderSize = 0;

		ImGui::End();
	}
}

void UI::drawMenuBar() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) { /*
			if (ImGui::MenuItem("Open File")) {
				char filename[1024];
				FILE* f = _popen("zenity --file-selection", "r");
				printf("%s\n", fgets(filename, 1024, f));
				loadEntity(&entityBuffer, filename);
			} */

			if (ImGui::MenuItem("Close", "ALT + F4")) {
				glfwSetWindowShouldClose(window.window(), GL_TRUE);
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")) {

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			ImGui::MenuItem("FPS", NULL, &this->showFPS);
			ImGui::MenuItem("Left Column", NULL, &this->showLeftColumn);
			ImGui::MenuItem("Right Column", NULL, &this->showRightColumn);
			ImGui::MenuItem("Bottom Row", NULL, &this->showBottomRow);

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

void UI::drawCrosshair() {
	// TO IMPLEMENT
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

	this->drawCrosshair();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// // just calls all the other methods, this method is public
void UI::drawInfo() {
	static double tmpTime;
	this->fpsTime = glfwGetTime() - tmpTime;
	tmpTime = glfwGetTime();

	if (displayInfo) {
		this->drawImGui();
	}

	if (updated) {
		updateResolution = false;
	}
	
	updated = false;
}

