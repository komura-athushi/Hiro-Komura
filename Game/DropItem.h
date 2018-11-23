#pragma once
class Player;
//エネミーのドロップアイテムのクラスです
class DropItem:public IGameObject
{
public:
	DropItem();
	~DropItem();
	bool Start();
	void Update();
	//プレイヤーのポインタを設定
	void SetPlayer(Player* player)
	{
		m_player=player;
	}
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//アイテムのレア度を設定
	void SetState(const int& state)
	{
		m_state = state;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position;                                        //座標
	CVector3 m_scale = { 0.5f,0.5f,0.5f };                      //大きさ
	CQuaternion m_rotation;                                     //クオンテーション
	int m_state;                                               //ドロップ品の番号
	Player* m_player;                                           //プレイヤークラスのポインタ
};

