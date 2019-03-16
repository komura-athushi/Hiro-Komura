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
	//受け取った数字の桁数を求める
	int digit = (int)log10((double)m_number) + 1;
	//桁数分だけ各桁の数字を求める
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
	//ダメ表記の座標にランダムに加算
	int rn = rand() % 25;
	int rn2 = rand() % 30;
	if (rn > 13) {
		m_plusposition.x += rn2 * 0.0008f + 0.01f;
	}
	else {
		m_plusposition.x -= rn2 * 0.0008f - 0.01f;
	}
	if (rn2 > 15) {
		m_plusposition.y += rn * 0.0008f + 0.01f;
	}
	else {
		m_plusposition.y -= rn * 0.0008f - 0.01f;
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
		pos += m_plusposition;
		if (0.0f <= pos.x && pos.x <= 1.0f && 0.0f <= pos.y && pos.y <= 1.0f && 0.0f <= pos.z && pos.z <= 1.0f) {
			pos.y += m_y;
			for (int i = 0; i < m_spritelist.size(); i++) {
				if (m_isred) {
					m_spritelist[i]->Draw(pos, m_scale, { 0.5f,0.5f },
						0.0f,
						{ 225.0f, 0.2f, 0.2f, m_alpha },
						DirectX::SpriteEffects_None,
						1.0f
					);
				}
				else {
					m_spritelist[i]->Draw(pos, m_scale, { 0.5f,0.5f },
						0.0f,
						{ 1.0f, 1.0f, 1.0f, m_alpha },
						DirectX::SpriteEffects_None,
						1.0f
					);
				}
				pos.x += m_addx;
			}
		}
	}
}

