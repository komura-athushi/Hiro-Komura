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
	void Chase();												//追跡
	void Turn();												//キャラクターの向きを計算
	void AnimationController();									//アニメーションの再生
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
	void SetStage1(Stage1* stage1)
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
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_run,
		enAnimationClip_attack1,
		enAnimationClip_aria,
		enAnimationClip_aria2,
		enAnimationClip_death,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Attack1,
		enState_Aria,
		enState_Aria2,
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
	bool m_gekiha = false;                                      //deleteするかどうか
	const int m_attackfire = 50;								//ファイヤーの攻撃力
	const float m_attackr = 80.0f;								//攻撃時に発生させるコリジョンの大きさ
	const int m_attack1 = 500;
};

