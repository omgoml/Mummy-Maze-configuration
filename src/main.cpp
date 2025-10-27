#include <SDL3/SDL.h>
#include <iostream>

#define endl "\n";

const int WINDOW_WIDHT = 640;
const int WINDOW_HEIGHT = 480;

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "failed to initiallize SDL!" << SDL_GetError() << endl; 
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Mummy Maze", WINDOW_WIDHT, WINDOW_HEIGHT, 0);  

    if(!window) {
        std::cerr << "Failed to create the window screen" << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

    if (!renderer) {
        std::cerr << "Failed to create renderer!" << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    float x = 100, y = 200;
    float speed = 1000.0f;
    Uint64 last_time = SDL_GetTicks();


    while(running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } 
        }
        
        const bool *state = SDL_GetKeyboardState(NULL);     
        Uint64 current_time = SDL_GetTicks();
        float delta = (current_time - last_time) / 1000.0f;
        last_time = current_time; 

        if (state[SDL_SCANCODE_W]) y -= speed * delta;
        if (state[SDL_SCANCODE_S]) y += speed * delta;
        if (state[SDL_SCANCODE_A]) x -= speed * delta;
        if (state[SDL_SCANCODE_D]) x += speed * delta;
        
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + 200 > WINDOW_WIDHT) x = WINDOW_WIDHT - 200;
        if (y + 150 > WINDOW_HEIGHT) y = WINDOW_HEIGHT - 150; 

        
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        SDL_FRect rect = {x, y, 200, 150};
        
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}