#include "stdafx.h"
#include "Dragon.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy_Fire.h"
#include "Teleport.h"
//cppでエネミーのレア度ごとのドロップ率を設定
const int Dragon::m_dropChances[Weapon::m_HighestRarity] = { 0,0,0,100,0,0,0 };
const int Dragon::m_dropmaterialChances[Material::m_HighestRarity] = { 0.0f,100.0f,0.0f };
//ボス2(ドラゴン)です
Dragon::Dragon() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{

}

Dragon::~Dragon()
{
	delete m_skinModelRender;
	Teleport* tl = new Teleport;
	tl->SetPosition(m_position);
	tl->SetName(L"Teleport");
}

bool Dragon::Start()
{
	IEnemy::CCollision(m_position, m_collisionheight, m_r);
	//アニメーション
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/boss2/boss2_idle.tka");
	//m_animClip[enAnimationClip_idle].Load(L"Asset/animData/boss_2/attack1.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/boss2/boss2_run.tka");
	m_animClip[enAnimationClip_hikkaki].Load(L"Asset/animData/boss2/boss2_hikkaki.tka");
	m_animClip[enAnimationClip_fire].Load(L"Asset/animData/boss2/boss2_fire.tka");
	m_animClip[enAnimationClip_press].Load(L"Asset/animData/boss2/boss2_press.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/boss2/boss2_damage.tka");
	m_animClip[enAnimationClip_death].Load(L"Asset/animData/boss2/boss2_death.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_run].SetLoopFlag(true);
	m_animClip[enAnimationClip_hikkaki].SetLoopFlag(false);
	m_animClip[enAnimationClip_fire].SetLoopFlag(false);
	m_animClip[enAnimationClip_press].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_death].SetLoopFlag(false);
	//ドラゴンのスキンモデルレンダーを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/DarkDragon.cmo", m_animClip, enAnimationClip_num);
	//m_skinModelRender->Init(L"Resource/modelData/rockgolem.cmo", m_animClip, enAnimationClip_num);
	//m_skinModelRender->Init(L"Resource/modelData/rockgolem.cmo");
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	//pos.y += 500.0f;
	m_staticobject.CreateSphere(pos, rot, 150.0f);
	//unityChanのボーンを検索
	m_bonehead = m_skinModelRender->FindBoneID(L"Bone016");
	m_bone = m_skinModelRender->FindBoneID(m_bonename);
	return true;
}

void Dragon::Attack()
{
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	m_playerposition.y += 100.0f;
	//プレイヤーとドラゴンの距離
	CVector3 pos = m_player->GetPosition() - m_position;
	
	//ひっかき
	if(pos.LengthSq() < 300.0f*300.0f){
		if (m_timer >= m_cooltime) {
			m_state = enState_Hikkaki;
			//タイマーをリセット。
			m_timer = 0;
		}
	}
	//プレス
	else if (pos.LengthSq() < 450.0f * 450.0f) {
		if (m_timer >= m_cooltime) {
			m_state = enState_Press;
			//タイマーをリセット。.
			m_timer = 0;
		}
	}
	//ファイヤーブレス
	else if (pos.LengthSq() < 1000.0f*1000.0f){
		if (m_timer >= m_cooltime) { 
			m_state = enState_Fire;
			//タイマーをリセット。
			m_timer = 0;
		}
	}
}

void Dragon::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f * 40.0f * GetDeltaTimeSec());
	//ステート分岐によってアニメーションを再生させる
	switch (m_state) {
	case enState_Idle_Run:
		if (m_movespeed.LengthSq() > 1.0f*1.0f) {
			//走りモーション。
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		else {
			//待機モーション
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		}
		Chase();
		Turn();
		//Attack();
		break;
	case enState_Hikkaki:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_hikkaki, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Fire:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_fire, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Press:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_press, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Damage:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Dead:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_death, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_gekiha = true;
		}
		break;
	}
}

