#include "stdafx.h"
#include "GameData.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Magic.h"
GameData::GameData()
{
}


GameData::~GameData()
{
}

bool GameData::Start()
{
	m_weapons = new Weapon[6]{
		Weapon(0 ,"ソード"                ,0  ,10 ,20 ,0),
		Weapon(1 ,"ファイアソード"        ,1  ,30 ,40 ,1),
		Weapon(2 ,"アイスソード"          ,1  ,30 ,40 ,2),
		Weapon(3 ,"ウィンドソード"        ,1  ,30 ,40 ,3),
		Weapon(4 ,"グレイトソード"        ,2  ,50 ,50 ,4),
		Weapon(5 ,"ブルーライトソード"    ,3  ,60 ,70 ,5)
	};
	m_enemies = new Enemy[2]{
		Enemy(0 ,"Bone Soldier"          ,50  ,20 ,20  ,new float[4]{0.1f,0.03f,0.0f,0.0f }),
	    Enemy(1, "ボス"                  ,500 ,40 ,400 ,new float[4]{ 0.0f,0.0f,0.2f,0.0f }),
	};
	m_magics = new Magic[6]{
		Magic(0 ,"斬撃"                  ,1.5f ,30),
		Magic(1 ,"ファイアボール"        ,1.7f ,40),
		Magic(2 ,"アイスボール"          ,1.9f ,40),
		Magic(3 ,"ウィンド"              ,1.6f ,40),
		Magic(4 ,"超斬撃"                ,2.1f ,50),
		Magic(5 ,"トゥインクルスター"    ,2.3f ,60),
	};
	return true;
}

void GameData::Update()
{

}