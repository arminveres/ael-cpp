#ifndef __AEL_BOARDS_PI_PICO_EXTRAS_HPP
#define __AEL_BOARDS_PI_PICO_EXTRAS_HPP
#include <optional>

#include "../spi.hpp"
#include "ael/peripherals/lis3dh/lis3dh.hpp"
#include "ael/peripherals/lis3dh/registers.hpp"
#include "ael/types.hpp"

namespace ael::boards::pi_pico::extras::lis3dh {
using namespace ael::boards::pi_pico::spi;
using namespace ael::types;
using namespace ael::peripherals::lis3dh;

class LIS3DH : private I_LIS3DH {
   public:
    static constexpr u8 LIS3DH_ID = 0x33;

    explicit LIS3DH(spi::SPI& p_spi,
                    const types::u8 sampling_rate = peripherals::lis3dh::reg_ctrl1::RATE_10_HZ);
    ~LIS3DH();

    // LIS3DH() = delete;
    // LIS3DH(LIS3DH &&) = delete;
    // LIS3DH(const LIS3DH &) = delete;
    // LIS3DH &operator=(LIS3DH &&) = delete;
    // LIS3DH &operator=(const LIS3DH &) = delete;

    auto init() -> std::optional<eError> override;
    auto reg_set(const u8 reg, const u8 value) const -> void override;
    auto reg_update(const u8 reg, const u8 val) const -> void override;
    [[nodiscard]] auto reg_read(const u8 reg) const -> u8 override;
    [[nodiscard]] auto read_accel() const -> Accel override;

   private:
    static constexpr u8 LIS3DH_SPI_READ_FLAG = 0x80;
    static constexpr u8 LIS3DH_SPI_WRITE_FLAG = 0x00;
    static constexpr u8 LIS3DH_SPI_AUTO_INC_FLAG = 0x40;

    SPI& m_spi;

    /**
     * @brief Convert an unsigned 2 Byte to signed 16byte
     *
     * @source http://tpcg.io/NHmBRR
     */
    template <u8 nobits>
    constexpr static auto convert_to_signed(const u16 inp) -> i16 {
        u16 trim = inp >> (16 - nobits);
        i16 convertedValueI16 = 0;
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
            convertedValueI16 = static_cast<i16>(trim);
        }
        return convertedValueI16;
    }
};
}  // namespace ael::boards::pi_pico::extras::lis3dh
#endif  // !__AEL_BOARDS_PI_PICO_EXTRAS_HPP
