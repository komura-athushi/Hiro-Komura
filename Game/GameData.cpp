#include "stdafx.h"
#include "GameData.h"

GameData::GameData()
{
}

GameData::~GameData()
{
}

bool GameData::Start()
{
	//�R���X�g���N�^���g���Ċe�f�[�^�N���X�̐�������сA�e�X�e�[�^�X�̐ݒ�����܂�
	//Weapon�N���X�̃C���X�^���X�𐶐�
	m_weaponlist.push_back(Weapon(0 , L"�������X���b�V��"		, 1, 10, 20, 0,  100));
	m_weaponlist.push_back(Weapon(1 , L"�t�@�C�A�\�[�h"			, 2, 30, 40, 1,  500));
	m_weaponlist.push_back(Weapon(2 , L"�A�C�X�\�[�h"			, 2, 30, 40, 2,  500));
	m_weaponlist.push_back(Weapon(3 , L"�E�B���h�\�[�h"			, 2, 30, 40, 3,  500));
	m_weaponlist.push_back(Weapon(4 , L"�O���C�g�\�[�h"			, 3, 50, 50, 4, 1000));
	m_weaponlist.push_back(Weapon(5 , L"�N���X�^���G�b�W"		, 4, 60, 70, 5, 1500));
	m_weaponlist.push_back(Weapon(6 , L"�o�g���u���[�h"         , 5, 80, 80, 6, 2000));
	m_weaponlist.push_back(Weapon(7 , L"�o���f�b�h�\�[�h"       , 6,120, 70, 7, 5000));
	m_weaponlist.push_back(Weapon(8 , L"�G�N�X�J���o�[�����K��" , 7,150,150, 8,10000));
	//Magic�N���X�̃C���X�^���X�𐶐�
	m_magiclist.push_back(Magic(0 , L"����"					    , 0.0f,999));
	m_magiclist.push_back(Magic(1 , L"�t�H�C�G"		  	        , 1.7f, 40));
	m_magiclist.push_back(Magic(2 , L"�C���E�O�����c"			, 1.9f, 40));
	m_magiclist.push_back(Magic(3 , L"�U���o�[�X"				, 1.6f, 40));
	m_magiclist.push_back(Magic(4 , L"�V�t�^"					, 0.0f, 50));
	m_magiclist.push_back(Magic(5 , L"�}�W�b�N�X�t�B�A"		    , 2.3f, 60));
	m_magiclist.push_back(Magic(6 , L"�}�W�b�N�X�t�B�A"         , 2.3f, 60));
	m_magiclist.push_back(Magic(7 , L"�}�W�b�N�X�t�B�A"         , 2.3f, 60));
	m_magiclist.push_back(Magic(8 , L"�}�W�b�N�X�t�B�A"         , 2.3f, 60));
	//Material�N���X�̃C���X�^���X�𐶐�
	m_materiallist.push_back(Material(L"��"					, 1));
	m_materiallist.push_back(Material(L"��"					, 2));
	m_materiallist.push_back(Material(L"�����K"				, 3));

	return true;
}

void GameData::Update()
{

}
