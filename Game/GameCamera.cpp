#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "IEnemy.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//PerspectiveCameraクラス(奥行のあるカメラ)を生成し、メインカメラに設定
	m_camera = FindGO<GameObj::PerspectiveCamera>(L"Camera");
	m_camera->SetPos(m_position);
	m_camera->SetNear(1.0f);
	m_camera->SetFar(200000.0f);
	SetMainCamera(m_camera);
	return true;
}

void GameCamera::Update()
{
	if (m_player->isCagliostro()) {
		cagliostro();
	}
	else {
		unityChan();
	}
	
}

void GameCamera::cagliostro()
{
	if (Pad(0).GetButton(enButtonUp)) {
		m_r -= 0.8f;
	}
	else if (Pad(0).GetButton(enButtonDown)) {
		m_r += 0.8f;
	}
	if (m_r <= 1.0f) {
		m_r = 1.0f;
	}
	//右スティックの入力量を取得
	CVector2 stickL;
	stickL = Pad(0).GetStick(L);
	m_topos += stickL.y * 1.0f;
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	//右スティックの入力量を取得
	CVector2 stickR;
	stickR = Pad(0).GetStick(R);
	stickR.x = -stickR.x;
	float m_sdegreexz = -stickR.x * 2.0f * 60.0f * GetDeltaTimeSec();
	float m_sdegreey = -stickR.y * 2.0f * 60.0f * GetDeltaTimeSec();
	//回転度加算
	m_degreexz += m_sdegreexz;
	m_degreey += m_sdegreey;
	//上下方向のカメラ移動を制限
	if (m_degreey >= 80.0f) {
		m_degreey = 80.0f;
	}
	if (m_degreey <= -80.0f) {
		m_degreey = -80.0f;
	}
	//角度をラジアン単位に直す
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	//注視点を設定する
	m_target = { 0.0f,0.0f,0.0f };
	m_target.y += m_topos;
	m_target += m_player->GetPosition();
	//Y軸周りに回転させる。
	CQuaternion qRot;
	qRot.SetRotation(m_axisY, m_radianx);
	//これがプレイヤーとカメラを結ぶベクトルです
	CVector3 toPos = { 0.0f, 0.0f, 1.0f };
	qRot.Multiply(toPos);
	//上下の回転。
	//まずは回す軸を計算する。
	CVector3 rotAxis;
	rotAxis.Cross(toPos, m_axisY);
	//ベクトルを正規化する。
	rotAxis.Normalize();
	qRot.SetRotation(rotAxis, m_radiany);
	qRot.Multiply(toPos);
	toPos *= m_r;
	m_position = m_target + toPos;
	toPos *= 2;
	//m_target -= toPos;
	//視点
	m_camera->SetTarget(m_target);
	//座標
	m_camera->SetPos(m_position);
}

void GameCamera::unityChan()
{
	//プレイヤーの座標を取得
	CVector3 m_playerposition = m_player->GetPosition();
	//右スティックの入力量を取得
	CVector2 stickR;
	stickR = Pad(0).GetStick(R);
	stickR.x = -stickR.x;
	float m_sdegreexz = -stickR.x * 2.0f;
	float m_sdegreey = -stickR.y * 2.0f;
	//回転度加算
	float i = m_timer - 0.0f;
	if (fabs(i) < 0.0001f) {
		m_degreexz += m_sdegreexz;
		m_degreey += m_sdegreey;
	}
	//上下方向のカメラ移動を制限
	if (m_degreey >= 40.0f) {
		m_degreey = 40.0f;
	}
	if (m_degreey <= -15.0f) {
		m_degreey = -15.0f;
	}
	//角度をラジアン単位に直す
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	Hutu();
	//視点
	m_camera->SetTarget(m_target);
	//座標
	m_camera->SetPos(m_position);
}

