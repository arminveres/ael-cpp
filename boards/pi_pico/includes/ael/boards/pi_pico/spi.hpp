#ifndef __AEL_BOARDS_PICO_SPI_HPP
#define __AEL_BOARDS_PICO_SPI_HPP
#include <hardware/gpio.h>
#include <hardware/spi.h>
#include <pico/stdlib.h>

#include <cstdio>

#include "ael/boards/pi_pico/gpio.hpp"
#include "ael/types.hpp"

namespace ael::boards::pi_pico::spi {

enum class eInstSPI { SPI_0, SPI_1 };

/**
 * SPI Class holding all necessary methods
 *
 * @warn : DO NOT use multiple instances of SPIs
 */

// template <eInstSPI SPI_INSTANCE, u8 CS, u8 SCLK, u8 TX, u8 RX, u32 SPI_SPEED>
class SPI {
   public:
    explicit SPI(const eInstSPI espi,
                 const types::u8 CSpin,
                 const types::u8 SCLKpin,
                 const types::u8 TXpin,
                 const types::u8 RXpin,
                 const types::u32 spi_speed)
        : CS_PIN(CSpin) {
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
        spi_set_format(m_spi, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
    }

    // SPI(){}
    // SPI(SPI &&) = delete;
    // SPI(const SPI &) = delete;
    // SPI &operator=(SPI &&) = delete;
    // SPI &operator=(const SPI &) = delete;

    ~SPI() { spi_deinit(m_spi); }

    /**
     * @brief Read from a register
     *
     * @returns Number of bytes read
     */
    template <types::u8 buflen>
    [[maybe_unused]] auto rread(const types::u8 reg, types::u8 buf[]) -> types::u8 {
        GPIO_Lock spi_lock(CS_PIN);
        constexpr auto mb = buflen == 1 ? 0u : 1u;
        const types::u8 tx = (reg) | (mb << 6);

        // u8 rx[buflen + 1];
        // memset(rx, 0xff, buflen + 1);
        // auto bytes_read = spi_write_read_blocking(m_spi, buf, rx, buflen + 1);

        spi_write_blocking(m_spi, &tx, 1);
        types::u8 bytes_read = spi_read_blocking(m_spi, 0, buf, buflen);

        // auto bytes_read = spi_read_blocking(this->get_instance(), 0, rx, buflen);
        // for (size_t i = 0; i < buflen; i++) {
        //     // shift above one because of invalid byte
        //     buf[i] = rx[i + 1];
        // }

        return bytes_read;
    }

    /**
     * @brief Write Data to register
     */
    template <types::u8 buflen>
    auto rwrite(const types::u8 reg, const types::u8 data[]) -> void {
        GPIO_Lock spi_lock(CS_PIN);

        constexpr auto len = 1 + buflen;
        types::u8 msg[len];

        // Construct message (set ~W bit low, MB bit low)
        msg[0] = 0x00 | reg;
        // msg[1] = data;

        for (auto i = 0u; i < buflen; ++i) {
            msg[i + 1] = data[i];
        }

        // Write to register
        spi_write_blocking(this->m_spi, msg, len);
    }

    auto rupdate(const types::u8 reg, const types::u8 data) -> void {
        GPIO_Lock spi_lock(CS_PIN);
        constexpr auto len = 2;

        // get old val und use it to update
        types::u8 reg_val = 0;
        if (not spi_read_blocking(this->m_spi, 0, &reg_val, 1))
            printf("ERROR while reading register\n");
        // printf("Status: 0b%b\n", reg_val);

        // Construct message (set ~W bit low, MB bit low)
        types::u8 msg[len];
        msg[0] = 0x00 | reg;
        msg[1] = reg_val | data;

        // Write to register
        spi_write_blocking(this->m_spi, msg, len);
    }

   private:
    gpio::GPIO<gpio::eGPIODir::OUT> CS_PIN;
    spi_inst_t *m_spi;

    /**
     * @brief Little helper class to clear and set the spi line
     */
    template <gpio::eGPIODir dir>
    struct GPIO_Lock {
        GPIO_Lock(gpio::GPIO<dir> &pin) : m_pin(pin) {
            // set chip select to low, to indicate transmission
            m_pin.clear();
        }
        ~GPIO_Lock() {
            // set back to high -> no transmission
            m_pin.set();
        }

       private:
        gpio::GPIO<dir> &m_pin;
    };
};

}  // namespace ael::boards::pi_pico::spi
#endif  // !__AEL_BOARDS_PICO_SPI_HPP
