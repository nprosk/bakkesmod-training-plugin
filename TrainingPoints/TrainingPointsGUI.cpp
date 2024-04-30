#include "pch.h"
#include "TrainingPoints.h"

/* Plugin Settings Window code here
std::string TrainingPoints::GetPluginName() {
	return "TrainingPoints";
}

void TrainingPoints::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Render the plugin settings here
// This will show up in bakkesmod when the plugin is loaded at
//  f2 -> plugins -> TrainingPoints
void TrainingPoints::RenderSettings() {
	ImGui::TextUnformatted("TrainingPoints plugin settings");
}
*/

/*
// Do ImGui rendering here
void TrainingPoints::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

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
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool TrainingPoints::IsActiveOverlay()
{
	return true;
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
*/
