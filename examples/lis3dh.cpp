#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/time.h>

#include "ael/boards/pi_pico/extras/lis3dh.hpp"
#include "ael/boards/pi_pico/spi.hpp"
#include "ael/peripherals/lis3dh/registers.hpp"
#include "ael/types.hpp"

using namespace ael::types;
using namespace ael::boards::pi_pico::spi;
using namespace ael::boards::pi_pico::extras::lis3dh;
using namespace ael::peripherals::lis3dh;

[[noreturn]] int main() {
    stdio_init_all();

    auto spi = SPI(eInstSPI::SPI_0, 17, 18, 19, 16, 10'000'000);
    auto accm = LIS3DH(spi);
    (void)accm.reg_read(reg_addr::WHO_AM_I);

    const auto id = accm.reg_read(reg_addr::WHO_AM_I);
    if (id == LIS3DH::LIS3DH_ID)
        printf("SPI address 0x%x\n", id);
    else {
        printf("ERROR: Expected Address 0x%x\n", reg_addr::WHO_AM_I);
        while (true) {
            sleep_us(10'000);
        }
    }

    // neat error handling
    if (const auto err = accm.init(); err) {
        printf("ERROR: Ecountered error\n");
        while (true) sleep_us(10000);
    }

    while (true) {
        // Clear terminal
        // printf("\e[1;1H\e[2J");

        // reg_status status;

        if (const auto status = accm.reg_read(reg_status::ADDR); not(status & 0x0Fu)) {
            // printf("Status: 0b%08b\n", status);
            printf("Status: %b\n", status);
            sleep_ms(5);
            continue;
        }

        const auto accel = accm.read_accel();
        printf("CON: x: %03d, y: %03d, z: %03d\n", accel.x, accel.y, accel.z);

        sleep_ms(5);
    }
}
