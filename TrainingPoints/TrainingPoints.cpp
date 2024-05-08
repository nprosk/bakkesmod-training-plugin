#include "pch.h"
#include "TrainingPoints.h"

BAKKESMOD_PLUGIN(TrainingPoints, "TrainingPoints", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void TrainingPoints::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("Plugin loaded!");

	persistent_storage_ = std::make_shared<PersistentStorage>(this, "TrainingPointsStorage", true, true);

	// persistent variables
	auto point_rate = persistent_storage_->RegisterPersistentCvar("point_rate", "0", "How many points per time interval", true, true, 0);
	auto points = persistent_storage_->RegisterPersistentCvar("points", "0", "How many points you have", true, true, 0);
	auto points_window_enabled = persistent_storage_->RegisterPersistentCvar("points_window_enabled", "1", "Whether or not the mod is enabled", true, true, 0, true, 1);
	auto ranked_game_cost = persistent_storage_->RegisterPersistentCvar("ranked_game_cost", "2000", "the point cost of queueing a ranked game", true);
	auto casual_game_quota = persistent_storage_->RegisterPersistentCvar("casual_game_quota", "5", "How many casual games you can play per session", true, true, 0);

	// initialize per session variables
	sessionPoints = 0;
	sessionWins = 0;
	sessionGames = 0;
	currentWinstreak = 0;
	CVarWrapper casualGameQuota = cvarManager->getCvar("casual_game_quota");
	casualGamesLeft = casualGameQuota.getIntValue();

	matchmakingStarted = false;

	// start rendering window
	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
		Render(canvas);
	});

	// start point updating loop
	updatePoints();

	gameWrapper->HookEventPost("Function TAGame.GFxData_Matchmaking_TA.StartMatchmaking", std::bind(&TrainingPoints::CheckValidMatchmaking, this));
	gameWrapper->HookEventPost("Function GameEvent_Soccar_TA.Active.StartRound", std::bind(&TrainingPoints::RemovePoints, this));


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
	// gameWrapper->HookEventWithCallerPost<ActorWrapper>("Function TAGame.GFxData_Matchmaking_TA.StartMatchmaking", std::bind(&TrainingPoints::FUNCTION, this, _1, _2, _3));
	// gameWrapper->HookEventWithCallerPost<MatchmakingWrapper>("Function TAGame.GFxData_Matchmaking_TA.StartMatchmaking",
	// 	[this](MatchmakingWrapper caller, void* params, std::string eventname) {
	// 		CheckValidMatchmaking(caller);
	// 	});


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
		CVarWrapper pointRateCvar = cvarManager->getCvar("point_rate");
		addPoints(pointRateCvar.getIntValue());
	}
	gameWrapper->SetTimeout(std::bind(&TrainingPoints::updatePoints, this), secondsToUpdate);
}

void TrainingPoints::addPoints(int difference) {
	CVarWrapper pointsCvar = cvarManager->getCvar("points");
	pointsCvar.setValue(pointsCvar.getIntValue() + difference);
	sessionPoints += difference;
}

void TrainingPoints::CheckValidMatchmaking() {
	MatchmakingWrapper caller = gameWrapper->GetMatchmakingWrapper();
	if (!caller) return;

	int viewTab = caller.GetActiveViewTab();
	LOG(std::to_string(viewTab));
	//cas standard 7
	if (viewTab == 0) {
		if (casualGamesLeft > 0) {
			matchmakingStarted = true;
			return;
		}
	}
	else if (viewTab == 1) {
		CVarWrapper pointsCvar = cvarManager->getCvar("points");
		CVarWrapper rankedGameCostCvar = cvarManager->getCvar("ranked_game_cost");
		if (pointsCvar.getIntValue() >= rankedGameCostCvar.getIntValue()) {
			matchmakingStarted = true;
			return;
		}
	}
	else {
		matchmakingStarted = true;
		return;
	}

	if (caller.IsSearching()) {
		caller.CancelMatchmaking();
	}
}

void TrainingPoints::RemovePoints() {
	if (!gameWrapper->IsInOnlineGame()) {
		return;
	}

	ServerWrapper sw = gameWrapper->GetCurrentGameState();
	if (!sw) return;
	GameSettingPlaylistWrapper playlist = sw.GetPlaylist();
	if (!playlist) return;
	int playlistID = playlist.GetPlaylistId();

	if (matchmakingStarted) {
		if (playlistID < 5) {
			casualGamesLeft--;
		}
		else if (playlistID > 9 && playlistID < 14) {
			CVarWrapper rankedGameCostCvar = cvarManager->getCvar("ranked_game_cost");
			addPoints(-rankedGameCostCvar.getIntValue());
		}
	}

	matchmakingStarted = false;
}

/*
void TrainingPoints::enableIncrementPoints() {
	incrementPoints_ = true;
}

void TrainingPoints::disableIncrementPoints() {
	incrementPoints_ = false;
}
*/