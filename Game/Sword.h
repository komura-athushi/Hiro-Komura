#pragma once
class Sword:public IGameObject
{
public:
	Sword();
	~Sword();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//回転を設定
	void SetRot(const CQuaternion& rot)
	{
		m_qRot = rot;
	}
	//大きさを設定
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position = { 0.0f,0.0f,0.0f };                   //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	CQuaternion m_qRot;                                         //クォータニオン
};

