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
	//武器の所持状況をすべてfalseに設定
	for (int i = 0; i < GameData::enWeapon_num; i++) {
		m_weaponinventorylist.push_back({ Equipment(i),false,0 });
	}
	//最初の武器だけ所持状況をtrueに設定する
	m_weaponinventorylist[0].s_ishave = true;
	SetWeaponStatus();
	SetMagicStatus();
	//該当するddsファイルを読み込んでおく
	m_sprite[0].Init(L"Resource/sprite/sword.dds");
	m_sprite[1].Init(L"Resource/sprite/firesword.dds");
	m_sprite[2].Init(L"Resource/sprite/icesword.dds");
	m_sprite[3].Init(L"Resource/sprite/windsword.dds");
	m_sprite[4].Init(L"Resource/sprite/greatsword.dds");
	m_sprite[5].Init(L"Resource/sprite/bluelightsword.dds");
	m_sprite[6].Init(L"Resource/sprite/battlereadyblade.dds");
	m_sprite[7].Init(L"Resource/sprite/ancientwarriorblade.dds");
	m_sprite[8].Init(L"Resource/sprite/excaliburmorgan.dds");
	m_cursor.Init(L"Resource/sprite/cursor.dds");
	return true;
}

void PlayerStatus::Update()
{
	//LSBボタンを押すと全部武器所持状態に移行
	if (Pad(0).GetDown(enButtonLSB)) {
		for (int i = 0; i < GameData::enWeapon_num; i++) {
			m_weaponinventorylist[i] = { Equipment(i),true};
		}
		for (int i = 0; i < GameData::enMaterial_num; i++) {
			m_havemateriallist[i] = 100;
		}
		for (int i = 0; i < m_gamedata->m_stagenumber; i++) {
			//m_gamedata->SetClear(i);
		}
		//PlusExp(1000000000);
	}
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
		m_NextExp = (int)((1 + (float)(m_Level*m_Level * 0.1f)) * 50);
		m_LevelExp += m_NextExp;
		m_Power += 5 + rand() % 3;
		m_Attack = m_Power + m_SwordAttack;
		m_MaxHP += 10;
		m_MaxPP += 10;
		m_Clever += 10;
		m_Attack = m_Power + m_SwordAttack;
		m_Mattack = m_Clever + m_SwordMattack;
		m_levelup = true;
	}
		m_NextExp -= ep;
}

void PlayerStatus::SetWeaponStatus()
{
	m_SwordMattack = m_weaponinventorylist[m_SwordId].s_equipment.GetMatk();
	m_SwordAttack = m_weaponinventorylist[m_SwordId].s_equipment.GetAtk();
	m_MagicId = m_weaponinventorylist[m_SwordId].s_equipment.GetMagicId();
	m_Rarity = m_weaponinventorylist[m_SwordId].s_equipment.GetRarity();
	m_SwordName = m_weaponinventorylist[m_SwordId].s_equipment.GetName();
	m_Mattack = m_Clever + m_SwordMattack;
	m_Attack = m_Power + m_SwordAttack;
}

void PlayerStatus::SetMagicStatus()
{
	m_MagicName = m_weaponinventorylist[m_SwordId].s_equipment.GetMagicName();
	m_DamageRate = m_weaponinventorylist[m_SwordId].s_equipment.GetDamageRate();
	m_PPCost = m_weaponinventorylist[m_SwordId].s_equipment.GetPPCost();
}

bool PlayerStatus::GetWeapon(int number)
{
	//引数が武器の番号の範囲を超えていたら関数の処理を終了させる
	if (number < 0 || number > GameData::enWeapon_num-1) {
		return false;
	}
	//左ボタン押した時の処理
	if (m_SwordId > number) {
		for (int i = number; i >= 0; i--) {
			if (m_weaponinventorylist[i].s_ishave) {
				m_SwordId = i;
				SetWeaponStatus();
				SetMagicStatus();
				return true;
			}
		}
	}
	//右ボタンを押したときの処理
	else if (m_SwordId < number) {
		for (int i = number; i < GameData::enWeapon_num; i++) {
			if (m_weaponinventorylist[i].s_ishave) {
				m_SwordId = i;
				SetWeaponStatus();
				SetMagicStatus();
				return true;
			}
		}
	}
	return false;
}

void PlayerStatus::SetWeapon(const int& number)
{
	if (m_weaponinventorylist[number].s_ishave) {
		m_havemeseta += m_weaponinventorylist[number].s_equipment.GetMeseta();
	}
	else {
		m_weaponinventorylist[number].s_ishave = true;
	}
}

void PlayerStatus::PostRender()
{
	//ステを文字表示
	wchar_t output[256];
	swprintf_s(output, L"木   %d\n石   %d\nレンガ  %d\nメセタ  %d\n", m_havemateriallist[0], m_havemateriallist[1], m_havemateriallist[2],m_havemeseta);
	//swprintf_s(output, L"x   %f\ny   %f\nz  %f\nw   %f\n", m_swordqRot.x, m_swordqRot.y, m_swordqRot.z, m_swordqRot.w);
	m_font.DrawScreenPos(output, { 00.0f,200.0f }, CVector4::White(),
		CVector2::One(),
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		1.0f
	);
	//武器のアイコン表示
	CVector2 pos = m_position;
	for (int i = 0; i < GameData::enWeapon_num; i++) {
		//所持状況がtrueなら該当する画像を表示する
		if (m_weaponinventorylist[i].s_ishave) {
			m_sprite[i].DrawScreenPos(pos, m_scale, CVector2::Zero(),
				0.0f,
				CVector4::White(),
				DirectX::SpriteEffects_None,
				1.0f);
			if (m_SwordId == i) {
				m_cursor.DrawScreenPos(pos, m_scale,CVector2::Zero(),
					0.0f,
					CVector4::White(),
					DirectX::SpriteEffects_None,
					0.9f);
			}
			pos.x += 64.0f;
		}
	}
}