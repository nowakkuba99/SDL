#ifndef B48B6F7C_C8ED_4F71_AB61_6735D6F9879E
#define B48B6F7C_C8ED_4F71_AB61_6735D6F9879E
// Includes
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
// User defined includes

namespace Barrel
{
    class Log
    {
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    public:
        // Constructor
        Log();
        // Destructor
        ~Log();
        // Member functions
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;};
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;};

        static void Init();
    };
    
}

#endif /* B48B6F7C_C8ED_4F71_AB61_6735D6F9879E */
