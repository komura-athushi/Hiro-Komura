#include "stdafx.h"
#include "Title.h"
#include "Town.h"
#include "Fade.h"
Title::Title()
{
}

Title::~Title()
{
	//newしてないのでspriteはインスタンスが破棄されたらspriteは自動的に破棄されます
	
}

bool Title::Start()
{
	//m_sprite.Init(L"Resource/sprite/Title.dds");
	m_sprite.Init(L"Resource/sprite/MokoTitle.dds");
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	return true;
}

void Title::Update()
{
	
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			Town* town = new Town;
			delete this;
		}
	}
	else {
		if (Pad(0).GetDown(enButtonStart)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}

void Title::PostRender()
{
	m_sprite.DrawScreenPos(m_position,m_scale);
}
