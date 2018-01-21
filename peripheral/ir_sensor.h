#ifndef PERIPHERAL_IR_SENSOR_H
# define PERIPHERAL_IR_SENSOR_H
# include <peripheral/gpio_input.h>
namespace peripheral {

template<typename TConfig>
using ir_sensor = gpio_input<TConfig>;

}
#endif
