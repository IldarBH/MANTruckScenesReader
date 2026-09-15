#include "MANTruckDataset/Sensor.hpp"

namespace man::dataset::sensors {

DataItem::DataItem(const size_t timestamp, const std::string& filename, const DataItem* prev, const DataItem* next)
  : TIMESTAMP_(timestamp), FILENAME_(filename)
{}

void DataItem::set_prev_sample(DataItem* prev) noexcept 
{
  if (prev == this) {
    #ifdef DEBUG
      std::cerr << "Warning: Attempted to set previous sample to self for DataItem with timestamp " << TIMESTAMP_ << "\n";
    #endif
    return;
  };
  prev_sample_ = prev;
  if (prev && (prev->get_next_sample() != this))
    prev->set_next_sample(this);
}

void DataItem::set_next_sample(DataItem* next) noexcept 
{ 
  if (next == this) {
    #ifdef DEBUG
      std::cerr << "Warning: Attempted to set next sample to self for DataItem with timestamp " << TIMESTAMP_ << "\n";
    #endif
    return;
  };
  next_sample_ = next;
  if (next && (next->get_prev_sample() != this))
    next->set_prev_sample(this);
}


// void SensorBase::add_file(const std::string& filename, const size_t timestamp) 
// { 
//   if (samples_vec_.empty()){
//     samples_vec_.emplace_back(std::make_shared<DataItem>(timestamp, filename));
//   } else {
//     const auto& last_sample = samples_vec_.back();
//     auto new_sample = std::make_shared<DataItem>(timestamp, filename, last_sample.get());
//     samples_vec_.emplace_back(std::move(new_sample));
//   }
// }

// const DataItem SensorBase::operator[](const size_t index) const 
// { 
//   if (index >= samples_vec_.size()) {
//     throw std::out_of_range("Index " + std::to_string(index) + " out of range.");
//   }
//   return *samples_vec_[index]; 
// }
}