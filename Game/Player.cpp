#include "stdafx.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
#include "Sword.h"
#include "GameCamera.h"
#include "PlayerStatus.h"
#include "IEnemy.h"
#include "ShotMagic.h"
#include "Human.h"
#include "Merchant.h"
#include "Effekseer.h"
const float Player::m_frame = 40.0f;
Player::Player()
{
}

Player::~Player()
{
	delete m_skinModelRender;
	delete m_sword;
	m_collision->Delete();
}

void Player::unityChan()
{
	//アニメーションファイルをロード
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"Asset/animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/unityChan/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"Asset/animData/unityChan/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/unityChan/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"Asset/animData/unityChan/KneelDown.tka");
	m_animClip[enAnimationClip_Clear].Load(L"Asset/animData/unityChan/Clear.tka");
	m_animClip[enAnimationClip_attack].Load(L"Asset/animData/unityChan/attack.tka", false, enZtoY);
	m_animClip[enAnimationClip_aria].Load(L"Asset/animData/unityChan/aria.tka", false, enZtoY);
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
	m_animClip[enAnimationClip_aria].SetLoopFlag(false);
	//unityChanを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/unityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetRot(m_rotation);
	m_sword = new Sword;
	//unityChanのボーンを検索
	m_bonehand = m_skinModelRender->FindBoneID(L"Character1_RightHand");
	m_bonecenter = m_skinModelRender->FindBoneID(L"center");
	CQuaternion qRot = m_skinModelRender->GetBoneRot(m_bonecenter);
	m_sword->SetRot(qRot);
	CVector3 pos = m_position;
	pos.y += 170.0f;
	pos.x -= 70.0f;
	pos.z += 10.0f;
	m_sword->SetPosition(pos);
	m_sword->SetSwordId(m_SwordId);
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
}

void Player::cagliostro()
{
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/cagliostro.cmo");
	m_scale = {1.0f, 1.0f, 1.0f};
	m_skinModelRender->SetScale(m_scale);
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
	m_collision = new SuicideObj::CCollisionObj;
	//形状の作成
	m_collision->CreateSphere(m_position + CVector3::AxisY()*m_collisionUp, CQuaternion::Identity(), m_r);
	//寿命を設定
	m_collision->SetTimer(enNoTimer);//enNoTimerで寿命なし
	//名前を設定
	m_collision->SetName(L"Player");
	//クラスのポインタを設定
	m_collision->SetClass(this);
	//プレイヤーステータスクラスのポインタを検索検索ぅ～
	m_playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
	Status();
	WeaponStatus();
	MagicStatus();
	if (m_cagliostro) {
		cagliostro();
	}
	else {
		unityChan();
	}

	return true;
}
void Player::Update()
{
	if (m_cagliostro) {
	}
	else {
		if (m_stop) {
			Turn();
		}
		else {
			//キャラクターのアニメーションの処理、移動や回転も入ってる
			AnimationController();
			Kougeki();
			SwitchWeapon();
		}
	}
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		m_movespeed.y = 0.0f;
		m_isjump = false;
	}
	m_charaCon.SetPosition(m_position);
	m_skinModelRender->SetPos(m_position);
	m_collision->SetPosition(m_position + CVector3::AxisY()*m_collisionUp);
	if (m_PPtimer >= 50) {
		if (m_PP < m_MaxPP) {
			m_PP++;
			m_PPtimer = 0.0f;
		}
	}
	RelationHuman();
	RelationMerchant();
	//攻撃力上昇魔法
	Shihuta();
	//PlayerStatusクラスのメンバ変数をプレイヤーのメンバ変数に反映
	Status();
	LevelUp();
	//OutTarget();
	m_PPtimer += m_frame * GetDeltaTimeSec();
	m_timer2 += m_frame * GetDeltaTimeSec();
}

