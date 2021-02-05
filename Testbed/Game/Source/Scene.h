#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Defs.h"
#include "Timer.h"

class GuiControl;
class GuiButton;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

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

	bool OnGuiMouseClickEvent(GuiControl* control);

	int moneyCont = 21;

	bool firstEntry = true;
	bool amelia = false;
	bool letitia = false;
	bool ada = false;
	
	bool change1 = false;
	bool change2 = false;
	bool change3 = false;

	bool minus1 = false;
	bool minus2 = false;
	bool minus3 = false;
	SDL_Texture* waterBckGrnd;

	GuiButton* btn1;
	GuiButton* btn2;
	GuiButton* btn3;

private:

	SDL_Texture* bckground;
	Timer timer;

	bool collision = false;
};


#endif // __SCENE_H__