#include "Event.h"

namespace System {
    namespace Core {

        Event& Event::operator+=(const std::function<void(void*, void*)> handler) {
            handlers.push_back(handler);
            return *this;
        }

        Event& Event::operator()(void* sender, void* args) {
            for (std::vector<std::function<void(void*, void*)>>::size_type  i = 0; i < handlers.size(); i++) {
                handlers[i](sender, args);
            }
            return *this;
        }

    }
}