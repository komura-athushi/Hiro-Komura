#pragma once
class Sword:public IGameObject
{
public:
	Sword();
	~Sword();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//��]��ݒ�
	void SetRot(const CQuaternion& rot)
	{
		m_qRot = rot;
	}
	//�ړ����x��ݒ�
	void SetMovespeed(const CVector3& move)
	{
		m_movespeed = move;
	}
	//�傫����ݒ�
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position = { 0.0f,0.0f,0.0f };                   //���W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	CVector3 m_movespeed = { 0.0f,0.0f,0.0f };                  //�ړ����x
	CQuaternion m_qRot;                                         //�N�H�[�^�j�I��
};

