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
}

bool Boss2_Fire::Start()
{
	m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/efk/magic_proj02.efk", 1.0f, m_position, m_rotation, m_scale);
	m_boss2 = FindGO<Boss2>(L"Enemy");

	//�R���W����
	//�U������̔���
	 attackCol = NewGO<SuicideObj::CCollisionObj>();
	//�`��̍쐬
	attackCol->CreateSphere(m_position, CQuaternion::Identity(), m_attack3r);
	////������ݒ�
	//attackCol->SetTimer(150);//�t���[����폜�����
	attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
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
	attackCol->SetPosition(m_position);
	//�e�ۂ̏���...�܂��ǂ̃^�C�~���O�ŏ��������߂ĂȂ�
	if (m_boss2->GetCount()) {
		delete this;
	}
}