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
	void Base();
	void Material();
	void Decision();
	void Upgrade();
	//Bボタンでステートを一つ前の状態に戻す
	void BackState();
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
		if (m_state == enState_Free) {
			m_state=enState_Base;
		}
	}
	//トーク状態をオフ
	void OffTalk()
	{
		m_state = enState_Free;
	}
	//トーク状態かどうかを取得
	bool GetTalk() const
	{
		return m_state != enState_Free;
	}
	//ベース選択時かどうかを取得
	bool GetBase() const
	{
		return m_state == enState_Base;
	}
	//アイドル状態かどうかを取得
	bool GetIdle() const
	{
		return m_state == enState_Free;
	}
private:
	enum State {
		enState_Free,                               //何もしてない状態
		enState_Base,								//ベースを選択
		enState_Material,							//素材を選択
		enState_Decision,							//強化するかどうかを決定
		enState_Upgrade,							//強化終わり、結果を表示
	};
	State m_state = enState_Free;
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero();
	CVector2 m_aiconposition = { 800.0f,50.0f+70.0f*4 };	    //画像の位置;
	CVector3 m_aiconscale = { 0.15f,0.15f,0.15f };
	CVector3 m_scale = { 0.8f,0.8f,0.8f };
	CQuaternion m_rotation = CQuaternion::Identity();
	CSprite m_sprite2,m_sprite3;
	CSprite m_equipment, m_base;							    //装備中表示とベース表示
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
	int m_swordid1 =0, m_swordid2 =0, m_swordid3 =0;              //それぞれプレイヤーが装備している武器の番号、ベースの番号、素材の番号である
	bool m_button = false;
	int m_equipmentnumber = 0;
	CSprite m_basesprite, m_materialsprite, m_upgradesprite;      //それぞれベース、素材、強化結果の武器のスプライトである
	CSprite m_mesetasprite;
	CSprite m_back;												  //強化の時に武器のバックに表示する画像
	bool m_isspriteInit = false;								  //上記の画像の読み込みが終わったかどうか
	int m_level = 0;
	bool m_isstrength = false;									  //武器の強化ができるかどうか
	const float m_sevolume = 2.0f;
};

