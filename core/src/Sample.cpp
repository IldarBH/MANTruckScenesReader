#include "MANTruckDataset/Sample.hpp"

namespace man::dataset::samples {

namespace {
  constexpr std::string_view SAMPLE_FIELD_TOKEN = "token";
  constexpr std::string_view SAMPLE_FIELD_SCENE_TOKEN = "scene_token";
  constexpr std::string_view SAMPLE_FIELD_TIMESTAMP = "timestamp";
  constexpr std::string_view SAMPLE_FIELD_PREV = "prev";
  constexpr std::string_view SAMPLE_FIELD_NEXT = "next";
}

Sample::Sample(const Token& token, const Token& scene_token, const int64_t timestamp, Sample* prev_sample, Sample* next_sample)
: TOKEN_(token), SCENE_TOKEN_(scene_token), TIMESTAMP_(timestamp)
{
  if (prev_sample)
    this->set_prev_sample(prev_sample);
  if (next_sample)
    this->set_next_sample(next_sample);
}

Sample::~Sample()
{
  if (prev_sample_)
    prev_sample_->set_next_sample(next_sample_);
  if (next_sample_)
    next_sample_->set_prev_sample(prev_sample_);
}

void Sample::set_prev_sample(Sample* prev) noexcept 
{ 
  prev_sample_ = prev;
  if (prev && (prev->get_next_sample() != this))
    prev->set_next_sample(this);
}

void Sample::set_next_sample(Sample* next) noexcept 
{ 
  next_sample_ = next; 
  if (next && (next->get_prev_sample() != this))
    next->set_prev_sample(this);
}

std::ostream& operator<<(std::ostream& os, const Sample& sample) {
  os << "Sample:\n"
     << "\tToken: " << sample.TOKEN_ << "\n"
     << "\tScene token: " << sample.SCENE_TOKEN_ << "\n"
     << "\tTimestamp: " << sample.TIMESTAMP_;
  return os;
}

void SampleSequence::read_samples(const std::string& filename, const Token& scene_token)
{
  const auto data = read_json_file(filename);
  for (const auto& item : data) {
    const Token item_scene_token(item.at(SAMPLE_FIELD_SCENE_TOKEN).get<std::string>());
    if (item_scene_token == scene_token) {
      const Token sample_token(item.at(SAMPLE_FIELD_TOKEN).get<std::string>());
      const Token prev_token(item.at(SAMPLE_FIELD_PREV).get<std::string>());
      const size_t timestamp = item.at(SAMPLE_FIELD_TIMESTAMP).get<int64_t>();
      this->add_sample(sample_token, item_scene_token, timestamp, prev_token);
      // Next token will be linked when its sample is added
    }
  }
}

void SampleSequence::add_sample(const Token& token, const Token& scene_token,const int64_t timestamp, const Token& prev_token,const Token& next_token)
{
  if (samples_map_.find(token) != samples_map_.end()) {
    throw std::invalid_argument("Sample with token " + token.value + " already exists.");
  }
  samples_vec_.emplace_back(std::make_shared<Sample>(token, scene_token, timestamp));
  samples_map_.emplace(std::make_pair(token, samples_vec_.back()));
  if (!prev_token.value.empty()) {
    const auto& prev_sample = samples_map_.at(prev_token).lock();
    prev_sample->set_next_sample(samples_vec_.back().get());
    samples_vec_.back()->set_prev_sample(prev_sample.get());
  }
  if (!next_token.value.empty()) {
    const auto& next_sample = samples_map_.at(next_token).lock();
    next_sample->set_prev_sample(samples_vec_.back().get());
    samples_vec_.back()->set_next_sample(next_sample.get());
  }
}

const Sample& SampleSequence::operator[](std::size_t index) const
{
  return *samples_vec_.at(index);
}

std::vector<Token> SampleSequence::get_tokens() const noexcept
{
  std::vector<Token> tokens;
  tokens.reserve(samples_vec_.size());
  for (const auto& sample_ptr : samples_vec_) {
    tokens.push_back(sample_ptr->get_token());
  }
  return tokens;
}

}
