#include "stdafx.h"
#include "PlayerStatus.h"
#include "Weapon.h"
#include "Magic.h"
PlayerStatus::PlayerStatus()
{
}

PlayerStatus::~PlayerStatus()
{
}

bool PlayerStatus::Start()
{
	for (int i = 0; i < GameData::enWeapon_num; i++) {
		m_weaponinventorylist.push_back({ Equipment(i),false });
		m_haveweaponmateriallist.push_back(0);
	}
	m_weaponinventorylist[0].s_ishave = true;
	GetWeaponStatus();
	GetMagicStatus();
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
	//レベルごとに必要な累計経験値がプレイヤーの累計経験値より大きくなるまでループ
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
		m_Mattack = m_Clever + m_SwordMattack;
	}
		m_NextExp -= ep;
}

void PlayerStatus::GetWeaponStatus()
{
	m_weapon = m_gamedata->GetWeapon(m_SwordId);
	m_SwordMattack = m_weapon->GetMatk();
	m_SwordAttack = m_weapon->GetAtk();
	m_MagicId = m_weapon->GetMagicId();
	m_Rarity = m_weapon->GetRarity();
	m_SwordName = m_weapon->GetName();
	m_Mattack = m_Clever + m_SwordMattack;
	m_Attack = m_Power + m_SwordAttack;
}

void PlayerStatus::GetMagicStatus()
{
	m_magic = m_gamedata->GetMagic(m_MagicId);
	m_MagicName = m_magic->GetName();
	m_DamageRate = m_magic->GetDamageRate();
	m_PPCost = m_magic->GetPPCost();
}

bool PlayerStatus::GetWeapon(int number)
{
	//引数が武器の番号の範囲を超えていたら関数の処理を終了させる
	if (number<0 || number>GameData::enWeapon_num-1) {
		return false;
	}
	//左ボタン押した時の処理
	if (m_SwordId > number) {
		for (int i = number; i >= 0; i--) {
			if (m_weaponinventorylist[i].s_ishave) {
				m_SwordId = i;
				GetWeaponStatus();
				GetMagicStatus();
				return true;
			}
		}
	}
	//右ボタンを押したときの処理
	else if (m_SwordId < number) {
		for (int i = number; i < GameData::enWeapon_num; i++) {
			if (m_weaponinventorylist[i].s_ishave) {
				m_SwordId = i;
				GetWeaponStatus();
				GetMagicStatus();
				return true;
			}
		}
	}
	return false;
}

void PlayerStatus::PostRender()
{
	wchar_t output[256];
	swprintf_s(output, L"木   %d\n石   %d\nレンガ  %d\nそざい  %d\n", m_havemateriallist[0], m_havemateriallist[1], m_havemateriallist[2],m_haveweaponmateriallist[m_SwordId]);
	//swprintf_s(output, L"x   %f\ny   %f\nz  %f\nw   %f\n", m_swordqRot.x, m_swordqRot.y, m_swordqRot.z, m_swordqRot.w);
	m_font.DrawScreenPos(output, { 00.0f,200.0f }, CVector4::White());
}