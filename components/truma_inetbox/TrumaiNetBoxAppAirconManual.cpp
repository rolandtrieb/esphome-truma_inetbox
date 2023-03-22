#include "TrumaiNetBoxAppAirconManual.h"
#include "TrumaStatusFrameBuilder.h"
#include "esphome/core/log.h"
#include "helpers.h"

namespace esphome {
namespace truma_inetbox {

static const char *const TAG = "truma_inetbox.TrumaiNetBoxAppAirconManual";

StatusFrameAirconManualResponse *TrumaiNetBoxAppAirconManual::update_prepare() {
  // An update is currently going on.
  if (this->update_status_prepared_ || this->update_status_stale_) {
    return &this->update_status_;
  }

  // prepare status response
  this->update_status_ = {};
  this->update_status_.mode = this->data_.mode;
  this->update_status_.operation = this->data_.operation;
  this->update_status_.energy_mix = this->data_.energy_mix;
  this->update_status_.target_temp_aircon = this->data_.target_temp_aircon;

  this->update_status_prepared_ = true;
  return &this->update_status_;
}

void TrumaiNetBoxAppAirconManual::create_update_data(StatusFrame *response, u_int8_t *response_len,
                                                u_int8_t command_counter) {
  status_frame_create_empty(response, STATUS_FRAME_AIRCON_MANUAL_RESPONSE, sizeof(StatusFrameAirconManualResponse),
                            command_counter);

  response->inner.airconManualResponse.mode = this->update_status_.mode;
  response->inner.airconManualResponse.unknown_02 = this->update_status_.unknown_02;
  response->inner.airconManualResponse.operation = this->update_status_.operation;
  response->inner.airconManualResponse.energy_mix = this->update_status_.energy_mix;
  response->inner.airconManualResponse.target_temp_aircon = this->update_status_.target_temp_aircon;

  status_frame_calculate_checksum(response);
  (*response_len) = sizeof(StatusFrameHeader) + sizeof(StatusFrameAirconManualResponse);

  TrumaStausFrameResponseStorage<StatusFrameAirconManual, StatusFrameAirconManualResponse>::update_submitted();
}

void TrumaiNetBoxAppAirconManual::dump_data() const {}

}  // namespace truma_inetbox
}  // namespace esphome