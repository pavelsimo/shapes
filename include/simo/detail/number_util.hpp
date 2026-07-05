#pragma once

#include <ciso646>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#ifdef _MSC_VER
#include <locale.h>
#elif defined(__APPLE__)
#include <xlocale.h>
#else
#include <locale.h>
#endif

namespace simo
{
namespace shapes
{
namespace detail
{

#ifdef _MSC_VER

inline _locale_t c_locale() noexcept
{
    static _locale_t locale = _create_locale(LC_ALL, "C");
    return locale;
}

#else

inline locale_t c_locale() noexcept
{
    static locale_t locale = newlocale(LC_ALL_MASK, "C", static_cast<locale_t>(nullptr));
    return locale;
}

#endif

/*!
 * @brief Converts the initial part of the given string to a double, always using the "C"
 *        locale regardless of the process global locale
 * @param str the string to convert
 * @param str_end optional out parameter set to the first character past the number
 * @return the converted value
 *
 * @since 0.0.1
 */
inline double parse_double(const char* str, char** str_end = nullptr)
{
#ifdef _MSC_VER
    return _strtod_l(str, str_end, c_locale());
#else
    return strtod_l(str, str_end, c_locale());
#endif
}

/*!
 * @brief Formats a double with "%.*g" in the "C" locale
 * @param buf the output buffer
 * @param size the output buffer size
 * @param precision the number of significant digits
 * @param value the value to format
 * @return the number of characters written
 *
 * @since 0.0.1
 */
inline int format_double(char* buf, std::size_t size, int precision, double value) noexcept
{
#ifdef _MSC_VER
    return _snprintf_l(buf, size, "%.*g", c_locale(), precision, value);
#else
    locale_t old = uselocale(c_locale());
    int len      = std::snprintf(buf, size, "%.*g", precision, value);
    uselocale(old);
    return len;
#endif
}

/*!
 * @brief Appends a double to the given string
 * @param out the output string
 * @param value the value to append
 * @param precision the number of significant digits, a negative value formats with the
 *        smallest number of digits that round-trips back to the same value
 *
 * @since 0.0.1
 */
inline void append_double(std::string& out, double value, std::int32_t precision)
{
    char buf[40];
    int len;
    if (precision >= 0)
    {
        len = format_double(buf, sizeof(buf), static_cast<int>(precision), value);
    }
    else
    {
        len = format_double(buf, sizeof(buf), 15, value);
        if (parse_double(buf) != value)
        {
            len = format_double(buf, sizeof(buf), 16, value);
            if (parse_double(buf) != value)
            {
                len = format_double(buf, sizeof(buf), 17, value);
            }
        }
    }
    if (len > 0)
    {
        out.append(buf, static_cast<std::size_t>(len));
    }
}

}  // namespace detail
}  // namespace shapes
}  // namespace simo
