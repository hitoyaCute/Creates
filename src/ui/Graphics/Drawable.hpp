/* Drawable objects that contain internal states and define how they would be drawn
 * the base shoulf not contain any states only the derived objects should implement those states 
 *
 */


#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
namespace MEU {
namespace Graphics {

// base class that describes a object that can be drawn to the screen
class Drawable {
public:
    friend class RenderTarget;

private:
    // internal draw function, this is to let the object draw anything
    virtual void draw(class sf::RenderTarget* target) = 0;


};




}; // namespace Graphics
}; // namespace MEU


