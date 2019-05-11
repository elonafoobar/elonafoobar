#include <boost/predef.h>
#include "filepathutil.hpp"

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

constexpr int handled_signals_max = 6;
int handled_signals[handled_signals_max] =
    {SIGINT, SIGILL, SIGFPE, SIGSEGV, SIGTERM, SIGABRT};
struct sigaction prev_signal_actions[handled_signals_max];

#if BOOST_OS_LINUX
char stack_memory[SIGSTKSZ] = {};
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

constexpr size_t output_line_size = sizeof(void *) * 2 + 3;
constexpr size_t buffer_size = 50 + output_line_size * max_backtrace_frames;
char cmd_buffer[buffer_size];

FILE *addr2line(void **addresses, char **symbols, int address_count)
{
    int length;
    auto exe_path = filepathutil::get_executable_path();
    if (!exe_path)
    {
        return nullptr;
    }

#if BOOST_OS_LINUX
    length = snprintf(
        cmd_buffer,
        buffer_size,
        "addr2line -C -f -e \"%s\"",
        exe_path->c_str());
#elif BOOST_OS_MACOS
    length = snprintf(cmd_buffer, buffer_size, "atos -p %d", (int)getpid());
#endif

    if (length <= 0)
    {
        length = strlen(cmd_buffer);
    }

    for (int i = 0; i < address_count; i++)
    {
        void *address = addresses[i];

        // Get the symbol name. It seems that only some of the symbols are found
        // with dladdr, so parsing the address in the output of
        // backtrace_symbols() is needed.

        // Parse address in symbol "./Elona_foobar(+0x60000)""
        char *tmp = strstr(symbols[i], "(+0x");
        if (tmp)
        {
            address = (void *)strtoull(tmp + 4, nullptr, 16);
        }
        else
        {
            // Read dynamic library info.
            Dl_info info;
            if (dladdr(addresses[i], &info) && info.dli_saddr)
            {
                address =
                    (char *)((char *)addresses[i] - (char *)info.dli_fbase);
            }
        }
        snprintf(&cmd_buffer[length], buffer_size - length, " %p", address);
        length = strlen(cmd_buffer);
    }

    return popen(cmd_buffer, "r");
}

char *get_demangled(void *address)
{
    char *demangled = nullptr;
    Dl_info info;

    if (dladdr(address, &info) && info.dli_sname)
    {
        int status;

        if (info.dli_sname[0] == '_')
        {
            demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);

            if (status != 0)
            {
                demangled = nullptr;
            }
        }
    }

    return demangled;
}

void signal_handler(int signal)
{
    void *addresses[max_backtrace_frames];

    int frame_count = backtrace(addresses, max_backtrace_frames);
    char **symbols = backtrace_symbols(addresses, frame_count);

    printf("Received signal %d: %s\n", signal, strsignal(signal));

    if (symbols == nullptr)
    {
        perror("couldn't get backtrace");
        exit(1);
    }

    reset_signal_handlers();

    // Convert addresses to source file locations where possible.
    constexpr int line_buffer_size = 1035;
    FILE *lines = addr2line(addresses, symbols, frame_count);
    char line_buffer[line_buffer_size];

    printf("Backtrace:\n");
    for (int i = 0; i < frame_count; i++)
    {
        bool do_free = false;
        char *demangled = nullptr;
        const char *line = symbols[i];

        if (lines != nullptr)
        {
            // Read line from addr2line/atos.
            demangled = fgets(line_buffer, line_buffer_size, lines);
            line_buffer[strlen(line_buffer) - 1] = '\0';
        }

        if (demangled != nullptr)
        {
            // Skip lines not found by addr2line/atos.
            if (strcmp(line_buffer, "??") != 0)
            {
                line = line_buffer;
            }
        }
        else
        {
            // Use the C++ ABI.
            demangled = get_demangled(addresses[i]);
            if (demangled != nullptr)
            {
                line = demangled;
                do_free = true;
            }
        }

        // Print address and symbol name.
        printf(
            "%-3d %*p %s\n", i, (int)output_line_size - 1, addresses[i], line);

        if (lines != nullptr)
        {
            // Print source file location.
            if (fgets(line_buffer, line_buffer_size - 1, lines) != nullptr)
            {
                if (strcmp(line_buffer, "??:0\n") != 0)
                {
                    printf(
                        "%*sat %s", (int)output_line_size + 4, "", line_buffer);
                }
            }
        }

        if (do_free)
        {
            free(demangled);
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

    // Backtrace doesn't seem to be output if signal stack is changed in macOS.
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
