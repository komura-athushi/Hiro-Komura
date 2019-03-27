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
	//コリジョン
	//攻撃判定の発生
	m_attackCol = NewGO<SuicideObj::CCollisionObj>();
	//形状の作成
	CVector3 pos = m_position;
	pos.y += m_collisionheight;
	m_attackCol->CreateSphere(pos, CQuaternion::Identity(), m_attack3r);
	////寿命を設定
	m_attackCol->SetTimer(enNoTimer);
	m_attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		//衝突した判定の名前が"Player"ならダメージを与える
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
	//再生速度
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	//弾丸の発射
	m_position += m_moveSpeed;
	m_effect->SetPos(m_position);
	CVector3 pos = m_position;
	pos.y += m_collisionheight;
	m_attackCol->SetPosition(pos);
	//弾丸の消去
	if (m_timer >= m_time) {
		delete this;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}