#ifndef PERIPHERAL_BUTTON_H
# define PERIPHERAL_BUTTON_H
# include <peripheral/gpio_input.h>
namespace peripheral {

template<typename TConfig>
using button = gpio_input<TConfig>;

}
#endif
