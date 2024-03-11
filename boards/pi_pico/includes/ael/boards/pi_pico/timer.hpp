#ifndef __AEL_BOARDS_PI_PICO_TIMER_HPP
#define __AEL_BOARDS_PI_PICO_TIMER_HPP
#include <hardware/timer.h>

#include <tuple>

#include "ael/types.hpp"

using namespace ael::types;

namespace ael::boards::pi_pico::timer {

using TimeStamp = std::tuple<u8, u8, u8>;

enum class eTimeType { eMicro, eMilli, eSec };

template <eTimeType type>
struct Timer {
    auto start() -> Timer& {
        m_start_time = time_us_64();
        return *this;
    };

    [[nodiscard]] auto stop() -> u64 {
        const auto end = time_us_64();
        const auto diff = end - this->m_start_time;
        assert(diff != end);

        this->m_start_time = 0;
        if constexpr (type == eTimeType::eMicro)
            return diff;
        else if constexpr (type == eTimeType::eMilli)
            return diff / 1000;
        else if constexpr (type == eTimeType::eSec)
            return diff / (1000 * 1000);
    };

    [[nodiscard]] auto get_now() const -> u64 {
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
    [[nodiscard]] auto get_now_triple() const -> TimeStamp {
        return convert_to_tuple(this->get_now());
    }

    /**
     * @brief Stops the clock and returns the current time in Hours, Minutes and Seconds as a tuple
     */
    [[nodiscard]] auto stop_with_triple() -> TimeStamp { return convert_to_tuple(this->stop()); }

   private:
    /// start time in microseconds
    u64 m_start_time = 0;

    /**
     * @brief Convert time to timestep in Hours, Minutes and seconds
     */
    static auto convert_to_tuple(const u64 now) -> TimeStamp {
        auto now_s = 0u;
        if constexpr (type == eTimeType::eMicro) {
            now_s = now / (1000u * 1000u);
        } else if constexpr (type == eTimeType::eMilli) {
            now_s = now / 1000u;
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
