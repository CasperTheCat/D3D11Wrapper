#pragma once
#include <cstdint>
#define LOG(x) "[INFO] " << x
#define LOGWRT(x) "[WRTE] " << x
#define LOGERR(x) "[ERRO] " << x
#define LOGWARN(x) "[WARN] " << x


bool IsWow64();

/// Convert the specified single precision float number to a half precision float number.
static uint16_t FloatToHalfFloat(float floatValue);

/// Convert the specified half float number to a single precision float number.
float HalfFloatToFloat(uint16_t halfFloat);