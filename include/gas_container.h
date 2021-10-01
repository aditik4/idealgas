#pragma once
#include "cinder/gl/gl.h"
#include "particle.h"
#include <string>
using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * Constructs a gas container with a lower bound and an upper bound.
   */
  GasContainer(int numY, int numR, int numO);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Handles partice on particle collisions
   */
  void CollideWithContainerParticles();
  void AddParticles(ci::Color color, int num);

  /**
   * Determines whether or not the given particle is crashing a vertical wall
   * @param part the particle being examined
   * @return true if the particle is crashing a vertical wall, otherwise false.
   */
  bool ParticleIsCrashingVerticalWall(const Particle& part);
  /**
   * Determines whether or not the given particle is crashing a horizontal wall
   * @param part the particle being examined
   * @return true if the particle is crashing a horizontal wall, otherwise false.
   */
  bool ParticleIsCrashingHorizontalWall(const Particle& part);
  /**
   * Sets the lower and upper bounds for testing purposes.
   * @param lower the lower bounds
   * @param upper the upper bounds
   */
  void SetLowerAndUpperBounds(const vec2 lower, const vec2 upper);
  /**
   * Sets the particle vector for testing purposes
   * @param particles the particles to set
   */
  void SetParticles(const std::vector<Particle>& particles);
  std::vector<Particle> GetParticles();
  /**
   * Determines whether particles should collide or not if they are going
   * toward eachother.
   * @param particle1 the first particle
   * @param particle2 the second particle
   * @return true if it is fine for the particles to collide
   */
  bool ParticlesShouldCollide(const Particle& particle1, const Particle& particle2);
  void CollideWithParticle(Particle& first, Particle& second);

 private:
  /**
   * The lower bound of the container
   */
  vec2 lowerbound_;
  /**
   * The upperbound of the container
   */
  vec2 upperbound_;
  /**
   * The vector that holds the particles currently in the container
   */
  std::vector<Particle> particles_;
  /**
   * The box color
   */
  cinder::ColorT<float> kHistoColor = "white";


  cinder::ColorT<float> kColorYellow = "yellow";
  cinder::ColorT<float> kColorOrange = "orange";
  cinder::ColorT<float> kColorRed = "red";
  /**
   * Sets up the bounds of the container
   */
  const int kLowerXBound = 100;
  const int kLowerYBound = 100;
  const int kUpperXBound = 600;
  const int kUpperYBound = 400;


};
}  // namespace idealgas
