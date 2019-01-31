#include "stdafx.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
#include "Sword.h"
#include "GameCamera.h"
#include "PlayerStatus.h"
#include "IEnemy.h"
#include "ShotMagic.h"
#include "Human.h"
#include "Merchant.h"
#include "Effekseer.h"
const float Player::m_frame = 40.0f;
Player::Player()
{
}

Player::~Player()
{
	delete m_skinModelRender;
	delete m_sword;
	m_collision->Delete();
}

void Player::unityChan()
{
	//�A�j���[�V�����t�@�C�������[�h
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"Asset/animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/unityChan/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"Asset/animData/unityChan/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/unityChan/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"Asset/animData/unityChan/KneelDown.tka");
	m_animClip[enAnimationClip_Clear].Load(L"Asset/animData/unityChan/Clear.tka");
	m_animClip[enAnimationClip_attack].Load(L"Asset/animData/unityChan/attack.tka", false, enZtoY);
	m_animClip[enAnimationClip_aria].Load(L"Asset/animData/unityChan/aria.tka", false, enZtoY);
	//�A�j���[�V�����̃��[�v�t���O��true�ɂ���
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	//�ꕔ�A�j���[�V�����̃��[�v�t���O��false�ɂ���
	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_Clear].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_attack].SetLoopFlag(false);
	m_animClip[enAnimationClip_aria].SetLoopFlag(false);
	//unityChan��\��
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/unityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetRot(m_rotation);
	m_sword = new Sword;
	//unityChan�̃{�[��������
	m_bonehand = m_skinModelRender->FindBoneID(L"Character1_RightHand");
	m_bonecenter = m_skinModelRender->FindBoneID(L"center");
	CQuaternion qRot = m_skinModelRender->GetBoneRot(m_bonecenter);
	m_sword->SetRot(qRot);
	CVector3 pos = m_position;
	pos.y += 170.0f;
	pos.x -= 70.0f;
	pos.z += 10.0f;
	m_sword->SetPosition(pos);
	m_sword->SetSwordId(m_SwordId);
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
}

void Player::cagliostro()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/cagliostro.cmo");
	m_scale = {1.0f, 1.0f, 1.0f};
	m_skinModelRender->SetScale(m_scale);
}

bool Player::Start()
{
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,			//���a�B 
		40.0f,			//�����B
		m_position		//�����ʒu�B
	);
	//���炢����̍쐬
	m_collision = new SuicideObj::CCollisionObj;
	//�`��̍쐬
	m_collision->CreateSphere(m_position + CVector3::AxisY()*m_collisionUp, CQuaternion::Identity(), m_r);
	//������ݒ�
	m_collision->SetTimer(enNoTimer);//enNoTimer�Ŏ����Ȃ�
	//���O��ݒ�
	m_collision->SetName(L"Player");
	//�N���X�̃|�C���^��ݒ�
	m_collision->SetClass(this);
	//�v���C���[�X�e�[�^�X�N���X�̃|�C���^�������������`
	m_playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
	Status();
	WeaponStatus();
	MagicStatus();
	if (m_cagliostro) {
		cagliostro();
	}
	else {
		unityChan();
	}

	return true;
}
void Player::Update()
{
	if (m_cagliostro) {
	}
	else {
		if (m_stop) {
			Turn();
		}
		else {
			//�L�����N�^�[�̃A�j���[�V�����̏����A�ړ����]�������Ă�
			AnimationController();
			Kougeki();
			SwitchWeapon();
		}
	}
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_movespeed.y = 0.0f;
		m_isjump = false;
	}
	m_charaCon.SetPosition(m_position);
	m_skinModelRender->SetPos(m_position);
	m_collision->SetPosition(m_position + CVector3::AxisY()*m_collisionUp);
	if (m_PPtimer >= 50) {
		if (m_PP < m_MaxPP) {
			m_PP++;
			m_PPtimer = 0.0f;
		}
	}
	RelationHuman();
	RelationMerchant();
	//�U���͏㏸���@
	Shihuta();
	//PlayerStatus�N���X�̃����o�ϐ����v���C���[�̃����o�ϐ��ɔ��f
	Status();
	LevelUp();
	//OutTarget();
	m_PPtimer += m_frame * GetDeltaTimeSec();
	m_timer2 += m_frame * GetDeltaTimeSec();
}

