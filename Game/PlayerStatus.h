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
		return m_Level;
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
	//レベルを設定
	void SetLevel(const int& level) 
	{
		m_Level = level;
	}
	//経験値を加算
	void PlusExp(const int& exp)
	{
		m_Exp += exp;
	}
private:  
	int m_Level=1;                                        //レベル
	int m_Exp=0;                                          //経験値
	int m_MaxHP=100;                                      //最大HP
	int m_MaxPP=100;                                      //最大PP(魔法撃つのに必要)
	int m_Attack=15;                                      //攻撃力
}; 

