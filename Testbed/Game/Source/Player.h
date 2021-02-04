#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Point.h"
#include "Entity.h"
#include "Animation.h"
#include "DynArray.h"

struct SDL_Texture;
struct Collider;

class Player : Body
{
public:
	Player(Module* listener, fPoint position, float mass, float weight, float height, SDL_Texture* texture, Type type);

	bool Start();

	bool Update(float dt);

	bool Draw();

	void Collision(Collider* coll);

	void CleanUp();

private:
	Animation rightAnimation;
	Animation leftAnimation;

	Animation* currentAnimation;

	SDL_Texture* tex;

	bool isJumping;
	bool gun = false;

	int scoreFont = -1;
	char scoreText[10] = { "\0" };
};


#endif // __SCENE_H__
