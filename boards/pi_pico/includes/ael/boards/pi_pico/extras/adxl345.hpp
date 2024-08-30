#ifndef __AEL_BOARDS_PI_PICO_EXTRAS_ADXL345_HPP
#define __AEL_BOARDS_PI_PICO_EXTRAS_ADXL345_HPP
#include <expected>

#include "../spi.hpp"
#include "ael/drivers/interfaces/accelerometer.hpp"
#include "ael/types.hpp"

namespace ael::boards::pi_pico::extras::adxl345 {

class ADXL345 : private drivers::interfaces::I_Accelerometer {
   public:
    static constexpr types::u8 ADXL345_ID = 0xE5;

    explicit ADXL345(spi::SPI& p_spi, const types::u8 sampling_rate = 0);
    ~ADXL345();

    auto init() -> std::expected<void, types::eError> override;
    auto reg_set(const types::u8 reg, const types::u8 value) const -> void override;
    auto reg_update(const types::u8 reg, const types::u8 val) const -> void override;
    [[nodiscard]] auto reg_read(const types::u8 reg) const -> types::u8 override;
    [[nodiscard]] auto read_accel() const -> Accel override;

   private:
    spi::SPI& m_spi;
    types::u8 m_sampling_rate;
};

}  // namespace ael::boards::pi_pico::extras::adxl345

#endif  // !__AEL_BOARDS_PI_PICO_EXTRAS_ADXL345_HPP
