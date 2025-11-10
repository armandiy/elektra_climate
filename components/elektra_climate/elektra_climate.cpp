#include "elektra_climate.h"

namespace esphome {
namespace elektra_climate {

void ElektraClimate::setup() { irsend_.begin(); }

}  // namespace elektra_climate
}  // namespace esphome
