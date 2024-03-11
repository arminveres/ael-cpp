#ifndef __AEL_BOARDS_PI_PICO_TIMER_HPP
#define __AEL_BOARDS_PI_PICO_TIMER_HPP
#include <hardware/timer.h>

#include <tuple>

#include "ael/types.hpp"

using namespace ael::types;

namespace ael::boards::pi_pico::timer {

using TimeStamp = std::tuple<u64, u64, u64>;

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
            return diff / (1000 * 1000);
    };

    [[nodiscard]] auto get_now() -> u64 {
        if constexpr (type == eTimeType::eMicro)
            return time_us_64();
        else if constexpr (type == eTimeType::eMilli)
            return time_us_64() / 1000;
        else if constexpr (type == eTimeType::eSec)
            return time_us_64() / (1000 * 1000);
    }

    /**
     * @brief Returns the current time in Hours, Minutes and Seconds as a tuple
     */
    [[nodiscard]] auto get_now_triple() -> TimeStamp { return convert_to_tuple(get_now()); }

    /**
     * @brief Stops the clock and returns the current time in Hours, Minutes and Seconds as a tuple
     */
    [[nodiscard]] auto stop_with_triple() -> TimeStamp { return convert_to_tuple(stop()); }

   private:
    /// start time in microseconds
    u64 start_time = 0;

    /**
     * @brief Convert time to timestep in Hours, Minutes and seconds
     */
    auto convert_to_tuple(const u64 now) -> TimeStamp {
        auto now_s = 0;
        if constexpr (type == eTimeType::eMicro) {
            now_s = now / (1000 * 1000);
        } else if constexpr (type == eTimeType::eMilli) {
            now_s = now / 1000;
        } else if constexpr (type == eTimeType::eSec) {
            now_s = now;
        }
        const auto hours = now_s / (60 * 60);
        auto rem_s = now % (60 * 60);
        const auto mins = rem_s / 60;
        rem_s = rem_s % 60;
        return {hours, mins, rem_s};
    }
};
}  // namespace ael::boards::pi_pico::timer

#endif  // !__AEL_BOARDS_PI_PICO_TIMER_HPP
