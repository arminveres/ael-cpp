#include "ael/boards/pico/spi.hpp"
#include "ael/boards/pico/gpio.hpp"

using namespace ael::boards::pico;

int main() {
    // RX Pin
    static constexpr auto MISO_PIN = 8;
    static constexpr auto CS_PIN = 9;
    static constexpr auto CLK_PIN = 10;
    // TX Pin
    static constexpr auto MOSI_PIN = 11;

    spi::SPI<spi::eInstSPI::SPI_0, CS_PIN, CLK_PIN, MOSI_PIN, MISO_PIN, 10'000 * 1000> spi_inst;

    // static constexpr auto RST_PIN = 12;
    GPIO<12, eGPIODir::OUT> RST_PIN;

    // static constexpr auto BL_PIN = 13;
    GPIO<13, eGPIODir::OUT> BL_PIN;

    BL_PIN.set();

    return 0;
}
