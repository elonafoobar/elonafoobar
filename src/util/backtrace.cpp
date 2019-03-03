#include <boost/predef.h>

#if BOOST_OS_LINUX
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#endif

namespace
{

#ifdef BOOST_OS_LINUX
constexpr int max_backtrace_frames = 100;
char stack_memory[SIGSTKSZ] = {};

stack_t prev_signal_stack = {};

constexpr int handled_signals_max = 6;
int handled_signals[handled_signals_max] =
    {SIGINT, SIGILL, SIGFPE, SIGSEGV, SIGTERM, SIGABRT};
struct sigaction prev_signal_actions[handled_signals_max];

void reset_signal_handlers()
{
    for (int i = 0; i < handled_signals_max; i++)
    {
        sigaction(handled_signals[i], &prev_signal_actions[i], nullptr);
    }
    sigaltstack(&prev_signal_stack, nullptr);
}

void signal_handler(int signal)
{
    void* buffer[max_backtrace_frames];

    int frame_count = backtrace(buffer, max_backtrace_frames);
    char** strings = backtrace_symbols(buffer, frame_count);

    printf("Received signal %d: %s\n", signal, strsignal(signal));

    if (strings == nullptr)
    {
        perror("couldn't get backtrace");
        exit(1);
    }

    reset_signal_handlers();

    printf("Backtrace:\n");
    for (int i = 0; i < frame_count; i++)
    {
        printf("    %s\n", strings[i]);
    }

    free(strings);
    raise(signal);
}
#endif

} // namespace

namespace lib
{

#ifdef BOOST_OS_LINUX
void setup_backtrace()
{
    stack_t signal_stack;
    signal_stack.ss_sp = stack_memory;
    signal_stack.ss_size = SIGSTKSZ;
    signal_stack.ss_flags = 0;
    sigaltstack(&signal_stack, &prev_signal_stack);

    struct sigaction signal_action = {};
    signal_action.sa_handler = signal_handler;
    signal_action.sa_flags = SA_ONSTACK;

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
