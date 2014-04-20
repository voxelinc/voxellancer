#pragma once

#include <string>
#include <vector>

namespace {
    enum BufferNames {
        Default = 0,
        Color,
        FXAA,
        NormalZ,
        Emissisiveness,
        BlurTmp,
        Bloom,
        TransparencyAccumulation,
        BufferCount // should always be last member and not be used as a name
    };

    // used to map enum values to strings
    std::vector<std::string> bufferNames = {
        "Default",
        "Color",
        "FXAA",
        "NormalZ",
        "Emissisiveness",
        "BlurTmp",
        "Bloom",
        "TransparencyAccumulation",
    };
}
