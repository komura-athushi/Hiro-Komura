#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "Ground.h"
#include "Town.h"
#include "PlayerStatus.h"
#include "Skeleton1.h"
#include "Skeleton2.h"
#include "Boss.h"
#include "Boss2.h"
#include "Boss3.h"
#include "DropItem.h"
#include "DropMaterial.h"
#include "IEnemy.h"
#include "GameData.h"
#include "Fade.h"
#include "MainSound.h"
#include "Teleport.h"
#include "GameClear.h"
#include "Kurage.h"
#include "Kurage2.h"
#include "Kurage3.h"
#include "Kurage4.h"
#include "Kurage5.h"
#include "Wall.h"
Game::Game()
{
}

Game::~Game()
{
	//なんか色々消す
	delete m_player;
	delete m_gamecamera;
	delete m_ground;
	delete m_lig;
	delete m_CascadeShadowmap;
	QueryGOs<Skeleton1>(L"Enemy", [&](Skeleton1* oni)
	{
		delete oni;
		return true;
	});
	QueryGOs<Skeleton2>(L"Enemy", [&](Skeleton2* sk2)
	{
		delete sk2;
		return true;
	});
	QueryGOs<Kurage>(L"Enemy", [&](Kurage* kg)
	{
		delete kg;
		return true;
	});
	QueryGOs<Kurage2>(L"Enemy", [&](Kurage2* kg2)
	{
		delete kg2;
		return true;
	});
	QueryGOs<Kurage3>(L"Enemy", [&](Kurage3* kg3)
	{
		delete kg3;
		return true;
	});
	QueryGOs<Kurage4>(L"Enemy", [&](Kurage4* kg4)
	{
		delete kg4;
		return true;
	});
	QueryGOs<Kurage5>(L"Enemy", [&](Kurage5* kg5)
	{
		delete kg5;
		return true;
	});
	QueryGOs<Boss>(L"Enemy", [&](Boss* boss)
	{
		delete boss;
		return true;
	});
	QueryGOs<Boss2>(L"Enemy", [&](Boss2* boss2)
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
	delete m_wall;
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
	//カスケードシャドウ、カメラとの距離に応じてシャドウの解像度を変える？とかなんとか
	m_CascadeShadowmap = new CascadeShadowHandler;

	//初期化

	m_CascadeShadowmap->Init(5,//分割数

		m_lig->GetDirection(),//ライトの方向

		0.1f//シャドウマップの範囲(メインカメラのFarにかかる係数です)

	);

	m_CascadeShadowmap->SetNear(30.0f);

	m_CascadeShadowmap->SetFar(50000.0f);
	//レベルを構築する。
	const wchar_t* levelpath = nullptr;
	//ステージの番号によって読み込むレベルファイルを変える
	switch (m_stagenumber) {
	case 1:
		levelpath = L"Asset/level/stage1.tkl";
			break;
	case 2:
		levelpath = L"Asset/level/stage2.tkl";
			break;
	case 3:
		levelpath = L"Asset/level/stage2.tkl";
	}
	//エネミーごとに番号を付ける
	int number = 0;
	m_level.Init(levelpath, [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"stage1_ground") == true) {
			m_ground = new Ground;
			m_ground->SetStage(1);
			m_ground->SetPosition(objData.position);
			m_ground->SetRot(objData.rotation);
			m_ground->SetScale(objData.scale);
			return true;
		}
		else if (objData.EqualObjectName(L"stage2_ground") == true) {
			m_ground = new Ground;
			m_ground->SetStage(2);
			m_ground->SetPosition(objData.position);
			m_ground->SetRot(objData.rotation);
			m_ground->SetScale(objData.scale);
			return true;
		}
		else if (objData.EqualObjectName(L"wall") == true) {
			m_wall = new Wall;
			m_wall->SetPosition(objData.position);
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
		else if (objData.EqualObjectName(L"skeleton1") == true) {
			//スケルトン
			//プレイヤーのインスタンスを生成する。
			Skeleton1* sk1 = new Skeleton1;
			sk1->SetPosition(objData.position);
			sk1->SetOldPosition(objData.position);
			sk1->SetRotation(objData.rotation);
			sk1->SetName(L"Enemy");
			sk1->SetPlayer(m_player);
			sk1->SetGame(this);
			sk1->SetNumber(number);
			number++;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"skeleton2") == true) {
			//スケルトン
			//プレイヤーのインスタンスを生成する。
			Skeleton2* sk2 = new Skeleton2;
			sk2->SetPosition(objData.position);
			sk2->SetOldPosition(objData.position);
			sk2->SetRotation(objData.rotation);
			sk2->SetName(L"Enemy");
			sk2->SetPlayer(m_player);
			sk2->SetGame(this);
			sk2->SetNumber(number);
			number++;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"kurage") == true) {
			//スケルトン
			//プレイヤーのインスタンスを生成する。
			Kurage* kr = new Kurage;
			kr->SetPosition(objData.position);
			kr->SetName(L"Enemy");
			//後で削除するのでリストに積んで記憶しておく。
			kr->SetPlayer(m_player);
			kr->SetNumber(number);
			number++;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"kurage2") == true) {
			//スケルトン
			//プレイヤーのインスタンスを生成する。
			Kurage2* kr2 = new Kurage2;
			kr2->SetPosition(objData.position);
			kr2->SetName(L"Enemy");
			//後で削除するのでリストに積んで記憶しておく。
			kr2->SetPlayer(m_player);
			kr2->SetGame(this);
			kr2->SetNumber(number);
			number++;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"kurage3") == true) {
			//スケルトン
			//プレイヤーのインスタンスを生成する。
			Kurage3* kr3 = new Kurage3;
			kr3->SetPosition(objData.position);
			kr3->SetName(L"Enemy");
			//後で削除するのでリストに積んで記憶しておく。
			kr3->SetPlayer(m_player);
			kr3->SetGame(this);
			kr3->SetNumber(number);
			number++;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"kurage4") == true) {
		//スケルトン
		//プレイヤーのインスタンスを生成する。
		Kurage4* kr4 = new Kurage4;
		kr4->SetPosition(objData.position);
		kr4->SetName(L"Enemy");
		//後で削除するのでリストに積んで記憶しておく。
		kr4->SetPlayer(m_player);
		kr4->SetGame(this);
		kr4->SetNumber(number);
		number++;
		//フックした場合はtrueを返す。
		return true;
		}
		else if (objData.EqualObjectName(L"kurage5") == true) {
		//スケルトン
		//プレイヤーのインスタンスを生成する。
		Kurage5* kr5 = new Kurage5;
		kr5->SetPosition(objData.position);
		kr5->SetName(L"Enemy");
		//後で削除するのでリストに積んで記憶しておく。
		kr5->SetPlayer(m_player);
		kr5->SetGame(this);
		kr5->SetNumber(number);
		number++;
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
			boss->SetNumber(number);
			/*Boss2* boss2 = new Boss2;
			boss2->SetPosition(objData.position);
			boss2->SetOldPosition(objData.position);
			boss2->SetName(L"Enemy");
			boss2->SetPlayer(m_player);
			boss2->SetNumber(number);*/
			number++;
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"boss2") == true) {
			//ボス
			//プレイヤーのインスタンスを生成する。
			Boss2* boss2 = new Boss2;
			boss2->SetPosition(objData.position);
			boss2->SetOldPosition(objData.position);
			boss2->SetName(L"Enemy");
			boss2->SetPlayer(m_player);
			boss2->SetNumber(number);
			number++;
			//フックした場合はtrueを返す。
			return true;
		}
		return false;
	});
	//仮ここから
	//ボス2
	//プレイヤーのインスタンスを生成する。
	/*Boss2* boss2 = new Boss2;
	boss2->SetName(L"Enemy");
	boss2->SetPlayer(m_player);*/
	//ここまで
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	//ステージに応じて流すBGMを変化させます
	MainSound* ms = FindGO<MainSound>();
	if (m_stagenumber == 1) {
		ms->SetBGM(MainSound::enBGM_Stage1);
	}
	else if (m_stagenumber == 2) {
		ms->SetBGM(MainSound::enBGM_Stage2);
	}
	else if (m_stagenumber == 3) {
		ms->SetBGM(MainSound::enBGM_Stage3);
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
		//プレイヤーのシーン遷移フラグがオンになればシーン遷移します
		if (m_player->GetTransScene()) {
			//プレイヤーのクリアフラグがオンになれば、GameDataのステージごとのクリアフラグをオンにします
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

