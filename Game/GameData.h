#pragma once
#include "Weapon.h"
class Enemy;
class Magic;
class GameData:public IGameObject
{
public:
	GameData();
	~GameData();
	bool Start();
	void Update();
	//引数の番号の武器のポインタを取得
	Weapon* GetWeapon(int number) 
	{
		return &m_weaponlist[number];
	}
	enum EnWeapon {
		enWeapon_Sword,									//ソード
		enWeapon_FireSword,								//ファイアソード
		enWeapon_IceSword,								//アイスソード
		enWeapon_WindSword,								//ウィンドソード
		enWeapon_GreatSword,							//グレイトソード
		enWeapon_BlueLightSword,						//ブルーライトソード
		enWeapon_num									//ウェポンの種類
	};
	enum EnMagic {
		enMagic_Zangeki,
		enMagic_Fire,
		enMagic_Ice,
		enMagic_Wind,
		enMagic_SuperZangeki,
		enMagic_TwincleStar,
		enMagic_num
	};
private:
	std::vector<Weapon> m_weaponlist;                   //Weaponクラスの可変長配列
    Enemy* m_enemies;
	Magic* m_magics;
};

