#pragma once
#include "MANTruckDataset/utils.hpp"

#include <Eigen/Dense>
#include <memory>

namespace man::dataset::sensors {

class Calibration {
public:
  using SPtr = std::shared_ptr<Calibration>;
  using WPtr = std::weak_ptr<Calibration>;

  Calibration() = delete;

  Calibration(
    const Token& token,
    const Token& sensor_token,
    const Eigen::Vector3d& translation,
    const Eigen::Quaterniond& rotation,
    const Eigen::Matrix3d& camera_intrinsic = Eigen::Matrix3d::Zero()
  );

  const auto& get_token() const noexcept { return TOKEN_; }
  const auto& get_sensor_token() const noexcept { return SENSOR_TOKEN_; }
  const Eigen::Vector3d& get_translation() const noexcept {return TRANSLATION_; }
  const Eigen::Quaterniond& get_rotation() const noexcept { return ROTATION_; }
  const Eigen::Matrix3d& get_camera_intrinsic() const noexcept { return CAMERA_INTRINSIC_; }

  friend std::ostream& operator<<(std::ostream& os, const Calibration& calibration);
private:
  const Token TOKEN_;
  const Token SENSOR_TOKEN_;
  const Eigen::Vector3d TRANSLATION_;
  const Eigen::Quaterniond ROTATION_;
  const Eigen::Matrix3d CAMERA_INTRINSIC_;
};

std::ostream& operator<<(std::ostream& os, const Calibration& calibration);
} // namespace man::dataset::sensors