void Player::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��擾
	CVector2 stickL;
	//�_���[�W���󂯂Ă���Ƃ��A�Q�[���I�[�o�[�̎��A�Q�[���N���A�̎��͉E�X�e�B�b�N�̓��͂𖳌��ɂ���
	if (m_state == enState_Damage || m_state==enState_GameOver || m_state==enState_GameClear) {
		stickL = { 0.0f,0.0f };
	}
	else {
		stickL = Pad(0).GetStick(L);	//�A�i���O�X�e�B�b�N�̓��͗ʂ��擾�B
		if (Pad(0).GetDown(enButtonA) //A�{�^���������ꂽ��
			&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
			) {
			//�W�����v����B
			m_movespeed.y = 500.0f;	//������ɑ��x��ݒ肵�āA
			m_state = enState_Jump;
			m_isjump = true;
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
	m_playerheikou = moveSpeedXZ;
	m_rotation.SetRotation({0.0f,1.0f,0.0f}, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
}

void Player::Animation()
{
	//�_���[�W���󂯂���
	if (m_damage) {
		m_state = enState_Damage;
		m_damage = false;
	}
	//X�{�^������������
	else if (Pad(0).GetDown(enButtonX) && m_timer>=15) {
		if (m_state != enState_Attack) {
			m_state = enState_Attack;
			m_timer = 0;
		}
	}
	//Y�{�^������������
	else if (Pad(0).GetButton(enButtonY) && m_timer >= 15) {
		if (m_state != enState_Aria) {
			if (m_PP >= m_PPCost) {
				m_state = enState_Aria;
				m_timer = 0;
				m_PP -= m_PPCost;
			}
		}
	}
	if (m_HP <= 0 || Pad(0).GetButton(enButtonLT)) {
		m_state = enState_GameOver;
	}
	else if (Pad(0).GetButton(enButtonLB1)) {
		m_state = enState_GameClear;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}

void Player::ClearVoice()
{
	//SE
	if (m_state == enState_GameClear) {
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/clear.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(2.6f);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
	}
	else {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/gameover.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(2.6f);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
	}
}

void Player::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f*60.0f*GetDeltaTimeSec());
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
			//�A�j���[�V�����̍Đ����I�������A�ĂуA�j���[�V��������
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
		m_sword->SetScale({ 0.001f,0.001f,0.001f });
		if (!m_clear_over_voice) {
			ClearVoice();
			m_clear_over_voice = true;
		}
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {

		}
		else {
			//�A�j���[�V�����̍Đ����I�������A�N���A�t���O��ON�ɂ���
			if (Pad(0).GetButton(enButtonBack)) {
				m_gameclear = true;
				m_transscene = true;
			}
		}
		Move();
		Turn();
		break;
	case enState_GameOver:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_KneelDown, 0.2f);
		m_sword->SetScale({ 0.001f,0.001f,0.001f });
		if (!m_clear_over_voice) {
			ClearVoice();
			m_clear_over_voice = true;
		}
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
		}
		else {
			//�A�j���[�V�����̍Đ����I�������A�Q�[���I�[�o�[�t���O��ON�ɂ���
			if (Pad(0).GetButton(enButtonBack)) {
				m_gameover = true;
				m_transscene = true;
			}
		}
		Move();
		//�L�����N�^�[�̌����֌W
		Turn();
		break;
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
	case enState_Attack:
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump==true) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(7.0f*60.0f*GetDeltaTimeSec());
			Animation();
			m_isjump = false;
			m_timer = 0;
		}
		else {
			//�A�j���[�V�����̍Đ����I�������A�A�j���[�V��������
			m_timer += m_frame * GetDeltaTimeSec();
			if (m_timer >= 20) {
				if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
					m_state = enState_Run;
				}
				else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
					m_state = enState_Idle;
				}
				m_timer = 0;
			}
			
		}
		//�L�����N�^�[�̌����֌W
		Turn();
		break;
	case enState_Aria:
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump == true) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_aria, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(1.0f*60.0f*GetDeltaTimeSec());
			Animation();
			m_isjump = false;
			m_timer = 0;
		}
		else {
			//�A�j���[�V�����̍Đ����I�������A�A�j���[�V��������
			m_timer += m_frame * GetDeltaTimeSec();
			if (m_timer >= 20) {
				if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
					m_state = enState_Run;
				}
				else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
					m_state = enState_Idle;
				}
				m_timer = 0;
			}
		}
		//�L�����N�^�[�̌����֌W
		Turn();
		break;
	}
}

