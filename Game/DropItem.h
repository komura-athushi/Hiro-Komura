#pragma once
class Player;
class Equipment;
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
	//武器のレアリティの中の番号を設定
	void SetState(const int& state)
	{
		m_state = state;
	}
	//武器のレアリティを設定
	void SetRarity(int rare)
	{
		m_rarity = rare;
	}
	//メセタの額を設定
	void SetMeseta(const int& meseta)
	{
		m_meseta = meseta;
	}
	//武器であると設定
	void SetisWeapon()
	{
		m_isweapon = true;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position;                                        //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	CQuaternion m_rotation=CQuaternion::Identity();             //クオンテーション
	int m_state;                                                //ドロップ品の番号
	Player* m_player;                                           //プレイヤークラスのポインタ
	Equipment* m_equipment = nullptr;
	int m_rarity;												//武器のレアリティ
	int m_number;												//武器のレアリティの中の番号
	int m_meseta;												//メメタの額
	bool m_isweapon = false;									//自身が武器かどうか
	bool m_issetweapon = false;
	static const float m_height;								//ドロップ時に+するy座標
	static const float m_height_weapon;							//ドロップ時に+するy座標(武器)
	float m_degree = 0.0f;
	const float m_sevolume = 2.0f;
};

