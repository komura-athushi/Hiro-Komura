#include "stdafx.h"
#include "Weapon.h"
const int Weapon::m_raritynumber[Weapon::m_HighestRarity+1] = { 1,3,1,1,1,1,1 };

Weapon::Weapon(const int& id, const wchar_t* name, const int& rarity, const int& atk, const int& matk, const int& mnumber)
	:m_id(id),m_name(name),m_rarity(rarity),m_atk(atk),m_matk(matk),m_magicid(mnumber)
{
}

Weapon::Weapon(const Weapon& wpn):m_id(wpn.m_id), m_name(wpn.m_name), m_rarity(wpn.m_rarity), m_atk(wpn.m_atk), m_matk(wpn.m_matk), m_magicid(wpn.m_magicid)
{

}

Weapon::~Weapon()
{
}


