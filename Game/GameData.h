#pragma once
#include "Weapon.h"
#include "Magic.h"
#include "Material.h"
class Enemy;
class GameData:public IGameObject
{
	//シングルトン、そのクラスのインスタンスが一つしか存在しえないことを示すデザインパターンの一つです
private:
	//コンストラクタとデストラクタをprivateに宣言することで外部から生成出来なくする
	GameData();
	~GameData();
public:
	//この関数を使ってGameDataクラスのインスタンスを生成します
	//この関数内のローカルな静的変数は最初に関数が呼ばれるときには初期化されますが、以降呼ばれる時は初期化されません
	static GameData& GetInstance()
	{
		//privateなコンストラクタを呼び出す
		static GameData inst;
		return inst;
	}
public:
	bool Start();
	void Update();
	//引数の番号の武器のポインタを取得
	Weapon* GetWeapon(int number) 
	{
		return &m_weaponlist[number];
	}
	//引数の番号の魔法のポインタを取得
	Magic* GetMagic(int number)
	{
		return &m_magiclist[number];
	}
	enum EnWeapon {
		enWeapon_Sword,									//ソード
		enWeapon_FireSword,								//ファイアソード
		enWeapon_IceSword,								//アイスソード
		enWeapon_WindSword,								//ウィンドソード
		enWeapon_GreatSword,							//グレイトソード
		enWeapon_BlueLightSword,						//ブルーライトソード
		enWeapon_BattleReadyBlade,
		enWeapon_AncientWarriorBlade,
		enWeapon_LegendalySword,
		enWeapon_num									//ウェポンの種類
	};
	enum EnMagic {
		enMagic_Zangeki,								//斬撃
		enMagic_Fire,									//ファイアー
		enMagic_Ice,									//アイス
		enMagic_Wind,									//ウィンド
		enMagic_SuperZangeki,							//超斬撃
		enMagic_TwincleStar,							//トゥインクルスター
		enMagic_1,
		enMagic_2,
		enMagic_3,
		enMagic_num										//魔法の種類
	};
	enum EnMaterial {
		enMaterial_Straw,								//藁(わら)
		enMaterial_Soil,								//土
		enMaterial_Stone,								//石
		enMaterial_num									//素材の種類
	};
private:
	std::vector<Weapon> m_weaponlist;                   //Weaponクラスの可変長配列
	std::vector<Magic> m_magiclist;						//Magicクラスの可変長配列
	std::vector<Material> m_materiallist;				//Materialクラスの可変長配列
    Enemy* m_enemies;
};

