#include "stdafx.h"
#include "Stage2_Teleport.h"


Stage2_Teleport::Stage2_Teleport()
{
}

Stage2_Teleport::~Stage2_Teleport()
{
	delete m_skinModelRender;
	delete m_effect;
}

bool Stage2_Teleport::Start()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/stage2_teleport.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_staticobject.CreateMesh(*m_skinModelRender);
	m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/tornade/tornade.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,10.0f,12.0f });
	return true;
}

void Stage2_Teleport::Update()
{
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
}