void Player::Move()
{
	//左スティックの入力量を取得
	CVector2 stickL;
	//ダメージを受けているとき、ゲームオーバーの時、ゲームクリアの時は右スティックの入力を無効にする
	if (m_state == enState_Damage || m_state==enState_GameOver || m_state==enState_GameClear) {
		stickL = { 0.0f,0.0f };
	}
	else {
		stickL = Pad(0).GetStick(L);	//アナログスティックの入力量を取得。
		if (Pad(0).GetDown(enButtonA) //Aボタンが押されたら
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
	//ダメージを受けたら
	if (m_damage) {
		m_state = enState_Damage;
		m_damage = false;
	}
	//Xボタンを押したら
	else if (Pad(0).GetDown(enButtonX) && m_timer>=15) {
		if (m_state != enState_Attack) {
			m_state = enState_Attack;
			m_timer = 0;
		}
	}
	//Yボタンを押したら
	else if (Pad(0).GetButton(enButtonY) && m_timer >= 15) {
		if (m_state != enState_Aria) {
			if (m_PP >= m_PPCost) {
				m_state = enState_Aria;
				m_timer = 0;
				m_PP -= m_PPCost;
			}
		}
	}
	if (m_HP <= 0 || Pad(0).GetButton(enButtonLT)) {
		m_state = enState_GameOver;
	}
	else if (Pad(0).GetButton(enButtonLB1)) {
		m_state = enState_GameClear;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}

void Player::ClearVoice()
{
	//SE
	if (m_state == enState_GameClear) {
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/clear.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(2.6f);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
	else {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/gameover.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(2.6f);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
}

void Player::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f*60.0f*GetDeltaTimeSec());
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
			//アニメーションの再生が終わったら、再びアニメーション分岐
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
		m_sword->SetScale({ 0.001f,0.001f,0.001f });
		if (!m_clear_over_voice) {
			ClearVoice();
			m_clear_over_voice = true;
		}
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {

		}
		else {
			//アニメーションの再生が終わったら、クリアフラグをONにする
			if (Pad(0).GetButton(enButtonBack)) {
				m_gameclear = true;
				m_transscene = true;
			}
		}
		Move();
		Turn();
		break;
	case enState_GameOver:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_KneelDown, 0.2f);
		m_sword->SetScale({ 0.001f,0.001f,0.001f });
		if (!m_clear_over_voice) {
			ClearVoice();
			m_clear_over_voice = true;
		}
		if (m_skinModelRender->GetAnimCon().IsPlaying()) {
		}
		else {
			//アニメーションの再生が終わったら、ゲームオーバーフラグをONにする
			if (Pad(0).GetButton(enButtonBack)) {
				m_gameover = true;
				m_transscene = true;
			}
		}
		Move();
		//キャラクターの向き関係
		Turn();
		break;
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
			m_skinModelRender->GetAnimCon().SetSpeed(7.0f*60.0f*GetDeltaTimeSec());
			Animation();
			m_isjump = false;
			m_timer = 0;
		}
		else {
			//アニメーションの再生が終わったら、アニメーション分岐
			m_timer += m_frame * GetDeltaTimeSec();
			if (m_timer >= 20) {
				if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
					m_state = enState_Run;
				}
				else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
					m_state = enState_Idle;
				}
				m_timer = 0;
			}
			
		}
		//キャラクターの向き関係
		Turn();
		break;
	case enState_Aria:
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump == true) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_aria, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(1.0f*60.0f*GetDeltaTimeSec());
			Animation();
			m_isjump = false;
			m_timer = 0;
		}
		else {
			//アニメーションの再生が終わったら、アニメーション分岐
			m_timer += m_frame * GetDeltaTimeSec();
			if (m_timer >= 20) {
				if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
					m_state = enState_Run;
				}
				else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
					m_state = enState_Idle;
				}
				m_timer = 0;
			}
		}
		//キャラクターの向き関係
		Turn();
		break;
	}
}

void Player::Status()
{
	//プレイヤーステータスクラスの経験値をプレイヤークラスに加算
	m_Exp = m_playerstatus->GetExp();
	m_NextExp = m_playerstatus->GetNextExp();
	//レベルアップしてなかったら処理を終了する
	if (m_Level == m_playerstatus->GetLevel()) {
		return;
	}
	else {
		//レベルアップしてたら、プレイヤーステータスクラスのステータスを反映、ついでにHPとPP回復
		m_Level = m_playerstatus->GetLevel();
		m_MaxHP = m_playerstatus->GetMaxHP();
		m_MaxPP = m_playerstatus->GetMaxPP();
		m_Attack = m_playerstatus->GetAttack();
		m_ShihutaAttack = m_Attack;
		m_Mattack = m_playerstatus->GetMattack();
		m_HP = m_MaxHP;
		m_PP = m_MaxPP;
		m_SwordId = m_playerstatus->GetSwordId();
	}
}  

