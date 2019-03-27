#include "stdafx.h"
#include "Boss.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
#include "Player.h"
#include "GameCamera.h"
#include "Teleport.h"
#include "ShotMagic.h"
#include "Enemy_Ice.h"
//cppでエネミーのレア度ごとのドロップ率を設定
const int Boss::m_dropChances[Weapon::m_HighestRarity] = { 0,0,50,0,0,0,0 };
const int Boss::m_dropmaterialChances[Material::m_HighestRarity] = { 0,100,0 };
//ボスです
Boss::Boss() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{

}
Boss::~Boss()
{
	delete m_skinModelRender;
	Teleport* tl = new Teleport;
	tl->SetPosition(m_position);
	tl->SetName(L"Teleport");
}

bool Boss::Start()
{
	//コリジョンを設定
	IEnemy::CCollision(m_position , m_height, m_r);
	//ボスのスキンモデルレンダーを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/boss.cmo");
	m_skinModelRender->SetScale(m_scale);
	CVector3 po = m_position;
	po.y += m_y;
	m_skinModelRender->SetPos(po);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	pos.y += 500.0f;
	//静的オブジェクトを設定
	m_staticobject.CreateSphere(pos, rot, 150.0f);
	m_player = FindGO<Player>(L"Player");
	return true;
}

//IEnemyにいれる
void Boss::Turn()
{
	CVector3 rotation = { 0.0f,0.0f,0.0f };
	//自機の角度の差分
	float sdegree = 0.0f;
	m_radian = M_PI / 180 * m_degree;
	//回転処理
	m_degree += sdegree;
	auto moveSpeedXZ = m_player->GetPosition() - m_position;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	if (moveSpeedXZ.LengthSq() < 0.5f) {
		return;
	}
	m_parallel = moveSpeedXZ;
	if (m_isaria && !m_ismagic) {

	}
	else {
		m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(-moveSpeedXZ.x, -moveSpeedXZ.z));
		m_skinModelRender->SetRot(m_rotation);
	}
}

void Boss::One()
{
	switch (m_attackstate) {
	case enState_FS:
		if (!m_isaria) {
			Aria();
			m_isaria = true;
		}
		else {
			if (!m_ismagic) {
				if (m_timer >= m_FSariatimer * m_timemultiply) {
					if (m_timer2 >= 0.1f * m_timemultiply) {
						if (m_fscounter == 0) {
							CVector3 pos = m_position;
							pos.y += m_height;
							m_magicdirection = (m_player->GetPosition() + CVector3::AxisY()*40.0f) - pos;
							m_magicdirection.Normalize();
							CQuaternion qRot;
							qRot.SetRotationDeg(CVector3::AxisY(), m_plusdegree * 2);
							qRot.Multiply(m_magicdirection);
							FS();
						}
						else {
							CQuaternion qRot;
							qRot.SetRotationDeg(CVector3::AxisY(), -m_plusdegree);
							qRot.Multiply(m_magicdirection);
							FS();
						}
					}
					if (m_fscounter == m_fsnumber) {
						m_ismagic = true;
						m_fscounter = 0;
						m_timer = 0.0f;
					}
					m_timer2 += GetDeltaTimeSec();
				}
			}
			else if (m_timer >= m_posetime3 * m_timemultiply) {
				m_ismagic = false;
				m_attackstate = enState_MG;
				m_timer = 0.0f;
				m_isaria = false;
				if (m_HP < m_MaxHP * 0.6f) {
					m_state = enState_Two;
					m_attackstate = enState_MG;
					m_isaria = false;
					m_timer = 0.0f;
					m_fscounter = 0;
					m_mgcounter = 0;
					m_timer2 = 0.0f;
				}
			}
		}
		break;
	case enState_MG:
		if (!m_isaria) {
			Aria();
			m_isaria = true;
		}
		else {
			if (!m_ismagic) {
				if (m_timer >= m_MGariatimer * m_timemultiply) {
					if (m_timer2 >= 0.5f * m_timemultiply) {
						CVector3 pos = m_position;
						pos.y += m_height;
						m_magicdirection = (m_player->GetPosition() + CVector3::AxisY()*40.0f) - pos;
						m_magicdirection.Normalize();
						MG();
					}
					if (m_mgcounter == 3) {
						m_ismagic = true;
						m_mgcounter = 0;
						m_timer = 0.0f;
					}
					m_timer2 += GetDeltaTimeSec();
				}
			}
			else if (m_timer >= m_posetime1 * m_timemultiply) {
				m_ismagic = false;
				m_attackstate=enState_FS;
				m_timer = 0.0f;
				m_isaria = false;
			}
		}
		break;
	case enState_EB:

		break;
	}
	m_timer += GetDeltaTimeSec();
}

