#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{

	int kk = 1;
	const int frameDelay = 0;
	Uint32 frameStart;
	int frameTime;


	while (kk == 1) {
	
		Mix_Init(MIX_INIT_MP3);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		// Load âm thanh MP3 vào biến Mix_Music
		Mix_Music* music = Mix_LoadMUS("nhacnen.mp3");

		// Phát âm thanh MP3
		Mix_PlayMusic(music, 1);

 	game = new Game();

	game->init("GameWindow", 800, 640, false);

		while (game->running())
		{

			//if (game->gamestate == 0)
			//{

			//}
			frameStart = SDL_GetTicks();

			game->handleEvents(kk);
			game->update(kk);
			game->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
			

		}

		

		game->clean();
	}
	return 0;
}