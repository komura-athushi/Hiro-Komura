#pragma once
#include "GameData.h"
#include "Equipment.h"
//プレイヤーのステータスを管理するクラスです
class PlayerStatus:public IGameObject
{
	//シングルトン、そのクラスのインスタンスが一つしか存在しえないことを示すデザインパターンの一つです
	//コンストラクタをprivateな関数にすることでインスタンスの生成を制限します
	private:
	PlayerStatus();
	~PlayerStatus();
public:
	//この関数を使ってPlayerStatusクラスのインスタンスを生成します
	//この関数内のローカルな静的変数は最初に関数が呼ばれるときには初期化されますが、以降呼ばれる時は初期化されません
	static PlayerStatus& GetInstance()
	{
		static PlayerStatus inst;
		return inst;
	}
public:
	bool Start();
	void Update();
	//武器のステータスを設定
	void SetWeaponStatus();
	//魔法のステータスを設定
	void SetMagicStatus();
	//武器切り替えの際に武器の切り替えが出来ればtrue、出来なければfalseを返す
	bool GetWeapon(int number);
	//経験値を加算
	void PlusExp(const int& exp);
	//指定の番号の武器をプレイヤーに所持させる
	void SetWeapon(Equipment* number);
	//文字表示
	void PostRender()override;
	//該当の武器の強化費用より所持メセタが多い場合、武器の強化を実行します
	void WeaponStrengthen(const int& number);
	//該当の番号の武器を削除
	void DeleteEquipment(const int& number);
	//武器強化によるステータスを更新
	void SetStatus();
	//GameDataクラスのインスタンスのポインタを設定
	void SetGameData(GameData* gamedata)
	{
		m_gamedata = gamedata;
	}
	//レベルを取得
	int GetLevel() const
	{
		return m_Level;
	}
	//最大HPを取得
	int GetMaxHP() const
	{
		return m_MaxHP * (1 + 0.01f * float(m_ability->GetHP()));
	}
	//最大PPを取得
	int GetMaxPP() const
	{
		return m_MaxPP * (1 + 0.01f * float(m_ability->GetPP()));
	}
	//攻撃力を取得
	int GetAttack() const
	{
		return m_Attack * (1 + 0.01f * float(m_ability->GetPower()));
	}
	//魔法攻撃力を取得
	int GetMattack() const
	{
		return m_Mattack * (1 + 0.01f * float(m_ability->GetMpower()));
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
	//装備している武器の番号を取得
	int GetSwordId() const
	{
		return m_SwordId;
	}
	//装備している武器の番号を取得
	const wchar_t* GetSwordName() const
	{
		return m_SwordName;
	}
	//レベルを設定
	void SetLevel(const int& level) 
	{
		m_Level = level;
	}
	//レベルアップしたかどうかを取得
	bool GetLevelUp() const
	{
		return m_levelup;
	}
	//レベルアップをfalseにする
	void OffLevelUp()
	{
		m_levelup = false;
	}
	//指定の番号の素材をプレイヤーに所持させる
	void SetMaterial(const int& number)
	{
		m_havemateriallist[number] += 1;
	}
	//魔法の番号を取得
	const wchar_t* GetMagicName() const
	{
		return m_MagicName;
	}
	//魔法のダメージ倍率を取得
	float GetDamageRate() const
	{
		return m_DamageRate;
	}
	//魔法のPP消費量を取得
	int GetPPCost() const
	{
		return m_PPCost;
	}
	//該当の素材の所持数を取得
	int GetMaterial(const int& number) const
	{
		return m_havemateriallist[number];
	}
	//該当の素材を指定数だけ減らす
	void CutMateial(const int& number,const int& amount)
	{
		m_havemateriallist[number] -= amount;
	}
	//現在装備中の武器の強化レベルを取得
	int GetWeaponLv()
	{
		return m_equipmentlist[m_SwordId]->GetLv();
	}
	//所持中のメセタの額を取得
	int GetHaveMeseta() const
	{
		return m_havemeseta;
	}
	//引数より所持メセタが多いかどうかを返す
	bool isManyMeseta(const int& meseta) 
	{
		return m_havemeseta >= meseta;
	}
	//引数分のメセタをプレイヤーのメセタに加算
	void AddMeseta(const int& meseta) 
	{
		m_havemeseta += meseta;
		if (m_havemeseta > 99999) {
			m_havemeseta = 99999;
		}
	}
	//引数文のメセタをプレイヤーのメセタから減産
	void CutMeseta(const int& meseta)
	{
		m_havemeseta -= meseta;
	}
	//該当のEquipmentクラスのインスタンスにアクセス
	Equipment* GetEuipment(const int& number) const
	{
		return m_equipmentlist[number];
	}
	//所持武器の個数
	int GetEquipmentNumber() const
	{
		return m_equipmentlist.size();
	}
	//画像の読み込むフォルダの名前
	const wchar_t* GetSpriteName(const int& number) const
	{
		return m_spritenamelist[number];
	}
	//配列の添え字の武器の番号を取得
	int GetWeaponNumber(const int& number) const
	{
		return m_equipmentlist[number]->GetId();
	}
	//プレイヤーの力を取得
	int GetPower() const
	{
		return m_Power;
	}
	//プレイヤーの賢さを取得
	int GetClever() const
	{
		return m_Clever;
	}
	//武器の打撃力を取得
	int GetWeaponAttack() const
	{
		return m_SwordAttack;
	}
	//武器の法撃力を取得
	int GetWeaponMattack() const
	{
		return m_SwordMattack;
	}
	//該当の番号の武器を装備しているかどうかを取得
	bool GetisEquippedto(const int& number) const
	{
		return m_SwordId == number;
	}
private:  
	int m_Level = 1;                                      //レベル
	int m_Exp = 0;                                        //経験値
	int m_NextExp = 40;                                   //次のレベルアップに必要な経験値
	int m_LevelExp = 40;                                  //レベルごとに必要な累計経験値
	int m_MaxHP = 65;                                    //最大HP
	int m_MaxPP = 100;                                    //最大PP(魔法撃つのに必要)
	int m_Mattack = 40;                                   //魔法攻撃力(賢さ+武器の魔法攻撃力)
	int m_Clever = 20;                                    //賢さ
	int m_SwordMattack = 10;                              //武器の魔法攻撃力
	int m_Attack = 40;                                    //攻撃力(力＋武器の攻撃力)
	int m_Power = 20;                                     //力
	int m_SwordAttack = 10;                               //武器の攻撃力
	int m_MagicId = 0;                                    //使える魔法の番号
	int m_SwordId = 0;                                    //装備中の武器の番号
	int m_Rarity = 0;                                     //装備中の武器のレアリティ
	const wchar_t* m_SwordName;                           //装備中の武器の名前
	const wchar_t* m_MagicName;						      //魔法の名前
	float m_DamageRate;									  //魔法のダメージ倍率
	int m_PPCost;										  //魔法を放つのに必要なPP
	bool m_levelup = false;
	CFont m_font;                                         //文字表示クラス
	CSprite m_cursor;									  //武器のカーソル
	CVector3 m_scale = { 0.1f,0.1f,0.1f };				  //画像の大きさ
	CVector2 m_position = { 350.0f+64.0f*6,670.0f };      //画像の位置
	std::vector<Equipment*> m_equipmentlist;              //Equipment構造体の配列
	std::vector<CSprite*> m_spritelist;				      //画像の配列
	std::vector<const wchar_t*> m_spritenamelist;		  //画像の名前
	int m_havemateriallist[GameData::enMaterial_num] = { 0,0,0 };      //プレイヤーの各素材の所持状況
	int m_havemeseta = 0;								  //所持しているメセタの額
	GameData* m_gamedata;                                 //GameDataクラスのポインタ
	Weapon* m_weapon;									  //Weaponクラスのポインタ
	Magic* m_magic;										  //Magicクラスのポインタ
	Ability* m_ability;
	const int m_ProtHP = 65;
	const int m_ProtPP = 100;
	const int m_ProtPower = 20;
	const int m_ProtMpower = 20;
};