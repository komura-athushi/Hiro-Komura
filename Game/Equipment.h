#pragma once
class GameData;
class Weapon;
class Magic;
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
		return m_SwordAttack;
	}
	//����̖��@�U���͂��擾
	int GetMatk() const
	{
		return m_SwordMattack;
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
	
private:
	int m_SwordMattack = 0;                               //����̖��@�U����                          
	int m_SwordAttack = 0;                                //����̍U����
	int m_MagicId = 0;                                    //�g���閂�@�̔ԍ�
	int m_SwordId = 0;                                    //����̔ԍ�
	int m_Rarity = 0;                                     //����̃��A���e�B
	const wchar_t* m_SwordName;                           //����̖��O
	const wchar_t* m_MagicName;						      //���@�̖��O
	float m_DamageRate;									  //���@�̃_���[�W�{��
	int m_PPCost;                                         //���@����̂ɕK�v��PP
	int m_weaponextend = 0;                               //����G�N�X�e���h���x��
	GameData* m_gamedata;                                 //GameData�N���X�̃|�C���^
	Weapon* m_weapon;									  //Weapon�N���X�̃|�C���^
	Magic* m_magic;										  //Magic�N���X�̃|�C���^		  
};

