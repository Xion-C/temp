#include "drawing.h"
#include <algorithm>
#include <cmath>

const double PI = 3.1415926535897;
const double RAD2DEG = (180 / PI);
const double DEG2RAD = (PI / 180);
const double DELTA = 0.000001;

void DrawFilledCircle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
            }
        }
    }
}

float wedge(const Vector2f& a, const Vector2f& b) {
    return a[0] * b[1] - a[1] * b[0];
}
int smallest(int a, int b, int c) {
    int temp = std::min(a, b);
    return std::min(temp, c);
}
int largest(int a, int b, int c) {
    int temp = std::max(a, b);
    return std::max(temp, c);
}
float InTriangle(const Vector2f& v0, const Vector2f& v1, const Vector2f& v2, const Vector2f& x, float fuzz) {
    Vector2f e0 = v1 - v0;
    Vector2f e1 = v2 - v1;
    Vector2f e2 = v0 - v2;
    float N = wedge(e1, -e0);
    if (N <= -0.00001) {
        N *= -1.0;
        e0 *= -1.0;
        e1 *= -1.0;
        e2 *= -1.0;
    }
    float b0 = wedge(e0, x - v0);
    if (b0 <= -0.00001) { return 0.0; }
    float b1 = wedge(e1, x - v1);
    if (b1 <= -0.00001) { return 0.0; }
    float b2 = wedge(e2, x - v2);
    if (b2 <= -0.00001) { return 0.0; }
    if (fuzz == 0.0) return 1.0;
    return std::min(1.0, (pow(b0*b1*b2, 0.33) * 3.0 / N) / fuzz);
}

