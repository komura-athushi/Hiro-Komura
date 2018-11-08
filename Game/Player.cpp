#include "stdafx.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 

Player::Player()
{
}

Player::~Player()
{
	delete m_skinModelRender;
}

bool Player::Start()
{
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0,			//半径。 
		30.0f,			//高さ。
		m_position		//初期位置。
	);
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"Asset/animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/unityChan/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"Asset/animData/unityChan/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/unityChan/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"Asset/animData/unityChan/KneelDown.tka");
	m_animClip[enAnimationClip_Clear].Load(L"Asset/animData/unityChan/Clear.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_Clear].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_skinModelRender = new GameObj::CSkinModelRender;
    m_skinModelRender->Init(L"Resource/modelData/unityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);
	m_skinModelRender->SetPos(m_position);
	return true;
}
void Player::Update()
{
	if (m_state == enState_Damage) {
		
	}
	else {
		Move();
		//キャラクターコントローラーを使用して、座標を更新。
		m_position = m_charaCon.Execute(m_movespeed, GetDeltaTimeSec());
	}
	//重力
	m_movespeed.y -= 800.0f *GetDeltaTimeSec();
	//キャラクターの向き関係
	Turn();
	//キャラクターのアニメーションの処理
	AnimationController();
	
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		m_movespeed.y = 0.0f;
	}
	//ジャンプのアニメーションだけ都合上ここに記載
	if (m_state == enState_Jump) {
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_jump, 0.2f);
		if (!m_charaCon.IsJump()) {
			if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				//入力がなくなった。
				m_state = enState_Idle;
			}
			else {
				m_state = enState_Run;
			}
		}
	}
	else if (Pad(0).GetButton(enButtonB)) {
		m_state = enState_Damage;
	}
	
	m_charaCon.SetPosition(m_position);
	m_skinModelRender->SetPos(m_position);
	
}
void Player::Move()
{
	//左スティックの入力量を取得
	CVector2 stickL;
	stickL = Pad(0).GetStick(L);	//アナログスティックの入力量を取得。
	stickL.x = -stickL.x;
	//左スティック
	//スティックの左右入力の処理
	m_movespeed.z = 0.0f;
	m_movespeed.x = 0.0f;
	m_movespeed.z = +sin(m_radian)*stickL.x * m_multiply;
	m_movespeed.x = -cos(m_radian)*stickL.x * m_multiply;
	//スティックの上下入力の処理
	m_movespeed.z += cos(m_radian)*stickL.y * m_multiply;
	m_movespeed.x += sin(m_radian)*stickL.y * m_multiply;
	if (Pad(0).GetButton(enButtonA) //Aボタンが押されたら
		&& m_charaCon.IsOnGround()  //かつ、地面に居たら
		) {
		//ジャンプする。
		m_movespeed.y = 500.0f;	//上方向に速度を設定して、
		m_state = enState_Jump;
	}
	
}

void Player::Turn()
{
	CVector3 rotation = {0.0f,0.0f,0.0f};
	//自機の角度の差分
	float sdegree = 0.0f;
	m_radian = M_PI / 180 * m_degree;
	//右スティック
	CVector2 stickR;
	stickR = Pad(0).GetStick(R);	//アナログスティックのxの入力量を取得。
	stickR.x = -stickR.x;
	//向き
	//右スティック
	sdegree = -stickR.x * 2.0f;
	//回転処理
	m_degree += sdegree;
	//m_movespeedからキャラクターを回転させる
	auto moveSpeedXZ = m_movespeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	moveSpeedXZ.y = 0;
	if (moveSpeedXZ.LengthSq() < 0.5f) {
		return;
	}
	m_rotation.SetRotation({0.0f,1.0f,0.0f}, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
	
}

void Player::AnimationController()
{
	//ステート分岐によってアニメーションを再生させる
	switch (m_state) {
	case enState_Run:
	case enState_Idle:
		if (m_movespeed.LengthSq() > 300.0f * 300.0f) {
			//走りモーション。
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		else if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			//歩きモーション。
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_walk, 0.2f);
		}
		else {
			//待機モーション
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		}
		if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			m_state = enState_Run;
		}
		else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
			m_state = enState_Idle;
		}
		break;
	case enState_Damage:
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
		}
		else {
			if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
				m_state = enState_Run;
			}
			else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				m_state = enState_Idle;
			}
		}
		break;
	case enState_GameClear:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_Clear, 0.2f);
		break;
	case enState_GameOver:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_KneelDown, 0.2f);
		break;
		//ジャンプだけは他のとこでやる
	case enState_Jump:
		break;
	}

}
