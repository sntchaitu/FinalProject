//
//  BreakOut.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/21/20.
//

#ifndef BreakOut_hpp
#define BreakOut_hpp
#include "Game.hpp"
#include "Paddle.hpp"
class BreakOut : public Game{
    
public:
    virtual void Init(GameController& game_controller) override;
    virtual void Update(u_int32_t dt) override;
    virtual void Draw(Screen& screen) override;
    virtual const std::string& GetName() const override;
private:
    void ResetGame();
    Paddle paddle_;
    
};
#endif /* BreakOut_hpp */
