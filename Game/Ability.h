#pragma once
class Ability
{
public:
	/*!
    @brief	Abilityのコンストラクタ
    *int id;							アビリティの番号
    *const wchar_t* name;				アビリティの名前
    *int power;						    ＋する打撃力
    *int mpower;					    ＋する法撃力
    *int hp;							＋するＨＰ
    *int pp;						    ＋するＰＰ
    */
	Ability(const int& id, const wchar_t* name, const int& power, const int& mpower, const int& hp, const int& pp);
	//コピーコンストラクタ
	Ability(const Ability& ab);
	~Ability();
	//番号を取得
	int GetId() const
	{
		return m_id;
	}
	//名前を取得
	const wchar_t* GetName() const
	{
		return m_abilityname;
	}
	//打撃力を取得
	int GetPower() const
	{
		return m_power;
	}
	//法撃力を取得
	int GetMpower() const
	{
		return m_mpower;
	}
	//hpを取得
	int GetHP() const
	{
		return m_hp;
	}
	//ppを取得
	int GetPP() const
	{
		return m_pp;
	}
private:
	int m_id;
	const wchar_t* m_abilityname;
	int m_power = 0;
	int m_mpower = 0;
	int m_hp = 0;
	int m_pp = 0;
};

