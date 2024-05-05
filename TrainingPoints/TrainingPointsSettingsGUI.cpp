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
	CVarWrapper pointsCvar = cvarManager->getCvar("points");
	ImGui::TextUnformatted(("Points: " + pointsCvar.getStringValue()).c_str());
	ImGui::Separator();
	RenderSettingsSettings();
	ImGui::Separator();
	RenderSettingsCasual();
	ImGui::Separator();
	RenderSettingsCompetitive();
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void TrainingPoints::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void TrainingPoints::RenderSettingsCasual() {
	ImGui::TextUnformatted("Queue Casual");
	if (ImGui::Button("Standard")) {
		CVarWrapper pointsCvar = cvarManager->getCvar("points");
		if (pointsCvar.getIntValue() >= ranked_game_cost) {
			pointsCvar.setValue(pointsCvar.getIntValue() - ranked_game_cost);
			StartMatchmaking(Playlist::CASUAL_STANDARD, PlaylistCategory::CASUAL);
		}
	}
	
}

void TrainingPoints::RenderSettingsCompetitive() {
	ImGui::TextUnformatted("Queue Competitive");
	if (ImGui::Button("Standard")) {

	}
	
}

void TrainingPoints::RenderSettingsSettings() {
	ImGui::TextUnformatted("Settings");

	CVarWrapper rateCvar = cvarManager->getCvar("point_rate");
	if (!rateCvar) { return; }
	int rate = rateCvar.getIntValue();
	if (ImGui::SliderInt("Rate", &rate, 0.0, 40.0)) {
		rateCvar.setValue(rate);
	}
	if (ImGui::IsItemHovered()) {
		std::string hoverText = "rate is " + std::to_string(rate) + " points per 5 seconds";
		ImGui::SetTooltip(hoverText.c_str());
	}


	float mins_per_ranked_game = (ranked_game_cost * secondsToUpdate / (rateCvar.getFloatValue() * 60.0));
	std::string time_str = "It takes " + std::to_string(mins_per_ranked_game) + " minutes to get enough points to queue a ranked game";
	ImGui::TextUnformatted(time_str.c_str());

	CVarWrapper enabledCvar = cvarManager->getCvar("points_window_enabled");
	bool check = enabledCvar.getBoolValue();
	if (ImGui::Checkbox("Enable window that shows points", &check)) {
		enabledCvar.setValue(check);
	}
}