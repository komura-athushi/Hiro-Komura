#pragma once
class IEnemy;
//プレイヤーの放つ呪文のクラスです
class ShotMagic:public IGameObject
{
public:
	ShotMagic();
	/*!
	@brief	ShotMagicのコンストラクタ
	*int id;							//魔法の番号
	*const wchar_t* name;					//魔法の名前
	*int damageRate;						//魔法のダメージ倍率
	*int ppCost;							//魔法を放つのに必要なPP
	*/
	ShotMagic(const int& id, const wchar_t* name, const float& damageRate, const int& ppCost);
	//コピーコンストラクタ
	ShotMagic(const ShotMagic& magic);
	~ShotMagic();
	bool Start();
	void Update();
	/*!
	//コリジョンとモデルを設定、座標とコリジョンの大きさ
	@brief	魔法のモデルをコリジョンを生成します
	*CVector3 pos;					//座標
	*float scale;					//コリジョンの大きさ
	*int id;						//魔法の番号
	*int number						//ダメージ無しの時にいる 
	*bool damage;					//trueでダメージありのコリジョンを生成します
	*/
	void SetCollisionModel(const CVector3& pos, const float& scale,const int& id,const int& number=0,bool damage = true); //こ↑こ↓をfalseにするとダメージ無しのコリジョンを生成します
	/*!
	//ダメ無しコリジョンを発生させたい場合はこっち
	//コリジョンとモデルを設定、座標とコリジョンの大きさ
	@brief	魔法のモデルをコリジョンを生成します
	*CVector3 pos;					//座標
	*float scale;					//コリジョンの大きさ
	*int id;						//魔法の番号
	*int number						//m_modelcountを代入してください
	*bool damage;					//trueでダメージありのコリジョンを生成します
	*/
	void SetCollisionModelnoDamage(const CVector3& pos, const float& scale, const int& id, const int& number = 0, bool damage = true);
	//フォイエ
	void Foie();
	void FoieUpdate();
	//イルグラ
	void Irugra();
	void IrugraUpdate();
	//ザンバース
	void Zanbas();
	void ZanbasUpdate();
	//シフタ
	void Shihuta();
	void ShihutaUpdate();
	//マジックスフィア
	void MagicSphere();
	void MagicSphereUpdate();
	//魔法の番号を取得
	int GetId() const
	{
		return m_id;
	}
	//魔法の名前を取得
	const wchar_t* GetName() const
	{
		return m_name;
	}
	//魔法のダメージ倍率を取得
	float GetDamageRate() const
	{
		return m_damageRate;
	}
	//魔法のPPコストを取得
	int GetPPCost() const
	{
		return m_ppCost;
	}
	//魔法の番号を設定
	void SetId(const int& id) 
	{
		m_id = id;
	}
	//座標を設定
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	//移動速度を設定
	void SetMoveSpeed(const CVector3& movespeed)
	{
		m_movespeed = movespeed;
	}
	//大きさを設定
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//ダメージを設定
	void SetDamage(const int& mattack, const float& damagerate)
	{
		m_damage = int(mattack*damagerate);
	}
	//ダメージを取得
	int GetDamage()
	{
		return m_damage;
	}
	//プレイヤーの向きを設定
	void SetDirectionPlayer(const CVector3& pos)
	{
		m_directionplayer = pos;
	}
	//該当の番号のMagicModelの配列の座標を取得
	CVector3 GetPosition(const int& number)
	{
		return m_magicmocelList[number].s_position;
	}
	//該当の番号のMagicModelの配列の色々を削除
	void DeleteMagicModel(const int& number);

private:
	int m_id;											//魔法の番号
	const wchar_t* m_name;								//魔法の名前
	float m_damageRate;									//魔法のダメージ倍率
	int m_ppCost;										//魔法を放つのに必要なPP
	CVector3 m_scale{ CVector3::One() };				//エフェクトの大きさ
	CVector3 m_position{ CVector3::Zero() };            //エフェクトの座標
	CVector3 m_movespeed{ CVector3::Zero() };			//エフェクトの移動速度
	CVector3 m_directionplayer{ CVector3::Zero() };		//プレイヤーの向きに平行なベクトル
	int m_damage;										//当たった場合にエネミーに与えるダメージ
	float m_deletetime = 0;								//魔法を消すまでの時間
	SuicideObj::CCollisionObj* m_collision;		        //丸いコリジョン
	int m_modelnumber = 0;								//モデルの数
	int m_modelcount = 0;								//生成したモデルの数
	int m_timer = 0;									//複数のモデルとコリジョンを時間差ありで生成する場合のクールタイム
	int m_timer1 = 0;
	//スキンモデル、コリジョン、タイマー、削除したかどうか
	struct MagicModel {
		GameObj::CSkinModelRender* s_skinModelReder;    //モデル
		SuicideObj::CCollisionObj* s_collision;			//コリジョン
		float s_timer = 0.0f;							//デリートタイム
		CVector3 s_position = {CVector3::Zero()};		//座標
		bool s_delete = false;							//モデルとコリジョンを削除したかどうか
		int s_number = 0;								//配列の添え字
	};
	std::vector<MagicModel> m_magicmocelList;			//MagicModel構造体の可変長配列
	static const int m_number[];
};

