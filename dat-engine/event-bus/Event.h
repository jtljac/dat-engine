#pragma once


namespace DatEngine::Events{
    struct Event {};

    struct CancellableEvent : public Event {
    protected:
        bool cancelled = false;
    public:
        [[nodiscard]] bool isCancelled() const {
            return cancelled;
        }

        void cancelEvent() {
            cancelled = true;
        }
    };
}
