#pragma once
#include "Weapon.h"
class Enemy:public IGameObject
{
public:
	/*!
	@brief	Enemyのコンストラクタ
	*int id;							//エネミーの番号
	*std::string name;					//エネミーの名前
	*int hp;						//エネミーのHP
	*int atk;							//エネミーの攻撃力
	*int exp;							//エネミー撃破時の経験値
	*int dropchances[4];						//エネミーのドロップするアイテム
	*/
	Enemy(const int& id,const std::string& name,const int& hp,const int& atk,const int& exp,const int dropchances[Weapon::m_HighestRarity]);
	//コピーコンストラクタ
	Enemy(const Enemy& enemy);
	~Enemy();
	bool Start();
	void Update();
private:
	int m_id;													//エネミーの番号
	std::string m_name;											//エネミーの名前
	int m_hp;													//エネミーのHP
	int m_atk;													//エネミーの攻撃力
	int m_exp;													//エネミー撃破時の経験値
	int m_dropChances[Weapon::m_HighestRarity];					//エネミーのドロップするアイテム
};

