#include "stdafx.h"
#include "Enemy_Fire.h"
#include "Player.h"

Enemy_Fire::Enemy_Fire()
{
}


Enemy_Fire::~Enemy_Fire()
{
	delete m_effect;
	delete m_attackCol;
}

bool Enemy_Fire::Start()
{
	m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/Effects/efk/enemy_fire_01.efk", 1.0f, m_position, m_rotation, m_scale);
	//�R���W����
	//�U������̔���
	m_attackCol = NewGO<SuicideObj::CCollisionObj>();
	//�`��̍쐬
	m_attackCol->CreateSphere(m_position, CQuaternion::Identity(), m_attack3r);
	////������ݒ�
	m_attackCol->SetTimer(enNoTimer);//�t���[����폜�����
	m_attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		//�Փ˂�������̖��O��"Player"�Ȃ�m_Attack3�������_���[�W�^����
		if (param.EqualName(L"Player")) {
			Player* player = param.GetClass<Player>();
			player->Damage(m_attack);
		}
	}
	);
	m_moveSpeed *= 2.0f * 20.0f;
	m_moveSpeed *= m_speed;
	return true;
}

void Enemy_Fire::Update() 
{
	//�Đ����x
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	//�e�ۂ̔���
	m_position += m_moveSpeed * 20.0f * GetDeltaTimeSec();
	m_effect->SetPos(m_position);
	m_attackCol->SetPosition(m_position);
	//�e�ۂ̏���...�܂��ǂ̃^�C�~���O�ŏ��������߂ĂȂ�
	if (m_timer>=m_time) {
		delete this;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}