void DrawFilledTriangle(
    SDL_Renderer* renderer,
    SDL_Point p0,
    SDL_Point p1,
    SDL_Point p2,
    SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    Vector2f v0(p0.x, p0.y);
    Vector2f v1(p1.x, p1.y);
    Vector2f v2(p2.x, p2.y);

    float x = smallest(v0[0], v1[0], v2[0]);
    float y = smallest(v0[1], v1[1], v2[1]);
    Vector2f box0(x, y);
    //std::cout << "box0: " << box0 << std::endl;

    x = largest(v0[0], v1[0], v2[0]);
    y = largest(v0[1], v1[1], v2[1]);
    Vector2f box1(x, y);
    //std::cout << "box1: " << box1 << std::endl;

    for (int x = box0[0]; x <= box1[0]; ++x) {
        for (int y = box0[1]; y <= box1[1]; ++y) {
            Vector2f p(x, y);
            if (InTriangle(v0, v1, v2, p, 0.6)) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
    SDL_RenderDrawLine(renderer, p0.x, p0.y, p2.x, p2.y);
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

void DrawFilledRect(
    SDL_Renderer* renderer,
    SDL_Rect rect,
    SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Point points[4] = {
        {rect.x, rect.y},
        {rect.x + rect.w, rect.y},
        {rect.x + rect.w, rect.y + rect.h},
        {rect.x, rect.y + rect.h}
    };
    DrawFilledPolygon(renderer, points, 4, color);
}

void DrawGradientRect(
    SDL_Renderer* renderer,
    SDL_Rect rect,
    SDL_Color color1,
    SDL_Color color2)
{
    for (int y = rect.y; y < (rect.y + rect.h); ++y) {
        float c = static_cast<float>(y - rect.y) / rect.h;
        SDL_Color color = {
            color1.r + (color2.r - color1.r) * c,
            color1.g + (color2.g - color1.g) * c,
            color1.b + (color2.b - color1.b) * c,
            255
        };
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, rect.x, y, rect.x + rect.w, y);
    }
}

void DrawFilledPolygon(
    SDL_Renderer* renderer,
    const SDL_Point* points,
    int count,
    SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int i = 3; i <= count; i++) {
        DrawFilledTriangle(renderer, points[0], points[i - 2], points[i - 1], color);
    }
}

void DrawThickLine(
    SDL_Renderer* renderer,
    SDL_Point p0,
    SDL_Point p1,
    int thickness,
    SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int offset = (thickness - 1) / 2;
    offset = offset < 1 ? 1 : offset;

    if (p1.x - p0.x == 0) {
        //for (int i = 0; i < thickness; i++) {
        //    SDL_RenderDrawLine(renderer, p0.x - offset + i, p0.y, p1.x - offset + i, p1.y);
        //}
        SDL_Point points[4] = {
            { p0.x - offset, p0.y },
            { p0.x - offset + thickness, p0.y },
            { p1.x - offset + thickness, p1.y },
            { p1.x - offset, p1.y }
        };
        DrawFilledPolygon(renderer, points, 4, color);
    }
    else if (p1.y - p0.y == 0) {
        //for (int i = 0; i < thickness; i++) {
        //    SDL_RenderDrawLine(renderer, p0.x, p0.y - offset + i, p1.x, p1.y - offset + i);
        //}
        SDL_Point points[4] = {
            { p0.x, p0.y - offset },
            { p0.x, p0.y - offset + thickness },
            { p1.x, p1.y - offset + thickness },
            { p1.x, p1.y - offset }
        };
        DrawFilledPolygon(renderer, points, 4, color);
    }
    else {
        const float m = -1 / (float(p1.y - p0.y) / float(p1.x - p0.x));
        const float b0 = p0.y - m * p0.x;
        const float b1 = p1.y - m * p1.x;
        //int x0, x1, y0, y1;
        int x00, y00, x01, y01, x10, y10, x11, y11;
        if (m < 1.0f && m > -1.0f) { //when |m|<1
            x00 = p0.x - offset;
            y00 = round(m * x00 + b0);
            x01 = p0.x - offset + thickness;
            y01 = round(m * x01 + b0);
            x10 = p1.x - offset;
            y10 = round(m * x10 + b1);
            x11 = p1.x - offset + thickness;
            y11 = round(m * x11 + b1);
            SDL_Point points[4] = {
                { x00, y00 },
                { x01, y01 },
                { x11, y11 },
                { x10, y10 }
            };
            DrawFilledPolygon(renderer, points, 4, color);
        }
        else { //when |m|>=1
            y00 = p0.y - offset;
            x00 = round((y00 - b0) / m);
            y01 = p0.y - offset + thickness;
            x01 = round((y01 - b0) / m);
            y10 = p1.y - offset;
            x10 = round((y10 - b1) / m);
            y11 = p1.y - offset + thickness;
            x11 = round((y11 - b1) / m);
            SDL_Point points[4] = {
                { x00, y00 },
                { x01, y01 },
                { x11, y11 },
                { x10, y10 }
            };
            DrawFilledPolygon(renderer, points, 4, color);
        }
    }
}

void DrawPartialAnnulus(
    SDL_Renderer* renderer,
    SDL_Point center,
    int r0,
    int r1,
    int start_degree,
    int end_degree,
    SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int rmax = r0 > r1 ? r0 : r1;
    int rmin = r0 < r1 ? r0 : r1;
    int dx, dy;
    double degree;
    for (int py = center.y - rmax; py <= center.y + rmax; py++) {
        for (int px = center.x - rmax; px <= center.x + rmax; px++) {
            dx = px - center.x;
            dy = py - center.y;
            //SDL_RenderDrawPoint(renderer, px, py);
            if (dx * dx + dy * dy <= rmax * rmax && dx * dx + dy * dy >= rmin * rmin) {
                //SDL_RenderDrawPoint(renderer, px, py);
                degree = atan2(dy, dx) * RAD2DEG + 180;
                if (degree >= start_degree - DELTA && degree <= end_degree + DELTA) {
                    SDL_RenderDrawPoint(renderer, px, py);
                }
            }
        }
    }
}

void DrawRadialLine(
    SDL_Renderer* renderer,
    SDL_Point center,
    int radius,
    int start_degree,
    int end_degree,
    int step,
    int thickness,
    SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Point end;
    for (int theta = start_degree; theta <= end_degree; theta += step) {
        end.x = center.x + radius * cos(theta * DEG2RAD);
        end.y = center.y + radius * sin(theta * DEG2RAD);
        DrawThickLine(renderer, center, end, thickness, color);
    }
}