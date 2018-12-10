#include "stdafx.h"
#include "Town.h"
#include "Ground.h"
#include "GameCamera.h"
#include "Player.h"
#include "Stone.h"
#include "House.h"
#include "Stage1_Teleport.h"
#include "Stage1.h"
#include "PlayerStatus.h"
#include "Cagliostro_view.h"
#include "Human.h"
Town::Town()
{
	
}


Town::~Town()
{
	delete m_player;
	delete m_human;
	delete m_ground;
	delete m_gamecamera;
	delete m_lig;
	delete m_stage1_teleport;
	for (auto& stone : m_stoneList) {
		delete stone;
	}
	for (auto& house : m_houseList) {
		delete house;
	}
}

bool Town::Start()
{
	//ディレクションライトを設定
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	//レベルを構築する。
	m_level.Init(L"Asset/level/town00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"ground") == true) {
			m_ground = new Ground;
			m_ground->SetStage(0);
			m_ground->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"stone") == true) {
			//Starオブジェクト。
			Stone* stone = new Stone;
			stone->SetPosition(objData.position);
			//後で削除するのでリストに積んで記憶しておく。
			m_stoneList.push_back(stone);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"house") == true) {
			//Starオブジェクト。
			House* house = new House;
			house->SetPosition(objData.position);
			house->SetRotation(objData.rotation);
			//後で削除するのでリストに積んで記憶しておく。
			m_houseList.push_back(house);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"stage1_teleport") == true) {
			//Starオブジェクト。
			m_stage1_teleport = new Stage1_Teleport;
			m_stage1_teleport->SetPosition(objData.position);
			//フックしたのでtrueを返す。
			return true;
		}
		else if (objData.EqualObjectName(L"human") == true) {
			//Human
			m_human = new Human;
			m_human->SetPosition(objData.position);
			m_player->SetName(L"Human");
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
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	return true;
}

void Town::Update()
{
	//プレイヤーとステージ1に遷移するオブジェクトの距離を計算
	CVector3 pos= m_player->GetPosition() - m_stage1_teleport->GetPosition();
	//距離が一定以下ならステージ1に遷移する
	if (pos.Length() <= 100.0f) {
		Stage1* stage1 = new Stage1;
		delete this;
	}
	//拠点に居る時にSTARTボタンを押すとカリオストロちゃん☆モードに遷移する
	if (Pad(0).GetDown(enButtonStart)) {
		Cagliostro_view* cag = new Cagliostro_view;
		delete this;
	}
}
