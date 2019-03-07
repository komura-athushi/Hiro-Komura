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
#include "Morugan.h"
#include "Town.h"
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
	m_sword->SetSwordId(m_WeaponNumber);
	//アニメーションイベントのコールバック関数を設定
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
	//色々なddsファイル読み込み
	m_targetsprite.Init(L"Resource/sprite/target.dds");
	m_locktargetsprite.Init(L"Resource/sprite/locktarget.dds");
	m_statussprite.Init(L"Resource/sprite/status.dds");
	m_weaponstatussprite.Init(L"Resource/sprite/weaponstatus.dds");
	m_inventorystatussprite.Init(L"Resource/sprite/inventorystatus.dds");
	m_hpframe.Init(L"Resource/sprite/hpframe.dds");
	m_hpgage.Init(L"Resource/sprite/hpgage.dds");
	m_ppframe.Init(L"Resource/sprite/ppframe.dds");
	m_ppgage.Init(L"Resource/sprite/ppgage.dds");
	m_hud.Init(L"Resource/sprite/hud.dds");
	m_logo.Init(L"Resource/sprite/logo.dds");
}

void Player::cagliostro()
{
	//カリオストロちゃんモードのときはカリオストロのモデルをロード
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/cagliostro.cmo");
	m_scale = {1.0f, 1.0f, 1.0f};
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetIsShadowCaster(false);
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
	m_town = FindGO<Town>();
	//ステータス
	Status();
	//武器のステータス
	WeaponStatus();
	//魔法
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
		//停止状態なら回転だけ
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
	m_collision->SetPosition(m_position + CVector3::AxisY() * m_collisionUp);
	//一定時間経過したらppを自動回復
	if (m_PPtimer >= m_PPtime) {
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
	//オートターゲッティング
	OutTarget();
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
	m_movespeed.z = 0.0f;
	m_movespeed.x = 0.0f;
	//カメラの前方と右方向のベクトルを取得
	CVector3 frontxz = m_gamecamera->GetFront();
	CVector3 rightxz = m_gamecamera->GetRight();
	//上記のベクトルをスティックの入力量に応じて乗算
	frontxz *= stickL.y;
	rightxz *= stickL.x;
	//計算したベクトルを移動速度に加算
	m_movespeed += frontxz * m_multiply;
	m_movespeed += rightxz * m_multiply;
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
	moveSpeedXZ.y = 0.0f;
	//移動速度が一定以下、つまり入力がない場合、処理を終了
	if (moveSpeedXZ.LengthSq() < 0.5f) {
		return;
	}
	m_playerheikou = moveSpeedXZ;
	//移動速度のベクトルから角度を求めて、その分キャラクターを回転させる
	m_rotation.SetRotation({0.0f,1.0f,0.0f}, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
}

void Player::Animation()
{
	//Xボタンを押したら、通常攻撃
	if (Pad(0).GetDown(enButtonX) && m_timer >= m_attacktime) {
		if (m_state != enState_Attack) {
			m_state = enState_Attack;
			m_timer = 0;
		}
	}
	//Yボタンを押したら、テクニック発動
	else if (Pad(0).GetButton(enButtonY) && m_timer >= m_attacktime) {
		if (m_state != enState_Aria) {
			if (m_PP >= m_PPCost) {
				if (m_MagicId == 7) {                                                    
					if (m_targetdisplay) {
						m_playerheikou = m_attacktarget;
						m_state = enState_Aria;
						m_timer = 0;
						m_PP -= m_PPCost;
					}
				}
				else {
					if (m_targetdisplay) {
						m_playerheikou = m_attacktarget;
					}
					m_state = enState_Aria;
					m_timer = 0;
					m_PP -= m_PPCost;
				}
			}
		}
	}
	if (m_town == nullptr) {
		//LT押したらゲームオーバー
		if (m_HP <= 0 || Pad(0).GetButton(enButtonLT)) {
			m_state = enState_GameOver;
		}
		//LB1押したらゲームクリア
		else if (Pad(0).GetButton(enButtonRT)) {
			m_state = enState_GameClear;
		}
	}
	if (Pad(0).GetDown(enButtonStart)) {
		if (!m_displaystatus) {
			m_displaystatus = true;
		}
		else {
			m_displaystatus = false;
		}
		int a = 0;
	}
	m_timer += m_frame * GetDeltaTimeSec();
}

void Player::ClearVoice()
{
	//SE
	if (m_state == enState_GameClear) {
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/clear.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_voicevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
	else {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/gameover.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_voicevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
}

void Player::AnimationController()
{
	//アニメーションの再生速度を可変フレームに対応させる
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f * 60.0f * GetDeltaTimeSec());
	//ステート分岐によってアニメーションを再生させる
	switch (m_state) {
	case enState_Run:
	case enState_Idle:
		//	一定速度以上なら走りモーション
		if (m_movespeed.LengthSq() > 300.0f * 300.0f) {
			//走りモーション。
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		//一定速度以上かつ、一定速度以下なら歩きモーション
		else if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
			//歩きモーション。
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_walk, 0.2f);
		}
		//一定速度以下なら待機モーション
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
		//移動
		Move();
		//キャラクターの向き関係
		Turn();
		Animation();
		break;
	case enState_Damage:
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump || m_aria || m_isattack) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
			m_aria = false;
			m_isjump = false;
			m_isattack = false;
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
		//クリアモーションの時には剣は見えなくする
		m_sword->SetScale({ 0.001f,0.001f,0.001f });
		if (!m_clear_over_voice) {
			//クリアボイス
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
			//ゲームオーバーボイス
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
		//ジャンプが終わったら
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
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(7.0f * 60.0f * GetDeltaTimeSec());
			Animation();
			m_isjump = false;
			m_timer = 0;
			m_isattack = true;
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
				m_isattack = false;
			}
			
		}
		//キャラクターの向き関係
		Turn();
		break;
	case enState_Aria:
		if (m_skinModelRender->GetAnimCon().IsPlaying() || m_isjump == true) {
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_aria, 0.2f);
			m_skinModelRender->GetAnimCon().SetSpeed(1.0f * 60.0f * GetDeltaTimeSec());
			Animation();
			m_isjump = false;
			m_timer = 0;
			m_aria = true;
		}
		else {
			//アニメーションの再生が終わったら、アニメーション分岐
			m_timer += m_frame * GetDeltaTimeSec();
			if (m_MagicId == 8) {
				if (m_timer >= m_morugantime) {
					if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
						m_state = enState_Run;
					}
					else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
						m_state = enState_Idle;
					}
					m_timer = 0;
					m_aria = false;
				}
			}
			else {
				if (m_timer >= 20) {
					if (m_movespeed.LengthSq() > 40.0f * 40.0f) {
						m_state = enState_Run;
					}
					else if (m_movespeed.LengthSq() < 40.0f * 40.0f) {
						m_state = enState_Idle;
					}
					m_timer = 0;
					m_aria = false;
				}
			}
		}
		//キャラクターの向き関係
		//Turn();
		//ターゲット座標に応じてキャラクターを回転させる
		float degree = atan2f(m_attacktarget.x, m_attacktarget.z);
		CQuaternion qRot;
		qRot.SetRotation(CVector3::AxisY(), degree);
		m_skinModelRender->SetRot(qRot);
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
		//手のボーンの座標と回転を剣に反映させる
		CVector3 pos = m_skinModelRender->GetBonePos(m_bonehand);
		CQuaternion qRot = m_skinModelRender->GetBoneRot(m_bonehand);
		m_swordrot = qRot;
	    m_swordposition = pos;
	}
	//攻撃していないときは、武器をunityChanの背中に移動させる
	else {
		//ここら辺なにやってたっけ
		//プレイヤーの後方のベクトルを取得し、プレイヤーの後方に武器の座標を設定する
		CVector3 pos = m_playerheikou;
		CQuaternion qRot;
		qRot.SetRotation({0.0f,1.0f,0.0f}, -90.0f);
		pos.Normalize();
		pos *= 10.0f;
		pos = m_position - pos;
		//y座標を加算する
		pos.y += 70.0f;
		CQuaternion qRot2;
		qRot2.SetRotation({ 0.0f,1.0f,0.0f }, -90.0f);
		CVector3 pos2 = m_playerheikou;
		pos2.Normalize();
		qRot2.Multiply(pos2);
		pos2 *= 70.0f;
		pos += pos2;
		m_swordposition = pos;
		//プレイヤーのどっかのボーンの回転を剣の回転に反映
		CQuaternion qRot3 = m_skinModelRender->GetBoneRot(m_bonecenter);
		m_swordrot = qRot3;
	}
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName,L"attack") == 0) {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/attack.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_voicevolume);
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
		//呪文詠唱のエフェクトを発生させる
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		switch (m_MagicId) {
		case 1:
			effect->Play(L"Asset/effect/Effects/efk/cast_fire.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 2:
			effect->Play(L"Asset/effect/Effects/efk/cast_ice.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 3:
			effect->Play(L"Asset/effect/Effects/efk/cast_wind.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 4:
			effect->Play(L"Asset/effect/Effects/efk/cast_sphere.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 5:
			effect->Play(L"Asset/effect/Effects/efk/cast_sphere.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 6:
			effect->Play(L"Asset/effect/Effects/efk/cast_sphere.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 7:
			effect->Play(L"Asset/effect/Effects/efk/cast_sword.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		case 8:
			effect->Play(L"Asset/effect/Effects/efk/cast_laser.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,12.0f,12.0f });
			break;
		}
		effect->SetSpeed(2.0f);
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/aria.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_voicevolume);
		int i = 0;
		if (i == 0) {
			//SE
			SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/aria.wav");
			se->Play(); //再生(再生が終わると削除されます)
			se->SetVolume(m_lvupvollume);
			//3D再生
			se->SetPos(m_position);//音の位置
			se->SetDistance(200.0f);//音が聞こえる範囲
			se->Play(true); //第一引数をtrue
		}
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
	//魔法を発生させる
	else if (wcscmp(eventName, L"aria") == 0) {
		//この魔法だけは他と違うクラスを使う
		if (m_MagicId == 8) {
			Morugan* morugan = new Morugan;
			morugan->SetDamage(m_Mattack, m_DamageRate);
			morugan->SetPosition(m_position + CVector3::AxisY() * m_height);
			morugan->SetRotation(m_rotation);
		}
		else {
			ShotMagic* shotmagic = new ShotMagic;
			if (m_MagicId == 7) {
				shotmagic->SetPosition(m_target);
			}
			else {
				shotmagic->SetPosition(m_position);
			}
			shotmagic->SetDirectionPlayer(m_attacktarget);
			shotmagic->SetId(m_MagicId);
			shotmagic->SetDamage(m_Mattack, m_DamageRate);
			shotmagic->SetName(L"ShotMagic");
		}
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
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/unityChan/bad.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_voicevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
		if (0 == 0) {
			SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/hidamage.wav");
			se->Play(); //再生(再生が終わると削除されます)
			se->SetVolume(m_lvupvollume+1.2f);
			//3D再生
			se->SetPos(m_position);//音の位置
			se->SetDistance(500.0f);//音が聞こえる範囲
			se->Play(true); //第一引数をtrue
		}
		m_damage = true;
		m_timer2 = 0;
		m_state = enState_Damage;
	}
}

void Player::WeaponStatus()
{
	m_Mattack = m_playerstatus->GetMattack();
	m_Attack = m_playerstatus->GetAttack();
	m_ShihutaAttack = m_Attack;
	m_SwordId = m_playerstatus->GetSwordId();
	m_WeaponNumber = m_playerstatus->GetWeaponNumber(m_SwordId);
	m_SwordName = m_playerstatus->GetSwordName();
	m_MagicId = m_playerstatus->GetMagicId();
	m_MaxHP = m_playerstatus->GetMaxHP();
	if (m_HP > m_MaxHP) {
		m_HP = m_MaxHP;
	}
	m_MaxPP = m_playerstatus->GetMaxPP();
	if (m_PP > m_MaxPP) {
		m_PP = m_MaxPP;
	}
}

void Player::MagicStatus()
{
	m_MagicName = m_playerstatus->GetMagicName();
	m_DamageRate = m_playerstatus->GetDamageRate();
	m_PPCost = m_playerstatus->GetPPCost();
}

void Player::SwitchWeapon()
{
	//特定のアニメーション再生時は武器の切り替えをしません
	if (m_state == enState_Aria || m_state == enState_Attack || m_state == enState_Damage || m_state == enState_GameClear ||
		m_state == enState_GameOver) {
		return;
	}
	if (!Pad(0).GetButton(enButtonLB1) && !Pad(0).GetButton(enButtonRB1)) {
		m_isbutton = true;
	}
	//直前にボタンを押していないときにだけ、入力を有効にする
	if (m_isbutton) {
		//左ボタン
		if (Pad(0).GetButton(enButtonLB1)) {
			m_isbutton = false;
			//武器の切り替えが有効であったならば武器のステータスを反映させる
			if (m_playerstatus->GetWeapon(m_SwordId - 1)) {
				WeaponStatus();
				MagicStatus();
				//SE
				SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/swtich.wav");
				se->Play(); //再生(再生が終わると削除されます)
				se->SetVolume(m_voicevolume);
				//3D再生
				se->SetPos(m_position);//音の位置
				se->SetDistance(200.0f);//音が聞こえる範囲
				se->Play(true); //第一引数をtrue
			}
			else {
				return;
			}
		}
		//右ボタン
		if (Pad(0).GetButton(enButtonRB1)) {
			m_isbutton = false;
			//武器の切り替えが有効であったならば武器のステータスを反映させる
			if (m_playerstatus->GetWeapon(m_SwordId + 1)) {
				WeaponStatus();
				MagicStatus();
				//SE
				SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/swtich.wav");
				se->Play(); //再生(再生が終わると削除されます)
				se->SetVolume(m_voicevolume);
				//3D再生
				se->SetPos(m_position);//音の位置
				se->SetDistance(200.0f);//音が聞こえる範囲
				se->Play(true); //第一引数をtrue
			}
			else {
				return;
			}
		}
	}
	m_WeaponNumber = m_playerstatus->GetWeaponNumber(m_SwordId);
	m_sword->SetSwordId(m_WeaponNumber);
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
	//レベルアップ時にエフェクトとSEを発生させる
	if (m_playerstatus->GetLevelUp()) {
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		CVector3 pos = m_position;
		pos.y += m_lvheight;
		effect->Play(L"Asset/effect/lvup/lvup.efk", 1.0f, pos, CQuaternion::Identity(), { 20.0f,20.0f,20.0f });
		effect->SetSpeed(1.5f);
		m_playerstatus->OffLevelUp();
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/lvup.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_lvupvollume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(200.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
	}
}

void Player::Shihuta()
{
	if (m_Shihuta) {
		m_Attack = (int)(m_ShihutaAttack * m_AttackMultiply);
		m_Shihutatimer += m_frame * GetDeltaTimeSec();
		//一定時間経過でシフタ状態をオフにする
		if (m_Shihutatimer >= m_Shihutatime) {
			m_Shihuta = false;
			m_Shihutatimer = 0;
		}
	}
	else {
		m_Attack = m_ShihutaAttack;
	}
}

void Player::Resta(const int& volume)
{
	m_HP += volume;
	if (m_HP > m_MaxHP) {
		m_HP = m_MaxHP;
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
	if (pos.LengthSq() <= 300.0f * 300.0f && m_state==enState_Idle) {
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
	//プレイヤーとの距離が一定以内なら話せます
	if (pos.LengthSq() <= 300.0f * 300.0f && m_state == enState_Idle) {
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
	//RSBボタンでターゲットをロックします
	if (Pad(0).GetDown(enButtonRSB)) {
		if (m_targetlock) {
			m_targetlock = false;
		}
		else {
			m_targetlock = true;
		}
	}
	//ターゲットロック中であれば、ロックしたエネミーの座標をターゲットの座標とします
 	if (m_targetlock && m_targetdisplay) {
		if (!m_enemy->GetDeath()) {
			CVector3 pos = m_enemy->GetCollisionPosition() - m_position;
			if (pos.LengthSq() >= m_distancetarget) {
				m_targetdisplay = false;
				m_targetlock = false;
			}
			else {
				m_target = m_enemy->GetCollisionPosition();	
				m_targetdisplay = true;
				return;
			}
		}
		else {
			m_targetdisplay = false;
			m_targetlock = false;
		}
	}
	//エネミーの座標とプレイヤーとエネミーの距離を記憶する配列です
	std::vector<CVector3> enemyList;
	std::vector<float> distanceList;
	//各可変長配列の長さです
	int enemynumber = 0;
	//プレイヤーの向いている角度を計算します
	float degreep = atan2f(m_playerheikou.x, m_playerheikou.z);
	//計算して出た暫定的に一番小さい角度を記憶する変数です
	float degreemum= M_PI * 2;
	QueryGOs<IEnemy>(L"Enemy", [&](IEnemy* enemy)
	{
		//エネミーが死んでいたら処理を終了します
		if (enemy->GetDeath()) {
			return true;
		}
		CVector3 pos = m_position - enemy->GetCollisionPosition();
		//プレイヤーとエネミーの距離が一定外だったら処理を終了します
		if (pos.LengthSq() >= m_distancetarget) {
			return true;
		}
		//プレイヤーとエネミーを結ぶベクトルを出します
		CVector3 pos2 = enemy->GetCollisionPosition() - m_position;
		//y座標、すなわち高さを0にします
		pos2.y = 0.0f;
		//ベクトルを正規化します
		pos2.Normalize();
		//プレイヤーとエネミーを結ぶベクトルの角度を計算します
		float degree = atan2f(pos2.x, pos2.z);
		//ここら辺のif文要らない可能性が微レ存、「プレイヤーの正面のベクトルの角度」と
		//「プレイヤーとエネミーを結ぶベクトルの角度」の差を計算します
		if (M_PI <= (degreep - degree)) {
			degree = degreep - degree - M_PI * 2;
		}
		else if (-M_PI >= (degreep - degree)) {
			degree = degreep - degree + M_PI * 2;
		}
		else {
			degree = degreep - degree;
		}
		//求めた角度にプレイヤーとエネミーの距離に応じて補正をかけます、距離が長いほど補正は大きいです(値が大きくなります)
		degree = degree + degree * (pos.LengthSq() / m_distancetarget) * m_degreemultiply;
		//求めた値を比較していき、一番小さい値を決めていきます
		if (fabs(degreemum) >= fabs(degree)) {
			degreemum = degree;
			//エネミーの座標を記憶します
			m_target = enemy->GetCollisionPosition();
			m_enemy = enemy;
 		}
		//配列の長さを加算します
		enemynumber++;
		return true;
	});
	//配列の長さが0つまり、配列に何も記憶されていない場合、処理を終了します
	if (enemynumber == 0) {
		m_enemy = nullptr;
		m_targetdisplay = false;
		return;
	}
	//求めた一番小さい値が一定値より小さい場合、ターゲッティングをオンにします
	if (fabs(degreemum) <= M_PI / 3) {
		m_targetdisplay = true;
	}
	//逆に一定値より大きい場合、ターゲッティングをオフにします
	else {
		m_targetdisplay = false;
		m_enemy = nullptr;
	}
}

void Player::PostRender()
{
	if (m_cagliostro) {
		return;
	}
	//ターゲッティングがオンであればターゲットの画像を表示します
	if (m_targetdisplay) {
		//該当のワールド座標を2D座標を変換します)
		CVector3 pos = m_gamecamera->GetCamera()->CalcScreenPosFromWorldPos(m_target);
		//エネミーの座標が画面外であれば画像は表示しません
		//該当の座標にターゲットの座標を表示します
		if (0.0f <= pos.x && pos.x <= 1.0f && 0.0f <= pos.y && pos.y <= 1.0f && 0.0f <= pos.z && pos.z <= 1.0f) {
			CVector3 scpos = pos;
			//ターゲットロック中かどうかで表示する画像を変えます
			if (m_targetlock) {
				m_locktargetsprite.Draw(scpos, { 0.2f,0.2f }, { 0.5f,0.5f },
					0.0f,
					{ 1.0f, 1.0f, 1.0f, 1.0f },
					DirectX::SpriteEffects_None,
					1.0f);
			}
			else {
				m_targetsprite.Draw(scpos, { 0.2f,0.2f }, { 0.5f,0.5f },
					0.0f,
					{ 1.0f, 1.0f, 1.0f, 1.0f },
					DirectX::SpriteEffects_None,
					1.0f);
			}
			CVector3 pos = m_position;
			pos.y += 60.0f;
			pos = m_target - pos;
			pos.Normalize();
			m_attacktarget = pos;
		}
		else {
			m_attacktarget = m_playerheikou;
			m_targetdisplay = false;
		}
	}
	else {
		m_attacktarget = m_playerheikou;
	}
	//プレイヤーのステータスを表示します
	/*wchar_t output[256];
	swprintf_s(output, L"x   %f\ny   %f\nz  %f\n", m_position.x, m_position.y, m_position.z);
	m_font.Draw(output,CVector2::Zero());*/
	//ステータス表示
	if (m_displaystatus) {
		//プレイヤーのステータスを表示します
		wchar_t output[256];
		swprintf_s(output, L"unityChan\nLv. %d\nHP        %d\nPP        %d\n力        %d\n賢さ      %d\n打撃力    %d\n法撃力    %d\nEx        %d\nNex       %d\n",m_Level,m_MaxHP,m_MaxPP,m_playerstatus->GetPower(),m_playerstatus->GetClever(),m_Attack,m_Mattack,m_Exp,m_NextExp);
		m_font.DrawScreenPos(output, { 705.0f,60.0f }, CVector4::White(), {1.0f,1.0f});
		m_statussprite.DrawScreenPos({ 700.0f,50.0f }, {1.0f,1.0f}, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
		//武器関連のステータスを表示します
		wchar_t output2[256];
		swprintf_s(output2, L"武器\n武器Lv  %d\n武器名  %ls\n打撃力  %d\n法撃力  %d\n魔法    %ls\n消費PP  %d\n威力    %d\n",m_playerstatus->GetWeaponLv(),m_SwordName,m_playerstatus->GetWeaponAttack(),m_playerstatus->GetWeaponMattack(),m_MagicName,m_PPCost,int(m_DamageRate*100));
		m_font.DrawScreenPos(output2, { 230.0f,60.0f }, CVector4::White(), { 0.7f,0.7f });
		m_weaponstatussprite.DrawScreenPos({ 227.0f,50.0f }, { 1.0f,1.0f }, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
		//インベントリ関連のステータスを表示します
		wchar_t output3[256];
		swprintf_s(output3, L"インベントリ\n木        %d\n石        %d\nレンガ    %d\nメセタ    %dM\n",m_playerstatus->GetMaterial(0), m_playerstatus->GetMaterial(1), m_playerstatus->GetMaterial(2), m_playerstatus->GetHaveMeseta());
		m_font.DrawScreenPos(output3, { 445.0f,317.0f }, CVector4::White(), { 0.7f,0.7f });
		m_inventorystatussprite.DrawScreenPos({ 442.0f,307.0f }, { 1.0f,1.0f }, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			1.0f);
	}
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
			0.7f);
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
			0.7f);
	}
	//hpのHUD関係
	float hpRate = (float)m_HP / m_MaxHP;
	float offsetX = (hpRate - 1.0f) / 2;
	m_spriteposition.x = m_protspriteposition.x + offsetX;
	m_hud.DrawScreenPos({ 5.0f,595.0f }, CVector2::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		1.0f);
	m_logo.DrawScreenPos({ 30.0f,640.0f }, {0.4f,0.4f}, CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.9f);
	if (true) {
		wchar_t output[50];
		swprintf_s(output, L"unityChan\n");
		m_name.DrawScreenPos(output, { 165.0f,600.0f }, CVector4::White(), { 0.6f,0.6f });
	}
	if (true) {
		wchar_t output[50];
		swprintf_s(output, L"Lv  %d\n", m_Level);
		m_lvf.DrawScreenPos(output, { 20.0f,600.0f }, CVector4::White(), { 0.7f,0.7f });
	}
	if (true) {
		m_hpf.DrawScreenPos(L"HP", { 140.0f,643.0f }, CVector4::White(), { 0.4f,0.4f });
		wchar_t output[10];
		swprintf_s(output, L"%d", m_HP);
		m_hpf.DrawScreenPos(output, { 180.0f,635.0f }, CVector4::White(), { 0.6f,0.6f });
		wchar_t output2[10];
		swprintf_s(output2, L"/ %d\n", m_MaxHP);
		m_hpf.DrawScreenPos(output2, { 235.0f,635.0f }, CVector4::White(), { 0.6f,0.6f });
		m_hpframe.DrawScreenPos({140.0f,662.0f}, CVector2::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.9f);
		m_hpgage.DrawScreenPos({ 140.0f,662.0f }, {(float)m_HP/m_MaxHP,1.0f}, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.8f);
	}
	if (true) {
		m_ppf.DrawScreenPos(L"PP", { 140.0f,682.0f }, CVector4::White(), { 0.4f,0.4f });
		wchar_t output[30];
		swprintf_s(output, L"%d", m_PP);
		m_ppf.DrawScreenPos(output, { 180.0f,674.0f }, CVector4::White(), { 0.6f,0.6f });
		wchar_t output2[10];
		swprintf_s(output2, L"/ %d\n", m_MaxPP);
		m_ppf.DrawScreenPos(output2, { 235.0f,674.0f }, CVector4::White(), { 0.6f,0.6f });
		m_ppframe.DrawScreenPos({ 140.0f,701.0f }, CVector2::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.9f);
		m_ppgage.DrawScreenPos({ 140.0f,701.0f }, { (float)m_PP / m_MaxPP,1.0f }, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.8f);
	}
}
