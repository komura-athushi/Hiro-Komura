#include "stdafx.h"
#include "Stage1.h"
#include "Player.h"
#include "GameCamera.h"
#include "Ground.h"
#include "Town.h"
Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	delete m_player;
	delete m_gamecamera;
	delete m_ground;
	delete m_lig;
}

bool Stage1::Start()
{
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
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

void Stage1::Update()
{
	if (Pad(0).GetButton(enButtonSelect)) {
		Town* town = new Town;
		delete this;
	}
}