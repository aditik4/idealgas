#pragma once


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "histogram.h"
using glm::vec2;

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;

  const int kWindowSize = 875;
  const int kMargin = 100;

 private:
  GasContainer container_ = GasContainer(10, 20, 30);
  Histogram histogram1_ = Histogram((vec2(100, 500)), (glm::vec2(300, 700)),  ("red"));
  Histogram histogram2_ = Histogram(vec2(350, 500), vec2(550, 700), "blue");
  Histogram histogram3_ = Histogram(vec2(600, 500), vec2(800, 700), "orange");
};

}  // namespace idealgas
