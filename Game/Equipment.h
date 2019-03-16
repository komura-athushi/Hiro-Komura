#pragma once
#include "Ability.h"
class GameData;
class Weapon;
class Magic;
//��������[���Ă���C���x���g���̃N���X�ł�
class Equipment
{
public:
	//Equipment();
	Equipment(const int& number);
	Equipment(const Equipment& eq);
	~Equipment();
	//����̃X�e�[�^�X��ݒ�
	void SetWeaponStatus();
	//���@�̃X�e�[�^�X��ݒ�
	void SetMagicStatus();
	//�������������
	void Strengthen();
	//�Y���̓���\�̖͂��O���擾
	const wchar_t* GetAbilityName(const int& number);
	//�o���l�����Z
	void PlusExp(const int& exp);
	//�o���l�����ɗ^�����ꍇ�ɃX�e�[�^�X���v�Z
	void KariPlusExp(const int& exp);
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
	//����̉��̋������x�����擾
	int GetKariLv() const
	{
		return m_kariweaponextend;
	}
	//����̕����U���͂��擾
	int GetAtk() const
	{
		return m_Attack;
	}
	//����̉��̕����U���͂��擾
	int GetKariAtk() const
	{
 		return m_kariAttack;
	}
	//����̖��@�U���͂��擾
	int GetMatk() const
	{
		return m_Mattack;
	}
	//����̉��̖��@�U���͂��擾
	int GetKariMatk() const
	{
		return m_kariMattack;
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
	//�݌v�o���l���擾
	int GetExp() const
	{
		return m_Exp;
	}
	//���̗݌v�o���l���擾
	int GetKariExp() const
	{
		return m_kariExp;
	}
	//���̃��x���A�b�v�ɕK�v�Ȍo���l���擾
	int GetNextExp() const
	{
		return m_NextExp;
	}
	//���̃��x���A�b�v�ɕK�v�ȉ��̌o���l���擾
	int GetKariNextExp() const
	{
		return m_kariNextExp;
	}
	//�f�ނɂ����Ƃ��̌o���l���擾
	int GetMaterialExp() const
	{
		return (m_weaponextend + 1) * m_explevel1 * 0.6f;
	}
	//�A�r���e�B�̍��v�l�̒l�������Ă���A�r���e�B�N���X�̃|�C���^��Ԃ�
	Ability* GetAbility() const
	{
		return m_ability;
	}
private:
	int m_kariExp = 0;                                    //�o���l
	int m_kariNextExp = 0;                                //���̃��x���A�b�v�ɕK�v�Ȍo���l
	int m_kariLevelExp = 0;                               //���x�����ƂɕK�v�ȗ݌v�o���l
	int m_kariSwordMattack = 0;                           //����̖��@�U����
	int m_kariSwordAttack = 0;                            //����̍U����
	int m_kariweaponextend = 0;                           //����G�N�X�e���h���x��
	int m_kariAttack = 0;							      //����\�͂⋭���ɂ��ŏI�I�ȉ��̑Ō���
	int m_kariMattack = 0;							      //����\�͂⋭���ɂ��ŏI�I�ȉ��̖@����
	int m_Exp = 0;                                        //�o���l
	int m_NextExp = 0;                                    //���̃��x���A�b�v�ɕK�v�Ȍo���l
	int m_LevelExp = 0;                                   //���x�����ƂɕK�v�ȗ݌v�o���l
	int m_explevel1 = 50;						          //���x��1�܂łɕK�v�Ȍo���l
	const int m_expcost = 1.5f;							  //���x�����オ�邲�ƂɕK�v�Ȍo���l�̏�Z
	const float m_exprarity = 0.3f;					      //���A���e�B���ƂɃ��x���A�b�v�ɕK�v�Ȍo���l����Z
	int m_SwordMattack = 0;                               //����̖��@�U����
	int m_protSwordMattack = 0;							  //����̏����̖��@�U����
	int m_SwordAttack = 0;                                //����̍U����
	int m_protSwordAattack = 0;							  //����̏����̍U����
	int m_Attack = 0;									  //����\�͂⋭���ɂ��ŏI�I�ȑŌ���
	int m_Mattack = 0;									  //����\�͂⋭���ɂ��ŏI�I�Ȗ@����
	int m_MagicId = 0;                                    //�g���閂�@�̔ԍ�
	int m_SwordId = 0;                                    //����̔ԍ�
	int m_Rarity = 0;                                     //����̃��A���e�B
	const wchar_t* m_SwordName;                           //����̖��O
	const wchar_t* m_MagicName;						      //���@�̖��O
	float m_DamageRate;									  //���@�̃_���[�W�{��
	int m_PPCost;                                         //���@����̂ɕK�v��PP
	int m_weaponextend = 0;                               //����G�N�X�e���h���x��
	int m_meseta = 0;									  //���p���Ɋl���ł��郁�Z�^�̊z
	GameData* m_gamedata;                                 //GameData�N���X�̃|�C���^
	Weapon* m_weapon;									  //Weapon�N���X�̃|�C���^
	Magic* m_magic;										  //Magic�N���X�̃|�C���^
	Ability* m_ability;									  //�����Ă�A�r���e�B�̍��v�l
	std::vector<Ability*> m_abilitylist;				  //�A�r���e�B�N���X�̃|�C���^�̉ϒ��z��
	static const float m_multiply;						  //�������̃X�e�[�^�X�̏㏸�{��
	static const float m_costmultiply;					  //������p�̏㏸�{��
	const int m_slotlimitnumber = 3;				      //����\�͐��̏��
	bool m_ishaveability = false;						  //����\�͂��������Ă��邩�ǂ���
	const int m_probability[3] = {75, 40, 20};			  //����\�͂̕t�^������
};

