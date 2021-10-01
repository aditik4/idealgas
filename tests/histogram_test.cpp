//
// Created by Aditi Khanna on 3/23/21.
//
#include <catch2/catch.hpp>
#include <gas_simulation_app.h>
#include <histogram.h>
#include <gas_container.h>
#include <particle.h>

using idealgas::GasContainer;
using idealgas::Histogram;

GasContainer container_ = GasContainer(3, 2, 0);
Histogram histogram_1 = Histogram(vec2(200, 100), vec2(400, 500), "yellow");
Histogram histogram_2 = Histogram(vec2(100, 100), vec2(300, 400), "red");

idealgas::Particle particle_1 = idealgas::Particle(vec2(20, 19), vec2(1, -1), 1, 30, "yellow");
idealgas::Particle particle_2 = idealgas::Particle(vec2(21, 19), vec2(-1, -1), 1, 30, "yellow");



TEST_CASE("All Speeds added to the vector initially") {
  histogram_1.SetAllSpeedsOfParticleType(container_, "yellow");
  std::vector<double> test;
  test.push_back(3.1);
  histogram_1.GetParticleSpeeds();
  REQUIRE(histogram_1.GetParticleSpeeds() == test);
}
TEST_CASE("New speeds added to the vector after collision") {
  std::vector<idealgas::Particle> particles;
  particles.push_back(particle_1);
  particles.push_back(particle_2);
  container_.SetParticles(particles);
  container_.CollideWithParticle(particle_1, particle_2);
  REQUIRE(histogram_1.GetParticleSpeeds().at(0) == 3.1);
}
TEST_CASE("Map adds appropriately") {
  //std::map<double, int> expected;
  //expected.insert(std::pair<double, int>(0.7, 1));
  histogram_1.StoreFrequenciesOfSpeed();
  REQUIRE(histogram_1.GetSpeedMap().at(0) == 1);
}




