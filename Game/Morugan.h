#pragma once
class Player;
class Morugan:public IGameObject
{
public:
	Morugan();
	~Morugan();
	bool Start() override;
	void Update() override;
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
	GameObj::Suicider::CEffekseer* m_effect = nullptr;			//�G�t�F�N�g
	CVector3 m_position = CVector3::Zero();						//���W
	CQuaternion m_rotation;										//��]
	const CVector3 m_scale = { 6.0f,6.0f,5.5f };				//�G�t�F�N�g�̑傫��
	int m_damage = 0;											//�ڐG�������ɗ^����_���[�W
	const float m_frame = 40.0f;
	const float m_length = 1700.0f;								//�����K���̒���
	const float m_time = 240.0f;								//�r�[�������̎���
 	float m_timer = 0.0f;										//�^�C�}�[
	Player* m_player;
	const float m_r = 10.0f;									//���񂿂��̔��a
};

