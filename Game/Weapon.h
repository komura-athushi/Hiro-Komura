#pragma once
//����f�[�^�̃N���X�ł�
class Weapon:public IGameObject
{
public:
	Weapon();
	~Weapon();
	bool Start();
	void Update();
private:
	int m_id;							//����̔ԍ�
	std::string m_name;					//����̖��O
	int m_rarity;						//����̃��A���e�B
	int m_atk;							//����̕����U����
	int m_matk;							//����̖��@�U����
	int m_magicid;						//����̖��@�̔ԍ�
};

