#pragma once
class Player;
//�G�l�~�[�̃h���b�v�A�C�e���̃N���X�ł�
class DropItem:public IGameObject
{
public:
	DropItem();
	~DropItem();
	bool Start();
	void Update();
	//�v���C���[�̃|�C���^��ݒ�
	void SetPlayer(Player* player)
	{
		m_player=player;
	}
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//����̃��A���e�B�̒��̔ԍ���ݒ�
	void SetState(const int& state)
	{
		m_state = state;
	}
	//����̃��A���e�B��ݒ�
	void SetRarity(int rare)
	{
		m_rarity = rare;
	}
	//���Z�^�̊z��ݒ�
	void SetMeseta(const int& meseta)
	{
		m_meseta = meseta;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position;                                        //���W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	CQuaternion m_rotation;                                     //�N�I���e�[�V����
	int m_state;                                                //�h���b�v�i�̔ԍ�
	Player* m_player;                                           //�v���C���[�N���X�̃|�C���^
	int m_rarity;												//����̃��A���e�B
	int m_number;												//����̃��A���e�B�̒��̔ԍ�
	int m_meseta = 0;
};

