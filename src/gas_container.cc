#include "gas_container.h"
namespace idealgas {
using glm::vec2;

GasContainer::GasContainer(int numYellow, int numRed, int numOrange) {
  lowerbound_ = vec2(kLowerXBound, kLowerYBound);
  upperbound_ = vec2(kUpperXBound, kUpperYBound);
  AddParticles("yellow", numYellow);
  AddParticles("red", numRed);
  AddParticles("orange", numOrange);

}
void GasContainer::AddParticles(ci::Color color, int num)  {
  for(size_t i = 0; i < num; i++) {
    if(color == kColorYellow) {
      Particle yellow = Particle(vec2(200, 200),
                               vec2(3.1, 3.1), 10, 30.00, "yellow");
      particles_.push_back(yellow);
    }
    if(color == kColorRed) {
      Particle red = Particle(vec2(140, 300),
                                 vec2(1.9, 2.2), 10, 100.0, "red");
      particles_.push_back(red);
    }
    if(color == kColorOrange) {
      Particle orange = Particle(vec2(140, 260),
                                 vec2(.9, 1.2), 10, 500.0, "orange");
      particles_.push_back(orange);
    }
  }
}
void GasContainer::Display() const {
  ci::gl::color(ci::Color(kHistoColor));
  ci::gl::drawStrokedRect(ci::Rectf(lowerbound_, upperbound_));

  for (const Particle& part: particles_) {
    ci::gl::color(ci::Color(part.GetColor()));
    part.Draw();
  }
}

bool GasContainer::ParticleIsCrashingVerticalWall(const Particle& part) {
  return ((part.GetXPosition() - part.GetRadius() <= lowerbound_.x ||
           part.GetXPosition() + part.GetRadius() >= upperbound_.x));
}

bool GasContainer::ParticleIsCrashingHorizontalWall(const Particle& part) {
  return ((part.GetYPosition() - part.GetRadius() <= lowerbound_.y ||
           part.GetYPosition() + part.GetRadius() >= upperbound_.y));
}

void GasContainer::AdvanceOneFrame() {
  CollideWithContainerParticles();
  for (Particle& part: particles_) {
    if (ParticleIsCrashingHorizontalWall(part)) {
      part.CrashIntoHorizontalWall();
    } else if (ParticleIsCrashingVerticalWall(part)) {
      part.CrashIntoVerticalWall();
   }
    part.UpdatePosition();
  }
}
void GasContainer::CollideWithParticle(Particle& first, Particle& second) {
  vec2 vel1 = first.FindVelocityAfterParticleCollision(first, second);
  vec2 vel2 = second.FindVelocityAfterParticleCollision(second, first);
  first.SetVelocity(vel1);
  second.SetVelocity(vel2);
}

void GasContainer::CollideWithContainerParticles() {
  for (size_t i = 0; i < particles_.size(); i++) {
    for (size_t j = i + 1; j < particles_.size(); j++) {
      if (particles_[i].IsCollidingWithParticle(particles_[j])) {
        if (ParticlesShouldCollide(particles_[i], particles_[j])) {
          CollideWithParticle(particles_[i], particles_[j]);
          //particles_[i].CollideWithParticle(particles_[j]);
          //make CollideParticles with two particles
          //particles_[j].CollideWithParticle(particles_[i]);
          break;
        }
      }

    }
  }
}

void GasContainer::SetLowerAndUpperBounds(const vec2 lower, const vec2 upper) {
  lowerbound_ = lower;
  upperbound_ = upper;
}

void GasContainer::SetParticles(const std::vector<Particle>& particles) {
  particles_ = particles;

}

std::vector<Particle> GasContainer::GetParticles() {
  return particles_;
}

bool GasContainer::ParticlesShouldCollide(const Particle& particle1, const Particle& particle2) {
  vec2 velocityDiff = particle1.GetVelocity() - particle2.GetVelocity();
  vec2 positionDiff = particle1.GetPosition() - particle2.GetPosition();
  if (glm::dot(velocityDiff, positionDiff) < 0) {
    return true;
  }
  return false;
}
}  // namespace idealgas
