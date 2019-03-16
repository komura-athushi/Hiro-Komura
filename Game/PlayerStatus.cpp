#include "stdafx.h"
#include "PlayerStatus.h"
#include "Weapon.h"
#include "Magic.h"
#include "Player.h"
#include "Town.h"
PlayerStatus::PlayerStatus()
{
}

PlayerStatus::~PlayerStatus()
{
}

bool PlayerStatus::Start()
{
	//最初の武器だけ所持状況をtrueに設定する
	m_equipmentlist.push_back(new Equipment(0));
	m_NextExp = m_Level * (m_Level + 1) * (m_Level + 4);
	m_LevelExp += m_NextExp;
	m_MaxHP = m_ProtHP + m_Level * (m_Level + 34) * (m_Level + 100) / 100;
	m_MaxPP = m_ProtPP + m_Level * (m_Level + 10) / 20;
	m_Power = m_ProtPower + m_Level * (m_Level + 10);
	m_Clever = m_ProtMpower + m_Level * (m_Level + 10);
	SetWeaponStatus();
	SetMagicStatus();
	//該当するddsファイルを読み込んでおく
	m_spritenamelist.push_back(L"Resource/sprite/sword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/firesword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/icesword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/windsword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/greatsword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/bluelightsword.dds");
	m_spritenamelist.push_back(L"Resource/sprite/battlereadyblade.dds");
	m_spritenamelist.push_back(L"Resource/sprite/ancientwarriorblade.dds");
	m_spritenamelist.push_back(L"Resource/sprite/excaliburmorgan.dds");
	m_cursor.Init(L"Resource/sprite/cursor.dds");
	CSprite* sprite = new CSprite;
	sprite->Init(m_spritenamelist[0]);
	m_spritelist.push_back(sprite);
	m_NextExp = m_Level * (m_Level + 1) * (m_Level + 2) * 5 - 10;
	m_LevelExp = m_Level * (m_Level + 1) * (m_Level + 2) * 5 - 10;
	return true;
}

void PlayerStatus::Update()
{
	//LSBボタンを押すと全部武器所持状態に移行
	if (Pad(0).GetDown(enButtonLSB)) {
		Town* town = FindGO<Town>();
		if (town == nullptr) {
			for (int i = 1; i < GameData::enWeapon_num; i++) {
				m_equipmentlist.push_back(new Equipment(i));
				CSprite* sprite = new CSprite;
				sprite->Init(m_spritenamelist[i]);
				m_spritelist.push_back(sprite);
			}
		}
		for (int i = 0; i < GameData::enMaterial_num; i++) {
			m_havemateriallist[i] = 100;
		}
		for (int i = 0; i < m_gamedata->m_stagenumber; i++) {
			//m_gamedata->SetClear(i);
		}
		m_MaxPP = 1000;
		m_havemeseta = 10000;
		Player* player = FindGO<Player>(L"Player");
		if (player != nullptr) {
			player->SetPP(m_MaxPP);
		}
	}
}

void PlayerStatus::PlusExp(const int& exp)
{
	int ep = exp;
	//経験値を加算
	m_Exp += ep;
	//レベルアップに必要な累計経験値がプレイヤーの累計経験値より大きくなるまでループ
	while (m_LevelExp <= m_Exp) {
		ep -= m_NextExp;
		m_Level += 1;
		m_NextExp = m_Level * (m_Level + 1) * (m_Level + 2) * 5 - 10;
		m_LevelExp += m_NextExp;
		m_MaxHP = m_ProtHP + m_Level * (m_Level + 34) * (m_Level + 100) / 100;
		m_MaxPP = m_ProtPP + m_Level * (m_Level + 10) / 20;
		m_Power = m_ProtPower + m_Level * (m_Level + 10);
		m_Clever = m_ProtMpower + m_Level * (m_Level +10);
		m_Attack = m_Power + m_SwordAttack;
		m_Mattack = m_Clever + m_SwordMattack;
		m_levelup = true;
	}
	m_NextExp -= ep;
}

