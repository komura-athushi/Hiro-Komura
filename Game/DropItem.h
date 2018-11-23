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
	//何をドロップするかを設定
	void SetNumber(const int& number)
	{
		m_number = number;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position;                                        //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	CQuaternion m_rotation;                                     //クオンテーション
	int m_number;                                               //ドロップ品の番号
	Player* m_player;                                           //プレイヤークラスのポインタ
};

