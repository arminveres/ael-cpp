#ifndef __AEL_PERIPHERALS_LIS3DH_LIS3DH_HPP
#define __AEL_PERIPHERALS_LIS3DH_LIS3DH_HPP
#include <optional>

#include "ael/types.hpp"

namespace ael::peripherals::lis3dh {

/**
 * @brief Interface class to be implemented by board specifics
 *
 * @todo
 *  - add more optional or expected return types
 */
class I_LIS3DH {
   public:
    /**
     * @brief Acceleration data in signed 16 bit integers
     */
    struct Accel {
        types::i16 x;
        types::i16 y;
        types::i16 z;
    };

    virtual ~I_LIS3DH(){};

    virtual auto init() -> std::optional<types::eError> = 0;
    virtual auto reg_set(const types::u8 reg, const types::u8 value) const -> void = 0;
    virtual auto reg_update(const types::u8 reg, const types::u8 val) const -> void = 0;
    [[nodiscard]] virtual auto reg_read(const types::u8 reg) const -> types::u8 = 0;
    [[nodiscard]] virtual auto read_accel() const -> Accel = 0;

    // auto reset() -> void {
    //     // const u8 reg[8] = {0};
    //     const u8 reg = {0};
    //     reg_set(reg_addr::TEMP_CFG, reg);
    //     reg_set(reg_addr::FIFO_CTRL, reg);
    //     reg_set(reg_addr::INT1_CFG, reg);
    //     reg_set(reg_addr::INT1_THS, reg);
    //     reg_set(reg_addr::INT2_CFG, reg);
    //     reg_set(reg_addr::INT2_THS, reg);
    //     reg_set(reg_addr::CLICK_CFG, reg);
    //     reg_set(reg_addr::CLICK_THS, reg);
    // }

   private:
};

}  // namespace ael::peripherals::lis3dh
#endif
