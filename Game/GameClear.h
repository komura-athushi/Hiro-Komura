#pragma once
class Fade;
//ゲームをクリアしたときに呼びだされる画面
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start() override;
	void Update() override;
	void PostRender()override;
private:
	CSprite m_sprite;									//スプライト
	CVector2 m_position = CVector2::Zero();				//スプライトの座標
	CVector2 m_scale = CVector2::One();					//スプライトの大きさ
	const float m_stopY = -6200.0f;						//スプライトのy座標を一定値で停止させる
	const float m_speedmultiply = -95.0f;				//y座標を毎フレーム＋する
	float m_timer = 0.0f;								//タイマー
	const int m_time = 3.0f;							//タイマーの制限
	bool m_isgo = false;								//trueでy座標を動かす
	Fade* m_fade;										//フェード
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
};