void Player::Kougeki()
{
	//攻撃しているときは武器の位置をunityChanの手に移動させる
	if (m_state == enState_Attack) {
		CVector3 pos = m_skinModelRender->GetBonePos(m_bonehand);
		CQuaternion qRot = m_skinModelRender->GetBoneRot(m_bonehand);
		m_sword->SetRot(qRot);
		m_sword->SetPosition(pos);
	}
	//攻撃していないときは、武器をunityChanの背中に移動させる
	else {
		CVector3 pos = m_playerheikou;
		CQuaternion qRot;
		qRot.SetRotation({0.0f,1.0f,0.0f}, -90.0f);
		pos.Normalize();
		pos *= 10.0f;
		pos = m_position - pos;
		pos.y += 70.0f;
		CQuaternion qRot2;
		qRot2.SetRotation({ 0.0f,1.0f,0.0f }, -90.0f);
		CVector3 pos2 = m_playerheikou;
		pos2.Normalize();
		qRot2.Multiply(pos2);
		pos2 *= 70.0f;
		pos += pos2;
		m_sword->SetPosition(pos);
		CQuaternion qRot3 = m_skinModelRender->GetBoneRot(m_bonecenter);
		m_sword->SetRot(qRot3);
	}
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName,L"attack")==0) {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/attack.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(2.6f);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
		//攻撃判定の発生
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//形状の作成
		CVector3 pos = m_position + CVector3::AxisY()*60.0f;
		pos += m_playerheikou * 90.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), 70.0f);
		//寿命を設定
		attackCol->SetTimer(3);//15フレーム後削除される
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
			if (param.EqualName(L"IEnemy")) {
				IEnemy* enemy = param.GetClass<IEnemy>();//相手の判定に設定されているCEnemyのポインタを取得
				//エネミーにダメージ
				enemy->Damage(m_Attack);
				//もしエネミーのHPが0以下になったら
				if (enemy->GetDeath()) {
					//エネミーの経験値をプレイヤーの経験値に加算
					m_playerstatus->PlusExp(enemy->GetExp());
				}
			}
		}
		);
	}
	//呪文詠唱スタート！
	else if (wcscmp(eventName, L"aria_start") == 0) {
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		effect->Play(L"Asset/effect/efk/magic_cast01.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
		effect->SetSpeed(2.0f);
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/aria.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(2.6f);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
	//魔法を発生させる
	else if (wcscmp(eventName, L"aria") == 0) {
		ShotMagic* shotmagic = new ShotMagic;
		shotmagic->SetPosition(m_position);
		shotmagic->SetDirectionPlayer(m_playerheikou);
		shotmagic->SetId(m_MagicId);
		shotmagic->SetDamage(m_Mattack, m_DamageRate);
		shotmagic->SetName(L"ShotMagic");
	}
}

void Player::Damage(const int& attack)
{
	//ゲームオーバーかゲームクリアの場合、ダメージの処理をしない
	if (m_state == enState_GameOver || m_state==enState_GameClear) {
		return;
	}
	else if (m_timer2 >= 30) {
		m_HP -= attack;
		//HPが0より小さくなったら0にする
		if (m_HP < 0) {
			m_HP = 0;
		}
		m_damage = true;
		m_timer2 = 0;
	}
}

void Player::WeaponStatus()
{
	m_Mattack = m_playerstatus->GetMattack();
	m_Attack = m_playerstatus->GetAttack();
	m_ShihutaAttack = m_Attack;
	m_SwordId = m_playerstatus->GetSwordId();
	m_SwordName = m_playerstatus->GetSwordName();
	m_MagicId = m_playerstatus->GetMagicId();
}

void Player::MagicStatus()
{
	m_MagicName = m_playerstatus->GetMagicName();
	m_DamageRate = m_playerstatus->GetDamageRate();
	m_PPCost = m_playerstatus->GetPPCost();
}

void Player::SwitchWeapon()
{
	if (!Pad(0).GetButton(enButtonLeft) && !Pad(0).GetButton(enButtonRight)) {
		m_isbutton=true;
	}
	//直前にボタンを押していないときにだけ、入力を有効にする
	if (m_isbutton) {
		//左ボタン
		if (Pad(0).GetButton(enButtonLeft)) {
			m_isbutton = false;
			//武器の切り替えが有効であったならば武器のステータスを反映させる
			if (m_playerstatus->GetWeapon(m_SwordId - 1)) {
				WeaponStatus();
				MagicStatus();
			}
			else {
				return;
			}
		}
		//右ボタン
		if (Pad(0).GetButton(enButtonRight)) {
			m_isbutton = false;
			//武器の切り替えが有効であったならば武器のステータスを反映させる
			if (m_playerstatus->GetWeapon(m_SwordId + 1)) {
				WeaponStatus();
				MagicStatus();
			}
			else {
				return;
			}
		}
	}
	m_sword->SetSwordId(m_SwordId);
}

void Player::RecoveryPP()
{
	m_PP += m_AttackRecoveryPP;
	if (m_PP > m_MaxPP) {
		m_PP = m_MaxPP;
	}
}

void Player::LevelUp()
{
	if (m_playerstatus->GetLevelUp()) {
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		CVector3 pos = m_position;
		pos.y += m_height;
		effect->Play(L"Asset/effect/lvup/lvup.efk", 1.0f, pos, CQuaternion::Identity(), { 20.0f,20.0f,20.0f });
		effect->SetSpeed(1.5f);
		m_playerstatus->OffLevelUp();
	}
}

void Player::Shihuta()
{
	if (m_Shihuta) {
		m_Attack = (int)(m_ShihutaAttack * m_AttackMultiply);
		m_Shihutatimer += 40.0f * GetDeltaTimeSec();
		if (m_Shihutatimer >= m_Shihutatime) {
			m_Shihuta = false;
			m_Shihutatimer = 0;
		}
	}
	else {
		m_Attack = m_ShihutaAttack;
	}
}

void Player::RelationHuman()
{
	if (m_human == nullptr) {
		m_human = FindGO<Human>(L"Human");
		return;
	}
	CVector3 pos = m_human->GetPosition() - m_position;
	//待機状態かつ距離が一定以内の時にBボタンを押すと話せる
	if (pos.Length() <= 300.0f && m_state==enState_Idle) {
		if (Pad(0).GetDown(enButtonB)) {
			if (m_human->GetTalk() && m_human->isLevelUpTown()) {
				m_human->SetLevelUpTown();
			}
			m_human->OnTalk();
			m_stop = true;
		}
		if (Pad(0).GetDown(enButtonA)) {
			m_human->OffTalk();
			m_stop = false;
		}
	}
}

void Player::RelationMerchant()
{
	if (m_merchant == nullptr) {
		m_merchant = FindGO<Merchant>();
		return;
	}
	CVector3 pos = m_merchant->GetPosition() - m_position;
	if (pos.Length() <= 300.0f && m_state == enState_Idle) {
		if (Pad(0).GetDown(enButtonB)) {
			if (m_merchant->GetTalk()) {

			}
			else {
				m_merchant->SetTalk();
				m_stop = true;
			}
		}
		else if (Pad(0).GetDown(enButtonA)) {
			if (m_merchant->GetTalk()) {
				m_merchant->OffTalk();
				m_stop = false;
			}
		}
	}
}

void Player::OutTarget()
{
	std::vector<CVector3> enemyList;
	int enemynumber = 0;
	CVector3 target;
	QueryGOs<IEnemy>(L"Enemy", [&](IEnemy* enemy)
	{
		CVector3 pos = enemy->GetCollisionPosition();
		enemyList.push_back(pos);
		enemynumber++;
		return true;
	});
	if (enemynumber == 0) {
		m_gamecamera->OffTage();
		return;
	}
	target = m_position - enemyList[0];
	for (int i = 0; i < enemynumber; i++) {
		CVector3 pos = m_position - enemyList[enemynumber];
		
		if (target.Length() > pos.Length()) {
			target = pos;
		}
	}
	m_target = target;
	m_gamecamera->SetTarget(m_target);
	m_gamecamera->SetTage();
}

void Player::PostRender()
{
	if (m_transscene) {
		return;
	}
	wchar_t output[256];
	swprintf_s(output, L"Lv   %d\nExp  %d\nNexp %d\nHP   %d\nPP   %d\nAtk  %d\nMatk %d\nWpn  %s\nMgc  %s\nMPC  %d\nMgg  %d\nWLv  %d\n", m_Level, m_Exp, m_NextExp, m_HP, m_PP, m_Attack, m_Mattack, m_SwordName, m_MagicName, m_PPCost, int(m_Mattack*m_DamageRate),m_playerstatus->GetWeaponLv(m_SwordId));
	//swprintf_s(output, L"x   %f\ny   %f\nz  %f\nw   %f\n", m_swordqRot.x, m_swordqRot.y, m_swordqRot.z, m_swordqRot.w);
	m_font.DrawScreenPos(output, { 700.0f,100.0f }, CVector4(200.0f, 00.0f, 100.0f, 1.0f));
	/*m_sprite.DrawScreenPos(CVector2::Zero(), CVector2::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.4f);*/
	//ゲームオーバー表示
	if (m_state == enState_GameOver && !m_skinModelRender->GetAnimCon().IsPlaying()) {
		if (!m_displaysprite) {
			m_sprite2.Init(L"Resource/sprite/gameover.dds");
			m_displaysprite = true;
		}
		m_sprite2.DrawScreenPos(CVector2::Zero(), CVector2::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
	}
	//ゲームクリア表示
	else if (m_state == enState_GameClear && !m_skinModelRender->GetAnimCon().IsPlaying()) {
		if (!m_displaysprite) {
			m_sprite2.Init(L"Resource/sprite/clear.dds");
			m_displaysprite = true;
		}
		m_sprite2.DrawScreenPos(CVector2::Zero(), CVector2::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
	}
}