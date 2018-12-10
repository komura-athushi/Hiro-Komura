#include "stdafx.h"
#include "House.h"


House::House()
{
}


House::~House()
{
	delete m_skinModelRender;
}

bool House::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/house.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRot(m_rotation);
	m_staticobject.CreateMesh(*m_skinModelRender);
	return true;
}

void House::Update()
{

}
