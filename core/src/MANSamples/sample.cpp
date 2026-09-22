#include "MANSamples/sample.hpp"
#include "MANTruckDataset/utils.hpp"

namespace man::dataset::samples {

Sample::Sample(const Token& token, const Token& scene_token, const int64_t timestamp, 
  Sample* prev_sample, Sample* next_sample)
: TOKEN_(token), SCENE_TOKEN_(scene_token), TIMESTAMP_(timestamp)
{
  if (prev_sample)
    this->set_prev_sample_(prev_sample);
  if (next_sample)
    this->set_next_sample_(next_sample);
}

Sample::Sample(const Sample& other)
: TOKEN_(other.TOKEN_), SCENE_TOKEN_(other.SCENE_TOKEN_), TIMESTAMP_(other.TIMESTAMP_)
{
  if (other.prev_sample_)
    this->set_prev_sample_(other.prev_sample_);
  if (other.next_sample_)
    this->set_next_sample_(other.next_sample_);
}

Sample::~Sample()
{
  if (prev_sample_)
    prev_sample_->set_next_sample_(next_sample_);
  if (next_sample_)
    next_sample_->set_prev_sample_(prev_sample_);
}

void Sample::set_prev_sample_(Sample* prev) noexcept 
{ 
  if (prev == this)
    return;
  this->prev_sample_ = prev;
  if (prev && (prev->next_sample_ != this))
    prev->set_next_sample_(this);
}

void Sample::set_next_sample_(Sample* next) noexcept 
{ 
  if (next == this)
    return;
  this->next_sample_ = next;
  if (next && (next->prev_sample_ != this))
    next->set_prev_sample_(this);
}

std::ostream& operator<<(std::ostream& os, const Sample& sample) {
  os << "Sample:"
     << "\n\tToken: " << sample.TOKEN_
     << "\n\tScene token: " << sample.SCENE_TOKEN_
     << "\n\tTimestamp: " << sample.TIMESTAMP_;
  return os;
}

}