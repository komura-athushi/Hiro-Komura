#include "stdafx.h"
#include "Kurage4.h"
#include "Player.h"
#include "ShotMagic.h"
//cppでエネミーのレア度ごとのドロップ率を設定
const int Kurage4::m_dropChances[Weapon::m_HighestRarity] = { 0,25,5,0,0,0,0 };
const int Kurage4::m_dropmaterialChances[Material::m_HighestRarity] = { 20.0f,20.0f,0.0f };
Kurage4::Kurage4() :IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{
}


Kurage4::~Kurage4()
{
	delete m_skinModelRender;
}

bool Kurage4::Start()
{
	IEnemy::CCollision(m_position, m_collisionheight, m_r);
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/kurage4.cmo");
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	pos.y += m_collisionheight;
	m_staticobject.CreateSphere(pos, rot, m_r);
	m_protposition = m_position;
	return true;
}

void Kurage4::Update()
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

void Kurage4::Chase()
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
					ChangeAttack();
				}
				m_chasetimer += m_frame * GetDeltaTimeSec();
				m_movetimer += m_frame * GetDeltaTimeSec();
				if (m_movetimer >= m_movetime) {
					m_state = enState_Pose;
					m_chasetimer = 0.0f;
					m_movetimer = 0.0f;
					ChangeAttack();
				}
				break;
			case enState_Pose:
				m_stoptimer += m_frame * GetDeltaTimeSec();
				m_movespeed = CVector3::Zero();
				if (m_stoptimer >= m_stoptime) {
					m_stoptimer = 0.0f;
					m_state = enState_Chase;
					ChangeAttack();
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

void Kurage4::Aria()
{
	GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
	effect->Play(L"Asset/effect/Effects/efk/cast_fire.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
	effect->SetSpeed(2.0f);
	//SE
	SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/aria.wav");
	se->Play(); //再生(再生が終わると削除されます)
	se->SetVolume(m_sevolume);
	//3D再生
	se->SetPos(m_position);//音の位置
	se->SetDistance(200.0f);//音が聞こえる範囲
	se->Play(true); //第一引数をtrue
}

void Kurage4::Attack()
{
	CVector3 bulletPos = m_player->GetPosition() - m_position;
	bulletPos.Normalize();
	ShotMagic* sm = new ShotMagic;
	sm->SetPosition(m_position);
	sm->SetDirectionPlayer(bulletPos);
	sm->SetDamage(m_Attack);
	sm->SetEnemy();
	sm->SetId(1);
	sm->SetSpeed(0.7f);
	sm->SetDeleteTime(90.0f);
	m_state = enState_Pose;
	m_stoptimer = 0.0f;
	m_movetimer = 0.0f;
	m_attacktimer = 0.0f;
}

void Kurage4::ChangeAttack()
{
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.LengthSq() < m_attackdistance) {
		m_state = enState_Chase;
		int rn = rand() % 100;
		if (rn >= 80) {
			m_state = enState_Attack;
		}
	}
	m_stoptimer = 0.0f;
	m_movetimer = 0.0f;
	m_attacktimer = 0.0f;
}