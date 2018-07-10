#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <iostream>
#include <allegro5\allegro_acodec.h>
#include <cgGame.h>
#include <cgAudioManager.h>
#include <cgInputManager.h>
#include <cgGameState.h>
#include "SwGameState.h"
#include "globals.h"
using namespace std;

int main(void) {

	// Game (manager)
	__game = new cgGame(840, 600, 60);

	// Audio Manager
	cgAudioManager* audio_manager = new cgAudioManager(__game, "sounds", 3);
	__game->setAudioManager(audio_manager);
	audio_manager->set_file(0, "song.ogg");
	audio_manager->set_file(1, "jump.ogg");
	audio_manager->set_file(2, "EnemyDeath.ogg");
	audio_manager->set_loop(0, true);

	// Input Manager
	cgInputManager* inp = new cgInputManager(__game);
	__game->setInputManager(inp);

	// Game State
	SwGameState* gs = new SwGameState(__game);
	__game->setGameState(gs);

	return __game->play();
}