

typedef struct {
    resolution_t resolution;
    display_depth_t depth;
    gamma_correction_t gamma;
    display_filter_mode_t filter;
    int bufferCount;
} DisplaySettingsComponent;

void display_init(
    resolution_t res,           // screen resolution (e.g., 320x240)
    display_depth_t depth,      // color depth (16 or 32 bits)
    int buffer_count,           // number of frame buffers (typically 2 or 3)
    gamma_correction_t gamma,   // gamma correction mode
    display_filter_mode_t filter // filtering method
);
