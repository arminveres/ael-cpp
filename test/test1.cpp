#include "ael/boards/pico/spi.hpp"

using namespace ael::boards::pico;

int main() {
    // RX Pin
    static constexpr auto MISO_PIN = 8;
    static constexpr auto CS_PIN = 9;
    static constexpr auto CLK_PIN = 10;
    // TX Pin
    static constexpr auto MOSI_PIN = 11;

    // static constexpr auto RST_PIN = 12;
    // static constexpr auto BL_PIN = 13;

    SPI<eInstSPI::SPI_0, CS_PIN, CLK_PIN, MOSI_PIN, MISO_PIN, 10'000 * 1000> inst;

    return 0;
}
