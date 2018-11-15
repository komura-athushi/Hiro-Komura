#include "stdafx.h"
#include "Oni.h"

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
	m_animClip[enAnimationClip_attack].Load(L"Asset/animData/enemy/attack.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/enemy/damage.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_attack].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	//�S�̃X�L�����f�������_�[��\��
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/enemy.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisZ);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot;
	m_staticobject.CreateCapsule(m_position, rot, 40.0f, 50.0f);
	return true;
}

void Oni::Attack()
{
}
//�Ȃ����G�l�~�[�����ɖ��܂����܂܂ɂȂ��Ă���
//push�̂����̊m�F
//�v���C���[�̎�������邭�����Ă��܂�
void Oni::Chase()
{
	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//�v���C���[�̍��W���擾
	CVector3 m_playerposition = m_player->GetPosition();
	//�v���C���[�ƓG�̋���
	CVector3 pos = m_player->GetPosition()-m_position;
	//�߂�������~�܂�
	if (pos.Length() < 50.0f) {
	m_state = enState_Attack;
	}
	//�����v���C���[�ƋS�̋������߂��Ȃ�����
	else if (pos.Length() < 1000.0f) {
		//�߂Â��Ă���
		CVector3 EnemyPos = m_playerposition - m_position;
		EnemyPos.Normalize();
		m_moveSpeed = EnemyPos * 5.0f;
		m_position += m_moveSpeed;
	}
	else {
		m_state = enState_Idle;
	}
	m_skinModelRender->SetPos(m_position);
	/*
	else if(oldpos == m_position){
		//�����ʒu�ɋA��
		CVector3 EnemyPos = oldpos - m_position;
		EnemyPos.Normalize();
		m_moveSpeed += EnemyPos * 5.0f;
		m_position += m_moveSpeed;
		m_skinModelRender->SetPos(m_position);
	}
	*/
	
}

void Oni::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f);
	//�X�e�[�g����ɂ���ăA�j���[�V�������Đ�������
	switch (m_state) {
	case enState_Idle:
		//�ҋ@���[�V����
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		break;
	case enState_Attack:
		//�U�����[�V����
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack, 0.2f);
		break;
	case enState_Damage:
		//�_���[�W���[�V����
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
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

void Oni::Update()
{
	Chase();
	//�G�l�~�[���f��Ȃ��Ȃ���
	AnimationController();
	Damage();
	CQuaternion rot;
	m_staticobject.SetPositionAndRotation(m_position, rot);

}