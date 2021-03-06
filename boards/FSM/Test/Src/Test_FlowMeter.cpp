#include "Test_Fsm.h"

extern "C"
{
#include "App_FlowMeter.h"
}

FAKE_VALUE_FUNC(float, get_flow_rate);

class FlowMeterTest : public testing::Test
{
  protected:
    void SetUp() override
    {
        flow_meter = App_FlowMeter_Create(get_flow_rate);

        RESET_FAKE(get_flow_rate);
    }

    void TearDown() override
    {
        TearDownObject(flow_meter, App_FlowMeter_Destroy);
    }

    struct FlowMeter *flow_meter;
};

TEST_F(FlowMeterTest, check_if_flow_rate_is_updated_after_tick)
{
    get_flow_rate_fake.return_val = 1.0f;
    ASSERT_EQ(
        get_flow_rate_fake.return_val, App_FlowMeter_GetFlowRate(flow_meter));
}
