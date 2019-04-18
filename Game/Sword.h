#pragma once
class Player;
//プレイヤーが装備している武器のデータです
class Sword:public IGameObject
{
public:
	Sword();
	~Sword();
	bool Start() override;
	void Update() override;
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//回転を設定
	void SetRot(const CQuaternion& rot)
	{
		m_qRot = rot;
	}
	//大きさを設定
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//武器の番号を設定
	void SetSwordId(const int& id) 
	{
		m_SwordId2 = id;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	Player* m_player = nullptr;									//プレイヤークラスのポインタ
	CVector3 m_position = CVector3::Zero();                     //座標
	CVector3 m_scale = CVector3::One();                         //大きさ
	CQuaternion m_qRot;                                         //クォータニオン
	int m_SwordId = 0;                                          //武器の番号
	int m_SwordId2 = 0;                                         //切り替え予定の武器の番号
	bool m_delete = true;                                       //武器を切り替える前に装備している武器を削除しているかどうか
	bool m_switch = false;										//武器切り替えをするかどうか
};

