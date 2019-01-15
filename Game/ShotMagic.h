#pragma once
class IEnemy;
//�v���C���[�̕������̃N���X�ł�
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
	/*!
	//�R���W�����ƃ��f����ݒ�A���W�ƃR���W�����̑傫��
	@brief	���@�̃��f�����R���W�����𐶐����܂�
	*CVector3 pos;					//���W
	*float scale;					//�R���W�����̑傫��
	*int id;						//���@�̔ԍ�
	*int number						//�_���[�W�����̎��ɂ��� 
	*bool damage;					//true�Ń_���[�W����̃R���W�����𐶐����܂�
	*/
	void SetCollisionModel(const CVector3& pos, const float& scale,const int& id, const CVector3& scl = CVector3::Zero(),const int& number=0,bool damage = true); //����������false�ɂ���ƃ_���[�W�����̃R���W�����𐶐����܂�
	/*!
	//�_�������R���W�����𔭐����������ꍇ�͂�����
	//�R���W�����ƃ��f����ݒ�A���W�ƃR���W�����̑傫��
	@brief	���@�̃��f�����R���W�����𐶐����܂�
	*CVector3 pos;					//���W
	*float scale;					//�R���W�����̑傫��
	*int id;						//���@�̔ԍ�
	*int number						//m_modelcount�������Ă�������
	*bool damage;					//true�Ń_���[�W����̃R���W�����𐶐����܂�
	*/
	void SetCollisionModelnoDamage(const CVector3& pos, const float& scale, const int& id, const CVector3& scl = CVector3::Zero(), const int& number = 0, bool damage = true);
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
	void ShihutaUpdate();
	//�}�W�b�N�X�t�B�A
	void MagicSphere();
	void MagicSphereUpdate();
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
	//�_���[�W���擾
	int GetDamage()
	{
		return m_damage;
	}
	//�v���C���[�̌�����ݒ�
	void SetDirectionPlayer(const CVector3& pos)
	{
		m_directionplayer = pos;
	}
	//�Y���̔ԍ���MagicModel�̔z��̍��W���擾
	CVector3 GetPosition(const int& number)
	{
		return m_magicmocelList[number].s_position;
	}
	//�Y���̔ԍ���MagicModel�̔z��̐F�X���폜
	void DeleteMagicModel(const int& number);

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
	int m_timer1 = 0;
	//�X�L�����f���A�R���W�����A�^�C�}�[�A�폜�������ǂ���
	struct MagicModel {
		GameObj::Suicider::CEffekseer* s_effect;		//�G�t�F�N�g
		SuicideObj::CCollisionObj* s_collision;			//�R���W����
		float s_timer = 0.0f;							//�f���[�g�^�C��
		CVector3 s_position = {CVector3::Zero()};		//���W
		bool s_delete = false;							//���f���ƃR���W�������폜�������ǂ���
	};
	std::vector<MagicModel> m_magicmocelList;			//MagicModel�\���̂̉ϒ��z��
	static const int m_number[];
	//�e���@�̐F�X�Ȃ��
	//�t�H�C�G
	const float m_deletetime1 = 30.0f;
	const int m_modelnumber1 = 1;
	const CVector3 m_scale1 = { 2.0f,2.0f,2.0f };
	const float m_collisionscale1 = 90.0f;
	const float m_multiplyspeed1 = 15.0f*60.0f;
	//�C���O��
	const float m_deletetime2 = 50.0f;
	const int m_modelnumber2 = 3;
	const CVector3 m_scale2 = { 1.0f,1.0f,1.0f };
	const float m_collisionscale2 = 50.0f;
 	const float m_multiplyspeed2 = 30.0f*60.0f;
	const int m_time2 = 12;
	//�U���o�[�X
	const float m_deletetime3 = 10.0f;
	const int m_modelnumber3 = 1;
	const CVector3 m_scale3 = { 5.0f,5.0f,5.0f };
	const float m_collisionscale3 = 225.0f;
	const float m_multiplyspeed3 = 0.0f;
	//�V�t�^
	const float m_deletetime4 = 10.0f;
	const int m_modelnumber4 = 1;
	const CVector3 m_scale4 = { 3.0f,3.0f,3.0f };
	const float m_collisionscale4 = 0.0f;
	const float m_multiplyspeed4 = 0.0f;
	//�}�W�X�t�B
	const float m_deletetime5 = 30.0f;
	const float m_deletecollisiontime5 = 10;
	const int m_modelnumber5 = 1;
	const CVector3 m_scale5 = { 0.5f,0.5f,0.5f };
	const float m_collisionscale5 = 28.0f;
	const float m_multiplyspeed5 = 15.0f*60.0f;
	const float m_multiply5 = 6.0f;
};

