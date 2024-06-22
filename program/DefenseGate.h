class Defense {
public:
	int pos_x, pos_y;
	int pos_2x, pos_2y;
	int image;
	int image2;
	int image_now;
	int gate_size;
	int time_allow;
	int num_gate;
	int combo_hit[3];
	int is_gate1;
	int g;
	int b;
	int time_c;
	void Init();
	void Update();
	void Render();
	void Exit();
};