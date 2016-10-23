#include <errno.h>

#include "ctlr.h"
#include "devices.h"
#include "devices/device_impl.h"

struct ctlr_dev_connect_func_t {
	enum ctlr_dev_id_t id;
	ctlr_dev_connect_func connect;
};

DECLARE_DEV_CONNECT_FUNC(simple_connect);

static const struct ctlr_dev_connect_func_t devices[] = {
	{CTLR_DEV_SIMPLE, simple_connect},
};
#define CTLR_NUM_DEVS (sizeof(devices) / sizeof(devices[0]))

struct ctlr_dev_t *ctlr_dev_connect(enum ctlr_dev_id_t dev_id,
				    ctlr_event_func event_func,
				    void *userdata,
				    void *future)
{
	if(dev_id < CTLR_NUM_DEVS && devices[dev_id].connect)
		return devices[dev_id].connect(event_func,
					       userdata,
					       future);
	return 0;
}

uint32_t ctlr_dev_poll(struct ctlr_dev_t *dev)
{
	if(dev && dev->poll)
		return dev->poll(dev);
	return 0;
}

int32_t ctlr_dev_disconnect(struct ctlr_dev_t *dev)
{
	if(dev && dev->disconnect)
		return dev->disconnect(dev);
	return -ENOTSUP;
}

void ctlr_dev_light_set(struct ctlr_dev_t *dev, uint32_t light_id,
			uint32_t light_status)
{
	if(dev && dev->light_set)
		dev->light_set(dev, light_id, light_status);
}

void ctlr_dev_grid_light_set(struct ctlr_dev_t *dev, uint32_t grid_id,
			     uint32_t light_id, uint32_t light_status)
{
	if(dev && dev->grid_light_set)
		dev->grid_light_set(dev, grid_id, light_id, light_status);
}
