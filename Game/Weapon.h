#pragma once
//武器データのクラスです
class Weapon
{
public:
	Weapon() {}
	/*!
	@brief	Weaponのコンストラクタ
	*int id;							//武器の番号
	*const wchar_t* name;				//武器の名前
	*int rarity;						//武器のレアリティ
	*int atk;							//武器の物理攻撃力
	*int matk;							//武器の魔法攻撃力
	*int mnumber;						//武器の魔法の番号
	*/
	Weapon(const int& id, const wchar_t* name,const int& rarity,const int& atk,const int& matk,const int& mnumber);
	//コピーコンストラクタ
	Weapon(const Weapon& wpn);
	~Weapon();
	
	//武器の番号を取得
	int GetId() const
	{
		return m_id;
	}
	//武器の名前を取得
	const wchar_t* GetName() const
	{
		return m_name;
	}
	//武器のレアリティを取得
	int GetRarity() const
	{
		return m_rarity;
	}
	//武器の物理攻撃力を取得
	int GetAtk() const
	{
		return m_atk;
	}
	//武器の魔法攻撃力を取得
	int GetMatk() const
	{
		return m_matk;
	}
	//武器の魔法の番号を取得
	int GetMagicId() const
	{
		return m_magicid;
	}
	static const int m_HighestRarity = 4;     //武器の最高レアリティ
	static const int m_raritynumber[];        //レアリティごとの武器の種類
private:
	int m_id;								//武器の番号
	const wchar_t* m_name;					//武器の名前
	int m_rarity;							//武器のレアリティ
	int m_atk;								//武器の物理攻撃力
	int m_matk;								//武器の魔法攻撃力
	int m_magicid;							//武器の魔法の番号
};

/*
暫定的なソードのレアリティと番号と名前
0
Sword                 0
1
FireSword             1
IceSword              2
WindSword             3
2 
GreatSword            4
3
BlueLightSword        5
*/

