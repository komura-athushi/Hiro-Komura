#include "stdafx.h"
#include "Boss3.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
#include "Game.h"
#include "Player.h"
#include "BossAttack.h"
#include "GameCamera.h"
#include "Teleport.h"
//cpp�ŃG�l�~�[�̃��A�x���Ƃ̃h���b�v����ݒ�
const int Boss3::m_dropChances[Weapon::m_HighestRarity] = { 0,0,0,100,0,0,0 };
const int Boss3::m_dropmaterialChances[Material::m_HighestRarity] = { 0.0f,100.0f,0.0f };
//�{�X3()�ł�
Boss3::Boss3() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{

}

Boss3::~Boss3()
{
	delete m_skinModelRender;
	Teleport* tl = new Teleport;
	tl->SetPosition(m_position);
	tl->SetName(L"Teleport");
}

bool Boss3::Start()
{
	IEnemy::CCollision(m_position, m_collisionheight, m_r);
	//�A�j���[�V����
	m_animClip[enAnimationClip_idle1].Load(L"Asset/animData/boss3/boss3_idle1.tka");
	m_animClip[enAnimationClip_idle2].Load(L"Asset/animData/boss3/boss3_idle2.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/boss3/boss3_run.tka");
	m_animClip[enAnimationClip_tuki].Load(L"Asset/animData/boss3/boss3_tuki.tka");
	m_animClip[enAnimationClip_harai].Load(L"Asset/animData/boss3/boss3_harai.tka");
	m_animClip[enAnimationClip_nidan].Load(L"Asset/animData/boss3/boss3_nidan.tka");
	m_animClip[enAnimationClip_bash].Load(L"Asset/animData/boss3/boss3_bash.tka");
	m_animClip[enAnimationClip_kaiten].Load(L"Asset/animData/boss3/boss3_kaiten.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/boss3./boss3_damage.tka");
	m_animClip[enAnimationClip_death].Load(L"Asset/animData/boss3/boss3_death.tka");
	m_animClip[enAnimationClip_idle1].SetLoopFlag(true);
	m_animClip[enAnimationClip_idle2].SetLoopFlag(false);
	m_animClip[enAnimationClip_run].SetLoopFlag(true);
	m_animClip[enAnimationClip_tuki].SetLoopFlag(false);
	m_animClip[enAnimationClip_harai].SetLoopFlag(false);
	m_animClip[enAnimationClip_nidan].SetLoopFlag(false);
	m_animClip[enAnimationClip_bash].SetLoopFlag(false);
	m_animClip[enAnimationClip_kaiten].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_death].SetLoopFlag(false);
	//�R�m�̃X�L�����f�������_�[��\��
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/boss3.cmo", m_animClip, enAnimationClip_num);
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	//pos.y += 50.0f;
	m_staticobject.CreateSphere(pos, rot, 150.0f);
	//m_player = FindGO<Player>(L"player");
	//unityChan�̃{�[��������
	//m_bonehead = m_skinModelRender->FindBoneID(L"Bone016");
	return true;
}
void Boss3::Attack()
{
	int t = rand() % 100;

	if (t < 20) {
		//�˂��̃X�e�[�g
		m_state = enState_tuki;
	}
	else if (t < 40) {
		//�����̃X�e�[�g
		m_state = enState_harai;
	}
	else if (t < 60) {
		//��i�˂��̃X�e�[�g
		m_state = enState_nidan;
	}
	else if (t < 80) {
		//�V�[���h�o�b�V���̃X�e�[�g
		m_state = enState_bash;
	}
	else {
		//��]�˂��̃X�e�[�g
		m_state = enState_kaiten;
	}
}

void Boss3::Chase()
{
	m_movespeed = { 0.0f,0.0f,0.0f };
	//�v���C���[�̍��W���擾
	CVector3 m_playerposition = m_player->GetPosition();
	//�v���C���[�ƓG�̋���
	CVector3 pos = m_player->GetPosition() - m_position;
	//�G�̏����ʒu�ƌ��݈ʒu�̋���
	CVector3 oldpos = m_oldpos - m_position;
	//�U��
	if (pos.LengthSq() < 500.0f * 500.0f) {
		Attack();
	}
	//�����v���C���[�ƋS�̋������߂��Ȃ�����
	if (pos.LengthSq() < 2000.0f * 2000.0f) {
		if (pos.LengthSq() > 200.0f * 200.0f) {
			//�߂Â��Ă���
			CVector3 EnemyPos = m_playerposition - m_position;
			EnemyPos.Normalize();
			m_movespeed = EnemyPos * 5.0f;
			m_movespeed.y = 0.0f;
			m_position += m_movespeed;
			m_ischase = true;
		}
		else {
			m_ischase = false;
		}
	}

	else if (pos.LengthSq() > 1000.0f*1000.0f) {
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

//IEnemy�ɂ����
void Boss3::Turn()
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
	if (m_ischase) {
		m_parallel = moveSpeedXZ;
		m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	}
	else {
		CVector3 pos = m_player->GetPosition() - m_position;
		pos.y = 0.0f;
		pos.Normalize();
		m_rotation.GetRotation(CVector3::AxisY(), atan2f(pos.x, pos.z));
	}
	m_skinModelRender->SetRot(m_rotation);
}

void Boss3::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f);
	//�X�e�[�g����ɂ���ăA�j���[�V�������Đ�������
	switch (m_state) {
	case enState_Idle_Run:
		if (m_movespeed.LengthSq() > 1.0f*1.0f) {
			//���胂�[�V�����B
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		else {
			if (m_timer >= m_cooltime) {
				m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle2, 0.2f);
				m_timer = 0;
				if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
					m_state = enState_Idle_Run;
				}
			}
			else {
				if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
					m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle1, 0.2f);
					m_state = enState_Idle_Run;
				}
			}
		}
		Chase();
		Turn();
		break;
	case enState_tuki:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_tuki, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_harai:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_harai, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_nidan:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_nidan, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_bash:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_bash, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_kaiten:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_kaiten, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Damage:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Dead:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_death, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_gekiha = true;
		}
		break;
	}
}

