#pragma once
class Player;
//�G�l�~�[���h���b�v����f�ނ̃N���X�ł�
class DropMaterial:public IGameObject
{
public:
	DropMaterial();
	~DropMaterial();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3 pos)
	{
		m_position = pos;
	}
	//���A���e�B�̒��̔ԍ���ݒ�
	void SetNumber(const int& number)
	{
		m_number = number;
	}
	//���A���e�B��ݒ�
	void SetRarity(const int& rarity)
	{
		m_rarity = rarity;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position;                                        //���W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	CQuaternion m_rotation;                                     //�N�I���e�[�V����
	int m_state;                                                //�h���b�v�i�̔ԍ�
	Player* m_player;                                           //�v���C���[�N���X�̃|�C���^
	int m_rarity;												//�f�ނ̃��A���e�B
	int m_number;												//�f�ނ̃��A���e�B�̒��̔ԍ�
	float m_degree = 0.0f;
	const float m_sevolume = 1.7f;
};

