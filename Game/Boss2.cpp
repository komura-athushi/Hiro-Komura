#include "stdafx.h"
#include "Boss2.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy_Fire.h"
#include "Teleport.h"
//cpp�ŃG�l�~�[�̃��A�x���Ƃ̃h���b�v����ݒ�
const int Boss2::m_dropChances[Weapon::m_HighestRarity] = { 0,0,0,100,0,0,0 };
const int Boss2::m_dropmaterialChances[Material::m_HighestRarity] = { 0.0f,100.0f,0.0f };
//�{�X2(�h���S��)�ł�
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
	//�A�j���[�V����
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/boss_2/attack1.tka");
	//m_animClip[enAnimationClip_idle].Load(L"Asset/animData/boss2/boss2_fire.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/boss_2/walk.tka");
	m_animClip[enAnimationClip_attack1].Load(L"Asset/animData/boss_2/attack1.tka");
	m_animClip[enAnimationClip_aria].Load(L"Asset/animData/boss_2/aria.tka");
	m_animClip[enAnimationClip_aria2].Load(L"Asset/animData/boss_2/aria2.tka");
	m_animClip[enAnimationClip_death].Load(L"Asset/animData/boss_2/death.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_run].SetLoopFlag(true);
	m_animClip[enAnimationClip_attack1].SetLoopFlag(false);
	m_animClip[enAnimationClip_aria].SetLoopFlag(false);
	m_animClip[enAnimationClip_aria2].SetLoopFlag(false);
	m_animClip[enAnimationClip_death].SetLoopFlag(false);
	//�h���S���̃X�L�����f�������_�[��\��
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
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f * 30.0f * GetDeltaTimeSec());
	//�X�e�[�g����ɂ���ăA�j���[�V�������Đ�������
	switch (m_state) {
	case enState_Idle:
		//�ҋ@���[�V����
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);	
		Turn();
		break;
	case enState_Run:
		if (m_movespeed.LengthSq() > 1.0f*1.0f) {
			//���胂�[�V�����B
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		Chase();
		Turn();
		break;
	case enState_Attack1:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack1, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle;
		}
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
	//�v���C���[�̍��W���擾
	CVector3 m_playerposition = m_player->GetPosition();
	//�v���C���[�ƓG�̋���
	CVector3 pos = m_player->GetPosition() - m_position;
	//�G�̏����ʒu�ƌ��݈ʒu�̋���
	CVector3 oldpos = m_oldpos - m_position;
	//�����v���C���[�ƋS�̋������߂��Ȃ�����
	if (pos.LengthSq() < 1800.0f * 1800.0f) {
		if (pos.LengthSq() > 200.0f * 200.0f) {
			//�߂Â��Ă���
			CVector3 EnemyPos = m_playerposition - m_position;
			EnemyPos.Normalize();
			m_movespeed = EnemyPos * 2.5f;
			m_movespeed.y = 0.0f;
			m_position += m_movespeed;
		}
		else {
			m_state = enState_Attack1;
		}
	}
	else if (pos.LengthSq() > 2000.0f * 2000.0f) {
		//�����ʒu�ɋA��
		CVector3 EnemyOldPos = m_oldpos - m_position;
		EnemyOldPos.Normalize();
		m_movespeed = EnemyOldPos * 5.0f;
		m_movespeed.y = 0.0f;
		//�G�̏����ʒu�ƌ��݈ʒu�̋������ق�0��������~�܂�
		if (oldpos.LengthSq() < 50.0f * 50.0f) {
			m_movespeed = { 0.0f,0.0f,0.0f };
		}
		m_position += m_movespeed;
	}
	m_skinModelRender->SetPos(m_position);
}

void Boss2::Turn()
{
	//m_movespeed����L�����N�^�[����]������
	auto moveSpeedXZ = m_movespeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	moveSpeedXZ.y = 0;
	if (moveSpeedXZ.LengthSq() < 0.5f) {
		return;
	}
	else {
		CVector3 pos = m_player->GetPosition() - m_position;
		pos.y = 0.0f;
		pos.Normalize();
		m_rotation.GetRotation(CVector3::AxisY(), atan2f(pos.x, pos.z));
	}
	m_skinModelRender->SetRot(m_rotation);
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
	//�U��
	if (wcscmp(eventName, L"attack1") == 0) {
		//�U������̔���
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//�`��̍쐬
		CVector3 pos = m_position + CVector3::AxisY() * (m_collisionheight - 50.0f);
		pos += m_parallel * 150.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), m_attackr);
		//������ݒ�
		attackCol->SetTimer(60);//�t���[����폜�����
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//�Փ˂�������̖��O��"Player"�Ȃ�m_Attack1�������_���[�W�^����
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_attack1);
			}
		}
		);
		//�v���X
	}
	else if (wcscmp(eventName, L"aria") == 0) {
		//�U������̔���
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//�`��̍쐬
		CVector3 atkpos = m_position;
		atkpos.y -= 150.0f;
		//attackCol->CreateSphere(atkpos, CQuaternion::Identity(), m_attack2r);
		//������ݒ�
		attackCol->SetTimer(5);//�t���[����폜�����
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//�Փ˂�������̖��O��"Player"�Ȃ�m_Attack1�������_���[�W�^����
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack2);
			}
		}
		);
	}
	//�t�@�C���[
	else if (wcscmp(eventName, L"fire") == 0) {
		//�v���C���[�̍��W���擾
		CVector3 m_playerposition = m_player->GetPosition();
		m_playerposition.y += 100.0f;
		//�{�X�̓��̍��W
		//CVector3 b_pos = m_skinModelRender->GetBonePos(m_bonehead);
		//�v���C���[�ƃ{�X�̋���
		CVector3 pos = m_player->GetPosition() - m_position;
		Enemy_Fire* fire = new Enemy_Fire;
		//�e�ۂ̍��W�Ƀ{�X�̍��W��������B
		//fire->SetPosition(b_pos);
		fire->SetAttack(m_attackfire);
		//CVector3 bulletPos = m_playerposition - b_pos;
		//bulletPos.Normalize();
		//�e�̃X�s�[�h��ς���
		//fire->SetMoveSpeed(bulletPos);
	}
}

void Boss2::ChangeBehavior()
{

}

void Boss2::Update()
{
	m_timer++;
	AnimationController();
	if (!IEnemy::m_death) {
		CQuaternion rot;
		m_staticobject.SetPositionAndRotation(m_position + CVector3::AxisY() * m_collisionheight, rot);
		IEnemy::SetCCollision(m_position, m_collisionheight);
	}
	Dead();
	//���񂾂����
	if (m_gekiha) {
		delete this;
	}
}
