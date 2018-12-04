#include "stdafx.h"
#include "Stage1.h"
#include "Player.h"
#include "GameCamera.h"
#include "Ground.h"
#include "Town.h"
#include "PlayerStatus.h"
#include "Oni.h"
#include "Boss.h"
Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	delete m_player;
	delete m_gamecamera;
	delete m_ground;
	delete m_lig;
	/*for (auto& oni : m_oniList) {
		delete oni;
	}*/
<<<<<<< HEAD
	delete boss;

=======
	//m_player = FindGO<Player>(L"Player");
>>>>>>> 9d1aea755c2c8ef1254aea0bc83dfb8791247c2c
}

bool Stage1::Start()
{
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	//レベルを構築する。
	m_level.Init(L"Asset/level/stage1.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"stage1_ground") == true) {
			m_ground = new Ground;
			m_ground->SetStage(1);
			m_ground->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"unityChan") == true) {
			//Unityちゃん。
			//プレイヤーのインスタンスを生成する。
			m_player = new Player;
			m_player->SetPosition(objData.position);
			m_player->SetPlayerStatus(m_playerstatus);
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"enemy") == true) {
			//スケルトン
			//プレイヤーのインスタンスを生成する。
			//Starオブジェクト。
			Oni* oni = new Oni;
			oni->SetPosition(objData.position);
			oni->SetOldPosition(objData.position);
			oni->SetName(L"Skelton");
			//後で削除するのでリストに積んで記憶しておく。
			m_oniList.push_back(oni);
			oni->SetPlayer(m_player);
			oni->SetStage1(this);
			//フックした場合はtrueを返す。
			return true;
		}
		//else if (objData.EqualObjectName(L"boss") == true) {
		//	//ボス
		//	//プレイヤーのインスタンスを生成する。
		//	//Bossオブジェクト。
		//	boss = new Boss;
		//	boss->SetPosition(objData.position);
		//	boss->SetOldPosition(objData.position);
		//	boss->SetPlayer(m_player);
		//	boss->SetStage1(this);
		//	//フックした場合はtrueを返す。
		//	return true;
		//}
		return false;
	});
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	//仮に生成しております
	boss = new Boss;
	boss->SetPlayer(m_player);
	return true;
}

void Stage1::Update()
{
	if (m_player->GetGameOver()) {
		Town* town = new Town;
		town->SetPlayerStatus(m_playerstatus);
		delete this;
	}
}