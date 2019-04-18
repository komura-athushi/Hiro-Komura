#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
//プレイヤーがこのオブジェクトに近づくとステージ1に移動します
class Stage2_Teleport :public IGameObject
{
public:
	Stage2_Teleport();
	~Stage2_Teleport();
	bool Start() override;
	void Update() override;
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
	GameObj::Suicider::CEffekseer* m_effect = nullptr;			//エフェクト
	const float m_frame = 40.0f;
	CVector3 m_position = CVector3::Zero();                     //座標
	CVector3 m_scale = CVector3::One();                         //大きさ
	CQuaternion m_rotation;                                     //クオンテーション
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
};

