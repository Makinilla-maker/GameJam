#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "Timer.h"
#include "PerfTimer.h"

#include "PugiXml/src/pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class EntityManager;
class Map;
class Collisions;

//Scenes
class Logo;
class Intro;
class Title;
class Scene1;
class Options;
class FadeToBlack;
class DeathScreen;
class WinScreen;
class PathFinding;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// Load/Save Requests Methods
	void LoadGameRequest();
	void SaveGameRequest() const;

private:

	// Load config file
	bool LoadConfig();

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Logo* logo;
	Intro* intro;
	Title* title;
	Scene1* scene1;
	Map* map;
	EntityManager* entityManager;
	Options* options;
	FadeToBlack* fade;
	Collisions* collisions;
	DeathScreen* deathScreen;
	WinScreen* winScreen;
	PathFinding* pathFinding;

	uint activeFonts = 0;
	uint totalFonts = 0;

	bool debugButton = false;

	bool stop = false;
	int currentLevel;

	bool loadingGame = false;

	bool fileSaved;

private:

	int argc;
	char** args;
	SString titl;
	SString organization;

	List<Module*> modules;

	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	uint frames;
	float dt;

	mutable bool saveGameRequested;
	bool loadGameRequested;

	pugi::xml_document saveLoadFile;
	pugi::xml_node saveLoadNode;

	PerfTimer perfTimer;
	uint64 fpsCount = 0;

	int frameRate60;
	int frameRate30;

	Timer startTime;
	Timer frameTime;
	Timer lastSecond;
	uint32 lastSecFrameCnt = 0;
	uint32 prevLastSecFrameCnt = 0;
	uint32 framesSecond = 0;
	uint32 lastFrameMs = 0;
	float fps;
	float frameRate;
	float tempFps;
	float fpsAverageSinceStart;
	bool cappedFrameRate;
	float startFramesTimeMs;
	
	
	float timePerfect;
	float oldLastFrame = 0.0f;
	int cappedMs = -1;
	bool caped;

};

extern App* app;

#endif	// __APP_H__