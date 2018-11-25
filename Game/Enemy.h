#pragma once
class Enemy:public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
private:
	int m_id;								//�G�l�~�[�̔ԍ�
	std::string m_name;						//�G�l�~�[�̖��O
	int m_hp;								//�G�l�~�[��HP
	int m_atk;								//�G�l�~�[�̍U����
	int m_exp;								//�G�l�~�[���j���̌o���l
	float m_dropChances[3];					//�G�l�~�[�̃h���b�v����A�C�e��
};

