#include <boost/predef.h>

#if BOOST_OS_LINUX || BOOST_OS_MACOS
#include <cxxabi.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#endif

namespace
{

#if BOOST_OS_LINUX || BOOST_OS_MACOS
constexpr int max_backtrace_frames = 128;
char stack_memory[SIGSTKSZ] = {};

constexpr int handled_signals_max = 6;
int handled_signals[handled_signals_max] =
    {SIGINT, SIGILL, SIGFPE, SIGSEGV, SIGTERM, SIGABRT};
struct sigaction prev_signal_actions[handled_signals_max];

#if BOOST_OS_LINUX
stack_t prev_signal_stack = {};

void setup_signal_stack()
{
    stack_t signal_stack;
    signal_stack.ss_sp = stack_memory;
    signal_stack.ss_size = SIGSTKSZ;
    signal_stack.ss_flags = 0;
    sigaltstack(&signal_stack, &prev_signal_stack);
}
#endif

void reset_signal_handlers()
{
    for (int i = 0; i < handled_signals_max; i++)
    {
        sigaction(handled_signals[i], &prev_signal_actions[i], nullptr);
    }

#if BOOST_OS_LINUX
    sigaltstack(&prev_signal_stack, nullptr);
#endif
}

void signal_handler(int signal)
{
    void *buffer[max_backtrace_frames];

    int frame_count = backtrace(buffer, max_backtrace_frames);
    char **symbols = backtrace_symbols(buffer, frame_count);

    printf("Received signal %d: %s\n", signal, strsignal(signal));

    if (symbols == nullptr)
    {
        perror("couldn't get backtrace");
        exit(1);
    }

    reset_signal_handlers();

    printf("Backtrace:\n");
    for (int i = 0; i < frame_count; i++)
    {
        Dl_info info;
        if (dladdr(buffer[i], &info) && info.dli_sname)
        {
            char *demangled = nullptr;
            int status = -1;
            if (info.dli_sname[0] == '_')
            {
                demangled =
                    abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
            }

            printf(
                "%-3d %*p %s + %zd\n",
                i,
                int(2 + sizeof(void *) * 2),
                buffer[i],
                status == 0 ? demangled
                            : info.dli_sname == 0 ? symbols[i] : info.dli_sname,
                (char *)buffer[i] - (char *)info.dli_saddr);

            free(demangled);
        }
        else
        {
            printf(
                "%-3d %*p %s\n",
                i,
                int(2 + sizeof(void *) * 2),
                buffer[i],
                symbols[i]);
        }
    }

    free(symbols);
    raise(signal);
}
#endif

} // namespace

namespace lib
{

#if BOOST_OS_LINUX || BOOST_OS_MACOS
void setup_backtrace()
{
    struct sigaction signal_action = {};
    signal_action.sa_handler = signal_handler;

#if BOOST_OS_LINUX
    setup_signal_stack();
    signal_action.sa_flags = SA_ONSTACK;
#else
    signal_action.sa_flags = 0;
#endif

    for (int i = 0; i < handled_signals_max; i++)
    {
        sigaction(handled_signals[i], &signal_action, &prev_signal_actions[i]);
    }
}
#else
void setup_backtrace()
{
}
#endif

} // namespace lib
