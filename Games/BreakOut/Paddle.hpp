//
//  Paddle.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/22/20.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include <stdint.h>
#include "Screen.hpp"
#include "Excluder.hpp"


enum PaddleDirection{
 
  LEFT  = 1 << 0,
  RIGHT = 1 << 1
};
class Paddle: public Excluder{
  
public:
    static const uint32_t PADDLE_WIDTH = 50;
    static const uint32_t PADDLE_HEIGHT = 10;
    
    void Init(const AARectangle& rect, const AARectangle& boundary);
    void Update(uint32_t dt);
    void Draw(Screen& screen);
    
    inline bool  IsMovingLeft() const {return direction_ == PaddleDirection::LEFT;}
    inline bool  IsMovingRight() const {return direction_ == PaddleDirection::RIGHT;}
    inline void SetMovementDirection(PaddleDirection paddle_direction){direction_ |= paddle_direction; };
    inline void UnSetMovementDirection(PaddleDirection paddle_direction){direction_ &= ~paddle_direction; };
    inline void StopMovement() {direction_ = 0;};

private:
    uint32_t direction_;
    AARectangle boundary_;
     const float VELOCITY = 100.0f;
    
};


#endif /* Paddle_hpp */
