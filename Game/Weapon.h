#pragma once
//νf[^ΜNXΕ·
class Weapon:public IGameObject
{
public:
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
	~Weapon();
	bool Start();
	void Update();
private:
	int m_id;							//νΜΤ
	std::string m_name;					//νΜΌO
	int m_rarity;						//νΜAeB
	int m_atk;							//νΜ¨UΝ
	int m_matk;							//νΜ@UΝ
	int m_magicid;						//νΜ@ΜΤ
};

