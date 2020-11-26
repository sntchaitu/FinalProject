//
//  BreakOut.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/21/20.
//
#include "GameController.hpp"
#include "BreakOut.hpp"
#include "AARectangle.hpp"
#include "App.hpp"
#include "Vec2D.hpp"
#include <iostream>

using namespace std;
void BreakOut::Init(GameController& game_controller){
    
    game_controller.ClearAll();
    ResetGame();
    ButtonAction left_key_action;
    left_key_action.key = GameController::LeftKey();
    left_key_action.action = [this](uint32_t dt, InputState input_state){
        if(GameController::IsPressed(input_state)){
            std::cout<<"left key pressed";
            paddle_.SetMovementDirection(PaddleDirection::LEFT);
        }
        else{
            paddle_.UnSetMovementDirection(PaddleDirection::LEFT);
        }
    };
    game_controller.AddInputActionForKey(left_key_action);
    
    
    ButtonAction right_key_action;
    right_key_action.key = GameController::RightKey();
    right_key_action.action = [this](uint32_t dt, InputState input_state){
        if(GameController::IsPressed(input_state)){
            std::cout<<"right key pressed";
            paddle_.SetMovementDirection(PaddleDirection::RIGHT);
        }
        else{
            paddle_.UnSetMovementDirection(PaddleDirection::RIGHT);
        }
    };
    game_controller.AddInputActionForKey(right_key_action);
    
}
void BreakOut::Update(u_int32_t dt){
    
    paddle_.Update(dt);
}
void BreakOut::Draw(Screen& screen){
    
    paddle_.Draw(screen);
}
const string&  BreakOut::GetName() const{
    static string name = "Break Out!";
    return name;
}

void BreakOut::ResetGame(){
    
//    AARectangle paddleRect = {Vec2D(App::Singleton().Width()/2 - Paddle::PADDLE_WIDTH/2, App::Singleton().Height() - 3*Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
    
    cout<<"start w "<< App::Singleton().Width()/2;
    cout<<"start h "<< App::Singleton().Height();
    AARectangle paddle_rect = {Vec2D((App::Singleton().Width())/2 -Paddle::PADDLE_WIDTH/2, (App::Singleton().Height())), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
    
    AARectangle level_boundary = {Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()};
    
    
    paddle_.Init(paddle_rect, level_boundary);
}
