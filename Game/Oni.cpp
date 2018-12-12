#include "stdafx.h"
#include "Oni.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
#include "Stage1.h"
#include "Player.h"
//cppでエネミーのレア度ごとのドロップ率を設定
const int Oni::m_dropChances[Weapon::m_HighestRarity] = { 0,100,0,0,0,0,0 };
const int Oni::m_dropmaterialChances[Material::m_HighestRarity] = { 100.0f,0.0f,0.0f };
//鬼（見た目はスケルトン）です
Oni::Oni():IEnemy(m_MaxHP,m_Attack,m_EXP,m_dropChances,m_dropmaterialChances)
{

}

Oni::~Oni()
{
	delete m_skinModelRender;
}

bool Oni::Start()
{
	IEnemy::CCollision({ m_position }, m_collisionheight, m_r);
	//アニメーション
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/enemy/idle.tka");
	m_animClip[enAnimationClip_attack].Load(L"Asset/animData/enemy/attack.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/enemy/damage.tka");
	m_animClip[enAnimationClip_death].Load(L"Asset/animData/enemy/death.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_attack].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_death].SetLoopFlag(false);
	//鬼のスキンモデルレンダーを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/enemy.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisZ);
	m_skinModelRender->GetAnimCon().AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot;
	CVector3 pos = m_position;
	pos.y += 55.0f;
	m_staticobject.CreateCapsule(pos, rot, 40.0f, 50.0f);
	return true;
}

void Oni::Attack()
{
}
void Oni::Chase()
{
	m_movespeed = { 0.0f,0.0f,0.0f };
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	//プレイヤーと敵の距離
	CVector3 pos = m_player->GetPosition() - m_position;
	//敵の初期位置と現在位置の距離
	CVector3 oldpos = m_oldpos - m_position;
	//接触したら攻撃
	if (pos.Length() < 100.0f) {
	m_state = enState_Attack;
	}
	//もしプレイヤーと鬼の距離が近くなったら
	else if (pos.Length() < 1000.0f) {
		//近づいてくる
		CVector3 EnemyPos = m_playerposition - m_position;
		EnemyPos.Normalize();
		m_movespeed = EnemyPos * 5.0f;
		m_movespeed.y = 0.0f;
		m_position += m_movespeed;
	}
	
	else if(pos.Length() > 1000.0f){
		//初期位置に帰る
		CVector3 EnemyOldPos = m_oldpos - m_position;
		EnemyOldPos.Normalize();
		m_movespeed = EnemyOldPos * 5.0f;
		m_movespeed.y = 0.0f;
		//敵の初期位置と現在位置の距離がほぼ0だったら止まる
		if (oldpos.Length() < 50.0f) {
			m_movespeed = { 0.0f,0.0f,0.0f };
		}
		m_position += m_movespeed;
	}
	m_skinModelRender->SetPos(m_position);
}

void Oni::AnimationController()
{
	m_skinModelRender->GetAnimCon().SetSpeed(1.0f);
	//ステート分岐によってアニメーションを再生させる
	switch (m_state) {
	case enState_Idle_Run:
		if (m_movespeed.LengthSq() > 300.0f * 300.0f) {
			//走りモーション。
			//m_skinModelRender->GetAnimCon().Play(enAnimationClip_run, 0.2f);
		}
		else {
			//待機モーション
			m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		}
		//m_state = enState_Idle_Run;
		Chase();
		Turn();
		break;
	case enState_Attack:
		//攻撃と攻撃の間にクールタイムを設ける
		if (m_timer > 60) {
			if (m_skinModelRender->GetAnimCon().IsPlaying()) {
				m_skinModelRender->GetAnimCon().Play(enAnimationClip_attack, 0.0f);
				m_timer = 0;
			}
			else {
				m_state = enState_Idle_Run;
			}
		}
		Turn();
		break;
	case enState_Damage:
		m_skinModelRender->GetAnimCon().SetSpeed(2.0f);
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_damage, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()){
				m_state = enState_Idle_Run;
		}
		Turn();
		break;
	case enState_Dead:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_death, 0.2f);
		if (!m_skinModelRender->GetAnimCon().IsPlaying()){
			m_gekiha = true;
		}
		break;
	}
}

void Oni::Turn()
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
	m_heikou = moveSpeedXZ;
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
	m_skinModelRender->SetRot(m_rotation);
}

void Oni::Damage() 
{
	if (IEnemy::m_damage) {
		m_state = enState_Damage;
		IEnemy::m_damage = false;
	}
}

void Oni::Dead()
{
	if (IEnemy::m_death) {
		m_state = enState_Dead;
	}
}

void Oni::Update()
{
	m_timer++;
	AnimationController();
	Damage();
	Dead();
	IEnemy::SetCCollision(m_position, m_collisionheight);
	if (!IEnemy::m_death) {
		CQuaternion rot;
		CVector3 pos = m_position;
		pos.y += 55.0f;
		m_staticobject.SetPositionAndRotation(pos, rot);
	}
	if (m_gekiha) {
		delete this;
	}
}

void Oni::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName, L"attack") == 0) {
		//攻撃判定の発生
		SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
		//形状の作成
		CVector3 pos = m_position + CVector3::AxisY()*m_collisionheight;
		pos += m_heikou * 130.0f;
		attackCol->CreateSphere(pos, CQuaternion::Identity(), m_attackr);
		//寿命を設定
		attackCol->SetTimer(3);//15フレーム後削除される
		attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
			//衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
			if (param.EqualName(L"Player")) {
				Player* player = param.GetClass<Player>();//相手の判定に設定されているCEnemyのポインタを取得
				player->Damage(m_Attack);
			}
		}
		);
	}
}
