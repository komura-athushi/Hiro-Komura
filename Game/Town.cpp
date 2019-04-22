#include "stdafx.h"
#include "Town.h"
#include "Ground.h"
#include "GameCamera.h"
#include "Player.h"
#include "Stage1_Teleport.h"
#include "Stage2_Teleport.h"
#include "Stage3_Teleport.h"
#include "Game.h"
#include "PlayerStatus.h"
#include "Cagliostro_view.h"
#include "Human.h"
#include "Merchant.h"
#include "GameData.h"
#include "Fade.h"
#include "MainSound.h"
Town::Town()
{
	
}


Town::~Town()
{
	//�e�C���X�^���X���폜
	delete m_player;
	delete m_human;
	delete m_merchant;
	delete m_ground;
	delete m_gamecamera;
	delete m_lig;
	delete m_CascadeShadowmap;
	delete m_stage1_teleport;
	if (m_stage2_teleport != nullptr) {
		delete m_stage2_teleport;
	}
	if (m_stage3_teleport != nullptr) {
		delete m_stage3_teleport;
	}
}

bool Town::Start()
{
	m_gamedata = &GameData::GetInstance();
	//�f�B���N�V�������C�g��ݒ�
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,-1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	m_CascadeShadowmap = new CascadeShadowHandler;

	//������

	m_CascadeShadowmap->Init(5,//������

		m_lig->GetDirection(),//���C�g�̕���

		0.1f//�V���h�E�}�b�v�͈̔�(���C���J������Far�ɂ�����W���ł�)

	);

	m_CascadeShadowmap->SetNear(30.0f);

	m_CascadeShadowmap->SetFar(50000.0f);
	BuildLevel();
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	m_fade = &Fade::GetInstance();
	m_fade->StartFadeIn();
	MainSound* ms = &MainSound::GetInstance();
	ms->SetBGM(MainSound::enBGM_Town);
	return true;
}

void Town::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			//m_state�ɂ���Ď��̃��[�h�𕪊򂳂���
			if (m_state == enSt1) {
				Game* game = new Game;
				game->SetStageNumber(enSt1);
				delete this;
			}
			else if (m_state == enSt2) {
				Game* game = new Game;
				game->SetStageNumber(enSt2);
				delete this;
 			}
			else if (m_state == enSt3) {
				Game* game = new Game;
				game->SetStageNumber(enSt3);
				delete this;
			}
			else if (m_state == enCga) {
				Cagliostro_view* cag = new Cagliostro_view;
				delete this;
			}
			else {
				Town* town = new Town;
				delete this;
			}
		}
	}
	else {
		//�v���C���[�ƃX�e�[�W1�ɑJ�ڂ���I�u�W�F�N�g�̋������v�Z
		CVector3 pos = m_player->GetPosition() - m_stage1_teleport->GetPosition();
		CVector3 pos2 = {1000.0f,1000.0f,1000.0f};
		CVector3 pos3 = { 1000.0f,1000.0f,1000.0f };
		if (m_gamedata->GetTownLevel() >= 1 && m_stage2_teleport != nullptr) {
			pos2 = m_player->GetPosition() - m_stage2_teleport->GetPosition();
		}
		if (m_gamedata->GetTownLevel() >= 2 && m_stage3_teleport != nullptr) {
			pos3 = m_player->GetPosition() - m_stage3_teleport->GetPosition();
		}
		//���������ȉ��Ȃ�X�e�[�W1�ɑJ�ڂ���
		if (pos.LengthSq() <= 100.0f*100.0f) {
			m_state = enSt1;
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		//���������ȉ��Ȃ�X�e�[�W1�ɑJ�ڂ���
		else if (pos2.LengthSq() <= 100.0f*100.0f) {
			m_state = enSt2;
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		//���������ȉ��Ȃ�X�e�[�W1�ɑJ�ڂ���
		else if (pos3.LengthSq() <= 100.0f*100.0f) {
			m_state = enSt3;
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		////���_�ɋ��鎞��START�{�^���������ƃJ���I�X�g������񁙃��[�h�ɑJ�ڂ���
		//else if (Pad(0).GetDown(enButtonBack)) {
		//	m_state = enCga;
		//	m_isWaitFadeout = true;
		//	m_fade->StartFadeOut();
		//}
		//�X���č\�z
		else if (m_developtown) {
			m_state = enTown;
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}

void Town::BuildLevel()
{
	//�ǂݍ��ރt�@�C�������߂�
	wchar_t levelname[50];
	swprintf_s(levelname, L"Asset/level/town0%d.tkl",m_gamedata->GetTownLevel());
	m_level.Init(levelname, [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"ground") == true) {
			//�n�ʂƂ��ǂƂ�
			m_ground = new Ground;
			m_ground->SetStage(0);
			m_ground->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"ground2") == true) {
			//�n�ʂƂ��ǂƂ�
			m_ground = new Ground;
			m_ground->SetStage(0);
			m_ground->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"ground3") == true) {
			//�n�ʂƂ��ǂƂ�
			m_ground = new Ground;
			m_ground->SetStage(0);
			m_ground->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"stage1_teleport") == true) {
			//�߂Â�����X�e�[�W1�Ɉړ�����
			m_stage1_teleport = new Stage1_Teleport;
			m_stage1_teleport->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"stage2_teleport") == true) {
			//�߂Â�����X�e�[�W2�Ɉړ�����
			m_stage2_teleport = new Stage2_Teleport;
			m_stage2_teleport->SetPosition(objData.position);
		
			return true;
		}
		else if (objData.EqualObjectName(L"stage3_teleport") == true) {
			//�߂Â�����X�e�[�W3�Ɉړ�����
			m_stage3_teleport = new Stage3_Teleport;
			m_stage3_teleport->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"human") == true) {
			//���_���W
			m_human = new Human;
			m_human->SetPosition(objData.position);
			m_human->SetName(L"Human");
			return true;
		}
		else if (objData.EqualObjectName(L"merchant") == true) {
			//���틭������l
			m_merchant = new Merchant;
			m_merchant->SetPosition(objData.position);
			m_merchant->SetRotation(objData.rotation);
			m_merchant->SetName(L"Merchant");
			return true;
		}
		else if (objData.EqualObjectName(L"unityChan") == true) {
			//Unity�����B
			//�v���C���[�̃C���X�^���X�𐶐�����B
			m_player = new Player;
			m_player->SetPosition(objData.position);
			m_player->SetRotation(objData.rotation);
			m_player->SetName(L"Player");
			return true;
		}
		return false;
	});
}

