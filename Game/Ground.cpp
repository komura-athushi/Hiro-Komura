#include "stdafx.h"
#include "Ground.h"
Ground::Ground()
{
	
}

Ground::~Ground()
{
	delete m_skinModelRender;
}
bool Ground::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender2 = new GameObj::CSkinModelRender;
	//ステージによって読み込むfbxファイルを変えます
	switch (m_stage) {
	case 0:
		m_skinModelRender->Init(L"Resource/modelData/ground.cmo");
		break;
	case 1:
		m_skinModelRender->Init(L"Resource/modelData/stage1_ground.cmo");
	}
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender2->Init(L"Resource/modelData/sky.cmo");
	m_scale = { 200.0f,200.0f,200.0f };
	m_skinModelRender2->SetPos(m_position);
	m_skinModelRender2->SetScale(m_scale);
	m_skinModelRender2->SetIsShadowCaster(false);
	m_staticobject.CreateMesh(*m_skinModelRender);
	m_staticobject2.CreateMesh(*m_skinModelRender2);
	return true;
}

void Ground::Update()
{
	
}

