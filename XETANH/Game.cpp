#include "Game.h"

#include"ECS.h "
#include"Components.h"

Map* map;

GameObject* player1;
GameObject* player2;
GameObject* player3;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{

	gameState = GameState::MENU;
	dead = false;
	dead2 = false;
	dead3 = false;


}

Game::~Game()
{}


void Game::renderResult(SDL_Texture* instructionsTexture) {
	SDL_RenderClear(renderer);
	
	// Load background texture for instructions

	SDL_Rect instructionsRect = { 0, 0, 800, 640 }; // Kích thước của background hướng dẫn

	// Render background texture for instructions
	SDL_RenderCopy(renderer, instructionsTexture, NULL, &instructionsRect);

	// Present renderer
	SDL_RenderPresent(renderer);

	// Free loaded texture
	SDL_DestroyTexture(instructionsTexture);
}///////////

void Game::renderResult2(SDL_Texture* instructionsTexture) {
	SDL_RenderClear(renderer);

	// Load background texture for instructions

	SDL_Rect instructionsRect = { 0, 0, 800, 640 }; // Kích thước của background hướng dẫn

	// Render background texture for instructions
	SDL_RenderCopy(renderer, instructionsTexture, NULL, &instructionsRect);

	// Present renderer
	SDL_RenderPresent(renderer);

	// Free loaded texture
	SDL_DestroyTexture(instructionsTexture);
}///////////
void Game::renderResult3(SDL_Texture* instructionsTexture) {
	SDL_RenderClear(renderer);

	// Load background texture for instructions

	SDL_Rect instructionsRect = { 0, 0, 800, 640 }; // Kích thước của background hướng dẫn

	// Render background texture for instructions
	SDL_RenderCopy(renderer, instructionsTexture, NULL, &instructionsRect);

	// Present renderer
	SDL_RenderPresent(renderer);

	// Free loaded texture
	SDL_DestroyTexture(instructionsTexture);
}///////////


void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	
		player1 = new GameObject("0 bit/s3.png", 736, 32);

		player2 = new GameObject("0 bit/s2.png", 32, 32);
		
	
		
		player3 = new GameObject("0 bit/s2.png", 32, 512);
		map = new Map();
	

	




	newPlayer.addComponent<PositionComponent>();

}

void Game::handleEvents(int & kk)
{
	int k1 = 1;
	int k2 = 1;
	int k3 = 1;
	if (gameState == GameState::MENU) {
		handleEventsMenu(kk);
	}
	else if(gameState == GameState::PLAY) {
		SDL_Event event;

		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_KEYDOWN:
			

			player1->handles(event, bullets, dead);

			player2->handles2(event, bullets,dead2);

			if (dead == true)
			{
				gameState = GameState::EXIT;
			}
			if (dead2 == true)
			{
				gameState = GameState::EXIT2;
			}


			

			break;
		case SDL_QUIT:
			kk = false;
			break;
		default:
			break;
		}
	}

	else if (gameState == GameState::PLAY2) {
		SDL_Event event;

		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_KEYDOWN:

			
                player1->handles(event, bullets, dead);

			
				player2->handles2(event, bullets, dead2);
				

			
					player3->handles3(event, bullets, dead3);
					
			
			

			

			if (dead3 == true&& dead2 == true)
			{
				gameState = GameState::EXIT2;
			}
			if (dead == true&&dead3 == true)
			{
				gameState = GameState::EXIT;
			}
			if (dead == true && dead2 == true)
			{
				gameState = GameState::EXIT3;
			}





			break;
		case SDL_QUIT:
			kk = false;
			break;
		default:
			break;
		}
	}

	else if (gameState == GameState::EXIT2)
	{
		SDL_Event event;

		SDL_PollEvent(&event);
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			/*gameState = GameState::MENU;*/
			isRunning = false;
		}
		switch (event.type)
		{
		case SDL_QUIT:
			kk = false;
			break;
		default:
			break;
		}

	}
	else if (gameState == GameState::EXIT)
	{
		SDL_Event event;

		SDL_PollEvent(&event);
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			isRunning = false;
		}

		switch (event.type)
		{
		case SDL_QUIT:
			kk = false;
			break;
		default:
			break;
		}
	}
	else if (gameState == GameState::EXIT3)
	{
		SDL_Event event;

		SDL_PollEvent(&event);
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			isRunning = false;
		}

		switch (event.type)
		{
		case SDL_QUIT:
			kk = false;
			break;
		default:
			break;
		}
		}

}

