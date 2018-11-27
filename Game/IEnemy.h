#pragma once
#include "Weapon.h"
class IEnemy : public IGameObject
{
public:

	/*!
	* @brief	IEnemyのコンストラクタ
	* int h     HPを設定
	* int a     Attackを設定
	* int e     撃破時の経験値を設定
	* int dropchances[]  ドロップするアイテムのレア度と確率、今んとこレア度0～3
	*/
	IEnemy(const int& h,const int& a,const int& e, const int dropchances[Weapon::m_HighestRarity]);
	virtual ~IEnemy();
	/*!
	* @brief	コリジョンの生成。
	* CVector3 pos   コリジョンの座標
	* float l        コリジョンの座標のyをlだけ加算する
	* float r        コリジョンの半径
	*/
    void CCollision(const CVector3& pos,const float& l,const float& r);

	/*!
	* @brief	コリジョンの移動。
	* CVector3 pos    コリジョンの座標
	* float l        コリジョンのy座標をlだけ加算      
	*/
	void SetCCollision(const CVector3& pos,const float& l);
	//プレイヤーがエネミーにダメージを与える時の処理
	void Damage(const int& attack);
	//ドロップするアイテムの処理
	void Drop();
	//エネミーのHPが0を切ったかどうか
	bool GetDeath()
	{
		return m_death;
	}
	//エネミーの所持している経験値を返す
	int GetExp()
	{
		return m_Exp;
	}
	//文字表示
	void PostRender()override;
protected:
	SuicideObj::CCollisionObj* m_collision;                      //丸いコリジョン
	//エネミーの色々なステータス
	int m_MaxHP;                                              //最大HP
	int m_HP;                                                 //HP
	int m_MaxPP;                                              //最大PP
	int m_PP;                                                 //PP
	int m_Attack;                                             //攻撃力
	int m_Exp;                                                //経験値
	int m_timer = 0;                                          //当たり判定にクールタイム
	bool m_damage = false;                                    //ダメージを受けたかどうか
	bool m_death = false;                                     //HPが0以下になったかどうか
	CFont m_font;                                             //文字表示クラス
	int m_dropChances[Weapon::m_HighestRarity];			      //エネミーのドロップするアイテム、[1]が0.4fならレア度1が40%でドロップするみたいな
};

