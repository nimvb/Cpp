#pragma once
#pragma once
#include <functional>
#include <vector>
namespace System {
    namespace Core {


        class IDelegate {
          public:
            IDelegate() {

            }
            virtual ~IDelegate() {

            }
            virtual bool operator == (const IDelegate& delegate) = 0;
            virtual void operator()(void* sender, void* args) = 0;
          private:
        };

        template<class TClass>
        class Delegate : public IDelegate {
          public:
            typedef void(TClass::*FuncPtr)(void*, void*);
            Delegate(TClass* obj, FuncPtr handler) {
                obj_ptr = obj;
                func_ptr = handler;
            }

            virtual bool operator ==(const IDelegate& delegate) override {
                const Delegate<TClass>& del = dynamic_cast<const Delegate<TClass>&>(delegate);
                if (!del)
                    return false;
                if (del.obj_ptr == obj_ptr) {
                    if (del.func_ptr == func_ptr) {
                        return true;
                    }
                }
                return false;
            }

            virtual void operator()(void* sender, void* args) override {
                std::function<void(void*, void*)> handler = std::bind(func_ptr, obj_ptr, std::placeholders::_1, std::placeholders::_2);
                handler(sender, args);
            }

          private:
            TClass* obj_ptr;
            FuncPtr func_ptr;

        };

        class Event {
          public:
            Event() {


            }
            ~Event() {
                for (std::vector<IDelegate*>::size_type i = 0; i < handlers.size(); i++) {
                    IDelegate* handler = handlers[i];
                    delete handler;
                    handler = nullptr;
                }
                handlers.clear();
            }
            Event& operator+=(IDelegate* delegate) {
                for (std::vector<IDelegate*>::size_type i = 0; i < handlers.size(); i++) {
                    IDelegate* handler = handlers[i];
                    if (*handler == *delegate) {
                        return *this;
                    }
                }
                handlers.push_back(delegate);
                return *this;
            }
            Event& operator-=(IDelegate* delegate) {
                bool found = false;
                std::vector<IDelegate*>::size_type index = 0;
                for (std::vector<IDelegate*>::size_type i = 0; i < handlers.size(); i++) {
                    IDelegate* handler = handlers[i];
                    if (*handler == *delegate) {
                        index = i;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    IDelegate* handler = handlers[index];
                    delete handler;
                    handler = nullptr;
                    handlers.erase(handlers.begin() + index);
                }
                return *this;
            }
            void operator()(void* sender, void* args) {
                for (std::vector<IDelegate*>::size_type i = 0; i < handlers.size(); i++) {
                    IDelegate* handler = handlers[i];
                    (*handler)(sender, args);
                }
            }
          private:
            std::vector<IDelegate*> handlers;
        };

    }
}


