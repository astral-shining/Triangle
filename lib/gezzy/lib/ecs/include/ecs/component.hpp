#pragma once
#include <cpputils/constexpr_for.hpp>

namespace ECS {
    
struct Component {

    
    virtual void start() {

    }
    
    virtual void update() {

    }

    virtual void destroy() {
        
    }
};

};