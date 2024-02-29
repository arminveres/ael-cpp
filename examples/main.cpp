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

    auto spi = SPI(eInstSPI::SPI_0, 17, 18, 19, 16, 1'000'000);
    sleep_ms(50);
    auto accm = LIS3DH(spi);
    sleep_ms(50);
    (void)accm.reg_read(reg_addr::WHO_AM_I);
    sleep_ms(500);

    const auto id = accm.reg_read(reg_addr::WHO_AM_I);
    if (id == LIS3DH::LIS3DH_ID)
        printf("SPI address 0x%x\n", id);
    else {
        printf("ERROR: Expected Address 0x%x\n", reg_addr::WHO_AM_I);
        while (true) {
            sleep_us(10'000);
        }
    }
    // if (id.has_value()) {
    //     printf("SPI address 0x%x\n", *id);
    // } else if (id.error() == eError::errorGeneric or id.error() == eError::errorOther) {
    //     printf("ERROR: Expected Address 0x%x\n", reg_addr::WHO_AM_I);
    //     while (true) {
    //         sleep_us(10'000);
    //     }
    // }

    accm.init();

    while (true) {
        // Clear terminal
        printf("\e[1;1H\e[2J");

        // reg_status status;
        if (const auto status = accm.reg_read(reg_status::ADDR); not(status & 0x0Fu)) {
            printf("Status: 0b%08b\n", status);
            continue;
        }

        const auto accel = accm.read_accel();
        printf("CON: x: %03d, y: %03d, z: %03d\n", accel.x, accel.y, accel.z);
        sleep_ms(100);

        // if (const auto prot_accel = accm.read_accel(); prot_accel.has_value()) {
        //     const auto accel = *prot_accel;
        //     printf("CON: x: %03d, y: %03d, z: %03d\n", accel.x, accel.y, accel.z);
        //     sleep_ms(100);
        // }
    }
}
