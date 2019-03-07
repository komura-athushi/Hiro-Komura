#include "stdafx.h"
#include "Equipment.h"
#include "GameData.h"
const float Equipment::m_multiply = 1.15f;
const float Equipment::m_costmultiply = 1.2f;
Equipment::Equipment(const int& number):m_SwordId(number)
{
	//GameDataクラスを経由して各ステータスを取得する
	m_gamedata = FindGO<GameData>(L"GameData");
	//それぞれのステータスを設定
	SetWeaponStatus();
	SetMagicStatus();
	if (m_SwordId != 0) {
		for (int i = 0; i < m_slotlimitnumber; i++) {
			int rn = rand() % 100 + 1;
			if (rn < m_probability) {
				rn = rn % m_gamedata->GetAbilityListNumber();
				if (m_ishaveability) {
					for (int i = 0; i < m_abilitylist.size(); i++) {
						if (rn == m_abilitylist[i]->GetId()) {
							break;
						}
						if (i == m_abilitylist.size()) {
							m_abilitylist.push_back(m_gamedata->GetAbility(rn));
							m_ishaveability = true;
						}
					}
				}
				else {
					m_abilitylist.push_back(m_gamedata->GetAbility(rn));
					m_ishaveability = true;
				}
		
			}
		}
		SetWeaponStatus();
	}
}

Equipment::~Equipment()
{
}

void Equipment::SetWeaponStatus()
{
	m_weapon = m_gamedata->GetWeapon(m_SwordId);
	m_SwordMattack = m_weapon->GetMatk();
	m_Mattack = m_SwordMattack;
	m_SwordAttack = m_weapon->GetAtk();
	m_Attack = m_SwordAttack;
	m_MagicId = m_weapon->GetMagicId();
	m_Rarity = m_weapon->GetRarity();
	m_SwordName = m_weapon->GetName();
	m_meseta = m_weapon->GetMeseta();
	m_Attack = m_SwordAttack;
	m_Mattack = m_SwordMattack;
	m_hp = 0;
	m_pp = 0;
	if (m_ishaveability) {
		for (int i = 0; i < m_abilitylist.size(); i++) {
			m_Attack += m_abilitylist[i]->GetPower();
			m_Mattack += m_abilitylist[i]->GetMpower();
			m_hp += m_abilitylist[i]->GetHP();
			m_pp += m_abilitylist[i]->GetPP();
		}
	}

}

void Equipment::SetMagicStatus()
{
	m_magic = m_gamedata->GetMagic(m_MagicId);
	m_MagicName = m_magic->GetName();
	m_DamageRate = m_magic->GetDamageRate();
	m_PPCost = m_magic->GetPPCost();
}

void Equipment::Strengthen()
{
	m_weaponextend++;
	m_SwordAttack *= m_multiply;
	m_SwordMattack *= m_multiply;
	SetWeaponStatus();
}

const wchar_t* Equipment::GetAbilityName(const int& number)
{
	if (!m_ishaveability) {
		return L"無し";
	}
	else {
		if (number <= m_abilitylist.size()) {
			return m_abilitylist[number - 1]->GetName();
		}
		else {
			return L"無し";
		}
	}
}