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
	//����̃X�e�[�^�X��ݒ�
	void SetWeaponStatus();
	//���@�̃X�e�[�^�X��ݒ�
	void SetMagicStatus();
	//����؂�ւ��̍ۂɕ���̐؂�ւ����o�����true�A�o���Ȃ����false��Ԃ�
	bool GetWeapon(int number);
	//�o���l�����Z
	void PlusExp(const int& exp);
	//�w��̔ԍ��̕�����v���C���[�ɏ���������
	void SetWeapon(Equipment* number);
	//�����\��
	void PostRender()override;
	//�Y���̕���̋�����p��菊�����Z�^�������ꍇ�A����̋��������s���܂�
	void WeaponStrengthen(const int& number);
	//�Y���̔ԍ��̕�����폜
	void DeleteEquipment(const int& number);
	//���틭���ɂ��X�e�[�^�X���X�V
	void SetStatus();
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
		return m_MaxHP * (1 + 0.01f * float(m_ability->GetHP()));
	}
	//�ő�PP���擾
	int GetMaxPP() const
	{
		return m_MaxPP * (1 + 0.01f * float(m_ability->GetPP()));
	}
	//�U���͂��擾
	int GetAttack() const
	{
		return m_Attack * (1 + 0.01f * float(m_ability->GetPower()));
	}
	//���@�U���͂��擾
	int GetMattack() const
	{
		return m_Mattack * (1 + 0.01f * float(m_ability->GetMpower()));
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
	//�������Ă��镐��̔ԍ����擾
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
	//���x���A�b�v�������ǂ������擾
	bool GetLevelUp() const
	{
		return m_levelup;
	}
	//���x���A�b�v��false�ɂ���
	void OffLevelUp()
	{
		m_levelup = false;
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
	//���ݑ������̕���̋������x�����擾
	int GetWeaponLv()
	{
		return m_equipmentlist[m_SwordId]->GetLv();
	}
	//�������̃��Z�^�̊z���擾
	int GetHaveMeseta() const
	{
		return m_havemeseta;
	}
	//������菊�����Z�^���������ǂ�����Ԃ�
	bool isManyMeseta(const int& meseta) 
	{
		return m_havemeseta >= meseta;
	}
	//�������̃��Z�^���v���C���[�̃��Z�^�ɉ��Z
	void AddMeseta(const int& meseta) 
	{
		m_havemeseta += meseta;
		if (m_havemeseta > 99999) {
			m_havemeseta = 99999;
		}
	}
	//�������̃��Z�^���v���C���[�̃��Z�^���猸�Y
	void CutMeseta(const int& meseta)
	{
		m_havemeseta -= meseta;
	}
	//�Y����Equipment�N���X�̃C���X�^���X�ɃA�N�Z�X
	Equipment* GetEuipment(const int& number) const
	{
		return m_equipmentlist[number];
	}
	//��������̌�
	int GetEquipmentNumber() const
	{
		return m_equipmentlist.size();
	}
	//�摜�̓ǂݍ��ރt�H���_�̖��O
	const wchar_t* GetSpriteName(const int& number) const
	{
		return m_spritenamelist[number];
	}
	//�z��̓Y�����̕���̔ԍ����擾
	int GetWeaponNumber(const int& number) const
	{
		return m_equipmentlist[number]->GetId();
	}
	//�v���C���[�̗͂��擾
	int GetPower() const
	{
		return m_Power;
	}
	//�v���C���[�̌������擾
	int GetClever() const
	{
		return m_Clever;
	}
	//����̑Ō��͂��擾
	int GetWeaponAttack() const
	{
		return m_SwordAttack;
	}
	//����̖@���͂��擾
	int GetWeaponMattack() const
	{
		return m_SwordMattack;
	}
	//�Y���̔ԍ��̕���𑕔����Ă��邩�ǂ������擾
	bool GetisEquippedto(const int& number) const
	{
		return m_SwordId == number;
	}
private:  
	int m_Level = 1;                                      //���x��
	int m_Exp = 0;                                        //�o���l
	int m_NextExp = 40;                                   //���̃��x���A�b�v�ɕK�v�Ȍo���l
	int m_LevelExp = 40;                                  //���x�����ƂɕK�v�ȗ݌v�o���l
	int m_MaxHP = 65;                                    //�ő�HP
	int m_MaxPP = 100;                                    //�ő�PP(���@���̂ɕK�v)
	int m_Mattack = 40;                                   //���@�U����(����+����̖��@�U����)
	int m_Clever = 20;                                    //����
	int m_SwordMattack = 10;                              //����̖��@�U����
	int m_Attack = 40;                                    //�U����(�́{����̍U����)
	int m_Power = 20;                                     //��
	int m_SwordAttack = 10;                               //����̍U����
	int m_MagicId = 0;                                    //�g���閂�@�̔ԍ�
	int m_SwordId = 0;                                    //�������̕���̔ԍ�
	int m_Rarity = 0;                                     //�������̕���̃��A���e�B
	const wchar_t* m_SwordName;                           //�������̕���̖��O
	const wchar_t* m_MagicName;						      //���@�̖��O
	float m_DamageRate;									  //���@�̃_���[�W�{��
	int m_PPCost;										  //���@����̂ɕK�v��PP
	bool m_levelup = false;
	CFont m_font;                                         //�����\���N���X
	CSprite m_cursor;									  //����̃J�[�\��
	CVector3 m_scale = { 0.1f,0.1f,0.1f };				  //�摜�̑傫��
	CVector2 m_position = { 350.0f+64.0f*6,670.0f };      //�摜�̈ʒu
	std::vector<Equipment*> m_equipmentlist;              //Equipment�\���̂̔z��
	std::vector<CSprite*> m_spritelist;				      //�摜�̔z��
	std::vector<const wchar_t*> m_spritenamelist;		  //�摜�̖��O
	int m_havemateriallist[GameData::enMaterial_num] = { 0,0,0 };      //�v���C���[�̊e�f�ނ̏�����
	int m_havemeseta = 0;								  //�������Ă��郁�Z�^�̊z
	GameData* m_gamedata;                                 //GameData�N���X�̃|�C���^
	Weapon* m_weapon;									  //Weapon�N���X�̃|�C���^
	Magic* m_magic;										  //Magic�N���X�̃|�C���^
	Ability* m_ability;
	const int m_ProtHP = 65;
	const int m_ProtPP = 100;
	const int m_ProtPower = 20;
	const int m_ProtMpower = 20;
};