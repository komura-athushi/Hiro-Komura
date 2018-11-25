#pragma once
//魔法のデータのクラスです
class Magic
{
public:
	Magic();
	~Magic();
	bool Start();
	void Update();
private:
	int m_id;							//魔法の番号
	std::string m_name;					//魔法の名前
	float m_damageRate;					//魔法のダメージ倍率
	int m_ppCost;						//魔法を放つのに必要なPP
};

