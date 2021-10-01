//
// Created by Aditi Khanna on 3/21/21.
//

#include "histogram.h"

#include <glm/vec2.hpp>

namespace idealgas {

using glm::vec2;
Histogram::Histogram(vec2 lower, vec2 upper, cinder::ColorT<float> type) {
  histlowerbound_ = lower;
  histupperbound_ = upper;
  particleType_ = type;
}
const void Histogram::SetAllSpeedsOfParticleType(GasContainer container, cinder::Color type) {
  particleSpeeds_.clear();
  for(Particle& particle : container.GetParticles()) {
    if(particle.GetColor() == type) {
      particleSpeeds_.push_back(glm::length(particle.GetVelocity()));
    }
  }
  std::sort(particleSpeeds_.begin(), particleSpeeds_.end());
}
const void Histogram::StoreFrequenciesOfSpeed() {
  speed_frequency_map_.clear();
  for(double speed: particleSpeeds_) {
    if (speed_frequency_map_.count(speed) > 0) {
      int count = speed_frequency_map_.at(speed);
      speed_frequency_map_.erase(speed);
      speed_frequency_map_.insert(std::pair<double, int>(speed, count+1));
      std::cout << "here";
    } else {
      speed_frequency_map_.insert(std::pair<double, int>(speed, 1));
    }
  }
}

const std::vector<double> Histogram::GetParticleSpeeds() {
  return particleSpeeds_;
}
const std::map<double, int> Histogram::GetSpeedMap() {
  return speed_frequency_map_;
}
const void Histogram::CreateHistogram() const {
  ci::gl::color(ci::Color("white"));
  //ci::gl::color(ci::Color(kBoxColor));
  ci::gl::drawStrokedRect(ci::Rectf(histlowerbound_, histupperbound_));

  int numBoxes = particleSpeeds_.size() / 10;

 for(size_t i = 0; i < numBoxes; i++) {
   int frequency = speed_frequency_map_.at(particleSpeeds_[i]);
   for(size_t j = 0; j < i + 10; j+= numBoxes) {
     frequency = speed_frequency_map_.at(particleSpeeds_[j]) + speed_frequency_map_.at(particleSpeeds_[j+1]);
    }
   ci::gl::drawStrokedRect(ci::Rectf(vec2(histlowerbound_.x + 10*i, histupperbound_.y), vec2(histlowerbound_.x + (10 * (i + 1)), histlowerbound_.y + frequency)));
  }
}

}