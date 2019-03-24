#include "stdafx.h"
#include "Kurage2.h"
#include "Player.h"
#include "Enemy_Ice.h"
//cpp�ŃG�l�~�[�̃��A�x���Ƃ̃h���b�v����ݒ�
const int Kurage2::m_dropChances[Weapon::m_HighestRarity] = { 5,15,0,0,0,0,0 };
const int Kurage2::m_dropmaterialChances[Material::m_HighestRarity] = { 20.0f,0.0f,0.0f };
Kurage2::Kurage2() :IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{
}


Kurage2::~Kurage2()
{
	delete m_skinModelRender;
}

bool Kurage2::Start()
{
	IEnemy::CCollision(m_position, m_collisionheight, m_r);
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/kurage2.cmo");
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	pos.y += m_collisionheight;
	m_staticobject.CreateSphere(pos, rot, m_r);
	m_protposition = m_position;
	return true;
}

void Kurage2::Update()
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

void Kurage2::Chase()
{
	CVector3 pos = m_protposition - m_position;
	if (pos.LengthSq() > m_chasedistance) {
		if (pos.LengthSq() > 100.0f * 100.0f) {
			pos.Normalize();
			pos *= m_movespeedmultiply;
			m_movespeed = pos;
		}
		else {
			m_movespeed = CVector3::Zero();
		}
	}
	else {
		CVector3 pos = m_player->GetPosition() - m_position;
		if (pos.LengthSq() < m_chasedistance) {
			switch (m_state) {
			case enState_Chase:
				if (m_chasetimer >= m_chasetime) {
					CVector3 pos = CVector3::Zero();
					int rn = rand();
					if (rn % 10 > 5) {
						pos.x += m_movespeedmultiply;
					}
					else {
						pos.x -= m_movespeedmultiply;
					}
					if (rn % 23 > 12) {
						pos.z += m_movespeedmultiply;
					}
					else {
						pos.z -= m_movespeedmultiply;
					}
					m_movespeed = pos;
					m_chasetimer = 0.0f;
				}
				m_chasetimer += m_frame * GetDeltaTimeSec();
				m_movetimer += m_frame * GetDeltaTimeSec()*(rand() % 2 + 1);
				if (m_movetimer >= m_movetime) {
					m_state = enState_Pose;
					m_chasetimer = 0.0f;
					m_movetimer = 0.0f;
					ChangeAttack();
				}
				break;
			case enState_Pose:
				m_stoptimer += m_frame * GetDeltaTimeSec()*(rand() %2 + 1);
				m_movespeed = CVector3::Zero();
				if (m_stoptimer >= m_stoptime) {
					m_stoptimer = 0.0f;
					m_state = enState_Chase;
					//ChangeAttack();
				}
				break;
			case enState_Attack:
				m_movespeed = CVector3::Zero();
				m_attacktimer += m_frame * GetDeltaTimeSec();
				if (m_attacktimer >= m_ariatime && !m_isaria) {
					Aria();
					m_attacktimer = 0.0f;
					m_isaria = true;
				}
				else if (m_attacktimer >= m_attacktime && m_isaria) {
					Attack();
					m_attacktimer = 0.0f;
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
	}
	/*if (IEnemy::m_damage) {
		m_state = enState_Pose;
		m_stoptimer = 0.0f;
		m_movetimer = 0.0f;
		m_attacktimer = 0.0f;
		m_isaria = false;
		IEnemy::m_damage = false;
	}*/
	m_position += m_movespeed * GetDeltaTimeSec() * m_frame;
}

void Kurage2::Aria()
{
	GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
	effect->Play(L"Asset/effect/Effects/efk/cast_ice.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
	effect->SetSpeed(2.0f);
	//SE
	SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/aria.wav");
	se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
	se->SetVolume(m_sevolume);
	//3D�Đ�
	se->SetPos(m_position);//���̈ʒu
	se->SetDistance(200.0f);//������������͈�
	se->Play(true); //��������true
}

void Kurage2::Attack()
{
	Enemy_Ice* ei = new Enemy_Ice;
	CVector3 pos = m_position + CVector3::AxisY() * 60.0f;
	CVector3 pos2 = (m_player->GetPosition() + CVector3::AxisY()*40.0f) - pos;
	pos2.Normalize();
	ei->SetPosition(pos);
	ei->SetMoveSpeed(pos2);
	ei->SetAttack(m_Attack);
	ei->SetDeleteTime(m_magicdeletetime);
	//ei->SetSpeed(m_magicspeed);
	m_state = enState_Pose;
	m_stoptimer = 0.0f;
	m_movetimer = 0.0f;
	m_attacktimer = 0.0f;
}

void Kurage2::ChangeAttack()
{
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.LengthSq() < m_attackdistance) {
		m_state = enState_Attack;
	}
	m_stoptimer = 0.0f;
	m_movetimer = 0.0f;
	m_attacktimer = 0.0f;
}