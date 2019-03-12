#pragma once
class Player;
//エネミーがドロップする素材のクラスです
class DropMaterial:public IGameObject
{
public:
	DropMaterial();
	~DropMaterial();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3 pos)
	{
		m_position = pos;
	}
	//レアリティの中の番号を設定
	void SetNumber(const int& number)
	{
		m_number = number;
	}
	//レアリティを設定
	void SetRarity(const int& rarity)
	{
		m_rarity = rarity;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position;                                        //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	CQuaternion m_rotation;                                     //クオンテーション
	int m_state;                                                //ドロップ品の番号
	Player* m_player;                                           //プレイヤークラスのポインタ
	int m_rarity;												//素材のレアリティ
	int m_number;												//素材のレアリティの中の番号
	float m_degree = 0.0f;
	const float m_sevolume = 1.7f;
};

