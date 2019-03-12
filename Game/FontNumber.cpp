#include "stdafx.h"
#include "FontNumber.h"
#include "GameData.h"
#include "GameCamera.h"
#include "Math.h"
FontNumber::FontNumber()
{
}


FontNumber::~FontNumber()
{
}

bool FontNumber::Start()
{
	m_gamedata = FindGO<GameData>(L"GameData");
	m_gamecamera = FindGO<GameCamera>();
	int nm = m_number;
	//ó‚¯æ‚Á‚½”š‚ÌŒ…”‚ğ‹‚ß‚é
	int digit = (int)log10((double)m_number) + 1;
	//Œ…”•ª‚¾‚¯ŠeŒ…‚Ì”š‚ğ‹‚ß‚é
	for (int i = 0; i < digit; i++) {
		int Divide = std::pow(10, (i + 1));
		int Divide2 = std::pow(10, i);
		int remainder = nm % Divide / Divide2;
		nm = nm - remainder * Divide2;
		m_numberlist.push_back(remainder);
	}
	for (int i = 0; i < m_numberlist.size(); i++) {
		m_spritelist.push_back(m_gamedata->GetCSprite(m_numberlist[i]));
	}
	return true;
}

void FontNumber::Update()
{
	m_timer += m_frame * GetDeltaTimeSec();
	m_alpha -= GetDeltaTimeSec() * 0.7f;
	m_y += m_addy;
	if (m_timer >= m_time) {
		delete this;
	}
}

void FontNumber::PostRender()
{
	if (m_gamecamera == nullptr) {
		m_gamecamera = FindGO<GameCamera>();
	}
	else {
		CVector3 pos = m_gamecamera->GetCamera()->CalcScreenPosFromWorldPos(m_position);
		if (0.0f <= pos.x && pos.x <= 1.0f && 0.0f <= pos.y && pos.y <= 1.0f && 0.0f <= pos.z && pos.z <= 1.0f) {
			pos.y += m_y;
			for (int i = 0; i < m_spritelist.size(); i++) {
				m_spritelist[i]->Draw(pos, m_scale, { 0.5f,0.5f },
					0.0f,
					{1.0f,1.0f,1.0f,m_alpha},
					DirectX::SpriteEffects_None,
					1.0f
				);
				pos.x += m_addx;
			}
		}
	}
}

