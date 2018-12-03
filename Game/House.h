#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class House:public IGameObject
{
public:
	House();
	~House();
	bool Start();
	void Update();
	//座標をセット
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position = { 0.0f,0.0f,0.0f };                     //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
};

