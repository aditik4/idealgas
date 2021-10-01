#include <catch2/catch.hpp>
#include <particle.h>

using idealgas::Particle;

idealgas::Particle particle_1 = idealgas::Particle(vec2(20, 19), vec2(1, -1), 1);
idealgas::Particle particle_2 = idealgas::Particle(vec2(21, 19), vec2(-1, -1), 1);

TEST_CASE("Test update position") {
  particle_1.UpdatePosition();
  REQUIRE(particle_1.GetPosition() == vec2(21, 18));
}
TEST_CASE("Velocity changes after vertical wall crash") {
  particle_1.CrashIntoVerticalWall();
  REQUIRE(particle_1.GetVelocity() == vec2(-1, -1));
}
TEST_CASE("Velocity changes after horizontal wall crash") {
  particle_1.CrashIntoHorizontalWall();
  REQUIRE(particle_1.GetVelocity() == vec2(1,1));
}
TEST_CASE("Velocity changes after colliding with other particle") {
  particle_1.CollideWithParticle(particle_2);
  REQUIRE(particle_1.GetVelocity() == vec2(-1, -1));
}
TEST_CASE("Tests if colliding with particle from appropriate distance") {
  REQUIRE(particle_1.IsCollidingWithParticle(particle_2) == true);
}