#include <catch2/catch.hpp>

#include <gas_container.h>
#include <particle.h>

using idealgas::GasContainer;

idealgas::Particle particle1 = idealgas::Particle(vec2(20, 19.9), vec2(1, -0.1), 1);
idealgas::Particle particle2 = idealgas::Particle(vec2(9, 25), vec2(1, 4), 1);
idealgas::Particle particle3 = idealgas::Particle(vec2(21.4, 21.4), vec2(-1, -0.1), 1);
idealgas::Particle particle4 = idealgas::Particle(vec2(21.4, 21.4), vec2(1, -0.1), 1);


TEST_CASE("Particle senses Vertical Wall") {
  GasContainer container;
  container.SetLowerAndUpperBounds(vec2(0, 10), vec2(20, 25));
  REQUIRE(container.ParticleIsCrashingVerticalWall(particle1) == true);
}
TEST_CASE("Particle senses Horizontal Wall") {
  GasContainer container;
  container.SetLowerAndUpperBounds(vec2(0, 10), vec2(20, 25));
  REQUIRE(container.ParticleIsCrashingHorizontalWall(particle2) == true);
}
TEST_CASE("Positions update by velocity") {
  GasContainer container;
  container.SetLowerAndUpperBounds(vec2(0, 10), vec2(30, 25));
  container.AdvanceOneFrame();
  REQUIRE(particle1.GetPosition() == vec2(20, 19.9));
}
TEST_CASE("Velocities update appropriately after particle collisions") {
  GasContainer container;
  container.SetLowerAndUpperBounds(vec2(0, 10), vec2(30, 25));
  std::vector<idealgas::Particle> particles;
  particles.push_back(particle1);
  particles.push_back(particle3);
  container.SetParticles(particles);
  container.Collide();
  REQUIRE(particles[1].GetPosition() == vec2(21.400, 21.400));
}
TEST_CASE("No collision when particles are not going toward each other") {
  GasContainer container;
  container.SetLowerAndUpperBounds(vec2(0, 10), vec2(30, 25));
  std::vector<idealgas::Particle> particles;
  REQUIRE(container.ParticlesShouldCollide(particle1, particle4) == false);
}
