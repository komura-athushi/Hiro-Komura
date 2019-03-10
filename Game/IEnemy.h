#pragma once
#include "Weapon.h"
#include "Material.h"
class GameCamera;
//�G�l�~�[�̊�{�N���X�ł�
//HP��h���b�v�A�폜�̏����Ȃǂ͂��̃N���X�ŏ������܂�
class IEnemy : public IGameObject
{
public:
	/*!
	* @brief	IEnemy�̃R���X�g���N�^
	* int h     HP��ݒ�
	* int a     Attack��ݒ�
	* int e     ���j���̌o���l��ݒ�
	* int dropchances[]  �h���b�v����A�C�e���̃��A�x�Ɗm��
	* int dropmaterialchances[]  �h���b�v����f�ނ̃��A�x�Ɗm��
	* int meseta   �h���b�v���郁�Z�^�̑�̂̊z
	*/
	IEnemy(const int& h,const int& a,const int& e,const int dropchances[Weapon::m_HighestRarity],const int dropmaterialchances[Material::m_HighestRarity],const int& meseta);
	virtual ~IEnemy();
	/*!
	* @brief	�R���W�����̐����B
	* CVector3 pos   �R���W�����̍��W
	* float l        �R���W�����̍��W��y��l�������Z����
	* float r        �R���W�����̔��a
	*/
    void CCollision(const CVector3& pos,const float& l,const float& r);

	/*!
	* @brief	�R���W�����̈ړ��B
	* CVector3 pos    �R���W�����̍��W
	* float l        �R���W������y���W��l�������Z      
	*/
	void SetCCollision(const CVector3& pos,const float& l);
	//�v���C���[���G�l�~�[�Ƀ_���[�W��^���鎞�̏���
	void Damage(const int& attack,int number = 0);
	//�h���b�v����A�C�e���̏���
	void Drop();
	//�����\��
	void PostRender()override;
	//�G�l�~�[��HP��0��؂������ǂ���
	bool GetDeath()
	{
		return m_death;
	}
	//�G�l�~�[�̏������Ă���o���l��Ԃ�
	int GetExp()
	{
		return m_Exp;
	}
	//�G�l�~�[�̃|�W�V�������擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�G�l�~�[�̃R���W�����̍��W���擾
	CVector3 GetCollisionPosition() const
	{
		return m_collisionposition;
	}
	//�R���W�����̔��a���擾
	float GetRadius() const
	{
		return m_r;
	}
	//�G�l�~�[�̔ԍ���ݒ�
	void SetNumber(const int& number)
	{
		m_number = number;
	}
	//�G�l�~�[�̔ԍ����擾
	int GetNumber() const 
	{
		return m_number;
	}
protected:
	SuicideObj::CCollisionObj* m_collision;                   //�ۂ��R���W����
	float m_r;												  //�R���W�����̔��a
	CVector3 m_position;									  //���W
	CVector3 m_collisionposition;
	CVector3 m_fontposition;
	//�G�l�~�[�̐F�X�ȃX�e�[�^�X
	int m_MaxHP;                                              //�ő�HP
	int m_HP;                                                 //HP
	int m_MaxPP;                                              //�ő�PP
	int m_PP;                                                 //PP
	int m_Attack;                                             //�U����
	int m_damagecount;										  //�󂯂��_���[�W
	int m_Exp;                                                //�o���l
	float m_timer = 0.0f;                                     //�����蔻��ɃN�[���^�C��
	float m_timer1 = 0.0f;									  //�t�H�C�G�̓����蔻��̃N�[���^�C��
	float m_timer2 = 0.0f;									  //�C���O�����c��
	float m_timer3 = 0.0f;									  //�U���o�[�X��
	float m_timer5 = 0.0f;									  //�}�W�X�t�B��
	float m_timer7 = 0.0f;									  //�e���a��
	float m_timer8 = 0.0f;									  //�����K����	
	float m_fonttimer = 0.0f;								  //�����\���̃^�C�}�[
	bool m_damage = false;                                    //�_���[�W���󂯂����ǂ���
	bool m_death = false;                                     //HP��0�ȉ��ɂȂ������ǂ���
	bool m_displayfont = false;								  //�_���\�����邩�ǂ���
	CFont m_font;                                             //�����\���N���X
	int m_dropmeseta;										  //�h���b�v���郁�Z�^�̑�̂̊z
	int m_dropChances[Weapon::m_HighestRarity];			      //�G�l�~�[�̃h���b�v����A�C�e���A[1]��0.4f�Ȃ烌�A�x1��40%�Ńh���b�v����݂�����
	int m_dropmaterialChances[Material::m_HighestRarity];	  //�G�l�~�[�̃h���b�v����f�ނ̊m��
	bool m_isdropWeapon = false;							  //���킪�h���b�v�������ǂ���
	static const int m_mesetarand = 2;
	static const float m_frame;								  //fps
	GameCamera* m_gamecamera;
	const float m_sevolume = 2.5f;
	int m_number = 0;
};

