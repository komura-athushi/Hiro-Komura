#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Boss;
//壁
class Wall:public IGameObject
{
public:
	Wall();
	~Wall();
	bool Start() override;
	void Update() override;
	//座標をセット
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position = { 0.0f,0.0f,0.0f };                   //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	bool m_iscreatstaticobject = false;							//静的オブジェクトを生成したかどうか			
	Boss* m_boss = nullptr;										//ボス
};

