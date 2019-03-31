#include "stdafx.h"
#include "Boss2.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy_Fire.h"
#include "ShotMagic.h"
#include "Teleport.h"
//cppでエネミーのレア度ごとのドロップ率を設定
const int Boss2::m_dropChances[Weapon::m_HighestRarity] = { 0,0,0,100,0,0,0 };
const int Boss2::m_dropmaterialChances[Material::m_HighestRarity] = { 0.0f,100.0f,0.0f };
//ボス2(ドラゴン)です
Boss2::Boss2() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{

}

Boss2::~Boss2()
{
	delete m_skinModelRender;
	Teleport* tl = new Teleport;
	tl->SetPosition(m_position);
	tl->SetName(L"Teleport");
}

bool Boss2::Start()
{
	IEnemy::CCollision(m_position, m_collisionheight, m_r);
	//アニメーション
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/boss_2/idle.tka");
	//m_animClip[enAnimationClip_idle].Load(L"Asset/animData/boss2/boss2_fire.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/boss_2/walk.tka");
	m_animClip[enAnimationClip_aria].Load(L"Asset/animData/boss_2/aria.tka");
	m_animClip[enAnimationClip_aria2].Load(L"Asset/animData/boss_2/aria2.tka");
	m_animClip[enAnimationClip_aria3].Load(L"Asset/animData/boss_2/aria3.tka");
	m_animClip[enAnimationClip_death].Load(L"Asset/animData/boss_2/death.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_run].SetLoopFlag(true);
	m_animClip[enAnimationClip_aria].SetLoopFlag(false);
	m_animClip[enAnimationClip_aria2].SetLoopFlag(false);
	m_animClip[enAnimationClip_aria3].SetLoopFlag(false);
	m_animClip[enAnimationClip_death].SetLoopFlag(false);
	//ドラゴンのスキンモデルレンダーを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/rockgolem.cmo", m_animClip, enAnimationClip_num);
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	m_staticobject.CreateSphere(m_position + CVector3::AxisY()*m_collisionheight, rot, m_r);
	return true;
}

void Boss2::AnimationController()
{
	if (!m_isanger) {
		m_skinModelRender->GetAnimCon().SetSpeed(1.0f * 35.0f * GetDeltaTimeSec());
	}
	else {
		m_skinModelRender->GetAnimCon().SetSpeed(1.0f * 40.0f * GetDeltaTimeSec());
	}
	//ステート分岐によってアニメーションを再生させる
	switch (m_state) {
	case enState_Idle:
		//待機モーション
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		if (!m_isanger) {
			if (m_timer >= m_idletime) {
				ChangeBehavior();
				m_timer = 0.0f;
			}
		}
		else {
			if (m_timer >= m_idletimeanger) {
				ChangeBehavior();
				m_timer = 0.0f;
			}
		}
		Turn();
		m_timer += GetDeltaTimeSec();
		break;
	case enState_Run:
		if (m_movespeed.LengthSq() > 1.0f*1.0f) {
			//走りモーション。
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
			if (!m_isanger) {
				if (m_timer >= m_movetime) {
					ChangeBehavior();
					m_timer = 0.0f;
				}
			}
			else {
				if (m_timer >= m_movetimeanger) {
					ChangeBehavior();
					m_timer = 0.0f;
				}
			}
		}
		m_timer += GetDeltaTimeSec();
		Chase();
		Turn();
		break;
	case enState_Aria:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_aria, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle;
		}
		Turn();
		break;
	case enState_Aria2:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_aria2, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle;
		}
		Turn();
		break;
	case enState_Aria3:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_aria3, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle;
		}
		Turn();
		break;
	case enState_Death:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_death, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_gekiha = true;
		}
		break;
	}
}


