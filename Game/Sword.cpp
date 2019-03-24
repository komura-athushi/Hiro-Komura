#include "stdafx.h"
#include "Sword.h"
#include "Player.h"
#include "GameData.h"
Sword::Sword()
{
}

Sword::~Sword()
{
	delete m_skinModelRender; m_skinModelRender = nullptr;
}

bool Sword::Start()
{
	//初期状態だとデフォルトの剣を読み込む
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/Sword.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRot(m_qRot);
	m_player = FindGO<Player>(L"Player");
	return true;
}

void Sword::Update()
{
	if (m_SwordId != m_SwordId2) {
		m_SwordId = m_SwordId2;
		m_delete = false;
	}
	if (m_skinModelRender) {
		m_skinModelRender->SetPos(m_player->GetSwordPosition());
		m_skinModelRender->SetRot(m_player->GetSwordRot());
		m_skinModelRender->SetScale(m_scale);
	}
	if (!m_delete) {
		delete m_skinModelRender; 
		m_skinModelRender = nullptr;
		m_delete = true;
		m_switch = true;
	}
	else if(m_switch){
		m_skinModelRender = new GameObj::CSkinModelRender;
		//受け取った番号によって読み込むファイルを変える
		switch (m_SwordId) {
		case GameData::enWeapon_Sword:
			m_skinModelRender->Init(L"Resource/modelData/Sword.cmo");
			break;
		case GameData::enWeapon_FireSword:
			m_skinModelRender->Init(L"Resource/modelData/FireSword.cmo");
			break;
		case GameData::enWeapon_IceSword:
			m_skinModelRender->Init(L"Resource/modelData/IceSword.cmo");
			break;
		case GameData::enWeapon_WindSword:
			m_skinModelRender->Init(L"Resource/modelData/WindSword.cmo");
			break;
		case GameData::enWeapon_GreatSword:
			m_skinModelRender->Init(L"Resource/modelData/GreatSword.cmo");
			break;
		case GameData::enWeapon_BlueLightSword:
			m_skinModelRender->Init(L"Resource/modelData/BlueLightSword.cmo");
			break;
		case GameData::enWeapon_BattleReadyBlade:
			m_skinModelRender->Init(L"Resource/modelData/BattleReadyBlade.cmo");
			break;
		case GameData::enWeapon_AncientWarriorBlade:
			m_skinModelRender->Init(L"Resource/modelData/AncientWarriorBlade.cmo");
			break;
		case GameData::enWeapon_LegendalySword:
			m_skinModelRender->Init(L"Resource/modelData/excaliburmorgan.cmo");
			break;
		}
		m_switch = false;
		//プレイヤー側で計算した座標と回転を反映させます
		m_skinModelRender->SetPos(m_player->GetSwordPosition());
		m_skinModelRender->SetRot(m_player->GetSwordRot());
		m_skinModelRender->SetScale(m_scale);
	}
}