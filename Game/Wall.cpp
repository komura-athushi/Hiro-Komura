#include "stdafx.h"
#include "Wall.h"
#include "Boss.h"

Wall::Wall()
{
}


Wall::~Wall()
{
	delete m_skinModelRender;
}

bool Wall::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/wall.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	//モデルの描画はしない
	m_skinModelRender->SetIsDraw(false);
	m_boss = FindGO<Boss>(L"Enemy");
	return true;
}

void Wall::Update()
{
	if (m_boss == nullptr) {
		m_boss = FindGO<Boss>(L"Enemy");
	}
	//ボスが行動開始したら静的オブジェクトを生成する
	else if(m_boss != nullptr && !m_iscreatstaticobject) {
		if (m_boss->GetisStart()) {
			m_staticobject.CreateMesh(*m_skinModelRender);
			m_iscreatstaticobject = true;
		}
	}
}
