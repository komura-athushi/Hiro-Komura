#pragma once
class Player;
//�v���C���[��Ǐ]����J�����ł�
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	//�O�l�̎��_�̍��W�ƒ����_���v�Z����֐�
	void Hutu();
	//unityChan�̃��[�h
	void unityChan();
	//���������J���I�X�g�������𒭂߂邽�߂̃��[�h
	void cagliostro();
	//�v���C���[�̃|�C���g���Z�b�g
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	//�J�����̍��W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�J�����̒����_���擾
	CVector3 GetTarget() const
	{
		return m_target;
	}
	GameObj::PerspectiveCamera* GetCamera()
	{
		return m_camera;
	}
private:
	GameObj::PerspectiveCamera* m_camera;                  //3D�J�����̃C���X�^���X
	CVector3 m_position = { 0.0f,200.0f,400.0f};           //�J�����̍��W
	CVector3 m_target;                                     //�J�����̒����_
	float m_degreexz=0.0f, m_degreey=0.0f;                 //�p�x
	float m_radianx = 0.0f, m_radiany = 0.0f;              //�p�x�����W�A���P�ʂɒ��������
	 float m_r = 160.0f;								   //�L�����N�^�[�ƃJ�����̋���
	const CVector3 m_axisY={ 0.0f,1.0f,0.0f };             //Y�����̃x�N�g��   
	CVector3 m_playerposition;                             //�v���C���[�̍��W
	Player* m_player;                                      //�v���C���[�N���X�̃|�C���^
	float m_topos = 80.0f;
};

