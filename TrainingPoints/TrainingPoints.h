#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "PersistentStorage.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class TrainingPoints: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow//, public BakkesMod::Plugin::PluginWindow
{
	std::shared_ptr<PersistentStorage> persistent_storage_;
	//constants
	int ranked_game_cost = 2000;
	int secondsToUpdate = 5;
	Vector2 canvas_size = { 1920, 1080 };
	bool matchmakingStarted = false;

	//Boilerplate
	virtual void onLoad();
	virtual void onUnload();

	// bool incrementPoints_ = false;
	
	void updatePoints();
	void addPoints(int difference);

	void StopMatchmaking();
	void StartMatchmaking(Playlist playlist, PlaylistCategory category);
	void RemovePoints();
	// void enableIncrementPoints();
	// void disableIncrementPoints();

	// Inherited via PluginSettingsWindow
	void RenderSettings() override;
	std::string GetPluginName() override;
	virtual void SetImGuiContext(uintptr_t ctx) override;

	void RenderSettingsCasual();
	void RenderSettingsCompetitive();
	void RenderSettingsSettings();

	// Inherited via PluginWindow
	/*
	bool isWindowOpen_ = true;
	bool isMinimized_ = false;
	std::string menuTitle_ = "TrainingPoints";
	virtual void Render() override;
	virtual std::string GetMenuName() override;
	virtual std::string GetMenuTitle() override;
	
	virtual bool ShouldBlockInput() override;
	virtual bool IsActiveOverlay() override;
	virtual void OnOpen() override;
	virtual void OnClose() override;
	void ToggleWindow();
	*/

	void Render(CanvasWrapper canvas);

	void BlackBackground(CanvasWrapper* canvas);
	void TotalPointsText(CanvasWrapper* canvas);
	void SessionPointsText(CanvasWrapper* canvas);
};

