#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "App_InvWorld.h"

struct InvWorld
{
    struct InvCanTxInterface *can_tx_interface;
    struct InvCanRxInterface *can_rx_interface;
    struct HeartbeatMonitor * heartbeat_monitor;
    struct RgbLedSequence *   rgb_led_sequence;
    struct Clock *            clock;
    struct ErrorTable * error_table;
};

struct InvWorld *App_InvWorld_Create(
    struct InvCanTxInterface *const can_tx_interface,
    struct InvCanRxInterface *const can_rx_interface,
    struct HeartbeatMonitor *const  heartbeat_monitor,
    struct RgbLedSequence *const    rgb_led_sequence,
    struct ErrorTable *       error_table,
    struct Clock *const             clock)
{
    struct InvWorld *world = (struct InvWorld *)malloc(sizeof(struct InvWorld));
    assert(world != NULL);

    world->can_tx_interface        = can_tx_interface;
    world->can_rx_interface        = can_rx_interface;
    world->heartbeat_monitor       = heartbeat_monitor;
    world->rgb_led_sequence        = rgb_led_sequence;
    world->error_table = error_table;
    world->clock                   = clock;

    return world;
}

void App_InvWorld_Destroy(struct InvWorld *world)
{
    free(world);
}

struct InvCanTxInterface *
    App_InvWorld_GetCanTx(const struct InvWorld *const world)
{
    return world->can_tx_interface;
}

struct InvCanRxInterface *
    App_InvWorld_GetCanRx(const struct InvWorld *const world)
{
    return world->can_rx_interface;
}

struct HeartbeatMonitor *
    App_InvWorld_GetHeartbeatMonitor(const struct InvWorld *const world)
{
    return world->heartbeat_monitor;
}

struct RgbLedSequence *
    App_InvWorld_GetRgbLedSequence(const struct InvWorld *const world)
{
    return world->rgb_led_sequence;
}

struct Clock *App_InvWorld_GetClock(const struct InvWorld *world)
{
    return world->clock;
}
