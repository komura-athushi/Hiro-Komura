#include "stdafx.h"
#include "Merchant.h"
#include "Player.h"
#include "PlayerStatus.h"
Merchant::Merchant()
{
}


Merchant::~Merchant()
{
	delete m_skinModelRender;
	for (int i = 0; i < m_playerstatus->GetEquipmentNumber(); i++) {
		delete m_spritelist[i];
		delete m_spritefont[i];
	}
}

bool Merchant::Start()
{
	//アニメーションファイルをロード
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/idle.tka", true);
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/zunko.cmo", m_animClip, enAnimationClip_num);
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	//m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_protrotation = m_rotation;
	m_skinModelRender->SetRot(m_rotation);
	m_playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
	m_gamedata = FindGO<GameData>(L"GameData");
	m_equipmentnumber = m_playerstatus->GetEquipmentNumber();
 	for (int i = 0; i < m_equipmentnumber; i++) {
		CSprite* sprite = new CSprite;
		sprite->Init(m_playerstatus->GetSpriteName(m_playerstatus->GetWeaponNumber(i)));
		m_spritelist.push_back(sprite);
		m_spritefont.push_back(new CFont);
	}
	m_cursor.Init(L"Resource/sprite/cursor.dds");
	m_sprite2.Init(L"Resource/sprite/window.dds");
	m_sprite3.Init(L"Resource/sprite/upgradewindow.dds");
	return true;
}

void Merchant::Update()
{
	if (m_player == nullptr) {
		m_player = FindGO<Player>();
		return;
	}
	Turn();
	m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
}

void Merchant::Turn()
{
	CVector3 pos = m_player->GetPosition() - m_position;
	//プレイヤーが一定距離以内に居たらプレイヤーの方向を向くようにする
	if (pos.Length() <= 300.0f) {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(pos.x, pos.z));
	}
	//プレイヤーが一定距離以外に居たら回転をもとに戻す
	else if (pos.Length() >= 1500.0f) {
		m_rotation = m_protrotation;
	}
	m_skinModelRender->SetRot(m_rotation);
}

void Merchant::PostRender()
{
	if (!m_talk) {
		m_button = false;
		m_swordid = m_playerstatus->GetSwordId();
		return;
	}
	wchar_t output[256];
	swprintf_s(output, L"どの武器を強化しますか？\n");
	//武器のアイコン表示
	CVector2 pos = m_aiconposition;
	pos.y -= m_swordid * 70.0f;
	for (int i = 0; i < m_playerstatus->GetEquipmentNumber(); i++) {
			m_spritelist[i]->DrawScreenPos(pos, m_aiconscale);
			wchar_t output[30];
			if (m_playerstatus->GetEuipment(i).GetLv() != 5) {
				swprintf_s(output, L"武器Lv %d\n強化費用 %dメセタ\n", m_playerstatus->GetEuipment(i).GetLv(), m_playerstatus->GetEuipment(i).GetCost());
			}
			else {
				swprintf_s(output, L"武器Lv %d\n", m_playerstatus->GetEuipment(i).GetLv());
			}
			CVector2 pos2 = pos;
			pos2.x += 100.0f;
			m_spritefont[i]->DrawScreenPos(output, pos2, CVector4::White(), {0.7f,0.7f});
			pos.y += 70.0f;
	}
	m_cursor.DrawScreenPos(m_aiconposition, m_aiconscale, CVector2::Zero(),
		0.0f,
		CVector4::White(),
		DirectX::SpriteEffects_None,
		0.4f);
	int number = m_swordid;
	if (Pad(0).GetButton(enButtonUp) && m_button) {
		number--;
		m_button = false;
	}
	else if (Pad(0).GetButton(enButtonDown) && m_button) {
		number++;
		m_button = false;
	}
	else {
		if (!Pad(0).GetButton(enButtonUp) && !Pad(0).GetButton(enButtonDown) && !Pad(0).GetButton(enButtonB)) {
			m_button = true;
		}
	}
	//上ボタン
	if (m_swordid > number) {
		if (m_swordid != 0) {
			m_swordid = number;
		}
	}
	//下ボタン
	else if (m_swordid < number) {
		if (m_swordid != m_playerstatus->GetEquipmentNumber()-1) {
			m_swordid = number;
		}
	}
	if (Pad(0).GetButton(enButtonB) && m_button) {
		if (m_playerstatus->GetEuipment(m_swordid).GetLv() == 5) {
		}
		else {
			m_playerstatus->WeaponStrengthen(m_swordid);
			m_player->WeaponStatus();
			m_player->MagicStatus();
		}
		m_button = false;
	}
	m_font.DrawScreenPos(output, { 300.0f,450.0f }, CVector4::White(), { 0.6f,0.6f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
	m_sprite2.DrawScreenPos({ 290.0f,440.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
	m_sprite3.DrawScreenPos({ 780.0f,0.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.8f);
}
