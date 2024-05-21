#pragma once

#include <ctime>

namespace JulianTime {

inline constexpr unsigned long JulianDay(const std::tm& date) noexcept
{
  return (1461 * (date.tm_year + 4800 + (date.tm_mon - 14) / 12)) / 4 +
         (367 * (date.tm_mon - 2 - 12 * ((date.tm_mon - 14) / 12))) / 12 -
         (3 * ((date.tm_year + 4900 + (date.tm_mon - 14) / 12) / 100)) / 4 +
         date.tm_mday - 32075;
}

/**
 * @brief Convert Julaian day to seconds since Unix epoch (1 jan 1970) excluding leap seconds.
 * @param julianDay Julian date to convert
 */
inline constexpr unsigned long EpochSeconds(unsigned long julianDay) noexcept
{
    return (julianDay - 2440587.5) * 86400;
}


/**
 * @brief Convert std::tm struct to seconds since Unix epoch (1 jan 1970 00:00) excluding leap seconds.
 * @param date std::tm struct to convert
 */
inline constexpr unsigned long EpochSeconds(const std::tm& date) noexcept
{
    unsigned long result = 0;

    result += EpochSeconds(JulianDay(date));
    result += date.tm_hour * 3600;
    result += date.tm_min * 60;
    result += date.tm_sec;

    return result;
}

} // namespace JulianTime