void Boss2::Chase()
{
	m_movespeed = { 0.0f,0.0f,0.0f };
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	//プレイヤーと敵の距離
	CVector3 pos = m_player->GetPosition() - m_position;
	//敵の初期位置と現在位置の距離
	CVector3 oldpos = m_oldpos - m_position;
	//もしプレイヤーと鬼の距離が近くなったら
	if (pos.LengthSq() > 300.0f * 300.0f) {
			//近づいてくる
			CVector3 EnemyPos = m_playerposition - m_position;
			EnemyPos.Normalize();
			m_movespeed = EnemyPos * 8.0f;
			m_movespeed.y = 0.0f;
			m_position += m_movespeed * 40.0f* GetDeltaTimeSec();
	}
	else if (pos.LengthSq() > 2300.0f * 2300.0f) {
		//初期位置に帰る
		CVector3 EnemyOldPos = m_oldpos - m_position;
		EnemyOldPos.Normalize();
		m_movespeed = EnemyOldPos * 7.0f;
		m_movespeed.y = 0.0f;
		//敵の初期位置と現在位置の距離がほぼ0だったら止まる
		if (oldpos.LengthSq() < 50.0f * 50.0f) {
			m_movespeed = { 0.0f,0.0f,0.0f };
		}
		m_position += m_movespeed;
	}
	else {
		m_state = enState_Aria3;
	}
	m_skinModelRender->SetPos(m_position);
}

void Boss2::Turn()
{
	//m_movespeedからキャラクターを回転させる
	auto moveSpeedXZ = m_movespeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	moveSpeedXZ.y = 0;
	if (moveSpeedXZ.LengthSq() < 0.5f) {
		CVector3 pos = m_player->GetPosition() - m_position;
		pos.y = 0.0f;
		pos.Normalize();
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(pos.x, pos.z));
	}
	else {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	}
	m_skinModelRender->SetRot(m_rotation);
	m_parallel = CVector3::AxisZ();
	m_rotation.Multiply(m_parallel);
}

void Boss2::Dead()
{
	if (IEnemy::m_death) {
		m_state = enState_Death;
	}
}


