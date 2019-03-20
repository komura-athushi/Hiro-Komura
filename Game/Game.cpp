#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "Ground.h"
#include "Town.h"
#include "PlayerStatus.h"
#include "Oni.h"
#include "Skeleton2.h"
#include "Boss.h"
#include "Boss2.h"
#include "DropItem.h"
#include "DropMaterial.h"
#include "IEnemy.h"
#include "GameData.h"
#include "Fade.h"
#include "MainSound.h"
#include "Teleport.h"
#include "GameClear.h"
#include "Kurage.h"
#include "Kurage2.h"
#include "Kurage3.h"
#include "Wall.h"
Game::Game()
{
}

Game::~Game()
{
	delete m_player;
	delete m_gamecamera;
	delete m_ground;
	delete m_lig;
	delete m_CascadeShadowmap;
	QueryGOs<Oni>(L"Enemy", [&](Oni* oni)
	{
		delete oni;
		return true;
	});
	QueryGOs<Skeleton2>(L"Enemy", [&](Skeleton2* sk2)
	{
		delete sk2;
		return true;
	});
	QueryGOs<Kurage>(L"Enemy", [&](Kurage* kg)
	{
		delete kg;
		return true;
	});
	QueryGOs<Kurage2>(L"Enemy", [&](Kurage2* kg2)
	{
		delete kg2;
		return true;
	});
	QueryGOs<Kurage3>(L"Enemy", [&](Kurage3* kg3)
	{
		delete kg3;
		return true;
	});
	QueryGOs<Boss>(L"Enemy", [&](Boss* boss)
	{
		delete boss;
		return true;
	});
	QueryGOs<Boss2>(L"Enemy", [&](Boss2* boss2)
	{
		delete boss2;
		return true;
	});
	QueryGOs<DropItem>(L"DropItem", [&](DropItem* dropitem)
	{
		delete dropitem;
		return true;
	});
	QueryGOs<DropMaterial>(L"DropMaterial", [&](DropMaterial* dropmaterial)
	{
		delete dropmaterial;
		return true;
	});
	QueryGOs<Teleport>(L"Teleport", [&](Teleport* tl)
	{
		delete tl;
		return true;
	});
	delete m_wall;
}

