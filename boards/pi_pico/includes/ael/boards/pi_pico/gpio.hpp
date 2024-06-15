#ifndef __AEL_BOARDS_PICO_GPIO_HPP
#define __AEL_BOARDS_PICO_GPIO_HPP
#include <hardware/gpio.h>

#include "ael/types.hpp"

namespace ael::boards::pi_pico::gpio {


/// GPIO Direction, either OUT or IN
enum class eGPIODir : bool { OUT = 1, IN = 0 };

template <eGPIODir dir>
class GPIO {
   public:
    GPIO(const types::u8 pin) : m_pin(pin) {
        gpio_init(m_pin);
        gpio_set_dir(m_pin, static_cast<bool>(dir));
    }
    GPIO(GPIO &&) = default;
    GPIO(const GPIO &) = default;
    GPIO &operator=(GPIO &&) = default;
    GPIO &operator=(const GPIO &) = default;
    ~GPIO() {}

    auto set() { gpio_put(m_pin, 1); }
    auto clear() { gpio_put(m_pin, 0); }
    auto toggle() {
        if (gpio_get(m_pin))
            clear();
        else
            set();
    }

   private:
    types::u8 m_pin;
};

}  // namespace ael::boards::pi_pico::gpio
#endif  // !__AEL_BOARDS_PICO_GPIO_HPP
