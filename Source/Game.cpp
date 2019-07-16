#include "Game.h"
#include "Actions.h"
#include "Constants.h"
#include "GameFont.h"
#include"Player.h"
#include"Enemy.h"
#include "Bullet.h"
#include"EnemyBullet .h"
#include"Barrier.h"
#include"CollisionDetction.h"
#include"mothership.h"

#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

/**
*   @brief   Default Constructor.
*/
InvadersGame::InvadersGame()
{
	score = 0;
	srand(time(NULL));

}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
InvadersGame::~InvadersGame()
{
	this->inputs->unregisterCallback(callback_id);
	this->inputs->unregisterCallback(state_callback_id);
}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The input callback should also
			 be set in the initialise function. 
*   @return  True if the game initialised correctly.
*/
bool InvadersGame::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Invaders - Exercise 1");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	toggleFPS();

	// input callback function
	callback_id = this->inputs->addCallbackFnc(&InvadersGame::input, this);
	
	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42), "default", 42);
	
	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}	

	enemyPt = std::make_unique<Enemy>();
	enemyPt->init(renderer);

	playerPt = std::make_unique<Player>();
	playerPt->init(renderer);

	bulletPt = std::make_unique<Bullet>();
	enemybulletPt = std::make_unique<EnemyBullet>();

	barrierPt = std::make_unique<Barrier>();
	barrierPt->init(renderer);

	MotherShipPt = std::make_unique<MotherShip>();
	MotherShipPt->init(renderer);

	colisionPt = std::make_unique<CollisionDetction>();

	state_callback_id = this->inputs->addCallbackFnc(&InvadersGame::stateInput, this);

	return true;
}

/**
*   @brief   The main game loop. 
*   @details The main loop should be responsible for updating the game
			 and rendering the current scene. Runs until the shouldExit
			 signal is received.
*   @return  True if the game ran correctly. 
*/

