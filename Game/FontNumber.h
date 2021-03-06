#pragma once
class GameCamera;
class GameData;
class FontNumber:public IGameObject
{
public:
	FontNumber();
	~FontNumber();
	bool Start() override;
	void Update() override;
	void PostRender() override;
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
	//赤色に設定
	void SetRed()
	{
		m_isred = true;
	}
private:
	std::vector<int> m_numberlist;						//引数で受け取った数字を記憶する、154なら{1, 5, 4}みたいな感じで
	std::vector<CSprite*> m_spritelist;		            //CSpriteの可変長配列
	CVector3 m_position = CVector3::Zero();				//受け取った座標
	CVector3 m_spriteposition = CVector3::Zero();		//スクリーン座標
	CVector2 m_scale = { 0.3f,0.3f};					//画像の大きさ
	CVector3 m_plusposition = CVector3::Zero();			//ランダムに座標を変える
	const float m_addx = -0.016f;						//表示する数字をx方向に少しずつずらします
	const float m_addy = -0.0015f;						//表示する数字を少しずつ上に動くようにします
	float m_y = 0.0f;									//初期のy座標からどれだけyに足したか
	const float m_frame = 40.0f;
	float m_alpha = 1.0f;								//画像の透明度
	float m_timer = 0.0f;								//タイマー
	const int m_time = 40;								//タイマーの制限
	GameCamera* m_gamecamera = nullptr;					//ゲームカメラクラスのポインタ
	GameData* m_gamedata = nullptr;						//ゲームデータクラスのポインタ
	int m_number = 0;								    //受け取った数値を記憶します
	bool m_isred = false;								//プレイヤーの被ダメ表示は赤くします
};

