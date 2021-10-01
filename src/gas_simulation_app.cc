#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  container_.Display();
  histogram1_.CreateHistogram();
  histogram2_.CreateHistogram();
  histogram3_.CreateHistogram();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
  histogram1_.SetAllSpeedsOfParticleType(container_, "red");
  histogram1_.StoreFrequenciesOfSpeed();
  histogram2_.SetAllSpeedsOfParticleType(container_, "blue");
  histogram2_.StoreFrequenciesOfSpeed();
  histogram3_.SetAllSpeedsOfParticleType(container_, "orange");
  histogram3_.StoreFrequenciesOfSpeed();

}

}  // namespace idealgas
