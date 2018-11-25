#pragma once
//武器データのクラスです
class Weapon:public IGameObject
{
public:
	Weapon();
	~Weapon();
	bool Start();
	void Update();
private:
	int m_id;							//武器の番号
	std::string m_name;					//武器の名前
	int m_rarity;						//武器のレアリティ
	int m_atk;							//武器の物理攻撃力
	int m_matk;							//武器の魔法攻撃力
	int m_magicid;						//武器の魔法の番号
};

