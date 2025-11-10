#pragma once
#include "esphome.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "ir_ELEKTRA.h"

namespace esphome {
namespace elektra_climate {

class ElektraClimate : public climate::Climate, public Component {
 public:
  explicit ElektraClimate(uint16_t tx_pin) : irsend_(tx_pin) {}

  void setup() override { irsend_.begin(); }

  void control(const climate::ClimateCall &call) override {
    IRElektraAc ac(&irsend_);
    ac.begin();

    if (call.get_mode().has_value()) this->mode = *call.get_mode();
    if (call.get_target_temperature().has_value())
      this->target_temperature = *call.get_target_temperature();

    ac.setPower(this->mode != climate::CLIMATE_MODE_OFF);
    switch (this->mode) {
      case climate::CLIMATE_MODE_COOL: ac.setMode(kElektraCool); break;
      case climate::CLIMATE_MODE_HEAT: ac.setMode(kElektraHeat); break;
      case climate::CLIMATE_MODE_DRY: ac.setMode(kElektraDry); break;
      case climate::CLIMATE_MODE_FAN_ONLY: ac.setMode(kElektraFan); break;
      default: ac.setMode(kElektraAuto); break;
    }

    ac.setTemp((uint8_t) roundf(this->target_temperature));
    ac.send();
    this->publish_state();
  }

  climate::ClimateTraits traits() override {
    auto traits = climate::ClimateTraits();
    traits.set_supported_modes({
      climate::CLIMATE_MODE_OFF,
      climate::CLIMATE_MODE_COOL,
      climate::CLIMATE_MODE_HEAT,
      climate::CLIMATE_MODE_DRY,
      climate::CLIMATE_MODE_FAN_ONLY,
      climate::CLIMATE_MODE_AUTO
    });
    traits.set_visual_min_temperature(16);
    traits.set_visual_max_temperature(30);
    traits.set_visual_temperature_step(1.0f);
    return traits;
  }

 protected:
  IRsend irsend_;
};

}  // namespace elektra_climate
}  // namespace esphome
