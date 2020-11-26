//
//  Paddle.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/22/20.
//

#include "Paddle.hpp"
#include "Screen.hpp"
#include "Utils.hpp"
#include "BoundaryEdge.hpp"

void Paddle::Init(const AARectangle &rect, const AARectangle& boundary ){
    Excluder::Init(rect);
    boundary_ = boundary;
    direction_ = 0;
}

void Paddle::Update(uint32_t dt){
    Vec2D dir;

    if(direction_!= 0){
        if((direction_ & PaddleDirection::LEFT)==PaddleDirection::LEFT &&
           (direction_ & PaddleDirection::RIGHT)== PaddleDirection::RIGHT){
            dir = Vec2D::Zero;
        }
        else if(direction_ == PaddleDirection::LEFT){
            dir = LEFT_DIR;
        }
        else{
            dir = RIGHT_DIR;
        }
    }
    Vec2D dx = dir* VELOCITY * MilliSecondsToSeconds(dt);

    MoveBy(dx);
    
    const AARectangle& aa_rect = GetAARectangle();
    if(IsGreaterThanOrEqual(boundary_.GetTopLeftPoint().GetX(), aa_rect.GetTopLeftPoint().GetX())){
        MoveTo(Vec2D(boundary_.GetTopLeftPoint().GetX(),aa_rect.GetTopLeftPoint().GetY()));
    }
    else if(IsGreaterThanOrEqual(aa_rect.GetBottomRightPoint().GetX(), boundary_.GetBottomRightPoint().GetX())){
        MoveTo(Vec2D(boundary_.GetBottomRightPoint().GetX() -aa_rect.GetWidth(), aa_rect.GetTopLeftPoint().GetY()));
    }

}
void Paddle::Draw(Screen& screen){
    screen.Draw(GetAARectangle(), Color::Blue(), true, Color::Blue());
}
