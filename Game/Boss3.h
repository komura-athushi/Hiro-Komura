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
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
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
	float m_collisionheight = 70.0f;							//コリジョンをm_positionからどれだけ上にあげるか
	//Bossの色々なステータス
	static const int m_MaxHP = 900;                             //最大HP
	static const int m_Attack1 = 20;							//ひっかきの攻撃力
	static const int m_EXP = 500;                               //経験値
	static const int m_dropChances[];				            //ドラゴンのドロップするアイテム、[1]が10ならレア度1が10%でドロップするみたいな
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	bool m_gekiha = false;                                      //deleteするかどうか
};