void Game::update(int & kk)
{
	if (gameState == GameState::MENU) {
		// Thêm xử lý update cho menu nếu cần
		SDL_Event event;

		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			kk = false;
			break;
		default:
			break;
		}
	}
	else if (gameState == GameState::PLAY) {

		player1->Update();

		player2->Update();

		for (auto it = bullets.begin(); it != bullets.end();)
		{
			(*it)->Update();
			if ((*it)->IsDestroyed())
			{
				delete* it;
				it = bullets.erase(it);

			}
			else ++it;
		}
		
		manager.update();
		//std::cout << newPlayer.getComponent<PositionComponent>().x() << "," <<
		//	newPlayer.getComponent<PositionComponent>().y() << std::endl;
	}

	else if (gameState == GameState::PLAY2) {

		player1->Update();

		player2->Update();

		player3->Update();

		for (auto it = bullets.begin(); it != bullets.end();)
		{
			(*it)->Update();
			if ((*it)->IsDestroyed())
			{
				delete* it;
				it = bullets.erase(it);

			}
			else ++it;
		}
		
		manager.update();
		//std::cout << newPlayer.getComponent<PositionComponent>().x() << "," <<
		//	newPlayer.getComponent<PositionComponent>().y() << std::endl;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	if (gameState == GameState::MENU) {
		renderMenu();
	}
	else if(gameState == GameState::PLAY){

		map->DrawMap();
		player1->Render2();
		player2->Render();

		for (auto it = bullets.begin(); it != bullets.end(); ++it)
		{
			(*it)->Render();
		}
		
		SDL_RenderPresent(renderer);
	}

	else if (gameState == GameState::PLAY2) {

		map->DrawMap();
		player1->Render2();
		player2->Render();
		player3->Render3();

		for (auto it = bullets.begin(); it != bullets.end(); ++it)
		{
			(*it)->Render();
		}
		
		SDL_RenderPresent(renderer);
	}

	else if (gameState == GameState::EXIT) {
		
		SDL_Texture* instructionsTex = TextureManager::LoadTexture("0 bit/1win.png");
		renderResult(instructionsTex);
	}
	else if (gameState == GameState::EXIT2) {

		SDL_Texture* instructionsTex = TextureManager::LoadTexture("0 bit/2win.png");
		renderResult2(instructionsTex);
	}
	else if (gameState == GameState::EXIT3) {

		SDL_Texture* instructionsTex = TextureManager::LoadTexture("0 bit/3win.png");
		renderResult2(instructionsTex);
	}


}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::renderMenu() {
	SDL_RenderClear(renderer);

	// Load background texture
	SDL_Texture* backgroundTexture = TextureManager::LoadTexture("0 bit/background.png");
	SDL_Rect backgroundRect = { 0, 0, 800, 640 }; // Kích thước của background



	// Render background texture
	SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);

	// Load button textures
	SDL_Texture* buttonTexture1 = TextureManager::LoadTexture("0 bit/button1.png");
	SDL_Texture* buttonTexture2 = TextureManager::LoadTexture("0 bit/button3.png");
	SDL_Texture* buttonTexture3 = TextureManager::LoadTexture("0 bit/huongdan1.png");

	// Render button 1
	SDL_Rect buttonRect1 = { 50, 50, 102, 32 }; // Vị trí và kích thước của button 1
	SDL_RenderCopy(renderer, buttonTexture1, NULL, &buttonRect1);

	// Render button 2
	SDL_Rect buttonRect2 = { 50, 100, 102, 32 }; // Vị trí và kích thước của button 2
	SDL_RenderCopy(renderer, buttonTexture2, NULL, &buttonRect2);

	// Render button 2
	SDL_Rect buttonRect3 = { 50, 150, 102, 32 }; // Vị trí và kích thước của button 3
	SDL_RenderCopy(renderer, buttonTexture3, NULL, &buttonRect3);
	SDL_Texture* instructionsTexture = TextureManager::LoadTexture("0 bit/huongdan.png");
	
	if (k == 1) {
		renderInstructions( instructionsTexture);
	}



	// Present renderer
	SDL_RenderPresent(renderer);

	// Free loaded textures
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(buttonTexture1);
	SDL_DestroyTexture(buttonTexture2);
	SDL_DestroyTexture(buttonTexture3);

}

void Game::handleEventsMenu(int & kk) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_2) {
				gameState = GameState::PLAY;
			}
			else if (event.key.keysym.sym == SDLK_3) {
				gameState = GameState::PLAY2;
			}
			
			
			else if (event.key.keysym.sym == SDLK_SPACE) {
				k = 0;
			}

			break;
		case SDL_MOUSEBUTTONDOWN:
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			// Kiểm tra xem vị trí click của chuột có nằm trong vùng của nút 2 người chơi hay không
			if (mouseX >= 50 && mouseX <= 152 && mouseY >= 50 && mouseY <= 82) {
				gameState = GameState::PLAY;
			}
			// Kiểm tra xem vị trí click của chuột có nằm trong vùng của nút 3 người chơi hay không
			else if (mouseX >= 50 && mouseX <= 152 && mouseY >= 100 && mouseY <= 132) {
				gameState = GameState::PLAY2;
			}
			else if (mouseX >= 50 && mouseX <= 152 && mouseY >= 150 && mouseY <= 182) {
				k = 1;
			}
			break;
		case SDL_QUIT:
			kk = false;
			break;
		default:
			break;
		}
	}
}

void Game::renderInstructions(SDL_Texture* instructionsTexture) {
	SDL_RenderClear(renderer);

	// Load background texture for instructions

	SDL_Rect instructionsRect = { 0, 0, 800, 640 }; // Kích thước của background hướng dẫn

	// Render background texture for instructions
	SDL_RenderCopy(renderer, instructionsTexture, NULL, &instructionsRect);

	// Present renderer
	SDL_RenderPresent(renderer);

	// Free loaded texture
	SDL_DestroyTexture(instructionsTexture);
}