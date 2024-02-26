#include "ael/boards/pi_pico/gpio.hpp"
#include "ael/boards/pi_pico/spi.hpp"

using namespace ael::boards::pi_pico;
using namespace ael::boards::pi_pico::spi;
using namespace ael::boards::pi_pico::gpio;

int main() {
    // RX Pin
    static constexpr auto MISO_PIN = 8;
    static constexpr auto CS_PIN = 9;
    static constexpr auto CLK_PIN = 10;
    // TX Pin
    static constexpr auto MOSI_PIN = 11;

    spi::SPI spi_inst(spi::eInstSPI::SPI_0, CS_PIN, CLK_PIN, MOSI_PIN, MISO_PIN, 10'000 * 1000);

    // static constexpr auto RST_PIN = 12;
    GPIO<eGPIODir::OUT> RST_PIN(12);

    // static constexpr auto BL_PIN = 13;
    GPIO<eGPIODir::OUT> BL_PIN(12);

    BL_PIN.set();

    return 0;
}