void Boss2::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	//ファイアローばら撒き
	if (wcscmp(eventName, L"magic") == 0) {
		if (!m_isanger) {
			float degree = 0.0f;
			for (int i = 0; i < m_firenumber; i++) {
				CVector3 pos = m_parallel;
				CQuaternion rot;
				rot.SetRotation(CVector3::AxisY(), degree);
				rot.Multiply(pos);
				ShotMagic* sm = new ShotMagic;
				sm->SetPosition(m_position + CVector3::AxisY() * m_fireheight);
				sm->SetDirectionPlayer(pos);
				sm->SetDamage(m_AttackFIRE);
				sm->SetEnemy();
				sm->SetMultiplyScale(m_firespeed);
				sm->SetId(ShotMagic::enMagic_Fire);
				sm->SetScale(m_firescale);
				degree += M_PI * 2 / m_firenumber;
				sm->SetDeleteTime(150.0f);
			}
		}
		else {
			float degree = 0.0f;
			for (int i = 0; i < m_firenumberanger; i++) {
				CVector3 pos = m_parallel;
				CQuaternion rot;
				rot.SetRotation(CVector3::AxisY(), degree);
				rot.Multiply(pos);
				ShotMagic* sm = new ShotMagic;
				sm->SetPosition(m_position + CVector3::AxisY() * m_fireheight);
				sm->SetDirectionPlayer(pos);
				sm->SetDamage(m_AttackFIRE);
				sm->SetEnemy();
				sm->SetMultiplyScale(m_firespeedanger);
				sm->SetId(ShotMagic::enMagic_Fire);
				sm->SetScale(m_firescaleanger);
				degree += M_PI * 2 / m_firenumberanger;
				sm->SetDeleteTime(150.0f);
			}
		}
	}
	//かきう
	else if (wcscmp(eventName, L"magic2") == 0) {
		CVector3 pos = m_position + CVector3::AxisY() * m_enemyfireheight;
		CVector3 bulletPos = (m_player->GetPosition() + CVector3::AxisY() * m_playerheight) - pos;
		bulletPos.Normalize();
		if (!m_isanger) {
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY(), m_plusdegree * m_enemyfirenumber / 2);
			qRot.Multiply(bulletPos);
			Enemy_Fire* sm = new Enemy_Fire;
			sm->SetPosition(pos);
			sm->SetMoveSpeed(bulletPos);
			sm->SetAttack(m_AttackEF);
			sm->SetSpeed(m_enemyfirespeed);
			sm->SetDeleteTime(170.0f);
			for (int i = 0; i < m_enemyfirenumber; i++) {
				Enemy_Fire* sm = new Enemy_Fire;
				sm->SetPosition(pos);
				sm->SetMoveSpeed(bulletPos);
				sm->SetAttack(m_AttackEF);
				sm->SetSpeed(m_enemyfirespeed);
				sm->SetDeleteTime(170.0f);
				CQuaternion qRot;
				qRot.SetRotationDeg(CVector3::AxisY(), -m_plusdegree);
				qRot.Multiply(bulletPos);
			}
		}
		else {
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY(), m_plusdegreeanger * m_enemyfirenumberanger / 2);
			qRot.Multiply(bulletPos);
			Enemy_Fire* sm = new Enemy_Fire;
			sm->SetPosition(pos);
			sm->SetMoveSpeed(bulletPos);
			sm->SetAttack(m_AttackEF);
			sm->SetSpeed(m_enemyfirespeed);
			sm->SetDeleteTime(170.0f);
			for (int i = 0; i < m_enemyfirenumberanger; i++) {
				Enemy_Fire* sm = new Enemy_Fire;
				sm->SetPosition(pos);
				sm->SetMoveSpeed(bulletPos);
				sm->SetAttack(m_AttackEF);
				sm->SetSpeed(m_enemyfirespeed);
				sm->SetDeleteTime(170.0f);
				CQuaternion qRot;
				qRot.SetRotationDeg(CVector3::AxisY(), -m_plusdegreeanger);
				qRot.Multiply(bulletPos);
			}
		}
	}
	else if (wcscmp(eventName, L"magic3") == 0) {
		ShotMagic* sm = new ShotMagic;
		sm->SetPosition(m_position + CVector3::AxisY()*50.0f);
		sm->SetDirectionPlayer(m_parallel);
		sm->SetDamage(m_AttackEB);
		sm->SetEnemy();
		sm->SetMultiplyScale(1.2f);
		sm->SetId(ShotMagic::enMagic_Wind);

	}
	//以下呪文詠唱
	else if (wcscmp(eventName, L"aria") == 0) {
		CVector3 pos = m_position;
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		effect->SetSpeed(2.0f);
		effect->Play(L"Asset/effect/Effects/efk/cast_fire.efk", 1.0f, m_position, CQuaternion::Identity(), m_ariascale);
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/aria.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_sevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(500.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
	else if (wcscmp(eventName, L"aria2") == 0) {
		CVector3 pos = m_position;
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		effect->SetSpeed(2.0f);
		effect->Play(L"Asset/effect/Effects/efk/cast_fire.efk", 1.0f, m_position, CQuaternion::Identity(), m_ariascale);
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/aria.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_sevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(500.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
	else if (wcscmp(eventName, L"aria3") == 0) {
		CVector3 pos = m_position;
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		effect->SetSpeed(2.0f);
		effect->Play(L"Asset/effect/Effects/efk/cast_wind.efk", 1.0f, m_position, CQuaternion::Identity(), m_ariascale);
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/aria.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_sevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(500.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
}

void Boss2::ChangeBehavior()
{
	if (!m_start) {
		m_state = enState_Idle;
	}
	else {
		int ran = rand() % 100 + 1;
		if (!m_isanger) {
			if (ran < 50) {
				m_state = enState_Aria;
			}
			else {
				m_state = enState_Aria2;
			}
		}
		else {
			CVector3 pos = m_player->GetPosition() - m_position;
			if (pos.LengthSq() < 300.0f * 300.0f) {
				m_state = enState_Aria3;
			}
			if (ran < 50) {
				m_state = enState_Aria;
			}
			else {
				m_state = enState_Aria2;
			}
			if (35 <= ran && ran <= 65) {
				m_state = enState_Run;
			}
		}
	}
}

void Boss2::Update()
{
	if (!m_start) {
		CVector3 po = m_player->GetPosition() - m_position;
		if (po.LengthSq() < m_startdistance) {
			m_start = true;
		}
	}
	if (m_HP <= m_MaxHP * 0.5f) {
		m_isanger = true;
	}
	AnimationController();
	if (!IEnemy::m_death) {
		CQuaternion rot;
		m_staticobject.SetPositionAndRotation(m_position + CVector3::AxisY() * m_collisionheight, rot);
		IEnemy::SetCCollision(m_position, m_collisionheight);
	}
	Dead();
	//死んだら消す
	if (m_gekiha) {
		delete this;
	}
}
