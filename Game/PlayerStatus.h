#pragma once
#include "GameData.h"
#include "Equipment.h"
//�v���C���[�̃X�e�[�^�X���Ǘ�����N���X�ł�
class PlayerStatus:public IGameObject
{
	//�V���O���g���A���̃N���X�̃C���X�^���X����������݂����Ȃ����Ƃ������f�U�C���p�^�[���̈�ł�
	//�R���X�g���N�^��private�Ȋ֐��ɂ��邱�ƂŃC���X�^���X�̐����𐧌����܂�
	private:
	PlayerStatus();
	~PlayerStatus();
public:
	//���̊֐����g����PlayerStatus�N���X�̃C���X�^���X�𐶐����܂�
	//���̊֐����̃��[�J���ȐÓI�ϐ��͍ŏ��Ɋ֐����Ă΂��Ƃ��ɂ͏���������܂����A�ȍ~�Ă΂�鎞�͏���������܂���
	static PlayerStatus& GetInstance()
	{
		static PlayerStatus inst;
		return inst;
	}
public:
	bool Start();
	void Update();
	//GameData�N���X�̃C���X�^���X�̃|�C���^��ݒ�
	void SetGameData(GameData* gamedata)
	{
		m_gamedata = gamedata;
	}
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
	//�������Ă��镐��̔ԍ����擾
	const wchar_t* GetSwordName() const
	{
		return m_SwordName;
	}
	//���x����ݒ�
	void SetLevel(const int& level) 
	{
		m_Level = level;
	}
	//�w��̔ԍ��̑f�ނ��v���C���[�ɏ���������
	void SetMaterial(const int& number)
	{
		m_havemateriallist[number] += 1;
	}
	//���@�̔ԍ����擾
	const wchar_t* GetMagicName() const
	{
		return m_MagicName;
	}
	//���@�̃_���[�W�{�����擾
	float GetDamageRate() const
	{
		return m_DamageRate;
	}
	//���@��PP����ʂ��擾
	int GetPPCost() const
	{
		return m_PPCost;
	}
	//�Y���̑f�ނ̏��������擾
	int GetMaterial(const int& number) const
	{
		return m_havemateriallist[number];
	}
	//�Y���̑f�ނ��w�萔�������炷
	void CutMateial(const int& number,const int& amount)
	{
		m_havemateriallist[number] -= amount;
	}
    //���ݑ������̕��틭���f�ނ̏����󋵂�Ԃ�
	int GetWeaponMaterial(const int& number)
	{
		return m_weaponinventorylist[number].s_material;
	}
	//���ݑ������̕���̋������x�����擾
	int GetWeaponLv(const int& number)
	{
		return m_weaponinventorylist[number].s_equipment.GetLv();
	}
	//����̃X�e�[�^�X��ݒ�
	void SetWeaponStatus();
	//���@�̃X�e�[�^�X��ݒ�
	void SetMagicStatus();
	//����؂�ւ��̍ۂɕ���̐؂�ւ����o�����true�A�o���Ȃ����false��Ԃ�
	bool GetWeapon(int number);
	//�o���l�����Z
	void PlusExp(const int& exp);
	//�w��̔ԍ��̕�����v���C���[�ɏ���������
	void SetWeapon(const int& number);
	//�����\��
	void PostRender()override;
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
	const wchar_t* m_SwordName;                           //�������̕���̖��O
	const wchar_t* m_MagicName;						      //���@�̖��O
	float m_DamageRate;									  //���@�̃_���[�W�{��
	int m_PPCost;										  //���@����̂ɕK�v��PP
	CFont m_font;                                         //�����\���N���X
	struct WeaponInventory {							  //�������Ă��镐��̏󋵂�\���\����
		Equipment s_equipment;
		bool s_ishave = false;
		int s_material = 0;
	};
	std::vector<WeaponInventory> m_weaponinventorylist;   //WeaponInventory�\���̂̔z��
	int m_havemateriallist[GameData::enMaterial_num] = { 0,0,0 };										  //�v���C���[�̊e�f�ނ̏�����
	GameData* m_gamedata;                                 //GameData�N���X�̃|�C���^
	Weapon* m_weapon;									  //Weapon�N���X�̃|�C���^
	Magic* m_magic;										  //Magic�N���X�̃|�C���^
	bool m_Master = true;								  //����S�������[�h
};