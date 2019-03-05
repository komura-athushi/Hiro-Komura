#include "stdafx.h"
#include "Weapon.h"
const int Weapon::m_raritynumber[Weapon::m_HighestRarity] = { 1,3,1,1,1,1,1 };
//コンストラクタで各ステータスを設定
Weapon::Weapon(const int& id, const wchar_t* name, const int& rarity, const int& atk, const int& matk, const int& mnumber,const int& meseta)
	:m_id(id),m_name(name),m_rarity(rarity),m_atk(atk),m_matk(matk),m_magicid(mnumber),m_meseta(meseta)
{
	
}

Weapon::Weapon(const Weapon& wpn):m_id(wpn.m_id), m_name(wpn.m_name), m_rarity(wpn.m_rarity), m_atk(wpn.m_atk), m_matk(wpn.m_matk), m_magicid(wpn.m_magicid),m_meseta(wpn.m_meseta)
{

}

Weapon::~Weapon()
{
}


