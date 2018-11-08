#pragma once
#include "DemolisherWeapon/physics/character/CCharacterController.h"
//プレイヤーです
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	//キャラクターの向きを計算
	void Turn();
	//キャラクターのアニメーションを設定
	void AnimationController();
	//キャラクターの移動を計算
	void Move();
	//プレイヤーの座標をセット
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//プレイヤーの座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//プレイヤーのHPを取得
	float GetHP() const
	{
		return m_HP;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_movespeed;                                       //移動速度
	CVector3 m_position = {0.0f,100.0f,00.0f};                  //ユニティちゃんの座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	//自機の角度　初期は180度
	float m_degree = 180.0f;                                    //ユニティちゃんの向いてる角度
	float m_radian = 0;                                         //上記をラジアン単位に直したもの
	//移動速度乗算
	const float m_multiply = 400.0f;                            //ユニティちゃんの移動速度を調整する
	CQuaternion m_rotation;                                     //クオンテーション
	CCharacterController m_charaCon;                            //キャラクターの当たり判定とか移動とか
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_KneelDown,
		enAnimationClip_Clear,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Jump,
		enState_Damage,
		enState_GameOver,
		enState_WaitStartGameClear,
		enState_GameClear,
	};
	AnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
	//プレイヤーの色々なステータス
	int m_level;                                                //レベル
	float m_MaxHP;                                              //最大HP
	float m_HP;                                                 //HP
	float m_MaxPP;                                              //最大PP
	float m_PP;                                                 //PP
	float m_Attack;                                             //攻撃力
	float m_Defense;                                            //防御力
};

