#include "stdafx.h"
#include "Title.h"
#include "Town.h"
Title::Title()
{
}

Title::~Title()
{
	//new���ĂȂ��̂�sprite�̓C���X�^���X���j�����ꂽ��sprite�͎����I�ɔj������܂�
	
}

bool Title::Start()
{
	//m_sprite.Init(L"Resource/sprite/Title.dds");
	m_sprite.Init(L"Resource/sprite/MokoTitle.dds");
	return true;
}

void Title::Update()
{
	if (Pad(0).GetDown(enButtonStart)) {
		Town* town = new Town;
		delete this;
	}
}

void Title::PostRender()
{
	m_sprite.DrawScreenPos(m_position,m_scale);
}
