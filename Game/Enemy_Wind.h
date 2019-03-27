#pragma once
class Enemy_Wind:IGameObject
{
public:
	Enemy_Wind();
	~Enemy_Wind();
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
	//�t�@�C���[�̍U���͂�ݒ�
	void SetAttack(const int& attack)
	{
		m_attack = attack;
	}
	//�����@�̑傫����ύX
	void SetScale(const float& scale)
	{
		m_scale *= scale;
		m_attack3r *= scale;
	}
private:
	GameObj::Suicider::CEffekseer* m_effect = nullptr;			//�G�t�F�N�g
	CVector3 m_position = CVector3::Zero();						//�e�̍��W
	CQuaternion m_rotation;										//��]
	CVector3 m_scale = { 24.0f,24.0f,24.0f };				    //�e�̑傫��
	CVector3 m_moveSpeed = { 0.0f,0.0f,0.0f };					//�ړ����x�B
	int m_damage = 0;											//�ڐG�����ۂɗ^����_���[�W
	const float m_frame = 100.0f;
	//�R���W�����֌W
	SuicideObj::CCollisionObj* m_attackCol;						//�R���W����
	float m_attack3r = 140.0f;									//�U�������Ƃ��ɔ���������R���W�����̔��a
	const float m_collisionheight = 20.0f;						//�R���W�������G�t�F�N�g������������
	int m_attack = 30;											//�t�@�C���[�̍U���́A�f�t�H���g��30
	float m_timer = 0.0f;										//�^�C�}�[
	const float m_time = 40.0f;									//�폜����^�C�~���O
	bool m_hitplayer = false;									//�v���C���[�ɓ����������ǂ���
};

