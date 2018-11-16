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
		return m_level;
	}
	//�ő�HP���擾
	float GetMaxHP() const
	{
		return m_MaxHP;
	}
	//�ő�PP���擾
	float GetMaxPP() const
	{
		return m_MaxPP;
	}
	//�U���͂��擾
	float GetAttack() const
	{
		return m_Attack;
	}
	//�h��͂��擾
	float GetDefense() const
	{
		return m_Defense;
	}
	//���x����ݒ�
	void SetLevel(const int& level) 
	{
		m_level = level;
	}
	//�o���l�����Z
	void PlusExp(const int& exp)
	{
		m_exp += exp;
	}
private:  
	int m_level;                                          //���x��
	int m_exp;                                            //�o���l
	int m_MaxHP=100;                                      //�ő�HP
	int m_MaxPP=100;                                      //�ő�PP(���@���̂ɕK�v)
	int m_Attack=50;                                      //�U����
	int m_Defense=50;                                     //�h���
}; 

