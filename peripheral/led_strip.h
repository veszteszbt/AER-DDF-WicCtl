#ifndef PERIPHERAL_LED_STRIP_H
# define PERIPHERAL_LED_STRIP_H
# include <peripheral/gpio_output.h>
namespace peripheral {

template<typename TConfig>
using led_strip = gpio_output<TConfig>;

}
