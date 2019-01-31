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
		return;
	}
	//武器のアイコン表示
	CVector2 pos = m_aiconposition;
	wchar_t output[256];
	swprintf_s(output, L"どの武器を強化しますか？\n");
	m_font.DrawScreenPos(output, { 00.0f,00.0f }, CVector4::White());
	for (int i = 0; i < GameData::enWeapon_num; i++) {
		if (m_playerstatus->GetisHaveWeapon(i)) {
			m_sprite[i].DrawScreenPos(pos, m_aiconscale);
		}
		if (m_playerstatus->GetSwordId() == i) {
			m_cursor.DrawScreenPos(pos, m_aiconscale, CVector2::Zero(),
				0.0f,
				CVector4::White(),
				DirectX::SpriteEffects_None,
				0.4f);
		}
		pos.y += 64.0f;
	}
}