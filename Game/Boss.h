#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Game;
class Player;
class BossAttack;
class Boss : public IEnemy
{
public:
	Boss();
	~Boss();
	bool Start() override;
	void Update() override;
	void Attack();       										//攻撃
	void Damage();												//ダメージを受けた時のアクション
	void Turn();												//キャラクターの向きを計算
	//文字表示
	void PostRender()override;
	void SetPlayer(Player* player)								//プレイヤーのポイントをセット
	{
		m_player = player;
	}
	void SetBossAttack(BossAttack* bossattack)					//BossAttackのポイントをセット
	{
		m_bossattack = bossattack;
	}
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	void SetStage1(Game* stage1)
	{
		m_stage1 = stage1;
	}
	void SetOldPosition(const CVector3 pos)
	{
		m_oldpos = pos;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	CVector3 m_oldpos = { 0.0f,0.0f,0.0f };						//ボスの初期位置
	CVector3 m_position = { 0.0f,0.0f,0.0f };					//ボスの座標
	CVector3 m_scale = { 1.5f,1.5f,1.5f };						//ボスのスケール
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//移動速度
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//ユニティちゃんの向きと平行なベクトル
	Player* m_player;											//プレイヤークラスのポインタ
	BossAttack* m_bossattack;									//BossAttackクラスのポインタ
	CFont m_font;												//文字表示クラス
	bool m_disp = false;										//ダメ表示するかどうか
	//自機の角度　初期は180度
	float m_degree = 180.0f;                                    //ユニティちゃんの向いてる角度
	float m_radian = 0;                                         //上記をラジアン単位に直したもの
	CQuaternion m_rotation;
	Game* m_stage1;
	int m_timer = 0;											//攻撃のクールタイムのためにフレーム数を数える
	int m_atk3timer = 0;										//攻撃3のクールタイムのためにフレーム数を数える
	int m_atk3count = 0;
	int m_cooltime = 200;										//攻撃が終わった後のクールタイム
	int m_atk3cooltime = 300;									//攻撃3が終わった後のクールタイム
	int m_posttiming = 30;										//攻撃が来る前の注意のタイミング
	int m_atktype = 0;											//攻撃の種類
	float m_r = 150.0f;                                         //コリジョンの半径
	float m_collisionheight = 270.0f;                           //コリジョンをm_positionからどれだけ上にあげるか
	//Bossの色々なステータス
	static const int m_MaxHP = 1800;                             //最大HP
	static const int m_Attack1 = 50;							//攻撃力1
	static const int m_Attack2 = 100;							//攻撃力2
	static const int m_Attack3 = 90;							//攻撃力3
	static const int m_EXP = 500;                               //経験値
	static const int m_dropChances[];				            //エネミーのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	float m_deathtimer = 0.0f;
	const int m_attack1 = 50;
	const int m_attack2 = 60;
	const int m_attack3 = 80;
};

