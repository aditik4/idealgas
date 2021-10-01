//
// Created by Aditi Khanna on 3/21/21.
//
#include "cinder/gl/gl.h"
#include <glm/vec2.hpp>
#include "gas_container.h"
#include <map>
#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H


#endif  // IDEAL_GAS_HISTOGRAM_H

namespace idealgas {
class Histogram {
 public:
  /**
   * Constructs a new Histogram with an upper bound, lowerboud, and color
   * @param lowerbound the lower bound of the histogram box
   * @param upperbound the upper bound of the histogram box
   * @param type the color of particles this histogram is handling
   */
  Histogram(vec2 lowerbound, vec2 upperbound, cinder::Color type);
  /**
   * Obtains the lower bound of the histogram
   * @return the lower bound vec2
   */
  const vec2 GetLowerBound();
  /**
   * Obtains the upper bound
   * @return the upper bound of box
   */
  const vec2 GetUpperBound();
  /**
   * stores all the speeds of the particular particle type
   * @param container the gas container
   * @param type the type of particles handled
   */
  const void SetAllSpeedsOfParticleType(GasContainer container, cinder::ColorT<float> type);
  /**
   * Stores the frequencies of the speeds
   */
  const void StoreFrequenciesOfSpeed();
  /**
   * Creates the histogram, draws the bars
   */
  const void CreateHistogram() const;
  /**
   * Obtains the speed vector
   * @return the vector
   */
  const std::vector<double> GetParticleSpeeds();
  /**
   * Obtains the speed frequenc map
   * @return the map
   */
  const std::map<double, int> GetSpeedMap();
 private:
  /**
   * the lower bound of the histogram
   */
  vec2 histlowerbound_;
  /**
   * The upperbound of the histogram
   */
  vec2 histupperbound_;
  /**
   * Storees the frequencies
   */
  std::map<double, int> speed_frequency_map_;
  /**
   * Stores the particle color
   */
  cinder::Color particleType_;
  /**
   * Stores the speeds of the particles
   */
  std::vector<double> particleSpeeds_;
  /**
   * The color of the box
   */
  cinder::Color kBoxColor;
};
}
