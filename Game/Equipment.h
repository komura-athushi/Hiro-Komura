#pragma once
#include "Ability.h"
class GameData;
class Weapon;
class Magic;
//武器を収納しているインベントリのクラスです
class Equipment
{
public:
	//Equipment();
	Equipment(const int& number);
	Equipment(const Equipment& eq);
	~Equipment();
	//武器のステータスを設定
	void SetWeaponStatus();
	//魔法のステータスを設定
	void SetMagicStatus();
	//武器を強化する
	void Strengthen();
	//該当の特殊能力の名前を取得
	const wchar_t* GetAbilityName(const int& number);
	//経験値を加算
	void PlusExp(const int& exp);
	//経験値を仮に与えた場合にステータスを計算
	void KariPlusExp(const int& exp);
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
	//武器の仮の強化レベルを取得
	int GetKariLv() const
	{
		return m_kariweaponextend;
	}
	//武器の物理攻撃力を取得
	int GetAtk() const
	{
		return m_Attack;
	}
	//武器の仮の物理攻撃力を取得
	int GetKariAtk() const
	{
 		return m_kariAttack;
	}
	//武器の魔法攻撃力を取得
	int GetMatk() const
	{
		return m_Mattack;
	}
	//武器の仮の魔法攻撃力を取得
	int GetKariMatk() const
	{
		return m_kariMattack;
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
	//武器の売却価格を取得
	int GetMeseta() const
	{
		return m_meseta;
	}
	//強化コスト(メセタ)を取得
	int GetCost() const
	{
		return (m_weaponextend + 1) * m_meseta * m_costmultiply;
	}
	//特殊能力の数を取得
	int GetAbilityNumber() const
	{
		return m_abilitylist.size();
	}
	//特殊能力を所持しているかどうかを取得
	bool GetisHaveAbility() const
	{
		return m_ishaveability;
	}
	//累計経験値を取得
	int GetExp() const
	{
		return m_Exp;
	}
	//仮の累計経験値を取得
	int GetKariExp() const
	{
		return m_kariExp;
	}
	//次のレベルアップに必要な経験値を取得
	int GetNextExp() const
	{
		return m_NextExp;
	}
	//次のレベルアップに必要な仮の経験値を取得
	int GetKariNextExp() const
	{
		return m_kariNextExp;
	}
	//素材にしたときの経験値を取得
	int GetMaterialExp() const
	{
		return (m_weaponextend + 1) * m_explevel1 * 0.6f;
	}
	//アビリティの合計値の値を持っているアビリティクラスのポインタを返す
	Ability* GetAbility() const
	{
		return m_ability;
	}
private:
	int m_kariExp = 0;                                    //経験値
	int m_kariNextExp = 0;                                //次のレベルアップに必要な経験値
	int m_kariLevelExp = 0;                               //レベルごとに必要な累計経験値
	int m_kariSwordMattack = 0;                           //武器の魔法攻撃力
	int m_kariSwordAttack = 0;                            //武器の攻撃力
	int m_kariweaponextend = 0;                           //武器エクステンドレベル
	int m_kariAttack = 0;							      //特殊能力や強化による最終的な仮の打撃力
	int m_kariMattack = 0;							      //特殊能力や強化による最終的な仮の法撃力
	int m_Exp = 0;                                        //経験値
	int m_NextExp = 0;                                    //次のレベルアップに必要な経験値
	int m_LevelExp = 0;                                   //レベルごとに必要な累計経験値
	int m_explevel1 = 50;						          //レベル1までに必要な経験値
	const int m_expcost = 1.5f;							  //レベルが上がるごとに必要な経験値の乗算
	const float m_exprarity = 0.3f;					      //レアリティごとにレベルアップに必要な経験値を乗算
	int m_SwordMattack = 0;                               //武器の魔法攻撃力
	int m_protSwordMattack = 0;							  //武器の初期の魔法攻撃力
	int m_SwordAttack = 0;                                //武器の攻撃力
	int m_protSwordAattack = 0;							  //武器の初期の攻撃力
	int m_Attack = 0;									  //特殊能力や強化による最終的な打撃力
	int m_Mattack = 0;									  //特殊能力や強化による最終的な法撃力
	int m_MagicId = 0;                                    //使える魔法の番号
	int m_SwordId = 0;                                    //武器の番号
	int m_Rarity = 0;                                     //武器のレアリティ
	const wchar_t* m_SwordName;                           //武器の名前
	const wchar_t* m_MagicName;						      //魔法の名前
	float m_DamageRate;									  //魔法のダメージ倍率
	int m_PPCost;                                         //魔法を放つのに必要なPP
	int m_weaponextend = 0;                               //武器エクステンドレベル
	int m_meseta = 0;									  //売却時に獲得できるメセタの額
	GameData* m_gamedata;                                 //GameDataクラスのポインタ
	Weapon* m_weapon;									  //Weaponクラスのポインタ
	Magic* m_magic;										  //Magicクラスのポインタ
	Ability* m_ability;									  //持ってるアビリティの合計値
	std::vector<Ability*> m_abilitylist;				  //アビリティクラスのポインタの可変長配列
	static const float m_multiply;						  //強化時のステータスの上昇倍率
	static const float m_costmultiply;					  //強化費用の上昇倍率
	const int m_slotlimitnumber = 3;				      //特殊能力数の上限
	bool m_ishaveability = false;						  //特殊能力を所持しているかどうか
	const int m_probability[3] = {75, 40, 20};			  //特殊能力の付与成功率
};