bool InvadersGame::run()
{
	while (!shouldExit())
	{
		switch (game_state)
		{
		case GameState::MAIN_MENU:
			updateMenue();
			break;
		case GameState::PLAYING:
			updateGame();
			break;
		case GameState::GAME_OVER:
		case GameState::WIN_SCREEN:
			updateGameEndScreen();
			break;
		case GameState::PAUSE:
			updatePause();
			break;
		case GameState::RESET:
			updateReset();
				break;
		default:
			break;
		}
	}
	return true;
}
void InvadersGame::updateMenue()
{
	beginFrame();
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("SPACE INVADERS\n PRESS ENTER TO START", 375, 325, 1.0, ASGE::COLOURS::DARKORANGE);
	endFrame();
}
void InvadersGame::updateGame()
{
	std::chrono::high_resolution_clock timer;
	auto start = timer.now();

	processGameActions();
	render();

	enemyPt->Move(deltaTime);
	MotherShipPt->MoveShip();

	if (playerPt->GetHasShot())
	{
		if (bulletPt->getBulletFierd())
		{
			bulletPt->shoot(renderer, playerPt->GetXpostion(0));
		}
		bulletPt->MoveBullet();
		if (!bulletPt->deleteBullet())
		{
			playerPt->SetHasShot(false);
		}
		for (int i = 0; i < 3; i++)
		{
			if (barrierPt->getHealth(i) > 0 && colisionPt->hasThereBeenACollision(barrierPt->GetBarrierX(i), barrierPt->GetBarrierY(i), barrierPt->Gethight(i), barrierPt->GetWidth(i)
				, bulletPt->GetBulletX(), bulletPt->GetBulletY(), bulletPt->Gethight(), bulletPt->GetWidth()))
			{
				playerPt->SetHasShot(false);
				barrierPt->TakeDamge(i);
			}
		}
		for (int i = 0; i < 55; i++)
		{
			if (!enemyPt->GetDeadSprites(i))
			{
				if (colisionPt->hasThereBeenACollision(enemyPt->GetXpostion(i), enemyPt->GetYpostion(i), enemyPt->Gethight(i), enemyPt->GetWidth(i)
					, bulletPt->GetBulletX(), bulletPt->GetBulletY(), bulletPt->Gethight(), bulletPt->GetWidth()))
				{
					playerPt->SetHasShot(false);
					enemyPt->killSprite(i);
   					score =enemyPt->Getvalue(i);
				}
			}
		}
	}
	if (!Spawned)
	{
		ran = rand() % 55 + 0;
		float spawnNumber = (float)rand() / (float)RAND_MAX;
		if (spawnNumber < 0.05)
		{
			enemybulletPt->setBulletFierd(true);
			enemybulletPt->shoot(renderer, enemyPt->GetXpostion(ran), enemyPt->GetYpostion(ran));
			Spawned = true;
		}
	}
	if (Spawned)
	{
	for (int i = 0; i < 3; i++)
	{
		if (barrierPt->getHealth(i)>0 && colisionPt->hasThereBeenACollision(barrierPt->GetBarrierX(i), barrierPt->GetBarrierY(i), barrierPt->Gethight(i), barrierPt->GetWidth(i)
			, enemybulletPt->GetEnemyBulletX(), enemybulletPt->GetEnemyBulletY(), enemybulletPt->Gethight(), enemybulletPt->GetWidth()))
		{
			enemybulletPt->setBulletFierd(false);
			Spawned = false;
			barrierPt->TakeDamge(i);
		}
	}
		
		if (enemybulletPt->getBulletFierd())
		{
			enemybulletPt->MoveBullet();// move out of for loop
			if (!enemybulletPt->deleteBullet())
			{
				enemybulletPt->setBulletFierd(false);
				Spawned = false;
			}
			if (playerPt->getIsAlive())
			{
				if (colisionPt->hasThereBeenACollision(playerPt->GetXpostion(0), playerPt->GetYpostion(0), playerPt->Gethight(0), playerPt->GetWidth(0)
					, enemybulletPt->GetEnemyBulletX(), enemybulletPt->GetEnemyBulletY(), enemybulletPt->Gethight(), enemybulletPt->GetWidth()))
				{
					enemybulletPt->setBulletFierd(false);
					Spawned = false;
					if (playerPt->playerHit() <= 0)
					{
						enemyPt->setEnemyWin(true);
					}
				}
			}
		}
	}
	enemyPt->hasEnemyhasWon();
	
	if (enemyPt->getHasEnemyWon())
	{
		game_state = GameState::GAME_OVER;
	}
	else if (enemyPt->areAllSpritesDead())
	{
		game_state = GameState::WIN_SCREEN;
	}
	auto stop = timer.now();
	using ms = std::chrono::duration<float, std::milli>;
	deltaTime = std::chrono::duration_cast<ms>(stop - start).count() / 100;
}
void InvadersGame::updateGameEndScreen()
{
	scoreString = std::to_string(score);
	scoreChar = scoreString.c_str();
	beginFrame();
	renderer->setFont(GameFont::fonts[0]->id);
	if (game_state == GameState::WIN_SCREEN)
	{
		renderer->renderText("YOU WIN", 375, 325, 1.0, ASGE::COLOURS::DARKORANGE);
	}
	else
	{
		renderer->renderText("GAME OVER", 375, 325, 1.0, ASGE::COLOURS::DARKORANGE);
	}

	renderer->renderText("SCORE", 375, 425, 0.5, ASGE::COLOURS::DARKORANGE);
	renderer->renderText(scoreChar, 475, 425, 0.5, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("PRESS ENTER TO PLAY AGAIN", 375, 480, 0.5, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("PRESS ESC TO QUIT", 375, 540, 0.5, ASGE::COLOURS::DARKORANGE);
	endFrame();
}

void InvadersGame::updatePause()
{
	beginFrame();
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("GAME PAUSED", 375, 325, 1.0, ASGE::COLOURS::DARKORANGE);
	endFrame();
}
void InvadersGame::updateReset()
{
	enemyPt->reset();
	enemyPt->init(renderer);
	playerPt->reset();
	playerPt->init(renderer);
	barrierPt->init(renderer);
	barrierPt->Reset();
	playerPt->SetHasShot(false);
	bulletPt->setBulletFierd(false);
	game_state = GameState::PLAYING;

}
void InvadersGame::stateInput(int key, int action)
{
	if (action == ASGE::KEYS::KEY_PRESS&& game_state == GameState::MAIN_MENU)
	{
		if (key == ASGE::KEYS::KEY_ENTER)
		{
			game_state = GameState::PLAYING;
		}
	}
	else if (action == ASGE::KEYS::KEY_PRESS&& game_state == GameState::PAUSE)
	{
		if (key == ASGE::KEYS::KEY_P)
		{
			game_state = GameState::PLAYING;
		}
	}
	else if (action == ASGE::KEYS::KEY_PRESS&& game_state == GameState::GAME_OVER || game_state == GameState::WIN_SCREEN)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			game_action = GameAction::EXIT;
		}
		if (key == ASGE::KEYS::KEY_ENTER)
		{
			game_state = GameState::RESET;
		}
	}
	else if (action == ASGE::KEYS::KEY_PRESS&& game_state == GameState::PLAYING)
	{
		if (key == ASGE::KEYS::KEY_P)
		{
			game_state = GameState::PAUSE;
		}
	}
	
	processGameActions();
}
/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool InvadersGame::shouldExit() const
{
	return (renderer->exit() || this->exit && game_action != GameAction::EXIT);
}