void Boss::Two()
{
	switch (m_attackstate) {
	case enState_FS:
		if (!m_isaria) {
			Aria();
			m_isaria = true;
		}
		else {
			if (!m_ismagic) {
				if (m_timer >= m_FSariatimer * m_timemultiply) {
					if (m_timer2 >= 0.1f * m_timemultiply) {
						if (m_fscounter == 0) {
							CVector3 pos = m_position;
							pos.y += m_height;
							m_magicdirection = (m_player->GetPosition() + CVector3::AxisY()*40.0f) - pos;
							m_magicdirection.Normalize();
							CQuaternion qRot;
							qRot.SetRotationDeg(CVector3::AxisY(), m_plusdegree * 2);
							qRot.Multiply(m_magicdirection);
							FS();
						}
						else {
							CQuaternion qRot;
							qRot.SetRotationDeg(CVector3::AxisY(), -m_plusdegree);
							qRot.Multiply(m_magicdirection);
							FS();
						}
					}
					if (m_fscounter == m_fsnumber) {
						m_ismagic = true;
						m_fscounter = 0;
						m_timer = 0.0f;
						m_countfs++;
					}
					m_timer2 += GetDeltaTimeSec();
				}
			}
			else {
				if (m_countfs == 1) {
					if (m_timer >= m_posetime2 * m_timemultiply) {
						m_ismagic = false;
						m_attackstate = enState_FS;
						m_timer = 0.0f;
						m_isaria = false;
					}
				}
				else if (m_countfs == 2) {
					if (m_timer >= m_posetime3 * m_timemultiply) {
						m_ismagic = false;
						m_attackstate = enState_MG;
						m_timer = 0.0f;
						m_isaria = false;
						m_countfs = 0;
						if (m_HP < m_MaxHP * 0.3f) {
							m_state = enState_Three;
							m_attackstate = enState_MG;
							m_isaria = false;
							m_timer = 0.0f;
							m_fscounter = 0;
							m_mgcounter = 0;
							m_countfs = 0;
							m_countmg = 0;
							m_timer2 = 0.0f;
						}
					}
				}
			}
		}
		break;
	case enState_MG:
		if (!m_isaria) {
			Aria();
			m_isaria = true;
		}
		else {
			if (!m_ismagic) {
				if (m_timer >= m_MGariatimer * m_timemultiply) {
					if (m_timer2 >= 0.3f * m_timemultiply) {
						CVector3 pos = m_position;
						pos.y += m_height;
						m_magicdirection = (m_player->GetPosition() + CVector3::AxisY()*40.0f) - pos;
						m_magicdirection.Normalize();
						MG();
					}
					if (m_mgcounter == 5) {
						m_ismagic = true;
						m_mgcounter = 0;
						m_timer = 0.0f;
					}
					m_timer2 += GetDeltaTimeSec();
				}
			}
			else if (m_timer >= m_posetime1 * m_timemultiply) {
				m_ismagic = false;
				m_attackstate = enState_FS;
				m_timer = 0.0f;
				m_isaria = false;
			}
		}
		break;
	case enState_EB:

		break;
	}
	m_timer += GetDeltaTimeSec();
}

