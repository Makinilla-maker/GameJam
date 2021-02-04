#include <iostream>
#include <Windows.h>
#include "SDL2-2.0.12/include/SDL.h"
#include "main.h"

class Player
{
public:
	SDL_Rect playerRect;
	float velocityX;

	Player(int x_, int y_, int w_, int h_)
	{
		playerRect =
		{
			x_,y_,w_,h_
		};
		velocityX = 0;
	}
	~Player();
};
class GoodBoxes
{
public:
	SDL_Rect goodRect;
	int boxesLives;

	GoodBoxes(int _x, int _y, int _w, int _h)
	{
		goodRect =
		{
			_x,_y,_w,_h
		};
		boxesLives = 3;
	}
};

class Bullets
{
public:
	SDL_Rect bulletRect;
	int velocityBulletY;
	Bullets(int x, int y, int w, int h)
	{
		bulletRect =
		{
			x,y,w,h
		};
		velocityBulletY = 1;
	}
};

class Enemies
{
public:
	SDL_Rect enemieRect;
	int velocityEnemieY;
	int velocityEnemieX;
	Enemies(int _x_, int _y_, int _w_, int _h_)
	{
		enemieRect =
		{
			_x_,_y_,_w_,_h_
		};
		velocityEnemieY = 0;
		velocityEnemieX = 4;
	}
};
class EnemieBullet
{
public: 
	SDL_Rect enemieBulletRect;
	float velocityEnemieBulletY;
	EnemieBullet(int xx, int yy, int ww, int hh)
	{
		enemieBulletRect =
		{
			xx,yy,ww,hh
		};
		velocityEnemieBulletY = enemieBulletRect.y;
	}
};
class Lives
{
public:
	SDL_Rect livesRect;
	Lives(int xx, int yy, int ww, int hh)
	{
		livesRect =
		{
			xx,yy,ww,hh
		};
	}
};
class Walls
{
public:
	SDL_Rect leftWall;
	SDL_Rect rightWall;
	Walls(int xx, int yy, int ww, int hh)
	{
		leftWall =
		{
			xx,yy,ww,hh
		};
		rightWall =
		{
			xx,yy,ww,hh
		};
	}
};

