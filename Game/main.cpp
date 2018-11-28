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
	//GameDataクラスのインスタンスを生成
	GameData* gamedata = new GameData;
	//インスタンスに名前を設定
	gamedata->SetName(L"GameData");
	//PlayerStatusクラスのインスタンスを生成
	PlayerStatus* playerstatus = new PlayerStatus;
	//インスタンスに名前を設定
	playerstatus->SetName(L"PlayerStatus");
	playerstatus->SetGameData(gamedata);
	Town* town = new Town;
	//Title* titel = new Title;
	town->SetPlayerStatus(playerstatus);
	SetPhysicsDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//ゲームループ。
	GetEngine().RunGameLoop();
}

