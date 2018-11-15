#pragma once
#include "Player.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Oni : public IEnemy
{
public:
	Oni();
	~Oni();
	bool Start() override;
	void Update() override;
	void Attack() override;										//攻撃
	void Chase();												//追跡
	void AnimationController();									//アニメーションの再生
	void Damage();												//ダメージを受けた時のアクション
	void Turn();												//キャラクターの向きを計算
	void Dead();												//エネミーが死んだときの処理
	void SetPlayer(Player* player)								//プレイヤーのポイントをセット
	{
		m_player = player;
	}

private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_attack,
		enAnimationClip_damage,
		enAnimationClip_death,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle_Run,
		enState_Attack,
		enState_Damage,
		enState_Dead,
	};
	AnimationClip m_animClip[enAnimationClip_num];				
	EnState m_state = enState_Idle_Run;
	CVector3 m_oldpos = { 30.0f,100.0f,1500.0f };               //鬼の初期位置
	CVector3 m_position = { 30.0f,100.0f,1500.0f };				//鬼の座標
	CVector3 m_scale = { 10.0f,10.0f,10.0f };					//鬼のスケール
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//移動速度
	Player* m_player;											//プレイヤークラスのポインタ
	//自機の角度　初期は180度
	float m_degree = 180.0f;                                    //ユニティちゃんの向いてる角度
	float m_radian = 0;                                         //上記をラジアン単位に直したもの
	CQuaternion m_rotation;
	int m_timer;												//攻撃のクールタイムのためにフレーム数を数える
	//プレイヤーの色々なステータス
	int m_level;                                                //レベル
	float m_MaxHP;                                              //最大HP
	float m_HP;                                                 //HP
	float m_MaxPP;                                              //最大PP
	float m_PP;                                                 //PP
	float m_Attack;                                             //攻撃力
	float m_Defense;                                            //防御力
};

