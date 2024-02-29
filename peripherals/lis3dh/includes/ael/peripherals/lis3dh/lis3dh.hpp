#ifndef __AEL_PERIPHERALS_LIS3DH_LIS3DH_HPP
#define __AEL_PERIPHERALS_LIS3DH_LIS3DH_HPP
#include "ael/types.hpp"

namespace ael::peripherals::lis3dh {
using namespace ael::types;

class I_LIS3DH {
   public:
    /**
     * @brief Acceleration data in signed 16 bit integers
     */
    struct Accel {
        i16 x;
        i16 y;
        i16 z;
    };
    // I_LIS3DH() = default;
    // I_LIS3DH(I_LIS3DH &&) = delete;
    // I_LIS3DH(const I_LIS3DH &) = delete;
    // virtual I_LIS3DH &operator=(I_LIS3DH &&) = delete;
    // virtual I_LIS3DH &operator=(const I_LIS3DH &) = delete;

    virtual ~I_LIS3DH(){};

    virtual auto init() -> void = 0;
    virtual auto reg_set(const u8 reg, const u8 value) const -> void = 0;
    virtual auto reg_update(const u8 reg, const u8 val) const -> void = 0;
    [[nodiscard]] virtual auto reg_read(const u8 reg) const -> u8 = 0;
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
