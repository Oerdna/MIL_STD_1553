/* Author Andrej Tsymb */

/* Include Section */
#include <types.h>
#include <string.h>
#include "device_1895va1t.h"

#ifdef DEBUG
#include "print.h"
// or something
#endif

void device_1895va1t_deinit(DEVICE_1895VA1T *device)
{
#ifdef DEBUG
print_txt("entered in caller deinit device\n\r");
#endif

    /* Reset Device */
    device->regs->SRR.bits.RESET = _1895VA1T_ENABLE;
    /* Erase ram mem */
    memset(device->ram, 0x0, (sizeof(*device->ram)));
};