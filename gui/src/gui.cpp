#include "gui.hpp"
#include <format>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "components.hpp"
#include "contact.hpp"

namespace fonts {
	ImFont* Roboto_Regular_Small;
	ImFont* Roboto_Regular_Large;
	ImFont* Roboto_Regular_XLarge;
	ImFont* Roboto_Bold_small;
	ImFont* Roboto_Bold_Small;
	ImFont* Roboto_Bold_Large;
	ImFont* Roboto_Bold_XLarge;
}


static void glfwError(int error, const char* description) {
	std::cerr << std::format("[GLFW]-[CODE: {}]: {}", error, description);
}

gui::Gui::Gui(const char* applicationName, const int& width, const int& height, const core::PhoneBook& phoneBook) 
	: m_applicationName(applicationName), m_width(width), m_height(height), m_phoneBook(phoneBook)
{
	init();
}

gui::Gui::~Gui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void gui::Gui::init()
{
	//GLFW initialization
	
	glfwSetErrorCallback(glfwError);
	if (!glfwInit())
		throw std::runtime_error("[GLFW]-[ERROR]: GLFW isn't initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	float mainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());

	m_window = glfwCreateWindow(static_cast<int>(m_width), static_cast<int>(m_height),m_applicationName, NULL, NULL);

	if (!m_window)
		throw std::runtime_error("[GLFW]-[ERROR]: Failed to create window");

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	// ImGui initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	std::string fontPathRobotoRegular = std::format("{}/assets/fonts/Roboto-Regular.ttf", SOURCE_DIR);
	std::string fontPathRobotoBold = std::format("{}/assets/fonts/Roboto-Bold.ttf", SOURCE_DIR);

	//Fonts
	fonts::Roboto_Regular_Small = io.Fonts->AddFontFromFileTTF(fontPathRobotoRegular.c_str(), 16.0f);
	fonts::Roboto_Regular_Large = io.Fonts->AddFontFromFileTTF(fontPathRobotoRegular.c_str(), 20.0f);
	fonts::Roboto_Regular_XLarge = io.Fonts->AddFontFromFileTTF(fontPathRobotoRegular.c_str(), 24.0f);
	fonts::Roboto_Bold_Small = io.Fonts->AddFontFromFileTTF(fontPathRobotoBold.c_str(), 16.0f);
	fonts::Roboto_Bold_Large = io.Fonts->AddFontFromFileTTF(fontPathRobotoBold.c_str(), 20.0f);
	fonts::Roboto_Bold_XLarge = io.Fonts->AddFontFromFileTTF(fontPathRobotoBold.c_str(), 24.0f);

	ImGui::StyleColorsDark();												//Set default components' color

	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameRounding = 4.0f;												// For Components Frames Button, Input
	style.WindowRounding = 8.0f;											//Application Frame

	const char* glsl_version = "#version 130";
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void gui::Gui::run()
{
	while (!glfwWindowShouldClose(m_window)) {						// Main Loop that keeps the application running
		glfwPollEvents();

		if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0) {	 // Stop rendering when the window is minimized
			ImGui_ImplGlfw_Sleep(10);
			continue;
		}
		renderFrame();
	}
}

void gui::Gui::renderFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// ImGui Window styling
	ImGuiWindowFlags flags{
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus };

	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
	ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->WorkSize.x, ImGui::GetMainViewport()->WorkSize.y));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.01f, 0.02f, 0.07f, 1.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 8.0f);
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, gui::math::colorToFloat(140), gui::math::colorToFloat(3), 1.f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20.0f, 30.0f));

	// Rendering UI
	ImGui::Begin(m_applicationName, nullptr, flags);				// Start rendering the UI components

	ImGui::PopStyleVar(3);
	ImGui::PopStyleColor(2);

	renderUI();

	ImGui::End();
	ImGui::Render();

	int displayWidth{};
	int displayHeight{};
	glfwGetFramebufferSize(m_window, &displayWidth, &displayHeight);
	glViewport(0, 0, displayWidth, displayHeight);			//Display everything withing the viewport of the window
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_window);
}

namespace {
	char Variable_Name_Buffer[100] = "";		// Buffer for Name input
	char Variable_Phone_Buffer[20] = "";		// Buffer for phone number input : +921 (234) 234-2345
	char Variable_Search_Buffer[100] = "";		// Buffer for search input
	bool Variable_Send_Button_Clicked = false;
	bool Variable_Is_Name_Valid = true;
	bool Variable_Is_Phone_Number_Valid = true;
	bool Variable_Is_Editing = false;

	constexpr int SMALL_WINDOW = 500;
}

