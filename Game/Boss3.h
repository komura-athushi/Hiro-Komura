#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Stage1;
class Player;
class Boss3 : public IEnemy
{
public:
	Boss3();
	~Boss3();
	bool Start() override;
	void Update() override;
	void Attack();       										//攻撃
	void Chase();												//追跡
	void Turn();												//キャラクターの向きを計算
	void AnimationController();									//アニメーションの再生
	void Damage();												//ダメージを受けた時のアクション
	void Dead();												//ドラゴンが死んだときの処理
	//アニメーションイベント
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	void SetPlayer(Player* player)								//プレイヤーのポイントをセット
	{
		m_player = player;
	}
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	void SetOldPosition(const CVector3 pos)
	{
		m_oldpos = pos;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle1,
		enAnimationClip_idle2,
		enAnimationClip_run,
		enAnimationClip_tuki,
		enAnimationClip_harai,
		enAnimationClip_nidan,
		enAnimationClip_bash,
		enAnimationClip_kaiten,
		enAnimationClip_damage,
		enAnimationClip_death,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle_Run,
		enState_tuki,
		enState_harai,
		enState_nidan,
		enState_bash,
		enState_kaiten,
		enState_Damage,
		enState_Dead,
	};
	EnState m_state = enState_Idle_Run;
	AnimationClip m_animClip[enAnimationClip_num];
	CVector3 m_oldpos = { 1000.0f,0.0f,-1000.0f };				//騎士の初期位置
	CVector3 m_position = { 1000.0f,0.0f,-1000.0f };			//騎士の座標
	//スケールは100.0f
	CVector3 m_scale = { 1.0f,1.0f,1.0f };						//騎士のスケール
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//移動速度
	//自機の角度　初期は180度
	float m_degree = 180.0f;                                    //騎士の向いてる角度
	float m_radian = 0;                                         //上記をラジアン単位に直したもの
	CQuaternion m_rotation;
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//騎士の向きと平行なベクトル
	int m_idlecount = 0;
	int m_timer = 0;											//待機モーションのクールタイムのためにフレーム数を数える
	int m_Ctimer = 0;											//二段突きの二手目のためにフレーム数を数える
	int m_cooltime = 500;
	Player* m_player;											//プレイヤークラスのポインタ
	bool m_ischase = true;										//プレイヤーを追尾しているかどうか
	//Bossの色々なステータス
	static const int m_MaxHP = 100;                             //最大HP
	static const int m_Attack =50;								//突きの攻撃力
	static const int m_EXP = 500;                               //経験値
	static const int m_dropChances[];				            //ドラゴンのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	bool m_gekiha = false;                                      //deleteするかどうか
	//コリジョン関係
	float m_collisionheight = 70.0f;							//コリジョンをm_positionからどれだけ上にあげるか
	CVector3 m_size = { 130.0f, 120.0f, 400.0f};				//突きのコリジョンの半径
	const float m_harai_r = 150.0f;								//はらいをしたときに発生させるコリジョンの半径
	//二段
//	const float m_harai_r = 150.0f;								//二段突きをしたときに発生させるコリジョンの半径
	bool deletefirst = false;									//二段突きの初撃を行ったかどうか
};

