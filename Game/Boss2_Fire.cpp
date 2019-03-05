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
	//コリジョン
	//攻撃判定の発生
	m_attackCol = NewGO<SuicideObj::CCollisionObj>();
	//形状の作成
	m_attackCol->CreateSphere(m_position, CQuaternion::Identity(), m_attack3r);
	////寿命を設定
	m_attackCol->SetTimer(enNoTimer);//フレーム後削除される
	m_attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		//衝突した判定の名前が"Player"ならm_Attack3分だけダメージ与える
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
	//再生速度
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	//弾丸の発射
	m_position += m_moveSpeed;
	m_effect->SetPos(m_position);
	m_attackCol->SetPosition(m_position);
	//弾丸の消去...まだどのタイミングで消すか決めてない
	if (m_timer>=m_time) {
		delete this;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}