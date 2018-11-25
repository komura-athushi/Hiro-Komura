#pragma once
class Enemy:public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
private:
	int m_id;								//エネミーの番号
	std::string m_name;						//エネミーの名前
	int m_hp;								//エネミーのHP
	int m_atk;								//エネミーの攻撃力
	int m_exp;								//エネミー撃破時の経験値
	float m_dropChances[3];					//エネミーのドロップするアイテム
};

