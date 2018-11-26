#include "stdafx.h"
#include "Title.h"
#include "Town.h"
#include "Stage1.h"
#include "PlayerStatus.h"
#include <time.h>
#include "GameData.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned)time(NULL));
	//ゲームの初期化。
	InitEngineParameter initparam; 
	GetEngine().InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game", initparam);	
	GameObj::PerspectiveCamera cam; SetMainCamera(&cam);
	Town* town = new Town;
	PlayerStatus* playerstatus = new PlayerStatus;
	town->SetPlayerStatus(playerstatus);
	GameData* gamedata = new GameData;
	SetPhysicsDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//ゲームループ。
	GetEngine().RunGameLoop();
}

