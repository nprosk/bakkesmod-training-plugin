#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "PersistentStorage.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class TrainingPoints: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow//, public BakkesMod::Plugin::PluginWindow
{
	//constants
	int secondsToUpdate = 5;
	Vector2 canvas_size = { 1920, 1080 };
	std::shared_ptr<PersistentStorage> persistent_storage_;
	bool matchmakingStarted = false;
	int sessionPoints, sessionWins, sessionGames, currentWinstreak = 0;
	int casualGamesLeft = 5;
	// int currentWinstreak

	//Boilerplate
	virtual void onLoad();
	virtual void onUnload();
	
	// updates points with point rate when in training
	void updatePoints();
	// modifies points and session points by given amount
	void addPoints(int difference);
	// removes points with ranked game cost
	void RemovePoints();

	// checks if user is allowed to do this matchmaking
	void CheckValidMatchmaking();

	// Inherited via PluginSettingsWindow
	void RenderSettings() override;
	std::string GetPluginName() override;
	virtual void SetImGuiContext(uintptr_t ctx) override;

	// helpers for plugin settings
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

	// render to canvas
	void Render(CanvasWrapper canvas);

	// helpers for rendering to canvas
	void BlackBackground(CanvasWrapper* canvas);
	void TotalPointsText(CanvasWrapper* canvas);
	void SessionPointsText(CanvasWrapper* canvas);
};

