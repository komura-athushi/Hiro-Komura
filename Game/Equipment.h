#pragma once
class GameData;
class Weapon;
class Magic;
//武器を収納しているインベントリのクラスです
class Equipment
{
public:
	Equipment();
	~Equipment();
	//武器のステータスを取得
	void GetWeaponStatus();
	//魔法のステータスを取得
	void GetMagicStatus();
	//武器IDを設定
	void SetWeaponID(const int& id);
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

