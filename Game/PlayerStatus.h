#pragma once
//プレイヤーのステータスを管理するクラスです
class PlayerStatus:public IGameObject
{
public:
	PlayerStatus();
	~PlayerStatus();
	bool Start();
	void Update();
	//レベルを取得
	int GetLevel() const
	{
		return m_level;
	}
	//最大HPを取得
	float GetMaxHP() const
	{
		return m_MaxHP;
	}
	//最大PPを取得
	float GetMaxPP() const
	{
		return m_MaxPP;
	}
	//攻撃力を取得
	float GetAttack() const
	{
		return m_Attack;
	}
	//防御力を取得
	float GetDefense() const
	{
		return m_Defense;
	}
	//レベルを設定
	void SetLevel(const float& level) 
	{
		m_level = level;
	}
	//経験値を加算
	void PlusExp(const float& exp)
	{
		m_exp += exp;
	}
private:
	int m_level;                                        //レベル
	int m_exp;                                          //経験値
	float m_MaxHP;                                      //最大HP
	float m_MaxPP;                                      //最大PP(魔法撃つのに必要)
	float m_Attack;                                     //攻撃力
	float m_Defense;                                    //防御力
};

