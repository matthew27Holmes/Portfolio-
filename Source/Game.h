#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <chrono>
#include <time.h>       /* time */
#include <string>
#include "Vector2Util.h"
#include "ObjectTagUtil.h"

class Player;
class EnemyController;
class BarrierManager;
class CollisionDetction;
class MotherShip;
struct GameFont;

enum class GameState
{
	MAIN_MENU = 0,
	PLAYING = 1,
	GAME_OVER = 2,
	PAUSE = 3,
	EXIT=4,
	RESET=5,
	WIN_SCREEN=6
};
/**
*  Invaders Game. An OpenGL Game based on ASGE.
*/
class InvadersGame:
	public ASGE::OGLGame
{
public:
	InvadersGame();
	~InvadersGame();

	// Inherited via Game
	virtual bool run() override;
	bool shouldExit() const;
	void render();

	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame();

	//state machine 
	void updateGame();
	void updateMenue();
	void updateGameEndScreen();
	void updatePause();
	void updateReset();
	//void updateWin_Screen();
	void stateInput(int key, int action);
private:
	void processGameActions(); 
	void input(int key, int action) ;
	int state_callback_id = -1;
	int callback_id = -1;     /**< Input Callback ID. The callback ID assigned by the game engine. */
	bool exit = false;  /**< Exit boolean. If true the game loop will exit. */

	int score;     
	int ran;
	bool Spawned;
	const char* scoreChar;
	std::string scoreString;
	

	//pointers to GameObjects
	std::unique_ptr<Player> playerPt; 
	std::unique_ptr<EnemyController> enemyControlPt;
	std::unique_ptr<BarrierManager> barrierPt;
	std::unique_ptr<CollisionDetction> colisionPt;
	GameState game_state = GameState::MAIN_MENU;

	//should create list of all in game objects so each object can control thier own collison detecion
	//with in there own class
	float deltaTime;
	
};

