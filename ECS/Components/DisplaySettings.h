

typedef struct {
    resolution_t resolution;
    display_depth_t depth;
    gamma_correction_t gamma;
    display_filter_mode_t filter;
    int bufferCount;
    bool needsUpdate;
} DisplaySettingsComponent;

void DisplaySettings_Apply(DisplaySettingsComponent* settings);
