#pragma once
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "phoneBook.hpp"

namespace gui {

	class Gui {
	public:
		Gui(const char* applicationName, const int& width, const int& height, const core::PhoneBook& phoneBook);
		Gui(const Gui&) = delete;
		Gui(Gui&&) noexcept = delete;
		~Gui();
		void run();
	private:
		void renderFrame();
		void renderUI();
		void init();
	public:
		Gui& operator=(const Gui&) = delete;
		Gui& operator=(Gui&&) noexcept = delete;
	private:
		const char* m_applicationName;
		int m_width;
		int m_height;
		core::PhoneBook m_phoneBook;
		GLFWwindow* m_window;
	};
}