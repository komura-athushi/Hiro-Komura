#include "stdafx.h"
#include "Cagliostro_view.h"
#include "Ground.h"
#include "GameCamera.h"
#include "Player.h"
#include "PlayerStatus.h"
#include "Town.h"
Cagliostro_view::Cagliostro_view()
{

}


Cagliostro_view::~Cagliostro_view()
{
	delete m_player;
	delete m_ground;
	delete m_gamecamera;
	delete m_lig;
}

bool Cagliostro_view::Start()
{
	m_lig = new GameObj::CDirectionLight;
	m_color = { 1.0f,1.0f,1.0f };
	m_color.Normalize();
	m_lig->SetDirection(m_color);
	m_lig->SetColor({ 1.0f, 1.0f, 1.0f });
	m_ground = new Ground;
	m_ground->SetStage(-1);
	m_player = new Player;
	m_player->SetPosition(m_position);
	m_player->SetPlayerStatus(m_playerstatus);
	m_player->Cagliostro();
	m_gamecamera = new GameCamera;
	m_gamecamera->SetPlayer(m_player);
	m_player->SetCamera(m_gamecamera);
	return true;
}

void Cagliostro_view::Update()
{
	if (Pad(0).GetButton(enButtonSelect)) {
		Town* town = new Town;
		town->SetPlayerStatus(m_playerstatus);
		delete this;
	}
}


