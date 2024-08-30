#include "ael/boards/pi_pico/extras/adxl345.hpp"

#include <hardware/watchdog.h>
#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <sys/unistd.h>

#include <cstdio>
#include <string_view>

#include "ael/boards/pi_pico/extras/adxl345.hpp"
#include "ael/boards/pi_pico/spi.hpp"
#include "ael/drivers/adxl345/registers.hpp"
#include "ael/types.hpp"

using namespace ael::types;
using namespace ael::boards::pi_pico::spi;
using namespace ael::boards::pi_pico::extras::adxl345;
using namespace ael::drivers::adxl345;

auto software_reset() {
    watchdog_enable(1, 1);
    while (1);
}

auto handle_hard_error(const std::string_view &error_msg) {
    std::printf("%s\n", error_msg);
    software_reset();
}

[[noreturn]] int main() {
    stdio_init_all();

    auto spi = SPI(eInstSPI::SPI_0, 17, 18, 19, 16, 10'000'000);
    auto accm = ADXL345(spi);

    (void)accm.reg_read(ADXL345_REG_DEVID);

    const auto id = accm.reg_read(ADXL345_REG_DEVID);
    printf("SPI address 0x%x\n", id);
    if (id != ADXL345::ADXL345_ID) {
        char str[256];
        std::sprintf(str, "ERROR: Expected Address 0x%x, got 0x%x\n", ADXL345::ADXL345_ID, id);
        handle_hard_error(str);
    }
    // neat error handling
    if (const auto err = accm.init(); err) {
        handle_hard_error("ERROR: Ecountered error\n");
    }

#if 0
    u8 format = 0;
    spi.rread<1>(ADXL345_REG_DATA_FORMAT | READ_FLAG, &format);

    /* Update the data rate */
    format &= ~0x0F;
    format |= ADXL345_RANGE_2_G;

    /* Make sure that the FULL-RES bit is enabled for range scaling */
    format |= 0x08;

    /* Write the register back to the IC */
    spi.rwrite<1>(ADXL345_REG_DATA_FORMAT, &format);

#endif  // 0

    while (true) {
        // Clear terminal
        // printf("\e[1;1H\e[2J");

        // if (const auto status = accm.reg_read(0); not(status & 0x0Fu)) {
        //     // printf("Status: 0b%08b\n", status);
        //     printf("Status: %b\n", status);
        //     sleep_ms(5);
        //     continue;
        // }

        const auto accel = accm.read_accel();
        printf("CON: x: %d, y: %d, z: %d\n", accel.x, accel.y, accel.z);

        sleep_ms(500);
    }
}