/**
*   @brief   Renders the scene
*   @details Prepares the renderer subsystem before drawing the 
			 current frame. Once the current frame is has finished
			 the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void InvadersGame::render()
{
	beginFrame();
	drawFrame();
	endFrame();
}

/**
*   @brief   Renderers the contents for this frame 
*   @details All game objects that need rendering should be done
			 in this function, as it ensures they are completed
			 before the buffers are swapped.
*   @return  void
*/
void InvadersGame::drawFrame()
{
	enemyPt->Render(renderer);
	playerPt->Render(renderer);
	barrierPt->Render(renderer);
	MotherShipPt->Render(renderer);
	if (Spawned)
	{
		enemybulletPt->Render(renderer);
	}
	if (playerPt->GetHasShot()==true)
	{
		bulletPt->Render(renderer);
	}
}

/**
*   @brief   Processes any key inputs and translates them to a GameAction
*   @details This function is added as a callback to handle the game's 
			 input. Key presseses are translated in to GameActions which 
			 are then processed by the main game loop.
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*   @return  void
*/

void InvadersGame::input(int key, int action) 
{
	if (action == ASGE::KEYS::KEY_PRESS)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			game_action = GameAction::EXIT;
		}
	}
	if (key == ASGE::KEYS::KEY_D)
	{
		playerPt->moveRight(deltaTime);
	}
	if (key == ASGE::KEYS::KEY_A)
	{
		playerPt->moveLeft(deltaTime);
	}
	if (action == ASGE::KEYS::KEY_PRESS)
	{
		if (key == ASGE::KEYS::KEY_SPACE)
		{
			if (game_state == GameState::PLAYING)
			{
				if (!playerPt->GetHasShot())
				{
					playerPt->SetHasShot(true);
					bulletPt->setBulletFierd(true);
				}
			}
		}
	}
}

/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of 
*            user input. It allows input to processed in a different
             thread and the game actions performed in the main thread. 
*   @return  void
*/
void InvadersGame::processGameActions()
{
	if (game_action == GameAction::EXIT)
	{
		this->exit = true;
	}

	game_action = GameAction::NONE;
}