void Player::Status()
{
	//�v���C���[�X�e�[�^�X�N���X�̌o���l���v���C���[�N���X�ɉ��Z
	m_Exp = m_playerstatus->GetExp();
	m_NextExp = m_playerstatus->GetNextExp();
	//���x���A�b�v���ĂȂ������珈�����I������
	if (m_Level == m_playerstatus->GetLevel()) {
		return;
	}
	else {
		//���x���A�b�v���Ă���A�v���C���[�X�e�[�^�X�N���X�̃X�e�[�^�X�𔽉f�A���ł�HP��PP��
		m_Level = m_playerstatus->GetLevel();
		m_MaxHP = m_playerstatus->GetMaxHP();
		m_MaxPP = m_playerstatus->GetMaxPP();
		m_Attack = m_playerstatus->GetAttack();
		m_ShihutaAttack = m_Attack;
		m_Mattack = m_playerstatus->GetMattack();
		m_HP = m_MaxHP;
		m_PP = m_MaxPP;
		m_SwordId = m_playerstatus->GetSwordId();
	}
}  

void Player::Kougeki()
{
	//�U�����Ă���Ƃ��͕���̈ʒu��unityChan�̎�Ɉړ�������
	if (m_state == enState_Attack) {
		CVector3 pos = m_skinModelRender->GetBonePos(m_bonehand);
		CQuaternion qRot = m_skinModelRender->GetBoneRot(m_bonehand);
		m_sword->SetRot(qRot);
		m_sword->SetPosition(pos);
	}
	//�U�����Ă��Ȃ��Ƃ��́A�����unityChan�̔w���Ɉړ�������
	else {
		CVector3 pos = m_playerheikou;
		CQuaternion qRot;
		qRot.SetRotation({0.0f,1.0f,0.0f}, -90.0f);
		pos.Normalize();
		pos *= 10.0f;
		pos = m_position - pos;
		pos.y += 70.0f;
		CQuaternion qRot2;
		qRot2.SetRotation({ 0.0f,1.0f,0.0f }, -90.0f);
		CVector3 pos2 = m_playerheikou;
		pos2.Normalize();
		qRot2.Multiply(pos2);
		pos2 *= 70.0f;
		pos += pos2;
		m_sword->SetPosition(pos);
		CQuaternion qRot3 = m_skinModelRender->GetBoneRot(m_bonecenter);
		m_sword->SetRot(qRot3);
	}
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName,L"attack")==0) {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/attack.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(2.6f);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
		//�U������̔���
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//�`��̍쐬
		CVector3 pos = m_position + CVector3::AxisY()*60.0f;
		pos += m_playerheikou * 90.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), 70.0f);
		//������ݒ�
		attackCol->SetTimer(3);//15�t���[����폜�����
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//�Փ˂�������̖��O��"IEnemy"�Ȃ�m_Attack�������_���[�W�^����
			if (param.EqualName(L"IEnemy")) {
				IEnemy* enemy = param.GetClass<IEnemy>();//����̔���ɐݒ肳��Ă���CEnemy�̃|�C���^���擾
				//�G�l�~�[�Ƀ_���[�W
				enemy->Damage(m_Attack);
				//�����G�l�~�[��HP��0�ȉ��ɂȂ�����
				if (enemy->GetDeath()) {
					//�G�l�~�[�̌o���l���v���C���[�̌o���l�ɉ��Z
					m_playerstatus->PlusExp(enemy->GetExp());
				}
			}
		}
		);
	}
	//�����r���X�^�[�g�I
	else if (wcscmp(eventName, L"aria_start") == 0) {
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		effect->Play(L"Asset/effect/efk/magic_cast01.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
		effect->SetSpeed(2.0f);
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/aria.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(2.6f);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
	}
	//���@�𔭐�������
	else if (wcscmp(eventName, L"aria") == 0) {
		ShotMagic* shotmagic = new ShotMagic;
		shotmagic->SetPosition(m_position);
		shotmagic->SetDirectionPlayer(m_playerheikou);
		shotmagic->SetId(m_MagicId);
		shotmagic->SetDamage(m_Mattack, m_DamageRate);
		shotmagic->SetName(L"ShotMagic");
	}
}

