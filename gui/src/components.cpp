#include "components.hpp"
#include <unordered_map>
#include "fonts.hpp"

namespace {
	constexpr float RGB_THRESHOLD = 255.0f;
}

namespace {
	std::unordered_map<std::string, bool> Variable_Bool_Map;
	bool draggingWindow = false;
}

bool gui::components::Button(const char* label, const ImVec4& color)
{
	bool isClicked {false};
	ImVec4 floatCode = gui::math::RGBAToImVec4(color.x, color.y, color.z, color.w);

	ImVec4 onHoverColor{ 
		std::abs(floatCode.x >= gui::math::colorToFloat(150) ? floatCode.x - gui::math::colorToFloat(50) : floatCode.x - gui::math::colorToFloat(20)),
		std::abs(floatCode.y >= gui::math::colorToFloat(150) ? floatCode.y - gui::math::colorToFloat(50) : floatCode.y - gui::math::colorToFloat(20)),
		std::abs(floatCode.z >= gui::math::colorToFloat(150) ? floatCode.z - gui::math::colorToFloat(50) : floatCode.z - gui::math::colorToFloat(20)),
		floatCode.w };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ floatCode.x,floatCode.y,floatCode.z,floatCode.w});
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, onHoverColor);
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4{ floatCode.x,floatCode.y,floatCode.z, (floatCode.w == 0 ? floatCode.w = 1.f : floatCode.w) });
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.5f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.f, 10.f));

	if (ImGui::Button(label)) {
		isClicked = true;
	}
	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar(2);

	return isClicked;
}

void gui::components::TextInputAndLabel(const char* label, const char* placeHolder, char* buffer, const int& bufferSize, const bool& isInvalid, const bool& readOnly)
{
	bool isActive = Variable_Bool_Map[label];

	if (isActive) {
		ImGui::PushStyleColor(ImGuiCol_Border, gui::math::RGBAToImVec4(0, 140, 3, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.5f);
	}

	if (isInvalid) {
		ImGui::PushStyleColor(ImGuiCol_Border, gui::math::RGBAToImVec4(0, 140, 3, 255));
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Border, gui::math::RGBAToImVec4(140, 0, 3, 255));
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.f, 10.f));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, gui::math::RGBAToImVec4(26, 28, 43, 255));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.f, 10.f));
	ImGui::BeginGroup();
	ImGui::PushFont(fonts::Roboto_Regular_XLarge);

	gui::components::Label(label);
	ImGui::PopFont();

	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	ImGui::InputTextWithHint(std::string("##" + std::string(label)).c_str(), placeHolder, buffer, bufferSize, readOnly ? ImGuiInputTextFlags_ReadOnly : ImGuiInputTextFlags_None);

	ImGui::EndGroup();
	ImGui::PopStyleColor(2);
	ImGui::PopStyleVar(2);


	if (isActive) {
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	Variable_Bool_Map[label] = ImGui::IsItemActive();
}

void gui::components::Label(const char* label)
{
	ImGui::PushFont(fonts::Roboto_Bold_Large);
	ImGui::TextColored(gui::math::RGBAToImVec4(255, 255, 255, 150), label);
	ImGui::PopFont();

}

void gui::components::Text(const char* label, const FontSize& fontSize, const bool& bold)
{
	if (!bold) {
		switch (fontSize) {
		case FontSize::SMALL:
			ImGui::PushFont(fonts::Roboto_Regular_Small);
			break;
		case FontSize::LARGE:
			ImGui::PushFont(fonts::Roboto_Regular_Large);
			break;
		case FontSize::XLARGE:
			ImGui::PushFont(fonts::Roboto_Regular_XLarge);
			break;
		}
	}
	else {
		switch (fontSize) {
		case FontSize::SMALL:
			ImGui::PushFont(fonts::Roboto_Bold_Small);
			break;						  
		case FontSize::LARGE:
			ImGui::PushFont(fonts::Roboto_Bold_Large);
			break;						  
		case FontSize::XLARGE:
			ImGui::PushFont(fonts::Roboto_Bold_XLarge);
			break;
		}
	}

	ImGui::Text(label);
	ImGui::PopFont();
}


//=================== MATH ======================

inline float gui::math::colorToFloat(const int& colorCode)
{
	return static_cast<float>(colorCode / RGB_THRESHOLD);
}

ImVec4 gui::math::RGBAToImVec4(const float& R, const float& G, const float& B, const float& A)
{
	return ImVec4(R / RGB_THRESHOLD, G / RGB_THRESHOLD, B / RGB_THRESHOLD, A /RGB_THRESHOLD);
}

void gui::math::setCursorPosition(const float& x, const float& y)
{
	float xPos = ImGui::GetContentRegionAvail().x + x;
	float yPos = ImGui::GetContentRegionAvail().y + y;
	ImGui::SetCursorPos(ImVec2(xPos, yPos));
}

void gui::math::setCursorCurrentPosition(const float& x, const float& y)
{
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + x, ImGui::GetCursorPosY() + y));
}
