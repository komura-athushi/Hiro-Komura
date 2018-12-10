#pragma once
//素材のデータクラスです
class Material
{
public:
	/*!
	@brief	Materialのコンストラクタ
	*const wchar_t* name;					//素材の名前
	*int rarity      //素材のレアリティ
	*/
	Material(const wchar_t* name, int rarity);
	Material();
	~Material();
	//素材の名前を取得
	const wchar_t* GetMaterialName()
	{
		return m_name;
	}
	//素材のレアリティを取得
	int GetRarity() const
	{
		return m_rarity;
	}
private:
	const wchar_t* m_name;					//素材の名前
	int m_rarity;							//素材のレアリティ
};

/*
暫定的な素材のレアリティと番号と名前
0
わら                 0
土					 1
1
石材			     2
*/