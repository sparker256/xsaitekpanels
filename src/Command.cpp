#include <string.h>

#include "Log.h"
#include "Command.h"

using namespace std;
using namespace xsaitekpanels;

Command::Command(string cmdname_in)
{
    cmdname = cmdname_in;
    cmd = NULL;
}

bool Command::lazy_init()
{
    if (cmd != NULL)
        return (true);
    cmd = XPLMFindCommand(cmdname.c_str());
    if (cmd == NULL) {
        return (false);
    }
    return (true);
}

void Command::perform_command(void (*perform_func)(XPLMCommandRef))
{
    if (!lazy_init())
        return;
    ASSERT(cmd != NULL);
    perform_func(cmd);
}

void Command::begin()
{
    perform_command(XPLMCommandBegin);
}

void Command::end()
{
    perform_command(XPLMCommandEnd);
}

void Command::once()
{
    perform_command(XPLMCommandOnce);
}

const string Command::get_cmdname() const
{
    return (cmdname);
}

XPLMCommandRef Command::getCommand()
{
    (void) lazy_init();
    return (cmd);
}
