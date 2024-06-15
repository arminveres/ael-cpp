#ifndef __AEL_BOARDS_PI_PICO_EXTRAS_HPP
#define __AEL_BOARDS_PI_PICO_EXTRAS_HPP
#include <optional>

#include "../spi.hpp"
#include "ael/peripherals/interfaces/accelerometer.hpp"
#include "ael/peripherals/lis3dh/registers.hpp"
#include "ael/types.hpp"

namespace ael::boards::pi_pico::extras::lis3dh {

class LIS3DH : private peripherals::interfaces::I_Accelerometer {
   public:
    static constexpr types::u8 LIS3DH_ID = 0x33;

    explicit LIS3DH(spi::SPI& p_spi,
                    const types::u8 sampling_rate = peripherals::lis3dh::reg_ctrl1::RATE_10_HZ);
    ~LIS3DH();

    auto init() -> std::optional<types::eError> override;
    auto reg_set(const types::u8 reg, const types::u8 value) const -> void override;
    auto reg_update(const types::u8 reg, const types::u8 val) const -> void override;
    [[nodiscard]] auto reg_read(const types::u8 reg) const -> types::u8 override;
    [[nodiscard]] auto read_accel() const -> Accel override;

   private:
    spi::SPI& m_spi;
    types::u8 m_sampling_rate;

    /**
     * @brief Convert an unsigned 2 Byte to signed 16byte
     *
     * @source http://tpcg.io/NHmBRR
     */
    template <types::u8 nobits>
    constexpr static auto convert_to_signed(const types::u16 inp) -> types::i16 {
        types::u16 trim = inp >> (16 - nobits);
        types::i16 convertedValueI16 = 0;
        // Need to handle negative number
        if ((trim & (0x0001 << (nobits - 1))) == (0x0001 << (nobits - 1))) {
            convertedValueI16 = ~trim;                       // invert bits
            convertedValueI16 &= (0xFFFF >> (16 - nobits));  // but keep just the 10-bits
            convertedValueI16 += 1;                          // add 1
            convertedValueI16 *= -1;                         // multiply by -1
            // NOTE: that the last two lines could be replaced by convertedValueI16 =
            // convertedValueI16 = ~convertedValueI16;
        } else {
            // positive number, just pass it through
            convertedValueI16 = static_cast<types::i16>(trim);
        }
        return convertedValueI16;
    }
};
}  // namespace ael::boards::pi_pico::extras::lis3dh
#endif  // !__AEL_BOARDS_PI_PICO_EXTRAS_HPP
