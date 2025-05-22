#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

// Set up origin point for the screen
struct {
	const float x = 400;
	const float y = 300;
} origin;

// Define a structure to hold display colors
struct {
	ALLEGRO_COLOR bg_color;
	ALLEGRO_COLOR font_color;
} display;

void handle_mouse_clicks(ALLEGRO_EVENT event, float& x, float& y, ALLEGRO_FONT* font);

int main() {

	if (!al_init()) {
		std::cerr << "Allegro not found!" << std::endl;
	}

	ALLEGRO_DISPLAY* screen = NULL;
	screen = al_create_display(800, 600);

	// Create a font and use the ttf addon to load a font
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT* font = NULL ;
	font = al_load_font("04B_30__.TTF", 16, 0);
	// Set initial font and background colors
	display.bg_color = al_map_rgb(50, 255, 50);
	display.font_color = al_map_rgb(50, 255, 50);

	if (!screen) {
		std::cerr << "Screen could not initialize!" << std::endl;
	}
	al_init_primitives_addon();

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT event;
	event_queue = al_create_event_queue();

	if (!event_queue) {
		std::cerr << "Event queue not found!" << std::endl;
	}

	if (!al_install_mouse()) {
		std::cerr << "Mouse device not found!" << std::endl;
	}
	// Allow mouse input into event queue
	al_register_event_source(event_queue, al_get_mouse_event_source());

	// Initial circle position
	float circle_x = origin.x;
	float circle_y = origin.y;

	while (true) {
		// Clear previously drawn circle
		al_clear_to_color(al_map_rgb(0, 0, 0));
		// Text will follow circle's every position
		al_draw_text(font, display.font_color, circle_x, circle_y, ALLEGRO_ALIGN_CENTER, "Click to move the circle!");
		// Draw circle at new position
		al_draw_circle(circle_x, circle_y, 50, al_map_rgb(50, 255, 50), 5);
		// Display the circle
		al_flip_display();
		// Listener for event queue, specifically mouse clicks
		al_wait_for_event(event_queue, &event);
		// Process game logic for mouse click
		handle_mouse_clicks(event, circle_x, circle_y, font);
	}

	al_destroy_display(screen);
	al_destroy_font(font);
	
	return 0;
}


void handle_mouse_clicks(ALLEGRO_EVENT event, float& x, float& y, ALLEGRO_FONT* font) {
	// RGB color variables for easy reference
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 50);
	ALLEGRO_COLOR blue = al_map_rgb(50, 50, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);

	if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		// Update circle position to mouse click position
		x = event.mouse.x;
		y = event.mouse.y;
	}
}

