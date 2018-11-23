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
	//�A�C�e���̃��A�x��ݒ�
	void SetState(const int& state)
	{
		m_state = state;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position;                                        //���W
	CVector3 m_scale = { 0.5f,0.5f,0.5f };                      //�傫��
	CQuaternion m_rotation;                                     //�N�I���e�[�V����
	int m_state;                                               //�h���b�v�i�̔ԍ�
	Player* m_player;                                           //�v���C���[�N���X�̃|�C���^
};

