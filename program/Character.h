#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
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
	void Init();		//	����������
	void Update(int mouseX, int mouseY);		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
