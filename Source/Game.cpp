#include "Game.h"
#include "Actions.h"
#include "Constants.h"
#include "GameFont.h"
#include "Player.h"
#include "EnemyController.h"

#include"BarrierManager.h"
#include"CollisionDetction.h"
#include"mothership.h"


/**
*   @brief   Default Constructor.
*/
InvadersGame::InvadersGame()
{
	score = 0;
	srand((int)time(NULL));
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
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42), "default", 50);
	
	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}

	//object list 
	std::vector<Actor*> objs;
	objs.reserve(116);

	enemyControlPt = std::make_unique<EnemyController>(renderer);
	enemyControlPt->addToObjList(objs);

	playerPt = std::make_unique<Player>(renderer);
	playerPt->addToObjList(objs);

	barrierPt = std::make_unique<BarrierManager>(renderer);
	barrierPt->addToObjList(objs);

	colisionPt = std::make_unique<CollisionDetction>(objs);

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
		case GameState::PAUSE:
		case GameState::PLAYING:
			updateGame();
			break;
		case GameState::GAME_OVER:
		case GameState::WIN_SCREEN:
			updateGameEndScreen();
			break;
		//case GameState::PAUSE:
		//	updatePause();
		//	break;
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
	renderer->renderText("SPACE INVADERS\nPRESS ENTER TO START", 375, 325, 1.0, ASGE::COLOURS::DARKORANGE);
	endFrame();
}

void InvadersGame::updateGame()
{
	std::chrono::high_resolution_clock timer;
	auto start = timer.now();

	processGameActions();
	render();
	if (game_state != GameState::PAUSE)
	{
		playerPt->Tick(deltaTime);
		enemyControlPt->Tick(deltaTime);
		barrierPt->Tick(deltaTime);

		colisionPt->Tick();

		if (enemyControlPt->getHasEnemyWon() || !playerPt->getIsAlive())//this might not be right dont think it handles lives 
		{
			game_state = GameState::GAME_OVER;
			score = enemyControlPt->getScore();
		}
		else if (enemyControlPt->areAllSpritesDead())
		{
			game_state = GameState::WIN_SCREEN;
			score = enemyControlPt->getScore();
		}
	}

	auto stop = timer.now();
	using ms = std::chrono::duration<float, std::milli>;
	deltaTime = std::chrono::duration_cast<ms>(stop - start).count() / 100;
}

void InvadersGame::updateGameEndScreen()
{
	beginFrame();
	renderer->setFont(GameFont::fonts[0]->id);
	if (game_state == GameState::WIN_SCREEN)
	{
		renderer->renderText("YOU WIN", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4, 1.0, ASGE::COLOURS::DARKORANGE);
	}
	else
	{
		renderer->renderText("GAME OVER", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4, 1.0, ASGE::COLOURS::DARKORANGE);
	}
	std::string scoreTxt = "SCORE  ";
	scoreTxt += std::to_string(score);
	scoreChar = scoreTxt.c_str();
	renderer->renderText(scoreChar, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4+50, 0.5, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("PRESS ENTER TO PLAY AGAIN", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 70, 0.5, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("PRESS ESC TO QUIT", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 90, 0.5, ASGE::COLOURS::DARKORANGE);
	endFrame();
}

//void InvadersGame::updatePause()
//{
//	beginFrame();
//	renderer->setFont(GameFont::fonts[0]->id);
//	renderer->renderText("GAME PAUSED", 375, 325, 1.0, ASGE::COLOURS::DARKORANGE);
//	endFrame();
//}

void InvadersGame::updateReset()
{
	playerPt->reset(enemyControlPt->areAllSpritesDead());
	enemyControlPt->reset();
	barrierPt->Reset();

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
	else if (action == ASGE::KEYS::KEY_PRESS && game_state == GameState::PAUSE)
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

bool InvadersGame::shouldExit() const
{
	return (renderer->exit() || this->exit && game_action != GameAction::EXIT);
}

void InvadersGame::render()
{
	beginFrame();
	drawFrame();
	endFrame();
}

void InvadersGame::drawFrame()
{
	playerPt->Render(renderer);
	barrierPt->Render(renderer);
	enemyControlPt->Render(renderer);
	if (game_state == GameState::PAUSE)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText("GAME PAUSED", WINDOW_WIDTH/2, WINDOW_HEIGHT/4 , 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderText("Press P To Continue", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 50, 0.5, ASGE::COLOURS::DARKORANGE);
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
		playerPt->MoveHorizontally(deltaTime,1);
	}

	if (key == ASGE::KEYS::KEY_A)
	{
		playerPt->MoveHorizontally(deltaTime, -1);
	}

	if (action == ASGE::KEYS::KEY_PRESS)
	{
		if (key == ASGE::KEYS::KEY_SPACE)
		{
			if (game_state == GameState::PLAYING)
			{
				playerPt->Shoot();
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