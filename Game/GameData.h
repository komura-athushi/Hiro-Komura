#pragma once
#include "Weapon.h"
#include "Magic.h"
#include "Material.h"
#include "Equipment.h"
class Enemy;
//データクラスのインスタンスを生成するクラスです
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
		enWeapon_BlueLightSword,						//クリスタルエッジ
		enWeapon_BattleReadyBlade,					    //バトルブレード
		enWeapon_AncientWarriorBlade,					//バンデッドソード
		enWeapon_LegendalySword,						//レジェンダリーソード
		enWeapon_num									//ウェポンの種類
	};
	enum EnMagic {
		enMagic_Zangeki,								//無し
		enMagic_Fire,									//フォイエ
		enMagic_Ice,									//イル・グランツ
		enMagic_Wind,									//ザンバース
		enMagic_SuperZangeki,							//シフタ
		enMagic_TwincleStar,							//マジックスフィア
		enMagic_1,										
		enMagic_2,
		enMagic_3,
		enMagic_num										//魔法の種類
	};
	enum EnMaterial {
		enMaterial_Wood,								//木
		enMaterial_Ishi,								//石
		enMaterial_Brick,								//レンガ
		enMaterial_num									//素材の種類
	};
private:
	std::vector<Weapon> m_weaponlist;                   //Weaponクラスの可変長配列
	std::vector<Magic> m_magiclist;						//Magicクラスの可変長配列
	std::vector<Material> m_materiallist;				//Materialクラスの可変長配列
	std::vector<Equipment> m_equipmentlist;				//Equipmentクラスの可変長配列
};

