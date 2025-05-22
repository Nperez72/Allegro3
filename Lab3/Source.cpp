#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

void handle_mouse_clicks(ALLEGRO_EVENT event, float& x, float& y);

int main() {

	if (!al_init()) {
		std::cerr << "Allegro not found!" << std::endl;
	}

	ALLEGRO_DISPLAY* screen = NULL;
	screen = al_create_display(800, 600);

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
	float circle_x = 400;
	float circle_y = 300;

	while (true) {
		// Clear previously drawn circle
		al_clear_to_color(al_map_rgb(0, 0, 0));
		// Draw circle at new position
		al_draw_circle(circle_x, circle_y, 50, al_map_rgb(50, 255, 50), 5);
		// Display the circle
		al_flip_display();
		// Listener for event queue, specifically mouse clicks
		al_wait_for_event(event_queue, &event);
		// Process game logic for mouse click
		// handle_mouse_clicks(event, circle_x, circle_y);
	}
	

	return 0;
}

