#include "stdafx.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
#include "Sword.h"
#include "GameCamera.h"
#include "PlayerStatus.h"
#include "IEnemy.h"
Player::Player()
{
}

Player::~Player()
{
	delete m_skinModelRender;
	delete m_sword;
}

bool Player::Start()
{
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0,			//半径。 
		40.0f,			//高さ。
		m_position		//初期位置。
	);
	//くらい判定の作成
	m_collision = std::make_unique<GameObj::CCollisionObj>();
	//形状の作成
	m_collision->CreateSphere(m_position + CVector3::AxisY()*m_collisionUp, CQuaternion::Identity(), m_r);
	//寿命を設定
	m_collision->SetTimer(enNoTimer);//enNoTimerで寿命なし
	//名前を設定
	m_collision->SetName(L"Player");
	//クラスのポインタを設定
	m_collision->SetClass(this);
	//アニメーションファイルをロード
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"Asset/animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/unityChan/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"Asset/animData/unityChan/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/unityChan/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"Asset/animData/unityChan/KneelDown.tka");
	m_animClip[enAnimationClip_Clear].Load(L"Asset/animData/unityChan/Clear.tka");
	m_animClip[enAnimationClip_attack].Load(L"Asset/animData/unityChan/attack.tka",false,enZtoY);
	//アニメーションのループフラグをtrueにする
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	//一部アニメーションのループフラグをfalseにする
	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_Clear].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_attack].SetLoopFlag(false);
	//unityChanを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
    m_skinModelRender->Init(L"Resource/modelData/unityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);
	m_skinModelRender->SetPos(m_position);
	m_sword = new Sword;
	//unityChanのボーンを検索
	m_bonehand=m_skinModelRender->FindBoneID(L"Character1_RightHand");
	CVector3 pos=m_skinModelRender->GetBonePos(m_bonehand);
	CQuaternion qRot= m_skinModelRender->GetBoneRot(m_bonehand);
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
	m_sword->SetRot(qRot);
	m_sword->SetPosition(pos);
	Status();
	return true;
}
void Player::Update()
{
	//キャラクターのアニメーションの処理、移動や回転も入ってる
	AnimationController();
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		m_movespeed.y = 0.0f;
		m_isjump = false;
	}
	m_charaCon.SetPosition(m_position);
	m_skinModelRender->SetPos(m_position);
	m_collision->SetPosition(m_position + CVector3::AxisY()*m_collisionUp);
	Kougeki();
	m_timer2++;
}

void Player::Move()
{
	//左スティックの入力量を取得
	CVector2 stickL;
	
	if (m_state == enState_Damage || m_state==enState_GameOver) {
		stickL = { 0.0f,0.0f };
	}
	else {
		stickL = Pad(0).GetStick(L);	//アナログスティックの入力量を取得。
		if (Pad(0).GetButton(enButtonA) //Aボタンが押されたら
			&& m_charaCon.IsOnGround()  //かつ、地面に居たら
			) {
			//ジャンプする。
			m_movespeed.y = 500.0f;	//上方向に速度を設定して、
			m_state = enState_Jump;
			m_isjump = true;
		}
	}
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
	//重力
	m_movespeed.y -= 800.0f *GetDeltaTimeSec();
	//キャラクターコントローラーを使用して、座標を更新。
	m_position = m_charaCon.Execute(m_movespeed, GetDeltaTimeSec());
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
	m_playerheikou = moveSpeedXZ;
	m_rotation.SetRotation({0.0f,1.0f,0.0f}, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
}

void Player::Animation()
{
	if (m_damage) {
		m_state = enState_Damage;
		m_damage = false;
		
	}
	else if (Pad(0).GetButton(enButtonX)) {
		if (m_state != enState_Attack && m_timer>=40) {
			m_state = enState_Attack;
			m_timer = 0;
		}
	}
	if (m_HP<=0) {
		m_state = enState_GameOver;
	}
	m_timer++;
}

void Player::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f);
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
		Move();
		//キャラクターの向き関係
		Turn();
		Animation();
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
		Move();
		//キャラクターの向き関係
		Turn();
		break;
	case enState_GameClear:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_Clear, 0.2f);
		break;
	case enState_GameOver:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_KneelDown, 0.2f);
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
			
		}
		else {
			if (Pad(0).GetButton(enButtonSelect)) {
				m_gameover = true;
			}
		}
		Move();
		//キャラクターの向き関係
		Turn();
		break;
		//ジャンプだけは他のとこでやる
	case enState_Jump:
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
		Move();
		//キャラクターの向き関係
		Turn();
		Animation();
		break;
	case enState_Attack:
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump==true) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(5.0f);
			Animation();
			m_isjump = false;
		}
		else {
			if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
				m_state = enState_Run;
			}
			else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
				m_state = enState_Idle;
			}
		}
		//キャラクターの向き関係
		Turn();
		break;
	}
}

void Player::Status()
{
	m_level = m_playerstatus->GetLevel();
	m_MaxHP = m_playerstatus->GetMaxHP();
	m_MaxPP = m_playerstatus->GetMaxPP();
	m_Attack = m_playerstatus->GetAttack();
	m_HP = m_MaxHP;
	m_PP = m_MaxPP;
}  

void Player::PostRender()
{
	wchar_t output[256];
	swprintf_s(output, L"HP   %d\nPP   %d\natk  %d\n", m_HP, m_PP, m_Attack);
	m_font.DrawScreenPos(output, { 800.0f,100.0f });
}

void Player::Kougeki()
{
	if (m_state == enState_Attack) {
		CVector3 pos = m_skinModelRender->GetBonePos(m_bonehand);
		CQuaternion qRot = m_skinModelRender->GetBoneRot(m_bonehand);
		m_sword->SetRot(qRot);
		m_sword->SetPosition(pos);
		m_sword->SetScale({ 1.0f, 1.0f, 1.0f });
	}
	else {
		m_sword->SetScale({ 0.001f, 0.001f, 0.001f });
	}
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName,L"attack")==0) {
		//攻撃判定の発生
		GameObj::CCollisionObj* attackCol = NewGO<GameObj::CCollisionObj>();
		//形状の作成
		CVector3 pos = m_position + CVector3::AxisY()*60.0f;
		pos += m_playerheikou * 60.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), 70.0f);
		//寿命を設定
		attackCol->SetTimer(10);//15フレーム後削除される
		attackCol->SetCallback([&](GameObj::CCollisionObj::SCallbackParam& param) {
			//衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
			if (param.EqualName(L"IEnemy")) {
				IEnemy* enemy = param.GetClass<IEnemy>();//相手の判定に設定されているCEnemyのポインタを取得
				enemy->Damege(m_Attack);
			}
		}
		);
	}
}