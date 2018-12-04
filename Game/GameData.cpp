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
	//�R���X�g���N�^���g���Ċe�f�[�^�N���X�̏��������s���܂�
	//Weapon�N���X�̃C���X�^���X�𐶐�
	m_weaponlist.push_back(Weapon(0 , L"���������X���b�V��"		, 0, 10, 20, 0));
	m_weaponlist.push_back(Weapon(1 , L"�t�@�C�A�\�[�h"			, 1, 30, 40, 1));
	m_weaponlist.push_back(Weapon(2 , L"�A�C�X�\�[�h"			, 1, 30, 40, 2));
	m_weaponlist.push_back(Weapon(3 , L"�E�B���h�\�[�h"			, 1, 30, 40, 3));
	m_weaponlist.push_back(Weapon(4 , L"�O���C�g�\�[�h"			, 2, 50, 50, 4));
	m_weaponlist.push_back(Weapon(5 , L"�N���X�^���G�b�W"		, 3, 60, 70, 5));
	//Magic�N���X�̃C���X�^���X�𐶐�
	m_magiclist.push_back(Magic(0 , L"����"					    , 0.0f,  0));
	m_magiclist.push_back(Magic(1 , L"�t�H�C�G"		  	        , 1.7f, 40));
	m_magiclist.push_back(Magic(2 , L"�C���E�O�����c"			, 1.9f, 40));
	m_magiclist.push_back(Magic(3 , L"�U���o�[�X"				, 1.6f, 40));
	m_magiclist.push_back(Magic(4 , L"�V�t�^"					, 0.0f, 50));
	m_magiclist.push_back(Magic(5 , L"�}�W�b�N�X�t�B�A"		    , 2.3f, 60));
	//Material�N���X�̃C���X�^���X�𐶐�
	m_materiallist.push_back(Material(L"�m"					, 0));
	m_materiallist.push_back(Material(L"�y"					, 0));
	m_materiallist.push_back(Material(L"�΍�"				, 1));
	return true;
}

void GameData::Update()
{

}