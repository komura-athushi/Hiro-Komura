#pragma once
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Player;
class Game;
//大き目のクラゲ
class Kurage5 :public IEnemy
{
public:
	Kurage5();
	~Kurage5();
	bool Start();
	void Update();
	void Chase();
	void Attack();
	void Aria();
	void ChangeAttack();
	void SetPlayer(Player* player)								//プレイヤーのポイントをセット
	{
		m_player = player;
	}
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	void SetGame(Game* game)
	{
		m_game = game;
	}
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	CVector3 m_position = CVector3::Zero();				        //鬼の座標
	CVector3 m_scale = CVector3::One();					        //鬼のスケール
	CVector3 m_movespeed = CVector3::Zero();					//移動速度
	CVector3 m_protposition = CVector3::Zero();
	const float m_r = 110.0f;                                    //コリジョンの半径
	const float m_collisionheight = 80.0f;                      //コリジョンをm_positionからどれだけ上にあげるか
	//クラゲの色々なステータス
	static const int m_MaxHP = 2000;                             //最大HP
	static const int m_Attack = 450;                             //攻撃力
	static const int m_EXP = 2790;                               //経験値
	//ヘッダーファイルでは宣言だけ、定義はcppファイルに書いてください
	static const int m_dropChances[];                           //エネミーのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];					//エネミーのドロップする素材の確率
	static const int m_meseta = 80;								//ドロップするメセタの大体の額
	bool m_gekiha = false;                                      //deleteするかどうか
	Player* m_player;											//プレイヤークラスのポインタ
	Game* m_game;
	enum State {
		enState_Chase,
		enState_Pose,
		enState_Attack,											//近接攻撃
		enState_Attack2,										//遠距離攻撃
	};
	bool m_isaria = false;
	const float m_chasedistance = 1400.0f * 1400.0f;
	const float m_attackdistance = 400.0f * 400.0f;
	const float m_attackdistance2 = 1000.0f * 1000.0f;
	State m_state = enState_Pose;
	const float m_frame = 40.0f;
	const float m_movespeedmultiply = 8.0f;
	float m_dethtimer = 0.0f;
	const int m_dethtime = 5;
	float m_chasetimer = 0.0f;
	const int m_chasetime = 30;
	float m_stoptimer = 0.0f;
	const int m_stoptime = 20;
	float m_movetimer = 0.0f;
	const int m_movetime = 130;
	float m_attacktimer = 0.0f;
	const int m_ariatime = 30;
	const int m_attacktime = 60;
	const int m_ariatime2 = 40;
	const int m_attacktime2 = 70;
	CVector3 m_castscale = { 20.0f,20.0f,20.0f };
	const float m_windscale = 2.0f;
};
