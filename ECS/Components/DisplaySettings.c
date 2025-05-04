// DisplaySettings.c
#include "DisplaySettings.h"
#include <libdragon.h>

void DisplaySettings_Apply(DisplaySettingsComponent* settings) {
    display_init(
        settings->resolution,
        settings->depth,
        settings->bufferCount,
        settings->gamma,
        settings->filter
    );
}

void display_init(
    resolution_t res,           // screen resolution (e.g., 320x240)
    display_depth_t depth,      // color depth (16 or 32 bits)
    int buffer_count,           // number of frame buffers (typically 2 or 3)
    gamma_correction_t gamma,   // gamma correction mode
    display_filter_mode_t filter // filtering method
);

void DisplaySystem(ComponentPool* pool, float deltaTime) {
    if (pool->count == 0) return;

    DisplaySettingsComponent* settings = (DisplaySettingsComponent*)pool->components[0];
    display_init(
        settings->resolution,
        settings->depth,
        settings->bufferCount,
        settings->gamma,
        settings->filter
    );

    if (!settings->needsUpdate) return;
    display_init(...);
    settings->needsUpdate = false;
}


void display_init(resolution_t res, display_depth_t depth, int buffer_count, gamma_correction_t gamma, display_filter_mode_t filter)
{
}
