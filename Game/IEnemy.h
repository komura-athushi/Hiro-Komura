#pragma once
class IEnemy : public IGameObject
{
public:
	/*!
	* @brief	IEnemyのコンストラクタ
	* int h     HPを設定
	* int a     Attackを設定
	*/
	IEnemy(int h,int a);
	virtual ~IEnemy();
	/*!
	* @brief	コリジョンの生成。
	* CVector3 pos   コリジョンの座標
	* float l        コリジョンの座標のyをlだけ加算する
	* float r        コリジョンの半径
	*/
    void CCollision(CVector3 pos,float l, float r);
	/*!
	* @brief	コリジョンの移動。
	* CVector pos    コリジョンの座標
	* float l        コリジョンのy座標をlだけ加算      
	*/
	void SetCCollision(CVector3 pos,float l);
	virtual void Update()=0;
	virtual void Attack()=0;
	void Damege(int attack);
	//void SetStatus(int h, int a);
protected:
	std::unique_ptr<GameObj::CCollisionObj> m_collision;      //丸いコリジョン
	//プレイヤーの色々なステータス
	int m_MaxHP;                                              //最大HP
	int m_HP;                                                 //HP
	int m_MaxPP;                                              //最大PP
	int m_PP;                                                 //PP
	int m_Attack;                                             //攻撃力
	int m_timer = 0;
	bool m_death = false;                                     //HPが0以下になったかどうか  
};

