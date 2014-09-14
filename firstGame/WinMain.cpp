#include "DxLib.h"

#define PLAYER_SPEED 3
#define ENEMY_SPEED 3
#define SHOT_SPEED 3

#define IMGWIDTH 64
#define IMGHEIGHT 64
#define SHOTWIDTH 16
#define SHOTHEIGHT 16

enum Direction
{
	RIGHT,
	LEFT,
};

struct Player
{	
	int x;
	int y;
	int handle;
};

struct Enemy
{
	int x;
	int y;
	int handle;
	int muki;
};

struct Shot
{
	int x;
	int y;
	int handle;
	int flag;
};


// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	Player player;
	player.handle = LoadGraph("img/Ball.png");
	player.x = 0;
	player.y = 288;

	Enemy enemy;
	enemy.handle = LoadGraph("img/Sikaku.png");
	enemy.x = 0;
	enemy.y = IMGHEIGHT;
	enemy.muki = LEFT;

	Shot shot;
	shot.handle = LoadGraph("img/Shot.png");
	shot.x = -SHOTWIDTH;
	shot.y = -SHOTHEIGHT;
	shot.flag = 1;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		//更新-------------------------------------------
		int newX = player.x;
		int newY = player.y;
		if (CheckHitKey(KEY_INPUT_UP))
			newY -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_DOWN))
			newY += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_RIGHT))
			newX += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT))
			newX -= PLAYER_SPEED;


		if ((0 <= newX && newX < 640-IMGWIDTH) && (0 <= newY && newY < 480-IMGHEIGHT))
		{		
				player.x = newX;
				player.y = newY;
		}

		
		if (enemy.x >= 640 - IMGWIDTH){
			enemy.muki = RIGHT;
			
		}else if (enemy.x <= 0){
			enemy.muki = LEFT;
		}
		
		if (enemy.muki){
			enemy.x += ENEMY_SPEED;
		}
		else{
			enemy.x -= ENEMY_SPEED;
		}

		if (!(0 <= shot.x && shot.x < 640 - SHOTWIDTH) && (-SHOTHEIGHT <= shot.y && shot.y < 480 - SHOTHEIGHT)){
			shot.flag = 1;
		}
		else{
			shot.flag = 0;
		}

		if (CheckHitKey(KEY_INPUT_Z) && shot.flag){
			shot.x = player.x + IMGWIDTH / 2 - SHOTWIDTH / 2;
			shot.y = player.y + IMGHEIGHT / 2 - SHOTHEIGHT / 2;
		}

		if ((0 <= shot.x && shot.x < 640 - SHOTWIDTH) && (-SHOTHEIGHT <= shot.y && shot.y < 480 - SHOTHEIGHT))
		{
			shot.y -= SHOT_SPEED;
		}else{
			shot.x = -SHOTWIDTH;
			shot.y = -SHOTHEIGHT;
		}
		
		//描画-------------------------------------------
		DrawGraph(enemy.x, enemy.y, enemy.handle, TRUE);
		DrawGraph(shot.x, shot.y, shot.handle, TRUE);
		DrawGraph(player.x, player.y, player.handle, TRUE);


		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}