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
	//回転をセット
	void SetRotation(const CQuaternion& qRot)
	{
		m_rotation = qRot;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position = { 0.0f,0.0f,0.0f };                     //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	CQuaternion m_rotation;										//回転
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
};

