#pragma once
class Enemy_Ice:public IGameObject
{
public:
	Enemy_Ice();
	~Enemy_Ice();
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
	//�e�̑��x��ω�������
	void SetSpeed(const float& speed)
	{
		m_speed = speed;
	}
	//�e�̍폜�����^�C�~���O��ω�������A�f�t�H���g��120
	void SetDeleteTime(const float& time)
	{
		m_time = time;
	}
private:
	GameObj::Suicider::CEffekseer* m_effect = nullptr;			//�G�t�F�N�g
	CVector3 m_position = CVector3::Zero();						//�e�̍��W
	CQuaternion m_rotation;										//�G�t�F�N�g�̉�]
	const CVector3 m_scale = { 24.0f,24.0f,24.0f };				//�e�̑傫��
	CVector3 m_moveSpeed = CVector3::Zero();					//�ړ����x�B
	float m_speed = 1.0f;							            //�e�̃X�s�[�h
	int m_damage = 0;											//�ڐG�����ۂɗ^����_���[�W
	const float m_frame = 60.0f;
	//�R���W�����֌W
	SuicideObj::CCollisionObj* m_attackCol = nullptr;			//�R���W����
	const float m_attack3r = 75.0f;                             //�U�������Ƃ��ɔ���������R���W�����̔��a
	int m_attack = 30;							                //�t�@�C���[�̍U���́A�f�t�H���g��30
	float m_timer = 0.0f;										//�^�C�}�[
	float m_time = 120.0f;										//�폜����^�C�~���O
	bool  m_hitplayer = false;									//�v���C���[�ɓ����������ǂ���			
};		

