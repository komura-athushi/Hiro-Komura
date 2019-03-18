#pragma once
class Ability
{
public:
	/*!
    @brief	Ability�̃R���X�g���N�^
    *int id;							�A�r���e�B�̔ԍ�
    *const wchar_t* name;				�A�r���e�B�̖��O
	*int group							�A�r���e�B�̏�������O���[�v
	*int weight							�A�r���e�B�̃E�F�C�g()
    *int power;						    �{����Ō���
    *int mpower;					    �{����@����
    *int hp;							�{����g�o
    *int pp;						    �{����o�o
    */
	Ability(const int& id, const wchar_t* name, const int& group, const int& weight, const int& power, const int& mpower, const int& hp, const int& pp);
	/*!
	@brief	Ability�̃R���X�g���N�^(Equipment�p)
	*int power;						    �{����Ō���
	*int mpower;					    �{����@����
	*int hp;							�{����g�o
	*int pp;						    �{����o�o
	*/
	Ability(const int& power, const int& mpower, const int& hp, const int& pp);
	//�R�s�[�R���X�g���N�^
	Ability(const Ability& ab);
	~Ability();
	//�ԍ����擾
	int GetId() const
	{
		return m_id;
	}
	//���O���擾
	const wchar_t* GetName() const
	{
		return m_abilityname;
	}
	//�Ō��͂��擾
	int GetPower() const
	{
		return m_power;
	}
	//�@���͂��擾
	int GetMpower() const
	{
		return m_mpower;
	}
	//hp���擾
	int GetHP() const
	{
		return m_hp;
	}
	//pp���擾
	int GetPP() const
	{
		return m_pp;
	}
	//�O���[�v���擾
	int GetGroup() const
	{
		return m_group;
	}
	//�E�F�C�g���擾
	int GetWeight() const
	{
		return m_weight;
	}
private:
	int m_id = 0;											//�A�r���e�B�̔ԍ�
	const wchar_t* m_abilityname = nullptr;					//�A�r���e�B�̖��O
	int m_power = 0;										//�Ō���
	int m_mpower = 0;										//�@����
	int m_hp = 0;											//�̗�
	int m_pp = 0;											//pp
	int m_group = 0;										//�O���[�v
	int m_weight = 0;										//���I�̍���
};

