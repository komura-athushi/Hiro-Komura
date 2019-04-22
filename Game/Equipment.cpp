#include "stdafx.h"
#include "Equipment.h"
#include "GameData.h"
const float Equipment::m_multiply = 1.15f;
const float Equipment::m_costmultiply = 1.2f;
Equipment::Equipment(const int& number):m_SwordId(number)
{
	//GameDataクラスを経由して各ステータスを取得する
	m_gamedata = &GameData::GetInstance();
	//それぞれのステータスを設定
	SetWeaponStatus();
	SetMagicStatus();
	//付与されたアビリティのグループを記憶jしておく
	std::vector <int> abilitygroupnumberlist;
	//付与されたアビリティの数
	int abilitynumber = 0;
	//全アビリティのウェイトをトータル
	int totalabilityweight = m_gamedata->GetTotalWeight();
	if (m_SwordId != 0) {
		//最高3回まで特殊能力を付与します
		for (int i = 0; i < m_slotlimitnumber; i++) {
			int rn = rand() % 100 + 1;
			//規定の値より乱数が大きければ特殊能力を付与します、2、3回目は確率が低くなります
			if (rn < m_probability[abilitynumber]) {
				//ウェイト値を求めます
				int rn2 = rand() % totalabilityweight;
				//特殊能力を既に付与しているかしていないかで処理を分けます
				if (m_ishaveability) {
					int i = 0;
					while (true) {
						bool isgroup = false;
						for (int j = 0; j < abilitynumber; j++) {
							//既に取得している特殊能力のグループは避けるようにします
							if (abilitygroupnumberlist[j] == m_gamedata->GetAbility(i)->GetGroup()) {
								isgroup = true;
								i++;
								break;
							}
						}
						if (!isgroup) {
							//ウェイト値を各特殊能力のウェイト値分だけ減算します
							if ((rn2 -= m_gamedata->GetAbility(i)->GetWeight()) > 0) {
								i++;
							}
							else {
								//ウェイト値が0以下になればその時の特殊能力を付与します
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
						//ウェイト値を各特殊能力のウェイト値分だけ減算します
						if ((rn2 -= m_gamedata->GetAbility(i)->GetWeight()) > 0) {
							i++;
						}
						else {
							//ウェイト値が0以下になればその時の特殊能力を付与します
							m_abilitylist.push_back(m_gamedata->GetAbility(i));
							abilitygroupnumberlist.push_back(m_gamedata->GetAbility(i)->GetGroup());
							abilitynumber++;
							totalabilityweight -= m_gamedata->GetTotalGroupWeight(m_gamedata->GetAbility(i)->GetGroup());
							//始めて特殊能力を付与した場合、特殊能力取得フラグをオンにします
							m_ishaveability = true;
							break;
						}
					}
				}
			}
			//特殊能力付与に失敗した場合、その時点でループを抜けます
			else {
				break;
			}
		}
	}
	//レベルアップに必要な経験値を設定します
	m_NextExp = pow(2.0f, m_Rarity) * m_weaponextend * (m_weaponextend + 9) / 2;
	m_LevelExp = m_NextExp;
	int attack = 0, mattack = 0, hp = 0, pp = 0;
	//付与された特殊能力の値をまとめたAbilityクラスを生成します
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
	//GameDataクラスから該当の番号の武器のデータを取得します
	if (m_weaponextend == 1) {
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
	//GameDataクラスから該当の番号の魔法のデータを取得します
	m_magic = m_gamedata->GetMagic(m_MagicId);
	m_MagicName = m_magic->GetName();
	m_DamageRate = m_magic->GetDamageRate();
	m_PPCost = m_magic->GetPPCost();
}

const wchar_t* Equipment::GetAbilityName(const int& number)
{
	//特殊能力が付与されていない場合、"無し"と表記します
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
		m_NextExp = pow(2.0f, m_Rarity) * m_weaponextend * (m_weaponextend + 9) / 2;
		m_LevelExp += m_NextExp;
		m_SwordAttack = m_protSwordAattack * (1 + (m_weaponextend + 4) * (m_weaponextend - 1) * 0.01) + 5 * (m_weaponextend - 1);
		m_SwordMattack = m_protSwordMattack * (1 + (m_weaponextend + 4) * (m_weaponextend - 1) * 0.01) + 5 * (m_weaponextend - 1);
		SetWeaponStatus();
		if (m_gamedata->GetWeaponLimitLv() == m_weaponextend) {
			return;
		}
	}
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
		m_kariNextExp = pow(2.0f, m_Rarity) * m_kariweaponextend * (m_kariweaponextend + 9) / 2;
		m_kariLevelExp += m_kariNextExp;
		m_kariSwordAttack = m_protSwordAattack * (1 + (m_kariweaponextend + 4) * (m_kariweaponextend - 1) * 0.01) + 5 * (m_kariweaponextend - 1);
		m_kariSwordMattack = m_protSwordMattack * (1 + (m_kariweaponextend + 4) * (m_kariweaponextend - 1) * 0.01) + 5 * (m_kariweaponextend - 1);
		m_kariAttack = m_kariSwordAttack;
		m_kariMattack = m_kariSwordMattack;
		if (m_gamedata->GetWeaponLimitLv() == m_kariweaponextend) {
			return;
		}
	}
	m_kariNextExp -= ep;
}

int Equipment::GetMaterialExp(const int& id) const
{
	//強化する予定の武器と自身が同じ種類の武器だった場合、素材としての経験値を二倍にします
	if(m_SwordId == id) {
		return pow(2.0f, m_Rarity) * (20 + 5 * m_weaponextend) * 2.0f;
	}
	else {
		return pow(2.0f, m_Rarity) * (20 + 5 * m_weaponextend);
	}
}