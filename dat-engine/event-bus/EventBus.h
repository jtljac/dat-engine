#pragma once
#include <functional>
#include <typeindex>
#include <typeinfo>

#include <util/TypeTraits.h>


#include "Event.h"
#include "service/EngineService.h"

namespace DatEngine::Events {
    class EventBus final : public Service::EngineService {
        std::unordered_multimap<std::type_index, std::function<void(void*)>> listenerMap;
    public:
        void init() override {

        }

        template<TypeTraits::CSubClass<Event> TEvent>
        void addListener(std::function<void(TEvent*)> listenerMethod) {
            listenerMap.emplace(std::type_index(typeid(TEvent)), [test = listenerMethod](void* event) {
                test(static_cast<TEvent*>(event));
            });
        }

        /* TODO: Unregister, handle threading, move to cpp file, document */

        template<TypeTraits::CSubClass<Event> TEvent>
        void callEvent(TEvent* eventData) {
            auto listeners = listenerMap.equal_range(std::type_index(typeid(TEvent)));
            for (auto it = listeners.first; it != listeners.second; ++it) {
                it->second(eventData);
            }
        }
    };
}