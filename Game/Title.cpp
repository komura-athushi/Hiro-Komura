#include "stdafx.h"
#include "Title.h"
#include "Town.h"
Title::Title()
{
}

Title::~Title()
{
	
}

bool Title::Start()
{
	m_sprite.Init(L"Resource/sprite/Title.dds");
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
	m_sprite.DrawScreenPos({ 0.0f, 0.0f },{ 1.0f,1.0f });
}
