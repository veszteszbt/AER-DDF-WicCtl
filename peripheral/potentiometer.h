#ifndef PERIPHERAL_POTENTIOMETER_H
# define PERIPHERAL_POTENTIOMETER_H
# include <peripheral/voltage_level.h>
namespace peripheral {

template<typename TConfig>
using potentiometer = voltage_level<TConfig>;

}
#endif
