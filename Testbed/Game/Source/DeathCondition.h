#ifndef __DEATHCONDITION_H__
#define __DEATHCONDITION_H__

#include "Module.h"
#include "Animation.h"
#include "Defs.h"


class DeathCondition : public Module
{
public:

	DeathCondition();

	// Destructor
	virtual ~DeathCondition();

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

	SDL_Texture* bckground;
	

	bool collision = false;
};


#endif // __SCENE_H__