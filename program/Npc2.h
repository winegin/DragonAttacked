class Npc2
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
	int memory_spawn;
	int time_warp;
	int image_index;
	int time_switch_image;
	void Init();		//	����������
	void Update(int mouseX, int mouseY);	//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
