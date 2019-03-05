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
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	GameObj::Suicider::CEffekseer* m_effect;		//エフェクト
	bool m_isdisplay = false;
	bool m_isaccess = false;
	bool m_isbutton = false;
	CSprite m_sprite,m_sprite2;
	CVector3 m_scale;
	CVector3 m_position;
	CVector2 m_displayposition;
	CFont m_font;                                               //文字表示クラス
	const float m_frame = 40.0f;
	Player* m_player;
	GameCamera* m_gamecamera;
};

