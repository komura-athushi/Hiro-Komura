#pragma once
class IEnemy : public IGameObject
{
public:
	/*!
	* @brief	IEnemy�̃R���X�g���N�^
	* int h     HP��ݒ�
	* int a     Attack��ݒ�
	*/
	IEnemy(int h,int a);
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
	* CVector pos    �R���W�����̍��W
	* float l        �R���W������y���W��l�������Z      
	*/
	void SetCCollision(CVector3 pos,float l);
	virtual void Update()=0;
	virtual void Attack()=0;
	void Damege(int attack);
	//void SetStatus(int h, int a);
protected:
	std::unique_ptr<GameObj::CCollisionObj> m_collision;      //�ۂ��R���W����
	//�v���C���[�̐F�X�ȃX�e�[�^�X
	int m_MaxHP;                                              //�ő�HP
	int m_HP;                                                 //HP
	int m_MaxPP;                                              //�ő�PP
	int m_PP;                                                 //PP
	int m_Attack;                                             //�U����
	int m_timer = 0;
	bool m_death = false;                                     //HP��0�ȉ��ɂȂ������ǂ���  
};

