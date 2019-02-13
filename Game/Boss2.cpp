#include "stdafx.h"
#include "Boss2.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
#include "Game.h"
#include "Player.h"
#include "BossAttack.h"
#include "GameCamera.h"
//cppでエネミーのレア度ごとのドロップ率を設定
const int Boss2::m_dropChances[Weapon::m_HighestRarity] = { 0,0,0,100,0,0,0 };
const int Boss2::m_dropmaterialChances[Material::m_HighestRarity] = { 0,0,100 };
//ボス2(ドラゴン)です
Boss2::Boss2() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{

}

Boss2::~Boss2()
{
	delete m_skinModelRender;
}

bool Boss2::Start()
{
	IEnemy::CCollision(m_position, m_collisionheight, m_r);
	//アニメーション
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/boss2/boss2_idle.tka");
	m_animClip[enAnimationClip_run].Load(L"Asset/animData/boss2/boss2_run.tka");
	m_animClip[enAnimationClip_attack1].Load(L"Asset/animData/boss2/boss2_attack1.tka");
	m_animClip[enAnimationClip_attack2].Load(L"Asset/animData/boss2/boss2_attack2.tka");
	m_animClip[enAnimationClip_attack3].Load(L"Asset/animData/boss2/boss2_attack3.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/boss2/boss2_damage.tka");
	m_animClip[enAnimationClip_death].Load(L"Asset/animData/boss2/boss2_death.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_run].SetLoopFlag(true);
	m_animClip[enAnimationClip_attack1].SetLoopFlag(false);
	m_animClip[enAnimationClip_attack2].SetLoopFlag(false);
	m_animClip[enAnimationClip_attack3].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_death].SetLoopFlag(false);
	//ドラゴンのスキンモデルレンダーを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/DarkDragon.cmo", m_animClip, enAnimationClip_num);
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	pos.y += 500.0f;
	m_staticobject.CreateSphere(pos, rot, 0.0f);
	return true;
}

void Boss2::Attack()
{
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	m_playerposition.y += 100.0f;
	//プレイヤーとドラゴンの距離
	CVector3 pos = m_player->GetPosition() - m_position;
	//ファイヤーブレス
	if (pos.LengthSq() > 500.0f*500.0f) {
	if (m_timer >= m_cooltime) {
			m_state = enState_Attack1;
			//タイマーをリセット。
			m_timer = 0;
		}
	}
	//プレス
	else if (pos.LengthSq() > 300.0f*300.0f) {
		if (m_timer >= m_cooltime) {
			m_state = enState_Attack2;
			//タイマーをリセット。
			m_timer = 0;
		}
	}
	//ひっかき
	else {
		if (m_timer >= m_cooltime) {
			m_state = enState_Attack3;
			//タイマーをリセット。
			m_timer = 0;
		}
	}
}

void Boss2::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f);
	//ステート分岐によってアニメーションを再生させる
	switch (m_state) {
	case enState_Idle_Run:
		if (m_movespeed.LengthSq() > 1.0f) {
			//走りモーション。
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		else {
			//待機モーション
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		}
		Turn();
		Chase();
		//Attack();
		break;
	case enState_Attack1:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack1, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Attack2:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack2, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Attack3:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack3, 0.2f);
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
void Boss2::Chase()
{
	m_movespeed = { 0.0f,0.0f,0.0f };
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	//プレイヤーと敵の距離
	CVector3 pos = m_player->GetPosition() - m_position;
	//ボスの初期位置と現在位置の距離
	CVector3 oldpos = m_oldpos - m_position;
	//もしプレイヤーとボスの距離が近くなったら
	if (pos.LengthSq() < 1000.0f*1000.0f) {
		//もしアニメーションが再生されていなかったら
		if (!m_skinModelRender->GetAnimCon().IsPlaying()) {
			//近づいてくる
			CVector3 EnemyPos = m_playerposition - m_position;
			EnemyPos.Normalize();
			m_movespeed = EnemyPos * m_enemyspeed;
			m_movespeed.y = 0.0f;
			m_position += m_movespeed;
		}
		else if (pos.LengthSq() > 1000.0f*1000.0f) {
			//初期位置に帰る
			CVector3 EnemyOldPos = m_oldpos - m_position;
			EnemyOldPos.Normalize();
			m_movespeed = EnemyOldPos * m_enemyspeed;
			m_movespeed.y = 0.0f;
			//敵の初期位置と現在位置の距離がほぼ0だったら止まる
			if (oldpos.Length() < 50.0f) {
				m_movespeed = { 0.0f,0.0f,0.0f };
			}
			m_position += m_movespeed;
		}
	}
	m_skinModelRender->SetPos(m_position);
}

//IEnemyにいれる
void Boss2::Turn()
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
	m_parallel = moveSpeedXZ;
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
}

void Boss2::Damage()
{
	if (IEnemy::m_damage) {
		m_state = enState_Damage;
		IEnemy::m_damage = false;
	}
}

void Boss2::Dead()
{
	if (IEnemy::m_death) {
		m_state = enState_Dead;
	}
}

void Boss2::PostRender()
{
	GameCamera* gc = FindGO<GameCamera>();
	//もしFindGOでカメラを見つけられたら
	if (gc != nullptr) {
		if (m_atktype == 1 || m_atktype == 2) {
			if (m_timer >= m_cooltime - m_posttiming) {
				wchar_t output[256];
				swprintf_s(output, L"！\n");
				CVector3 drawpos = m_player->GetPosition();
				drawpos.y += 150.0f;
				drawpos.x += 40.0f;
				//3Dの座標を2Dに変換
				CVector2 pos = gc->GetCamera()->CalcScreenPosFromWorldPos(drawpos);
				CVector2 scale = { 3.0f,3.0f };
				m_font.Draw(output, pos, CVector4(225.0f, 00.0f, 00.0f, 0.8f), scale);
			}
		}
		else if (m_atktype == 3) {
			if (m_timer >= m_atk3cooltime - m_posttiming) {
				wchar_t output[256];
				swprintf_s(output, L"！\n");
				CVector3 drawpos = m_player->GetPosition();
				drawpos.y += 150.0f;
				drawpos.x += 40.0f;
				//3Dの座標を2Dに変換
				CVector2 pos = gc->GetCamera()->CalcScreenPosFromWorldPos(drawpos);
				CVector2 scale = { 3.0f,3.0f };
				m_font.Draw(output, pos, CVector4(225.0f, 00.0f, 00.0f, 0.8f), scale);
			}

		}
	}
}

void Boss2::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName, L"attack1") == 0) {
		//攻撃判定の発生
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//形状の作成
		CVector3 atkpos = m_position;
		atkpos.z += 50.0f;
		CVector3 pos = atkpos + CVector3::AxisY()*m_collisionheight;
		pos += m_parallel * 130.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), m_attackr);
		//寿命を設定
		attackCol->SetTimer(3);//15フレーム後削除される
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//衝突した判定の名前が"Player"ならm_Attack1分だけダメージ与える
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();
				player->Damage(m_Attack1);
			}
		}
		);
	}
}


void Boss2::Update()
{
	m_timer++;
	AnimationController();
	Attack();
	if (!IEnemy::m_death) {
		CQuaternion rot;
		CVector3 pos = m_position;
		pos.y += 55.0f;
		m_staticobject.SetPositionAndRotation(pos, rot);
		IEnemy::SetCCollision(m_position, m_collisionheight);
	}
	Damage();
	Dead();

	//死んだら消す
	if (m_gekiha) {
		delete this;
	}
}
