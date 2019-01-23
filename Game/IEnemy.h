#pragma once
#include "Weapon.h"
#include "Material.h"
//エネミーの基本クラスです
//HPやドロップ、削除の処理などはこのクラスで処理します
class IEnemy : public IGameObject
{
public:

	/*!
	* @brief	IEnemyのコンストラクタ
	* int h     HPを設定
	* int a     Attackを設定
	* int e     撃破時の経験値を設定
	* int dropchances[]  ドロップするアイテムのレア度と確率
	* int dropmaterialchances[]  ドロップする素材のレア度と確率
	*/
	IEnemy(const int& h,const int& a,const int& e,const int dropchances[Weapon::m_HighestRarity],const int dropmaterialchances[Material::m_HighestRarity]);
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
	void Damage(const int& attack,int number=0);
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
	//エネミーのポジションを取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//エネミーのコリジョンの座標を取得
	CVector3 GetCollisionPosition() const
	{
		return m_collisionposition;
	}
	//文字表示
	void PostRender()override;
protected:
	SuicideObj::CCollisionObj* m_collision;                   //丸いコリジョン
	CVector3 m_position;									  //座標
	CVector3 m_collisionposition;
	CVector3 m_fontposition;
	//エネミーの色々なステータス
	int m_MaxHP;                                              //最大HP
	int m_HP;                                                 //HP
	int m_MaxPP;                                              //最大PP
	int m_PP;                                                 //PP
	int m_Attack;                                             //攻撃力
	int m_damagecount;										  //受けたダメージ
	int m_Exp;                                                //経験値
	int m_timer = 0;                                          //当たり判定にクールタイム
	int m_timer1 = 0;										  //フォイエの当たり判定のクールタイム
	int m_timer2 = 0;										  //イルグランツの
	int m_timer3 = 0;									      //ザンバースの
	int m_timer5 = 0;										  //マジスフィの
	int m_fonttimer = 0;									  //文字表示のタイマー
	bool m_damage = false;                                    //ダメージを受けたかどうか
	bool m_death = false;                                     //HPが0以下になったかどうか
	bool m_displayfont = false;								  //ダメ表示するかどうか
	CFont m_font;                                             //文字表示クラス
	int m_dropChances[Weapon::m_HighestRarity];			      //エネミーのドロップするアイテム、[1]が0.4fならレア度1が40%でドロップするみたいな
	int m_dropmaterialChances[Material::m_HighestRarity];	  //エネミーのドロップする素材の確率
};

