#ifndef __AEL_BOARDS_PI_PICO_TIMER_HPP
#define __AEL_BOARDS_PI_PICO_TIMER_HPP
#include <hardware/timer.h>

#include "ael/types.hpp"

using namespace ael::types;
namespace ael::boards::pi_pico::timer {

enum class eTimeType { eMicro, eMilli, eSec };

template <eTimeType type>
struct Timer {
    auto start() -> void { start_time = time_us_64(); };
    [[nodiscard]] auto stop() -> u64 {
        const auto end = time_us_64();
        const auto diff = end - start_time;
        assert(diff != end);

        start_time = 0;
        if constexpr (type == eTimeType::eMicro)
            return diff;
        else if constexpr (type == eTimeType::eMilli)
            return diff / 1000;
        else if constexpr (type == eTimeType::eSec)
            return diff / 1000 * 1000;
    };

    [[nodiscard]] auto get_now() -> u64 {
        if constexpr (type == eTimeType::eMicro)
            return start_time;
        else if constexpr (type == eTimeType::eMilli)
            return start_time / 1000;
        else if constexpr (type == eTimeType::eSec)
            return start_time / (1000 * 1000);
    }

   private:
    /// start time in microseconds
    u64 start_time = 0;
};
}  // namespace ael::boards::pi_pico::timer

#endif  // !__AEL_BOARDS_PI_PICO_TIMER_HPP
