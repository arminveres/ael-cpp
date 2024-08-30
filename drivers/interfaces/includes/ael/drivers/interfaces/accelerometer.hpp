#ifndef __AEL_DRIVERS_INTERFACES_ACCELEROMETER_HPP
#define __AEL_DRIVERS_INTERFACES_ACCELEROMETER_HPP
#include <expected>

#include "ael/types.hpp"

namespace ael::drivers::interfaces {

/**
 * @brief Interface class to be implemented by board specifics
 *
 * @todo
 *  - add more optional or expected return types
 *  - consider CRTP style inheritance to forego dynamic dispatch
 */
class I_Accelerometer {
   public:
    /**
     * @brief Acceleration data in signed 16 bit integers
     */
    struct Accel {
        types::i16 x;
        types::i16 y;
        types::i16 z;
    };

    virtual ~I_Accelerometer(){};

    virtual auto init() -> std::expected<void, types::eError> = 0;
    virtual auto reg_set(const types::u8 reg, const types::u8 value) const -> void = 0;
    virtual auto reg_update(const types::u8 reg, const types::u8 val) const -> void = 0;
    [[nodiscard]] virtual auto reg_read(const types::u8 reg) const -> types::u8 = 0;
    [[nodiscard]] virtual auto read_accel() const -> Accel = 0;

   private:
};

}  // namespace ael::drivers::interfaces
#endif
