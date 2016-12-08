#pragma once
#include <Engine/OGLGame.h>
#include <string>

class Player;
class Enemy;
class Bullet;
class EnemyBullet;
class  Barrier;
class CollisionDetction;
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
	void updateGameOver();
	void updatePause();
	void updateReset();
	void updateWin_Screen();
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
	std::unique_ptr<Enemy> enemyPt;
	std::unique_ptr<Bullet> bulletPt;
	std::unique_ptr<EnemyBullet> enemybulletPt;
	std::unique_ptr<Barrier> barrierPt;
	std::unique_ptr<CollisionDetction> colisionPt;
	GameState game_state = GameState::MAIN_MENU;

	
};

