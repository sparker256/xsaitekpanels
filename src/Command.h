#ifndef _XSP_COMMAND_H_
#define _XSP_COMMAND_H_

#include <string>
#include <stdlib.h>
#include "XPLMUtilities.h"

namespace xsaitekpanels {
    class Command {
        std::string cmdname;
        XPLMCommandRef cmd;

        bool lazy_init();
        void perform_command(void (*perform_func)(XPLMCommandRef));

    public:
        Command(std::string cmdname);

        void begin();
        void end();
        void once();

        const std::string get_cmdname() const;

        XPLMCommandRef getCommand();
    };
}

#endif  /* _XSP_COMMAND_H_ */
