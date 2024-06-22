#include "Main.h"
#include "Game.h"
#include "Npc2.h"
#include "Hit.h"



//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
void Npc2::Init()
{
	pos_x = -30;
	pos_y = -30;
	mode = 0;
	speed = 1;
	memory_spawn = 0;
	time_s = 60;
	time_warp = 20;
	image_index = 4;
	time_switch_image = 60;
	LoadDivGraph("data/flying_twin_headed_dragon-blue.png", 12, 3, 4, 432 / 3, 512 / 4, image);
}
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void Npc2::Update(int mouseX, int mouseY)
{
SettingMode:
	{
		//Reset
		if (mode == 0) {
			pos_x = -130;
			pos_y = -30;
			time_s = 60;
		}
		//RandomSpawn
		if (mode == 1) {
			spawn_pos = GetRand(1);
			mode = 2;
		}
		//SettingSpawn
		if (mode == 2) {
			switch (spawn_pos) {
			case 0:
				pos_x = -130;
				pos_y = GetRand(350);
				break;
			case 1:
				pos_x = SCREEN_W + 30;
				pos_y = GetRand(350);
				break;
			}
			mode = 3;
		}
		//Moving
		if (mode == 3) {
			switch (spawn_pos) {
			case 0:
				pos_x += speed+0.5f;
				break;
			case 1:
				pos_x -= speed+ 0.5f;
				break;
			}
			if (pos_x <= -150 || pos_x >= SCREEN_W + 50) {
				mode = 0;
			}
		}
		//Damaged
		if (mode == 4) {
			time_s--;
			if (time_s <= 0) {
				mode = 0;

			}
		}

		if (mode == 5) {
			time_warp--;
			if (time_warp <= 0) {
				time_warp = 20;
				mode = 7;
			}
		}
		//FallingDown
		if (mode == 6) {
			pos_y += speed + 5;
			if (pos_y >= 450) {
				mode = 4;
			}
		}
		//Warp
		if (mode == 7) {
			pos_x = mouseX - 50;
			pos_y = mouseY - 60;

		}
	}

SettingHitBox:
	{
		//TowerHit and Mouse Hit
		if (mode == 3)
		{
			if (PushMouseInput(MOUSE_INPUT_LEFT))
			{
				if (CheckBoxHit(mouseX, mouseY, 1, 1, pos_x + 10, pos_y + 20, 110, 90)) {
					memory_spawn = spawn_pos;
					mode = 5;
				}
			}
		}
		//Check Mouse Warp Position
		if (mode == 7)
		{
			if (PushMouseInput(MOUSE_INPUT_RIGHT)) {
				if ((mouseX >= SCREEN_W / 2 - 130 && mouseX <= SCREEN_W / 2 + 90) || mouseY >= 500) {
					return;
				}
				else
				{
					if (memory_spawn == 0) {
						if (mouseX < SCREEN_W / 2) spawn_pos = 0;
						if (mouseX > SCREEN_W / 2) spawn_pos = 0;
					}
					else if (memory_spawn == 1) {
						if (mouseX > SCREEN_W / 2) spawn_pos = 1;
						if (mouseX > SCREEN_W / 2)  spawn_pos = 1;
					}
					mode = 3;
				}
			}
		}
	}
SettingAnimation: {
	if ((mode <= 3 && mode > 0) && spawn_pos == 0 || mode == 5 && spawn_pos == 0)
	{
		time_switch_image--;
		if (time_switch_image < 0) {
			time_switch_image = 59;
		}
		if (time_switch_image % 10 == 0) {
			image_index++;
			if (image_index > 5) {
				image_index = 3;
			}
		}
	}
	if ((mode <= 3 && mode > 0) && spawn_pos == 1 || mode == 5 && spawn_pos == 1)
	{
		time_switch_image--;
		if (time_switch_image < 0) {
			time_switch_image = 59;
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
//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
void Npc2::Render()
{
	if (time_s % 20 >= 0 && time_s % 20 < 10)
	{
		if ((mode <= 4 && mode > 0) && spawn_pos == 0 || mode == 6 && spawn_pos == 0 || mode == 5 && spawn_pos == 0)
		{

			DrawGraph(pos_x, pos_y, image[image_index], TRUE);
		}
		if ((mode <= 4 && mode > 0) && spawn_pos == 1 || mode == 6 && spawn_pos == 1 || mode == 5 && spawn_pos == 1)
		{

			DrawGraph(pos_x, pos_y, image[image_index], TRUE);
		}
	}
}
//---------------------------------------------------------------------------------
//	èIóπèàóù
//---------------------------------------------------------------------------------
void Npc2::Exit()
{
	for (int i = 0; i < 12; i++)DeleteGraph(image[i]);
}
