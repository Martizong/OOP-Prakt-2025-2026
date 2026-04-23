#include "ConsultantUtils.h"
#include <cstring>

bool ConsultantUtils::isGoodForGaming(const Computer& c) {
    const char* cpu = c.getProcessor();
    int gpu = c.getVideo();

    bool cpuOK = (strcmp(cpu, "i5") == 0 || strcmp(cpu, "i7") == 0);
    bool gpuOK = (gpu == 3060 || gpu == 3070 || gpu == 3080 || gpu == 3090);
    bool hddOK = c.getHardDrive() >= 512;

    return cpuOK && gpuOK && hddOK;
}

bool ConsultantUtils::isGoodForTravel(const Computer& c) {
    return c.getWeight() <= 2.5 && c.getBatteryLife() > 6;
}
