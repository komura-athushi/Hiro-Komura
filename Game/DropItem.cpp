#include "stdafx.h"
#include "DropItem.h"
#include "Weapon.h"
#include "Player.h"
#include "PlayerStatus.h"
DropItem::DropItem()
{
}


DropItem::~DropItem()
{
	delete m_skinModelRender;
}

bool DropItem::Start()
{
	//ドロップさせる武器の番号を決めます
	/*m_state = 0;
	int type = Weapon::m_raritynumber[m_rarity];
	int rn = int(float(100 / type));
	int randm = rand() % 100+1;
	for (int i = 0; i < type; i++) {
		if (i*rn <= randm && randm < (i + 1)*rn) {
			m_number = i;
		}
	}
	for (int i = 0; i < m_rarity; i++) {
		m_state += Weapon::m_raritynumber[i];
	}
	m_state += m_number;*/
	m_skinModelRender = new GameObj::CSkinModelRender;
	//武器の番号によって読み込むfbxファイルを決めます
	/*switch (m_state) {
	case 1:
		m_skinModelRender->Init(L"Resource/modelData/FireSword.cmo");
		break;
	case 2:
		m_skinModelRender->Init(L"Resource/modelData/IceSword.cmo");
		break;
	case 3:
		m_skinModelRender->Init(L"Resource/modelData/WindSword.cmo");
		break;
	case 4:
		m_skinModelRender->Init(L"Resource/modelData/GreatSword.cmo");
		break;
	case 5:
		m_skinModelRender->Init(L"Resource/modelData/BlueLightSword.cmo");
		break;
	}*/
	m_skinModelRender->Init(L"Resouse/modelData/meseta.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_player = FindGO<Player>(L"Player");
	return true;
}

void DropItem::Update()
{
	//プレイヤーとの距離が一定以下になったらプレイヤーの所持武器に自身を追加する
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.Length() <= 80.0f) {
		PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
		//playerstatus->SetWeapon(m_state);
		playerstatus->AddMeseta(m_meseta);
		delete this;
	}
}