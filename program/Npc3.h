#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�m�o�b�N���X
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
	void Init();		//	����������
	void Update();	//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
