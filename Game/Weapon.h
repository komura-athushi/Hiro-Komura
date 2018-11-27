#pragma once
//νf[^ΜNXΕ·
class Weapon
{
public:
	Weapon() {}
	/*!
	@brief	WeaponΜRXgN^
	*int id;							//νΜΤ
	*std::string name;					//νΜΌO
	*int rarity;						//νΜAeB
	*int atk;							//νΜ¨UΝ
	*int matk;							//νΜ@UΝ
	*int mnumber;						//νΜ@ΜΤ
	*/
	Weapon(const int& id,const std::string& name,const int& rarity,const int& atk,const int& matk,const int& mnumber);
	//Rs[RXgN^
	Weapon(const Weapon& wpn);
	~Weapon();
	
	//νΜΤπζΎ
	int GetId() const
	{
		return m_id;
	}
	//νΜΌOπζΎ
	std::string GetName() const
	{
		return m_name;
	}
	//νΜAeBπζΎ
	int GetRarity() const
	{
		return m_rarity;
	}
	//νΜ¨UΝπζΎ
	int GetAtk() const
	{
		return m_atk;
	}
	//νΜ@UΝπζΎ
	int GetMatk() const
	{
		return m_matk;
	}
	//νΜ@ΜΤπζΎ
	int GetMagicId() const
	{
		return m_magicid;
	}
	static const int m_HighestRarity = 4;     //νΜΕAeB
	//static const int m_raritynumber[];
private:
	int m_id;								//νΜΤ
	std::string m_name;						//νΜΌO
	int m_rarity;							//νΜAeB
	int m_atk;								//νΜ¨UΝ
	int m_matk;								//νΜ@UΝ
	int m_magicid;							//νΜ@ΜΤ
};

/*
bθIΘ\[hΜAeBΖΤΖΌO
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

