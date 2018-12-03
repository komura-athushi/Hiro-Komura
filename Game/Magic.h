#pragma once
//���@�̃f�[�^�̃N���X�ł�
class Magic
{
public:
	/*!
	@brief	Magic�̃R���X�g���N�^
	*int id;							//���@�̔ԍ�
	*const wchar_t* name;					//���@�̖��O
	*int damageRate;						//���@�̃_���[�W�{��
	*int ppCost;							//���@����̂ɕK�v��PP
	*/
	Magic(const int& id, const wchar_t* name,const float& damageRate,const int& ppCost);
	//�R�s�[�R���X�g���N�^
	Magic(const Magic& magic);
	~Magic();
	bool Start();
	void Update();
	//���@�̔ԍ����擾
	int GetId() const
	{
		return m_id;
	}
	//���@�̖��O���擾
	const wchar_t* GetName() const
	{
		return m_name;
	}
	//���@�̃_���[�W�{�����擾
	float GetDamageRate() const
	{
		return m_damageRate;
	}
	//���@��PP�R�X�g���擾
	int GetPPCost() const
	{
		return m_ppCost;
	}
private:
	int m_id;							//���@�̔ԍ�
	const wchar_t* m_name;				//���@�̖��O
	float m_damageRate;					//���@�̃_���[�W�{��
	int m_ppCost;						//���@����̂ɕK�v��PP

};

