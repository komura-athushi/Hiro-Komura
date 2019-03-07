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
#include "Morugan.h"
#include "Town.h"
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
	m_sword->SetSwordId(m_WeaponNumber);
	//�A�j���[�V�����C�x���g�̃R�[���o�b�N�֐���ݒ�
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
	//�F�X��dds�t�@�C���ǂݍ���
	m_targetsprite.Init(L"Resource/sprite/target.dds");
	m_locktargetsprite.Init(L"Resource/sprite/locktarget.dds");
	m_statussprite.Init(L"Resource/sprite/status.dds");
	m_weaponstatussprite.Init(L"Resource/sprite/weaponstatus.dds");
	m_inventorystatussprite.Init(L"Resource/sprite/inventorystatus.dds");
	m_hpframe.Init(L"Resource/sprite/hpframe.dds");
	m_hpgage.Init(L"Resource/sprite/hpgage.dds");
	m_ppframe.Init(L"Resource/sprite/ppframe.dds");
	m_ppgage.Init(L"Resource/sprite/ppgage.dds");
	m_hud.Init(L"Resource/sprite/hud.dds");
	m_logo.Init(L"Resource/sprite/logo.dds");
}

void Player::cagliostro()
{
	//�J���I�X�g������񃂁[�h�̂Ƃ��̓J���I�X�g���̃��f�������[�h
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/cagliostro.cmo");
	m_scale = {1.0f, 1.0f, 1.0f};
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetIsShadowCaster(false);
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
	m_town = FindGO<Town>();
	//�X�e�[�^�X
	Status();
	//����̃X�e�[�^�X
	WeaponStatus();
	//���@
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
		//��~��ԂȂ��]����
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
	m_collision->SetPosition(m_position + CVector3::AxisY() * m_collisionUp);
	//��莞�Ԍo�߂�����pp��������
	if (m_PPtimer >= m_PPtime) {
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
	//�I�[�g�^�[�Q�b�e�B���O
	OutTarget();
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
	m_movespeed.z = 0.0f;
	m_movespeed.x = 0.0f;
	//�J�����̑O���ƉE�����̃x�N�g�����擾
	CVector3 frontxz = m_gamecamera->GetFront();
	CVector3 rightxz = m_gamecamera->GetRight();
	//��L�̃x�N�g�����X�e�B�b�N�̓��͗ʂɉ����ď�Z
	frontxz *= stickL.y;
	rightxz *= stickL.x;
	//�v�Z�����x�N�g�����ړ����x�ɉ��Z
	m_movespeed += frontxz * m_multiply;
	m_movespeed += rightxz * m_multiply;
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
	moveSpeedXZ.y = 0.0f;
	//�ړ����x�����ȉ��A�܂���͂��Ȃ��ꍇ�A�������I��
	if (moveSpeedXZ.LengthSq() < 0.5f) {
		return;
	}
	m_playerheikou = moveSpeedXZ;
	//�ړ����x�̃x�N�g������p�x�����߂āA���̕��L�����N�^�[����]������
	m_rotation.SetRotation({0.0f,1.0f,0.0f}, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
}

void Player::Animation()
{
	//X�{�^������������A�ʏ�U��
	if (Pad(0).GetDown(enButtonX) && m_timer >= m_attacktime) {
		if (m_state != enState_Attack) {
			m_state = enState_Attack;
			m_timer = 0;
		}
	}
	//Y�{�^������������A�e�N�j�b�N����
	else if (Pad(0).GetButton(enButtonY) && m_timer >= m_attacktime) {
		if (m_state != enState_Aria) {
			if (m_PP >= m_PPCost) {
				if (m_MagicId == 7) {                                                    
					if (m_targetdisplay) {
						m_playerheikou = m_attacktarget;
						m_state = enState_Aria;
						m_timer = 0;
						m_PP -= m_PPCost;
					}
				}
				else {
					if (m_targetdisplay) {
						m_playerheikou = m_attacktarget;
					}
					m_state = enState_Aria;
					m_timer = 0;
					m_PP -= m_PPCost;
				}
			}
		}
	}
	if (m_town == nullptr) {
		//LT��������Q�[���I�[�o�[
		if (m_HP <= 0 || Pad(0).GetButton(enButtonLT)) {
			m_state = enState_GameOver;
		}
		//LB1��������Q�[���N���A
		else if (Pad(0).GetButton(enButtonRT)) {
			m_state = enState_GameClear;
		}
	}
	if (Pad(0).GetDown(enButtonStart)) {
		if (!m_displaystatus) {
			m_displaystatus = true;
		}
		else {
			m_displaystatus = false;
		}
		int a = 0;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}

void Player::ClearVoice()
{
	//SE
	if (m_state == enState_GameClear) {
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/clear.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(m_voicevolume);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
	}
	else {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/gameover.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(m_voicevolume);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
	}
}

void Player::AnimationController()
{
	//�A�j���[�V�����̍Đ����x���σt���[���ɑΉ�������
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f * 60.0f * GetDeltaTimeSec());
	//�X�e�[�g����ɂ���ăA�j���[�V�������Đ�������
	switch (m_state) {
	case enState_Run:
	case enState_Idle:
		//	��葬�x�ȏ�Ȃ瑖�胂�[�V����
		if (m_movespeed.LengthSq() > 300.0f * 300.0f) {
			//���胂�[�V�����B
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		//��葬�x�ȏォ�A��葬�x�ȉ��Ȃ�������[�V����
		else if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			//�������[�V�����B
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_walk, 0.2f);
		}
		//��葬�x�ȉ��Ȃ�ҋ@���[�V����
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
		//�ړ�
		Move();
		//�L�����N�^�[�̌����֌W
		Turn();
		Animation();
		break;
	case enState_Damage:
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump || m_aria || m_isattack) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
			m_aria = false;
			m_isjump = false;
			m_isattack = false;
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
		//�N���A���[�V�����̎��ɂ͌��͌����Ȃ�����
		m_sword->SetScale({ 0.001f,0.001f,0.001f });
		if (!m_clear_over_voice) {
			//�N���A�{�C�X
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
			//�Q�[���I�[�o�[�{�C�X
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
		//�W�����v���I�������
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
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(7.0f * 60.0f * GetDeltaTimeSec());
			Animation();
			m_isjump = false;
			m_timer = 0;
			m_isattack = true;
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
				m_isattack = false;
			}
			
		}
		//�L�����N�^�[�̌����֌W
		Turn();
		break;
	case enState_Aria:
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump == true) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_aria, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(1.0f * 60.0f * GetDeltaTimeSec());
			Animation();
			m_isjump = false;
			m_timer = 0;
			m_aria = true;
		}
		else {
			//�A�j���[�V�����̍Đ����I�������A�A�j���[�V��������
			m_timer += m_frame * GetDeltaTimeSec();
			if (m_MagicId == 8) {
				if (m_timer >= m_morugantime) {
					if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
						m_state = enState_Run;
					}
					else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
						m_state = enState_Idle;
					}
					m_timer = 0;
					m_aria = false;
				}
			}
			else {
				if (m_timer >= 20) {
					if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
						m_state = enState_Run;
					}
					else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
						m_state = enState_Idle;
					}
					m_timer = 0;
					m_aria = false;
				}
			}
		}
		//�L�����N�^�[�̌����֌W
		//Turn();
		//�^�[�Q�b�g���W�ɉ����ăL�����N�^�[����]������
		float degree = atan2f(m_attacktarget.x, m_attacktarget.z);
		CQuaternion qRot;
		qRot.SetRotation(CVector3::AxisY(), degree);
		m_skinModelRender->SetRot(qRot);
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
		//��̃{�[���̍��W�Ɖ�]�����ɔ��f������
		CVector3 pos = m_skinModelRender->GetBonePos(m_bonehand);
		CQuaternion qRot = m_skinModelRender->GetBoneRot(m_bonehand);
		m_swordrot = qRot;
	    m_swordposition = pos;
	}
	//�U�����Ă��Ȃ��Ƃ��́A�����unityChan�̔w���Ɉړ�������
	else {
		//������ӂȂɂ���Ă�����
		//�v���C���[�̌���̃x�N�g�����擾���A�v���C���[�̌���ɕ���̍��W��ݒ肷��
		CVector3 pos = m_playerheikou;
		CQuaternion qRot;
		qRot.SetRotation({0.0f,1.0f,0.0f}, -90.0f);
		pos.Normalize();
		pos *= 10.0f;
		pos = m_position - pos;
		//y���W�����Z����
		pos.y += 70.0f;
		CQuaternion qRot2;
		qRot2.SetRotation({ 0.0f,1.0f,0.0f }, -90.0f);
		CVector3 pos2 = m_playerheikou;
		pos2.Normalize();
		qRot2.Multiply(pos2);
		pos2 *= 70.0f;
		pos += pos2;
		m_swordposition = pos;
		//�v���C���[�̂ǂ����̃{�[���̉�]�����̉�]�ɔ��f
		CQuaternion qRot3 = m_skinModelRender->GetBoneRot(m_bonecenter);
		m_swordrot = qRot3;
	}
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName,L"attack") == 0) {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/attack.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(m_voicevolume);
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
		//�����r���̃G�t�F�N�g�𔭐�������
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		switch (m_MagicId) {
		case 1:
			effect->Play(L"Asset/effect/Effects/efk/cast_fire.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 2:
			effect->Play(L"Asset/effect/Effects/efk/cast_ice.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 3:
			effect->Play(L"Asset/effect/Effects/efk/cast_wind.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 4:
			effect->Play(L"Asset/effect/Effects/efk/cast_sphere.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 5:
			effect->Play(L"Asset/effect/Effects/efk/cast_sphere.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 6:
			effect->Play(L"Asset/effect/Effects/efk/cast_sphere.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 7:
			effect->Play(L"Asset/effect/Effects/efk/cast_sword.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 8:
			effect->Play(L"Asset/effect/Effects/efk/cast_laser.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		}
		effect->SetSpeed(2.0f);
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/aria.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(m_voicevolume);
		int i = 0;
		if (i == 0) {
			//SE
			SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/aria.wav");
			se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
			se->SetVolume(m_lvupvollume);
			//3D�Đ�
			se->SetPos(m_position);//���̈ʒu
			se->SetDistance(200.0f);//������������͈�
			se->Play(true); //��������true
		}
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
	}
	//���@�𔭐�������
	else if (wcscmp(eventName, L"aria") == 0) {
		//���̖��@�����͑��ƈႤ�N���X���g��
		if (m_MagicId == 8) {
			Morugan* morugan = new Morugan;
			morugan->SetDamage(m_Mattack, m_DamageRate);
			morugan->SetPosition(m_position + CVector3::AxisY() * m_height);
			morugan->SetRotation(m_rotation);
		}
		else {
			ShotMagic* shotmagic = new ShotMagic;
			if (m_MagicId == 7) {
				shotmagic->SetPosition(m_target);
			}
			else {
				shotmagic->SetPosition(m_position);
			}
			shotmagic->SetDirectionPlayer(m_attacktarget);
			shotmagic->SetId(m_MagicId);
			shotmagic->SetDamage(m_Mattack, m_DamageRate);
			shotmagic->SetName(L"ShotMagic");
		}
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
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/bad.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(m_voicevolume);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
		if (0 == 0) {
			SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/hidamage.wav");
			se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
			se->SetVolume(m_lvupvollume+1.2f);
			//3D�Đ�
			se->SetPos(m_position);//���̈ʒu
			se->SetDistance(500.0f);//������������͈�
			se->Play(true); //��������true
		}
		m_damage = true;
		m_timer2 = 0;
		m_state = enState_Damage;
	}
}

void Player::WeaponStatus()
{
	m_Mattack = m_playerstatus->GetMattack();
	m_Attack = m_playerstatus->GetAttack();
	m_ShihutaAttack = m_Attack;
	m_SwordId = m_playerstatus->GetSwordId();
	m_WeaponNumber = m_playerstatus->GetWeaponNumber(m_SwordId);
	m_SwordName = m_playerstatus->GetSwordName();
	m_MagicId = m_playerstatus->GetMagicId();
	m_MaxHP = m_playerstatus->GetMaxHP();
	if (m_HP > m_MaxHP) {
		m_HP = m_MaxHP;
	}
	m_MaxPP = m_playerstatus->GetMaxPP();
	if (m_PP > m_MaxPP) {
		m_PP = m_MaxPP;
	}
}

void Player::MagicStatus()
{
	m_MagicName = m_playerstatus->GetMagicName();
	m_DamageRate = m_playerstatus->GetDamageRate();
	m_PPCost = m_playerstatus->GetPPCost();
}

void Player::SwitchWeapon()
{
	//����̃A�j���[�V�����Đ����͕���̐؂�ւ������܂���
	if (m_state == enState_Aria || m_state == enState_Attack || m_state == enState_Damage || m_state == enState_GameClear ||
		m_state == enState_GameOver) {
		return;
	}
	if (!Pad(0).GetButton(enButtonLB1) && !Pad(0).GetButton(enButtonRB1)) {
		m_isbutton = true;
	}
	//���O�Ƀ{�^���������Ă��Ȃ��Ƃ��ɂ����A���͂�L���ɂ���
	if (m_isbutton) {
		//���{�^��
		if (Pad(0).GetButton(enButtonLB1)) {
			m_isbutton = false;
			//����̐؂�ւ����L���ł������Ȃ�Ε���̃X�e�[�^�X�𔽉f������
			if (m_playerstatus->GetWeapon(m_SwordId - 1)) {
				WeaponStatus();
				MagicStatus();
				//SE
				SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/swtich.wav");
				se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
				se->SetVolume(m_voicevolume);
				//3D�Đ�
				se->SetPos(m_position);//���̈ʒu
				se->SetDistance(200.0f);//������������͈�
				se->Play(true); //��������true
			}
			else {
				return;
			}
		}
		//�E�{�^��
		if (Pad(0).GetButton(enButtonRB1)) {
			m_isbutton = false;
			//����̐؂�ւ����L���ł������Ȃ�Ε���̃X�e�[�^�X�𔽉f������
			if (m_playerstatus->GetWeapon(m_SwordId + 1)) {
				WeaponStatus();
				MagicStatus();
				//SE
				SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/swtich.wav");
				se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
				se->SetVolume(m_voicevolume);
				//3D�Đ�
				se->SetPos(m_position);//���̈ʒu
				se->SetDistance(200.0f);//������������͈�
				se->Play(true); //��������true
			}
			else {
				return;
			}
		}
	}
	m_WeaponNumber = m_playerstatus->GetWeaponNumber(m_SwordId);
	m_sword->SetSwordId(m_WeaponNumber);
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
	//���x���A�b�v���ɃG�t�F�N�g��SE�𔭐�������
	if (m_playerstatus->GetLevelUp()) {
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		CVector3 pos = m_position;
		pos.y += m_lvheight;
		effect->Play(L"Asset/effect/lvup/lvup.efk", 1.0f, pos, CQuaternion::Identity(), { 20.0f,20.0f,20.0f });
		effect->SetSpeed(1.5f);
		m_playerstatus->OffLevelUp();
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/lvup.wav");
		se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
		se->SetVolume(m_lvupvollume);
		//3D�Đ�
		se->SetPos(m_position);//���̈ʒu
		se->SetDistance(200.0f);//������������͈�
		se->Play(true); //��������true
	}
}

void Player::Shihuta()
{
	if (m_Shihuta) {
		m_Attack = (int)(m_ShihutaAttack * m_AttackMultiply);
		m_Shihutatimer += m_frame * GetDeltaTimeSec();
		//��莞�Ԍo�߂ŃV�t�^��Ԃ��I�t�ɂ���
		if (m_Shihutatimer >= m_Shihutatime) {
			m_Shihuta = false;
			m_Shihutatimer = 0;
		}
	}
	else {
		m_Attack = m_ShihutaAttack;
	}
}

void Player::Resta(const int& volume)
{
	m_HP += volume;
	if (m_HP > m_MaxHP) {
		m_HP = m_MaxHP;
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
	if (pos.LengthSq() <= 300.0f * 300.0f && m_state==enState_Idle) {
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
	//�v���C���[�Ƃ̋��������ȓ��Ȃ�b���܂�
	if (pos.LengthSq() <= 300.0f * 300.0f && m_state == enState_Idle) {
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
	//RSB�{�^���Ń^�[�Q�b�g�����b�N���܂�
	if (Pad(0).GetDown(enButtonRSB)) {
		if (m_targetlock) {
			m_targetlock = false;
		}
		else {
			m_targetlock = true;
		}
	}
	//�^�[�Q�b�g���b�N���ł���΁A���b�N�����G�l�~�[�̍��W���^�[�Q�b�g�̍��W�Ƃ��܂�
 	if (m_targetlock && m_targetdisplay) {
		if (!m_enemy->GetDeath()) {
			CVector3 pos = m_enemy->GetCollisionPosition() - m_position;
			if (pos.LengthSq() >= m_distancetarget) {
				m_targetdisplay = false;
				m_targetlock = false;
			}
			else {
				m_target = m_enemy->GetCollisionPosition();	
				m_targetdisplay = true;
				return;
			}
		}
		else {
			m_targetdisplay = false;
			m_targetlock = false;
		}
	}
	//�G�l�~�[�̍��W�ƃv���C���[�ƃG�l�~�[�̋������L������z��ł�
	std::vector<CVector3> enemyList;
	std::vector<float> distanceList;
	//�e�ϒ��z��̒����ł�
	int enemynumber = 0;
	//�v���C���[�̌����Ă���p�x���v�Z���܂�
	float degreep = atan2f(m_playerheikou.x, m_playerheikou.z);
	//�v�Z���ďo���b��I�Ɉ�ԏ������p�x���L������ϐ��ł�
	float degreemum= M_PI * 2;
	QueryGOs<IEnemy>(L"Enemy", [&](IEnemy* enemy)
	{
		//�G�l�~�[������ł����珈�����I�����܂�
		if (enemy->GetDeath()) {
			return true;
		}
		CVector3 pos = m_position - enemy->GetCollisionPosition();
		//�v���C���[�ƃG�l�~�[�̋��������O�������珈�����I�����܂�
		if (pos.LengthSq() >= m_distancetarget) {
			return true;
		}
		//�v���C���[�ƃG�l�~�[�����ԃx�N�g�����o���܂�
		CVector3 pos2 = enemy->GetCollisionPosition() - m_position;
		//y���W�A���Ȃ킿������0�ɂ��܂�
		pos2.y = 0.0f;
		//�x�N�g���𐳋K�����܂�
		pos2.Normalize();
		//�v���C���[�ƃG�l�~�[�����ԃx�N�g���̊p�x���v�Z���܂�
		float degree = atan2f(pos2.x, pos2.z);
		//������ӂ�if���v��Ȃ��\�����������A�u�v���C���[�̐��ʂ̃x�N�g���̊p�x�v��
		//�u�v���C���[�ƃG�l�~�[�����ԃx�N�g���̊p�x�v�̍����v�Z���܂�
		if (M_PI <= (degreep - degree)) {
			degree = degreep - degree - M_PI * 2;
		}
		else if (-M_PI >= (degreep - degree)) {
			degree = degreep - degree + M_PI * 2;
		}
		else {
			degree = degreep - degree;
		}
		//���߂��p�x�Ƀv���C���[�ƃG�l�~�[�̋����ɉ����ĕ␳�������܂��A�����������قǕ␳�͑傫���ł�(�l���傫���Ȃ�܂�)
		degree = degree + degree * (pos.LengthSq() / m_distancetarget) * m_degreemultiply;
		//���߂��l���r���Ă����A��ԏ������l�����߂Ă����܂�
		if (fabs(degreemum) >= fabs(degree)) {
			degreemum = degree;
			//�G�l�~�[�̍��W���L�����܂�
			m_target = enemy->GetCollisionPosition();
			m_enemy = enemy;
 		}
		//�z��̒��������Z���܂�
		enemynumber++;
		return true;
	});
	//�z��̒�����0�܂�A�z��ɉ����L������Ă��Ȃ��ꍇ�A�������I�����܂�
	if (enemynumber == 0) {
		m_enemy = nullptr;
		m_targetdisplay = false;
		return;
	}
	//���߂���ԏ������l�����l��菬�����ꍇ�A�^�[�Q�b�e�B���O���I���ɂ��܂�
	if (fabs(degreemum) <= M_PI / 3) {
		m_targetdisplay = true;
	}
	//�t�Ɉ��l���傫���ꍇ�A�^�[�Q�b�e�B���O���I�t�ɂ��܂�
	else {
		m_targetdisplay = false;
		m_enemy = nullptr;
	}
}

void Player::PostRender()
{
	if (m_cagliostro) {
		return;
	}
	//�^�[�Q�b�e�B���O���I���ł���΃^�[�Q�b�g�̉摜��\�����܂�
	if (m_targetdisplay) {
		//�Y���̃��[���h���W��2D���W��ϊ����܂�)
		CVector3 pos = m_gamecamera->GetCamera()->CalcScreenPosFromWorldPos(m_target);
		//�G�l�~�[�̍��W����ʊO�ł���Ή摜�͕\�����܂���
		//�Y���̍��W�Ƀ^�[�Q�b�g�̍��W��\�����܂�
		if (0.0f <= pos.x && pos.x <= 1.0f && 0.0f <= pos.y && pos.y <= 1.0f && 0.0f <= pos.z && pos.z <= 1.0f) {
			CVector3 scpos = pos;
			//�^�[�Q�b�g���b�N�����ǂ����ŕ\������摜��ς��܂�
			if (m_targetlock) {
				m_locktargetsprite.Draw(scpos, { 0.2f,0.2f }, { 0.5f,0.5f },
					0.0f,
					{ 1.0f, 1.0f, 1.0f, 1.0f },
					DirectX::SpriteEffects_None,
					1.0f);
			}
			else {
				m_targetsprite.Draw(scpos, { 0.2f,0.2f }, { 0.5f,0.5f },
					0.0f,
					{ 1.0f, 1.0f, 1.0f, 1.0f },
					DirectX::SpriteEffects_None,
					1.0f);
			}
			CVector3 pos = m_position;
			pos.y += 60.0f;
			pos = m_target - pos;
			pos.Normalize();
			m_attacktarget = pos;
		}
		else {
			m_attacktarget = m_playerheikou;
			m_targetdisplay = false;
		}
	}
	else {
		m_attacktarget = m_playerheikou;
	}
	//�v���C���[�̃X�e�[�^�X��\�����܂�
	/*wchar_t output[256];
	swprintf_s(output, L"x   %f\ny   %f\nz  %f\n", m_position.x, m_position.y, m_position.z);
	m_font.Draw(output,CVector2::Zero());*/
	//�X�e�[�^�X�\��
	if (m_displaystatus) {
		//�v���C���[�̃X�e�[�^�X��\�����܂�
		wchar_t output[256];
		swprintf_s(output, L"unityChan\nLv. %d\nHP        %d\nPP        %d\n��        %d\n����      %d\n�Ō���    %d\n�@����    %d\nEx        %d\nNex       %d\n",m_Level,m_MaxHP,m_MaxPP,m_playerstatus->GetPower(),m_playerstatus->GetClever(),m_Attack,m_Mattack,m_Exp,m_NextExp);
		m_font.DrawScreenPos(output, { 705.0f,60.0f }, CVector4::White(), {1.0f,1.0f});
		m_statussprite.DrawScreenPos({ 700.0f,50.0f }, {1.0f,1.0f}, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
		//����֘A�̃X�e�[�^�X��\�����܂�
		wchar_t output2[256];
		swprintf_s(output2, L"����\n����Lv  %d\n���햼  %ls\n�Ō���  %d\n�@����  %d\n���@    %ls\n����PP  %d\n�З�    %d\n",m_playerstatus->GetWeaponLv(),m_SwordName,m_playerstatus->GetWeaponAttack(),m_playerstatus->GetWeaponMattack(),m_MagicName,m_PPCost,int(m_DamageRate*100));
		m_font.DrawScreenPos(output2, { 230.0f,60.0f }, CVector4::White(), { 0.7f,0.7f });
		m_weaponstatussprite.DrawScreenPos({ 227.0f,50.0f }, { 1.0f,1.0f }, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
		//�C���x���g���֘A�̃X�e�[�^�X��\�����܂�
		wchar_t output3[256];
		swprintf_s(output3, L"�C���x���g��\n��        %d\n��        %d\n�����K    %d\n���Z�^    %dM\n",m_playerstatus->GetMaterial(0), m_playerstatus->GetMaterial(1), m_playerstatus->GetMaterial(2), m_playerstatus->GetHaveMeseta());
		m_font.DrawScreenPos(output3, { 445.0f,317.0f }, CVector4::White(), { 0.7f,0.7f });
		m_inventorystatussprite.DrawScreenPos({ 442.0f,307.0f }, { 1.0f,1.0f }, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
	}
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
			0.7f);
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
			0.7f);
	}
	//hp��HUD�֌W
	float hpRate = (float)m_HP / m_MaxHP;
	float offsetX = (hpRate - 1.0f) / 2;
	m_spriteposition.x = m_protspriteposition.x + offsetX;
	m_hud.DrawScreenPos({ 5.0f,595.0f }, CVector2::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		1.0f);
	m_logo.DrawScreenPos({ 30.0f,640.0f }, {0.4f,0.4f}, CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.9f);
	if (true) {
		wchar_t output[50];
		swprintf_s(output, L"unityChan\n");
		m_name.DrawScreenPos(output, { 165.0f,600.0f }, CVector4::White(), { 0.6f,0.6f });
	}
	if (true) {
		wchar_t output[50];
		swprintf_s(output, L"Lv  %d\n", m_Level);
		m_lvf.DrawScreenPos(output, { 20.0f,600.0f }, CVector4::White(), { 0.7f,0.7f });
	}
	if (true) {
		m_hpf.DrawScreenPos(L"HP", { 140.0f,643.0f }, CVector4::White(), { 0.4f,0.4f });
		wchar_t output[10];
		swprintf_s(output, L"%d", m_HP);
		m_hpf.DrawScreenPos(output, { 180.0f,635.0f }, CVector4::White(), { 0.6f,0.6f });
		wchar_t output2[10];
		swprintf_s(output2, L"/ %d\n", m_MaxHP);
		m_hpf.DrawScreenPos(output2, { 235.0f,635.0f }, CVector4::White(), { 0.6f,0.6f });
		m_hpframe.DrawScreenPos({140.0f,662.0f}, CVector2::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.9f);
		m_hpgage.DrawScreenPos({ 140.0f,662.0f }, {(float)m_HP/m_MaxHP,1.0f}, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.8f);
	}
	if (true) {
		m_ppf.DrawScreenPos(L"PP", { 140.0f,682.0f }, CVector4::White(), { 0.4f,0.4f });
		wchar_t output[30];
		swprintf_s(output, L"%d", m_PP);
		m_ppf.DrawScreenPos(output, { 180.0f,674.0f }, CVector4::White(), { 0.6f,0.6f });
		wchar_t output2[10];
		swprintf_s(output2, L"/ %d\n", m_MaxPP);
		m_ppf.DrawScreenPos(output2, { 235.0f,674.0f }, CVector4::White(), { 0.6f,0.6f });
		m_ppframe.DrawScreenPos({ 140.0f,701.0f }, CVector2::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.9f);
		m_ppgage.DrawScreenPos({ 140.0f,701.0f }, { (float)m_PP / m_MaxPP,1.0f }, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.8f);
	}
}
