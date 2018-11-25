#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(const int& id, const std::string& name, const int& rarity, const int& atk, const int& matk, const int& mnumber)
	:m_id(id),m_name(name),m_rarity(rarity),m_atk(atk),m_matk(matk),m_magicid(mnumber)
{
}


Weapon::~Weapon()
{
}

bool Weapon::Start()
{

	return true;
}

void Weapon::Update()
{

}
