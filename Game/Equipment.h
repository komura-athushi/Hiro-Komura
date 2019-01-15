#pragma once
class GameData;
class Weapon;
class Magic;
//武器を収納しているインベントリのクラスです
class Equipment
{
public:
	//Equipment();
	Equipment(const int& number);
	~Equipment();
	//武器のステータスを設定
	void SetWeaponStatus();
	//魔法のステータスを設定
	void SetMagicStatus();
	//武器の番号を取得
	int GetId() const
	{
		return m_SwordId;
	}
	//武器の名前を取得
	const wchar_t* GetName() const
	{
		return m_SwordName;
	}
	//武器のレアリティを取得
	int GetRarity() const
	{
		return m_Rarity;
	}
	//武器の強化レベルを取得
	int GetLv() const
	{
		return m_weaponextend;
	}
	//武器の物理攻撃力を取得
	int GetAtk() const
	{
		return m_SwordAttack;
	}
	//武器の魔法攻撃力を取得
	int GetMatk() const
	{
		return m_SwordMattack;
	}
	//武器の魔法の番号を取得
	int GetMagicId() const
	{
		return m_MagicId;
	}
	//魔法の名前を取得
	const wchar_t* GetMagicName() const
	{
		return m_MagicName;
	}
	//魔法のダメージ倍率を取得
	float GetDamageRate() const
	{
		return m_DamageRate;
	}
	//魔法のPPコストを取得
	int GetPPCost() const
	{
		return m_PPCost;
	}
	
private:
	int m_SwordMattack = 0;                               //武器の魔法攻撃力                          
	int m_SwordAttack = 0;                                //武器の攻撃力
	int m_MagicId = 0;                                    //使える魔法の番号
	int m_SwordId = 0;                                    //武器の番号
	int m_Rarity = 0;                                     //武器のレアリティ
	const wchar_t* m_SwordName;                           //武器の名前
	const wchar_t* m_MagicName;						      //魔法の名前
	float m_DamageRate;									  //魔法のダメージ倍率
	int m_PPCost;                                         //魔法を放つのに必要なPP
	int m_weaponextend = 0;                               //武器エクステンドレベル
	GameData* m_gamedata;                                 //GameDataクラスのポインタ
	Weapon* m_weapon;									  //Weaponクラスのポインタ
	Magic* m_magic;										  //Magicクラスのポインタ		  
};

