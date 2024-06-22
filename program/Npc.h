#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	ＮＰＣクラス
//---------------------------------------------------------------------------------
class Npc
{
public:
	int pos_x;
	int pos_y;
	int speed;
	int image[12];
	int mode;
	int spawn_pos;
	int time_s;
	int time_spawn;
	int time_warp;
	int image_index;
	int time_switch_image;
	void Init(  );		//	初期化処理
	void Update(int mouseX, int mouseY);	//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
