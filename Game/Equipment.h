#pragma once
class GameData;
class Weapon;
class Magic;
class Ability;
//��������[���Ă���C���x���g���̃N���X�ł�
class Equipment
{
public:
	//Equipment();
	Equipment(const int& number);
	~Equipment();
	//����̃X�e�[�^�X��ݒ�
	void SetWeaponStatus();
	//���@�̃X�e�[�^�X��ݒ�
	void SetMagicStatus();
	//�������������
	void Strengthen();
	//����̔ԍ����擾
	int GetId() const
	{
		return m_SwordId;
	}
	//����̖��O���擾
	const wchar_t* GetName() const
	{
		return m_SwordName;
	}
	//����̃��A���e�B���擾
	int GetRarity() const
	{
		return m_Rarity;
	}
	//����̋������x�����擾
	int GetLv() const
	{
		return m_weaponextend;
	}
	//����̕����U���͂��擾
	int GetAtk() const
	{
		return m_Attack;
	}
	//����̖��@�U���͂��擾
	int GetMatk() const
	{
		return m_Mattack;
	}
	//����̖��@�̔ԍ����擾
	int GetMagicId() const
	{
		return m_MagicId;
	}
	//���@�̖��O���擾
	const wchar_t* GetMagicName() const
	{
		return m_MagicName;
	}
	//���@�̃_���[�W�{�����擾
	float GetDamageRate() const
	{
		return m_DamageRate;
	}
	//���@��PP�R�X�g���擾
	int GetPPCost() const
	{
		return m_PPCost;
	}
	//����̔��p���i���擾
	int GetMeseta() const
	{
		return m_meseta;
	}
	//�����R�X�g(���Z�^)���擾
	int GetCost() const
	{
		return (m_weaponextend + 1) * m_meseta * m_costmultiply;
	}
	//����\�͂̐����擾
	int GetAbilityNumber() const
	{
		return m_abilitylist.size();
	}
	//����\�͂��������Ă��邩�ǂ������擾
	bool GetisHaveAbility() const
	{
		return m_ishaveability;
	}
	//�����HP���擾
	int GetHP() const
	{
		return m_hp;
	}
	//�����PP���擾
	int GetPP() const
	{
		return m_pp;
	}
private:
	int m_SwordMattack = 0;                               //����̖��@�U����                          
	int m_SwordAttack = 0;                                //����̍U����
	int m_Attack = 0;									  //����\�͂⋭���ɂ��ŏI�I�ȑŌ���
	int m_Mattack = 0;									  //����\�͂⋭���ɂ��ŏI�I�Ȗ@����
	int m_MagicId = 0;                                    //�g���閂�@�̔ԍ�
	int m_SwordId = 0;                                    //����̔ԍ�
	int m_Rarity = 0;                                     //����̃��A���e�B
	int m_hp = 0;										  //����\�͂ɂ���ĕt�^�����hp
	int m_pp = 0;										  //����\�͂ɂ���ĕt�^�����pp
	const wchar_t* m_SwordName;                           //����̖��O
	const wchar_t* m_MagicName;						      //���@�̖��O
	float m_DamageRate;									  //���@�̃_���[�W�{��
	int m_PPCost;                                         //���@����̂ɕK�v��PP
	int m_weaponextend = 0;                               //����G�N�X�e���h���x��
	int m_meseta = 0;									  //���p���Ɋl���ł��郁�Z�^�̊z
	GameData* m_gamedata;                                 //GameData�N���X�̃|�C���^
	Weapon* m_weapon;									  //Weapon�N���X�̃|�C���^
	Magic* m_magic;										  //Magic�N���X�̃|�C���^
	std::vector<Ability*> m_abilitylist;				  //�A�r���e�B�N���X�̃|�C���^�̉ϒ��z��
	static const float m_multiply;						  //�������̃X�e�[�^�X�̏㏸�{��
	static const float m_costmultiply;					  //������p�̏㏸�{��
	const int m_probability = 20;					      //����\�͂��P���m��
	const int m_slotlimitnumber = 3;				      //����\�͐��̏��
	bool m_ishaveability = false;						  //����\�͂��������Ă��邩�ǂ���
};

