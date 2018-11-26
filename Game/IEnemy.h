#pragma once
class DropItem;
class IEnemy : public IGameObject
{
public:

	/*!
	* @brief	IEnemy�̃R���X�g���N�^
	* int h     HP��ݒ�
	* int a     Attack��ݒ�
	* int e     ���j���̌o���l��ݒ�
	*/
	IEnemy(int h,int a,int e);
	virtual ~IEnemy();

	/*!
	* @brief	�R���W�����̐����B
	* CVector3 pos   �R���W�����̍��W
	* float l        �R���W�����̍��W��y��l�������Z����
	* float r        �R���W�����̔��a
	*/
    void CCollision(CVector3 pos,float l, float r);

	/*!
	* @brief	�R���W�����̈ړ��B
	* CVector3 pos    �R���W�����̍��W
	* float l        �R���W������y���W��l�������Z      
	*/
	void SetCCollision(CVector3 pos,float l);
	//�v���C���[���G�l�~�[�Ƀ_���[�W��^���鎞�̏���
	void Damage(int attack);
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
	struct Item {
		int m_rare;
		float m_chance;
	};
	GameObj::CCollisionObj* m_collision;                      //�ۂ��R���W����
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
	DropItem* m_dropitem;
};

