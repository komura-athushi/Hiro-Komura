#pragma once
#include "GameData.h"
//�v���C���[�̃X�e�[�^�X���Ǘ�����N���X�ł�
class PlayerStatus:public IGameObject
{
public:
	PlayerStatus();
	~PlayerStatus();
	bool Start();
	void Update();
	void SetGameData(GameData* gamedata)
	{
		m_gamedata = gamedata;
	}
	//����̃X�e�[�^�X���擾
	void GetWeaponStatus();
	//���x�����擾
	int GetLevel() const
	{
		return m_Level;
	}
	//�ő�HP���擾
	int GetMaxHP() const
	{
		return m_MaxHP;
	}
	//�ő�PP���擾
	int GetMaxPP() const
	{
		return m_MaxPP;
	}
	//�U���͂��擾
	int GetAttack() const
	{
		return m_Attack;
	}
	//���@�U���͂��擾
	int GetMattack() const
	{
		return m_Mattack;
	}
	//�g�p���閂�@�̔ԍ����擾
	int GetMagicId() const
	{
		return m_MagicId;
	}
	//�݌v�o���l���擾
	int GetExp() const
	{
		return m_Exp;
	}
	//���x���A�b�v�ɕK�v�Ȍo���l���擾
	int GetNextExp() const
	{
		return m_NextExp;
	}
	//�������镐��̔ԍ����擾
	int GetSwordId() const
	{
		return m_SwordId;
	}
	const wchar_t* GetSwordName() const
	{
		return m_SwordName;
	}
	//���x����ݒ�
	void SetLevel(const int& level) 
	{
		m_Level = level;
	}
	//�o���l�����Z
	void PlusExp(const int& exp);
	//�w��̔ԍ��̕�����v���C���[�ɏ���������
	void SetWeapon(int number)
	{
		m_haveweaponlist[number] = true;
	}
	//����؂�ւ��̍ۂɕ���̐؂�ւ����o�����true�A�o���Ȃ����false��Ԃ�
	bool GetWeapon(int number);
private:  
	int m_Level=1;                                        //���x��
	int m_Exp=0;                                          //�o���l
	int m_NextExp = 40;                                   //���̃��x���A�b�v�ɕK�v�Ȍo���l
	int m_LevelExp=40;                                    //���x�����ƂɕK�v�ȗ݌v�o���l
	int m_MaxHP=100;                                      //�ő�HP
	int m_MaxPP=100;                                      //�ő�PP(���@���̂ɕK�v)
	int m_Mattack = 10;                                   //���@�U����(����+����̖��@�U����)
	int m_Clever = 10;                                    ///����
	int m_SwordMattack = 10;                              //����̖��@�U����
	int m_Attack = 20;                                    //�U����(�́{����̍U����)
	int m_Power=10;                                       //��
	int m_SwordAttack = 10;                               //����̍U����
	int m_MagicId = 0;                                    //�g���閂�@�̔ԍ�
	int m_SwordId = 0;                                    //�������̕���̔ԍ�
	int m_Rarity = 0;                                     //�������̕���̃��A���e�B
	const wchar_t* m_SwordName;                              //�������̕���̖��O
	bool m_haveweaponlist[GameData::enWeapon_num] = { true,false,false,false,true,true };     //�v���C���[�̊e����̏�����
	GameData* m_gamedata;                                 //GameData�N���X�̃|�C���^
	Weapon* m_weapon;									  //Weapon�N���X�̃|�C���^
}; 

