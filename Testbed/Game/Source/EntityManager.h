#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Entity.h"



class EntityManager : public Module
{
public:
	EntityManager();

	// Destructor
	virtual ~EntityManager()
	{}

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void AddEntity(fPoint position, Entity::Type type);

	void OnCollision(Collider* a, Collider* b);

	struct PlayerData
	{
		fPoint position;
		int lives = 3;

		bool hit = false;
		bool godMode = false;
		bool footJump = false;

		fPoint initPositionScene1 = { 50.0f, 260.0f };
		fPoint initPositionScene2 = { 50.0f, 278.0f };
		fPoint initPositionScene3 = { 32.0f, 277.0f };
		fPoint initPositionScene4 = { 32.0f, 277.0f };

		//Pause Menu
		bool pauseCondition = false;
		bool debug = false;
		bool resetCamera;

		SDL_Texture* pauseMenu = nullptr;



		SDL_Rect cameraBckUp;
	};

	PlayerData playerData;

	List<Entity*> entityList;

private:


	SDL_Texture* texPlayer;
	SDL_Texture* texTarget;
	SDL_Texture* texGun;
	SDL_Texture* playerAnimation;

	Entity* playerEntity;
	Entity* targetEntity;
	Entity* gunEntity;
	Entity* player2Entity;
	Entity* coins;

	//Fonts
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
};

#endif // _ENTITYMANAGER_H_