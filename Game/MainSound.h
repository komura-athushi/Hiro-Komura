#pragma once
class MainSound:public IGameObject
{
	//シングルトン、そのクラスのインスタンスが一つしか存在しえないことを示すデザインパターンの一つです
private:
	//コンストラクタとデストラクタをprivateに宣言することで外部から生成出来なくします
	MainSound();
	~MainSound();
public:
	//この関数を使ってGameDataクラスのインスタンスを生成します
	//この関数内のローカルな静的変数は最初に関数が呼ばれるときには初期化されますが、以降呼ばれる時は初期化されません
	static MainSound& GetInstance()
	{
		//privateなコンストラクタを呼び出す
		static MainSound inst;
		return inst;
	}
	bool Start() override;
	void Update() override;
	//再生するBGMを設定します
	void SetBGM(const int& state)
	{
		m_state2 = state;
	}
	enum State {
		enBGM_Title,										//タイトル
		enBGM_Town,										    //拠点
		enBGM_Stage1,										//ステージ1
		enBGM_Stage2,										//ステージ2
		enBGM_Stage3,										//ステージ3
		enBGM_End,										    //終わり
	};
private:
	SuicideObj::CBGM* m_bgm = nullptr;
	int m_state1 = 0;										//現在再生している曲	
	int m_state2 = 0;										//再生予定の曲
};

