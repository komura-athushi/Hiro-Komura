#pragma once
class Player;
class GameCamera;
class Teleport:public IGameObject
{
public:
	Teleport();
	~Teleport();
	bool Start();
	void Update();
	void PostRender();
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
	GameObj::Suicider::CEffekseer* m_effect;		//�G�t�F�N�g
	bool m_isdisplay = false;
	bool m_isaccess = false;
	bool m_isbutton = false;
	CSprite m_sprite,m_sprite2;
	CVector3 m_scale;
	CVector3 m_position;
	CVector2 m_displayposition;
	CFont m_font;                                               //�����\���N���X
	const float m_frame = 40.0f;
	Player* m_player;
	GameCamera* m_gamecamera;
};