void Boss::Three()
{
	switch (m_attackstate) {
	case enState_FS:
		if (!m_isaria) {
			Aria();
			m_isaria = true;
		}
		else {
			if (!m_ismagic) {
				if (m_timer >= m_FSariatimer * m_timemultiply) {
					if (m_timer2 >= 0.1f * m_timemultiply) {
						if (m_fscounter == 0) {
							CVector3 pos = m_position;
							pos.y += m_height;
							m_magicdirection = (m_player->GetPosition()+CVector3::AxisY()*40.0f) - pos;
							m_magicdirection.Normalize();
							CQuaternion qRot;
							qRot.SetRotationDeg(CVector3::AxisY(), m_plusdegree * 2);
							qRot.Multiply(m_magicdirection);
							FS();
						}
						else {
							CQuaternion qRot;
							qRot.SetRotationDeg(CVector3::AxisY(), -m_plusdegree);
							qRot.Multiply(m_magicdirection);
							FS();
						}
					}
					if (m_fscounter == m_fsnumber) {
						m_ismagic = true;
						m_fscounter = 0;
						m_timer = 0.0f;
					}
					m_timer2 += GetDeltaTimeSec();
				}
			}
			else {
				if (m_timer >= m_posetime2 * m_timemultiply) {
					m_ismagic = false;
					m_attackstate = enState_MG;
					m_timer = 0.0f;
					m_isaria = false;
					m_countfs = 0;
					m_countmg = 0;
				}
			}
		}
		break;
	case enState_MG:
		if (m_countmg == 0) {
			if (!m_isaria) {
				Aria();
				m_isaria = true;
			}
			else {
				if (!m_ismagic) {
					if (m_timer >= m_MGariatimer * m_timemultiply) {
						if (m_timer2 >= 0.2f * m_timemultiply) {
							CVector3 pos = m_position;
							pos.y += m_height;
							m_magicdirection = (m_player->GetPosition() + CVector3::AxisY()*40.0f) - pos;
							m_magicdirection.Normalize();
							MG();
						}
						if (m_mgcounter == 5) {
							m_ismagic = false;
							m_mgcounter = 0;
							m_timer = 0.0f;
							m_countmg++;
							m_attackstate = enState_MG;
							m_isaria = false;
						}
						m_timer2 += GetDeltaTimeSec();
					}
				}
			}
		}
		else if (m_countmg == 1) {
			if (!m_isaria) {
				Aria();
				m_isaria = true;
			}
			else {
				if (!m_ismagic) {
					if (m_timer >= 1.0f * m_timemultiply) {
						CVector3 pos = m_position;
						pos.y += m_height;
						m_magicdirection = (m_player->GetPosition() + CVector3::AxisY()*40.0f) - pos;
						m_magicdirection.Normalize();
						MG();
						m_ismagic = true;
						m_timer = 0.0f;
						m_timer2 += GetDeltaTimeSec();
					}
				}
				else if (m_timer >= 0.75 * m_timemultiply) {
					m_ismagic = false;
					m_attackstate = enState_EB;
					m_timer = 0.0f;
					m_isaria = false;
				}
			}
		}
		break;
	case enState_EB:
		if (!m_isdecisionposition) {
			m_playerposition = m_player->GetPosition();
			m_isdecisionposition = true;
		}
		CVector3 pos = m_position;
		pos.y += m_height;
		CVector3 po = m_playerposition - pos;
		if (po.LengthSq() >= m_attackchanceEB && !m_isEB) {
			po.y = 0.0f;
			po.Normalize();
			CQuaternion qRot;
			qRot.SetRotation(CVector3::AxisY(), atan2f(-po.x, -po.z));
			m_skinModelRender->SetRot(qRot);
			m_movespeed = po * m_speedmultiply * GetDeltaTimeSec();
			m_position += m_movespeed;
		}
		else {
			m_isEB = true;
		}
		if (m_isEB) {
			if (!m_isaria) {
				Aria();
				m_isaria = true;
				CVector3 pos = m_position;
				pos.y += m_height;
				m_magicdirection = m_player->GetPosition() - pos;
				m_magicdirection.Normalize();
			}
			else {
				if (!m_ismagic) {
					if (m_timer >= m_FSariatimer * m_timemultiply) {
						EB();
						m_ismagic = true;
						m_timer = 0.0f;
						m_timer2 += GetDeltaTimeSec();
					}
				}
				else {
					if (m_timer >= m_posetime2 * m_timemultiply) {
						m_ismagic = false;
						m_attackstate = enState_FS;
						m_timer = 0.0f;
						m_isaria = false;
						m_isEB = false;
						m_isdecisionposition = false;
					}
				}
			}
		}
		break;
	}
	m_timer += GetDeltaTimeSec();
}

