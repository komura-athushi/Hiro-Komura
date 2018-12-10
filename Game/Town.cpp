#include "stdafx.h"
#include "Town.h"
#include "Ground.h"
#include "GameCamera.h"
#include "Player.h"
#include "Stone.h"
#include "House.h"
#include "Stage1_Teleport.h"
#include "Stage1.h"
#include "PlayerStatus.h"
#include "Cagliostro_view.h"
#include "Human.h"
Town::Town()
{
	
}


Town::~Town()
{
	delete m_player;
	delete m_human;
	delete m_ground;
	delete m_gamecamera;
	delete m_lig;
	delete m_stage1_teleport;
	for (auto& stone : m_stoneList) {
		delete stone;
	}
	for (auto& house : m_houseList) {
		delete house;
	}
}

bool Town::Start()
{
	//�f�B���N�V�������C�g��ݒ�
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	//���x�����\�z����B
	m_level.Init(L"Asset/level/town00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"ground") == true) {
			m_ground = new Ground;
			m_ground->SetStage(0);
			m_ground->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"stone") == true) {
			//Star�I�u�W�F�N�g�B
			Stone* stone = new Stone;
			stone->SetPosition(objData.position);
			//��ō폜����̂Ń��X�g�ɐς�ŋL�����Ă����B
			m_stoneList.push_back(stone);
			//�t�b�N�����̂�true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"house") == true) {
			//Star�I�u�W�F�N�g�B
			House* house = new House;
			house->SetPosition(objData.position);
			house->SetRotation(objData.rotation);
			//��ō폜����̂Ń��X�g�ɐς�ŋL�����Ă����B
			m_houseList.push_back(house);
			//�t�b�N�����̂�true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"stage1_teleport") == true) {
			//Star�I�u�W�F�N�g�B
			m_stage1_teleport = new Stage1_Teleport;
			m_stage1_teleport->SetPosition(objData.position);
			//�t�b�N�����̂�true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"human") == true) {
			//Human
			m_human = new Human;
			m_human->SetPosition(objData.position);
			m_player->SetName(L"Human");
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"unityChan") == true) {
			//Unity�����B
			//�v���C���[�̃C���X�^���X�𐶐�����B
			m_player = new Player;
			m_player->SetPosition(objData.position);
			m_player->SetRotation(objData.rotation);
			m_player->SetName(L"Player");
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}

		return false;
	});
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	return true;
}

void Town::Update()
{
	//�v���C���[�ƃX�e�[�W1�ɑJ�ڂ���I�u�W�F�N�g�̋������v�Z
	CVector3 pos= m_player->GetPosition() - m_stage1_teleport->GetPosition();
	//���������ȉ��Ȃ�X�e�[�W1�ɑJ�ڂ���
	if (pos.Length() <= 100.0f) {
		Stage1* stage1 = new Stage1;
		delete this;
	}
	//���_�ɋ��鎞��START�{�^���������ƃJ���I�X�g������񁙃��[�h�ɑJ�ڂ���
	if (Pad(0).GetDown(enButtonStart)) {
		Cagliostro_view* cag = new Cagliostro_view;
		delete this;
	}
}
