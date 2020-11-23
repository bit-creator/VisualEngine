#include "quad.h"

Quad::Quad(const vertex_t& first,
             const vertex_t& second,
             const vertex_t& third,
             const vertex_t& four) 
    : _first(first, second, third)
    , _second(second, third, four)
{  }

void Quad::render(const ShaderProgram& program) const noexcept
{
    _first.render(program);
    _second.render(program);
}

void Quad::setupBuffers() const noexcept
{
    
}


