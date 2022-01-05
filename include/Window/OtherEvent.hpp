#pragma once

#include "Event.hpp"

namespace Window {
    class OtherEvent : public Event {
    private:
        bool m_Quit = false;

    protected:
    public:
        OtherEvent(void);
        ~OtherEvent(void);
        void event(void);
        bool getQuit(void);
    };
}