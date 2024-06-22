#include "Main.h"
#include "Game.h"
#include "DefenseGate.h"

#include "Hit.h"

void Defense::Init()
{


	num_gate = 0;
	is_gate1 = 0;
	time_c = 20;
	time_allow = 120;
	gate_size = 0;

	pos_x = 0;
	pos_2x = 0;
	pos_y = 0;
	pos_2y = 0;
	image = LoadGraph("data/poratal2.png");
	image2 = LoadGraph("data/poratal2flip.png");
	image_now = image;
}

void Defense::Update()
{
KEY_INPUT:
	{
		if (time_allow == 120)
		{
			if (combo_hit[1] == 0 && combo_hit[2] == 0)
			{
				if (PushHitKey(KEY_INPUT_Q)) {
					combo_hit[0]++;
					if (combo_hit[0] > 2) {
						combo_hit[0] = 2;
					}
				}
			}

			if (combo_hit[2] == 0 && combo_hit[0] == 0)
			{
				if (PushHitKey(KEY_INPUT_W)) {
					combo_hit[1]++;
					if (combo_hit[1] > 2) {
						combo_hit[1] = 2;
					}
				}
			}
			if (combo_hit[1] == 0 && combo_hit[0] == 0)
			{
				if (PushHitKey(KEY_INPUT_E)) {
					combo_hit[2]++;
					if (combo_hit[2] > 2) {
						combo_hit[2] = 2;
					}
				}
			}
		}

		if (PushHitKey(KEY_INPUT_R) && time_allow == 120) {
			time_c = 20;
			if (combo_hit[0] == 2) {
				num_gate = 0;
			}

			if (combo_hit[1] == 2) {
				num_gate = 1;
			}

			if (combo_hit[2] == 2) {
				num_gate = 2;
			}
			for (int i = 0; i < 3; i++)
			{
				combo_hit[i] = 0;
			}
		}
		else {
			g = 255; b = 255; time_c--;
			if (time_c <= 0) {
				time_c = 0;
			}
		}

		if (num_gate == 0 && is_gate1 == true)
		{
			pos_x = SCREEN_W / 2 - 100;
			pos_y = SCREEN_H / 2 + 200;
			pos_2x = SCREEN_W / 2 + 100;
			pos_2y = SCREEN_H / 2 + 200;


		}
		if (num_gate == 1 && is_gate1 == true)
		{
			pos_x = SCREEN_W / 2 - 100;
			pos_y = SCREEN_H / 2 + 50;
			pos_2x = SCREEN_W / 2 + 100;
			pos_2y = SCREEN_H / 2 + 50;


		}
		if (num_gate == 2 && is_gate1 == true)
		{
			pos_x = SCREEN_W / 2 - 100;
			pos_y = SCREEN_H / 2 - 100;
			pos_2x = SCREEN_W / 2 + 100;
			pos_2y = SCREEN_H / 2 - 100;

		}
	}


	if (is_gate1 == true) {

		time_allow--;
		gate_size += 5;
		if (gate_size >= 35) {
			gate_size = 35;
		}
		if (time_allow <= 0) {
			time_allow = 0;
			is_gate1 = false;
		}
	}
	if (is_gate1 == false) {

	}
	if (time_allow == 0) {
		gate_size -= 5;

		if (gate_size <= 0) {
			time_allow = 120;
			gate_size = 0;
		}
	}

	if (time_c > 10) {
		g = 0;
		b = 0;
	}
}
void Defense::Render()
{

	/*DrawGraph(pos_x[i], pos_y[i], image_now, TRUE);*/
	if (is_gate1 == true || gate_size > 1)
	{
		DrawExtendGraph(pos_x - gate_size * 2, pos_y - gate_size * 2, pos_x + gate_size * 2, pos_y + gate_size * 2, image, TRUE);
		DrawExtendGraph(pos_2x - gate_size * 2, pos_2y - gate_size * 2, pos_2x + gate_size * 2, pos_2y + gate_size * 2, image2, TRUE);
	}
	for (int i = 0; i < 3; i++) {
		if (combo_hit[i] >= 1) {
			DrawCircle(SCREEN_W / 2 - 180, 560, 12, GetColor(i * 125, 255 / (i + 1), i * 125), TRUE);
			if (combo_hit[0] >= 1)DrawFormatString(SCREEN_W / 2 - 185, 550, GetColor(0, 0, 0), "Q");
			if (combo_hit[1] >= 1)DrawFormatString(SCREEN_W / 2 - 185, 550, GetColor(0, 0, 0), "W");
			if (combo_hit[2] >= 1)DrawFormatString(SCREEN_W / 2 - 185, 550, GetColor(0, 0, 0), "E");

		}
		if (combo_hit[i] == 2) {
			DrawCircle(SCREEN_W / 2 - 150, 560, 12, GetColor(i * 125, 255 / (i + 1), i * 125), TRUE);
			if (combo_hit[0] == 2)DrawFormatString(SCREEN_W / 2 - 155, 550, GetColor(0, 0, 0), "Q");
			if (combo_hit[1] == 2)DrawFormatString(SCREEN_W / 2 - 155, 550, GetColor(0, 0, 0), "W");
			if (combo_hit[2] == 2)DrawFormatString(SCREEN_W / 2 - 155, 550, GetColor(0, 0, 0), "E");
		}
	}
	DrawCircleAA(SCREEN_W / 2 - 120, 560, 12, 24, GetColor(255, g, b), TRUE);
	DrawFormatString(SCREEN_W / 2 - 125, 550, GetColor(0, 0, 0), "R");
}
void Defense::Exit()
{
}
