#pragma once
#include "gui.hpp"
#include <format>
#include <string>
#include <functional>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

namespace gui {
	namespace math {
		float colorToFloat(const int& colorCode);
		ImVec4 RGBAToImVec4(const float& R, const float& G, const float& B, const float& A);
		void setCursorPosition(const float& x = 0.0f, const float& y = 0.0f);
		void setCursorCurrentPosition(const float& x = 0.0f, const float& y = 0.0f);
	}
}

namespace gui {
	namespace components {

		enum class FontSize : int {
			SMALL, LARGE, XLARGE
		};

		bool Button(const char* label, const ImVec4& color = { 0.f, 140.f , 3.f , 255.f });
		void TextInputAndLabel(const char* label, const char* placeHolder, char* buffer, const int& bufferSize, const bool& isInvalid = true, const bool& readOnly = false);
		void Label(const char* label);
		void Text(const char* label, const FontSize& fontSize = FontSize::SMALL, const bool& bold = false);
	}
}