//try
void Dragon::Chase()
{
	m_movespeed = { 0.0f,0.0f,0.0f };
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	//プレイヤーと敵の距離
	CVector3 pos = m_player->GetPosition() - m_position;
	//敵の初期位置と現在位置の距離
	CVector3 oldpos = m_oldpos - m_position;
	//攻撃
	if (pos.LengthSq() < 500.0f * 500.0f) {
		Attack();
	}
	//もしプレイヤーと鬼の距離が近くなったら
	if (pos.LengthSq() < 1000.0f * 1000.0f) {
		if (pos.LengthSq() > 200.0f * 200.0f) {
			//近づいてくる
			CVector3 EnemyPos = m_playerposition - m_position;
			EnemyPos.Normalize();
			m_movespeed = EnemyPos * 2.5f;
			m_movespeed.y = 0.0f;
			m_position += m_movespeed;
			m_ischase = true;
		}
		else {
			m_ischase = false;
		}
	}

	else if (pos.LengthSq() > 1000.0f*1000.0f) {
		//初期位置に帰る
		CVector3 EnemyOldPos = m_oldpos - m_position;
		EnemyOldPos.Normalize();
		m_movespeed = EnemyOldPos * 5.0f;
		m_movespeed.y = 0.0f;
		//敵の初期位置と現在位置の距離がほぼ0だったら止まる
		if (oldpos.LengthSq() < 50.0f * 50.0f) {
			m_movespeed = { 0.0f,0.0f,0.0f };
		}
		m_position += m_movespeed;
	}

	m_skinModelRender->SetPos(m_position);
}

//IEnemyにいれる
void Dragon::Turn()
{
	CVector3 rotation = { 0.0f,0.0f,0.0f };
	//自機の角度の差分
	float sdegree = 0.0f;
	m_radian = M_PI / 180 * m_degree;
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
	if (m_ischase) {
		m_parallel = moveSpeedXZ;
		m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	}
	else {
		CVector3 pos = m_player->GetPosition() - m_position;
		pos.y = 0.0f;
		pos.Normalize();
		m_rotation.GetRotation(CVector3::AxisY(), atan2f(pos.x, pos.z));
	}
	m_skinModelRender->SetRot(m_rotation);
}

void Dragon::Damage()
{
	if (IEnemy::m_damage) {
		int ran = rand() % 10+1;
		if (ran > 7) {
			m_state = enState_Damage;
		}
		IEnemy::m_damage = false;
	}
}

void Dragon::Dead()
{
	if (IEnemy::m_death) {
		m_state = enState_Dead;
	}
}


void Dragon::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	//ひっかき
	if (wcscmp(eventName, L"hikkaki") == 0) {
		//攻撃判定の発生
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//形状の作成
		CVector3 atkpos = m_position;
		atkpos.z += 50.0f;
		CVector3 pos = atkpos + CVector3::AxisY() * (m_collisionheight-30.0f);
		pos += m_parallel * 150.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), m_attackr);
		//寿命を設定
		attackCol->SetTimer(20);//フレーム後削除される
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//衝突した判定の名前が"Player"ならm_Attack1分だけダメージ与える
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack1);
			}
		}
		);
	//プレス
	}else if (wcscmp(eventName, L"press") == 0) {
		//攻撃判定の発生
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//形状の作成
		CVector3 atkpos = m_position;
		atkpos.y -= 150.0f;
		attackCol->CreateSphere(atkpos, CQuaternion::Identity(), m_attack2r);
		//寿命を設定
		attackCol->SetTimer(5);//フレーム後削除される
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//衝突した判定の名前が"Player"ならm_Attack1分だけダメージ与える
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack2);
			}
		}
		);
	}
	//ファイヤー
	else if (wcscmp(eventName, L"fire") == 0) {
		//プレイヤーの座標を取得
		CVector3 m_playerposition = m_player->GetPosition();
		m_playerposition.y += 100.0f;
		//ボスの頭の座標
		CVector3 b_pos = m_skinModelRender->GetBonePos(m_bonehead);
		//プレイヤーとボスの距離
		CVector3 pos = m_player->GetPosition() - m_position;
		Enemy_Fire* fire = new Enemy_Fire;
		//弾丸の座標にボスの座標を代入する。
		fire->SetPosition(b_pos);
		fire->SetAttack(m_attackfire);
		CVector3 bulletPos = m_playerposition - b_pos;
		bulletPos.Normalize();
		//弾のスピードを変える
		fire->SetMoveSpeed(bulletPos);
	}
}

void Dragon::Update()
{
	m_timer++;
	AnimationController();
	Attack();
	if (!IEnemy::m_death) {
		CQuaternion rot;
		CVector3 pos = m_position;
		pos.y += 55.0f;
		if (m_state == enState_Press) {
			CVector3 pos = m_skinModelRender->GetBonePos(m_bone);
			m_staticobject.SetPositionAndRotation(pos, rot);
			IEnemy::SetCCollision(pos);
		}
		else {
			m_staticobject.SetPositionAndRotation(pos, rot);
			IEnemy::SetCCollision(m_position, m_collisionheight);
		}
	}
	Damage();
	Dead();
	//死んだら消す
	if (m_gekiha) {
		delete this;
	}
}
