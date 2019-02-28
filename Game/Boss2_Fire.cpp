#include "stdafx.h"
#include "Boss2_Fire.h"
#include "Boss2.h"

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
	return true;
}

void Boss2_Fire::Update() 
{
	//�Đ����x
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	//�e�ۂ̔���
	m_position += m_moveSpeed;
	m_effect->SetPos(m_position);
	//�e�ۂ̏���...�܂��ǂ̃^�C�~���O�ŏ��������߂ĂȂ�
	if (m_boss2->GetCount()) {
		delete this;
	}
}