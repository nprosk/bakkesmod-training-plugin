#include "pch.h"
#include "TrainingPoints.h"
 
void TrainingPoints::Render(CanvasWrapper canvas) {
	CVarWrapper enabledCvar = cvarManager->getCvar("points_window_enabled");
	if (!enabledCvar.getBoolValue()) {
		return;
	}

	canvas_size = gameWrapper->GetScreenSize();

	BlackBackground(&canvas);
	TotalPointsText(&canvas);
}

void TrainingPoints::BlackBackground(CanvasWrapper* canvas) {
	canvas->SetPosition(Vector2{ canvas_size.X - 170, 20 });
	LinearColor colors;
	colors.R = 50;
	colors.G = 50;
	colors.B = 50;
	colors.A = 200;
	canvas->SetColor(colors);
	Vector2 size = { 150, 100 };

	canvas->FillBox(size);
}

void TrainingPoints::TotalPointsText(CanvasWrapper* canvas) {
	canvas->SetPosition(Vector2{ canvas_size.X - 170, 20 });
	// defines colors in RGBA 0-255
	LinearColor colors;
	colors.A = 255;

	CVarWrapper pointsCvar = cvarManager->getCvar("points");
	float points = pointsCvar.getFloatValue();
	if (points < 500) {
		colors.R = 255;
		colors.G = 0;
		colors.B = 0;
	}
	else if (points < 1000) {
		colors.R = 255;
		colors.G = 255;
		colors.B = 0;
	}
	else {
		colors.R = 0;
		colors.G = 255;
		colors.B = 0;
	}

	canvas->SetColor(colors);
	// draws from the last set position
	// the two floats are text x and y scale
	// the false turns off the drop shadow
	canvas->DrawString("Points: " + pointsCvar.getStringValue(), 1.5, 1.5, false);
}

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

void TrainingPoints::ToggleWindow() {
	cvarManager->executeCommand("togglemenu " + GetMenuName());
}
*/

