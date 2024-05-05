#include "pch.h"
#include "TrainingPoints.h"

BAKKESMOD_PLUGIN(TrainingPoints, "TrainingPoints", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void TrainingPoints::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("Plugin loaded!");

	cvarManager->registerNotifier("UpdatePoints", [this](std::vector<std::string> args) {
		updatePoints();
		}, "", PERMISSION_ALL);

	auto point_rate = cvarManager->registerCvar("point_rate", "1", "How many points per time interval", true, true, 0);
	auto points = cvarManager->registerCvar("points", "0", "How many points you have", true, true, 0);
	auto session_points = cvarManager->registerCvar("points", "0", "How many points you have", true, true, 0);
	auto points_window_enabled = cvarManager->registerCvar("points_window_enabled", "1", "Whether or not the mod is enabled", true, true, 0, true, 1);

	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
		Render(canvas);
	});

	// gameWrapper->HookEvent("Function TAGame.GFxData_Training_TA.PlayFreeplayMap", std::bind(&TrainingPoints::enableIncrementPoints, this));
	// gameWrapper->HookEvent("Function TAGame.FreeplayCommands_TA.HandleSoccarGameDestroyed", std::bind(&TrainingPoints::disableIncrementPoints, this));

	updatePoints();

	gameWrapper->HookEventPost("Function TAGame.GFxData_Matchmaking_TA.StartMatchmaking", std::bind(&TrainingPoints::StopMatchmaking, this));
	gameWrapper->HookEvent("Function TAGame.Team_TA.PostBeginPlay", std::bind(&TrainingPoints::RemovePoints, this));

	//cvarManager->registerNotifier("my_aweseome_notifier", [&](std::vector<std::string> args) {
	//	cvarManager->log("Hello notifier!");
	//}, "", 0);

	//auto cvar = cvarManager->registerCvar("template_cvar", "hello-cvar", "just a example of a cvar");
	//auto cvar2 = cvarManager->registerCvar("template_cvar2", "0", "just a example of a cvar with more settings", true, true, -10, true, 10 );

	//cvar.addOnValueChanged([this](std::string cvarName, CVarWrapper newCvar) {
	//	cvarManager->log("the cvar with name: " + cvarName + " changed");
	//	cvarManager->log("the new value is:" + newCvar.getStringValue());
	//});

	// points_window_enabled.addOnValueChanged(std::bind(&TrainingPoints::ToggleWindow, this));

	// enabled decleared in the header

	//cvarManager->registerNotifier("NOTIFIER", [this](std::vector<std::string> params){FUNCTION();}, "DESCRIPTION", PERMISSION_ALL);
	//cvarManager->registerCvar("CVAR", "DEFAULTVALUE", "DESCRIPTION", true, true, MINVAL, true, MAXVAL);//.bindTo(CVARVARIABLE);
	//gameWrapper->HookEvent("FUNCTIONNAME", std::bind(&TEMPLATE::FUNCTION, this));
	//gameWrapper->HookEventWithCallerPost<ActorWrapper>("FUNCTIONNAME", std::bind(&TrainingPoints::FUNCTION, this, _1, _2, _3));


	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", [this](std::string eventName) {
	//	cvarManager->log("Your hook got called and the ball went POOF");
	//});
	// You could also use std::bind here
	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", std::bind(&TrainingPoints::YourPluginMethod, this);
}

void TrainingPoints::onUnload()
{
	cvarManager->log("I was too cool for this world B'(");
}

void TrainingPoints::updatePoints() {
	if (gameWrapper->IsInCustomTraining() || gameWrapper->IsInFreeplay() || gameWrapper->IsInReplay()) {//(incrementPoints_) {
		LOG("Updating Points");
		CVarWrapper pointsCvar = cvarManager->getCvar("points");
		CVarWrapper pointRateCvar = cvarManager->getCvar("point_rate");
		pointsCvar.setValue(pointsCvar.getIntValue() + pointRateCvar.getIntValue());
	}
	gameWrapper->SetTimeout(std::bind(&TrainingPoints::updatePoints, this), secondsToUpdate);
}

void TrainingPoints::StopMatchmaking() {
	CVarWrapper pointsCvar = cvarManager->getCvar("points");
	if (pointsCvar.getIntValue() >= ranked_game_cost) {
		return;
	}

	MatchmakingWrapper mmw = gameWrapper->GetMatchmakingWrapper();
	if (!mmw) {
		return;
	}

	if (mmw.IsSearching()) {
		mmw.CancelMatchmaking();
	}
}

void TrainingPoints::StartMatchmaking(Playlist playlist, PlaylistCategory category) {
	MatchmakingWrapper mmw = gameWrapper->GetMatchmakingWrapper();
	if (!mmw) {
		return;
	}

	mmw.SetViewTab(category);
	mmw.SetPlaylistSelection(playlist, true);
	mmw.StartMatchmaking(category);
}

void TrainingPoints::RemovePoints() {
	CVarWrapper pointsCvar = cvarManager->getCvar("points");
	pointsCvar.setValue(pointsCvar.getIntValue() - ranked_game_cost);
}

/*
void TrainingPoints::enableIncrementPoints() {
	incrementPoints_ = true;
}

void TrainingPoints::disableIncrementPoints() {
	incrementPoints_ = false;
}
*/