#pragma once
//����f�[�^�̃N���X�ł�
class Weapon:public IGameObject
{
public:
	/*!
	@brief	Weapon�̃R���X�g���N�^
	*int id;							//����̔ԍ�
	*std::string name;					//����̖��O
	*int rarity;						//����̃��A���e�B
	*int atk;							//����̕����U����
	*int matk;							//����̖��@�U����
	*int mnumber;						//����̖��@�̔ԍ�
	*/
	Weapon(const int& id,const std::string& name,const int& rarity,const int& atk,const int& matk,const int& mnumber);
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

