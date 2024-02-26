#include "ael/boards/pi_pico/extras/lis3dh.hpp"

#include <pico/stdlib.h>

#include "ael/boards/pi_pico/spi.hpp"
#include "ael/peripherals/lis3dh/registers.hpp"
#include "ael/types.hpp"

using namespace ael::boards::pi_pico::extras::lis3dh;
using namespace ael::boards::pi_pico::spi;
using namespace ael::peripherals::lis3dh;
using namespace ael::types;

LIS3DH::LIS3DH(SPI &p_spi) : m_spi(p_spi) {
    printf("Hi\n");
    constexpr reg_ctrl1 r1{
        .Xen = true,
        .Yen = true,
        .Zen = true,
        .LPen = false,
        .ODR = 10,
    };
    this->reg_set(reg_addr::CTRL1, r1.reg);

    // set High Pass Filter
    // auto val = regs::CTRL_REG2_FDS;  //| regs::CTRL_REG2_HPCLICK | ;

    constexpr reg_ctrl4 r4{.HR = false, .BDU = true};
    this->reg_set(reg_addr::CTRL4, r4.reg);

    // u8 ref;
    // spi.rread<1>(regs::REG_REFERENCE, &ref);
    // printf("ref: %02x\n", ref);

    constexpr reg_fifo_ctrl rfifo{.FM = reg_fifo_ctrl::BYPASS};
    this->reg_set(reg_addr::FIFO_CTRL, rfifo.reg);

    constexpr reg_temp_cfg rtemp{.TEMP_EN = true, .ADC_EN = true};
    this->reg_set(reg_temp_cfg::addr, rtemp.reg);
    printf("bye\n");
}

auto LIS3DH::reg_set(const u8 reg, const u8 value) -> std::expected<void, eError> const {
    m_spi.rwrite<1>(reg, &value);
}

auto LIS3DH::reg_update(const u8 reg, const u8 val) -> std::expected<void, eError> const {
    m_spi.rupdate(reg, val);
}

[[nodiscard]] auto LIS3DH::reg_read(const u8 reg) -> std::expected<u8, eError> const {
    u8 ldata;
    if (not m_spi.rread<1>(reg, &ldata)) return std::unexpected(eError::errorGeneric);
    return ldata;
}

[[nodiscard]] auto LIS3DH::read_accel() -> std::expected<Accel, eError> const {
    u16 rawx, rawy, rawz;
    m_spi.rread<2>(reg_addr::OUT_X_L, reinterpret_cast<u8 *>(&rawx));
    m_spi.rread<2>(reg_addr::OUT_Y_L, reinterpret_cast<u8 *>(&rawy));
    m_spi.rread<2>(reg_addr::OUT_Z_L, reinterpret_cast<u8 *>(&rawz));
    return Accel{.x = convert_to_signed<10>(rawx),
                 .y = convert_to_signed<10>(rawy),
                 .z = convert_to_signed<10>(rawz)};
}
