#pragma once
#include "Weapon.h"
#include "Magic.h"
#include "Material.h"
#include "Ability.h"
class Enemy;
//ゲームの色々なデータを持っているクラスです
class GameData:public IGameObject
{
	//シングルトン、そのクラスのインスタンスが一つしか存在しえないことを示すデザインパターンの一つです
private:
	//コンストラクタとデストラクタをprivateに宣言することで外部から生成出来なくする
	GameData();
	~GameData();
public:
	//この関数を使ってGameDataクラスのインスタンスを生成します
	//この関数内のローカルな静的変数は最初に関数が呼ばれるときには初期化されますが、以降呼ばれる時は初期化されません
	static GameData& GetInstance() 
	{
		//privateなコンストラクタを呼び出す
		static GameData inst;
		return inst;
	}
public:
	bool Start() override;
	void Update() override;
	//武器Lvの解放段階を進めれるかどうか
	bool GetisUpWeaponLimitStage() const; 
	//引数の番号の武器のポインタを取得
	Weapon* GetWeapon(const int& number) 
	{
		return &m_weaponlist[number];
	}
	//引数の番号の魔法のポインタを取得
	Magic* GetMagic(const int& number)
	{
		return &m_magiclist[number];
	}
	//引数の番号の素材のポインタを取得
	Material* GetMaterial(const int& number)
	{
		return &m_materiallist[number];
	}
	//引数のレアリティの素材のポインタを取得
	Material* GetRarityMaterial(const int& number)
	{
		return &m_materiallist[number - 1];
	}
	//ステージをクリア
	void SetClear(const int& number)
	{
		m_stage[number] = true;
	}
	//該当のステージをクリア済みかどうか
	bool GetStageClear(const int& number)
	{
		return m_stage[number];
	}
	//街の発展レベルを取得
	int GetTownLevel() const
	{
		return m_townlevel;
	}
	//街の発展レベルをうぴー
	void UpTownLevel()
	{
		m_townlevel++;
	}
	//ゲームをクリアしたかどうか
	bool GetisGameClear()
	{
		return m_isgameclear;
	}
	//ゲームクリア！
	void SetGameClear()
	{
		m_isgameclear = true;
	}
	//ゲームが一旦終わったかどうか
	bool GetisGameEnd()
	{
		return m_isgameend;
	}
	//ゲームを一旦終わる
	void SetGameEnd()
	{
		m_isgameend = true;
	}
	//該当のアビリティのポインタを取得
	Ability* GetAbility(const int& number)
	{
		return m_abilitylist[number];
	}
	//アビリティクラスの可変長配列の長さを取得
	int GetAbilityListNumber() const
	{
		return m_abilitylist.size();
	}
	//該当の番号の数字のCSpriteクラスのポインタを返す
	CSprite* GetCSprite(const int& number)
	{
		return m_numberspritelist[number];
	}
	//特殊能力のウェイトの合計値を取得
	int GetTotalWeight() const
	{
		return m_totalabilityweight;
	}
	//特殊能力の引数のグループのウェイトの合計値を取得
	int GetTotalGroupWeight(const int& group) const
	{
		return m_totalabilitygroupweightlist[group - 1];
	}
	//魔法の撃たれた数を加算
	void PlusMagicNumber()
	{
		m_magicnumber++;
	}
	//魔法の撃たれた数を取得
	int GetMagicNumber() const
	{
		return m_magicnumber;
	}
	//武器Lvの解放段階を取得
	int GetWeaponLimitStage() const
	{
		return m_weaponlimitstage;
	}
	//武器Lvの解放段階を進める
	void UpWeaponLimitStage()
	{
		m_weaponlimitstage++;
	}
	//武器Lvの上限解放に必要な素材の種類を取得
	int GetWeaponLimitStageMaterialType() const
	{
		return m_weaponlimitstagematerialtype[m_weaponlimitstage - 1];
	}
	//武器のLv上限を取得
	int GetWeaponLimitLv() const
	{
		return m_limitweaponlv[m_weaponlimitstage - 1];
	}
	//次の武器のLv上限を取得
	int GetNextWeaponLimitLv() const
	{
		return m_limitweaponlv[m_weaponlimitstage];
	}
	/*!
	@brief	MaterialNumer
	*int limitstage;					 武器の解放段階(1ならば解放段階が1の時に必要なる、初期段階は1)
	*int s_rarity;				   素材レアリティ
	*int s_number;						  素材の必要数
	*/
	struct MaterialNumber {
		int s_llimitstage;							   //武器の解放段階(1ならば解放段階を1にする時に必要なる、初期段階は0)
		int s_rarity;								   //素材レアリティ
		int s_number;								   //素材の必要数
	};
	//該当の構造体を取得
	MaterialNumber* GetMaterialNumber(const int& number) const
	{
		return m_weaponreleaserequirednumber[number];
	}
	//武器
	enum EnWeapon {
		enWeapon_Sword,									//ソード
		enWeapon_FireSword,								//ファイアソード
		enWeapon_IceSword,								//アイスソード
		enWeapon_WindSword,								//ウィンドソード
		enWeapon_GreatSword,							//グレイトソード
		enWeapon_BlueLightSword,						//クリスタルエッジ
		enWeapon_BattleReadyBlade,					    //バトルブレード
		enWeapon_AncientWarriorBlade,					//バンデッドソード
		enWeapon_LegendalySword,						//レジェンダリーソード
		enWeapon_num									//ウェポンの種類
	};
	//魔法
	enum EnMagic {
		enMagic_Fire = 1,								//フォイエ
		enMagic_Ice,									//イル・グランツ
		enMagic_Wind,									//ザンバース
		enMagic_Shihuta,							    //シフタ
		enMagic_MagicSphere,							//マジックスフィア
		enMagic_Heal,									//ヒール								
		enMagic_Haouzan,								//覇王斬
		enMagic_ExcaliburMorgan,						//エクスカリバーモルガン
		enMagic_num										//魔法の種類
	};
	//素材
	enum EnMaterial {
		enMaterial_Wood,								//木
		enMaterial_Ishi,								//石
		enMaterial_Brick,								//レンガ
		enMaterial_num									//素材の種類
	};
	static const int m_stagenumber = 3;					//ステージ数
private:
	std::vector<Weapon> m_weaponlist;                   //Weaponクラスの可変長配列
	std::vector<Magic> m_magiclist;						//Magicクラスの可変長配列
	std::vector<Material> m_materiallist;				//Materialクラスの可変長配列
	std::vector<Ability*> m_abilitylist;				//アビリティクラスの可変長配列
	std::vector<CSprite*> m_numberspritelist;           //数字の画像の可変長配列
	std::vector<const wchar_t*> m_filepathlist;			//数字の画像のファイルパスの可変長配列
	bool m_stage[3] = { false,false,false };			//各ステージをクリアしたかどうか
	int m_townlevel = 0;								//街の発展レベル
	bool m_isgameclear = false;							//ゲームをクリアしたかどうか
	bool m_isgameend = false;							//ゲームが一旦終わったかどうか
	int m_totalabilityweight = 0;						//全アビリティのウェイトの合計値
	int m_abilitygroupnumber = 0;						//アビリティのグループの数
	std::vector<int> m_totalabilitygroupweightlist;		//アビリティのグループごとにウェイトの合計値
	int m_magicnumber = 0;								//撃たれた魔法の数
	int m_weaponlimitstage = 1;							//武器Lvの上限解放段階
	int m_weaponlimit = 0;						//武器の上限解放段階の上限
	const int m_limitweaponlv[4] = { 7, 12, 16, 20};            
	std::vector<MaterialNumber*>  m_weaponreleaserequirednumber;		//各武器の上限解放に必要な素材とその数
	std::vector<int> m_weaponlimitstagematerialtype;					//各武器の上限解放に必要な素材の種類

};

