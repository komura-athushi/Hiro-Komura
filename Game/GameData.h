#pragma once
#include "Weapon.h"
#include "Magic.h"
#include "Material.h"
#include "Equipment.h"
class Enemy;
//�f�[�^�N���X�̃C���X�^���X�𐶐�����N���X�ł�
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
	Weapon* GetWeapon(int number) 
	{
		return &m_weaponlist[number];
	}
	//�����̔ԍ��̖��@�̃|�C���^���擾
	Magic* GetMagic(int number)
	{
		return &m_magiclist[number];
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
private:
	std::vector<Weapon> m_weaponlist;                   //Weapon�N���X�̉ϒ��z��
	std::vector<Magic> m_magiclist;						//Magic�N���X�̉ϒ��z��
	std::vector<Material> m_materiallist;				//Material�N���X�̉ϒ��z��
	std::vector<Equipment> m_equipmentlist;				//Equipment�N���X�̉ϒ��z��
};

