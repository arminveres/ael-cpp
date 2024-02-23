#ifndef __AEL_BOARDS_PICO_SPI_HPP
#define __AEL_BOARDS_PICO_SPI_HPP
#include <hardware/gpio.h>
#include <hardware/spi.h>

#include <array>
#include <limits>

#include "ael/boards/pico/gpio.hpp"
#include "ael/types.hpp"

namespace ael::boards::pico {

enum class eInstSPI { SPI_0, SPI_1 };

/**
 * SPI Class holding all necessary methods
 *
 * @warn : DO NOT use multiple instances of SPIs
 */
template <eInstSPI SPI_INSTANCE, u8 CS, u8 SCLK, u8 TX, u8 RX, u32 SPI_SPEED>
class SPI {
   public:
    // using spi_buf = std::array<ael::u8, std::numeric_limits<ael::u8>::max()>;
    template <u8 no>
    using spi_buf = std::array<ael::u8, no>;

    SPI() {
        // Pico Initialization of SPI
        spi_init(this->get_instance(), SPI_SPEED);
        gpio_set_function(SCLK, GPIO_FUNC_SPI);
        gpio_set_function(TX, GPIO_FUNC_SPI);
        CS_PIN.set();
        RX_PIN.clear();
    }

    SPI(SPI &&) = default;
    SPI(const SPI &) = default;
    SPI &operator=(SPI &&) = default;
    SPI &operator=(const SPI &) = default;

    ~SPI() { spi_deinit(this->get_instance()); }

    /**
     * @brief: Read from a register
     *
     * @returns Number of bytes read
     */
    template <u8 no>
    auto read(const u8 reg, const spi_buf<no> &buf) -> u8 {
        auto mb = buf.size() == 1 ? 0u : 1u;
        CS_PIN.clear();                        // set chip select to low, to indicate transmission
        u8 msg = (READ_OP | (mb << 6) | reg);  // construct msg
        spi_write_blocking(this->get_instance(), &msg, 1);
        auto bytes_read = spi_read_blocking(this->get_instance(), 0, buf, buf.size());
        CS_PIN.set();  // set back to high -> not transmission
        return bytes_read;
    }

    /**
     * @brief Write Data to register
     */
    template <u8 no>
    auto write(const u8 reg, const spi_buf<no> &data) {
        constexpr auto len = 1 + data.size;
        u8 msg[len];

        // Construct message (set ~W bit low, MB bit low)
        msg[0] = 0x00 | reg;
        // msg[1] = data;

        auto i = 0u;
        for (const auto &val : data) {
            msg[++i] = val;
        }

        // Write to register
        CS_PIN.clear();
        spi_write_blocking(this->get_instance(), msg, len);
        CS_PIN.set();
    }

   private:
    static constexpr u8 READ_OP = 0x80;
    GPIO<RX, eGPIODir::OUT> RX_PIN;
    GPIO<CS, eGPIODir::OUT> CS_PIN;

    /// Return the correct SPI instance
    constexpr auto get_instance() -> spi_inst_t * {
        if constexpr (SPI_INSTANCE == eInstSPI::SPI_0)
            return spi0;
        else
            return spi1;
    }
};

}  // namespace ael::boards::pico
#endif  // !__AEL_BOARDS_PICO_SPI_HPP
