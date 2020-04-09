#include <sstream>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

using namespace std;

bool gameloop = true;

// Display properties
int displayW = 800;
int displayH = 600;

float fps = 60.0;

// Keyboard controls properties
int keyUp = ALLEGRO_KEY_UP, keyDown = ALLEGRO_KEY_DOWN, keyRight = ALLEGRO_KEY_RIGHT, keyLeft = ALLEGRO_KEY_LEFT;
int keySprint = ALLEGRO_KEY_LSHIFT;
const int keyBack = ALLEGRO_KEY_ESCAPE;

enum directions { LEFT, DOWN, RIGHT, UP };

// Player properties
float playerX = displayW / 2 - 16, playerY = displayH / 2 - 32;
int playerDir = DOWN;
const float playerWalkSpeed = 2, playerSprintSpeed = 3;
float playerSpeed = 2;
int playerDX = 0, playerDY = 0;
bool moving = false, diagonal = false, sprinting = false;

int main()
{
	ALLEGRO_DISPLAY* display;

	ALLEGRO_EVENT_QUEUE* queue;

	ALLEGRO_TIMER* timer;

	bool draw = true;

	if (!al_init())
	{
		al_show_native_message_box(NULL, "Error", NULL, "Failed to initialize Allegro 5", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}

	// Colors
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR magenta = al_map_rgb(255, 0, 255);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

	// Fonts
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* advpix = al_load_font("Data/Fonts/advanced_pixel-7.ttf", 40, NULL);

	// Sprites
	al_init_image_addon();

	ALLEGRO_BITMAP* tiles = al_load_bitmap("Data/Sprites/tilemap_1.png");
	ALLEGRO_BITMAP* player = al_load_bitmap("Data/Sprites/pc_base.png");

	// Keyboard
	al_install_keyboard();

	ALLEGRO_KEYBOARD_STATE keyState;

	// Display creation
	display = al_create_display(displayW, displayH);
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	al_set_window_title(display, "Pointless Expedition");

	// Event queue creation
	queue = al_create_event_queue();

	// Timer creation
	timer = al_create_timer(1.0 / fps);

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (gameloop)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			gameloop = false;
		}
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
			case keyBack:
				gameloop = false;
			}
		}

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_get_keyboard_state(&keyState);

			if (al_key_down(&keyState, keyLeft))
			{
				playerDir = LEFT;
				playerDX = -1;
			}
			else if (al_key_down(&keyState, keyRight))
			{
				playerDir = RIGHT;
				playerDX = 1;
			}
			else
			{
				playerDX = 0;
			}

			if (al_key_down(&keyState, keyUp))
			{
				playerDir = UP;
				playerDY = -1;
			}
			else if (al_key_down(&keyState, keyDown))
			{
				playerDir = DOWN;
				playerDY = 1;
			}
			else
			{
				playerDY = 0;
			}

			if (playerDX != 0 && (abs(playerDX) == abs(playerDY)))
			{
				diagonal = true;
			}
			else
			{
				diagonal = false;
			}

			if (al_key_down(&keyState, keySprint))
			{
				sprinting = true;
			}
			else
			{
				sprinting = false;
			}

			if (sprinting)
			{
				playerSpeed = playerSprintSpeed;
			}
			else
			{
				playerSpeed = playerWalkSpeed;
			}

			if (!diagonal)
			{
				playerX += playerDX * playerSpeed;
				playerY += playerDY * playerSpeed;
			}
			else
			{
				playerX += playerDX * sin(45) * playerSpeed;
				playerY += playerDY * sin(45) * playerSpeed;
			}
			draw = true;
		}

		// Drawing graphics on display
		if (draw)
		{
			draw = false;
			al_clear_to_color(black);
			al_draw_bitmap_region(player, playerDir * 32, 0, 32, 64, playerX, playerY, NULL);

			al_flip_display();
		}
	}

	al_destroy_bitmap(player);
	al_destroy_bitmap(tiles);
	al_destroy_font(advpix);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_uninstall_keyboard();
	al_destroy_display(display);

	return 0;
}
