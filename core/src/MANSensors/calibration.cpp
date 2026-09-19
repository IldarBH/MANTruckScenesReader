#include "MANSensors/calibration.hpp"
#include "MANTruckDataset/utils.hpp"

namespace man::dataset::sensors {

Calibration::Calibration(
  const Token& token, 
  const Token& sensor_token, 
  const Eigen::Vector3d& translation,
  const Eigen::Quaterniond& rotation,
  const Eigen::Matrix3d& camera_intrinsic)
: TOKEN_(token)
, SENSOR_TOKEN_(sensor_token)
, TRANSLATION_(translation)
, ROTATION_(rotation)
, CAMERA_INTRINSIC_(camera_intrinsic)
{}

std::ostream& operator<<(std::ostream& os, const Calibration& calibration)
{
  os << "Calibration:\n\tToken: " << calibration.TOKEN_
     << "\n\tSensor Token: " << calibration.SENSOR_TOKEN_
     << "\n\tTranslation: " << calibration.TRANSLATION_.transpose()
     << "\n\tRotation (x,y,z,w): " << calibration.ROTATION_.coeffs().transpose()
     << "\n\tCamera Intrinsic: \n" << calibration.CAMERA_INTRINSIC_;
  return os;
}

}