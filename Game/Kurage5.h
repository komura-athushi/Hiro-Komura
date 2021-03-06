#pragma once
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Player;
class Game;
//ステージ2の大き目のクラゲ
class Kurage5 :public IEnemy
{
public:
	Kurage5();
	~Kurage5();
	bool Start() override;
	void Update() override;
	//移動
	void Chase();
	//攻撃
	void Attack();
	//詠唱
	void Aria();
	//攻撃に転ずる 
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
	CVector3 m_protposition = CVector3::Zero();					//初期に居た座標
	const float m_r = 110.0f;                                   //コリジョンの半径
	const float m_collisionheight = 80.0f;                      //コリジョンをm_positionからどれだけ上にあげるか
	//クラゲの色々なステータス
	static const int m_MaxHP = 2000;                            //最大HP
	static const int m_Attack = 450;                            //攻撃力
	static const int m_EXP = 4790;                              //経験値
	//ヘッダーファイルでは宣言だけ、定義はcppファイルに書いてください
	static const int m_dropChances[];                           //エネミーのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];					//エネミーのドロップする素材の確率
	static const int m_meseta = 600;							//ドロップするメセタの大体の額
	bool m_gekiha = false;                                      //deleteするかどうか
	Player* m_player = nullptr;											//プレイヤークラスのポインタ
	Game* m_game = nullptr;												
	//行動パターン
	enum State {
		enState_Chase,											//移動	
		enState_Pose,											//待機
		enState_Attack,											//攻撃
	};
	State m_state = enState_Pose;
	const float m_chasedistance = 1500.0f * 1500.0f;
	const float m_attackdistance = 1200.0f * 1200.0f;
	const float m_magicspeed = 0.4f;
	bool m_isaria = false;
	const float m_frame = 40.0f;
	const float m_movespeedmultiply = 3.5f;
	float m_dethtimer = 0.0f;
	const int m_dethtime = 5;
	float m_chasetimer = 0.0f;
	const int m_chasetime = 50;
	float m_stoptimer = 0.0f;
	const int m_stoptime = 80;
	float m_movetimer = 0.0f;
	const int m_movetime = 200;
	float m_attacktimer = 0.0f;
	const int m_ariatime = 30;
	const int m_attacktime = 70;
	CVector3 m_castscale = { 20.0f,20.0f,20.0f };
};
