#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Game;
class Player;
class Boss : public IEnemy
{
public:
	Boss();
	~Boss();
	bool Start() override;
	void Update() override;
	void Turn();												//キャラクターの向きを計算
	//パターン1
	void One();
	//パターン2
	void Two();
	//パターン3
	void Three();
	//マジックスフィア
	void MG();			
	//フリーズショット
	void FS();
	//エアルバースト
	void EB();
	//詠唱
	void Aria();
	void SetPlayer(Player* player)								//プレイヤーのポイントをセット
	{
		m_player = player;
	}
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	void SetStage1(Game* stage1)
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
	enum State {
		enState_One,						//一番目の行動パターン
		enState_Two,						//二番目の行動パターン
		enState_Three,						//三番目の行動パターン
	};
	State m_state = enState_One;
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	CVector3 m_oldpos = { 0.0f,0.0f,0.0f };						//ボスの初期位置
	CVector3 m_position = { 0.0f,0.0f,0.0f };					//ボスの座標
	CVector3 m_scale = { 1.5f,1.5f,1.5f };						//ボスのスケール
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//移動速度
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//ユニティちゃんの向きと平行なベクトル
	Player* m_player = nullptr;									//プレイヤークラスのポインタ
	CFont m_font;												//文字表示クラス
	//自機の角度　初期は180度
	float m_degree = 180.0f;                                    //ユニティちゃんの向いてる角度
	float m_radian = 0;                                         //上記をラジアン単位に直したもの
	CQuaternion m_rotation;
	Game* m_stage1 = nullptr;
	float m_r = 150.0f;                                         //コリジョンの半径
	const float m_height = 220.0f;                              //コリジョンをm_positionからどれだけ上にあげるか
	//Bossの色々なステータス
	static const int m_MaxHP = 5000;                            //最大HP
	static const int m_AttackMG = 75;							//マジスフィ
	static const int m_AttackFS = 90;							//フリーズショット
	static const int m_AttackEB = 185;							//エアリアルバースト
	static const int m_EXP = 5000;                              //経験値
	static const int m_dropChances[];				            //エネミーのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	float m_deathtimer = 0.0f;
	float m_timer = 0;
	enum Attack {
		enState_Move,
		enState_MG,
		enState_FS,
		enState_EB,
	};
	CVector3 m_magicdirection = CVector3::Zero();
	float m_timer2 = 0.0f;
	Attack m_attackstate = enState_MG;
	bool m_start = false;
	const float m_startdistance = 2000.0f * 2000.0f;
	const float m_MGariatimer = 1.5f;							//マジックスフィアの詠唱時間
	const float m_FSariatimer = 1.0f;							//フリーズショットとエアルバーストの詠唱タイム
	bool m_isaria = false;										//詠唱したかどうか
	bool m_ismagic = false;
	const float m_posetime1 = 0.5f, m_posetime2 = 1.0f, m_posetime3 = 3.5f;
	int m_fscounter = 0,m_mgcounter = 0;                        //魔法撃った個数
	const int m_fsnumber = 5;
	const float m_plusdegree = 22.5f;
	const CVector3 m_ariascale = { 25.0f,25.0f,25.0f };
	const float m_icedeletetime = 300.0f;
	const float m_timemultiply = 1.3f;
	int m_countfs = 0,m_countmg=0;								//魔法を撃った回数
	const float m_attackchanceEB = 400.0f * 400.0f;
	const float m_speedmultiply = 600.0f;
	bool m_isEB = false;										//EBを撃っていいかどうか
	CVector3 m_EBposition = CVector3::Zero();
	bool m_isdecisionposition = false;
	CVector3 m_playerposition = CVector3::Zero();
	const float m_y = -50.0f;
	const float m_MGdeletetime = 180.0f;

};

