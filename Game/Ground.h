#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
//ステージの床とか壁とかを生成するクラスです
class Ground : public IGameObject
{
public:
	Ground();
	~Ground();
	bool Start();
	void Update();
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
private:

	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position;                                        //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	CQuaternion m_rotation;                                     //クオンテーション
	PhysicsStaticObject m_staticobject;                         //静的オブジェクト
	int m_stage = 0;                                            //ステージ情報
};

