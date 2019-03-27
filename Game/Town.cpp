#include "stdafx.h"
#include "Town.h"
#include "Ground.h"
#include "GameCamera.h"
#include "Player.h"
#include "Stage1_Teleport.h"
#include "Stage2_Teleport.h"
#include "Stage3_Teleport.h"
#include "Game.h"
#include "PlayerStatus.h"
#include "Cagliostro_view.h"
#include "Human.h"
#include "Merchant.h"
#include "GameData.h"
#include "Fade.h"
#include "MainSound.h"
Town::Town()
{
	
}


Town::~Town()
{
	//各インスタンスを削除
	delete m_player;
	delete m_human;
	delete m_merchant;
	delete m_ground;
	delete m_gamecamera;
	delete m_lig;
	delete m_CascadeShadowmap;
	delete m_stage1_teleport;
	if (m_stage2_teleport != nullptr) {
		delete m_stage2_teleport;
	}
	if (m_stage3_teleport != nullptr) {
		delete m_stage3_teleport;
	}
}

bool Town::Start()
{
	m_gamedata = FindGO<GameData>(L"GameData");
	//ディレクションライトを設定
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,-1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	m_CascadeShadowmap = new CascadeShadowHandler;

	//初期化

	m_CascadeShadowmap->Init(5,//分割数

		m_lig->GetDirection(),//ライトの方向

		0.1f//シャドウマップの範囲(メインカメラのFarにかかる係数です)

	);

	m_CascadeShadowmap->SetNear(30.0f);

	m_CascadeShadowmap->SetFar(50000.0f);
	BuildLevel();
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	MainSound* ms = FindGO<MainSound>();
	ms->SetBGM(MainSound::enBGM_Town);
	return true;
}

void Town::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			//m_stateによって次のモードを分岐させる
			if (m_state == enSt1) {
				Game* game = new Game;
				game->SetStageNumber(enSt1);
				delete this;
			}
			else if (m_state == enSt2) {
				Game* game = new Game;
				game->SetStageNumber(enSt2);
				delete this;
 			}
			else if (m_state == enSt3) {
				Game* game = new Game;
				game->SetStageNumber(enSt3);
				delete this;
			}
			else if (m_state == enCga) {
				Cagliostro_view* cag = new Cagliostro_view;
				delete this;
			}
			else {
				Town* town = new Town;
				delete this;
			}
		}
	}
	else {
		//プレイヤーとステージ1に遷移するオブジェクトの距離を計算
		CVector3 pos = m_player->GetPosition() - m_stage1_teleport->GetPosition();
		CVector3 pos2 = {1000.0f,1000.0f,1000.0f};
		CVector3 pos3 = { 1000.0f,1000.0f,1000.0f };
		if (m_gamedata->GetTownLevel() >= 1 && m_stage2_teleport != nullptr) {
			pos2 = m_player->GetPosition() - m_stage2_teleport->GetPosition();
		}
		if (m_gamedata->GetTownLevel() >= 2 && m_stage3_teleport != nullptr) {
			pos3 = m_player->GetPosition() - m_stage3_teleport->GetPosition();
		}
		//距離が一定以下ならステージ1に遷移する
		if (pos.LengthSq() <= 100.0f*100.0f) {
			m_state = enSt1;
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		//距離が一定以下ならステージ1に遷移する
		else if (pos2.LengthSq() <= 100.0f*100.0f) {
			m_state = enSt2;
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		//距離が一定以下ならステージ1に遷移する
		else if (pos3.LengthSq() <= 100.0f*100.0f) {
			m_state = enSt3;
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		//拠点に居る時にSTARTボタンを押すとカリオストロちゃん☆モードに遷移する
		else if (Pad(0).GetDown(enButtonBack)) {
			m_state = enCga;
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		//街を再構築
		else if (m_developtown) {
			m_state = enTown;
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}

void Town::BuildLevel()
{
	//レベルを構築する。
	const wchar_t* levelname = nullptr;
	//街のレベルにより読み込むレベルファイルを決定する
	switch (m_gamedata->GetTownLevel()) {
	case 0:
		levelname = L"Asset/level/town00.tkl";
		break;
	case 1:
		levelname = L"Asset/level/town01.tkl";
		break;
	case 2:
		levelname = L"Asset/level/town02.tkl";
		break;
	}
	m_level.Init(levelname, [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"ground") == true) {
			m_ground = new Ground;
			m_ground->SetStage(0);
			m_ground->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"ground2") == true) {
			m_ground = new Ground;
			m_ground->SetStage(0);
			m_ground->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"ground3") == true) {
			m_ground = new Ground;
			m_ground->SetStage(0);
			m_ground->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"stage1_teleport") == true) {
			//Starオブジェクト。
			m_stage1_teleport = new Stage1_Teleport;
			m_stage1_teleport->SetPosition(objData.position);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"stage2_teleport") == true) {
			//Starオブジェクト。
			m_stage2_teleport = new Stage2_Teleport;
			m_stage2_teleport->SetPosition(objData.position);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"stage3_teleport") == true) {
			//Starオブジェクト。
			m_stage3_teleport = new Stage3_Teleport;
			m_stage3_teleport->SetPosition(objData.position);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"human") == true) {
			m_human = new Human;
			m_human->SetPosition(objData.position);
			m_human->SetName(L"Human");
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"merchant") == true) {
			m_merchant = new Merchant;
			m_merchant->SetPosition(objData.position);
			m_merchant->SetRotation(objData.rotation);
			m_merchant->SetName(L"Merchant");
			//フックした場合はtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"unityChan") == true) {
			//Unityちゃん。
			//プレイヤーのインスタンスを生成する。
			m_player = new Player;
			m_player->SetPosition(objData.position);
			m_player->SetRotation(objData.rotation);
			m_player->SetName(L"Player");
			//フックした場合はtrueを返す。
			return true;
		}
		return false;
	});
}