void Player::Damage(const int& attack)
{
	//�Q�[���I�[�o�[���Q�[���N���A�̏ꍇ�A�_���[�W�̏��������Ȃ�
	if (m_state == enState_GameOver || m_state==enState_GameClear) {
		return;
	}
	else if (m_timer2 >= 30) {
		m_HP -= attack;
		//HP��0��菬�����Ȃ�����0�ɂ���
		if (m_HP < 0) {
			m_HP = 0;
		}
		m_damage = true;
		m_timer2 = 0;
	}
}

void Player::WeaponStatus()
{
	m_Mattack = m_playerstatus->GetMattack();
	m_Attack = m_playerstatus->GetAttack();
	m_ShihutaAttack = m_Attack;
	m_SwordId = m_playerstatus->GetSwordId();
	m_SwordName = m_playerstatus->GetSwordName();
	m_MagicId = m_playerstatus->GetMagicId();
}

void Player::MagicStatus()
{
	m_MagicName = m_playerstatus->GetMagicName();
	m_DamageRate = m_playerstatus->GetDamageRate();
	m_PPCost = m_playerstatus->GetPPCost();
}

void Player::SwitchWeapon()
{
	if (!Pad(0).GetButton(enButtonLeft) && !Pad(0).GetButton(enButtonRight)) {
		m_isbutton=true;
	}
	//���O�Ƀ{�^���������Ă��Ȃ��Ƃ��ɂ����A���͂�L���ɂ���
	if (m_isbutton) {
		//���{�^��
		if (Pad(0).GetButton(enButtonLeft)) {
			m_isbutton = false;
			//����̐؂�ւ����L���ł������Ȃ�Ε���̃X�e�[�^�X�𔽉f������
			if (m_playerstatus->GetWeapon(m_SwordId - 1)) {
				WeaponStatus();
				MagicStatus();
			}
			else {
				return;
			}
		}
		//�E�{�^��
		if (Pad(0).GetButton(enButtonRight)) {
			m_isbutton = false;
			//����̐؂�ւ����L���ł������Ȃ�Ε���̃X�e�[�^�X�𔽉f������
			if (m_playerstatus->GetWeapon(m_SwordId + 1)) {
				WeaponStatus();
				MagicStatus();
			}
			else {
				return;
			}
		}
	}
	m_sword->SetSwordId(m_SwordId);
}

void Player::RecoveryPP()
{
	m_PP += m_AttackRecoveryPP;
	if (m_PP > m_MaxPP) {
		m_PP = m_MaxPP;
	}
}

void Player::LevelUp()
{
	if (m_playerstatus->GetLevelUp()) {
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		CVector3 pos = m_position;
		pos.y += m_height;
		effect->Play(L"Asset/effect/lvup/lvup.efk", 1.0f, pos, CQuaternion::Identity(), { 20.0f,20.0f,20.0f });
		effect->SetSpeed(1.5f);
		m_playerstatus->OffLevelUp();
	}
}

void Player::Shihuta()
{
	if (m_Shihuta) {
		m_Attack = (int)(m_ShihutaAttack * m_AttackMultiply);
		m_Shihutatimer += 40.0f * GetDeltaTimeSec();
		if (m_Shihutatimer >= m_Shihutatime) {
			m_Shihuta = false;
			m_Shihutatimer = 0;
		}
	}
	else {
		m_Attack = m_ShihutaAttack;
	}
}

