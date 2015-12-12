#pragma once
#pragma once
#include <functional>
#include <vector>
namespace System {
    namespace Core {
        class Event {
          public:
            Event() {

            }
            ~Event() {

            }
            Event& operator+=(const std::function<void(void*, void*)> handler);
            Event& operator-=(const std::function<void(void*, void*)> handler);
            Event& operator()(void* sender, void* args);
          private:
            std::vector<std::function<void(void*, void*)>> handlers;
        };
    }
}


