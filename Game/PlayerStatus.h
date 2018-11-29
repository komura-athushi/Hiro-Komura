#pragma once
#include "GameData.h"
//プレイヤーのステータスを管理するクラスです
class PlayerStatus:public IGameObject
{
public:
	PlayerStatus();
	~PlayerStatus();
	bool Start();
	void Update();
	void SetGameData(GameData* gamedata)
	{
		m_gamedata = gamedata;
	}
	//武器のステータスを取得
	void GetWeaponStatus();
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
	//魔法攻撃力を取得
	int GetMattack() const
	{
		return m_Mattack;
	}
	//使用する魔法の番号を取得
	int GetMagicId() const
	{
		return m_MagicId;
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
	//装備する武器の番号を取得
	int GetSwordId() const
	{
		return m_SwordId;
	}
	const wchar_t* GetSwordName() const
	{
		return m_SwordName;
	}
	//レベルを設定
	void SetLevel(const int& level) 
	{
		m_Level = level;
	}
	//経験値を加算
	void PlusExp(const int& exp);
	//指定の番号の武器をプレイヤーに所持させる
	void SetWeapon(int number)
	{
		m_haveweaponlist[number] = true;
	}
	//武器切り替えの際に武器の切り替えが出来ればtrue、出来なければfalseを返す
	bool GetWeapon(int number);
private:  
	int m_Level=1;                                        //レベル
	int m_Exp=0;                                          //経験値
	int m_NextExp = 40;                                   //次のレベルアップに必要な経験値
	int m_LevelExp=40;                                    //レベルごとに必要な累計経験値
	int m_MaxHP=100;                                      //最大HP
	int m_MaxPP=100;                                      //最大PP(魔法撃つのに必要)
	int m_Mattack = 10;                                   //魔法攻撃力(賢さ+武器の魔法攻撃力)
	int m_Clever = 10;                                    ///賢さ
	int m_SwordMattack = 10;                              //武器の魔法攻撃力
	int m_Attack = 20;                                    //攻撃力(力＋武器の攻撃力)
	int m_Power=10;                                       //力
	int m_SwordAttack = 10;                               //武器の攻撃力
	int m_MagicId = 0;                                    //使える魔法の番号
	int m_SwordId = 0;                                    //装備中の武器の番号
	int m_Rarity = 0;                                     //装備中の武器のレアリティ
	const wchar_t* m_SwordName;                              //装備中の武器の名前
	bool m_haveweaponlist[GameData::enWeapon_num] = { true,false,false,false,true,true };     //プレイヤーの各武器の所持状況
	GameData* m_gamedata;                                 //GameDataクラスのポインタ
	Weapon* m_weapon;									  //Weaponクラスのポインタ
}; 

