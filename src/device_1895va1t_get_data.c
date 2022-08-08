/* Author Andrej Tsymb */

/* Include Section */
#include <types.h>
#include "device_1895va1t.h"

#ifdef DEBUG_MKO
#include "print.h"
// or something
#endif

_1895VA1T_CONDITION_t device_1895va1t_get_data(DEVICE_1895VA1T * device,
                                                _1895VA1T_MSG_t msg_t, 
                                                uint16_t sub_addr, 
                                                uint16_t size_data, 
                                                uint16_t *ptr_data)
{
#ifdef DEBUG_MKO
print_txt("entered in caller get data device\n\r");
#endif

    uint16_t index;
    union _1895VA1T_DATA_REG *ptr_needed_tlb;
    union _1895VA1T_BLOCK_DATA *ptr_needed_blk_data;

    if (msg_t > ((_1895VA1T_TX_RT_TYPE) |
                (_1895VA1T_RX_RT_TYPE) |
                (_1895VA1T_BCST_RT_TYPE)))
    {
        return _1895VA1T_MSG_TYPE_ERROR;
    }

    else if(!(sub_addr < 32))
    {
        return _1895VA1T_SUBADDR_LENGH_ERROR;
    }
    
    else if(!(size_data < 32))
    {
        return _1895VA1T_DATA_LENGH_ERROR;
    }

    switch (msg_t)
    {
    case _1895VA1T_TX_RT_TYPE:
        ptr_needed_tlb = device->ram->TLB_SUBADR_TX_RT_A;
        break;
    
    case _1895VA1T_RX_RT_TYPE:
        ptr_needed_tlb = device->ram->TLB_SUBADR_RX_RT_A;
        break;

    case _1895VA1T_BCST_RT_TYPE:
        ptr_needed_tlb = device->ram->TLB_SUBADR_BCST_RT_A;
        break;

    default:
        ptr_needed_tlb = device->ram->TLB_SUBADR_RX_RT_A;
        break;
    }

#ifdef DEBUG
print_txt("ptr of tlb ");
print_hex(ptr_needed_tlb);
#endif

    ptr_needed_blk_data = _FROM_H1895VA1T_ADDR(ptr_needed_tlb[sub_addr].word, device);

#ifdef DEBUG
print_txt("ptr of blk data ");
print_hex(ptr_needed_blk_data);
#endif

    for(index = 0; index < size_data; index++){
        ptr_data[index] = ptr_needed_blk_data->WORD_DATA[index].word;
    }

#ifdef DEBUG
print_txt("rd data ");
print_hex(ptr_needed_blk_data->WORD_DATA[0].word);
#endif

    return _1895VA1T_OK;
}