void gui::Gui::renderUI()
{

	gui::components::TextInputAndLabel("Search: ", "Please write the complete name", Variable_Search_Buffer, std::size(Variable_Search_Buffer));

	ImGuiTableFlags contactListFlags =
		ImGuiTableFlags_PadOuterX | ImGuiTableFlags_SizingStretchSame |
		ImGuiTableFlags_Borders   | ImGuiTableFlags_ScrollY	;

	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(16, 24));
	ImGui::BeginTable(
		"Searched Contact",
		1, contactListFlags,
		ImVec2(ImGui::GetContentRegionAvail().x,
		ImGui::GetContentRegionAvail().y - 100));

	// Contact Table
	auto contactList = m_phoneBook.getContactList();
	if (std::strlen(Variable_Search_Buffer) != 0) {

		auto foundContact = m_phoneBook.find(Variable_Search_Buffer);
		ImGui::TableNextColumn();
		if (foundContact) {

			ImGui::TableNextColumn();
			gui::components::Label("Name: ");
			ImGui::SameLine();
			gui::components::Text(foundContact->getName().c_str(), gui::components::FontSize::LARGE);

			if (ImGui::GetContentRegionAvail().x > SMALL_WINDOW * 2.1)
				ImGui::SameLine(ImGui::GetContentRegionAvail().x * 0.2f);
			gui::components::Label("Phone Number: ");
			ImGui::SameLine();
			gui::components::Text(foundContact->getPhoneNumber().c_str(), gui::components::FontSize::LARGE);

			// Remove Button
			if (ImGui::GetContentRegionAvail().x > SMALL_WINDOW)
				ImGui::SameLine(ImGui::GetContentRegionAvail().x + ImGui::GetCursorPosX() - ImGui::GetCursorPosX() * 6);
			if (gui::components::Button(std::string(std::string("Remove ##") + foundContact->getName()).c_str(), ImVec4(140, 0, 3, 255))) {
				m_phoneBook.remove(foundContact->getName());
			}
			// Edit Button
			if (ImGui::GetContentRegionAvail().x > SMALL_WINDOW)
				ImGui::SameLine(ImGui::GetContentRegionAvail().x + ImGui::GetCursorPosX() - ImGui::GetCursorPosX() * 12);
			if (gui::components::Button(std::string(std::string("Edit ##") + foundContact->getName()).c_str(), ImVec4(140, 140, 3, 0))) {
				Variable_Is_Editing = true;
				strcpy(Variable_Name_Buffer, foundContact->getName().c_str());
				strcpy(Variable_Phone_Buffer, foundContact->getPhoneNumber().c_str());
			}
		}
		else {
			gui::components::Text("Not Found");
		}
	}
	else {
		for (const auto& contact : contactList) {

			ImGui::TableNextColumn();
			gui::components::Label("Name: "); ImGui::SameLine(); gui::components::Text(contact->getName().c_str(), gui::components::FontSize::LARGE);

			if (ImGui::GetContentRegionAvail().x > SMALL_WINDOW * 2.1)
				ImGui::SameLine(ImGui::GetContentRegionAvail().x * 0.2f);
			gui::components::Label("Phone Number: "); ImGui::SameLine(); gui::components::Text(contact->getPhoneNumber().c_str(), gui::components::FontSize::LARGE);

			// Remove button
			if(ImGui::GetContentRegionAvail().x > SMALL_WINDOW)
				ImGui::SameLine(ImGui::GetContentRegionAvail().x + ImGui::GetCursorPosX() - ImGui::GetCursorPosX() * 6);
			if (gui::components::Button(std::string(std::string("Remove ##") + contact->getName()).c_str(), ImVec4(140, 0, 3, 255))) {
				m_phoneBook.remove(contact->getName());
			}

			// Edit Button
			if (ImGui::GetContentRegionAvail().x > SMALL_WINDOW)
			ImGui::SameLine(ImGui::GetContentRegionAvail().x + ImGui::GetCursorPosX() - ImGui::GetCursorPosX() * 12);
			if (gui::components::Button(std::string(std::string("Edit ##") + contact->getName()).c_str(), ImVec4(140, 140, 3, 0))) {
				Variable_Is_Editing = true;
				strcpy(Variable_Name_Buffer, contact->getName().c_str());
				strcpy(Variable_Phone_Buffer, contact->getPhoneNumber().c_str());
			}
		}
	}

	ImGui::EndTable();
	ImGui::PopStyleVar(1);


	// Inputs
	ImGuiTableFlags contactInputFlags =
		ImGuiTableFlags_PadOuterX | ImGuiTableFlags_SizingStretchSame;

	ImGui::BeginGroup();
	ImGui::BeginTable("Inputs", ImGui::GetContentRegionAvail().x > SMALL_WINDOW ? 3 : 1, contactInputFlags);

	ImGui::TableNextColumn();
	gui::math::setCursorCurrentPosition(0.0f, 10.f);
	Variable_Is_Name_Valid = std::strlen(Variable_Name_Buffer) < 2 ? false : true;
	gui::components::TextInputAndLabel(
		"Name: ",
		"Example: Donald J. Trump",
		Variable_Name_Buffer,
		std::size(Variable_Name_Buffer),
		Variable_Is_Name_Valid,
		Variable_Is_Editing);

	ImGui::TableNextColumn();
	Variable_Is_Phone_Number_Valid = std::strlen(Variable_Phone_Buffer) < 11 || std::strlen(Variable_Phone_Buffer) > 20 ? false : true;
	gui::components::TextInputAndLabel(
		"Phone Number: ",
		"Example: +1 (234) 345-3467",
		Variable_Phone_Buffer,
		std::size(Variable_Phone_Buffer),
		Variable_Is_Phone_Number_Valid);

	ImGui::TableNextColumn();
	gui::math::setCursorCurrentPosition(0.0f, 34.f);
	if (gui::components::Button(Variable_Is_Editing ? "Edit" : "Submit", Variable_Is_Editing ? ImVec4(140, 140, 3, 0) : ImVec4(0, 140, 3, 255))) {

		if(Variable_Is_Phone_Number_Valid && Variable_Is_Name_Valid) {
			bool isAdded = m_phoneBook.push(Variable_Name_Buffer, Variable_Phone_Buffer);

			if (!isAdded || Variable_Is_Editing) {
				m_phoneBook.update(Variable_Name_Buffer, Variable_Phone_Buffer);
			}

			Variable_Name_Buffer[0] = '\0';
			Variable_Phone_Buffer[0] = '\0';
			Variable_Is_Editing = false;
		}
	}
	ImGui::EndTable();
	ImGui::EndGroup();


}

