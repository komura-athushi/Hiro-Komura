#include "stdafx.h"
#include "DropItem.h"

DropItem::DropItem()
{
}


DropItem::~DropItem()
{
	delete m_skinModelRender;
}

bool DropItem::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	switch (m_state) {
	case 1:
		m_skinModelRender->Init(L"Resource/modelData/WindSword.cmo");
		break;
	case 2:
		m_skinModelRender->Init(L"Resource/modelData/IceSword.cmo");
		break;
	case 3:
		m_skinModelRender->Init(L"Resource/modelData/FireSword.cmo");
		break;
	case 4:
		m_skinModelRender->Init(L"Resource/modelData/GreatSword.cmo");
		break;
	case 5:
		m_skinModelRender->Init(L"Resource/modelData/BlueLightSword.cmo");
		break;
	}
	m_skinModelRender->SetPos(m_position);
	return true;
}

void DropItem::Update()
{

}