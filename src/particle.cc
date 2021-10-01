#include "particle.h"
#include <glm/vec2.hpp>
using glm::vec2;
namespace idealgas {

Particle::Particle( vec2 pos,vec2 vel, double radius, double mass, cinder::ColorT<float> color) {
  velocity_ = vel;
  position_ = pos;
  radius_ = radius;
  mass_ = mass;
  color_ = color;

}
const vec2 Particle::GetVelocity() const {
  return velocity_;
}

const vec2 Particle::GetPosition() const {
  return position_;
}
const void Particle::SetVelocity(vec2 newVel){
  velocity_ = newVel;
}

const double Particle::GetXVelocity() const  {
  return velocity_.x;
}
const double Particle::GetYVelocity() const  {
  return velocity_.y;

}
const double Particle::GetXPosition() const{
  return position_.x;

}
auto Particle::GetYPosition() const -> const double {
  return position_.y;
}
auto Particle::GetRadius() const -> const double {
  return radius_;
}
const double Particle::GetMass() const {
  return mass_;
}
const void Particle::Draw() const {
  ci::gl::drawSolidCircle(position_, radius_);
}
const cinder::ColorT<float> Particle:: GetColor() const {
  return color_;
}
const void Particle::UpdatePosition() {
  position_ += velocity_;
}

const void Particle::CrashIntoHorizontalWall() {
  SetVelocity(vec2(this->GetXVelocity(), this->GetYVelocity() * -1));

}
const void Particle::CrashIntoVerticalWall() {
  SetVelocity(vec2(this->GetXVelocity() * -1, this->GetYVelocity()));
}


const vec2 Particle::FindVelocityAfterParticleCollision(Particle& first, Particle& second) const {
  vec2 velocityDifference = first.GetVelocity() - second.GetVelocity();
  vec2 positionDifference = first.GetPosition() - second.GetPosition();
  double product = glm::dot(velocityDifference, positionDifference);
  double length = glm::length(positionDifference);
  double massFrac = ((2 * second.GetMass())/(first.GetMass() + second.GetMass()));
  vec2 toSubtract = positionDifference.operator*=(massFrac * (product/(length * length)));
  return first.GetVelocity() - toSubtract;
}

auto Particle::IsCollidingWithParticle(Particle& other) -> const bool {
  if((glm::distance(this->GetPosition(), other.GetPosition())) <=
      (this->radius_ + other.GetRadius())) {
    return true;
  }
  return false;
}
};

