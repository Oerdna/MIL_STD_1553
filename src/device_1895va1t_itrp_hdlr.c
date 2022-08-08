/* Author Andrej Tsymb */

/* Include Section */
#include <types.h>
#include "device_1895va1t.h"

#ifdef DEBUG
#include "print.h"
// or something
#endif

/* Interrupt handler for device  
    @param DEVICE_1895VA1T * device - ptr of device struct
 */
void device_1895va1t_itrp_hdlr(DEVICE_1895VA1T * device)
{
#ifdef DEBUG
print_txt("entered in caller hdlr device\n\r");
#endif

    /* init new frame */
    _1895VA1T_FRAME_STACK_TYPE *current_frame;
    union _1895VA1T_STATE_WORD_BLOCK_REG reg_stat;
    union _1895VA1T_BLOCK_DATA *data;
    union _1895VA1T_ISR_REG isr;
    uint16_t time;
    uint16_t raw_cmd;

    /* read ISR reg */
    isr = device->regs->ISR;
    /* reset ir reg */
    device->regs->SRR.bits.IR = 0x1;
    
    if(isr.word == 0) {        
        //return;
    }
#ifdef DEBUG
print_txt("device isr ");
print_hex(isr.word);
#endif

    if(isr.bits.FE){
        ;
    } else if (isr.bits.EOM){
        ;
    }

    /* get ptr of current stack frame */
    current_frame = _FROM_H1895VA1T_ADDR((((uint32_t)device->ram->PTR_COMMAND_STACK_A - 4) & 0xff), device);

#ifdef DEBUG
print_txt("ptr to crnt stack frame ");
print_hex(current_frame);
#endif

    /* copy info */
    time = (uint16_t)current_frame->TIME_TAG.data;
    raw_cmd = (uint16_t)current_frame->COMMAND_WORD.data;
    reg_stat.data = (uint16_t)current_frame->WORD_OF_MESSAGE.data;
    data = _FROM_H1895VA1T_ADDR((uint32_t)current_frame->PTR_DATA_WORD, device);

#ifdef DEBUG
print_txt("time ");
print_hex(time);
print_txt("raw cmd ");
print_hex(raw_cmd);
print_txt("reg stat ");
print_hex(reg_stat.word);
print_txt("ptr data ");
print_hex(data);
#endif

#ifdef DEBUG
print_txt("finish hdlr\n\r");
#endif

};