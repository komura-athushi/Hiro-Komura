#pragma once
#include "Weapon.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Player;
class Game;
class Skeleton2:public IEnemy
{
public:
	Skeleton2();
	~Skeleton2();
	bool Start() override;
	void Update() override;
	void Chase();												//追跡
	void AnimationController();									//アニメーションの再生
	void Damage();												//ダメージを受けた時のアクション
	void Turn();												//キャラクターの向きを計算
	void Dead();												//エネミーが死んだときの処理
	//アニメーションイベント
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	void SetPlayer(Player* player)								//プレイヤーのポイントをセット
	{
		m_player = player;
	}
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//回転を設定
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	void SetGame(Game* game)
	{
		m_game = game;
	}
	void SetOldPosition(const CVector3& pos)
	{
		m_oldpos = pos;
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
	CVector3 m_scale = { 14.0f,14.0f,14.0f };					//鬼のスケール
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//移動速度
	CVector3 m_heikou = { 0.0f,0.0f,0.0f };                     //鬼の向いている方向に平行なベクトル
	Player* m_player;											//プレイヤークラスのポインタ
	//自機の角度　初期は180度
	float m_degree = 180.0f;                                    //ユニティちゃんの向いてる角度
	float m_radian = 0;                                         //上記をラジアン単位に直したもの
	CQuaternion m_rotation;                                     //クォータニオン
	Game* m_game;
	int m_timer = 0;											//攻撃のクールタイムのためにフレーム数を数える
	//コリジョンとか
	const float m_r = 110.0f;                                    //コリジョンの半径
	const float m_staticr = 85.0f;
	const float m_collisionheight = 85.0f;                      //コリジョンをm_positionからどれだけ上にあげるか
	const float m_attackr = 110.0f;                              //攻撃したときに発生させるコリジョンの半径
	//Oniの色々なステータス
	static const int m_MaxHP = 1200;                             //最大HP
	static const int m_Attack = 330;                               //攻撃力
	static const int m_EXP = 2450;                                //経験値
	//ヘッダーファイルでは宣言だけ、定義はcppファイルに書いてください
	static const int m_dropChances[];                           //エネミーのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];					//エネミーのドロップする素材の確率
	static const int m_meseta = 200;							//ドロップするメセタの大体の額
	bool m_gekiha = false;                                      //deleteするかどうか
};

