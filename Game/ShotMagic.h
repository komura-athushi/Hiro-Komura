#pragma once
class ShotMagic:public IGameObject
{
public:
	ShotMagic();
	/*!
	@brief	ShotMagic�̃R���X�g���N�^
	*int id;							//���@�̔ԍ�
	*const wchar_t* name;					//���@�̖��O
	*int damageRate;						//���@�̃_���[�W�{��
	*int ppCost;							//���@����̂ɕK�v��PP
	*/
	ShotMagic(const int& id, const wchar_t* name, const float& damageRate, const int& ppCost);
	//�R�s�[�R���X�g���N�^
	ShotMagic(const ShotMagic& magic);
	~ShotMagic();
	bool Start();
	void Update();
	//�R���W�����ƃ��f����ݒ�A���W�ƃR���W�����̑傫��
	void SetCollisionModel(const CVector3& pos, const float& scale);
	//�t�H�C�G
	void Foie();
	void FoieUpdate();
	//�C���O��
	void Irugra();
	void IrugraUpdate();
	//�U���o�[�X
	void Zanbas();
	void ZanbasUpdate();
	//�V�t�^
	void Shihuta();
	//�}�W�b�N�X�t�B�A
	void MagicSphere();
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
	//���@�̔ԍ���ݒ�
	void SetId(const int& id) 
	{
		m_id = id;
	}
	//���W��ݒ�
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	//�ړ����x��ݒ�
	void SetMoveSpeed(const CVector3& movespeed)
	{
		m_movespeed = movespeed;
	}
	//�傫����ݒ�
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//�_���[�W��ݒ�
	void SetDamage(const int& mattack, const float& damagerate)
	{
		m_damage = int(mattack*damagerate);
	}
	//�v���C���[�̌�����ݒ�
	void SetDirectionPlayer(const CVector3& pos)
	{
		m_directionplayer = pos;
	}
private:
	int m_id;											//���@�̔ԍ�
	const wchar_t* m_name;								//���@�̖��O
	float m_damageRate;									//���@�̃_���[�W�{��
	int m_ppCost;										//���@����̂ɕK�v��PP
	CVector3 m_scale{ CVector3::One() };				//�G�t�F�N�g�̑傫��
	CVector3 m_position{ CVector3::Zero() };            //�G�t�F�N�g�̍��W
	CVector3 m_movespeed{ CVector3::Zero() };			//�G�t�F�N�g�̈ړ����x
	CVector3 m_directionplayer{ CVector3::Zero() };		//�v���C���[�̌����ɕ��s�ȃx�N�g��
	int m_damage;										//���������ꍇ�ɃG�l�~�[�ɗ^����_���[�W
	float m_deletetime = 0;								//���@�������܂ł̎���
	SuicideObj::CCollisionObj* m_collision;		        //�ۂ��R���W����
	int m_modelnumber = 0;								//���f���̐�
	int m_modelcount = 0;								//�����������f���̐�
	int m_timer = 0;									//�����̃��f���ƃR���W���������ԍ�����Ő�������ꍇ�̃N�[���^�C��
	//�X�L�����f���A�R���W�����A�^�C�}�[�A�폜�������ǂ���
	struct MagicModel {
		GameObj::CSkinModelRender* s_skinModelReder;
		SuicideObj::CCollisionObj* s_collision;
		float s_timer=0.0f;
		bool s_delete = false;
	};
	std::vector<MagicModel> m_magicmocelList;
};

