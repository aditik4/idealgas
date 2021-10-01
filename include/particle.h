#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H
#include "cinder/gl/gl.h"
#include <glm/vec2.hpp>
using glm::vec2;

namespace idealgas {
class Particle {
 public:
  /**
   * Constructs a new Particle with a position, velocity, and radius
   * @param pos the position of the particle
   * @param vel the velocity of the particle
   * @param radius the radius of the particle
   */
  Particle(vec2 pos, vec2 vel,double radius, double mass, cinder::ColorT<float> color);
  /**
   * Returns the current velocity of the particle
   * @return the velocity vec2
   */
   const vec2 GetVelocity() const;
  /**
   * Obtains the current position of the particle
   * @return the position of the particle
   */
  const vec2 GetPosition() const;
  /**
   * Sets the velocity of the particle to the given velocity
   * @param newVel
   */
  const void SetVelocity(vec2 newVel);
  /**
   * Obtains the X coordinate of the velocity
   * @return the x coordinate
   */
  const double GetXVelocity() const;
  /**
   * Obtains the Y coordinate of the velocity
   * @return the y coordinate
   */
  const double GetYVelocity() const;
  /**
   * Obtains the X coordinate of the position
   * @return the x position
   */
  const double GetXPosition() const;
  /**
   * Obtains the Y coordinate of the position
   * @return the Y coordinate of the position
   */
  auto GetYPosition() const -> const double;
  /**
   * Returns the mass of the particlee
   * @return
   */
  const double GetMass() const;
  const void Draw() const;
  /**
   * Returns the color of the particle
   */
   const cinder::ColorT<float> GetColor() const;
  /**
   * Updates the position of the particle every frame.
   */
  const void UpdatePosition();
  /**
   * Obtains the radius of the particle
   * @return the particle's radius
   */
  const double GetRadius() const;
  /**
   * Handles vertical wall crash by
   * changing the particle's velocity when crashing into vertical wall
   */
  const void CrashIntoVerticalWall();
  /**
   * Handles Horizontal wall crash by
   * changing the particle's velocity when crashing into horizontal wall
   */
  const void CrashIntoHorizontalWall();
  /**
   * Handles the velocity change when particle collides with another given
   * particle
   * @param other the other particle to collide with
   */
  //void CollideWithParticle(Particle& first, Particle& second);
  /**
   * Determines whether or not a particle is colliding with another
   * @param other the particle to determine if colliding with
   * @return true if the two particles are colliding, otherwise false.
   */
  auto IsCollidingWithParticle(Particle& other) -> const bool;
  /**
   * Finds the velocities of the first particle after collision
   * @param first the particle whose velocity will be found
   * @param second the particle collided with
   * @return the velocity
   */
  const vec2 FindVelocityAfterParticleCollision(Particle& first, Particle& second) const;

 private:
  /**
   * Stores the velocity of the particle
   */
  vec2 velocity_;
  /**
   * Stores the position of the particle
   */
  vec2 position_;
  /**
   * Stores the radius of the particle
   */
  double radius_;
  /**
   * Stores the mass of the particle
   */
   double mass_;
   /**
    * Stores the
    */
   cinder::ColorT<float> color_;
};
}

#endif  // IDEAL_GAS_PARTICLE_H


