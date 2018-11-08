#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
	delete m_camera;
}
bool GameCamera::Start()
{
	//PerspectiveCameraクラス(奥行のあるカメラ)を生成し、メインカメラに設定
	m_camera = new GameObj::PerspectiveCamera;
	m_camera->SetPos(m_position);
	m_camera->SetNear(1.0f);
	m_camera->SetFar(20000.0f);
	SetMainCamera(m_camera);
	return true;
}
void GameCamera::Update()
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
	m_degreexz += m_sdegreexz;
	m_degreey += m_sdegreey;
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
	m_target -= toPos;
	/*m_target.y = m_playerposition.y;
	m_target.y += 140.0f;*/
}