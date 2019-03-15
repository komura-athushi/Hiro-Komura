#include "stdafx.h"
#include "Boss.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
#include "Player.h"
#include "BossAttack.h"
#include "GameCamera.h"
#include "Teleport.h"
//cppでエネミーのレア度ごとのドロップ率を設定
const int Boss::m_dropChances[Weapon::m_HighestRarity] = { 0,0,100,0,0,0,0 };
const int Boss::m_dropmaterialChances[Material::m_HighestRarity] = { 0,100,0 };
//ボスです
Boss::Boss() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{

}
Boss::~Boss()
{
	delete m_skinModelRender;
	Teleport* tl = new Teleport;
	tl->SetPosition(m_position);
	tl->SetName(L"Teleport");
}

bool Boss::Start()
{
	IEnemy::CCollision(m_position , m_collisionheight, m_r);
	//ボスのスキンモデルレンダーを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/boss.cmo");
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	pos.y += 500.0f;
	m_staticobject.CreateSphere(pos, rot, 150.0f);

	return true;
}

void Boss::Attack()
{
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	m_playerposition.y += 100.0f;

	if(m_HP >= 600) {
		if (m_timer >= m_cooltime) {
			BossAttack* bossattack = new BossAttack;
			bossattack->SetName(L"bossattack");
			bossattack->SetNumber(1);
			m_atktype = 1;
			//弾丸の座標にボスの座標を代入する。
			CVector3 l_pos = m_position;
			l_pos.y += 70.0f;
			bossattack->SetPosition(l_pos);
			CVector3 bulletPos = m_playerposition - l_pos;
			bulletPos.Normalize();
			bulletPos = bulletPos * 30.0f;
			//弾のスピードを変える
			bossattack->SetMoveSpeed(bulletPos);
			
			//タイマーをリセット。
			m_timer = 0;
		}
	}
	else if(m_HP >= 300) {
		if (m_timer >= m_cooltime) {
			BossAttack* bossattack = new BossAttack;
			bossattack->SetName(L"bossattack");
			bossattack->SetNumber(2);
			m_atktype = 2;

			//弾丸の座標にボスの座標を代入する。
			CVector3 l_pos = m_position;
			l_pos.y += 200.0f;
			bossattack->SetPosition(l_pos);

			CVector3 bulletPos = m_playerposition - l_pos;
			bulletPos.Normalize();
			bulletPos = bulletPos * 10.0f;
			//弾のスピードを変える
			bossattack->SetMoveSpeed(bulletPos);

			//タイマーをリセット。
			m_timer = 0;
		}
	}
	else {
		if (m_timer >= m_atk3cooltime) {
			m_atk3timer++;
			if (m_atk3timer >= 30) {
				BossAttack* bossattack = new BossAttack;
				bossattack->SetName(L"bossattack");
				bossattack->SetNumber(3);
				m_atktype = 3;

				//弾丸の座標にボスの座標を代入する。
				CVector3 l_pos = m_position;
				l_pos.y += 200.0f;
				bossattack->SetPosition(l_pos);

				CVector3 bulletPos = m_playerposition - l_pos;
				bulletPos.Normalize();
				bulletPos = bulletPos * 10.0f;
				//弾のスピードを変える
				bossattack->SetMoveSpeed(bulletPos);
				m_atk3timer = 0;
				m_atk3count++;
				if (m_atk3count == 3) {
					//タイマーをリセット。
					m_timer = 0;
					m_atk3count = 0;
				}
			}
		}
	}
} 

//IEnemyにいれる
void Boss::Turn()
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

void Boss::Damage()
{
	//プレイヤーと弾の当たり判定
	QueryGOs<BossAttack>(L"bossattack", [&](BossAttack* bullet)->bool {
		CVector3 diff = bullet->GetPosition() - m_player->GetPosition();
		if (diff.Length() < 130.0f) {  //距離が一定以下になったら。
			delete bullet;
			if (m_atktype == 1) {
				m_player->Damage(m_Attack1);
			}
			else if (m_atktype == 2) {
				m_player->Damage(m_Attack2);
			}
			else if (m_atktype == 3) {
				m_player->Damage(m_Attack3);

			}
		}
		return true;
	});
}

void Boss::PostRender()
{
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.LengthSq() < 1700.0f * 1700.0f) {
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
}

void Boss::Update()
{
	if (!IEnemy::m_death) {
		m_timer++;
		m_movespeed = m_player->GetPosition() - m_position;
		Turn();
		Attack();
		CQuaternion rot;
		CVector3 pos = m_position;
		pos.y += 270.0f;
		m_staticobject.SetPositionAndRotation(pos, rot);
		IEnemy::SetCCollision(m_position, m_collisionheight);
		Damage();
	}
	//死んだら消す
	if (m_death) {
		m_deathtimer += 40.0f * GetDeltaTimeSec();
		if (m_deathtimer = 10) {
			delete this;
		}
	}
}
