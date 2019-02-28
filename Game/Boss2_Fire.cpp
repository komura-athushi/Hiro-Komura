#include "stdafx.h"
#include "Boss2_Fire.h"
#include "Boss2.h"
#include "Player.h"

Boss2_Fire::Boss2_Fire()
{
}


Boss2_Fire::~Boss2_Fire()
{
	delete m_effect;
	delete m_attackCol;
}

bool Boss2_Fire::Start()
{
	m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/efk/magic_proj02.efk", 1.0f, m_position, m_rotation, m_scale);
	m_boss2 = FindGO<Boss2>(L"Enemy");
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
			player->Damage(m_Attack3);
		}
	}
	);
	return true;
}

void Boss2_Fire::Update() 
{
	//�Đ����x
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	//�e�ۂ̔���
	m_position += m_moveSpeed;
	m_effect->SetPos(m_position);
	m_attackCol->SetPosition(m_position);
	//�e�ۂ̏���...�܂��ǂ̃^�C�~���O�ŏ��������߂ĂȂ�
	if (m_timer>=m_time) {
		delete this;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}