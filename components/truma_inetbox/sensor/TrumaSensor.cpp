#include "TrumaSensor.h"
#include "esphome/core/log.h"
#include "esphome/components/truma_inetbox/helpers.h"

namespace esphome {
namespace truma_inetbox {

static const char *const TAG = "truma_inetbox.sensor";

void TrumaSensor::setup() {
  this->parent_->get_alde_status()->add_on_message_callback([this](const StatusFrameAldeStatus *status_alde) {
    switch (this->type_) {
      case TRUMA_SENSOR_TYPE::CURRENT_ROOM_TEMPERATURE:
        this->publish_state(temp_code_to_decimal(status_alde->current_temp_inside));
        break;
      case TRUMA_SENSOR_TYPE::CURRENT_WATER_TEMPERATURE:
        this->publish_state(static_cast<float>(status_alde->unknown_13));
        break;
      case TRUMA_SENSOR_TYPE::TARGET_ROOM_TEMPERATURE:
        this->publish_state(temp_code_to_decimal(status_alde->target_temp_room));
        break;
      case TRUMA_SENSOR_TYPE::TARGET_WATER_TEMPERATURE:
        this->publish_state(static_cast<float>(status_alde->water_mode));
        break;
      //case TRUMA_SENSOR_TYPE::HEATING_MODE:
      //this->publish_state(static_cast<float>(status_alde->heater_mode));
      //break;
      case TRUMA_SENSOR_TYPE::ELECTRIC_POWER_LEVEL:
        this->publish_state(static_cast<float>(status_alde->el_mode));
        break;
      case TRUMA_SENSOR_TYPE::ENERGY_MIX:
        this->publish_state(static_cast<float>(status_alde->gas_mode));
        break;
      case TRUMA_SENSOR_TYPE::OPERATING_STATUS:
        this->publish_state(static_cast<float>(status_alde->heater_prio));
        break;
     // case TRUMA_SENSOR_TYPE::HEATER_ERROR_CODE: {
     //   float errorcode = status_alde->error_code_high * 100.0f + status_alde->error_code_low;
     //   this->publish_state(errorcode);
     //   break;
     // }
      default:
        break;
    }
  });
}

void TrumaSensor::dump_config() {
  LOG_SENSOR("", "Truma Sensor", this);
  ESP_LOGCONFIG(TAG, "  Type '%s'", enum_to_c_str(this->type_));
}
}  // namespace truma_inetbox
}  // namespace esphome
