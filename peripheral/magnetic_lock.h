#ifndef PERIPHERAL_MAGNETIC_LOCK_H
# define PERIPHERAL_MAGNETIC_LOCK_H
# include <peripheral/gpio_output.h>
namespace peripheral {

template<typename TConfig>
using magnetic_lock = gpio_output<TConfig>;

}
