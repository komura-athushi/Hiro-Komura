#include "stdafx.h"
#include "Title.h"
#include "Town.h"
#include "Game.h"
#include "PlayerStatus.h"
#include "Fade.h"
#include <time.h>
#include "GameData.h"
#include "MainSound.h"
#include "GameClear.h"
#include "DemolisherWeapon/Graphic/Sky/CSkybox.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned)time(NULL));
	//�Q�[���̏������B
	InitEngineParameter initparam; 
	GetEngine().InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game", initparam);	
	GameObj::PerspectiveCamera* cam = new GameObj::PerspectiveCamera;
	SetMainCamera(cam);
	cam->SetName(L"Camera");
	//GameData�N���X�̃C���X�^���X��ÓI�Ȋ֐����g���Đ���
	GameData* gamedata = &GameData::GetInstance();
	//�C���X�^���X�ɖ��O��ݒ�
	gamedata->SetName(L"GameData");
	//PlayerStatus�N���X�̃C���X�^���X��ÓI�Ȋ֐����g���Đ���
	PlayerStatus* playerstatus = &PlayerStatus::GetInstance();
	//�C���X�^���X�ɖ��O��ݒ�
	playerstatus->SetName(L"PlayerStatus");
	playerstatus->SetGameData(gamedata);
	//Fade�N���X�̃C���X�^���X��ÓI�Ȋ֐����g���Đ���
	Fade* fade = &Fade::GetInstance();
	//MainSound�N���X�̃C���X�^���X��ÓI�Ȋ֐��������Đ���
	MainSound* mainsound = &MainSound::GetInstance();
	Title* titel = new Title;
	//GameClear* gc = new GameClear;
	GameObj::CSkybox* cs = new GameObj::CSkybox(L"Preset/modelData/skyCubeMap.dds",100000.0f);
	SetPhysicsDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//�Q�[�����[�v�B
	GetEngine().RunGameLoop();
}

