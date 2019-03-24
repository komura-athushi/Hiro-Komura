#include "stdafx.h"
#include "DropItem.h"
#include "Weapon.h"
#include "Player.h"
#include "PlayerStatus.h" 
#include "GameData.h"
#include "Equipment.h"
const float DropItem::m_height = 30.0f;
const float DropItem::m_height_weapon = 10.0f;
DropItem::DropItem()
{
}


DropItem::~DropItem()
{
	delete m_skinModelRender;
	if (!m_issetweapon) {
		delete m_equipment;
	}
}

bool DropItem::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	if (m_isweapon) {
		//�h���b�v�����镐��̔ԍ������߂܂�
		m_state = 0;
		int type = Weapon::m_raritynumber[m_rarity];
		int rn = int(float(100 / type));
		int randm = rand() % 100 + 1;
		for (int i = 0; i < type; i++) {
			if (i*rn <= randm && randm < (i + 1)*rn) {
				m_number = i;
			}
		}
		for (int i = 0; i < m_rarity; i++) {
			m_state += Weapon::m_raritynumber[i];
		}
		m_state += m_number;
		//����̔ԍ��ɂ���ēǂݍ���fbx�t�@�C�������߂܂�
		switch (m_state) {
		/*case 1:
			m_skinModelRender->Init(L"Resource/modelData/FireSword_drop.cmo");
			break;
		case 2:
			m_skinModelRender->Init(L"Resource/modelData/IceSword_drop.cmo");
			break;
		case 3:
			m_skinModelRender->Init(L"Resource/modelData/WindSword_drop.cmo");
			break;
		case 4:
			m_skinModelRender->Init(L"Resource/modelData/GreatSword_drop.cmo");
			break;
		case 5:
			m_skinModelRender->Init(L"Resource/modelData/BlueLightSword_drop.cmo");
			break;
		case 6:
			m_skinModelRender->Init(L"Resource/modelData/BattleReadyBlade_drop.cmo");
			break;
		case 7:
			m_skinModelRender->Init(L"Resource/modelData/AncientWarriorBlade_drop.cmo");
			break;
		case 8:
			m_skinModelRender->Init(L"Resource/modelData/excaliburmorgan_drop.cmo");
			break;*/
		case GameData::enWeapon_Sword:
			m_skinModelRender->Init(L"Resource/modelData/Sword_drop.cmo");
			break;
		case GameData::enWeapon_FireSword:
			m_skinModelRender->Init(L"Resource/modelData/FireSword_drop.cmo");
			break;
		case GameData::enWeapon_IceSword:
			m_skinModelRender->Init(L"Resource/modelData/IceSword_drop.cmo");
			break;
		case GameData::enWeapon_WindSword:
			m_skinModelRender->Init(L"Resource/modelData/WindSword_drop.cmo");
			break;
		case GameData::enWeapon_GreatSword:
			m_skinModelRender->Init(L"Resource/modelData/GreatSword_drop.cmo");
			break;
		case GameData::enWeapon_BlueLightSword:
			m_skinModelRender->Init(L"Resource/modelData/BlueLightSword_drop.cmo");
			break;
		case GameData::enWeapon_BattleReadyBlade:
			m_skinModelRender->Init(L"Resource/modelData/BattleReadyBlade_drop.cmo");
			break;
		case GameData::enWeapon_AncientWarriorBlade:
			m_skinModelRender->Init(L"Resource/modelData/AncientWarriorBlade_drop.cmo");
			break;
		case GameData::enWeapon_LegendalySword:
			m_skinModelRender->Init(L"Resource/modelData/excaliburmorgan_drop.cmo");
			break;
		}
		m_position.y += m_height_weapon;
		m_equipment = new Equipment(m_state);
	}
	else {
		m_skinModelRender->Init(L"Resource/modelData/meseta.cmo");
		m_position.y += m_height;
		m_issetweapon = true;
	}
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRot(m_rotation);
	m_player = FindGO<Player>(L"Player");
	return true;
}

void DropItem::Update()
{
	m_degree += 200.0f * GetDeltaTimeSec();
	m_rotation.SetRotationDeg(CVector3::AxisY(), m_degree);
	m_skinModelRender->SetRot(m_rotation);
	//�v���C���[�Ƃ̋��������ȉ��ɂȂ�����v���C���[�̏�������Ɏ��g��ǉ�����A���邢�̓��Z�^�̊z�����Z����
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.Length() <= 80.0f) {
		PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
		if (m_isweapon) {
			//���g������̏ꍇ�v���C���[�ɒǉ��A���ɏ������Ă���ꍇ�͐ݒ肵�����Z�^�̊z���v���C���[�ɒǉ�
			playerstatus->SetWeapon(m_equipment);
			m_issetweapon = true;
		}
		else {
			//�ݒ肵�����Z�^�̊z���v���C���[�ɒǉ�
			playerstatus->AddMeseta(m_meseta);
		}
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/get.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(m_sevolume);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
		delete this;
	}
}