#ifdef __cplusplus__
extern "C" {
#endif

#include <stdint.h>

#include <pthread.h>

/** Stupid WebRTC Audio Processing C "API". Dont use */

struct webrtc_aec;

/** Allocate a configured audio processor
 * @webrtc_aec: a pointer to an internal structure allocated by the library
 * @config_json: ignored
 * @returns: various mysterious error states, or 0
 * */
int webrtc_aec_init(struct webrtc_aec**, const char* config_json);

/** Deallocate main structure
 */
void webrtc_aec_destroy(struct webrtc_aec*);

//int webrtc_aec_process_playout
//int webrtc_aec_process_recording


#ifdef __cplusplus__
}
#endif
