#pragma once
class Player;
class Morugan:public IGameObject
{
public:
	Morugan();
	~Morugan();
	bool Start();
	void Update();
	//�_���[�W��ݒ�
	void SetDamage(const int& mattack, const float& damagerate)
	{
		m_damage = int(mattack*damagerate);
	}
	//��]��ݒ�
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	GameObj::Suicider::CEffekseer* m_effect = nullptr;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation;
	const CVector3 m_scale = { 7.0f,7.0f,7.0f };
	int m_damage = 0;
	const float m_frame = 40.0f;
	Player* m_player;
};

