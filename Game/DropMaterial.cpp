#include "stdafx.h"
#include "DropMaterial.h"
#include "Material.h"
#include "Player.h"
#include "PlayerStatus.h"
DropMaterial::DropMaterial()
{
}


DropMaterial::~DropMaterial()
{
	delete m_skinModelRender;
}

bool DropMaterial::Start()
{
	//�h���b�v�����镐��̔ԍ������߂܂�
	m_state = 0;
	int type = Material::m_raritynumber[m_rarity];
	int rn = int(float(100 / type));
	int randm = rand() % 100 + 1;
	for (int i = 0; i < type; i++) {
		if (i*rn <= randm && randm < (i + 1)*rn) {
			m_number = i;
		}
	}
	for (int i = 0; i < m_rarity; i++) {
		m_state += Material::m_raritynumber[i];
	}
	m_state += m_number;
	m_skinModelRender = new GameObj::CSkinModelRender;
	//�Y���̔ԍ��̑f�ނ̃t�@�C����ǂݍ���
	switch (m_state) {
	case GameData::enMaterial_Wood:
		m_skinModelRender->Init(L"Resource/modelData/wood.cmo");
		break;
	case GameData::enMaterial_Ishi:
		m_skinModelRender->Init(L"Resource/modelData/ishi.cmo");
		break;
	case GameData::enMaterial_Brick:
		m_skinModelRender->Init(L"Resource/modelData/brick.cmo");
		break;
	default:
		break;
	}
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRot(m_rotation);
	m_player = FindGO<Player>(L"Player");
	return true;
}

void DropMaterial::Update()
{
	m_degree += 200.0f * GetDeltaTimeSec();
	m_rotation.SetRotationDeg(CVector3::AxisY(), m_degree);
	m_skinModelRender->SetRot(m_rotation);
	//�v���C���[�Ƃ̋��������ȉ��ɂȂ�����v���C���[�̏����f�ނɎ��g��ǉ�����
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.Length() <= 80.0f) {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/get.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(m_sevolume);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
		PlayerStatus* playerstatus = &PlayerStatus::GetInstance();
		//�v���C���[�̏����f�ނɒǉ�
		playerstatus->SetMaterial(m_state);
		delete this;
	}
}