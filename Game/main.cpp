#include "stdafx.h"
#include "Title.h"
#include "Town.h"
#include "Stage1.h"
#include "PlayerStatus.h"
#include "Fade.h"
#include <time.h>
#include "GameData.h"
#include "MainSound.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned)time(NULL));
	//ゲームの初期化。
	InitEngineParameter initparam; 
	GetEngine().InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game", initparam);	
	GameObj::PerspectiveCamera* cam = new GameObj::PerspectiveCamera;
	SetMainCamera(cam);
	cam->SetName(L"Camera");
	//GameDataクラスのインスタンスを静的な関数を使って生成
	GameData* gamedata = &GameData::GetInstance();
	//インスタンスに名前を設定
	gamedata->SetName(L"GameData");
	//PlayerStatusクラスのインスタンスを静的な関数を使って生成
	PlayerStatus* playerstatus = &PlayerStatus::GetInstance();
	//インスタンスに名前を設定
	playerstatus->SetName(L"PlayerStatus");
	playerstatus->SetGameData(gamedata);
	//Fadeクラスのインスタンスを静的な関数を使って生成
	Fade* fade = &Fade::GetInstance();
	//MainSoundクラスのインスタンスを静的な関数をつかって生成
	MainSound* mainsound = &MainSound::GetInstance();
	Title* titel = new Title;
	SetPhysicsDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//ゲームループ。
	GetEngine().RunGameLoop();
}

