#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define BALL_RADIUS 50
#define BALL_SPEED 5

typedef struct {
    float x, y;
} Vector2;

typedef struct {
    Vector2 start;
    Vector2 end;
} Ray;

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void draw_ray(SDL_Renderer *renderer, Ray ray) {
    SDL_RenderDrawLine(renderer, ray.start.x, ray.start.y, ray.end.x, ray.end.y);
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Interactive Ray Tracing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    Vector2 ball_pos = {WIDTH / 2, HEIGHT / 2};

    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        ball_pos.y -= BALL_SPEED;
                        break;
                    case SDLK_DOWN:
                        ball_pos.y += BALL_SPEED;
                        break;
                    case SDLK_LEFT:
                        ball_pos.x -= BALL_SPEED;
                        break;
                    case SDLK_RIGHT:
                        ball_pos.x += BALL_SPEED;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        draw_circle(renderer, ball_pos.x, ball_pos.y, BALL_RADIUS);

        // Draw rays from the ball to the edges of the screen
        for (int angle = 0; angle < 360; angle += 10) {
            Ray ray;
            ray.start = ball_pos;
            ray.end.x = ball_pos.x + cos(angle * M_PI / 180) * WIDTH;
            ray.end.y = ball_pos.y + sin(angle * M_PI / 180) * HEIGHT;
            draw_ray(renderer, ray);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}