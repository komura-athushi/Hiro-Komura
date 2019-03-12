#pragma once
class GameCamera;
class GameData;
class FontNumber:public IGameObject
{
public:
	FontNumber();
	~FontNumber();
	bool Start();
	void Update();
	void PostRender()override;
	//表示する数字を受け取る
	void SetNumber(const int& number)
	{
		m_number = number;
	}
	//座標を設定
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
private:
	std::vector<int> m_numberlist;						//引数で受け取った数字を記憶する
	std::vector<CSprite*> m_spritelist;					//CSpriteの可変長配列
	CVector3 m_position;								//受け取った座標
	CVector3 m_spriteposition;							//スクリーン座標
	CVector2 m_scale = { 0.3f,0.3f};
	const float m_addx = -0.015f;
	const float m_addy = -0.0015f;
	float m_y = 0.0f;
	const float m_frame = 40.0f;
	float m_alpha = 1.0f;
	float m_timer = 0.0f;								//タイマー
	const int m_time = 40;								//タイマーの制限
	GameCamera* m_gamecamera = nullptr;
	GameData* m_gamedata = nullptr;
	int m_number;
};

