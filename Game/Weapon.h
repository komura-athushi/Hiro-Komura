#pragma once
//武器データのクラスです
class Weapon:public IGameObject
{
public:
	/*!
	@brief	Weaponのコンストラクタ
	*int id;							//武器の番号
	*std::string name;					//武器の名前
	*int rarity;						//武器のレアリティ
	*int atk;							//武器の物理攻撃力
	*int matk;							//武器の魔法攻撃力
	*int mnumber;						//武器の魔法の番号
	*/
	Weapon(const int& id,const std::string& name,const int& rarity,const int& atk,const int& matk,const int& mnumber);
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

