#pragma once
class Fade;
//タイトル
class Title:public IGameObject
{
public:
	Title();
	~Title();
	bool Start() override;
	void Update() override;
	void PostRender() override;
private:
	CSprite m_sprite,m_sprite2;								//スプライト
	CVector2 m_position = CVector2::Zero();					//画像の座標
	CVector2 m_scale = CVector2::One();						//画像の大きさ
	Fade* m_fade;											//フェード
	float m_currentAlpha = 0.0f;							//!<現在のα値。
	bool m_isadd = true;									//a値を加算するかどうか
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
};

