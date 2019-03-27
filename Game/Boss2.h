#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Stage1;
class Player;
class BossAttack;
class Boss2 : public IEnemy
{
public:
	Boss2();
	~Boss2();
	bool Start() override;
	void Update() override;
	void Attack();       										//攻撃
	void Chase();												//追跡
	void Damage();												//ダメージを受けた時のアクション
	void Turn();												//キャラクターの向きを計算
	void AnimationController();									//アニメーションの再生
	void Dead();												//ドラゴンが死んだときの処理
	//アニメーションイベント
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

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
	void SetStage1(Stage1* stage1)
	{
		m_stage1 = stage1;
	}
	void SetOldPosition(const CVector3 pos)
	{
		m_oldpos = pos;
	}
	bool GetCount() const
	{
		return m_fireend;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_run,
		enAnimationClip_hikkaki,
		enAnimationClip_fire,
		enAnimationClip_press,
		enAnimationClip_damage,
		enAnimationClip_death,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle_Run,
		enState_Hikkaki,
		enState_Fire,
		enState_Press,
		enState_Damage,
		enState_Dead,
	};
	EnState m_state = enState_Idle_Run;
	AnimationClip m_animClip[enAnimationClip_num];
	CVector3 m_oldpos = { 1000.0f,0.0f,-1000.0f };				//ドラゴンの初期位置
	CVector3 m_position = { 1000.0f,0.0f,-1000.0f };			//ドラゴンの座標
	//スケールは100.0f
	CVector3 m_scale = { 100.0f,100.0f,100.0f };				//ドラゴンのスケール
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//移動速度
	CVector3 m_heikou = { 0.0f,0.0f,0.0f };                     //ドラゴンの向いている方向に平行なベクトル
	float m_enemyspeed = 2.5f;									//ドラゴンの移動の倍率
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//ユニティちゃんの向きと平行なベクトル
	Player* m_player;											//プレイヤークラスのポインタ
	BossAttack* m_bossattack;									//BossAttackクラスのポインタ
	CFont m_font;												//文字表示クラス
	bool m_disp = false;										//ダメ表示するかどうか
	//自機の角度　初期は180度
	float m_degree = 180.0f;                                    //ユニティちゃんの向いてる角度
	float m_radian = 0;                                         //上記をラジアン単位に直したもの
	CQuaternion m_rotation;
	Stage1* m_stage1;
	int m_timer = 0;											//攻撃のクールタイムのためにフレーム数を数える
	int m_atk3timer = 0;										//攻撃3のクールタイムのためにフレーム数を数える
	int m_atk3count = 0;
	int m_cooltime = 400;										//攻撃が終わった後のクールタイム
	int m_atk3cooltime = 300;									//攻撃3が終わった後のクールタイム
	int m_posttiming = 30;										//攻撃が来る前の注意のタイミング
	int m_atktype = 0;											//攻撃の種類
	float m_r = 150.0f;                                         //コリジョンの半径
	const float m_attackr = 130.0f;                             //ひっかきしたときに発生させるコリジョンの半径
	const float m_attack2r = 350.0f;                            //プレスしたときに発生させるコリジョンの半径
	float m_collisionheight = 70.0f;							//コリジョンをm_positionからどれだけ上にあげるか
	int m_bonehead;                                             //頭のboneの番号
	//Bossの色々なステータス
	static const int m_MaxHP = 900;                             //最大HP
	static const int m_Attack1 = 20;							//ひっかきの攻撃力
	static const int m_Attack2 = 30;							//プレスの攻撃力
	static const int m_EXP = 500;                               //経験値
	static const int m_dropChances[];				            //ドラゴンのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	bool m_gekiha = false;                                      //deleteするかどうか
	//ファイヤー関連
	bool m_fireend=false;										//ファイヤーが終わったかどうか
	bool m_ischase = true;										//プレイヤーを追尾しているかどうか
	const int m_attackfire = 50;								//ファイヤーの攻撃力
};

