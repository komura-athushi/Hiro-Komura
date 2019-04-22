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
	//該当の番号の素材のファイルを読み込む
	switch (m_state) {
	case GameData::enMaterial_Wood:
		m_skinModelRender->Init(L"Resource/modelData/wood.cmo");
		break;
	case GameData::enMaterial_Ishi:
		m_skinModelRender->Init(L"Resource/modelData/ishi.cmo");
		break;
	case GameData::enMaterial_Brick:
		m_skinModelRender->Init(L"Resource/modelData/brick.cmo");
		break;
	default:
		break;
	}
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRot(m_rotation);
	m_player = FindGO<Player>(L"Player");
	return true;
}

void DropMaterial::Update()
{
	m_degree += 200.0f * GetDeltaTimeSec();
	m_rotation.SetRotationDeg(CVector3::AxisY(), m_degree);
	m_skinModelRender->SetRot(m_rotation);
	//プレイヤーとの距離が一定以下になったらプレイヤーの所持素材に自身を追加する
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.Length() <= 80.0f) {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/get.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_sevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
		PlayerStatus* playerstatus = &PlayerStatus::GetInstance();
		//プレイヤーの所持素材に追加
		playerstatus->SetMaterial(m_state);
		delete this;
	}
}