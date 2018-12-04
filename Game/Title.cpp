#include "stdafx.h"
#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
}

bool Title::Start()
{
	m_sprite.Init(L"Resource/sprite/Red.dds");
	return true;
}

void Title::Update()
{
	
}

void Title::PostRender()
{
	m_sprite.Draw({ 0.0f, 0.0f },{ 2.0f,2.0f });
}
