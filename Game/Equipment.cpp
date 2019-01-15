#include "stdafx.h"
#include "Equipment.h"
#include "GameData.h"
//Equipment::Equipment()
//{
//	
//}
Equipment::Equipment(const int& number):m_SwordId(number)
{
	//GameDataクラスを経由して各ステータスを取得する
	m_gamedata = FindGO<GameData>(L"GameData");
	SetWeaponStatus();
	SetMagicStatus();
}
Equipment::~Equipment()
{
}

void Equipment::SetWeaponStatus()
{
	m_weapon = m_gamedata->GetWeapon(m_SwordId);
	m_SwordMattack = m_weapon->GetMatk();
	m_SwordAttack = m_weapon->GetAtk();
	m_MagicId = m_weapon->GetMagicId();
	m_Rarity = m_weapon->GetRarity();
	m_SwordName = m_weapon->GetName();
}

void Equipment::SetMagicStatus()
{
	m_magic = m_gamedata->GetMagic(m_MagicId);
	m_MagicName = m_magic->GetName();
	m_DamageRate = m_magic->GetDamageRate();
	m_PPCost = m_magic->GetPPCost();
}


