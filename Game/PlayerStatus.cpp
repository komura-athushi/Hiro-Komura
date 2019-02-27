#include "stdafx.h"
#include "PlayerStatus.h"
#include "Weapon.h"
#include "Magic.h"
#include "Player.h"
#include "Town.h"
PlayerStatus::PlayerStatus()
{
}

PlayerStatus::~PlayerStatus()
{
}

bool PlayerStatus::Start()
{
	//�ŏ��̕��킾�������󋵂�true�ɐݒ肷��
	m_equipmentlist.push_back(new Equipment(0));
	SetWeaponStatus();
	SetMagicStatus();
	//�Y������dds�t�@�C����ǂݍ���ł���
	m_spritenamelist.push_back(L"Resource/sprite/sword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/firesword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/icesword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/windsword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/greatsword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/bluelightsword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/battlereadyblade.dds");
	m_spritenamelist.push_back(L"Resource/sprite/ancientwarriorblade.dds");
	m_spritenamelist.push_back(L"Resource/sprite/excaliburmorgan.dds");
	m_cursor.Init(L"Resource/sprite/cursor.dds");
	CSprite* sprite = new CSprite;
	sprite->Init(m_spritenamelist[0]);
	m_spritelist.push_back(sprite);
	return true;
}

void PlayerStatus::Update()
{
	//LSB�{�^���������ƑS�����폊����ԂɈڍs
	if (Pad(0).GetDown(enButtonLSB)) {
		Town* town = FindGO<Town>();
		if (town == nullptr) {
			for (int i = 1; i < GameData::enWeapon_num; i++) {
				m_equipmentlist.push_back(new Equipment(i));
				CSprite* sprite = new CSprite;
				sprite->Init(m_spritenamelist[i]);
				m_spritelist.push_back(sprite);
			}
		}
		for (int i = 0; i < GameData::enMaterial_num; i++) {
			m_havemateriallist[i] = 100;
		}
		for (int i = 0; i < m_gamedata->m_stagenumber; i++) {
			//m_gamedata->SetClear(i);
		}
		m_MaxPP = 1000000000;
		m_havemeseta = 10000000;
		Player* player = FindGO<Player>(L"Player");
		if (player != nullptr) {
			player->SetPP(m_MaxPP);
		}
		//PlusExp(1000000000);
		
	}
}

void PlayerStatus::PlusExp(const int& exp)
{
	int ep = exp;
	//�o���l�����Z
	m_Exp += ep;
	//���x�����ƂɕK�v�ȗ݌v�o���l���v���C���[�̗݌v�o���l���傫���Ȃ�܂Ń��[�v
	while (m_LevelExp <= m_Exp) {
		ep -= m_NextExp;
		m_Level += 1;
		m_NextExp = (int)((1 + (float)(m_Level * m_Level * 0.1f)) * 60);
		m_LevelExp += m_NextExp;
		m_Power += 5 + rand() % 3;
		m_Attack = m_Power + m_SwordAttack;
		m_MaxHP += 10;
		m_MaxPP += 10;
		m_Clever += 10;
		m_Attack = m_Power + m_SwordAttack;
		m_Mattack = m_Clever + m_SwordMattack;
		m_levelup = true;
	}
		m_NextExp -= ep;
}

void PlayerStatus::SetWeaponStatus()
{
	m_SwordMattack = m_equipmentlist[m_SwordId]->GetMatk();
	m_SwordAttack = m_equipmentlist[m_SwordId]->GetAtk();
	m_MagicId = m_equipmentlist[m_SwordId]->GetMagicId();
	m_Rarity = m_equipmentlist[m_SwordId]->GetRarity();
	m_SwordName = m_equipmentlist[m_SwordId]->GetName();
	m_Mattack = m_Clever + m_SwordMattack;
	m_Attack = m_Power + m_SwordAttack;
}

void PlayerStatus::SetMagicStatus()
{
	m_MagicName = m_equipmentlist[m_SwordId]->GetMagicName();
	m_DamageRate = m_equipmentlist[m_SwordId]->GetDamageRate();
	m_PPCost = m_equipmentlist[m_SwordId]->GetPPCost();
}

bool PlayerStatus::GetWeapon(int number)
{
	int equipnumber = m_equipmentlist.size();
	//����������̔ԍ��͈̔͂𒴂��Ă�����֐��̏������I��������
	if (number < 0 || number > equipnumber - 1) {
		return false;
	}
	//���{�^�����������̏���
	if (m_SwordId > number) {
		if (m_SwordId == 0) {
			return false;
		}
		else {
			m_SwordId--;
			SetWeaponStatus();
			SetMagicStatus();
			return true;
		}
	}
	//�E�{�^�����������Ƃ��̏���
	else if (m_SwordId < number) {
		if (m_SwordId == equipnumber) {
			return false;
		}
		else {
			m_SwordId++;
			SetWeaponStatus();
			SetMagicStatus();
			return true;
		}
	}
	return false;
}

void PlayerStatus::SetWeapon(Equipment* number)
{
	m_equipmentlist.push_back(number);
	CSprite* sprite = new CSprite;
	sprite->Init(m_spritenamelist[number->GetId()]);
	m_spritelist.push_back(sprite);

}

void PlayerStatus::PostRender()
{
	//�X�e�𕶎��\��
	/*wchar_t output[256];
	swprintf_s(output, L"��   %d\n��   %d\n�����K  %d\n���Z�^  %d\n", m_havemateriallist[0], m_havemateriallist[1], m_havemateriallist[2],m_havemeseta);
	//swprintf_s(output, L"x   %f\ny   %f\nz  %f\nw   %f\n", m_swordqRot.x, m_swordqRot.y, m_swordqRot.z, m_swordqRot.w);
	m_font.DrawScreenPos(output, { 00.0f,200.0f }, CVector4::White(),
		CVector2::One(),
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		1.0f
	);*/
	//����̃A�C�R���\��
	CVector2 pos = m_position;
	for (int i = 0; i < m_equipmentlist.size(); i++) {
		m_spritelist[i]->DrawScreenPos(pos, m_scale, CVector2::Zero(),
			0.0f,
			CVector4::White(),
			DirectX::SpriteEffects_None,
			1.0f);
		if (m_SwordId == i) {
			m_cursor.DrawScreenPos(pos, m_scale, CVector2::Zero(),
				0.0f,
				CVector4::White(),
				DirectX::SpriteEffects_None,
				0.9f);
		}
		pos.x += 64.0f;
	}
}

void PlayerStatus::WeaponStrengthen(const int& number)
{
	if (m_havemeseta >= m_equipmentlist[number]->GetCost()) {
		m_havemeseta -= m_equipmentlist[number]->GetCost();
		m_equipmentlist[number]->Strengthen();
		if (m_SwordId == number) {
			SetWeaponStatus();
			SetMagicStatus();
		}
	}
}