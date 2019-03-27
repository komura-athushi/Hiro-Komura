#include "stdafx.h"
#include "Enemy_Wind.h"
#include "Player.h"

Enemy_Wind::Enemy_Wind()
{
}


Enemy_Wind::~Enemy_Wind()
{
	delete m_effect;
	delete m_attackCol;
}

bool Enemy_Wind::Start()
{
	m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/Effects/efk/enemy_wind_01.efk", 1.0f, m_position, m_rotation, m_scale);
	//�R���W����
	//�U������̔���
	m_attackCol = NewGO<SuicideObj::CCollisionObj>();
	//�`��̍쐬
	CVector3 pos = m_position;
	pos.y += m_collisionheight;
	m_attackCol->CreateSphere(pos, CQuaternion::Identity(), m_attack3r);
	////������ݒ�
	m_attackCol->SetTimer(enNoTimer);
	m_attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		//�Փ˂�������̖��O��"Player"�Ȃ�_���[�W��^����
		if (param.EqualName(L"Player")) {
			if (!m_hitplayer) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_attack);
				m_hitplayer = true;
			}
		}
	}
	);
	return true;
}

void Enemy_Wind::Update()
{
	//�Đ����x
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	//�e�ۂ̔���
	m_position += m_moveSpeed;
	m_effect->SetPos(m_position);
	CVector3 pos = m_position;
	pos.y += m_collisionheight;
	m_attackCol->SetPosition(pos);
	//�e�ۂ̏���
	if (m_timer >= m_time) {
		delete this;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}