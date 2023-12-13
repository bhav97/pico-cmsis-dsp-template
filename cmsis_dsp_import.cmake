set(CMSIS_DSP_PATH "${CMSIS_DSP_PATH}"
    CACHE
    PATH "Path to the CMSIS DSP library"
)

if (NOT CMSIS_DSP_PATH)
    include(FetchContent)
    FetchContent_Declare(
        cmsis_dsp
        GIT_REPOSITORY https://github.com/ARM-software/CMSIS-DSP
        GIT_TAG main
        )

    if (NOT cmsis_dsp)
        message("Downloading CMSIS DSP libs")
        FetchContent_Populate(cmsis_dsp)
        set(CMSIS_DSP_PATH ${cmsis_dsp_SOURCE_DIR})
    endif()
endif()

set(CMSIS_DSP_PATH "${CMSIS_DSP_PATH}"
    CACHE
    PATH "Path to the CMSIS DSP library"
    FORCE
)
