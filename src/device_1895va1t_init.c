/* Author Andrej Tsymb */

/* Include Section */
#include <types.h>
#include <string.h>
#include "device_1895va1t.h"

#ifdef DEBUG
#include "print.h"
// or something
#endif

void device_1895va1t_init(DEVICE_1895VA1T * device, uint32_t vaddr)
{
#ifdef DEBUG
print_txt("entered in caller init device\n\r");
#endif

    /* Выдача виртуального адресов со смещением */
    device->regs = (_1895VA1T_REGS_TYPE*)((vaddr & 0xffff0000) + RTL_1895VA1T_ADDR);
    device->ram = (_1895VA1T_REGS_TYPE*)((vaddr & 0xffff0000) + RTL_1895VA1T_BASE_MEM);

#ifdef DEBUG
print_txt("type addr ");
print_hex(device->regs);
print_txt("mem addr ");
print_hex(device->ram);
#endif

    /* Сброс всех натсроек */
    device->regs->SRR.bits.RESET = _1895VA1T_ENABLE;
    //device->regs->SRR.data = 0x0001;

    /* Init variables */
    int index = 0;
    uint16_t garbaer_blk_data_rx = _TO_H1895VA1T_ADDR((uint16_t)&(device->ram->RAM_BLK_DATA_S[0]));
    uint16_t garbaer_blk_data_tx = _TO_H1895VA1T_ADDR((uint16_t)&(device->ram->RAM_BLK_DATA_S[1]));
    uint16_t garbaer_blk_data_bcs = _TO_H1895VA1T_ADDR((uint16_t)&(device->ram->RAM_BLK_DATA_S[2]));
    union _1895VA1T_RT_CW_REG template_single_rx_msg = {.bits.RX_EOM_I = 1};
    union _1895VA1T_RT_CW_REG template_single_tx_msg = {.bits.TX_EOM_I = 1};
    uint32_t index_ill_1 = _h1895VA1T_index_illegal_tlb(1, 0, 9, 0);
    uint32_t index_ill_2 = _h1895VA1T_index_illegal_tlb(1, 0, 10, 0);
    uint32_t index_ill_3 = _h1895VA1T_index_illegal_tlb(1, 1, 18, 0);

    /* Extended mode memory */
    device->regs->CFG3.bits.EME = _1895VA1T_ENABLE;
    //device->regs->CFG3.data = 0x8000;

#ifdef DEBUG
print_txt("cfg3 ");
print_hex(device->regs->CFG5.data);
#endif 

    device->regs->CFG5.bits._12MHZ = _1895VA1T_ENABLE;
    //device->regs->CFG5.data = 0x8000;

#ifdef DEBUG
print_txt("cfg5 ");
print_hex(device->regs->CFG5.data);
#endif 

    device->regs->CFG6.bits.ECA = _1895VA1T_ENABLE;
    //device->regs->CFG6.data = 0x4000;

#ifdef DEBUG
print_txt("cfg6 ");
print_hex(device->regs->CFG6.data);
#endif 

#ifdef DEBUG
print_txt("erase ram mem device\n\r");
#endif
    
    /* Erase Ram */
    memset(device->ram, 0x0, (sizeof(*device->ram)));

#ifdef DEBUG
print_txt("init ill tlb\n\r");
#endif

    /* Init illegal table */
    for(index = 0; index < 256; index++) {
        device->ram->TLB_SUBADR_ILLEGAL[index].data = 0xFFFF;
    };

#ifdef DEBUG
print_txt("check fst ");
print_hex(device->ram->TLB_SUBADR_ILLEGAL[0].word);
print_txt("check lst ");
print_hex(device->ram->TLB_SUBADR_ILLEGAL[255].word);
#endif

#ifdef DEBUG
print_txt("init subaddr tlb\n\r");
#endif

    /* Set address for garbage traffic */
    for(index = 0; index < 32; index++){
        device->ram->TLB_SUBADR_RX_RT_A[index].data = garbaer_blk_data_rx;
        device->ram->TLB_SUBADR_TX_RT_A[index].data = garbaer_blk_data_tx;
        device->ram->TLB_SUBADR_BCST_RT_A[index].data = garbaer_blk_data_bcs;
    }

#ifdef DEBUG
print_txt("check tx ");
print_hex(device->ram->TLB_SUBADR_RX_RT_A[31].word);
print_txt("check rx ");
print_hex(device->ram->TLB_SUBADR_TX_RT_A[31].word);
#endif

#ifdef DEBUG
print_txt("entity ram mem device's\n\r");
#endif

    /* init stack pointer */
    device->ram->PTR_COMMAND_STACK_A = device->ram->COMMAND_STACK_A;
    
    /* Set address for message by format 1 */
    device->ram->TLB_SUBADR_RX_RT_A[9].data = _TO_H1895VA1T_ADDR((uint16_t)&(device->ram->RAM_BLK_DATA_L[0]));
    device->ram->TLB_SUBADR_RX_RT_A[10].data = _TO_H1895VA1T_ADDR((uint16_t)&(device->ram->RAM_BLK_DATA_L[1]));
    
    /* Set address for message by format 2 */
    device->ram->TLB_SUBADR_TX_RT_A[18].data = _TO_H1895VA1T_ADDR((uint16_t)&(device->ram->RAM_BLK_DATA_L[2]));

    /* Setting reaction by message */
    device->ram->TLB_SUBADR_SACW_RT_A[9].data = (uint16_t)template_single_rx_msg.data;
    device->ram->TLB_SUBADR_SACW_RT_A[10].data = (uint16_t)template_single_rx_msg.data;
    device->ram->TLB_SUBADR_SACW_RT_A[18].data = (uint16_t)template_single_tx_msg.data;
    
    /* Set legal size of message */
    device->ram->TLB_SUBADR_ILLEGAL[index_ill_1].data = ~(1 << 6); // 6 words
    device->ram->TLB_SUBADR_ILLEGAL[index_ill_2].data = ~(1 << 0); // 32 words
    device->ram->TLB_SUBADR_ILLEGAL[index_ill_3].data = ~(1 << 1); // 1 words

    /* End of settings */
    /* IMR */
    //device->regs->IMR.bits.M_EOM    = _1895VA1T_ENABLE;     
    //device->regs->IMR.bits.M_SCW_E  = _1895VA1T_ENABLE;     
    device->regs->IMR.data = 0x0011;
#ifdef DEBUG
print_txt("imr ");
print_hex(device->regs->IMR.data);
#endif   
    /* CFG3 */
    //device->regs->CFG3.bits.I_RX_TD = _1895VA1T_ENABLE;     
    device->regs->CFG3.data = 0x8010;
#ifdef DEBUG
print_txt("cfg3 ");
print_hex(device->regs->CFG3.data);
#endif    
    /* CFG2 */
    //device->regs->CFG2.bits.ERMM    = _1895VA1T_ENABLE;     
    //device->regs->CFG2.bits.L_P_IR  = _1895VA1T_ENABLE;     
    //device->regs->CFG2.bits.ISAC    = _1895VA1T_ENABLE;     
    //device->regs->CFG2.bits.BLUTE   = _1895VA1T_ENABLE;     
    //device->regs->CFG2.bits.SBD     = _1895VA1T_ENABLE;     
    device->regs->CFG2.data = 0x210B;
#ifdef DEBUG
print_txt("cfg2 ");
print_hex(device->regs->CFG2.data);
#endif
    /* CFG1 */
    //device->regs->CFG1.bits_rt_std.MME      = _1895VA1T_DISABLE;        
    //device->regs->CFG1.bits_rt_std.CA_B_A   = _1895VA1T_DISABLE;        
    //device->regs->CFG1.bits_rt_std.RT_BC_MT = _1895VA1T_CFG3_MODE_RT;   
    //device->regs->CFG1.bits_rt_std.DBCA     = _1895VA1T_ENABLE;         
    //device->regs->CFG1.bits_rt_std.BUSY     = _1895VA1T_ENABLE;         
    //device->regs->CFG1.bits_rt_std.SR       = _1895VA1T_ENABLE;         
    //device->regs->CFG1.bits_rt_std.SF       = _1895VA1T_ENABLE;         
    //device->regs->CFG1.bits_rt_std.RTF      = _1895VA1T_ENABLE;         
    device->regs->CFG1.data = 0x8F80;
#ifdef DEBUG
print_txt("cfg1 ");
print_hex(device->regs->CFG1.data);
#endif
};
