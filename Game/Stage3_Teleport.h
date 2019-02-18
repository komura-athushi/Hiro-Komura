#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Stage3_Teleport:IGameObject
{
public:
	Stage3_Teleport();
	~Stage3_Teleport();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	GameObj::Suicider::CEffekseer* m_effect;		//エフェクト
	const float m_frame = 40.0f;
	CVector3 m_position;                                        //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	CQuaternion m_rotation;                                     //クオンテーション
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
};

