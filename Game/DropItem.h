#pragma once
class Player;
class Equipment;
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
	//����ł���Ɛݒ�
	void SetisWeapon()
	{
		m_isweapon = true;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position;                                        //���W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	CQuaternion m_rotation=CQuaternion::Identity();             //�N�I���e�[�V����
	int m_state;                                                //�h���b�v�i�̔ԍ�
	Player* m_player;                                           //�v���C���[�N���X�̃|�C���^
	Equipment* m_equipment = nullptr;
	int m_rarity;												//����̃��A���e�B
	int m_number;												//����̃��A���e�B�̒��̔ԍ�
	int m_meseta;												//�����^�̊z
	bool m_isweapon = false;									//���g�����킩�ǂ���
	bool m_issetweapon = false;
	static const float m_height;								//�h���b�v����+����y���W
	static const float m_height_weapon;							//�h���b�v����+����y���W(����)
	float m_degree = 0.0f;
	const float m_sevolume = 2.0f;
};

