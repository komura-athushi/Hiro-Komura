#pragma once
//�f�ނ̃f�[�^�N���X�ł�
class Material
{
public:
	/*!
	@brief	Material�̃R���X�g���N�^
	*const wchar_t* name;					//�f�ނ̖��O
	*int rarity      //�f�ނ̃��A���e�B
	*/
	Material(const wchar_t* name, int rarity);
	Material();
	~Material();
	//�f�ނ̖��O���擾
	const wchar_t* GetMaterialName()
	{
		return m_name;
	}
	//�f�ނ̃��A���e�B���擾
	int GetRarity() const
	{
		return m_rarity;
	}
	static const int m_HighestRarity = 3;
	static const int m_raritynumber[];      //���A���e�B���Ƃ̑f�ނ̎��
private:
	const wchar_t* m_name;					//�f�ނ̖��O
	int m_rarity;							//�f�ނ̃��A���e�B
};

/*
�b��I�ȑf�ނ̃��A���e�B�Ɣԍ��Ɩ��O
1
�y					0
2
��					1
3
�����K			    2
*/