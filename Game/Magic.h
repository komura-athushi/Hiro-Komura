#pragma once
//���@�̃f�[�^�̃N���X�ł�
class Magic
{
public:
	/*!
	@brief	Magic�̃R���X�g���N�^
	*int id;							//���@�̔ԍ�
	*std::string name;					//���@�̖��O
	*int damageRate;						//���@�̃_���[�W�{��
	*int ppCost;							//���@����̂ɕK�v��PP
	*/
	Magic(const int& id,const std::string& name,const float& damageRate,const int& ppCost);
	~Magic();
	bool Start();
	void Update();
private:
	int m_id;							//���@�̔ԍ�
	std::string m_name;					//���@�̖��O
	float m_damageRate;					//���@�̃_���[�W�{��
	int m_ppCost;						//���@����̂ɕK�v��PP
};

