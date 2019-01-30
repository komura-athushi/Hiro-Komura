#pragma once
//����f�[�^�̃N���X�ł�
class Weapon
{
public:
	Weapon() {}
	/*!
	@brief	Weapon�̃R���X�g���N�^
	*int id;							//����̔ԍ�
	*const wchar_t* name;				//����̖��O
	*int rarity;						//����̃��A���e�B
	*int atk;							//����̕����U����
	*int matk;							//����̖��@�U����
	*int mnumber;						//����̖��@�̔ԍ�
	*int meseta							//���p���̉��i
	*/
	Weapon(const int& id, const wchar_t* name,const int& rarity,const int& atk,const int& matk,const int& mnumber,int const& meseta);
	//�R�s�[�R���X�g���N�^
	Weapon(const Weapon& wpn);
	~Weapon();
	
	//����̔ԍ����擾
	int GetId() const
	{
		return m_id;
	}
	//����̖��O���擾
	const wchar_t* GetName() const
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
	//���p���i���擾
	int GetMeseta() const
	{
		return m_meseta;
	}
	static const int m_HighestRarity = 7;   //����̍ō����A���e�B
	static const int m_raritynumber[];      //���A���e�B���Ƃ̕���̎��
private:
	int m_id;								//����̔ԍ�
	const wchar_t* m_name;					//����̖��O
	int m_rarity;							//����̃��A���e�B
	int m_atk;								//����̕����U����
	int m_matk;								//����̖��@�U����
	int m_magicid;							//����̖��@�̔ԍ�
	int m_meseta;							//���p�����Ƃ��̉��i
};

/*
�b��I�ȃ\�[�h�̃��A���e�B�Ɣԍ��Ɩ��O
1
Sword                 0
2
FireSword             1
IceSword              2
WindSword             3
3 
GreatSword            4
4
BlueLightSword        5
5
BattleReadyBlade      6
6
AncientWarriorBlade   7
7
LegendalySword        8
*/

