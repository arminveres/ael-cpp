#ifndef AEL_ARRAY_HPP
#define AEL_ARRAY_HPP

#include <cstddef>
#include <optional>

namespace ael {

/**
 * @brief This class is meant as a replacement for the std::array, since that is made constexpr and
 * I need to be able to interface with C code.
 *
 * @note Very much WIP!
 */
template <typename T, size_t SIZE>
class array {
    T m_array[SIZE] = {};
    size_t m_len = SIZE;

   public:
    array() = default;
    ~array() = default;

    size_t size() const { return this->m_len; }

    T* raw_ptr() { return this->m_array; }

    /**
     * @brief Get the element at index i, wrappen into std::optional
     *
     * @returns std::nullopt if no available value, value T otherwise
     */
    std::optional<T> get(const size_t& i) {
        if (i >= this->m_len) return std::nullopt;
        return this->m_array[i];
    }
};

}  // namespace ael

#endif  // !AEL_ARRAY_HPP
