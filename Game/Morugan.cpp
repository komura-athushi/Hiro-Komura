#include "stdafx.h"
#include "Morugan.h"
#include "Player.h"

Morugan::Morugan()
{
}


Morugan::~Morugan()
{
	delete m_effect;
}

bool Morugan::Start()
{
    m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/morugan/morugan.efk", 1.0f, m_position, m_rotation, m_scale);
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	m_player = FindGO<Player>(L"Player");
	return true;
}

void Morugan::Update()
{
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), -atan2f(m_player->GetAttack().x, m_player->GetAttack().z));
	m_effect->SetRot(qRot);
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	if (!m_player->GetAria()) {
		delete this;
	}
}