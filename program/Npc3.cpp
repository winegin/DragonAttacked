#include "Main.h"
#include "Game.h"
#include "Npc3.h"
#include "Hit.h"
void Npc3::Init() {
	pos_x = -30;
	pos_y = -30;
	mode = 0;
	speed = 15;
	image_index = 4;
	time_switch_image = 60;
	warning_time = 180;
	warning = LoadGraph("data/warning.png");
	LoadDivGraph("data/NPC.png", 12, 3, 4, 432 / 3, 512 / 4, image);
}
void Npc3::Update() {
	//Reset
	if (mode == 0) {
		pos_x = -130;
		pos_y = -30;
	}
	//RandomSpawnX
	if (mode == 1) {
		spawn_posX = GetRand(1);
		mode = 2;
	}
	//RandomSpawnY
	if (mode == 2) {
		spawn_posY = GetRand(2);
		mode = 3;
	}
	//SettingSpawn
	{
		if (mode == 3) {
			switch (spawn_posY) {
			case 0:
				pos_y = SCREEN_H / 2 + 150;
				break;
			case 1:
				pos_y = SCREEN_H / 2 + 0;
				break;
			case 2:
				pos_y = SCREEN_H / 2 - 150;
				break;
			}
			switch (spawn_posX) {
			case 0:
				pos_x = -130;
				image_index = 3;
				break;
			case 1:
				pos_x = SCREEN_W + 30;
				image_index = 9;
				break;
			}
			warning_time = 180;
			mode = 4;
		}

	}
	//Warning
	{
		if (mode == 4) {
			warning_time--;
			if (warning_time == 1) {
				mode = 5;
			}
		}
	}
	//Moving
	{
		if (mode == 5) {
			switch (spawn_posX) {
			case 0:
				pos_x += speed;
				break;
			case 1:
				pos_x -= speed;
				break;
			}
			if (pos_x > SCREEN_W / 2 - 225 && pos_x < SCREEN_W / 2 + 125) {
				speed = 5;
			}
			else speed = 15;
		}
	}
SettingAnimation: {
	if (mode == 5 && spawn_posX == 0)
	{
		time_switch_image-=2;
		if (time_switch_image < 0) {
			time_switch_image = 60;
		}
		if (time_switch_image % 10 == 0) {
			image_index++;
			if (image_index > 5) {
				image_index = 3;
			}
		}
	}
	if (mode == 5 && spawn_posX == 1)
	{
		time_switch_image-=2;
		if (time_switch_image < 0) {
			time_switch_image = 60;
		}
		if (time_switch_image % 10 == 0) {
			image_index++;
			if (image_index > 11) {
				image_index = 9;
			}
		}
	}
	}
}
void Npc3::Render() {
	if (mode == 4&&spawn_posX == 0)
		DrawRotaGraph(pos_x + 170, pos_y+20,0.3,0, warning, TRUE);
	if (mode == 4 && spawn_posX == 1)
		DrawRotaGraph(pos_x -70, pos_y+20, 0.3, 0, warning, TRUE);
	if (mode == 5)
		DrawGraph(pos_x, pos_y, image[image_index], TRUE);
}
void Npc3::Exit() {
}