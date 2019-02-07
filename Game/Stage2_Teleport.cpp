#include "stdafx.h"
#include "Stage2_Teleport.h"


Stage2_Teleport::Stage2_Teleport()
{
}

Stage2_Teleport::~Stage2_Teleport()
{
	delete m_skinModelRender;
}

bool Stage2_Teleport::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/stage2_teleport.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_staticobject.CreateMesh(*m_skinModelRender);
	return true;
}

void Stage2_Teleport::Update()
{

}