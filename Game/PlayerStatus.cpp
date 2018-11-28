#include "stdafx.h"
#include "PlayerStatus.h"
#include "Weapon.h"
PlayerStatus::PlayerStatus()
{
}


PlayerStatus::~PlayerStatus()
{
}

bool PlayerStatus::Start()
{
	GetWeaponStatus();
	return true;
}

void PlayerStatus::Update()
{

}

void PlayerStatus::PlusExp(const int& exp)
{
	int ep = exp;
	//経験値を加算
	m_Exp += ep;
	while (m_LevelExp <= m_Exp) {
		ep -= m_NextExp;
		m_Level+=1;
		m_NextExp = (int)((1 + (float)(m_Level*m_Level * 0.1f)) * 80);
		m_LevelExp += m_NextExp;
		m_Power += 5 + rand() % 3;
		m_Attack = m_Power + m_SwordAttack;
		m_MaxHP += 10;
		m_MaxPP += 10;
		m_Clever += 10;
		m_Attack = m_Power + m_SwordAttack;
		m_Mattack = m_Mattack + m_SwordMattack;
	}
		m_NextExp -= ep;
}

void PlayerStatus::GetWeaponStatus()
{
	m_weapon = m_gamedata->GetWeapoin(m_SwordId);
	m_SwordMattack = m_weapon->GetMatk();
	m_SwordAttack = m_weapon->GetAtk();
	m_MagicId = m_weapon->GetMagicId();
	m_Rarity = m_weapon->GetRarity();
	m_SwordName = m_weapon->GetName();
	m_Mattack = m_Clever + m_SwordMattack;
	m_Attack = m_Power + m_SwordAttack;
}

bool PlayerStatus::GetWeapon(int number)
{
	if (number<0 || number>GameData::enWeapon_num-1) {
		return false;
	}
	//左ボタン押した時の処理
	if (m_SwordId > number) {
		for (int i = number; i >= 0; i--) {
			if (m_haveweaponlist[i]) {
				m_SwordId = i;
				GetWeaponStatus();
				return true;
			}
		}
	}
	else if (m_SwordId < number) {
		for (int i = number; i < GameData::enWeapon_num; i++) {
			if (m_haveweaponlist[i]) {
				m_SwordId = i;
				GetWeaponStatus();
				return true;
			}
		}
	}
	return false;
}