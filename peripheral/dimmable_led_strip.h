#ifndef PERIPHERAL_DIMMABLE_LED_STRIP_H
# define PERIPHERAL_DIMMABLE_LED_STRIP_H
# include <peripheral/pwm_output.h>
namespace peripheral {

template<typename TConfig>
using dimmable_led_strip = pwm_output<TConfig>;

}
#endif
