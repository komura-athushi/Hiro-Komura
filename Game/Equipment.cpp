#include "stdafx.h"
#include "Equipment.h"


Equipment::Equipment()
{
	
}

Equipment::~Equipment()
{
}

void Equipment::SetWeaponID(const int& id)
{
	m_SwordId = id;
	m_gamedata = FindGO<GameData>(L"GameData");
	GetWeaponStatus();
	GetMagicStatus();
}

void Equipment::GetWeaponStatus()
{
	m_weapon = m_gamedata->GetWeapon(m_SwordId);
	m_SwordMattack = m_weapon->GetMatk();
	m_SwordAttack = m_weapon->GetAtk();
	m_MagicId = m_weapon->GetMagicId();
	m_Rarity = m_weapon->GetRarity();
	m_SwordName = m_weapon->GetName();
}

void Equipment::GetMagicStatus()
{
	m_magic = m_gamedata->GetMagic(m_MagicId);
	m_MagicName = m_magic->GetName();
	m_DamageRate = m_magic->GetDamageRate();
	m_PPCost = m_magic->GetPPCost();
}
