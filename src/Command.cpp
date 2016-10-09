#include <string.h>

#include "Log.h"
#include "Command.h"

using namespace xsaitekpanels;

Command::Command(const char *cmdname_in)
{
    VERIFY(cmdname_in != NULL);
    cmdname = (char *)malloc(strlen(cmdname_in) + 1);
    strcpy(cmdname, cmdname_in);
    cmd = NULL;
}

Command::~Command()
{
    free(cmdname);
}

bool Command::resolve_command()
{
    if (cmd != NULL)
        return (true);
    cmd = XPLMFindCommand(cmdname);
    if (cmd == NULL) {
        return (false);
    }
    return (true);
}

void Command::perform_command(void (*perform_func)(XPLMCommandRef))
{
    if (!resolve_command())
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

const char *Command::get_cmdname()
{
    return (cmdname);
}

XPLMCommandRef Command::getCommand()
{
    resolve_command();
    return (cmd);
}
