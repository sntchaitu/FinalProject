//
//  Screen.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#include "Screen.hpp"
#include "SDL.h"
#include "Utils.hpp"
#include "Vec2D.hpp"
#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;

Screen::Screen():width_(0), height_(0), surface_(nullptr), window_(nullptr)
{
    
}

Screen::~Screen(){
    if(window_){
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    SDL_Quit();
    
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag){
   
    if(SDL_Init(SDL_INIT_VIDEO)){
        std::cout<<"Error SDL_Init Failed"<< endl;
        return nullptr;
    }
    width_ = w;
    height_ = h;
    window_  = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width_*mag, height_*mag, 0);
    if(window_){
        surface_ = SDL_GetWindowSurface(window_);
        SDL_PixelFormat* pixelFormat = surface_->format;
        Color::InitColorFormat(pixelFormat);
        clear_color_ = Color::Black();
        back_buffer_.Init(pixelFormat->format,width_, height_);
        back_buffer_.Clear(clear_color_);
    }
    return window_;
//    SDL_Surface* canvas = SDL_GetWindowSurface(sceneWindow);
//    SDL_PixelFormat* pixelFormat = canvas->format;
//    cout<<" pixel format"<<SDL_GetPixelFormatName(pixelFormat->format);
//    Color::InitColorFormat(pixelFormat);
}
void Screen::SwapScreen(){
    if(window_){
        ClearScreen();
        SDL_BlitSurface(back_buffer_.GetSurface(), nullptr, surface_, nullptr);
        SDL_UpdateWindowSurface(window_);
        back_buffer_.Clear(clear_color_);
    }
}

void Screen::Draw(int x, int y, const Color& color){
    assert(window_);
    if(window_){
        back_buffer_.SetPixel(color, x, y);
    }

}
void Screen::Draw(const Vec2D& point, const Color& color){
    assert(window_);
    if(window_){
        back_buffer_.SetPixel(color, point.GetX(), point.GetY());
    }
}

void Screen::Draw(const Line2D& line, const Color& color)
{
    assert(window_);
    if(window_)
    {
        int dx, dy;

        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());

        dx = x1 - x0;
        dy = y1 - y0;

        signed const char ix((dx > 0) - (dx < 0)); // evaluate to 1 or -1
        signed const char iy((dy > 0) - (dy < 0));

        dx = abs(dx) * 2;
        dy = abs(dy) * 2;

        Draw(x0, y0, color);

        if(dx >= dy)
        {
            //go along in the x

            int d = dy - dx/2;

            while(x0 != x1)
            {
                if(d >= 0)
                {
                    d -= dx;
                    y0 += iy;
                }

                d += dy;
                x0 += ix;

                Draw(x0, y0, color);
            }
        }
        else
        {
            //go along in y
            int d = dx - dy/2;

            while(y0 != y1)
            {
                if(d >= 0)
                {
                    d -= dy;
                    x0 += ix;
                }

                d += dx;
                y0 += iy;

                Draw(x0, y0, color);
            }
        }
    }
}

void Screen::Draw(const AARectangle& rect, const Color& color, bool fill, const Color& fillColor)
{
    if(fill)
    {
        //FillPoly(rect.GetPoints(), fillColor);
    }
    std::vector<Vec2D> points = rect.GetPoints();

    Line2D p0p1 = Line2D(points[0], points[1]);
    Line2D p1p2 = Line2D(points[1], points[2]);
    Line2D p2p3 = Line2D(points[2], points[3]);
    Line2D p3p0 = Line2D(points[3], points[0]);

    Draw(p0p1, color);
    Draw(p1p2, color);
    Draw(p2p3, color);
    Draw(p3p0, color);
}


//void Screen::Draw(const Line2D& line, const Color& color ){
//    assert(window_);
//    if(window_){
//        int dx, dy;
//        int x0= roundf(line.GetP0().GetX());
//        int y0= roundf(line.GetP0().GetY());
//        int x1= roundf(line.GetP1().GetX());
//        int y1= roundf(line.GetP1().GetY());
//
//        dx = x1-x0;
//        dy = y1-y0;
//        signed const char ix((dx > 0) - (dx < 0));
//        signed const char iy((dy > 0) - (dy < 0));
//        dx = abs(dx)*2;
//        dy = abs(dy)*2;
//
//        Draw(x0, y0, color);
//
//        if(dx >= dy){
//            int d = dy - dx/2;
//
//            while(x0 != x1){
//
//            }
//        }
//
//
//    }
//}

void Screen::ClearScreen(){
    assert(window_);
    if(window_){
       SDL_FillRect(surface_, nullptr, clear_color_.GetPixelColor());
        
    }
    
}

