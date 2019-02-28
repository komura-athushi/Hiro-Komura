#pragma once
#include "GameData.h"
class Player;
class GameData;
class PlayerStatus;
class Merchant:public IGameObject
{
public:
	Merchant();
	~Merchant();
	bool Start();
	void Update();
	void PostRender() override;
	void Turn();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//回転を設定
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	//座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//トーク状態をオン
	void SetTalk()
	{
		m_talk = true;
	}
	//トーク状態をオフ
	void OffTalk()
	{
		m_talk = false;
	}
	//トーク状態かどうかを取得
	bool GetTalk() const
	{
		return m_talk;
	}
private:
	
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero();
	CVector2 m_aiconposition = { 350.0f,50.0f+70.0f*4 };	    //画像の位置;
	CVector3 m_aiconscale = { 0.15f,0.15f,0.15f };
	CVector3 m_scale = { 0.8f,0.8f,0.8f };
	CQuaternion m_rotation = CQuaternion::Identity();
	CQuaternion m_protrotation = CQuaternion::Identity();
	CFont m_font;                                               //文字表示クラス
	std::vector<CFont*> m_spritefont;					        //文字表示
	bool m_talk = false;
	CSprite m_sprite[GameData::enWeapon_num];                   //画像表示クラス
	CSprite m_cursor;
	std::vector<CSprite*> m_spritelist;				            //画像の配列
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle,
	};
	AnimationClip m_animClip[enAnimationClip_num];
	CVector2 m_spriteposition[GameData::enWeapon_num];
	Player* m_player = nullptr;
	GameData* m_gamedata;
	PlayerStatus* m_playerstatus;
	int m_swordid;
	bool m_button = false;
	int m_equipmentnumber = 0;
};

