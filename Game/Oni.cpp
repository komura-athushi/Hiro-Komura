#include "stdafx.h"
#include "Oni.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 

//�S�i�����ڂ̓X�P���g���j�ł�
Oni::Oni()
{
}

Oni::~Oni()
{
	delete m_skinModelRender;
}

bool Oni::Start()
{
	//�A�j���[�V����
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/enemy/idle.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/enemy/death.tka");
	m_animClip[enAnimationClip_attack].Load(L"Asset/animData/enemy/attack.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/enemy/damage.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_run].SetLoopFlag(true);
	m_animClip[enAnimationClip_attack].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	//�S�̃X�L�����f�������_�[��\��
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/enemy.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisZ);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot;
	CVector3 pos = m_position;
	pos.y += 55.0f;
	m_staticobject.CreateCapsule(pos, rot, 40.0f, 50.0f);
	return true;
}

void Oni::Attack()
{
}
void Oni::Chase()
{
	m_movespeed = { 0.0f,0.0f,0.0f };
	//�v���C���[�̍��W���擾
	CVector3 m_playerposition = m_player->GetPosition();
	//�v���C���[�ƓG�̋���
	CVector3 pos = m_player->GetPosition()-m_position;
	//�ڐG������U��
	if (pos.Length() < 50.0f) {
	m_state = enState_Attack;
	}
	//�����v���C���[�ƋS�̋������߂��Ȃ�����
	else if (pos.Length() <= 1000.0f) {
		//�߂Â��Ă���
		CVector3 EnemyPos = m_playerposition - m_position;
		EnemyPos.Normalize();
		m_movespeed = EnemyPos * 5.0f;
		m_position += m_movespeed;
	}
	
	else if(pos.Length() > 1000.0f){
		//�����ʒu�ɋA��
		CVector3 EnemyOldPos = m_oldpos - m_position;
		EnemyOldPos.Normalize();
		m_movespeed = EnemyOldPos * 5.0f;
		m_position += m_movespeed;
	}
	
	m_skinModelRender->SetPos(m_position);
}

void Oni::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f);
	//�X�e�[�g����ɂ���ăA�j���[�V�������Đ�������
	switch (m_state) {
	case enState_Idle_Run:
		if (m_movespeed.LengthSq() > 300.0f * 300.0f) {
			//���胂�[�V�����B
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		else {
			//�ҋ@���[�V����
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		}
		m_state = enState_Idle_Run;
		Chase();
		Turn();
		break;
	//�U���ƍU���̊ԂɃN�[���^�C����݂���
	case enState_Attack:
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(2.0f);
			Animation();
		}
		else {
			m_state = enState_Idle_Run;
		}
		//�L�����N�^�[�̌����֌W
		Turn();
		break;
	case enState_Damage:
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
		}
		else {
			m_state = enState_Idle_Run;
		}
		Chase();
		Turn();
		break;
	case enState_Dead:
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
		}
		else {
			m_state = enState_Idle_Run;
		}
		delete this;
		break;
	}
}

void Oni::Damage() 
{
	if (Pad(0).GetButton(enButtonRB1)) //RB1�{�^���������ꂽ��
	{
		m_state = enState_Damage;
	}
}

void Oni::Turn()
{
	CVector3 rotation = { 0.0f,0.0f,0.0f };
	//���@�̊p�x�̍���
	float sdegree = 0.0f;
	m_radian = M_PI / 180 * m_degree;
	//��]����
	m_degree += sdegree;
	//m_movespeed����L�����N�^�[����]������
	auto moveSpeedXZ = m_movespeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	moveSpeedXZ.y = 0;
	if (moveSpeedXZ.LengthSq() < 0.5f) {
		return;
	}
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);

}

void Oni::Dead()
{
	if (Pad(0).GetButton(enButtonRT)) //RT�{�^���������ꂽ��
	{
		m_state = enState_Dead;
	}
}

void Oni::Update()
{
	AnimationController();
	Damage();
	Dead();
	CQuaternion rot;
	CVector3 pos = m_position;
	pos.y += 55.0f;
	m_staticobject.SetPositionAndRotation(pos, rot);

}
