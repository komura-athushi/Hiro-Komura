#include "stdafx.h"
#include "Skeleton1.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
#include "Game.h"
#include "Player.h"
//cpp�ŃG�l�~�[�̃��A�x���Ƃ̃h���b�v����ݒ�
const int Skeleton1::m_dropChances[Weapon::m_HighestRarity] = { 0,15,5,0,0,0,0 };
const int Skeleton1::m_dropmaterialChances[Material::m_HighestRarity] = { 20.0f,20.0f,0.0f };
//�S�i�����ڂ̓X�P���g���j�ł�
Skeleton1::Skeleton1():IEnemy(m_MaxHP,m_Attack,m_EXP,m_dropChances,m_dropmaterialChances,m_meseta)
{

}

Skeleton1::~Skeleton1()
{
	delete m_skinModelRender;
}

bool Skeleton1::Start()
{
	IEnemy::CCollision({ m_position }, m_collisionheight, m_r);
	//�A�j���[�V����
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/enemy/idle.tka");
	m_animClip[enAnimationClip_attack].Load(L"Asset/animData/enemy/attack.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/enemy/damage.tka");
	m_animClip[enAnimationClip_death].Load(L"Asset/animData/enemy/death.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_attack].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_death].SetLoopFlag(false);
	//�S�̃X�L�����f�������_�[��\��
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/enemy.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisZ);
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetRot(m_rotation);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	pos.y += 55.0f;
	m_staticobject.CreateCapsule(pos, rot, 40.0f, 50.0f);
	return true;
}

void Skeleton1::Chase()
{
	m_movespeed = { 0.0f,0.0f,0.0f };
	//�v���C���[�̍��W���擾
	CVector3 m_playerposition = m_player->GetPosition();
	//�v���C���[�ƓG�̋���
	CVector3 pos = m_player->GetPosition() - m_position;
	//�G�̏����ʒu�ƌ��݈ʒu�̋���
	CVector3 oldpos = m_oldpos - m_position;
	//�ڐG������U��
	if (pos.LengthSq() < 140.0f*140.0f) {
		m_state = enState_Attack;
	}
	//�����v���C���[�ƋS�̋������߂��Ȃ�����
	else if (pos.LengthSq() < 1100.0f*1100.0f) {
		//�߂Â��Ă���
		CVector3 EnemyPos = m_playerposition - m_position;
		EnemyPos.Normalize();
		m_movespeed = EnemyPos * 5.0f;
		m_movespeed.y = 0.0f;
		m_position += m_movespeed;
	}
	
	else if(pos.LengthSq() > 1000.0f*1000.0f){
		//�����ʒu�ɋA��
		CVector3 EnemyOldPos = m_oldpos - m_position;
		EnemyOldPos.Normalize();
		m_movespeed = EnemyOldPos * 5.0f;
		m_movespeed.y = 0.0f;
		//�G�̏����ʒu�ƌ��݈ʒu�̋������ق�0��������~�܂�
		if (oldpos.Length() < 50.0f) {
			m_movespeed = { 0.0f,0.0f,0.0f };
		}
		m_position += m_movespeed;
	}
	
	m_skinModelRender->SetPos(m_position);
}

void Skeleton1::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f);
	//�X�e�[�g����ɂ���ăA�j���[�V�������Đ�������
	switch (m_state) {
	case enState_Idle_Run:
		if (m_movespeed.LengthSq() > 300.0f * 300.0f) {
			//���胂�[�V�����B
			//m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		else {
			//�ҋ@���[�V����
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		}
		//m_state = enState_Idle_Run;
		Chase();
		Turn();
		break;
	case enState_Attack:
		//�U���ƍU���̊ԂɃN�[���^�C����݂���
		if (m_timer > 60) {
			if (m_skinModelRender->GetAnimCon().IsPlaying()) {
				m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack, 0.0f);
				m_timer = 0;
			}
			else {
				m_state = enState_Idle_Run;
			}
		}
		Turn();
		break;
	case enState_Damage:
		m_skinModelRender->GetAnimCon().SetSpeed(2.0f);
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()){
				m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Dead:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_death, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()){
			m_gekiha = true;
		}
		break;
	}
}

void Skeleton1::Turn()
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
	m_heikou = moveSpeedXZ;
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
}

void Skeleton1::Damage() 
{
	if (IEnemy::m_damage) {
		m_state = enState_Damage;
		IEnemy::m_damage = false;
	}
}

void Skeleton1::Dead()
{
	if (IEnemy::m_death) {
		m_state = enState_Dead;
	}
}

void Skeleton1::Update()
{
	m_timer++;
	AnimationController();
	Damage();
	Dead();
	IEnemy::SetCCollision(m_position, m_collisionheight);
	if (!IEnemy::m_death) {
		CQuaternion rot;
		CVector3 pos = m_position;
		pos.y += 55.0f;
		m_staticobject.SetPositionAndRotation(pos, rot);
	}
	if (m_gekiha) {
		delete this;
	}
}

void Skeleton1::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName, L"attack") == 0) {
		//�U������̔���
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//�`��̍쐬
		CVector3 pos = m_position + CVector3::AxisY()*m_collisionheight;
		pos += m_heikou * 130.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), m_attackr);
		//������ݒ�
		attackCol->SetTimer(3);//15�t���[����폜�����
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//�Փ˂�������̖��O��"IEnemy"�Ȃ�m_Attack�������_���[�W�^����
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack);
			}
		}
		);
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		effect->Play(L"Asset/effect/Effects/efk/enemy_slash_01.efk", 1.0f, pos, m_rotation, m_effectscale);
		effect->SetSpeed(1.3f);
	}
}