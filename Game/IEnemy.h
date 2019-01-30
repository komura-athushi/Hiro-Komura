#pragma once
#include "Weapon.h"
#include "Material.h"
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
	*/
	IEnemy(const int& h,const int& a,const int& e,const int dropchances[Weapon::m_HighestRarity],const int dropmaterialchances[Material::m_HighestRarity]);
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
	void Damage(const int& attack,int number=0);
	//�h���b�v����A�C�e���̏���
	void Drop();
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
	//�����\��
	void PostRender()override;
protected:
	SuicideObj::CCollisionObj* m_collision;                   //�ۂ��R���W����
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
	int m_timer = 0;                                          //�����蔻��ɃN�[���^�C��
	int m_timer1 = 0;										  //�t�H�C�G�̓����蔻��̃N�[���^�C��
	int m_timer2 = 0;										  //�C���O�����c��
	int m_timer3 = 0;									      //�U���o�[�X��
	int m_timer5 = 0;										  //�}�W�X�t�B��
	int m_fonttimer = 0;									  //�����\���̃^�C�}�[
	bool m_damage = false;                                    //�_���[�W���󂯂����ǂ���
	bool m_death = false;                                     //HP��0�ȉ��ɂȂ������ǂ���
	bool m_displayfont = false;								  //�_���\�����邩�ǂ���
	CFont m_font;                                             //�����\���N���X
	int m_dropChances[Weapon::m_HighestRarity];			      //�G�l�~�[�̃h���b�v����A�C�e���A[1]��0.4f�Ȃ烌�A�x1��40%�Ńh���b�v����݂�����
	int m_dropmaterialChances[Material::m_HighestRarity];	  //�G�l�~�[�̃h���b�v����f�ނ̊m��
};

