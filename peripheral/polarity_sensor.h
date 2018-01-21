#ifndef PERIPHERAL_POLARITY_SENSOR_H
# define PERIPHERAL_POLARITY_SENSOR_H
# include <peripheral/voltage_level.h>
namespace peripheral {

template<typename TConfig>
using polarity_sensor = voltage_level<TConfig>;

}
#endif
