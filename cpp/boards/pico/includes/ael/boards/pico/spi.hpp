#ifndef __AEL_BOARDS_PICO_SPI_HPP
#define __AEL_BOARDS_PICO_SPI_HPP
#include <hardware/gpio.h>
#include <hardware/spi.h>
#include <pico/stdlib.h>

#include <cstdio>

#include "ael/boards/pico/gpio.hpp"
#include "ael/types.hpp"

namespace ael::boards::pico::spi {

using namespace types;

// FIXME(aver): remove
static constexpr u8 LIS3DH_SPI_READ_FLAG = 0x80;
static constexpr u8 LIS3DH_SPI_WRITE_FLAG = 0x00;
static constexpr u8 LIS3DH_SPI_AUTO_INC_FLAG = 0x40;

enum class eInstSPI { SPI_0, SPI_1 };

/**
 * SPI Class holding all necessary methods
 *
 * @warn : DO NOT use multiple instances of SPIs
 */

template <eInstSPI SPI_INSTANCE, u8 CS, u8 SCLK, u8 TX, u8 RX, u32 SPI_SPEED>
class SPI {
   public:
    SPI() {
        // Pico Initialization of SPI
        spi_init(this->get_instance(), SPI_SPEED);
        gpio_set_function(SCLK, GPIO_FUNC_SPI);
        gpio_set_function(TX, GPIO_FUNC_SPI);
        gpio_set_function(RX, GPIO_FUNC_SPI);
        CS_PIN.set();
        RX_PIN.clear();
        sleep_ms(50);
        spi_set_format(this->get_instance(), 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
    }

    SPI(SPI &&) = delete;
    SPI(const SPI &) = delete;
    SPI &operator=(SPI &&) = delete;
    SPI &operator=(const SPI &) = delete;

    ~SPI() { spi_deinit(this->get_instance()); }

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
        const u8 tx = (reg) | (mb << 6) | LIS3DH_SPI_READ_FLAG | LIS3DH_SPI_AUTO_INC_FLAG;

        // u8 rx[buflen + 1];
        // memset(rx, 0xff, buflen + 1);

        // auto bytes_read = spi_write_read_blocking(get_instance(), buf, &msg, buflen + 1);

        spi_write_blocking(this->get_instance(), &tx, 1);

        auto bytes_read = spi_read_blocking(this->get_instance(), 0, buf, buflen);

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
        spi_write_blocking(this->get_instance(), msg, len);
        CS_PIN.set();
    }

    auto rupdate(const u8 reg, const u8 data) -> void {
        CS_PIN.clear();
        constexpr auto len = 2;

        // get old val und use it to update
        u8 reg_val = 0;
        if (not spi_read_blocking(this->get_instance(), 0, &reg_val, 1))
            printf("ERROR while reading register\n");
        // printf("Status: 0b%b\n", reg_val);

        // Construct message (set ~W bit low, MB bit low)
        u8 msg[len];
        msg[0] = 0x00 | reg;
        msg[1] = reg_val | data;

        // Write to register
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

}  // namespace ael::boards::pico::spi
#endif  // !__AEL_BOARDS_PICO_SPI_HPP
