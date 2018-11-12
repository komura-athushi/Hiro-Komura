#include "stdafx.h"
#include "Sword.h"


Sword::Sword()
{
}


Sword::~Sword()
{
	delete m_skinModelRender;
}

bool Sword::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/Sword.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRot(m_qRot);
	//m_ghostobject.CreateMesh(*m_skinModelRender);
	//m_ghostobject.SetPosition(m_position);
	return true;
}

void Sword::Update()
{
	m_position += m_movespeed;
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetRot(m_qRot);
	m_skinModelRender->SetScale(m_scale);
	//m_ghostobject.SetPosition(m_position);
}