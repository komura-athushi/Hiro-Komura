#pragma once
class Player;
class GameCamera;
class Teleport:public IGameObject
{
public:
	Teleport();
	~Teleport();
	bool Start() override;
	void Update() override;
	void PostRender() override;
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//���W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	GameObj::Suicider::CEffekseer* m_effect = nullptr;			//�G�t�F�N�g
	bool m_isdisplay = false;									//�^�[�Q�b�g�\�����邩�ǂ���
	bool m_isaccess = false;									//�A�N�Z�X�������ǂ���
	bool m_isbutton = false;									//�{�^��
	CSprite m_sprite,m_sprite2;									//�X�v���C�g
	CVector3 m_scale = CVector3::Zero();						//�G�t�F�N�g�̑傫��
	CVector3 m_position = CVector3::Zero();						//���W
	CVector2 m_displayposition = CVector2::Zero(); 				//�X�v���C�g�̍��W
	CFont m_font;                                               //�����\���N���X
	const float m_frame = 40.0f;
	Player* m_player = nullptr;									//�v���C���[
	GameCamera* m_gamecamera = nullptr;							//�Q�[�����̃J����
};

