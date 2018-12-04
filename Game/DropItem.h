#pragma once
#include "Weapon.h"
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
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position;                                        //座標
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	CQuaternion m_rotation;                                     //クオンテーション
	int m_state;                                                //ドロップ品の番号
	Player* m_player;                                           //プレイヤークラスのポインタ
	int m_rarity;												//武器のレアリティ
	int m_number;												//武器のレアリティの中の番号
};

