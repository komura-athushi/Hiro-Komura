#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
//ステージの床とか壁とかを生成するクラスです
class Ground : public IGameObject
{
public:
	Ground();
	~Ground();
	bool Start() override;
	void Update() override;
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//ステージの情報を設定
	void SetStage(const int& stage)
	{
		m_stage = stage;
	}
	//回転を設定
	void SetRot(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	//大きさを設定
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	GameObj::CSkinModelRender* m_skinModelRender2 = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position;                                        //座標
	CVector3 m_scale = CVector3::One();                         //大きさ
	CQuaternion m_rotation = CQuaternion::Identity();           //クオンテーション
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	PhysicsStaticObject m_staticobject2;                        //静的オブジェクト
	int m_stage = 0;											//ステージ情報
};																

