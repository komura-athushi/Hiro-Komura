#pragma once
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Player;
//プレイヤーに近づいて攻撃してくる一番弱い緑のクラゲ
class Kurage:public IEnemy
{
public:
	Kurage();
	~Kurage();
	bool Start() override;
	void Update() override;
	//移動
	void Move();
	//攻撃
	void Attack();
	//詠唱
	void Aria();
	//攻撃に移行？
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
	//大きさを設定
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
	CVector3 m_protposition = CVector3::Zero();					//最初に居た座標
	const float m_r = 60.0f;                                    //コリジョンの半径
	const float m_collisionheight = 40.0f;                      //コリジョンをm_positionからどれだけ上にあげるか
	//クラゲの色々なステータス
	static const int m_MaxHP = 150;                             //最大HP
	static const int m_Attack = 20;                             //攻撃力
	static const int m_EXP = 20;                                //経験値
	//ヘッダーファイルでは宣言だけ、定義はcppファイルに書いてください
	static const int m_dropChances[];                           //エネミーのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];					//エネミーのドロップする素材の確率
	static const int m_meseta = 30;								//ドロップするメセタの大体の額
	bool m_gekiha = false;                                      //deleteするかどうか
	Player* m_player;											//プレイヤークラスのポインタ
	//行動パターン
	enum State {
		enState_Chase,											//移動
		enState_Pose,											//待機
		enState_Attack,											//攻撃
	};
	bool m_isaria = false;										//詠唱したかどうか
	const float m_chasedistance = 1200.0f * 1200.0f;			//プレイヤーとの距離が一定以下になれば移動する
	const float m_attackdistance = 130.0f * 130.0f;				//プレイヤーとの距離が一定以下になれば攻撃する
	State m_state = enState_Pose;								//ステート
	const float m_frame = 40.0f;
	const float m_movespeedmultiply = 7.0f;						//移動速度
	float m_dethtimer = 0.0f;									//倒されるまでちょっと時間あける
	const int m_dethtime = 5;
	float m_chasetimer = 0.0f;									
	const int m_chasetime = 30;
	float m_stoptimer = 0.0f;
	const int m_stoptime = 20;
	float m_movetimer = 0.0f;
	const int m_movetime = 130;
	float m_attacktimer = 0.0f;
	const int m_ariatime = 20;
	const int m_attacktime = 60;
};

