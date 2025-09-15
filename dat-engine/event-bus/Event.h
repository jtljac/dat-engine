#pragma once


namespace DatEngine::Events{
    struct Event {};

    struct CancellableEvent : public Event {
    private:
        bool cancelled = false;
    public:

        bool isCancelled() const {
            return cancelled;
        }

        void cancelEvent() {
            cancelled = true;
        }
    };
}
