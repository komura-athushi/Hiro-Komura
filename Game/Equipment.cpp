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
	std::vector <int> abilitygroupnumberlist;
	int abilitynumber = 0;
	int totalabilityweight = m_gamedata->GetTotalWeight();
	if (m_SwordId != 0) {
		for (int i = 0; i < m_slotlimitnumber; i++) {
			int rn = rand() % 100 + 1;
			if (rn < m_probability[abilitynumber]) {
				//ウェイト値を求めます
				int rn2 = rand() % totalabilityweight;
				if (m_ishaveability) {
					int i = 0;
					while (true) {
						bool isgroup = false;
						for (int j = 0; j < abilitynumber; j++) {
							if (abilitygroupnumberlist[j] == m_gamedata->GetAbility(i)->GetGroup()) {
								isgroup = true;
								i++;
								break;
							}
						}
						if (!isgroup) {
							if ((rn2 -= m_gamedata->GetAbility(i)->GetWeight()) >= 0) {
								i++;
							}
							else {
								m_abilitylist.push_back(m_gamedata->GetAbility(i));
								abilitygroupnumberlist.push_back(m_gamedata->GetAbility(i)->GetGroup());
								abilitynumber++;
								totalabilityweight -= m_gamedata->GetTotalGroupWeight(m_gamedata->GetAbility(i)->GetGroup());
								m_ishaveability = true;
								break;
							}
						}
					}
				}
				else {
					int i = 0;
					while (true) {
						if ((rn2 -= m_gamedata->GetAbility(i)->GetWeight()) >= 0) {
							i++;
						}
						else {
							m_abilitylist.push_back(m_gamedata->GetAbility(i));
							abilitygroupnumberlist.push_back(m_gamedata->GetAbility(i)->GetGroup());
							abilitynumber++;
							totalabilityweight -= m_gamedata->GetTotalGroupWeight(m_gamedata->GetAbility(i)->GetGroup());
							m_ishaveability = true;
							break;
						}
					}
				}
			}
			else {
				break;
			}
		}
		SetWeaponStatus();
	}
	m_explevel1 = float(m_explevel1) * (1.0f + m_exprarity * float(m_Rarity));
	m_NextExp = m_explevel1;
	m_LevelExp = m_NextExp;
	int attack = 0, mattack = 0, hp = 0, pp = 0;
	if (m_ishaveability) {
		for (int i = 0; i < m_abilitylist.size(); i++) {
			attack += m_abilitylist[i]->GetPower();
			mattack += m_abilitylist[i]->GetMpower();
			hp += m_abilitylist[i]->GetHP();
			pp += m_abilitylist[i]->GetPP();
		}
	}
	m_ability = new Ability(attack, mattack, hp, pp);
}

Equipment::~Equipment()
{
	delete m_ability;
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
	m_kariNextExp -= ep;
}