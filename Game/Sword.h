#pragma once
//�v���C���[���������Ă��镐��̃f�[�^�ł�
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
	//�傫����ݒ�
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//����̔ԍ���ݒ�
	void SetSwordId(const int& id) 
	{
		m_SwordId2 = id;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position = { 0.0f,0.0f,0.0f };                   //���W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	CQuaternion m_qRot;                                         //�N�H�[�^�j�I��
	int m_SwordId;                                              //����̔ԍ�
	int m_SwordId2;                                             //�؂�ւ��\��̕���̔ԍ�
	bool m_delete = true;                                       //�����؂�ւ���O�ɑ������Ă��镐����폜���Ă��邩�ǂ���
	bool m_switch = false;
};

