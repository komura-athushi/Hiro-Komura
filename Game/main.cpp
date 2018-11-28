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
	//�Q�[���̏������B
	InitEngineParameter initparam; 
	GetEngine().InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game", initparam);	
	GameObj::PerspectiveCamera cam; SetMainCamera(&cam);
	//GameData�N���X�̃C���X�^���X�𐶐�
	GameData* gamedata = new GameData;
	//�C���X�^���X�ɖ��O��ݒ�
	gamedata->SetName(L"GameData");
	//PlayerStatus�N���X�̃C���X�^���X�𐶐�
	PlayerStatus* playerstatus = new PlayerStatus;
	//�C���X�^���X�ɖ��O��ݒ�
	playerstatus->SetName(L"PlayerStatus");
	playerstatus->SetGameData(gamedata);
	Town* town = new Town;
	//Title* titel = new Title;
	town->SetPlayerStatus(playerstatus);
	SetPhysicsDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//�Q�[�����[�v�B
	GetEngine().RunGameLoop();
}

