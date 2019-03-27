#include "stdafx.h"
#include "Ground.h"
#include "GameData.h"
Ground::Ground()
{
	
}

Ground::~Ground()
{
	if (m_skinModelRender != nullptr) {
		delete m_skinModelRender;
	}
	delete m_skinModelRender2;
}

bool Ground::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	GameData* gamedata = FindGO<GameData>(L"GameData");
	//ステージによって読み込むfbxファイルを変えます
	switch (m_stage) {
	case 0:
		if (gamedata->GetTownLevel() == 0) {
			m_skinModelRender->Init(L"Resource/modelData/ground.cmo");
		}
		else if (gamedata->GetTownLevel() == 1) {
			m_skinModelRender->Init(L"Resource/modelData/ground2.cmo");
		}
		else if (gamedata->GetTownLevel() == 2) {
			m_skinModelRender->Init(L"Resource/modelData/ground3.cmo");
		}
		m_scale = { 1.0f,1.45f,1.0f };
		break;
	case 1:
		m_skinModelRender->Init(L"Resource/modelData/stage1_ground.cmo");
		break;
	case 2:
		m_skinModelRender->Init(L"Resource/modelData/stage2_ground.cmo");
		break;
	default:
		return true;
		break;
	}
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetRot(m_rotation);
	m_staticobject.CreateMesh(*m_skinModelRender);
	return true;
}

void Ground::Update()
{

}

