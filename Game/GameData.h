#pragma once
#include "Weapon.h"
#include "Magic.h"
#include "Material.h"
#include "Ability.h"
class Enemy;
//�Q�[���̐F�X�ȃf�[�^�������Ă���N���X�ł�
class GameData:public IGameObject
{
	//�V���O���g���A���̃N���X�̃C���X�^���X����������݂����Ȃ����Ƃ������f�U�C���p�^�[���̈�ł�
private:
	//�R���X�g���N�^�ƃf�X�g���N�^��private�ɐ錾���邱�ƂŊO�����琶���o���Ȃ�����
	GameData();
	~GameData();
public:
	//���̊֐����g����GameData�N���X�̃C���X�^���X�𐶐����܂�
	//���̊֐����̃��[�J���ȐÓI�ϐ��͍ŏ��Ɋ֐����Ă΂��Ƃ��ɂ͏���������܂����A�ȍ~�Ă΂�鎞�͏���������܂���
	static GameData& GetInstance() 
	{
		//private�ȃR���X�g���N�^���Ăяo��
		static GameData inst;
		return inst;
	}
public:
	bool Start();
	void Update();
	//�����̔ԍ��̕���̃|�C���^���擾
	Weapon* GetWeapon(const int& number) 
	{
		return &m_weaponlist[number];
	}
	//�����̔ԍ��̖��@�̃|�C���^���擾
	Magic* GetMagic(const int& number)
	{
		return &m_magiclist[number];
	}
	//�����̔ԍ��̑f�ނ̃|�C���^���擾
	Material* GetMaterial(const int& number)
	{
		return &m_materiallist[number];
	}
	//�X�e�[�W���N���A
	void SetClear(const int& number)
	{
		m_stage[number] = true;
	}
	//�Y���̃X�e�[�W���N���A�ς݂��ǂ���
	bool GetStageClear(const int& number)
	{
		return m_stage[number];
	}
	//�X�̔��W���x�����擾
	int GetTownLevel() const
	{
		return m_townlevel;
	}
	//�X�̔��W���x�������ҁ[
	void UpTownLevel()
	{
		m_townlevel++;
	}
	//�Q�[�����N���A�������ǂ���
	bool GetisGameClear()
	{
		return m_isgameclear;
	}
	//�Q�[���N���A�I
	void SetGameClear()
	{
		m_isgameclear = true;
	}
	//�Q�[������U�I��������ǂ���
	bool GetisGameEnd()
	{
		return m_isgameend;
	}
	//�Q�[������U�I���
	void SetGameEnd()
	{
		m_isgameend = true;
	}
	//�Y���̃A�r���e�B�̃|�C���^���擾
	Ability* GetAbility(const int& number)
	{
		return m_abilitylist[number];
	}
	//�A�r���e�B�N���X�̉ϒ��z��̒������擾
	int GetAbilityListNumber() const
	{
		return m_abilitylist.size();
	}
	//�Y���̔ԍ��̐�����CSprite�N���X�̃|�C���^��Ԃ�
	CSprite* GetCSprite(const int& number)
	{
		return m_numberspritelist[number];
	}
	//����\�͂̃E�F�C�g�̍��v�l���擾
	int GetTotalWeight() const
	{
		return m_totalabilityweight;
	}
	//����\�͂̈����̃O���[�v�̃E�F�C�g�̍��v�l���擾
	int GetTotalGroupWeight(const int& group) const
	{
		return m_totalabilitygroupweightlist[group - 1];
	}
	//���@�̌����ꂽ�������Z
	void PlusMagicNumber()
	{
		m_magicnumber++;
	}
	//���@�̌����ꂽ�����擾
	int GetMagicNumber() const
	{
		return m_magicnumber;
	}
	enum EnWeapon {
		enWeapon_Sword,									//�\�[�h
		enWeapon_FireSword,								//�t�@�C�A�\�[�h
		enWeapon_IceSword,								//�A�C�X�\�[�h
		enWeapon_WindSword,								//�E�B���h�\�[�h
		enWeapon_GreatSword,							//�O���C�g�\�[�h
		enWeapon_BlueLightSword,						//�N���X�^���G�b�W
		enWeapon_BattleReadyBlade,					    //�o�g���u���[�h
		enWeapon_AncientWarriorBlade,					//�o���f�b�h�\�[�h
		enWeapon_LegendalySword,						//���W�F���_���[�\�[�h
		enWeapon_num									//�E�F�|���̎��
	};
	enum EnMagic {
		enMagic_Zangeki,								//����
		enMagic_Fire,									//�t�H�C�G
		enMagic_Ice,									//�C���E�O�����c
		enMagic_Wind,									//�U���o�[�X
		enMagic_SuperZangeki,							//�V�t�^
		enMagic_TwincleStar,							//�}�W�b�N�X�t�B�A
		enMagic_1,										
		enMagic_2,
		enMagic_3,
		enMagic_num										//���@�̎��
	};
	enum EnMaterial {
		enMaterial_Wood,								//��
		enMaterial_Ishi,								//��
		enMaterial_Brick,								//�����K
		enMaterial_num									//�f�ނ̎��
	};
	static const int m_stagenumber = 3;					//�X�e�[�W��
private:
	std::vector<Weapon> m_weaponlist;                   //Weapon�N���X�̉ϒ��z��
	std::vector<Magic> m_magiclist;						//Magic�N���X�̉ϒ��z��
	std::vector<Material> m_materiallist;				//Material�N���X�̉ϒ��z��
	std::vector<Ability*> m_abilitylist;				//�A�r���e�B�N���X�̉ϒ��z��
	std::vector<CSprite*> m_numberspritelist;           //�����̉摜�̉ϒ��z��
	std::vector<const wchar_t*> m_filepathlist;
	bool m_stage[3] = { false,false,false };			//�e�X�e�[�W���N���A�������ǂ���
	int m_townlevel = 0;								//�X�̔��W���x��
	bool m_isgameclear = false;							//�Q�[�����N���A�������ǂ���
	bool m_isgameend = false;							//�Q�[������U�I��������ǂ���
	CSprite* m_sprite;
	int m_totalabilityweight = 0;
	int m_abilitygroupnumber = 0;
	std::vector<int> m_totalabilitygroupweightlist;
	int m_magicnumber = 0;
};

