#pragma once
//�v���C���[�̃X�e�[�^�X���Ǘ�����N���X�ł�
class PlayerStatus:public IGameObject
{
public:
	PlayerStatus();
	~PlayerStatus();
	bool Start();
	void Update();
	//���x�����擾
	int GetLevel() const
	{
		return m_Level;
	}
	//�ő�HP���擾
	int GetMaxHP() const
	{
		return m_MaxHP;
	}
	//�ő�PP���擾
	int GetMaxPP() const
	{
		return m_MaxPP;
	}
	//�U���͂��擾
	int GetAttack() const
	{
		return m_Attack;
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
	//���x����ݒ�
	void SetLevel(const int& level) 
	{
		m_Level = level;
	}
	//�o���l�����Z
	void PlusExp(const int& exp);
private:  
	int m_Level=1;                                        //���x��
	int m_Exp=0;                                          //�o���l
	int m_NextExp = 40;                                   //���̃��x���A�b�v�ɕK�v�Ȍo���l
	int m_MaxHP=100;                                      //�ő�HP
	int m_MaxPP=100;                                      //�ő�PP(���@���̂ɕK�v)
	int m_Attack = 20;                                    //�U����(�́{����̍U����)
	int m_Power=10;                                       //��
	int m_SwordAttack = 10;                               //����̍U����
}; 

