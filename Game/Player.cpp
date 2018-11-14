#include "stdafx.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
#include "Sword.h"
#include "GameCamera.h"
#include "PlayerStatus.h"
Player::Player()
{
}

Player::~Player()
{
	delete m_skinModelRender;
	delete m_sword;
}

bool Player::Start()
{
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,			//���a�B 
		30.0f,			//�����B
		m_position		//�����ʒu�B
	);
	//�A�j���[�V�����t�@�C�������[�h
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"Asset/animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/unityChan/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"Asset/animData/unityChan/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/unityChan/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"Asset/animData/unityChan/KneelDown.tka");
	m_animClip[enAnimationClip_Clear].Load(L"Asset/animData/unityChan/Clear.tka");
	m_animClip[enAnimationClip_Test].Load(L"Asset/animData/unityChan/Zangeki1.tka",false,enZtoY);
	//�A�j���[�V�����̃��[�v�t���O��true�ɂ���
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	//�ꕔ�A�j���[�V�����̃��[�v�t���O��false�ɂ���
	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_Clear].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_Test].SetLoopFlag(false);
	//unityChan��\��
	m_skinModelRender = new GameObj::CSkinModelRender;
    m_skinModelRender->Init(L"Resource/modelData/unityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);
	m_skinModelRender->SetPos(m_position);
	m_sword = new Sword;
	//unityChan�̃{�[��������
	m_bonehand=m_skinModelRender->FindBoneID(L"Character1_RightHand");
	CVector3 pos=m_skinModelRender->GetBonePos(m_bonehand);
	CQuaternion qRot= m_skinModelRender->GetBoneRot(m_bonehand);
	m_sword->SetRot(qRot);
	m_sword->SetPosition(pos);
	Status();
	return true;
}
void Player::Update()
{
	//�L�����N�^�[�̃A�j���[�V�����̏����A�ړ����]�������Ă�
	AnimationController();
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_movespeed.y = 0.0f;
	}
	m_charaCon.SetPosition(m_position);
	m_skinModelRender->SetPos(m_position);
	Kougeki();
	
}

void Player::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��擾
	CVector2 stickL;
	
	if (m_state == enState_Damage) {
		stickL = { 0.0f,0.0f };
	}
	else {
		stickL = Pad(0).GetStick(L);	//�A�i���O�X�e�B�b�N�̓��͗ʂ��擾�B
		if (Pad(0).GetButton(enButtonA) //A�{�^���������ꂽ��
			&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
			) {
			//�W�����v����B
			m_movespeed.y = 500.0f;	//������ɑ��x��ݒ肵�āA
			m_state = enState_Jump;
		}
	}
	stickL.x = -stickL.x;
	//���X�e�B�b�N
	//�X�e�B�b�N�̍��E���͂̏���
	m_movespeed.z = 0.0f;
	m_movespeed.x = 0.0f;
	m_movespeed.z = +sin(m_radian)*stickL.x * m_multiply;
	m_movespeed.x = -cos(m_radian)*stickL.x * m_multiply;
	//�X�e�B�b�N�̏㉺���͂̏���
	m_movespeed.z += cos(m_radian)*stickL.y * m_multiply;
	m_movespeed.x += sin(m_radian)*stickL.y * m_multiply;
	//�d��
	m_movespeed.y -= 800.0f *GetDeltaTimeSec();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	m_position = m_charaCon.Execute(m_movespeed, GetDeltaTimeSec());
	
}

void Player::Turn()
{
	CVector3 rotation = {0.0f,0.0f,0.0f};
	//���@�̊p�x�̍���
	float sdegree = 0.0f;
	m_radian = M_PI / 180 * m_degree;
	//�E�X�e�B�b�N
	CVector2 stickR;
	stickR = Pad(0).GetStick(R);	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickR.x = -stickR.x;
	//����
	//�E�X�e�B�b�N
	sdegree = -stickR.x * 2.0f;
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
	m_rotation.SetRotation({0.0f,1.0f,0.0f}, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
	
}

void Player::Animation()
{
	if (Pad(0).GetButton(enButtonB)) {
		m_state = enState_Damage;
	}
	else if (Pad(0).GetButton(enButtonX)) {
		m_state = enState_Test;
	}
	if (Pad(0).GetButton(enButtonY)) {
		m_state = enState_GameOver;
	}
}

void Player::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f);
	//�X�e�[�g����ɂ���ăA�j���[�V�������Đ�������
	switch (m_state) {
	case enState_Run:
	case enState_Idle:
		if (m_movespeed.LengthSq() > 300.0f * 300.0f) {
			//���胂�[�V�����B
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		else if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			//�������[�V�����B
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_walk, 0.2f);
		}
		else {
			//�ҋ@���[�V����
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		}
		if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			m_state = enState_Run;
		}
		else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
			m_state = enState_Idle;
		}
		Move();
		//�L�����N�^�[�̌����֌W
		Turn();
		Animation();
		break;
	case enState_Damage:
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
		}
		else {
			if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
				m_state = enState_Run;
			}
			else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				m_state = enState_Idle;
			}
		}
		Move();
		//�L�����N�^�[�̌����֌W
		Turn();
		break;
	case enState_GameClear:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_Clear, 0.2f);
		break;
	case enState_GameOver:
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_KneelDown, 0.2f);
		}
		else {
			if (Pad(0).GetButton(enButtonSelect)) {
				m_gameover = true;
			}
		}
		break;
		//�W�����v�����͑��̂Ƃ��ł��
	case enState_Jump:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_jump, 0.2f);
		if (!m_charaCon.IsJump()) {
			if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				//���͂��Ȃ��Ȃ����B
				m_state = enState_Idle;
			}
			else {
				m_state = enState_Run;
			}
		}
		Move();
		//�L�����N�^�[�̌����֌W
		Turn();
		Animation();
		break;
	case enState_Test:
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_Test, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(2.0f);
			Animation();
		}
		else {
			if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
				m_state = enState_Run;
			}
			else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				m_state = enState_Idle;
			}
		}
		//�L�����N�^�[�̌����֌W
		Turn();
		break;
	}
}

void Player::Status()
{
	m_level = m_playerstatus->GetLevel();
	m_MaxHP = m_playerstatus->GetMaxHP();
	m_MaxPP = m_playerstatus->GetMaxPP();
	m_Attack = m_playerstatus->GetAttack();
	m_Defense = m_playerstatus->GetDefense();
	m_HP = m_MaxHP;
	m_PP = m_MaxPP;
}  

void Player::PostRender()
{
	wchar_t output[256];
	swprintf_s(output, L" %f\n %f\n %f\n %f\n", m_HP, m_PP, m_Attack, m_Defense);
	m_font.DrawScreenPos(output, { 800.0f,100.0f });
}

void Player::Kougeki()
{
	if (m_state == enState_Test) {
		CVector3 pos = m_skinModelRender->GetBonePos(m_bonehand);
		CQuaternion qRot = m_skinModelRender->GetBoneRot(m_bonehand);
		m_sword->SetRot(qRot);
		m_sword->SetPosition(pos);
		m_sword->SetScale({ 1.0f, 1.0f, 1.0f });
	}
	else {
		m_sword->SetScale({ 0.001f, 0.001f, 0.001f });
	}
}