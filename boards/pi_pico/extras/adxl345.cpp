#include "ael/boards/pi_pico/extras/adxl345.hpp"

#include <pico/platform.h>
#include <pico/stdlib.h>

#include <expected>

#include "ael/boards/pi_pico/spi.hpp"
#include "ael/peripherals/adxl345/registers.hpp"
#include "ael/types.hpp"
#include "pico/time.h"

using namespace ael::boards::pi_pico::extras::adxl345;
using namespace ael::boards::pi_pico::spi;
using namespace ael::types;
using namespace ael::peripherals::adxl345;

ADXL345::ADXL345(SPI &p_spi, const u8 sampling_rate)
    : m_spi(p_spi), m_sampling_rate(sampling_rate) {}

ADXL345::~ADXL345() {}

auto ADXL345::init() -> std::expected<void, eError> {
    this->reg_set(ADXL345_REG_POWER_CTL, 0x08);
    return {};
}

auto ADXL345::reg_set(const u8 reg, const u8 value) const -> void { m_spi.rwrite<1>(reg, &value); }

auto ADXL345::reg_update(const u8 reg, const u8 val) const -> void { m_spi.rupdate(reg, val); }

[[nodiscard]] auto ADXL345::reg_read(const u8 reg) const -> u8 {
    u8 ldata = 255;
    const auto retval = m_spi.rread<1>(reg | READ_FLAG, &ldata);
    if (retval == 0) {
        // panic("PANIC: no data received...");
        while (true) {
            printf("no data read...\n");
            sleep_ms(1000);
        }
    }
    return ldata;
    // if (not m_spi->rread<1>(reg, &ldata)) return std::unexpected(eError::errorGeneric);
}

[[nodiscard]] auto ADXL345::read_accel() const -> Accel {
    u16 rawx, rawy, rawz;
    m_spi.rread<2>(ADXL345_REG_DATAX0 | READ_FLAG | AUTO_INCREMENT_FLAG,
                   reinterpret_cast<u8 *>(&rawx));
    m_spi.rread<2>(ADXL345_REG_DATAY0 | READ_FLAG | AUTO_INCREMENT_FLAG,
                   reinterpret_cast<u8 *>(&rawy));
    m_spi.rread<2>(ADXL345_REG_DATAZ0 | READ_FLAG | AUTO_INCREMENT_FLAG,
                   reinterpret_cast<u8 *>(&rawz));

    return Accel{rawx, rawy, rawz};
}
