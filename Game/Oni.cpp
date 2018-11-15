#include "stdafx.h"
#include "Oni.h"

//鬼（見た目はスケルトン）です
Oni::Oni()
{
}


Oni::~Oni()
{
	delete m_skinModelRender;
}

bool Oni::Start()
{
	//アニメーション
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/enemy/idle.tka");
	m_animClip[enAnimationClip_attack].Load(L"Asset/animData/enemy/attack.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/enemy/damage.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_attack].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	//鬼のスキンモデルレンダーを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/enemy.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	return true;
}

void Oni::Attack()
{
}
//なぜかエネミーが床に埋まったままになっている
//プレイヤーの周りをくるくる回ってしまう
void Oni::Chase()
{
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	//プレイヤーと敵の距離
	CVector3 pos = m_player->GetPosition()-m_position;
	//もしプレイヤーと鬼の距離が近くなったら
	if (pos.Length() < 1000.0f) {

		//近すぎたら止まる
		if (pos.Length() < 300.0f) {
			m_moveSpeed = { 0.0f, 0.0f, 0.0f };
			m_state = enState_Attack;
		}

		//近づいてくる
		CVector3 EnemyPos = m_playerposition - m_position;
		EnemyPos.Normalize();
		m_moveSpeed += EnemyPos * 0.1f;
		m_position += m_moveSpeed;
		m_position.y = 0.0f;
		m_skinModelRender->SetPos(m_position);
	}
	/*
	else if(oldpos == m_position){
		//初期位置に帰る
		CVector3 EnemyPos = oldpos - m_position;
		EnemyPos.Normalize();
		m_moveSpeed += EnemyPos * 5.0f;
		m_position += m_moveSpeed;
		m_skinModelRender->SetPos(m_position);
	}
	*/
	else {
		m_state = enState_Idle;
	}
}

void Oni::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f);
	//ステート分岐によってアニメーションを再生させる
	switch (m_state) {
	case enState_Idle:
		//待機モーション
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		break;
	case enState_Attack:
		//攻撃モーション
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack, 0.2f);
		break;
	case enState_Damage:
		//ダメージモーション
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
		break;
	}
}

void Oni::Damage() 
{
	if (Pad(0).GetButton(enButtonRB1)) //RB1ボタンが押されたら
	{
		m_state = enState_Damage;
	}
}

void Oni::Update()
{
	Chase();
	//エネミーが映らなくなった
	AnimationController();
	Damage();
}
