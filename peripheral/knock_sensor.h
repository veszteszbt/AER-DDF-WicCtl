#ifndef PERIPHERAL_KNOCK_SENSOR_H
# define PERIPHERAL_KNOCK_SENSOR_H
# include <peripheral/gpio_input.h>
namespace peripheral {

template<typename TConfig>
using knock_sensor = gpio_input<TConfig>;

}
#endif
