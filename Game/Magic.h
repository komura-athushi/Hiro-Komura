#pragma once
//魔法のデータのクラスです
class Magic
{
public:
	/*!
	@brief	Magicのコンストラクタ
	*int id;							//魔法の番号
	*const wchar_t* name;					//魔法の名前
	*int damageRate;						//魔法のダメージ倍率
	*int ppCost;							//魔法を放つのに必要なPP
	*/
	Magic(const int& id, const wchar_t* name,const float& damageRate,const int& ppCost);
	//コピーコンストラクタ
	Magic(const Magic& magic);
	~Magic();
	bool Start();
	void Update();
	//魔法の番号を取得
	int GetId() const
	{
		return m_id;
	}
	//魔法の名前を取得
	const wchar_t* GetName() const
	{
		return m_name;
	}
	//魔法のダメージ倍率を取得
	float GetDamageRate() const
	{
		return m_damageRate;
	}
	//魔法のPPコストを取得
	int GetPPCost() const
	{
		return m_ppCost;
	}
private:
	int m_id;							//魔法の番号
	const wchar_t* m_name;				//魔法の名前
	float m_damageRate;					//魔法のダメージ倍率
	int m_ppCost;						//魔法を放つのに必要なPP

};

