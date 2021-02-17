#ifndef CB_LOG_HPP__
#define CB_LOG_HPP__

#include <spdlog/spdlog.h>
#include <memory>
#include <utility>

namespace CylinderBank
{
    class Log
    {
        public:
            Log() = default;
            
            static void init();

            template<typename Fmt, typename ...Args>
            inline static void core_trace(const Fmt fmt, Args&&... args)
            {
                core_logger->trace(fmt, std::forward<Args>(args)...);
            }
            template<typename Fmt, typename ...Args>
            inline static void core_info(const Fmt fmt, Args&&... args)
            {
                core_logger->info(fmt, std::forward<Args>(args)...);
            }
            template<typename Fmt, typename ...Args>
            inline static void core_warn(const Fmt fmt, Args&&... args)
            {
                core_logger->warn(fmt, std::forward<Args>(args)...);
            }
            template<typename Fmt, typename ...Args>
            inline static void core_error(const Fmt fmt, Args&&... args)
            {
                core_logger->error(fmt, std::forward<Args>(args)...);
            }
            template<typename Fmt, typename ...Args>
            inline static void core_critical(const Fmt fmt, Args&&... args)
            {
                core_logger->critical(fmt, std::forward<Args>(args)...);
            }

            template<typename Fmt, typename ...Args>
            inline static void trace(const Fmt fmt, Args&&... args)
            {
                client_logger->trace(fmt, std::forward<Args>(args)...);
            }
            template<typename Fmt, typename ...Args>
            inline static void info(const Fmt fmt, Args&&... args)
            {
                client_logger->info(fmt, std::forward<Args>(args)...);
            }
            template<typename Fmt, typename ...Args>
            inline static void warn(const Fmt fmt, Args&&... args)
            {
                client_logger->warn(fmt, std::forward<Args>(args)...);
            }
            template<typename Fmt, typename ...Args>
            inline static void error(const Fmt fmt, Args&&... args)
            {
                client_logger->error(fmt, std::forward<Args>(args)...);
            }
            template<typename Fmt, typename ...Args>
            inline static void critical(const Fmt fmt, Args&&... args)
            {
                client_logger->critical(fmt, std::forward<Args>(args)...);
            }

        private:
            static std::shared_ptr<spdlog::logger> core_logger;
            static std::shared_ptr<spdlog::logger> client_logger;
    };
}

#endif // CB_LOG_HPP__
