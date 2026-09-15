#pragma once

#include <string>
#include <string_view>
#include <ostream>

namespace man::dataset::sensors {

enum class Modality {
  CAMERA,
  LIDAR,
  RADAR,
  IMU,
};

/**
 * @brief Resolve the modality type from a string.
 * @param modality The string representation of the modality type.
 * @return The corresponding Modality enum value.
 */
Modality string_to_modality(const std::string_view modality);

/**
 * @brief Resolve the modality name from a Modality enum value.
 * @param modality The Modality enum value.
 * @return The corresponding string representation of the modality type.
 */
std::string modality_to_string(const Modality modality);

std::ostream& operator<<(std::ostream& os, const Modality type);

}  // namespace man::dataset::sensors