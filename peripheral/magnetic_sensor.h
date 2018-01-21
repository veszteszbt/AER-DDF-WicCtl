#ifndef PERIPHERAL_MAGNETIC_SENSOR_H
# define PERIPHERAL_MAGNETIC_SENSOR_H
# include <peripheral/gpio_input.h>
namespace peripheral {

template<typename TConfig>
using magnetic_sensor = gpio_input<TConfig>;

}
#endif
