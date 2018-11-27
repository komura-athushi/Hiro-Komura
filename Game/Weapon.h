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
	//�R�s�[�R���X�g���N�^
	Weapon(const Weapon& wpn);
	~Weapon();
	bool Start();
	void Update();
	//����̔ԍ����擾
	int GetId() const
	{
		return m_id;
	}
	//����̖��O���擾
	std::string GetName() const
	{
		return m_name;
	}
	//����̃��A���e�B���擾
	int GetRarity() const
	{
		return m_rarity;
	}
	//����̕����U���͂��擾
	int GetAtk() const
	{
		return m_atk;
	}
	//����̖��@�U���͂��擾
	int GetMatk() const
	{
		return m_matk;
	}
	//����̖��@�̔ԍ����擾
	int GetMagicId() const
	{
		return m_magicid;
	}
	static const int m_HighestRarity = 4;     //����̍ō����A���e�B
private:
	int m_id;								//����̔ԍ�
	std::string m_name;						//����̖��O
	int m_rarity;							//����̃��A���e�B
	int m_atk;								//����̕����U����
	int m_matk;								//����̖��@�U����
	int m_magicid;							//����̖��@�̔ԍ�
};
/*
�b��I�ȃ\�[�h�̃��A���e�B�Ɣԍ��Ɩ��O
0
Sword                 0
1
FireSword             1
IceSword              2
WindSword             3
2 
GreatSword            4
3
BlueLightSword        5
*/

