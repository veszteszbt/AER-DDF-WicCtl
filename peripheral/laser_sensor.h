#ifndef PERIPHERAL_LASER_SENSOR_H
# define PERIPHERAL_LASER_SENSOR_H
# include <peripheral/gpio_input.h>
namespace peripheral {

template<typename TConfig>
using laser_sensor = gpio_input<TConfig>;

}
#endif
