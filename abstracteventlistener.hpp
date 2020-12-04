/*
 *
 */

#ifndef ABSTRACTEVENTLISTENER_H
#define ABSTRACTEVENTLISTENER_H

#include <memory>

class EventListener
{
    public:
        virtual void onRender() noexcept {
        }

        virtual void onKeyPressed(int key, int scancode, int action, int mode) noexcept {
        }

        virtual void onMouseMove(double x, double y) noexcept {
        }

        virtual ~EventListener() noexcept {
        }
}; // EventListener

using EventListenerPtr = std::shared_ptr < EventListener >;

#endif // ABSTRACTEVENTLISTENER_H
