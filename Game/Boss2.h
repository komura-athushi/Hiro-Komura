#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Stage1;
class Player;
class Boss2 : public IEnemy
{
public:
	Boss2();
	~Boss2();
	bool Start() override;
	void Update() override;
	//ボスの行動をチェンジ
	void ChangeBehavior();									
	//追跡
	void Chase();											
	//キャラクターの向きを計算
	void Turn();											
	//アニメーションの再生
	void AnimationController();								
	//ドラゴンが死んだときの処理
	void Dead();											
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
	void SetStage1(Stage1* stage1)
	{
		m_stage1 = stage1;
	}
	void SetOldPosition(const CVector3 pos)
	{
		m_oldpos = pos;
	}
	//行動を開始したかどうか
	bool GetisStart() const
	{
		return m_start;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_run,
		enAnimationClip_aria,
		enAnimationClip_aria2,
		enAnimationClip_aria3,
		enAnimationClip_death,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Aria,											//ファイアアローばら撒き
		enState_Aria2,											//かきう
		enState_Aria3,											//エアルバースト
		enState_Death,
	};
	EnState m_state = enState_Idle;								//アニメーション分岐
	AnimationClip m_animClip[enAnimationClip_num];
	CVector3 m_oldpos = { 1000.0f,0.0f,-1000.0f };				//ドラゴンの初期位置
	CVector3 m_position = { 1000.0f,0.0f,-1000.0f };			//ドラゴンの座標
	//スケールは100.0f
	CVector3 m_scale = { 80.0f,80.0f,80.0f };				//ドラゴンのスケール
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//移動速度
	CVector3 m_heikou = { 0.0f,0.0f,0.0f };                     //ドラゴンの向いている方向に平行なベクトル
	float m_enemyspeed = 2.5f;									//ドラゴンの移動の倍率
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//ユニティちゃんの向きと平行なベクトル
	Player* m_player;											//プレイヤークラスのポインタ
	CFont m_font;												//文字表示クラス
	bool m_disp = false;										//ダメ表示するかどうか
	//自機の角度　初期は180度
	float m_degree = 180.0f;                                    //ユニティちゃんの向いてる角度
	float m_radian = 0;                                         //上記をラジアン単位に直したもの
	CQuaternion m_rotation;
	Stage1* m_stage1;
	float m_r = 180.0f;                                         //コリジョンの半径
	const float m_collisionheight = 150.0f;						//コリジョンをm_positionからどれだけ上にあげるか
	//Bossの色々なステータス
	static const int m_MaxHP = 25000;                             //最大HP
	static const int m_Attack1 = 20;							//ひっかきの攻撃力
	static const int m_Attack2 = 30;							//プレスの攻撃力
	static const int m_EXP = 50000;                               //経験値
	static const int m_dropChances[];				            //ドラゴンのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	bool m_isanger = false;										//HP半分以下になると攻撃が激しくなる
	bool m_gekiha = false;                                      //deleteするかどうか
	const int m_attackfire = 50;								//ファイヤーの攻撃力
	const float m_attackr = 170.0f;								//攻撃時に発生させるコリジョンの大きさ
	const int m_AttackEB = 600;
	const int m_AttackFIRE = 300;
	const int m_AttackEF = 400;
	const CVector3 m_ariascale = CVector3::One() * 40.0f;
	const int m_firenumber = 15, m_firenumberanger = 20;
	const float m_firespeed = 0.5f, m_firespeedanger = 0.7f;
	const float m_fireheight = 130.0f;
	const CVector3 m_firescale = CVector3::One() * 1.7f, m_firescaleanger = CVector3::One() * 2.3f;
	const float m_playerheight = 40.0f;
	const int m_enemyfirenumber = 4, m_enemyfirenumberanger = 6;
	const float m_plusdegree = 22.5, m_plusdegreeanger = 17.5f;
	const float m_enemyfirespeed = 0.8f;
	const float m_enemyfireheight = 60.0f;
	float m_timer = 0.0f;
	const float m_idletime = 1.5f, m_idletimeanger = 1.0f;
	const float m_movetime = 5.0f, m_movetimeanger = 4.0f;
	bool m_start = false;
	const float m_startdistance = 2300.0f * 2300.0f;
	CVector3 m_bossdirection = CVector3::Zero();
};

