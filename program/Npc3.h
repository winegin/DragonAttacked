#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	ＮＰＣクラス
//---------------------------------------------------------------------------------
class Npc3
{
public:
	int pos_x;
	int pos_y;
	int speed;
	int image[12];
	int mode;
	int spawn_posX;
	int spawn_posY;
	int time_spawn;
	int warning;
	int warning_time;
	int warning_mode;
	int image_index;
	int time_switch_image;
	void Init();		//	初期化処理
	void Update();	//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
