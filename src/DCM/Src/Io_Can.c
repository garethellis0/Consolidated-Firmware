/*****************************************************************************
 * Includes
 ******************************************************************************/
#include "Io_Can.h"
#include "SharedMacros.h"

/******************************************************************************
 * Module Preprocessor Constants
 ******************************************************************************/

/******************************************************************************
 * Module Preprocessor Macros
 ******************************************************************************/

/******************************************************************************
 * Module Typedefs
 ******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 ******************************************************************************/
// clang-format off
static CanMaskFilterConfig_Struct mask_filters[] =
{
    INIT_MASK_FILTER(MASKMODE_16BIT_ID_BMS, MASKMODE_16BIT_MASK_BMS),
    INIT_MASK_FILTER(MASKMODE_16BIT_ID_FSM, MASKMODE_16BIT_MASK_FSM),
    INIT_MASK_FILTER(MASKMODE_16BIT_ID_SHARED, MASKMODE_16BIT_MASK_SHARED),
    INIT_MASK_FILTER(MASKMODE_16BIT_ID_BAMOCAR_TX, MASKMODE_16BIT_MASK_BAMOCAR_TX),
    INIT_MASK_FILTER(MASKMODE_16BIT_ID_BAMOCAR_RX, MASKMODE_16BIT_MASK_BAMOCAR_RX)
};
// clang-format on

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

/******************************************************************************
 * Private Function Definitions
 ******************************************************************************/

/******************************************************************************
 * Function Definitions
 ******************************************************************************/
CanMaskFilterConfig_Struct *Io_Can_GetCanMaskFilters(void)
{
    return mask_filters;
}

uint32_t Io_Can_GetNumberOfCanMaskFilters(void)
{
    return NUM_ELEMENTS_IN_ARRAY(mask_filters);
}
