#include "stdafx.h"
#include "GameData.h"
#include "Enemy.h"

GameData::GameData()
{
}


GameData::~GameData()
{
}

bool GameData::Start()
{
<<<<<<< HEAD
	m_weapons = new Weapon[6]{
		Weapon(0 ,"�\�[�h"                ,0  ,10 ,20 ,0),
		Weapon(1 ,"�t�@�C�A�\�[�h"        ,1  ,30 ,40 ,1),
		Weapon(2 ,"�A�C�X�\�[�h"          ,1  ,30 ,40 ,2),
		Weapon(3 ,"�E�B���h�\�[�h"        ,1  ,30 ,40 ,3),
		Weapon(4 ,"�O���C�g�\�[�h"        ,2  ,50 ,50 ,4),
		Weapon(5 ,"�u���[���C�g�\�[�h"    ,3  ,60 ,70 ,5)
	};
	/*m_enemies = new Enemy[2]{
		Enemy(0 ,"Bone Soldier"          ,50  ,20 ,20  ,new float[4]{0,10,0,0 }),
	    Enemy(1, "�{�X"                  ,500 ,40 ,400 ,new float[4]{ 0,0,0,0})
	};*/
	m_magics = new Magic[6]{
		Magic(0 ,"�a��"                  ,1.5f ,30),
		Magic(1 ,"�t�@�C�A�{�[��"        ,1.7f ,40),
		Magic(2 ,"�A�C�X�{�[��"          ,1.9f ,40),
		Magic(3 ,"�E�B���h"              ,1.6f ,40),
		Magic(4 ,"���a��"                ,2.1f ,50),
		Magic(5 ,"�g�D�C���N���X�^�["    ,2.3f ,60)
	};
=======
	//Weapon�N���X�̃C���X�^���X�𐶐�
	m_weaponlist.push_back(Weapon(0 , L"�\�[�h"				    , 0, 10, 20, 0));
	m_weaponlist.push_back(Weapon(1 , L"�t�@�C�A�\�[�h"			, 1, 30, 40, 1));
	m_weaponlist.push_back(Weapon(2 , L"�A�C�X�\�[�h"			, 1, 30, 40, 2));
	m_weaponlist.push_back(Weapon(3 , L"�E�B���h�\�[�h"			, 1, 30, 40, 3));
	m_weaponlist.push_back(Weapon(4 , L"�O���C�g�\�[�h"			, 2, 50, 50, 4));
	m_weaponlist.push_back(Weapon(5 , L"�N���X�^���G�b�W"		, 3, 60, 70, 5));
	//Magic�N���X�̃C���X�^���X�𐶐�
	m_magiclist.push_back(Magic(0 , L"����"					    , 0.0f, 30));
	m_magiclist.push_back(Magic(1 , L"�t�H�C�G"		  	        , 1.7f, 40));
	m_magiclist.push_back(Magic(2 , L"�C���E�O�����c"			, 1.9f, 40));
	m_magiclist.push_back(Magic(3 , L"�U���o�[�X"				, 1.6f, 40));
	m_magiclist.push_back(Magic(4 , L"�V�t�^"					, 0.0f, 50));
	m_magiclist.push_back(Magic(5 , L"�}�W�b�N�X�t�B�A"		    , 2.3f, 60));
	//Material�N���X�̃C���X�^���X�𐶐�
	m_materiallist.push_back(Material(L"�m"					, 0));
	m_materiallist.push_back(Material(L"�y"					, 0));
	m_materiallist.push_back(Material(L"�΍�"				, 1));
>>>>>>> 4621d4808865101770bd6c9e39b60f3ff6afe2b0
	return true;
}

void GameData::Update()
{

}