void Boss3::Damage()
{
	if (IEnemy::m_damage) {
		m_state = enState_Damage;
		IEnemy::m_damage = false;
	}
}

void Boss3::Dead()
{
	if (IEnemy::m_death) {
		m_state = enState_Dead;
	}
}

void Boss3::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	//�˂�
	if (wcscmp(eventName, L"tuki") == 0) {
		//�U������̔���
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//�`��̍쐬
		CVector3 atkpos = m_position;
		//atkpos.z += 50.0f;
		CVector3 pos = atkpos + CVector3::AxisY() * (m_collisionheight - 30.0f);
		pos += m_parallel * 250.0f;
		pos.y += 20.0f;
		attackCol->CreateBox(pos, m_rotation, m_size);
		//������ݒ�
		attackCol->SetTimer(30);//�t���[����폜�����
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//�Փ˂�������̖��O��"Player"�Ȃ�m_Attack1�������_���[�W�^����
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack);
			}
		}
		);
	//�͂炢
	}else if (wcscmp(eventName, L"harai") == 0) {
		//�U������̔���
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//�`��̍쐬
		CVector3 atkpos = m_position;
		atkpos.z += 50.0f;
		CVector3 pos = atkpos + CVector3::AxisY() * (m_collisionheight - 30.0f);
		pos += m_parallel * 70.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), m_harai_r);
		//������ݒ�
		attackCol->SetTimer(30);//�t���[����폜�����
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//�Փ˂�������̖��O��"Player"�Ȃ�m_Attack�������_���[�W�^����
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack);
			}
		}
		);
	}
	//�˂��Ɠ�i�˂��͓���
	//��i�˂�
	else if (wcscmp(eventName, L"nidan") == 0) {
		//�U������̔���
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//�`��̍쐬
		CVector3 atkpos = m_position;
		//atkpos.z += 50.0f;
		CVector3 pos = atkpos + CVector3::AxisY() * (m_collisionheight - 30.0f);
		pos += m_parallel * 250.0f;
		pos.y += 20.0f;
		attackCol->CreateBox(pos, m_rotation, m_size);
		//������ݒ�
		attackCol->SetTimer(30);//�t���[����폜�����
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		//�Փ˂�������̖��O��"Player"�Ȃ�m_Attack�������_���[�W�^����
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack);
			}
		});
	}//�V�[���h�o�b�V��
	else if (wcscmp(eventName, L"bash") == 0) {
		//�U������̔���
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//�`��̍쐬
		CVector3 atkpos = m_position;
		//atkpos.z += 50.0f;
		CVector3 pos = atkpos + CVector3::AxisY() * (m_collisionheight - 30.0f);
		pos += m_parallel * 200.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), m_harai_r);
		//������ݒ�
		attackCol->SetTimer(30);//�t���[����폜�����
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//�Փ˂�������̖��O��"Player"�Ȃ�m_Attack�������_���[�W�^����
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack);
			}
		}
		);
	//��]
	}else if (wcscmp(eventName, L"kaiten") == 0) {
		//�U������̔���
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//�`��̍쐬
		CVector3 atkpos = m_position;
		//atkpos.z += 50.0f;
		CVector3 pos = atkpos + CVector3::AxisY() * (m_collisionheight - 30.0f);
		pos += m_parallel * 500.0f;
		m_position = pos;
		m_position.y = 0.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), m_harai_r);
		//������ݒ�
		attackCol->SetTimer(30);//�t���[����폜�����
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//�Փ˂�������̖��O��"Player"�Ȃ�m_Attack�������_���[�W�^����
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack);
			}
		}
		);
	}
}

void Boss3::Update()
{
	m_Ctimer++;
	m_timer++;
	AnimationController();
	if (!IEnemy::m_death) {
		CQuaternion rot;
		CVector3 pos = m_position;
		pos.y += 55.0f;
		m_staticobject.SetPositionAndRotation(pos, rot);
		IEnemy::SetCCollision(m_position, m_collisionheight);
	}
	Damage();
	Dead();
	if (m_gekiha) {
		delete this;
	}
}