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
	GameObj::Suicider::CEffekseer* m_effect = nullptr;			//エフェクト
	bool m_isdisplay = false;									//ターゲット表示するかどうか
	bool m_isaccess = false;									//アクセスしたかどうか
	bool m_isbutton = false;									//ボタン
	CSprite m_sprite,m_sprite2;									//スプライト
	CVector3 m_scale = CVector3::Zero();						//エフェクトの大きさ
	CVector3 m_position = CVector3::Zero();						//座標
	CVector2 m_displayposition = CVector2::Zero(); 				//スプライトの座標
	CFont m_font;                                               //文字表示クラス
	const float m_frame = 40.0f;
	Player* m_player = nullptr;									//プレイヤー
	GameCamera* m_gamecamera = nullptr;							//ゲーム中のカメラ
};

