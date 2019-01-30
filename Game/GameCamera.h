#pragma once
class Player;
//プレイヤーを追従するカメラです
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	//三人称視点の座標と注視点を計算する関数
	void Hutu();
	//unityChanのモード
	void unityChan();
	//可愛い可愛いカリオストロちゃんを眺めるためのモード
	void cagliostro();
	//プレイヤーのポイントをセット
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	//カメラの座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//カメラの注視点を取得
	CVector3 GetTarget() const
	{
		return m_target;
	}
	GameObj::PerspectiveCamera* GetCamera()
	{
		return m_camera;
	}
private:
	GameObj::PerspectiveCamera* m_camera;                  //3Dカメラのインスタンス
	CVector3 m_position = { 0.0f,200.0f,400.0f};           //カメラの座標
	CVector3 m_target;                                     //カメラの注視点
	float m_degreexz=0.0f, m_degreey=0.0f;                 //角度
	float m_radianx = 0.0f, m_radiany = 0.0f;              //角度をラジアン単位に直したやつ
	 float m_r = 160.0f;								   //キャラクターとカメラの距離
	const CVector3 m_axisY={ 0.0f,1.0f,0.0f };             //Y方向のベクトル   
	CVector3 m_playerposition;                             //プレイヤーの座標
	Player* m_player;                                      //プレイヤークラスのポインタ
	float m_topos = 80.0f;
};

