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
	GameObj::PerspectiveCamera* cam = new GameObj::PerspectiveCamera;
	SetMainCamera(cam);
	cam->SetName(L"Camera");
	//GameDataクラスのインスタンスを生成
	GameData* gamedata = &GameData::GetInstance();
	//インスタンスに名前を設定
	gamedata->SetName(L"GameData");
	//PlayerStatusクラスのインスタンスを生成
	PlayerStatus* playerstatus = &PlayerStatus::GetInstance();
	//インスタンスに名前を設定
	playerstatus->SetName(L"PlayerStatus");
	playerstatus->SetGameData(gamedata);
	//Town* town = new Town;
	Title* titel = new Title;
	SetPhysicsDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//ゲームループ。
	GetEngine().RunGameLoop();
}

