#include "stdafx.h"
#include "DropMaterial.h"
#include "Material.h"
#include "Player.h"
#include "PlayerStatus.h"
DropMaterial::DropMaterial()
{
}


DropMaterial::~DropMaterial()
{
	delete m_skinModelRender;
}

bool DropMaterial::Start()
{
	//ドロップさせる武器の番号を決めます
	m_state = 0;
	int type = Material::m_raritynumber[m_rarity];
	int rn = int(float(100 / type));
	int randm = rand() % 100 + 1;
	for (int i = 0; i < type; i++) {
		if (i*rn <= randm && randm < (i + 1)*rn) {
			m_number = i;
		}
	}
	for (int i = 0; i < m_rarity; i++) {
		m_state += Material::m_raritynumber[i];
	}
	m_state += m_number;
	m_skinModelRender = new GameObj::CSkinModelRender;
	switch (m_state) {
	case 0:
		m_skinModelRender->Init(L"Resource/modelData/wood.cmo");
		break;
	case 1:
		m_skinModelRender->Init(L"Resource/modelData/ishi.cmo");
		break;
	case 2:
		m_skinModelRender->Init(L"Resource/modelData/brick.cmo");
		break;
	default:
		break;
	}
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_player = FindGO<Player>(L"Player");
	return true;
}

void DropMaterial::Update()
{
	//プレイヤーとの距離が一定以下になったらプレイヤーの所持武器に自身を追加する
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.Length() <= 80.0f) {
		PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
		playerstatus->SetMaterial(m_state);
		delete this;
	}
}