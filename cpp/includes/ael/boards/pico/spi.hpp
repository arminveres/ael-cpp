#ifndef __AEL_BOARDS_PICO_SPI_HPP
#define __AEL_BOARDS_PICO_SPI_HPP
#include "ael/types.hpp"

namespace ael::boards::pico {

template <u8 MOSI>
class SPI {
   public:
    SPI() {}
    SPI(SPI &&) = default;
    SPI(const SPI &) = default;
    SPI &operator=(SPI &&) = default;
    SPI &operator=(const SPI &) = default;
    ~SPI() {}

   private:
};

}  // namespace ael::boards::pico
#endif  // !__AEL_BOARDS_PICO_SPI_HPP
