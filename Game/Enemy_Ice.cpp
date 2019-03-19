#include "stdafx.h"
#include "Enemy_Ice.h"
#include "Player.h"

Enemy_Ice::Enemy_Ice()
{
}


Enemy_Ice::~Enemy_Ice()
{
	delete m_effect;
	delete m_attackCol;
}

bool Enemy_Ice::Start()
{
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_moveSpeed.x, m_moveSpeed.z));
	m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/Effects/efk/enemy_ice_01.efk", 1.0f, m_position, m_rotation, m_scale);
	//�R���W����
	//�U������̔���
	m_attackCol = NewGO<SuicideObj::CCollisionObj>();
	//�`��̍쐬
	CVector3 pos = m_position;
	pos.y += m_collisionheight;
	m_attackCol->CreateSphere(pos, CQuaternion::Identity(), m_attack3r);
	////������ݒ�
	m_attackCol->SetTimer(enNoTimer);//�t���[����폜�����
	m_attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		//�Փ˂�������̖��O��"Player"�Ȃ�m_Attack3�������_���[�W�^����
		if (param.EqualName(L"Player")) {
			if (!m_hitplayer) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_attack);
				m_hitplayer = true;
			}
		}
	}
	);
	m_moveSpeed *= 7.0f * 60.0f;
	m_moveSpeed *= m_speed;
	return true;
}

void Enemy_Ice::Update()
{
	//�Đ����x
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	//�e�ۂ̔���
	m_position += m_moveSpeed * GetDeltaTimeSec();
	m_effect->SetPos(m_position);
	//CVector3 pos = m_position;
	//pos.y += m_collisionheight;
	m_attackCol->SetPosition(m_position);
	//�e�ۂ̏���...�܂��ǂ̃^�C�~���O�ŏ��������߂ĂȂ�
	if (m_timer >= m_time) {
		delete this;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}