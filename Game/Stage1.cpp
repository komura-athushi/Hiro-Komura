#include "stdafx.h"
#include "Stage1.h"
#include "Player.h"
#include "GameCamera.h"
#include "Ground.h"
#include "Town.h"
#include "PlayerStatus.h"
#include "Oni.h"
#include "Boss.h"
#include "DropItem.h"
#include "DropMaterial.h"
#include "IEnemy.h"
#include "GameData.h"
#include "Fade.h"
#include "MainSound.h"
Stage1::Stage1()
{
}

Stage1::~Stage1()
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
}

bool Stage1::Start()
{
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
			oni->SetName(L"Enemy");
			//後で削除するのでリストに積んで記憶しておく。
			m_oniList.push_back(oni);
			oni->SetPlayer(m_player);
			oni->SetStage1(this);
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"boss") == true) {
			//スケルトン
			//プレイヤーのインスタンスを生成する。
			//Starオブジェクト。
			/*Boss* boss = new Boss;
			boss->SetPosition(objData.position);
			boss->SetOldPosition(objData.position);
			boss->SetName(L"Enemy");
			boss->SetPlayer(m_player);
			boss->SetStage1(this);*/
			//フックした場合はtrueを返す。
			return true;
		}
		return false;
	});
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	MainSound* ms = FindGO<MainSound>();
	ms->SetBGM(2);
	//SE
	SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/start.wav");
	se->Play(); //再生(再生が終わると削除されます)
	se->SetVolume(2.6f);
	return true;
}

void Stage1::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			Town* town = new Town;
			delete this;
		}
	}
	else {
		//プレイヤーがゲームオーバーあるいはゲームクリアで拠点に遷移
		if (m_player->GetTransScene()) {
			if (m_player->GetGameClear()) {
				GameData* gamedata = FindGO<GameData>(L"GameData");
				gamedata->SetClear(0);
			}
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	
}

