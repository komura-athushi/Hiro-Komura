#include "stdafx.h"
#include "DropItem.h"
#include "Weapon.h"
#include "Player.h"
#include "PlayerStatus.h" 
#include "GameData.h"
#include "Equipment.h"
const float DropItem::m_height = 30.0f;
const float DropItem::m_height_weapon = 10.0f;
DropItem::DropItem()
{
}


DropItem::~DropItem()
{
	delete m_skinModelRender;
	if (!m_issetweapon) {
		delete m_equipment;
	}
}

bool DropItem::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	if (m_isweapon) {
		//ドロップさせる武器の番号を決めます
		m_state = 0;
		int type = Weapon::m_raritynumber[m_rarity];
		int rn = int(float(100 / type));
		int randm = rand() % 100 + 1;
		for (int i = 0; i < type; i++) {
			if (i*rn <= randm && randm < (i + 1)*rn) {
				m_number = i;
			}
		}
		for (int i = 0; i < m_rarity; i++) {
			m_state += Weapon::m_raritynumber[i];
		}
		m_state += m_number;
		//武器の番号によって読み込むfbxファイルを決めます
		switch (m_state) {
		case GameData::enWeapon_Sword:
			m_skinModelRender->Init(L"Resource/modelData/Sword_drop.cmo");
			break;
		case GameData::enWeapon_FireSword:
			m_skinModelRender->Init(L"Resource/modelData/FireSword_drop.cmo");
			break;
		case GameData::enWeapon_IceSword:
			m_skinModelRender->Init(L"Resource/modelData/IceSword_drop.cmo");
			break;
		case GameData::enWeapon_WindSword:
			m_skinModelRender->Init(L"Resource/modelData/WindSword_drop.cmo");
			break;
		case GameData::enWeapon_GreatSword:
			m_skinModelRender->Init(L"Resource/modelData/GreatSword_drop.cmo");
			break;
		case GameData::enWeapon_BlueLightSword:
			m_skinModelRender->Init(L"Resource/modelData/BlueLightSword_drop.cmo");
			break;
		case GameData::enWeapon_BattleReadyBlade:
			m_skinModelRender->Init(L"Resource/modelData/BattleReadyBlade_drop.cmo");
			break;
		case GameData::enWeapon_AncientWarriorBlade:
			m_skinModelRender->Init(L"Resource/modelData/AncientWarriorBlade_drop.cmo");
			break;
		case GameData::enWeapon_LegendalySword:
			m_skinModelRender->Init(L"Resource/modelData/excaliburmorgan_drop.cmo");
			break;
		}
		m_position.y += m_height_weapon;
		//該当の番号の武器のデータを生成します
		m_equipment = new Equipment(m_state);
	}
	else {
		//武器でなかった場合、メセタを生成します
		m_skinModelRender->Init(L"Resource/modelData/meseta.cmo");
		m_position.y += m_height;
		m_issetweapon = true;
	}
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRot(m_rotation);
	m_player = FindGO<Player>(L"Player");
	return true;
}

void DropItem::Update()
{
	//毎フレーム回転させます
	m_degree += 200.0f * GetDeltaTimeSec();
	m_rotation.SetRotationDeg(CVector3::AxisY(), m_degree);
	m_skinModelRender->SetRot(m_rotation);
	//プレイヤーとの距離が一定以下になったらプレイヤーの所持武器に自身を追加する、あるいはメセタの額を加算する
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.Length() <= 80.0f) {
		PlayerStatus* playerstatus = &PlayerStatus::GetInstance();
		if (m_isweapon) {
			//自身が武器の場合プレイヤーに追加
			playerstatus->SetWeapon(m_equipment);
			m_issetweapon = true;
		}
		else {
			//設定したメセタの額をプレイヤーに追加
			playerstatus->AddMeseta(m_meseta);
		}
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/get.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_sevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
		delete this;
	}
}