#pragma once
class Enemy:public IGameObject
{
public:
	/*!
	@brief	Enemy�̃R���X�g���N�^
	*int id;							//�G�l�~�[�̔ԍ�
	*std::string name;					//�G�l�~�[�̖��O
	*int hp;						//�G�l�~�[��HP
	*int atk;							//�G�l�~�[�̍U����
	*int exp;							//�G�l�~�[���j���̌o���l
	*int dropchances[4];						//�G�l�~�[�̃h���b�v����A�C�e��
	*/
	Enemy(const int& id,const std::string& name,const int& hp,const int& atk,const int& exp,const float dropchances[4]);
	//�R�s�[�R���X�g���N�^
	Enemy(const Enemy& enemy);
	~Enemy();
	bool Start();
	void Update();
private:
	int m_id;								//�G�l�~�[�̔ԍ�
	std::string m_name;						//�G�l�~�[�̖��O
	int m_hp;								//�G�l�~�[��HP
	int m_atk;								//�G�l�~�[�̍U����
	int m_exp;								//�G�l�~�[���j���̌o���l
	float m_dropChances[4];					//�G�l�~�[�̃h���b�v����A�C�e��
};

