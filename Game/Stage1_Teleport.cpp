#include "stdafx.h"
#include "Stage1_Teleport.h"


Stage1_Teleport::Stage1_Teleport()
{
}

Stage1_Teleport::~Stage1_Teleport()
{
	delete m_skinModelRender;
}

bool Stage1_Teleport::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/stage1_teleport.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_staticobject.CreateMesh(*m_skinModelRender);
	return true;
}

void Stage1_Teleport::Update()
{

}