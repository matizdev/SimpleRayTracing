#include <stdio.h>
#include <math.h>

#define WIDTH 40
#define HEIGHT 20
#define RADIUS 5
#define SUN_RADIUS 3

void draw_scene() {
    char canvas[HEIGHT][WIDTH];

    // Initialize canvas with spaces
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            canvas[y][x] = ' ';
        }
    }

    // Draw the sun at the top right corner
    int sun_x = WIDTH - SUN_RADIUS - 1;
    int sun_y = SUN_RADIUS + 1;

    for (int y = -SUN_RADIUS; y <= SUN_RADIUS; y++) {
        for (int x = -SUN_RADIUS; x <= SUN_RADIUS; x++) {
            if (x * x + y * y <= SUN_RADIUS * SUN_RADIUS) {
                if (sun_y + y >= 0 && sun_y + y < HEIGHT && sun_x + x >= 0 && sun_x + x < WIDTH) {
                    canvas[sun_y + y][sun_x + x] = 'O'; // Sun representation
                }
            }
        }
    }

    // Draw the ball in the center
    int ball_x = WIDTH / 2;
    int ball_y = HEIGHT / 2;

    for (int y = -RADIUS; y <= RADIUS; y++) {
        for (int x = -RADIUS; x <= RADIUS; x++) {
            if (x * x + y * y <= RADIUS * RADIUS) {
                if (ball_y + y >= 0 && ball_y + y < HEIGHT && ball_x + x >= 0 && ball_x + x < WIDTH) {
                    canvas[ball_y + y][ball_x + x] = 'O'; // Ball representation
                }
            }
        }
    }

    // Print the canvas
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            putchar(canvas[y][x]);
        }
        putchar('\n');
    }
}

int main() {
    draw_scene();
    return 0;
}
