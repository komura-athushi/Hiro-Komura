#pragma once
class Player;
class Morugan:public IGameObject
{
public:
	Morugan();
	~Morugan();
	bool Start();
	void Update();
	//ダメージを設定
	void SetDamage(const int& mattack, const float& damagerate)
	{
		m_damage = int(mattack*damagerate);
	}
	//回転を設定
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	GameObj::Suicider::CEffekseer* m_effect = nullptr;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation;
	const CVector3 m_scale = { 7.0f,7.0f,4.0f };
	int m_damage = 0;
	const float m_frame = 40.0f;
	const float m_length = 1700.0f;								//モルガンの長さ
	const float m_time = 240.0f;								//ビーム発生の時間
 	float m_timer = 0.0f;
	Player* m_player;
	const float m_r = 10.0f;									//えんちうの半径
};

