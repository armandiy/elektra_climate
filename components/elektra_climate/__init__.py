import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate
from esphome.const import CONF_NAME, CONF_ID, CONF_PIN

CODEOWNERS = [""]

DEPENDENCIES = ["climate"]

CONF_TX_PIN = "tx_pin"

elektra_climate_ns = cg.esphome_ns.namespace("elektra_climate")
ElektraClimate = elektra_climate_ns.class_(
    "ElektraClimate", climate.Climate, cg.Component
)

CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(ElektraClimate),
        cv.Required(CONF_TX_PIN): cv.int_,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_TX_PIN])
    await cg.register_component(var, config)
    await climate.register_climate(var, config)
