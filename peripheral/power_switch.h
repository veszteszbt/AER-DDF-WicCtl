#ifndef PERIPHERAL_POWER_SWITCH_H
# define PERIPHERAL_POWER_SWITCH_H
# include <peripheral/gpio_output.h>
namespace peripheral {

template<typename TConfig>
using power_switch = gpio_output<TConfig>;

}
#endif
