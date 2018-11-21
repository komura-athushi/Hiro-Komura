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
	int GetMaxHP() const
	{
		return m_MaxHP;
	}
	//最大PPを取得
	int GetMaxPP() const
	{
		return m_MaxPP;
	}
	//攻撃力を取得
	int GetAttack() const
	{
		return m_Attack;
	}
	//累計経験値を取得
	int GetExp() const
	{
		return m_Exp;
	}
	//レベルアップに必要な経験値を取得
	int GetNextExp() const
	{
		return m_NextExp;
	}
	//レベルを設定
	void SetLevel(const int& level) 
	{
		m_Level = level;
	}
	//経験値を加算
	void PlusExp(const int& exp);
private:  
	int m_Level=1;                                        //レベル
	int m_Exp=0;                                          //経験値
	int m_NextExp = 40;                                   //次のレベルアップに必要な経験値
	int m_MaxHP=100;                                      //最大HP
	int m_MaxPP=100;                                      //最大PP(魔法撃つのに必要)
	int m_Attack = 20;                                    //攻撃力(力＋武器の攻撃力)
	int m_Power=10;                                       //力
	int m_SwordAttack = 10;                               //武器の攻撃力
}; 

