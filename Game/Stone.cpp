#include "stdafx.h"
#include "Stone.h"


Stone::Stone()
{
}


Stone::~Stone()
{
	delete m_skinModelRender;
}

bool Stone::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/stone.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_staticobject.CreateMesh(*m_skinModelRender);
	return true;
}

void Stone::Update()
{

}