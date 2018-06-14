#define SDL_MAIN_HANDLED 
#include <SDL_main.h> 
#include <iostream>

#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "drawing.h"

const std::string NAME = "xcheng2";
const int WIDTH = 640;
const int HEIGHT = 480;

int main(void) {
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Draw a minion
    SDL_Point center = { 320, 240 };
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color black = { 0, 0, 0, 255 };
    SDL_Color lightgray = { 220, 220, 220, 255 };
    SDL_Color darkgray = { 50, 50, 50, 255 };
    SDL_Color gray = { 125, 125, 125, 255 };
    SDL_Color bananayellow = { 231, 218, 77, 255 };
    SDL_Color jeansblue = { 0, 117, 169, 255 };
    SDL_Color jeansdarkblue = { 0, 100, 150, 255 };
    SDL_Color lightblack = { 49, 49, 49, 255 };
    SDL_Color darkblack = { 20, 20, 20, 255 };

    SDL_Point headcenter = { 320, 185 };
    SDL_Point jeanscenter = { 320, 325 };
    SDL_Rect bodyrect = { 201, 185, 238, 140 };

    // background
    DrawGradientRect(renderer, { 0, 0, WIDTH, HEIGHT }, lightgray, darkgray);

    // draw hair
    DrawRadialLine(renderer, headcenter, 130, 210, 330, 10, 1, lightblack);

    // body
    DrawFilledCircle(renderer, headcenter, 120, bananayellow);
    DrawFilledCircle(renderer, jeanscenter, 120, jeansblue);
    DrawFilledRect(renderer, bodyrect, bananayellow);

    // mouth
    DrawPartialAnnulus(renderer, { 320, 270 }, 13, 16, 0, 360, lightblack);
    DrawFilledCircle(renderer, { 320, 267 }, 16, bananayellow);

    // eyeglass
    DrawFilledRect(renderer, { 200, 175, 50, 20 }, lightblack);
    DrawFilledRect(renderer, { 390, 175, 50, 20 }, lightblack);
    DrawPartialAnnulus(renderer, headcenter, 55, 70, 0, 360, gray);
    //DrawPartialAnnulus(renderer, headcenter, 70, 72, 0, 360, lightblack);

    // eye
    DrawFilledCircle(renderer, headcenter, 60, white);
    DrawFilledCircle(renderer, headcenter, 25, lightblack);
    DrawFilledCircle(renderer, { 333, 175}, 8, white);

    // right arm
    DrawThickLine(renderer, { 205, 285 }, { 180, 305 }, 16, bananayellow);
    DrawThickLine(renderer, { 180, 310 }, { 210, 340 }, 14, bananayellow);
    DrawFilledCircle(renderer, { 179, 308 }, 12, bananayellow);

    // jeans
    DrawFilledTriangle(renderer, { 265, 415 }, { 312, 435 }, { 312, 464 }, jeansdarkblue);
    DrawFilledTriangle(renderer, { 375, 415 }, { 328, 435 }, { 328, 464 }, jeansdarkblue);

    DrawPartialAnnulus(renderer, jeanscenter, 0, 120, 180, 360, jeansblue);
    DrawFilledRect(renderer, { 255, 295, 130, 30 }, jeansblue);
    DrawThickLine(renderer, { 195, 275 }, { 320, 320 }, 9, jeansblue);
    DrawThickLine(renderer, { 445, 275 }, { 320, 320 }, 9, jeansblue);
    DrawFilledCircle(renderer, { 265, 305 }, 6, lightblack);
    DrawFilledCircle(renderer, { 375, 305 }, 6, lightblack);
    DrawPartialAnnulus(renderer, { 320, 340 }, 29, 31, 180, 360, lightblack);
    DrawThickLine(renderer, { 290, 340 }, { 350, 340 }, 1, lightblack);

    // left arm
    SDL_Point hand = { 495, 230 };
    SDL_Point finger1 = { 490, 205 };
    SDL_Point finger2 = { 515, 210 };
    SDL_Point finger3 = { 522, 235 };
    SDL_Point glove[4] = {
        { 480, 225 },
        { 505, 240 },
        { 490, 262 },
        { 465, 240 }
    };
    DrawThickLine(renderer, { 430, 305 }, hand, 17, bananayellow);
    DrawFilledPolygon(renderer, glove, 4, darkblack);

    DrawThickLine(renderer, hand, finger1, 16, black);
    DrawThickLine(renderer, hand, finger2, 12, black);
    DrawThickLine(renderer, hand, finger3, 14, black);
    DrawFilledCircle(renderer, hand, 18, darkblack);
    DrawFilledCircle(renderer, finger1, 12, darkblack);
    DrawFilledCircle(renderer, finger2, 12, darkblack);
    DrawFilledCircle(renderer, finger3, 12, darkblack);

    // shoes
    DrawPartialAnnulus(renderer, { 290, 465 }, 0, 20, 0, 179, darkblack);
    DrawPartialAnnulus(renderer, { 350, 465 }, 0, 20, 0, 179, darkblack);
    DrawFilledRect(renderer, { 287, 450, 25, 14 }, darkblack);
    DrawFilledRect(renderer, { 328, 450, 25, 14 }, darkblack);

    // generate frame
    SDL_RenderPresent(renderer);
    FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
    frameGen.makeFrame();

    SDL_Event event;
    const Uint8* keystate;
    while (true) {
        keystate = SDL_GetKeyboardState(0);
        if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
