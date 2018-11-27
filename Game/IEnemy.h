#pragma once
#include "Weapon.h"
class IEnemy : public IGameObject
{
public:

	/*!
	* @brief	IEnemy�̃R���X�g���N�^
	* int h     HP��ݒ�
	* int a     Attack��ݒ�
	* int e     ���j���̌o���l��ݒ�
	* int dropchances[]  �h���b�v����A�C�e���̃��A�x�Ɗm���A����Ƃ����A�x0�`3
	*/
	IEnemy(const int& h,const int& a,const int& e, const int dropchances[Weapon::m_HighestRarity]);
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
	void Damage(const int& attack);
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
	//�����\��
	void PostRender()override;
protected:
	SuicideObj::CCollisionObj* m_collision;                      //�ۂ��R���W����
	//�G�l�~�[�̐F�X�ȃX�e�[�^�X
	int m_MaxHP;                                              //�ő�HP
	int m_HP;                                                 //HP
	int m_MaxPP;                                              //�ő�PP
	int m_PP;                                                 //PP
	int m_Attack;                                             //�U����
	int m_Exp;                                                //�o���l
	int m_timer = 0;                                          //�����蔻��ɃN�[���^�C��
	bool m_damage = false;                                    //�_���[�W���󂯂����ǂ���
	bool m_death = false;                                     //HP��0�ȉ��ɂȂ������ǂ���
	CFont m_font;                                             //�����\���N���X
	int m_dropChances[Weapon::m_HighestRarity];			      //�G�l�~�[�̃h���b�v����A�C�e���A[1]��0.4f�Ȃ烌�A�x1��40%�Ńh���b�v����݂�����
};

