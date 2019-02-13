#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "Ground.h"
#include "Town.h"
#include "PlayerStatus.h"
#include "Oni.h"
#include "Boss.h"
#include "Boss2.h"
#include "DropItem.h"
#include "DropMaterial.h"
#include "IEnemy.h"
#include "GameData.h"
#include "Fade.h"
#include "MainSound.h"
Game::Game()
{
}

Game::~Game()
{
	delete m_player;
	delete m_gamecamera;
	delete m_ground;
	delete m_lig;
	delete m_shadowMap;
	QueryGOs<Oni>(L"Enemy", [&](Oni* oni)
	{
		delete oni;
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
}

bool Game::Start()
{
	//�f�B���N�V�������C�g��ݒ�
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,-1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	m_shadowMap = new ShadowMapHandler;

	//������

	m_shadowMap->Init(8048,//�𑜓x(��

		8048,//�𑜓x(����

		m_lig->GetDirection()//���C�g�̕���

	);

	m_shadowMap->SetArea({ 20000.0f,20000.0f,20000.0f });//�V���h�E�}�b�v�͈̔�(Z�����C�g�̕���)

	m_shadowMap->SetTarget({ 0.0f,0.0f,0.0f });//�V���h�E�}�b�v�͈̔͂̒��S�ʒu*/
	//���x�����\�z����B
	m_level.Init(L"Asset/level/stage1.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"stage1_ground") == true) {
			m_ground = new Ground;
			m_ground->SetStage(1);
			m_ground->SetPosition(objData.position);
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
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		return false;
	});
	//����������
	//�{�X2
			//�v���C���[�̃C���X�^���X�𐶐�����B
	Boss2* boss2 = new Boss2;
	boss2->SetName(L"Enemy");
	boss2->SetPlayer(m_player);
	//�����܂�
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	MainSound* ms = FindGO<MainSound>();
	if (m_stagenumber == 1) {
		ms->SetBGM(2);
	}
	else if (m_stagenumber == 2) {
		ms->SetBGM(3);
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
			Town* town = new Town;
			delete this;
		}
	}
	else {
		//�v���C���[���Q�[���I�[�o�[���邢�̓Q�[���N���A�ŋ��_�ɑJ��
		if (m_player->GetTransScene()) {
			if (m_player->GetGameClear()) {
				GameData* gamedata = FindGO<GameData>(L"GameData");
				gamedata->SetClear(0);
			}
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	
}

