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
	m_explevel1 = float(m_explevel1) * (1.0f + m_exprarity * float(m_Rarity));
	m_NextExp = m_explevel1;
	m_LevelExp = m_NextExp;
}

Equipment::~Equipment()
{
}


void Equipment::SetWeaponStatus()
{
	if (m_weaponextend == 0) {
		m_weapon = m_gamedata->GetWeapon(m_SwordId);
		m_SwordMattack = m_weapon->GetMatk();
		m_protSwordMattack = m_SwordMattack;
		m_Mattack = m_SwordMattack;
		m_SwordAttack = m_weapon->GetAtk();
		m_protSwordAattack = m_SwordAttack;
		m_Attack = m_SwordAttack;
		m_MagicId = m_weapon->GetMagicId();
		m_Rarity = m_weapon->GetRarity();
		m_SwordName = m_weapon->GetName();
		m_meseta = m_weapon->GetMeseta();
	}
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

void Equipment::PlusExp(const int& exp)
{
	int ep = exp;
	//経験値を加算
	m_Exp += ep;
	//レベルアップに必要な累計経験値がプレイヤーの累計経験値より大きくなるまでループ
	while (m_LevelExp <= m_Exp) {
		ep -= m_NextExp;
		m_weaponextend += 1;
		m_NextExp = (int)((1 + (float)(m_weaponextend * m_weaponextend * 0.1f)) * m_explevel1);
		m_LevelExp += m_NextExp;
		m_SwordAttack = m_protSwordAattack * std::pow(m_multiply, m_weaponextend);
		m_SwordMattack = m_protSwordMattack * std::pow(m_multiply, m_weaponextend);
	}
	SetWeaponStatus();
	m_NextExp -= ep;
}

void Equipment::KariPlusExp(const int& exp)
{
	m_kariExp = m_Exp;
	m_kariNextExp = m_NextExp;                              
	m_kariLevelExp = m_LevelExp;                          
	m_kariSwordMattack = m_SwordMattack;                          
	m_kariSwordAttack = m_SwordAttack;                        
	m_kariweaponextend = m_weaponextend;
	m_kariAttack = m_kariSwordAttack;
	m_kariMattack = m_kariSwordMattack;
	int ep = exp;
	//経験値を加算
	m_kariExp += ep;
	//レベルアップに必要な累計経験値がプレイヤーの累計経験値より大きくなるまでループ
	while (m_kariLevelExp <= m_kariExp) {
		ep -= m_kariNextExp;
		m_kariweaponextend += 1;
		m_kariNextExp = (int)((1 + (float)(m_kariweaponextend * m_kariweaponextend * 0.1f)) * m_explevel1);
		m_kariLevelExp += m_kariNextExp;
		m_kariSwordAttack = m_protSwordAattack * std::pow(m_multiply, m_kariweaponextend);
		m_kariSwordMattack = m_protSwordMattack * std::pow(m_multiply, m_kariweaponextend);
		m_kariAttack = m_kariSwordAttack;
		m_kariMattack = m_kariSwordMattack;
	}
	if (m_ishaveability) {
		for (int i = 0; i < m_abilitylist.size(); i++) {
			m_kariAttack += m_abilitylist[i]->GetPower();
			m_kariMattack += m_abilitylist[i]->GetMpower();
		}
	}
	m_kariNextExp -= ep;
}