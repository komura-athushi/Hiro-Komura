#include "stdafx.h"
#include "Kurage3.h"
#include "Player.h"
//cppでエネミーのレア度ごとのドロップ率を設定
const int Kurage3::m_dropChances[Weapon::m_HighestRarity] = { 0,50,0,0,0,0,0 };
const int Kurage3::m_dropmaterialChances[Material::m_HighestRarity] = { 30.0f,0.0f,0.0f };
Kurage3::Kurage3() :IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{
}


Kurage3::~Kurage3()
{
	delete m_skinModelRender;
}

bool Kurage3::Start()
{
	IEnemy::CCollision(m_position, m_collisionheight, m_r);
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/kurage3.cmo");
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	pos.y += m_collisionheight;
	m_staticobject.CreateSphere(pos, rot, m_r);
	m_protposition = m_position;
	return true;
}

void Kurage3::Update()
{
	Chase();
	if (!IEnemy::m_death) {
		m_skinModelRender->SetPos(m_position);
		IEnemy::SetCCollision(m_position, m_collisionheight);
		CQuaternion rot;
		CVector3 pos = m_position;
		pos.y += m_collisionheight;
		m_staticobject.SetPositionAndRotation(pos, rot);
	}
	else {
		m_dethtimer += m_frame * GetDeltaTimeSec();
		if (m_dethtimer > m_dethtime) {
			delete this;
		}
	}
}

void Kurage3::Chase()
{
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.LengthSq() < m_attackdistance) {
		m_state = enState_Attack;
	}
	if (pos.LengthSq() < m_chasedistance) {
		switch (m_state) {
		case enState_Chase:
			if (m_chasetimer >= m_chasetime) {
				CVector3 pos = m_player->GetPosition() - m_position;
				pos.Normalize();
				pos *= m_movespeedmultiply;
				m_movespeed = pos;
				m_chasetimer = 0.0f;
			}
			m_chasetimer += m_frame * GetDeltaTimeSec();
			m_movetimer += m_frame * GetDeltaTimeSec();
			if (m_movetimer >= m_movetime) {
				m_state = enState_Pose;
				m_chasetimer = 0.0f;
				m_movetimer = 0.0f;
			}
			break;
		case enState_Pose:
			m_stoptimer += m_frame * GetDeltaTimeSec();
			m_movespeed = CVector3::Zero();
			if (m_stoptimer >= m_stoptime) {
				m_stoptimer = 0.0f;
				m_state = enState_Chase;
			}
			break;
		case enState_Attack:
			m_movespeed = CVector3::Zero();
			m_attacktimer += m_frame * GetDeltaTimeSec();
			if (m_attacktimer >= m_attacktime && !m_isaria) {
				Aria();
				m_attacktimer = 0.0f;
				m_isaria = true;
			}
			else if (m_attacktimer >= m_attacktime / 2 && m_isaria) {
				Attack();
				m_attacktimer =0.0f;
				m_isaria = false;
			}
			break;
		}
	}
	else {
		CVector3 pos = m_protposition - m_position;
		if (pos.LengthSq() > 100.0f * 100.0f) {
			pos.Normalize();
			pos *= m_movespeedmultiply;
			m_movespeed = pos;
		}
		else {
			m_movespeed = CVector3::Zero();
		}
	}
	if (IEnemy::m_damage) {
		m_state = enState_Pose;
		m_stoptimer = 0.0f;
		m_movetimer = 0.0f;
		m_attacktimer = 0.0f;
		m_isaria = false;
		IEnemy::m_damage = false;
	}
	m_position += m_movespeed * GetDeltaTimeSec() * m_frame;
}

void Kurage3::Aria()
{

}

void Kurage3::Attack()
{

	m_state = enState_Pose;
	m_stoptimer = 0.0f;
}