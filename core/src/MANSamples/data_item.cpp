#include "MANSamples/data_item.hpp"
#include "MANTruckDataset/utils.hpp"

namespace man::dataset::samples {

DataItem::DataItem(
  const Token& token, const Token& sample_token, const Token& ego_pose_token, const Token& calibrated_sensor_token, 
  const std::string& fileformat, const std::string& filename, const uint64_t timestamp, 
  DataItem* prev_sample, DataItem* next_sample)
  : TOKEN_(token)
  , SAMPLE_TOKEN_(sample_token)
  , EGO_POSE_TOKEN_(ego_pose_token)
  , CALIBRATED_SENSOR_TOKEN_(calibrated_sensor_token)
  , TIMESTAMP_(timestamp)
  , FILEFORMAT_(fileformat)
  , FILENAME_(filename)
  , prev_sample_(prev_sample)
  , next_sample_(next_sample) 
  {}

std::ostream& operator<<(std::ostream& os, const DataItem& sample) 
{
  os << "Data sample:\n\tToken: " << sample.TOKEN_
     << "\n\tSample token: " << sample.SAMPLE_TOKEN_
     << "\n\tCalibrated sensor token: " << sample.CALIBRATED_SENSOR_TOKEN_
     << "\n\tTimestamp: " << sample.TIMESTAMP_
     << "\n\tFilename: " << sample.FILENAME_ ;
  return os;
}

}
