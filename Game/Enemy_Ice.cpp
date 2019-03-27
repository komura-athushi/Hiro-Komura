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
	//移動の向きにエフェクトを回転させる
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_moveSpeed.x, m_moveSpeed.z));
	m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/Effects/efk/enemy_ice_01.efk", 1.0f, m_position, m_rotation, m_scale);
	//コリジョン
	//攻撃判定の発生
	m_attackCol = NewGO<SuicideObj::CCollisionObj>();
	//形状の作成
	m_attackCol->CreateSphere(m_position, CQuaternion::Identity(), m_attack3r);
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
	//移動速度
	m_moveSpeed *= 7.0f * 60.0f;
	m_moveSpeed *= m_speed;
	return true;
}

void Enemy_Ice::Update()
{
	//再生速度
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	//弾丸の発射
	m_position += m_moveSpeed * GetDeltaTimeSec();
	m_effect->SetPos(m_position);
	m_attackCol->SetPosition(m_position);
	//弾丸の消去
	if (m_timer >= m_time) {
		delete this;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}