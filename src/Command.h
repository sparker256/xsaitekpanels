#ifndef _XSP_COMMAND_H_
#define _XSP_COMMAND_H_

#include <stdlib.h>
#include "XPLMUtilities.h"

namespace xsaitekpanels {
    class Command {
        char *cmdname;
        XPLMCommandRef cmd;

        bool resolve_command();
        void perform_command(void (*perform_func)(XPLMCommandRef));

    public:
        Command(const char *cmdname);
        ~Command();

        void begin();
        void end();
        void once();

        const char *get_cmdname();

        XPLMCommandRef getCommand();
    };
}

#endif  /* _XSP_COMMAND_H_ */