void Player::RelationHuman()
{
	if (m_human == nullptr) {
		m_human = FindGO<Human>(L"Human");
		return;
	}
	CVector3 pos = m_human->GetPosition() - m_position;
	//�ҋ@��Ԃ����������ȓ��̎���B�{�^���������Ƙb����
	if (pos.Length() <= 300.0f && m_state==enState_Idle) {
		if (Pad(0).GetDown(enButtonB)) {
			if (m_human->GetTalk() && m_human->isLevelUpTown()) {
				m_human->SetLevelUpTown();
			}
			m_human->OnTalk();
			m_stop = true;
		}
		if (Pad(0).GetDown(enButtonA)) {
			m_human->OffTalk();
			m_stop = false;
		}
	}
}

void Player::RelationMerchant()
{
	if (m_merchant == nullptr) {
		m_merchant = FindGO<Merchant>();
		return;
	}
	CVector3 pos = m_merchant->GetPosition() - m_position;
	if (pos.Length() <= 300.0f && m_state == enState_Idle) {
		if (Pad(0).GetDown(enButtonB)) {
			if (m_merchant->GetTalk()) {

			}
			else {
				m_merchant->SetTalk();
				m_stop = true;
			}
		}
		else if (Pad(0).GetDown(enButtonA)) {
			if (m_merchant->GetTalk()) {
				m_merchant->OffTalk();
				m_stop = false;
			}
		}
	}
}

void Player::OutTarget()
{
	std::vector<CVector3> enemyList;
	int enemynumber = 0;
	CVector3 target;
	QueryGOs<IEnemy>(L"Enemy", [&](IEnemy* enemy)
	{
		CVector3 pos = enemy->GetCollisionPosition();
		enemyList.push_back(pos);
		enemynumber++;
		return true;
	});
	if (enemynumber == 0) {
		m_gamecamera->OffTage();
		return;
	}
	target = m_position - enemyList[0];
	for (int i = 0; i < enemynumber; i++) {
		CVector3 pos = m_position - enemyList[enemynumber];
		
		if (target.Length() > pos.Length()) {
			target = pos;
		}
	}
	m_target = target;
	m_gamecamera->SetTarget(m_target);
	m_gamecamera->SetTage();
}

void Player::PostRender()
{
	if (m_transscene) {
		return;
	}
	wchar_t output[256];
	swprintf_s(output, L"Lv   %d\nExp  %d\nNexp %d\nHP   %d\nPP   %d\nAtk  %d\nMatk %d\nWpn  %s\nMgc  %s\nMPC  %d\nMgg  %d\nWLv  %d\n", m_Level, m_Exp, m_NextExp, m_HP, m_PP, m_Attack, m_Mattack, m_SwordName, m_MagicName, m_PPCost, int(m_Mattack*m_DamageRate),m_playerstatus->GetWeaponLv(m_SwordId));
	//swprintf_s(output, L"x   %f\ny   %f\nz  %f\nw   %f\n", m_swordqRot.x, m_swordqRot.y, m_swordqRot.z, m_swordqRot.w);
	m_font.DrawScreenPos(output, { 700.0f,100.0f }, CVector4(200.0f, 00.0f, 100.0f, 1.0f));
	/*m_sprite.DrawScreenPos(CVector2::Zero(), CVector2::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.4f);*/
	//�Q�[���I�[�o�[�\��
	if (m_state == enState_GameOver && !m_skinModelRender->GetAnimCon().IsPlaying()) {
		if (!m_displaysprite) {
			m_sprite2.Init(L"Resource/sprite/gameover.dds");
			m_displaysprite = true;
		}
		m_sprite2.DrawScreenPos(CVector2::Zero(), CVector2::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
	}
	//�Q�[���N���A�\��
	else if (m_state == enState_GameClear && !m_skinModelRender->GetAnimCon().IsPlaying()) {
		if (!m_displaysprite) {
			m_sprite2.Init(L"Resource/sprite/clear.dds");
			m_displaysprite = true;
		}
		m_sprite2.DrawScreenPos(CVector2::Zero(), CVector2::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
	}
}