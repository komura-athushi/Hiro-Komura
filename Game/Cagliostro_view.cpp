#include "stdafx.h"
#include "Cagliostro_view.h"
#include "Ground.h"
#include "GameCamera.h"
#include "Player.h"
#include "PlayerStatus.h"
#include "Town.h"
#include "Fade.h"
Cagliostro_view::Cagliostro_view()
{

}

Cagliostro_view::~Cagliostro_view()
{
	delete m_player;
	delete m_ground;
	delete m_gamecamera;
	delete m_lig;
	delete m_shadowMap;
}

bool Cagliostro_view::Start()
{
	//ディレクションライトを設定
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,-1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	m_shadowMap = new ShadowMapHandler;

	//初期化

	m_shadowMap->Init(12048,//解像度(幅

		12048,//解像度(高さ

		m_lig->GetDirection()//ライトの方向

	);

	m_shadowMap->SetArea({ 20000.0f,20000.0f,20000.0f });//シャドウマップの範囲(Zがライトの方向)

	m_shadowMap->SetTarget({ 0.0f,0.0f,0.0f });//シャドウマップの範囲の中心位置*/
	m_ground = new Ground;
	m_ground->SetStage(-1);
	m_player = new Player;
	m_player->SetPosition(m_position);
	m_player->Cagliostro();
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	return true;
}

void Cagliostro_view::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			Town* town = new Town;
			delete this;
		}
	}
	else {
		if (Pad(0).GetButton(enButtonBack)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}


