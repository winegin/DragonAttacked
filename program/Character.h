#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	プレイヤークラス
//---------------------------------------------------------------------------------
class Character : public Base
{
public:
	//character animation
	int pos_x;
	int pos_y;
	int image[3];
	int image2[3];
	int index;
	int time;
	int face;
	//skills effect
	int warp_skill;
	int portal_image;
	int warpX;
	int warpY;
	float portal_size;
	int portal_change;
	void Init();		//	初期化処理
	void Update(int mouseX, int mouseY);		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
