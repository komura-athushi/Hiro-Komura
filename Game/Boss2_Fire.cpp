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
	//再生速度
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	//弾丸の発射
	m_position += m_moveSpeed;
	m_effect->SetPos(m_position);
	//弾丸の消去...まだどのタイミングで消すか決めてない
	if (m_boss2->GetCount()) {
		delete this;
	}
}