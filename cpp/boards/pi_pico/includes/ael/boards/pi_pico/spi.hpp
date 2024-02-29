#ifndef __AEL_BOARDS_PICO_SPI_HPP
#define __AEL_BOARDS_PICO_SPI_HPP
#include <hardware/gpio.h>
#include <hardware/spi.h>
#include <pico/stdlib.h>

#include <cstdio>

#include "ael/boards/pi_pico/gpio.hpp"
#include "ael/types.hpp"

namespace ael::boards::pi_pico::spi {

using namespace types;
using namespace gpio;

enum class eInstSPI { SPI_0, SPI_1 };

/**
 * SPI Class holding all necessary methods
 *
 * @warn : DO NOT use multiple instances of SPIs
 */

// template <eInstSPI SPI_INSTANCE, u8 CS, u8 SCLK, u8 TX, u8 RX, u32 SPI_SPEED>
class SPI {
   public:
    SPI(const eInstSPI espi,
        const u8 CSpin,
        const u8 SCLKpin,
        const u8 TXpin,
        const u8 RXpin,
        const u32 spi_speed)
        : RX_PIN(RXpin), CS_PIN(CSpin) {
        if (espi == eInstSPI::SPI_0) {
            m_spi = spi0;
        } else {
            m_spi = spi1;
        }
        // Pico Initialization of SPI
        spi_init(m_spi, spi_speed);
        gpio_set_function(SCLKpin, GPIO_FUNC_SPI);
        gpio_set_function(TXpin, GPIO_FUNC_SPI);
        gpio_set_function(RXpin, GPIO_FUNC_SPI);
        CS_PIN.set();
        RX_PIN.clear();
        spi_set_format(m_spi, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
    }

    SPI(SPI &&) = delete;
    SPI(const SPI &) = delete;
    SPI &operator=(SPI &&) = delete;
    SPI &operator=(const SPI &) = delete;

    ~SPI() { spi_deinit(m_spi); }

    /**
     * @brief Read from a register
     *
     * @returns Number of bytes read
     */
    template <u8 buflen>
    [[maybe_unused]] auto rread(const u8 reg, u8 buf[]) -> u8 {
        CS_PIN.clear();  // set chip select to low, to indicate transmission

        constexpr auto mb = buflen == 1 ? 0u : 1u;

        // u8 tx = (READ_OP | (mb << 6) | reg);  // construct msg
        const u8 tx = (reg) | (mb << 6);

        // u8 rx[buflen + 1];
        // memset(rx, 0xff, buflen + 1);

        // auto bytes_read = spi_write_read_blocking(get_instance(), buf, &msg, buflen + 1);

        spi_write_blocking(m_spi, &tx, 1);

        auto bytes_read = spi_read_blocking(m_spi, 0, buf, buflen);

        // auto bytes_read = spi_read_blocking(this->get_instance(), 0, rx, buflen);
        // for (size_t i = 0; i < buflen; i++) {
        //     // shift above one because of invalid byte
        //     buf[i] = rx[i + 1];
        // }

        CS_PIN.set();  // set back to high -> no transmission
        return bytes_read;
    }

    /**
     * @brief Write Data to register
     */
    template <u8 buflen>
    auto rwrite(const u8 reg, const u8 data[]) -> void {
        CS_PIN.clear();

        constexpr auto len = 1 + buflen;
        u8 msg[len];

        // Construct message (set ~W bit low, MB bit low)
        msg[0] = 0x00 | reg;
        // msg[1] = data;

        for (auto i = 0u; i < buflen; ++i) {
            msg[i + 1] = data[i];
        }

        // Write to register
        spi_write_blocking(this->m_spi, msg, len);
        CS_PIN.set();
    }

    auto rupdate(const u8 reg, const u8 data) -> void {
        CS_PIN.clear();
        constexpr auto len = 2;

        // get old val und use it to update
        u8 reg_val = 0;
        if (not spi_read_blocking(this->m_spi, 0, &reg_val, 1))
            printf("ERROR while reading register\n");
        // printf("Status: 0b%b\n", reg_val);

        // Construct message (set ~W bit low, MB bit low)
        u8 msg[len];
        msg[0] = 0x00 | reg;
        msg[1] = reg_val | data;

        // Write to register
        spi_write_blocking(this->m_spi, msg, len);
        CS_PIN.set();
    }

   private:
    GPIO<eGPIODir::OUT> RX_PIN;
    GPIO<eGPIODir::OUT> CS_PIN;
    spi_inst_t *m_spi;
};

}  // namespace ael::boards::pi_pico::spi
#endif  // !__AEL_BOARDS_PICO_SPI_HPP
