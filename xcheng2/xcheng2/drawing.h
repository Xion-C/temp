#pragma once
#include <SDL2/SDL.h>
#include "vector2f.h"

void DrawFilledCircle(
    SDL_Renderer* renderer, 
    SDL_Point center, 
    int radius, 
    SDL_Color color);

void DrawFilledTriangle(
    SDL_Renderer* renderer,
    SDL_Point p0,
    SDL_Point p1,
    SDL_Point p2,
    SDL_Color color);

void DrawFilledRect(
    SDL_Renderer* renderer,
    SDL_Rect rect,
    SDL_Color color);

void DrawGradientRect(
    SDL_Renderer* renderer,
    SDL_Rect rect,
    SDL_Color color1,
    SDL_Color color2);

void DrawFilledPolygon(
    SDL_Renderer* renderer,
    const SDL_Point* points,
    int count,
    SDL_Color color);

void DrawThickLine(
    SDL_Renderer* renderer,
    SDL_Point p0,
    SDL_Point p1,
    int thickness,
    SDL_Color color);

void DrawPartialAnnulus(
    SDL_Renderer* renderer,
    SDL_Point center,
    int r0,
    int r1,
    int start_degree,
    int end_degree,
    SDL_Color color);

void DrawRadialLine(
    SDL_Renderer* renderer,
    SDL_Point center,
    int radius,
    int start_degree,
    int end_degree,
    int step,
    int thickness,
    SDL_Color color);