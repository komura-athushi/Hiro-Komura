#pragma once
//���@�̃f�[�^�̃N���X�ł�
class Magic
{
public:
	Magic();
	~Magic();
	bool Start();
	void Update();
private:
	int m_id;							//���@�̔ԍ�
	std::string m_name;					//���@�̖��O
	float m_damageRate;					//���@�̃_���[�W�{��
	int m_ppCost;						//���@����̂ɕK�v��PP
};

