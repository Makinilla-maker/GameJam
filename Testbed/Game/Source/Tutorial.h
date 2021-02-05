#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

#include "Module.h"
#include "Animation.h"
#include "Defs.h"
#include "Timer.h"


class Tutorial : public Module
{
public:

	Tutorial();

	// Destructor
	virtual ~Tutorial();

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

	void OnCollision(Collider* a, Collider* b);

	bool firstEntry = true;

	

private:

	SDL_Texture* bckground1;
	SDL_Texture* bckground2;
	
	Timer timer;

	int x ;
	bool collision = false;
};


#endif // __SCENE_H__