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
	static const int m_HighestRarity = 3;
	static const int m_raritynumber[];      //レアリティごとの素材の種類
private:
	const wchar_t* m_name;					//素材の名前
	int m_rarity;							//素材のレアリティ
};

/*
暫定的な素材のレアリティと番号と名前
1
土					0
2
石					1
3
レンガ			    2
*/