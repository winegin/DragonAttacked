class Tower
{
public:
	int pos_x;
	int pos_y;
	int image;
	int HP;
	int Box_X;
	void Init();		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};