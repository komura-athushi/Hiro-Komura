#pragma once
class BossAttack : public IGameObject
{
public:
	BossAttack();
	~BossAttack();
	bool Start() override;
	void Update() override;
	void Attack1();
	void Attack2();
	void Attack3();
	//�e�̍��W���Z�b�g
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
	//�U���̃i���o�[���擾
	void SetNumber(const int& number)
	{
		m_number = number;
	}
private:
	GameObj::CSkinModelRender* m_bullet1skinModel = nullptr;		//1�X�L�����f�������_���[�B
	GameObj::CSkinModelRender* m_bullet2skinModel = nullptr;		//2�X�L�����f�������_���[�B
	GameObj::CSkinModelRender* m_bullet3skinModel = nullptr;		//3�X�L�����f�������_���[�B
	CVector3 m_position = { 0.0f,0.0f,0.0f };	//���W�B
	CVector3 m_moveSpeed = { 0.0f,0.0f,0.0f };	//�ړ����x�B
	CVector3 m_bulletpos = { 0.0f,0.0f,0.0f };
	CVector3 m_scale = { 20.0f,20.0f,20.0f };						//�e�̃X�P�[��
	CQuaternion m_rotation;											//�N�H�[�^�j�I��
	int m_timer = 0;
	int m_number = 0;
	//const wchar_t m_name[] = L"bullet";
};

