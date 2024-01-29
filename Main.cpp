// g++ main.cpp `pkg-config --cflags --libs sdl2`
#include <SDL.h>
#include <iostream>
#include <map>
#include <unistd.h>
#include "Matrix.h"
#include "Rules.h"


int CELL_LENGTH_X = 500;
int CELL_LENGTH_Y = 500;

int WINSIZE_X = 1000; int WINSIZE_Y = 800;
int SPEED = 10;

int xOffset = 0; int yOffset = 0;
int cell_margin = 1; int cell_size = 10;
int size = 0;

int subSecCounter = 0; int maxSecCounter = 1;
bool mouseDown = false;
int xMouse = 0, yMouse = 0;
int currentModifyingX = 0;
int currentModifyingY = 0;
bool spacePressToggle = false;

void displayGrid(SDL_Window *win, SDL_Renderer *renderer, Matrix matrix) {
    SDL_Rect rect = {5,5,cell_size,cell_size};
    for (int y = 0; y<CELL_LENGTH_Y; y++) {
        for (int x = 0; x<CELL_LENGTH_X; x++) {
            rect.x = x * (cell_size+cell_margin) + xOffset;
            rect.y = y * (cell_size+cell_margin) + yOffset;
            if (matrix.get(x,y) == 0) {
                SDL_SetRenderDrawColor(renderer,100,100,100,255);
                SDL_RenderFillRect(renderer,&rect);
            } else {
                SDL_SetRenderDrawColor(renderer,200,200,200,255);
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }
}

// key = #neighbors; value = state: 0 = tot; 1 = nichts passiert; 2 = leben
Rules RULES = Rules();

void update(Matrix &mat) {
    Matrix matB = mat;
    for (int y = 0; y < CELL_LENGTH_Y; ++y) {
        for (int x = 0; x < CELL_LENGTH_X; ++x) {
            int n = matB.sumNeighbors(x,y);
            mat.set(x,y,RULES.getAlive(n,matB.get(x,y)));
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("my window", 100, 100, WINSIZE_X,WINSIZE_Y, SDL_WINDOW_SHOWN);

    RULES.changeRule(0,0);
    RULES.changeRule(1,0);
    RULES.changeRule(2,1);
    RULES.changeRule(3,2);
    RULES.changeRule(4,0);
    RULES.changeRule(5,0);
    RULES.changeRule(6,0);
    RULES.changeRule(7,0);
    RULES.changeRule(8,0);

    if (!win) {
        std :: cout << "Failed to create a window! Error: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(win,-1,0);

    if (!renderer) {
        std :: cout << "Failed to create a renderer! Error: " << SDL_GetError() << "\n";
        return 1;
    }

    Matrix mat(CELL_LENGTH_X,CELL_LENGTH_Y);

    displayGrid(win,renderer,mat);

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (SDL_QUIT == event.type || (SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode)) {
                running = false;
                break;
            }

            if (SDL_MOUSEBUTTONDOWN == event.type) {
                if (SDL_BUTTON_LEFT == event.button.button) {
                    mouseDown = true;
                }
            } else if (SDL_MOUSEBUTTONUP == event.type) {
                if (SDL_BUTTON_LEFT == event.button.button) {
                    mouseDown = false;
                }
            }

            if (SDL_KEYDOWN == event.type) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    spacePressToggle = !spacePressToggle;
                    if (!spacePressToggle) {
                        update(mat);
                        subSecCounter = maxSecCounter;
                    }
                }

                if (event.key.keysym.sym == SDLK_u) {
                    update(mat);
                }
            }
        }

        if (mouseDown) {
            SDL_GetMouseState(&xMouse,&yMouse);
            int x = (xMouse - xOffset) / (cell_size+cell_margin);
            int y = (yMouse - yOffset) / (cell_size+cell_margin);
            if (!(currentModifyingX == x && currentModifyingY == y)) {
                mat.set(x,y,!mat.get(x,y));

                currentModifyingX = x;
                currentModifyingY = y;
            }
        } else {
            currentModifyingX = -1;
            currentModifyingY = -1;
        }

        const Uint8* state = SDL_GetKeyboardState(nullptr);

        xOffset += (state[SDL_SCANCODE_LEFT] - state[SDL_SCANCODE_RIGHT]) * SPEED;
        yOffset += (state[SDL_SCANCODE_UP] - state[SDL_SCANCODE_DOWN]) * SPEED;
        cell_margin += (state[SDL_SCANCODE_U] - state[SDL_SCANCODE_J]) * 5;
        if (cell_margin < 0) {
            cell_margin = 0;
        }
        cell_size += (state[SDL_SCANCODE_I] - state[SDL_SCANCODE_K]) * 5;
        if (cell_size < 1) {
            cell_size = 1;
        } if (subSecCounter == 0) {
            update(mat);
            subSecCounter = maxSecCounter;
        }

        if (!spacePressToggle) {
            subSecCounter-=1;
        }
        //SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 255, 255));
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        displayGrid(win,renderer,mat);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        std::cout << "a\n";
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
