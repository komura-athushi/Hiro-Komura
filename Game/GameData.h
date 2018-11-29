#pragma once
#include "Weapon.h"
class Enemy;
class Magic;
class GameData:public IGameObject
{
public:
	GameData();
	~GameData();
	bool Start();
	void Update();
	//�����̔ԍ��̕���̃|�C���^���擾
	Weapon* GetWeapon(int number) 
	{
		return &m_weaponlist[number];
	}
	enum EnWeapon {
		enWeapon_Sword,									//�\�[�h
		enWeapon_FireSword,								//�t�@�C�A�\�[�h
		enWeapon_IceSword,								//�A�C�X�\�[�h
		enWeapon_WindSword,								//�E�B���h�\�[�h
		enWeapon_GreatSword,							//�O���C�g�\�[�h
		enWeapon_BlueLightSword,						//�u���[���C�g�\�[�h
		enWeapon_num									//�E�F�|���̎��
	};
	enum EnMagic {
		enMagic_Zangeki,
		enMagic_Fire,
		enMagic_Ice,
		enMagic_Wind,
		enMagic_SuperZangeki,
		enMagic_TwincleStar,
		enMagic_num
	};
private:
	std::vector<Weapon> m_weaponlist;                   //Weapon�N���X�̉ϒ��z��
    Enemy* m_enemies;
	Magic* m_magics;
};

