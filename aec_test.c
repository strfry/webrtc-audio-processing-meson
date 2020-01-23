#include "aec.h"


int main() {
    struct webrtc_aec *aec_context;

    int result = webrtc_aec_init(&aec_context, "{}");

    webrtc_aec_destroy(&aec_context);
}