#pragma once
class Boss2;
class Boss2_Fire : public IGameObject
{
public:
	Boss2_Fire();
	~Boss2_Fire();
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
	//�e�̑��x���Z�b�g
	void SetMoveSpeed(const CVector3& pos)
	{
		m_moveSpeed = pos;
	}
	//�e�̍��W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	GameObj::Suicider::CEffekseer* m_effect = nullptr;
	CVector3 m_position = CVector3::Zero();						//�e�̍��W
	CQuaternion m_rotation;
	const CVector3 m_scale = { 30.0f,30.0f,30.0f };				//�e�̑傫��
	CVector3 m_moveSpeed = { 0.0f,0.0f,0.0f };					//�ړ����x�B
	int m_damage = 0;
	const float m_frame = 40.0f;
	Boss2* m_boss2;												//Boss2�N���X�̃|�C���^
};