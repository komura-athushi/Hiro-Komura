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
	return true;
}

void Sword::Update()
{
	if (m_SwordId != m_SwordId2) {
		m_SwordId = m_SwordId2;
		m_delete = false;
	}
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetRot(m_qRot);
	m_skinModelRender->SetScale(m_scale);
	if (!m_delete) {
		delete m_skinModelRender;
		m_delete = true;
		m_switch = true;
	}
	else if(m_switch){
		m_skinModelRender = new GameObj::CSkinModelRender;
		switch (m_SwordId) {
		case 0:
			m_skinModelRender->Init(L"Resource/modelData/Sword.cmo");
			break;
		case 1:
			m_skinModelRender->Init(L"Resource/modelData/FireSword.cmo");
			break;
		case 2:
			m_skinModelRender->Init(L"Resource/modelData/IceSword.cmo");
			break;
		case 3:
			m_skinModelRender->Init(L"Resource/modelData/WindSword.cmo");
			break;
		case 4:
			m_skinModelRender->Init(L"Resource/modelData/GreatSword.cmo");
			break;
		case 5:
			m_skinModelRender->Init(L"Resource/modelData/BlueLightSword.cmo");
			break;
		}
		m_switch = false;
	}
}