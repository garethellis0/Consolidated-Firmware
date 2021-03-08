#pragma once

// The argument history needs to be long enough for us to test write every
// one of the possible 16x16x16 = 4096 values on the three 7-segment displays.
#include <math.h>
#include "App_SharedConstants.h"

#include <fff.h>
#include <gtest/gtest.h>

#include "Test_Utils.h"