int main(int argc, char** argv)
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event events;

	//bools
	bool close;
	bool shoot;
	bool enemieShoot;
	bool enemieAlive;
	bool step;
	bool rightTrue;
	bool leftTrue;
	int counter;
	int counter2;
	int counterRight;
	int counterLeft;
	int deadCounter;
	int enemyShooting;
	int playerLives;
	int deadEnemies;

	//Player object
	Player* player = new Player(610, 690, 80, 20);
	
	//Boxes object
	GoodBoxes *goodboxes[7] =
	{
		new GoodBoxes(98, 545, 54, 20),
		new GoodBoxes(268, 545, 54, 20),
		new GoodBoxes(438, 545, 54, 20),
		new GoodBoxes(608, 545, 54, 20),
		new GoodBoxes(789, 545, 54, 20),
		new GoodBoxes(959, 545, 54, 20),
		new GoodBoxes(1129, 545, 54, 20),
	};
	//player Lives
	Lives* lives[3] =
	{
		new Lives(10,10,20,20),
		new Lives(40,10,20,20),
		new Lives(70,10,20,20),
	};
	//Bullet Object
	Bullets* bullets[8] =
	{
		nullptr
	};
	Walls* wall[2] =
	{
		new Walls(0,0,4,720),
		new Walls(1276,0,4,720),
	};
	EnemieBullet* enemiebullet[14] =
	{
		nullptr
	};

	Enemies* enemies[14] =
	{
		//ROW 2
		new Enemies(152,199,54,20),
		new Enemies(322,199,54,20),
		new Enemies(492,199,54,20),
		new Enemies(662,199,54,20),
		new Enemies(843,199,54,20),
		new Enemies(1013,199,54,20),
		new Enemies(1183,199,54,20),

		//ROW 3
		new Enemies(44,256,54,20),
		new Enemies(214,256,54,20),
		new Enemies(384,256,54,20),
		new Enemies(554,256,54,20),
		new Enemies(735,256,54,20),
		new Enemies(905,256,54,20),
		new Enemies(1075,256,54,20),
	};

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);

	//Initialize the window bool
	close = false;
	//Initialize shooting bool
	shoot = false;
	//Initialize the enemy bool
	enemieAlive = true;
	//Initialize the step bool
	step = false;
	counter = 0;
	counterRight = 0;
	counterLeft = 0;
	counter2 = 0;
	deadCounter = 0;
	enemieShoot = false;
	rightTrue = false;
	leftTrue = false;
	playerLives = 3;
	deadEnemies = 0;
	srand(time(NULL));
	while (close == false)
	{
		Uint32 startTime = SDL_GetTicks();
		//INPUT
		while (SDL_PollEvent(&events))
		{
			if (events.type == SDL_QUIT)
				close = true;
		}
		//Get the keyboard
		const Uint8* keysArray = SDL_GetKeyboardState(NULL);
		if (keysArray[SDL_SCANCODE_ESCAPE])
			close = true;

		//PLAYER MOVEMENT

		if (keysArray[SDL_SCANCODE_LEFT] && player->playerRect.x > 0)
			player->velocityX -= 0.5f;
		if (keysArray[SDL_SCANCODE_RIGHT] && player->playerRect.x < 1200)
			player->velocityX += 0.5f;
		//if (keysArray[SDL_SCANCODE_D])
		//	enemies[0]->velocityEnemieX *= -1;
		if (keysArray[SDL_SCANCODE_SPACE] && shoot == false)
		{
			for (int i = 0; i < 8; i++)
			{
				if (bullets[i] == nullptr)
				{
					shoot = true;
					bullets[i] = new Bullets(player->playerRect.x + 40, 690, 5, 10);
					break;
				}
			}
		}
		if (!keysArray[SDL_SCANCODE_SPACE])
		{
			shoot = false;
		}

		int bulletCount = 0;
		int enemieBullet = 0;
		//UPDATE
		for(auto i :bullets)
			if (i != nullptr)
			{
				bulletCount++;
			}

		for (auto i : enemiebullet)
			if (i != nullptr)
			{
				enemieBullet++;
			}
		static char title[256];
		sprintf_s(title, 256, "BULLETS [%d] | ENEMY BULLETS [%d]", bulletCount, enemieBullet);
		SDL_SetWindowTitle(window, title);
		//PLAYER SPEED
		player->playerRect.x = player->velocityX;
		for (int i = 0; i < 8; i++)
		{
			if (bullets[i] != nullptr)
			{
				bullets[i]->bulletRect.y -= bullets[i]->velocityBulletY;
				SDL_Point p =
				{
					bullets[i]->bulletRect.x,
					bullets[i]->bulletRect.y,

				};
				if (p.y <= 0)
				{
					delete bullets[i];
					bullets[i] = nullptr;
				}
				for (int j = 0; j < 7; j++)
				{
					if (goodboxes[j] != nullptr)
					{
						//COLLISIONS
						if (SDL_PointInRect(&p, &goodboxes[j]->goodRect))
						{
							delete bullets[i];
							bullets[i] = nullptr;
							break;
						}

					}
				}				
				for (int e = 0; e < 14; e++)
				{
					if (enemies[e] != nullptr)
					{
						if (SDL_PointInRect(&p, &enemies[e]->enemieRect))
						{
							deadEnemies++;
							delete enemies[e];
							enemies[e] = nullptr;
							delete bullets[i];
							bullets[i] = nullptr;
							break;
						}
					}
				}
			}
			for (int k = 0; k < 14; k++)
			{
				enemyShooting = rand() % 100;
				if (enemies[k] != nullptr)
				{
					for (int h = 0; h < 8; h++)
					{
						if (enemiebullet[h] == nullptr)
						{
							enemiebullet[h] = new EnemieBullet(enemies[k]->enemieRect.x + 27, enemies[k]->enemieRect.y, 5, 10);
							break;
						}
					}
				}
			}
			//BULLETS MOVEMENT
			for (int j = 0; j < 14; j++)
			{
				if (enemiebullet[j] != nullptr)
				{
					enemiebullet[j]->enemieBulletRect.y = enemiebullet[j]->velocityEnemieBulletY+=0.05f;
					SDL_Point e
					{
						enemiebullet[j]->enemieBulletRect.x,
						enemiebullet[j]->enemieBulletRect.y,
					};
					for (int z = 0; z < 7; z++)
					{
						if (e.y <= 0 || SDL_PointInRect(&e, &player->playerRect))
						{
							playerLives--;
							delete enemiebullet[j];
							enemiebullet[j] = nullptr;
							break;
						}
					}
					if (e.y >= 700)
					{
						delete enemiebullet[j];
						enemiebullet[j] = nullptr;
					}
					for (int d = 0; d < 7; d++)
					{
						if (goodboxes[d] != nullptr)
						{
							//COLLISIONS
							if (SDL_PointInRect(&e, &goodboxes[d]->goodRect))
							{
								goodboxes[d]->boxesLives--;
								if (goodboxes[d]->boxesLives == 0)
								{
									delete goodboxes[d];
									goodboxes[d] = nullptr;
								}
								delete enemiebullet[j];
								enemiebullet[j] = nullptr;
							}
						}
					}
				}
			}
			//LOSE CONDITION
			if (playerLives == 0)
			{
				close = true;
			}
			//WIN CONDITION
			if (deadEnemies == 14)
			{
				close = true;
			}
		}

		//ENEMIES DO GO DOWN
		{
			counter++;
			if (counter == 2000)
			{
				for (int e = 0; e < 14; e++)
				{
					if (enemies[e] != nullptr)
					{
						enemies[e]->enemieRect.y += 20;
					}
				}
				counter = 0;
			}
		}
		{
			if (counter % 10 == 0)
			{
				for (int e = 0; e < 14; e++)
				{
					if (enemies[e] != nullptr)
					{
						enemies[e]->enemieRect.x += enemies[e]->velocityEnemieX;
						if (enemies[e]->enemieRect.x <= 40 || enemies[e]->enemieRect.x + enemies[e]->enemieRect.w >= 1240)
						{
							enemies[e]->velocityEnemieX *= -1;
						}
					}
				}
			}
		}
		//DRAW
			//BACKGROUND
		SDL_SetRenderDrawColor(renderer, 0, 47, 187, 255);
		SDL_RenderClear(renderer);
			//PLAYER
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &player->playerRect);

		SDL_Rect aim =
		{
			player->playerRect.x + 40, 690, 5, 10
		};

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &aim);
	
			//GOODBOXES
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		for (int i = 0; i < 7; i++)
		{
			if (goodboxes[i] != nullptr)
			{
				SDL_SetRenderDrawColor(renderer, 200, 100, 0, (255 - (3 - goodboxes[i]->boxesLives) * 85));
				SDL_RenderFillRect(renderer, &goodboxes[i]->goodRect);
			}
		}
			//LIVES
		SDL_SetRenderDrawColor(renderer, 2, 125, 34, 255);
		for (int i = 0; i < playerLives; i++)
		{
			SDL_RenderFillRect(renderer, &lives[i]->livesRect);
		}
			//BULLETS
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for (int i = 0; i < 8; i++)
		{
			if(bullets[i] != nullptr)
				SDL_RenderFillRect(renderer, &bullets[i]->bulletRect);
		}
			//ENEMIE BULLET
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		for (int i = 0; i < 14; i++)
		{
			if (enemiebullet[i] != nullptr)
				SDL_RenderFillRect(renderer, &enemiebullet[i]->enemieBulletRect);
		}
			//ENEMIES
		for (int i = 0; i < 14; i++)
		{
			if (enemieAlive == true && enemies[i] != nullptr)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderFillRect(renderer, &enemies[i]->enemieRect);
			}
		}
		SDL_RenderPresent(renderer);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 100 / 60) SDL_Delay(100 / 60 - frameTime);
	}
	return 0;
}