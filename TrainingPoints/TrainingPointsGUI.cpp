#include "pch.h"
#include "TrainingPoints.h"

// Plugin Settings Window code here
std::string TrainingPoints::GetPluginName() {
	return "TrainingPoints";
}

// Render the plugin settings here
// This will show up in bakkesmod when the plugin is loaded at
//  f2 -> plugins -> TrainingPoints
void TrainingPoints::RenderSettings() {
	ImGui::TextUnformatted("TrainingPoints plugin settings");

	CVarWrapper rateCvar = cvarManager->getCvar("point_rate");
	if (!rateCvar) { return; }
	float rate = rateCvar.getFloatValue();
	if (ImGui::SliderFloat("Distance", &rate, 0.0, 40.0)) {
		rateCvar.setValue(rate);
	}
	if (ImGui::IsItemHovered()) {
		std::string hoverText = "rate is " + std::to_string(rate);
		ImGui::SetTooltip(hoverText.c_str());
	}

	CVarWrapper enabledCvar = cvarManager->getCvar("points_window_enabled");
	bool check = enabledCvar.getBoolValue();
	if (ImGui::Checkbox("checkbox", &check)) {
		enabledCvar.setValue(check);
	}
}


// Do ImGui rendering here
void TrainingPoints::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	
	ImGui::TextUnformatted("TrainingPoints plugin settings");

	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

// Name of the menu that is used to toggle the window.
std::string TrainingPoints::GetMenuName()
{
	return "trainingpoints";
}

// Title to give the menu
std::string TrainingPoints::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void TrainingPoints::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool TrainingPoints::ShouldBlockInput()
{
	return false;
}

// Return true if window should be interactive
bool TrainingPoints::IsActiveOverlay()
{
	return false;
}

// Called when window is opened
void TrainingPoints::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void TrainingPoints::OnClose()
{
	isWindowOpen_ = false;
}

// in a .cpp file 
void TrainingPoints::Render(CanvasWrapper canvas) {
	// defines colors in RGBA 0-255
	LinearColor colors;
	colors.R = 255;
	colors.G = 255;
	colors.B = 0;
	colors.A = 255;
	canvas.SetColor(colors);

	// sets position to top left
	// x moves to the right
	// y moves down
	// bottom right would be 1920, 1080 for 1080p monitors
	canvas.SetPosition(Vector2F{ 0.0, 0.0 });

	CVarWrapper pointsCvar = cvarManager->getCvar("points");
	// draws from the last set position
	// the two floats are text x and y scale
	// the false turns off the drop shadow
	canvas.DrawString("Points: " + pointsCvar.getStringValue(), 2.0, 2.0, false);
}