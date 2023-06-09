#pragma once

namespace View {
    class ShotReadable {
    public:
        virtual void ShotReader(int buf[2], bool askAgain=false, bool help_msg=false) = 0;
    };
}