#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "Ground.h"
#include "Town.h"
#include "PlayerStatus.h"
#include "Oni.h"
#include "Boss.h"
#include "Boss3.h"
#include "DropItem.h"
#include "DropMaterial.h"
#include "IEnemy.h"
#include "GameData.h"
#include "Fade.h"
#include "MainSound.h"
#include "Teleport.h"
#include "GameClear.h"
Game::Game()
{
}

Game::~Game()
{
	delete m_player;
	delete m_gamecamera;
	delete m_ground;
	delete m_lig;
	delete m_shadowMap;
	QueryGOs<Oni>(L"Enemy", [&](Oni* oni)
	{
		delete oni;
		return true;
	});
	QueryGOs<Boss>(L"Enemy", [&](Boss* boss)
	{
		delete boss;
		return true;
	});
	QueryGOs<Boss3>(L"Enemy", [&](Boss3* boss2)
	{
		delete boss2;
		return true;
	});
	QueryGOs<DropItem>(L"DropItem", [&](DropItem* dropitem)
	{
		delete dropitem;
		return true;
	});
	QueryGOs<DropMaterial>(L"DropMaterial", [&](DropMaterial* dropmaterial)
	{
		delete dropmaterial;
		return true;
	});
	QueryGOs<Teleport>(L"Teleport", [&](Teleport* tl)
	{
		delete tl;
		return true;
	});
}

bool Game::Start()
{
	m_gamedata = FindGO<GameData>(L"GameData");
	//ディレクションライトを設定
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,-1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	m_shadowMap = new ShadowMapHandler;

	//初期化

	m_shadowMap->Init(8048,//解像度(幅

		8048,//解像度(高さ

		m_lig->GetDirection()//ライトの方向

	);

	m_shadowMap->SetArea({ 20000.0f,20000.0f,20000.0f });//シャドウマップの範囲(Zがライトの方向)

	m_shadowMap->SetTarget({ 0.0f,0.0f,0.0f });//シャドウマップの範囲の中心位置*/
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
			m_player->SetName(L"Player");
			m_player->SetRotation(objData.rotation);
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"enemy") == true) {
			//スケルトン
			//プレイヤーのインスタンスを生成する。
			Oni* oni = new Oni;
			oni->SetPosition(objData.position);
			oni->SetOldPosition(objData.position);
			oni->SetName(L"Enemy");
			//後で削除するのでリストに積んで記憶しておく。
			m_oniList.push_back(oni);
			oni->SetPlayer(m_player);
			oni->SetGame(this);
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"boss") == true) {
			//ボス
			//プレイヤーのインスタンスを生成する。
			Boss* boss = new Boss;
			boss->SetPosition(objData.position);
			boss->SetOldPosition(objData.position);
			boss->SetName(L"Enemy");
			boss->SetPlayer(m_player);
			boss->SetStage1(this);
			//フックした場合はtrueを返す。
			return true;
		}
		return false;
	});
	//仮ここから
	//ボス3
	//プレイヤーのインスタンスを生成する。
	Boss3* boss3 = new Boss3;
	boss3->SetName(L"Enemy");
	//boss3->SetPlayer(m_player);
	//ここまで
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	MainSound* ms = FindGO<MainSound>();
	if (m_stagenumber == 1) {
		ms->SetBGM(2);
	}
	else if (m_stagenumber == 2) {
		ms->SetBGM(3);
	}
	else if (m_stagenumber == 3) {
		ms->SetBGM(4);
	}
	//SE
	SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/start.wav");
	se->Play(); //再生(再生が終わると削除されます)
	se->SetVolume(2.6f);
	return true;
}

void Game::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			if (m_gamedata->GetisGameClear() && !m_gamedata->GetisGameEnd()) {
				GameClear* gameclear = new GameClear;
				delete this;
			}
			else {
				Town* town = new Town;
				delete this;
			}
		}
	}
	else {
		//プレイヤーがゲームオーバーあるいはゲームクリアで拠点に遷移
		if (m_player->GetTransScene()) {
			if (m_player->GetGameClear()) {
				m_gamedata->SetClear(m_stagenumber - 1);
				if (m_stagenumber == 3 && !m_gamedata->GetisGameClear()) {
					m_gamedata->SetGameClear();
				}
			}
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	
}

