#ifndef __AEL_BOARDS_PICO_SPI_HPP
#define __AEL_BOARDS_PICO_SPI_HPP
#include <hardware/gpio.h>
#include <hardware/spi.h>

#include "ael/types.hpp"

namespace ael::boards::pico {

enum class eInstSPI { SPI_0, SPI_1 };

template <eInstSPI SPI_INSTANCE, u8 CS, u8 SCLK, u8 MOSI, u8 MISO, u32 SPI_SPEED>
class SPI {
   public:
    SPI() {
        // Pico Initialization of SPI
        if constexpr (SPI_INSTANCE == eInstSPI::SPI_0)
            spi_init(spi0, SPI_SPEED);
        else
            spi_init(spi1, SPI_SPEED);

        gpio_set_function(SCLK, GPIO_FUNC_SPI);
        gpio_set_function(MOSI, GPIO_FUNC_SPI);
    }
    SPI(SPI &&) = default;
    SPI(const SPI &) = default;
    SPI &operator=(SPI &&) = default;
    SPI &operator=(const SPI &) = default;
    ~SPI() {}

   private:
};

}  // namespace ael::boards::pico
#endif  // !__AEL_BOARDS_PICO_SPI_HPP