// 普通視点の処理 カメラの座標を移動させる、カメラの注視点をリセット
void GameCamera::Hutu()
{
	if (m_player->GetisTarget() && m_player->GetisTargetLock()) {
		m_target = m_player->GetTarget();
		m_locktarget = m_target;
		CVector3 pos = m_target - m_player->GetPosition();
		float r = pos.Length() + 200.0f;
		//float r = 160.0f;
		pos.y = 0.0f;
		pos.Normalize();
		m_position = m_target - pos * r;
		m_position.y = m_player->GetPosition().y + 200.0f;
		if (m_timer < 0.9999f) {
			//注視点を設定する
			CVector3 target = { 0.0f,0.0f,0.0f };
			target.y += 140.0f;
			target += m_player->GetPosition();
			//Y軸周りに回転させる。
			CQuaternion qRot;
			qRot.SetRotation(m_axisY, m_radianx);
			//これがプレイヤーとカメラを結ぶベクトルです
			CVector3 toPos = { 0.0f, 0.0f, 1.0f };
			qRot.Multiply(toPos);
			//上下の回転。
			//まずは回す軸を計算する。
			CVector3 rotAxis;
			rotAxis.Cross(toPos, m_axisY);
			//ベクトルを正規化する。
			rotAxis.Normalize();
			qRot.SetRotation(rotAxis, m_radiany);
			qRot.Multiply(toPos);
			toPos *= m_r;
			CVector3 position = target + toPos;
			m_position = m_position * m_timer + position * (1 - m_timer);
			m_target = m_target * m_timer + target * (1 - m_timer);
			m_timer += GetDeltaTimeSec();
			if (1.0f < m_timer) {
				m_timer = 1.0f;
			}
		}
		//ベクトルV1
		CVector3 pos2 = m_position - m_player->GetPosition();
		m_degreexz = atan2f(pos2.x, pos2.z);
		m_degreexz *= 180 / M_PI;
		//ベクトルV0
		CVector3 pos3 = pos2;
		pos3.y = 0.0f;
		pos2.Normalize();
		pos3.Normalize();
		float d = pos3.Dot(pos2);
		m_degreey = acosf(d);
		m_degreey *= 180 / M_PI;
	}
	else {
		//注視点を設定する
		m_target = { 0.0f,0.0f,0.0f };
		m_target.y += 140.0f;
		m_target += m_player->GetPosition();
		//Y軸周りに回転させる。
		CQuaternion qRot;
		qRot.SetRotation(m_axisY, m_radianx);
		//これがプレイヤーとカメラを結ぶベクトルです
		CVector3 toPos = { 0.0f, 0.0f, 1.0f };
		qRot.Multiply(toPos);
		//上下の回転。
		//まずは回す軸を計算する。
		CVector3 rotAxis;
		rotAxis.Cross(toPos, m_axisY);
		//ベクトルを正規化する。
		rotAxis.Normalize();
		qRot.SetRotation(rotAxis, m_radiany);
		qRot.Multiply(toPos);
		toPos *= m_r;
		m_position = m_target + toPos;
		toPos *= 2;
		//m_target -= toPos;
	    /*m_target.y = m_playerposition.y;
	    m_target.y += 140.0f;*/
		if (m_timer > 0.001f) {
			CVector3 target = m_locktarget;
			CVector3 pos = target - m_player->GetPosition();
			float r = pos.Length() + 200.0f;
			pos.y = 0.0f;
			pos.Normalize();
			CVector3 position = target - pos * r;
			position.y = m_player->GetPosition().y + 200.0f;
			m_position = position * m_timer + m_position * (1 - m_timer);
			m_target = target * m_timer + m_target * (1 - m_timer);
			m_timer -= GetDeltaTimeSec();
			if (m_timer < 0.0f) {
				m_timer = 0.0f;
			}
		}
	}
	m_front = m_target - m_position;
	m_front.y = 0.0f;
	m_front.Normalize();
	m_right = m_front;
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), -90.0f);
	rot.Multiply(m_right);
}

