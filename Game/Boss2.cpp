#include "stdafx.h"
#include "Boss2.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
#include "Stage1.h"
#include "Player.h"
#include "BossAttack.h"
#include "GameCamera.h"
//cpp�ŃG�l�~�[�̃��A�x���Ƃ̃h���b�v����ݒ�
const int Boss2::m_dropChances[Weapon::m_HighestRarity] = { 0,0,0,100,0,0,0 };
const int Boss2::m_dropmaterialChances[Material::m_HighestRarity] = { 0.0f,100.0f,0.0f };
//�{�X2�ł�
Boss2::Boss2() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{

}

Boss2::~Boss2()
{
	delete m_skinModelRender;
}

bool Boss2::Start()
{
	IEnemy::CCollision({ m_position }, m_collisionheight, m_r);
	//�{�X�̃X�L�����f�������_�[��\��
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/DarkDragon.cmo");
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	pos.y += 500.0f;
	m_staticobject.CreateSphere(pos, rot, 150.0f);

	return true;
}


void Boss2::Attack()
{
	//�v���C���[�̍��W���擾
	CVector3 m_playerposition = m_player->GetPosition();
	m_playerposition.y += 100.0f;
	//�v���C���[�ƃ{�X�̋���
	CVector3 pos = m_player->GetPosition() - m_position;

	if (m_HP >= 600) {
		if (m_timer >= m_cooltime) {
			BossAttack* bossattack = new BossAttack;
			bossattack->SetName(L"bossattack");
			bossattack->SetNumber(1);
			m_atktype = 1;
			//�e�ۂ̍��W�Ƀ{�X�̍��W��������B
			CVector3 l_pos = m_position;
			l_pos.y += 70.0f;
			bossattack->SetPosition(l_pos);
			CVector3 bulletPos = m_playerposition - l_pos;
			bulletPos.Normalize();
			bulletPos = bulletPos * 30.0f;
			//�e�̃X�s�[�h��ς���
			bossattack->SetMoveSpeed(bulletPos);

			//�^�C�}�[�����Z�b�g�B
			m_timer = 0;
		}
	}
	else if (m_HP >= 300) {
		if (m_timer >= m_cooltime) {
			BossAttack* bossattack = new BossAttack;
			bossattack->SetName(L"bossattack");
			bossattack->SetNumber(2);
			m_atktype = 2;

			//�e�ۂ̍��W�Ƀ{�X�̍��W��������B
			CVector3 l_pos = m_position;
			l_pos.y += 200.0f;
			bossattack->SetPosition(l_pos);

			CVector3 bulletPos = m_playerposition - l_pos;
			bulletPos.Normalize();
			bulletPos = bulletPos * 10.0f;
			//�e�̃X�s�[�h��ς���
			bossattack->SetMoveSpeed(bulletPos);

			//�^�C�}�[�����Z�b�g�B
			m_timer = 0;
		}
	}
	else {
		if (m_timer >= m_atk3cooltime) {
			m_atk3timer++;
			if (m_atk3timer >= 30) {
				BossAttack* bossattack = new BossAttack;
				bossattack->SetName(L"bossattack");
				bossattack->SetNumber(3);
				m_atktype = 3;

				//�e�ۂ̍��W�Ƀ{�X�̍��W��������B
				CVector3 l_pos = m_position;
				l_pos.y += 200.0f;
				bossattack->SetPosition(l_pos);

				CVector3 bulletPos = m_playerposition - l_pos;
				bulletPos.Normalize();
				bulletPos = bulletPos * 10.0f;
				//�e�̃X�s�[�h��ς���
				bossattack->SetMoveSpeed(bulletPos);
				m_atk3timer = 0;
				m_atk3count++;
				if (m_atk3count == 3) {
					//�^�C�}�[�����Z�b�g�B
					m_timer = 0;
					m_atk3count = 0;
				}
			}
		}
	}
}

void Boss2::Chase()
{
	m_movespeed = { 0.0f,0.0f,0.0f };
	//�v���C���[�̍��W���擾
	CVector3 m_playerposition = m_player->GetPosition();
	//�v���C���[�ƓG�̋���
	CVector3 pos = m_player->GetPosition() - m_position;
	//�{�X�̏����ʒu�ƌ��݈ʒu�̋���
	CVector3 oldpos = m_oldpos - m_position;
	//�ڐG������U��
	if (pos.Length() < 100.0f) {
		Attack();
	}
	//�����v���C���[�ƃ{�X�̋������߂��Ȃ�����
	else if (pos.Length() < 1000.0f) {
		//�߂Â��Ă���
		CVector3 EnemyPos = m_playerposition - m_position;
		EnemyPos.Normalize();
		m_movespeed = EnemyPos * 5.0f;
		m_movespeed.y = 0.0f;
		m_position += m_movespeed;
	}

	else if (pos.Length() > 1000.0f) {
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

//IEnemy�ɂ����
void Boss2::Turn()
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
	m_parallel = moveSpeedXZ;
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
}

void Boss2::Damage()
{
	//�v���C���[�ƒe�̓����蔻��
	QueryGOs<BossAttack>(L"bossattack", [&](BossAttack* bullet)->bool {
		CVector3 diff = bullet->GetPosition() - m_player->GetPosition();
		if (diff.Length() < 130.0f) {  //���������ȉ��ɂȂ�����B
			delete bullet;
			if (m_atktype == 1) {
				m_player->Damage(m_Attack1);
			}
			else if (m_atktype == 2) {
				m_player->Damage(m_Attack2);
			}
			else if (m_atktype == 3) {
				m_player->Damage(m_Attack3);

			}
		}
		return true;
	});
}

void Boss2::PostRender()
{
	GameCamera* gc = FindGO<GameCamera>();
	//����FindGO�ŃJ������������ꂽ��
	if (gc != nullptr) {
		if (m_atktype == 1 || m_atktype == 2) {
			if (m_timer >= m_cooltime - m_posttiming) {
				wchar_t output[256];
				swprintf_s(output, L"�I\n");
				CVector3 drawpos = m_player->GetPosition();
				drawpos.y += 150.0f;
				drawpos.x += 40.0f;
				//3D�̍��W��2D�ɕϊ�
				CVector2 pos = gc->GetCamera()->CalcScreenPosFromWorldPos(drawpos);
				CVector2 scale = { 3.0f,3.0f };
				m_font.Draw(output, pos, CVector4(225.0f, 00.0f, 00.0f, 0.8f), scale);
			}
		}
		else if (m_atktype == 3) {
			if (m_timer >= m_atk3cooltime - m_posttiming) {
				wchar_t output[256];
				swprintf_s(output, L"�I\n");
				CVector3 drawpos = m_player->GetPosition();
				drawpos.y += 150.0f;
				drawpos.x += 40.0f;
				//3D�̍��W��2D�ɕϊ�
				CVector2 pos = gc->GetCamera()->CalcScreenPosFromWorldPos(drawpos);
				CVector2 scale = { 3.0f,3.0f };
				m_font.Draw(output, pos, CVector4(225.0f, 00.0f, 00.0f, 0.8f), scale);
			}

		}
	}
}

void Boss2::Update()
{
	m_timer++;
	m_movespeed = m_player->GetPosition() - m_position;
	Turn();
	Attack();
	if (!IEnemy::m_death) {
		CQuaternion rot;
		CVector3 pos = m_position;
		pos.y += 55.0f;
		m_staticobject.SetPositionAndRotation(pos, rot);
		IEnemy::SetCCollision(m_position, m_collisionheight);
	}
	Damage();

	//���񂾂����
	if (m_death) {
		delete this;
	}
}
