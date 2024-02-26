#ifndef __AEL_BOARDS_PICO_GPIO_HPP
#define __AEL_BOARDS_PICO_GPIO_HPP
#include <hardware/gpio.h>

#include "ael/types.hpp"

namespace ael::boards::pi_pico::gpio {

using namespace types;

/// GPIO Direction, either OUT or IN
enum class eGPIODir : bool { OUT = 1, IN = 0 };

template <u8 pin, eGPIODir dir>
class GPIO {
   public:
    GPIO() {
        gpio_init(pin);
        gpio_set_dir(pin, static_cast<bool>(dir));
    }
    GPIO(GPIO &&) = default;
    GPIO(const GPIO &) = default;
    GPIO &operator=(GPIO &&) = default;
    GPIO &operator=(const GPIO &) = default;
    ~GPIO() {}

    auto set() { gpio_put(pin, true); }
    auto clear() { gpio_put(pin, false); }
    auto toggle() {
        if (gpio_get(pin))
            clear();
        else
            set();
    }

   private:
};

}  // namespace ael::boards::pi_pico::gpio
#endif  // !__AEL_BOARDS_PICO_GPIO_HPP