void Boss::Update()
{
	if (!IEnemy::m_death) {
		CVector3 po = m_player->GetPosition() - m_position;
		if (po.LengthSq() < m_startdistance) {
			m_start = true;
		}
		if (m_start) {
			Turn();
			switch (m_state) {
			case enState_One:
				One();
				break;
			case enState_Two:
				Two();
				break;
			case enState_Three:
				Three();
				break;
			}
		}
		CQuaternion rot;
		CVector3 pos = m_position;
		pos.y += m_height;
		m_staticobject.SetPositionAndRotation(pos, rot);
		CVector3 ps = m_position;
		ps.y += m_y;
		m_skinModelRender->SetPos(ps);
		m_skinModelRender->SetPos(m_position);
		IEnemy::SetCCollision(m_position, m_height);
	}
	//死んだら消す
	if (m_death) {
		m_deathtimer += 40.0f * GetDeltaTimeSec();
		if (m_deathtimer = 10) {
			delete this;
		}
	}
}

void Boss::MG()
{
	CVector3 pos = m_position;
	pos.y += m_height;
	ShotMagic* sm = new ShotMagic;
	sm->SetPosition(pos);
	sm->SetDirectionPlayer(m_magicdirection);
	if (m_countmg == 1) {
		sm->SetDamage(m_AttackMG * 2);
		sm->SetMultiplyScale(2.0f);
	}
	else {
		sm->SetDamage(m_AttackMG);
	}
	sm->SetEnemy();
	sm->SetId(ShotMagic::enMagic_MagicSphere);
	sm->SetSpeed(0.8f);
	sm->SetDeleteTime(m_MGdeletetime);
	sm->SetName(L"MagicSphere");
	m_timer2 = 0.0f;
	m_mgcounter++;
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), atan2f(-m_magicdirection.x, -m_magicdirection.z));
	m_skinModelRender->SetRot(qRot);
}

void Boss::FS()
{
	Enemy_Ice* ei = new Enemy_Ice;
	CVector3 pos = m_position;
	pos.y += m_height;
	ei->SetPosition(pos);
	ei->SetMoveSpeed(m_magicdirection);
	ei->SetAttack(m_AttackFS);
	ei->SetDeleteTime(m_icedeletetime);
	ei->SetSpeed(1.5f);
	m_timer2 = 0.0f;
	m_fscounter++;
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), atan2f(-m_magicdirection.x, -m_magicdirection.z));
	m_skinModelRender->SetRot(qRot);
}

void Boss::EB()
{
	CVector3 pos = m_position;
	pos.y += 100.0f;
	ShotMagic* sm = new ShotMagic;
	sm->SetPosition(pos);
	sm->SetDirectionPlayer(m_magicdirection);
	sm->SetDamage(m_AttackEB);
	sm->SetEnemy();
	sm->SetMultiplyScale(2.0f);
	sm->SetId(ShotMagic::enMagic_Wind);
	m_timer2 = 0.0f;
	m_timer = 0.0f;
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), atan2f(-m_magicdirection.x, -m_magicdirection.z));
	m_skinModelRender->SetRot(qRot);
}

void Boss::Aria()
{
	CVector3 pos = m_position;
	pos.y += 150.0f;
	GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
	switch (m_attackstate) {
	case enState_FS:
		effect->Play(L"Asset/effect/Effects/efk/cast_ice.efk", 1.0f, pos, CQuaternion::Identity(), m_ariascale);
		break;
	case enState_MG:
		effect->Play(L"Asset/effect/Effects/efk/cast_sphere.efk", 1.0f, pos, CQuaternion::Identity(), m_ariascale);
		break;
	case enState_EB:
		effect->Play(L"Asset/effect/Effects/efk/cast_wind.efk", 1.0f, pos, CQuaternion::Identity(), m_ariascale);
		break;
	}
	effect->SetSpeed(2.0f);
	//SE
	SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/aria.wav");
	se->Play(); //再生(再生が終わると削除されます)
	se->SetVolume(m_sevolume);
	//3D再生
	se->SetPos(m_position);//音の位置
	se->SetDistance(500.0f);//音が聞こえる範囲
	se->Play(true); //第一引数をtrue
	m_timer = 0.0f;
}