void PlayerStatus::SetWeaponStatus()
{
	m_SwordMattack = m_equipmentlist[m_SwordId]->GetMatk();
	m_SwordAttack = m_equipmentlist[m_SwordId]->GetAtk();
	m_MagicId = m_equipmentlist[m_SwordId]->GetMagicId();
	m_Rarity = m_equipmentlist[m_SwordId]->GetRarity();
	m_SwordName = m_equipmentlist[m_SwordId]->GetName();
	m_Mattack = m_Clever + m_SwordMattack;
	m_Attack = m_Power + m_SwordAttack;
	m_ability = m_equipmentlist[m_SwordId]->GetAbility();
}

void PlayerStatus::SetMagicStatus()
{
	m_MagicName = m_equipmentlist[m_SwordId]->GetMagicName();
	m_DamageRate = m_equipmentlist[m_SwordId]->GetDamageRate();
	m_PPCost = m_equipmentlist[m_SwordId]->GetPPCost();
}

bool PlayerStatus::GetWeapon(int number)
{
	int equipnumber = m_equipmentlist.size();
	//引数が武器の番号の範囲を超えていたら関数の処理を終了させる
	if (number < 0 || number > equipnumber - 1) {
		return false;
	}
	//左ボタン押した時の処理
	if (m_SwordId > number) {
		if (m_SwordId == 0) {
			return false;
		}
		else {
			m_SwordId--;
			SetWeaponStatus();
			SetMagicStatus();
			return true;
		}
	}
	//右ボタンを押したときの処理
	else if (m_SwordId < number) {
		if (m_SwordId == equipnumber) {
			return false;
		}
		else {
			m_SwordId++;
			SetWeaponStatus();
			SetMagicStatus();
			return true;
		}
	}
	return false;
}

void PlayerStatus::SetWeapon(Equipment* number)
{
	m_equipmentlist.push_back(number);
	CSprite* sprite = new CSprite;
	sprite->Init(m_spritenamelist[number->GetId()]);
	m_spritelist.push_back(sprite);

}

void PlayerStatus::PostRender()
{
	//ステを文字表示
	/*wchar_t output[256];
	swprintf_s(output, L"木   %d\n石   %d\nレンガ  %d\nメセタ  %d\n", m_havemateriallist[0], m_havemateriallist[1], m_havemateriallist[2],m_havemeseta);
	//swprintf_s(output, L"x   %f\ny   %f\nz  %f\nw   %f\n", m_swordqRot.x, m_swordqRot.y, m_swordqRot.z, m_swordqRot.w);
	m_font.DrawScreenPos(output, { 00.0f,200.0f }, CVector4::White(),
		CVector2::One(),
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		1.0f
	);*/
	//武器のアイコン表示
	CVector2 pos = m_position;
	pos.x -= m_SwordId * 64.0f;
	for (int i = 0; i < m_equipmentlist.size(); i++) {
		m_spritelist[i]->DrawScreenPos(pos, m_scale, CVector2::Zero(),
			0.0f,
			CVector4::White(),
			DirectX::SpriteEffects_None,
			1.0f);
		pos.x += 64.0f;
	}
	m_cursor.DrawScreenPos(m_position, m_scale, CVector2::Zero(),
		0.0f,
		CVector4::White(),
		DirectX::SpriteEffects_None,
		0.9f);

}

void PlayerStatus::WeaponStrengthen(const int& number)
{
	if (m_havemeseta >= m_equipmentlist[number]->GetCost()) {
		m_havemeseta -= m_equipmentlist[number]->GetCost();
		m_equipmentlist[number]->Strengthen();
		if (m_SwordId == number) {
			SetWeaponStatus();
			SetMagicStatus();
		}
	}
}

void PlayerStatus::SetStatus()
{
	SetWeaponStatus();
	SetMagicStatus();
}

void PlayerStatus::DeleteEquipment(const int& number)
{
	Equipment* eq = m_equipmentlist[number];
	CSprite* sp = m_spritelist[number];
 	m_equipmentlist.erase(m_equipmentlist.begin() + number);
	m_spritelist.erase(m_spritelist.begin() + number);
	delete eq;
	delete sp;
	if (m_SwordId > number) {
		m_SwordId -= 1;
	}
}