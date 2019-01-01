#pragma once
class GameData;
class Weapon;
class Magic;
//��������[���Ă���C���x���g���̃N���X�ł�
class Equipment
{
public:
	Equipment();
	~Equipment();
	//����̃X�e�[�^�X���擾
	void GetWeaponStatus();
	//���@�̃X�e�[�^�X���擾
	void GetMagicStatus();
	//����ID��ݒ�
	void SetWeaponID(const int& id);
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

