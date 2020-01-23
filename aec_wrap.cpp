#include "modules/audio_processing/include/audio_processing.h"

#include "aec.h"

using namespace webrtc;

struct webrtc_aec {
  AudioProcessing* proc{};
};

using AudioProcessingContext = webrtc_aec; // More C++-like name

namespace {

auto CreateApm(bool mobile_aec) -> AudioProcessing* {
  Config old_config;
  auto apm = AudioProcessingBuilder().Create(old_config);
  if (!apm) {
    return apm;
  }

  ProcessingConfig processing_config = {
      {{32000, 1}, {32000, 1}, {32000, 1}, {32000, 1}}};

  if (apm->Initialize(processing_config) != 0) {
    return nullptr;
  }

  // Disable all components except for an AEC and the residual echo detector.
  AudioProcessing::Config apm_config;
  apm_config.residual_echo_detector.enabled = true;
  apm_config.high_pass_filter.enabled = false;
  apm_config.gain_controller1.enabled = false;
  apm_config.gain_controller2.enabled = false;
  apm_config.echo_canceller.enabled = true;
  apm_config.echo_canceller.mobile_mode = mobile_aec;
  apm_config.noise_suppression.enabled = false;
  apm_config.level_estimation.enabled = false;
  apm_config.voice_detection.enabled = false;
  apm->ApplyConfig(apm_config);

  return apm;
}

} // end namespace


extern "C"
int webrtc_aec_init(struct webrtc_aec** aec, const char* config_json) {
	assert(aec);

	const bool use_mobile_aec = false;

	auto context = new AudioProcessingContext;
	*aec = context;

	context->proc = ::CreateApm(use_mobile_aec); 

  return 0;
}

extern "C"
void webrtc_aec_destroy(struct webrtc_aec* aec) {
  auto context = static_cast<AudioProcessingContext*>(aec);
  context->proc->Release();
  delete context;
}