bool Game::Start()
{
	m_gamedata = FindGO<GameData>(L"GameData");
	//�f�B���N�V�������C�g��ݒ�
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,-1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	//�J�X�P�[�h�V���h�E�A�J�����Ƃ̋����ɉ����ăV���h�E�̉𑜓x��ς���H�Ƃ��Ȃ�Ƃ�
	m_CascadeShadowmap = new CascadeShadowHandler;

	//������

	m_CascadeShadowmap->Init(5,//������

		m_lig->GetDirection(),//���C�g�̕���

		0.1f//�V���h�E�}�b�v�͈̔�(���C���J������Far�ɂ�����W���ł�)

	);

	m_CascadeShadowmap->SetNear(30.0f);

	m_CascadeShadowmap->SetFar(50000.0f);
	//���x�����\�z����B
	const wchar_t* levelpath = nullptr;
	switch (m_stagenumber) {
	case 1:
		levelpath = L"Asset/level/stage1.tkl";
			break;
	case 2:
		levelpath = L"Asset/level/stage2.tkl";
			break;
	case 3:
		levelpath = L"Asset/level/stage2.tkl";
	}
	int number = 0;
	m_level.Init(levelpath, [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"stage1_ground") == true) {
			m_ground = new Ground;
			m_ground->SetStage(1);
			m_ground->SetPosition(objData.position);
			m_ground->SetRot(objData.rotation);
			m_ground->SetScale(objData.scale);
			return true;
		}
		else if (objData.EqualObjectName(L"stage2_ground") == true) {
			m_ground = new Ground;
			m_ground->SetStage(2);
			m_ground->SetPosition(objData.position);
			m_ground->SetRot(objData.rotation);
			m_ground->SetScale(objData.scale);
			return true;
		}
		else if (objData.EqualObjectName(L"wall") == true) {
			m_wall = new Wall;
			m_wall->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"unityChan") == true) {
			//Unity�����B
			//�v���C���[�̃C���X�^���X�𐶐�����B
			m_player = new Player;
			m_player->SetPosition(objData.position);
			m_player->SetName(L"Player");
			m_player->SetRotation(objData.rotation);
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"enemy") == true) {
			//�X�P���g��
			//�v���C���[�̃C���X�^���X�𐶐�����B
			Oni* oni = new Oni;
			oni->SetPosition(objData.position);
			oni->SetOldPosition(objData.position);
			oni->SetName(L"Enemy");
			//��ō폜����̂Ń��X�g�ɐς�ŋL�����Ă����B
			m_oniList.push_back(oni);
			oni->SetPlayer(m_player);
			oni->SetGame(this);
			oni->SetNumber(number);
			number++;
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"enemy2") == true) {
			//�X�P���g��
			//�v���C���[�̃C���X�^���X�𐶐�����B
			Skeleton2* sk2 = new Skeleton2;
			sk2->SetPosition(objData.position);
			sk2->SetOldPosition(objData.position);
			sk2->SetName(L"Enemy");
			//��ō폜����̂Ń��X�g�ɐς�ŋL�����Ă����B
			m_sk2List.push_back(sk2);
			sk2->SetPlayer(m_player);
			sk2->SetGame(this);
			sk2->SetNumber(number);
			number++;
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"kurage") == true) {
			//�X�P���g��
			//�v���C���[�̃C���X�^���X�𐶐�����B
			Kurage* kr = new Kurage;
			kr->SetPosition(objData.position);
			kr->SetName(L"Enemy");
			//��ō폜����̂Ń��X�g�ɐς�ŋL�����Ă����B
			kr->SetPlayer(m_player);
			kr->SetGame(this);
			kr->SetNumber(number);
			number++;
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"kurage2") == true) {
			//�X�P���g��
			//�v���C���[�̃C���X�^���X�𐶐�����B
			Kurage2* kr2 = new Kurage2;
			kr2->SetPosition(objData.position);
			kr2->SetName(L"Enemy");
			//��ō폜����̂Ń��X�g�ɐς�ŋL�����Ă����B
			kr2->SetPlayer(m_player);
			kr2->SetGame(this);
			kr2->SetNumber(number);
			number++;
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"kurage3") == true) {
			//�X�P���g��
			//�v���C���[�̃C���X�^���X�𐶐�����B
			Kurage3* kr3 = new Kurage3;
			kr3->SetPosition(objData.position);
			kr3->SetName(L"Enemy");
			//��ō폜����̂Ń��X�g�ɐς�ŋL�����Ă����B
			kr3->SetPlayer(m_player);
			kr3->SetGame(this);
			kr3->SetNumber(number);
			number++;
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"boss") == true) {
			//�{�X
			//�v���C���[�̃C���X�^���X�𐶐�����B
			Boss* boss = new Boss;
			boss->SetPosition(objData.position);
			boss->SetOldPosition(objData.position);
			boss->SetName(L"Enemy");
			boss->SetPlayer(m_player);
			boss->SetStage1(this);
			boss->SetNumber(number);
			number++;
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"boss2") == true) {
			//�{�X
			//�v���C���[�̃C���X�^���X�𐶐�����B
			Boss2* boss = new Boss2;
			boss->SetPosition(objData.position);
			boss->SetOldPosition(objData.position);
			boss->SetName(L"Enemy");
			boss->SetPlayer(m_player);
			boss->SetNumber(number);
			number++;
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		return false;
	});
	//����������
	//�{�X2
	//�v���C���[�̃C���X�^���X�𐶐�����B
	/*Boss2* boss2 = new Boss2;
	boss2->SetName(L"Enemy");
	boss2->SetPlayer(m_player);*/
	//�����܂�
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	//�X�e�[�W�ɉ����ė���BGM��ω������܂�
	MainSound* ms = FindGO<MainSound>();
	if (m_stagenumber == 1) {
		ms->SetBGM(2);
	}
	else if (m_stagenumber == 2) {
		ms->SetBGM(3);
	}
	else if (m_stagenumber == 3) {
		ms->SetBGM(4);
	}
	//SE
	SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/start.wav");
	se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
	se->SetVolume(2.6f);
	return true;
}

void Game::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			if (m_gamedata->GetisGameClear() && !m_gamedata->GetisGameEnd()) {
				GameClear* gameclear = new GameClear;
				delete this;
			}
			else {
				Town* town = new Town;
				delete this;
			}
		}
	}
	else {
		//�v���C���[�̃V�[���J�ڃt���O���I���ɂȂ�΃V�[���J�ڂ��܂�
		if (m_player->GetTransScene()) {
			//�v���C���[�̃N���A�t���O���I���ɂȂ�΁AGameData�̃X�e�[�W���Ƃ̃N���A�t���O���I���ɂ��܂�
			if (m_player->GetGameClear()) {
				m_gamedata->SetClear(m_stagenumber - 1);
				if (m_stagenumber == 3 && !m_gamedata->GetisGameClear()) {
					m_gamedata->SetGameClear();
				}
			}
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	
}

