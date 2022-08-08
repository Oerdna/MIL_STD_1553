#ifndef __1895VA1T_H
#define __1895VA1T_H
/* Export Macros */

#include <types.h>
// or something

/* Export define*/

/* Addr reg mem  */
#define RTL_1895VA1T_ADDR       0x00000
/* Addr ram mem */
#define RTL_1895VA1T_BASE_MEM   0x40000

/* Export enum */

typedef enum {
    _1895VA1T_DISABLE, // True
    _1895VA1T_ENABLE,  // False
} _1895VA1T_Bool_t;

typedef enum {
    _1895VA1T_TX_RT_TYPE,   // TX type
    _1895VA1T_RX_RT_TYPE,   // RX type
    _1895VA1T_BCST_RT_TYPE, // BCST type
} _1895VA1T_MSG_t;

typedef enum {
    _1895VA1T_MSG_TYPE_ERROR,           // Ошибка в типе сообщения
    _1895VA1T_SUBADDR_LENGH_ERROR,      // Ошибка размерности подадреса
    _1895VA1T_DATA_LENGH_ERROR,         // Ошбика размерности данных
    _1895VA1T_OK,                       // Все замечательно
} _1895VA1T_CONDITION_t;

/* Export struct */

//==================================================
// DATA REG
//==================================================

// Общий дата регистр для 1895VA1T
union _1895VA1T_DATA_REG
{
    uint32_t data; // 32 bit
    uint16_t word; // 16 bit
};

union _1895VA1T_BLOCK_DATA
{
    union _1895VA1T_DATA_REG WORD_DATA[32]; // Array of 32 words
};

//==================================================
// IMR
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_IMR_BITS {
    uint16_t M_EOM          :1; // End of Message
    uint16_t M_SS_MC_PT     :1; // Status Set/Mode Code/Pattern Triger
    uint16_t M_FE           :1; // Format Error
    uint16_t M_BC_EOF       :1; // BC End Of Frame
    uint16_t M_SCW_E        :1; // Selective Control Word EOM
    uint16_t M_RT_CBR       :1; // Circular Buffer Rollover
    uint16_t M_TT_ROL       :1; // Time Tag Rollover
    uint16_t M_RT_APE       :1; // Address Parity Error
    uint16_t M_BC_R         :1; // BC Retry
    uint16_t M_HF           :1; // Handshake Failru
    uint16_t M_MT_DSR       :1; // MT Data Stack Rollover
    uint16_t M_MT_CSR       :1; // MT Command Stack Rollover
    uint16_t M_BT_CSR       :1; // BC/RT Command Stack Rollover
    uint16_t M_BT_TT        :1; // BC/RT transmiter Timeout
    uint16_t M_RP_ER        :1; // RAM Parity Error
    uint16_t rsrv           :1; // Reserv
    uint16_t padding        :16;   
};

// IMR - регистр маскирования прерывания
union _1895VA1T_IMR_REG {
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_IMR_BITS   bits;
};

//==================================================
// CFG1
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_CFG1_RT_STD_BITS{
    uint16_t RT_MIP     :1; // Message In Progress
    uint16_t RESERV     :6; // RESERV
    uint16_t RTF        :1; // invrs RT Flag
    uint16_t SF         :1; // invrs Subsytem Flag
    uint16_t SR         :1; // invrs Service Request
    uint16_t BUSY       :1; // invrs Busy
    uint16_t DBCA       :1; // invrs Dynamic Bus Control Acceptance
    uint16_t MME        :1; // Meassage Monitor Enable
    uint16_t CA_B_A     :1; // Current Area B/A
    uint16_t RT_BC_MT   :2; // MODE RAM RT/BC/MT
    uint16_t padding    :16;
};

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_CFG1_RT_ALT_BITS{
    uint16_t RT_MIP     :1;     // Message In Progress
    uint16_t S10        :11;    // S10 Array
    uint16_t MME        :1;     // Meassage Monitor Enable
    uint16_t CA_B_A     :1;     // Current Area B/A
    uint16_t RT_BC_MT   :2;     // MODE RAM RT/BC/MT
    uint16_t padding    :16;
};

// CFG1 - Регистр конфигурации 1
union _1895VA1T_CFG1_REG {
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_CFG1_RT_STD_BITS   bits_rt_std;
    struct _1895VA1T_CFG1_RT_ALT_BITS   bits_rt_alt;
};

enum _1895VA1T_CFG3_RT_BC_MT{
    _1895VA1T_CFG3_MODE_BC,
    _1895VA1T_CFG3_MODE_MT,
    _1895VA1T_CFG3_MODE_RT,
    _1895VA1T_CFG3_MODE_HH
};

//==================================================
// CFG2
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_CFG2_BITS{
    uint16_t SBD        :1; // Separate Bradcast Data
    uint16_t ERMM       :1; // Enhaced RT Memory Management
    uint16_t CSR        :1; // Clear Service Request
    uint16_t L_P_IR     :1; // Level/Puls Interrupt Request
    uint16_t ISAC       :1; // Intrp Status Clear
    uint16_t L_TTOS     :1; // Load Time Tag On Synchronize
    uint16_t C_TTOS     :1; // Clear Time Tag On Synchronize
    uint16_t TT_RSL     :3; // Time Tag Resolution
    uint16_t WBD        :1; // Word Bindery Disable
    uint16_t OID        :1; // Overwrite Invalid Data
    uint16_t RSDBE      :1; // RX SA Double Buffer Enable
    uint16_t BLUTE      :1; // Busy Look Up Table Enable
    uint16_t RP_EN      :1; // RAM Parity Enable
    uint16_t EI         :1; // Enhanced Interrupts
    uint16_t padding    :16;
};

// CFG2 - Регистр конфигурации 2
union _1895VA1T_CFG2_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_CFG2_BITS bits;
};

// Разрешение счетчика времени
enum _1895VA1T_CFG2_TT_RSL_t{
    _1895VA1T_CFG2_TT_RSL_64,
    _1895VA1T_CFG2_TT_RSL_32,
    _1895VA1T_CFG2_TT_RSL_16,
    _1895VA1T_CFG2_TT_RSL_8,
    _1895VA1T_CFG2_TT_RSL_4,
    _1895VA1T_CFG2_TT_RSL_2,
    _1895VA1T_CFG2_TT_RSL_TEST,
    _1895VA1T_CFG2_TT_RSL_EXT_SYNC,
};

//==================================================
// SRR
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_SRR_BITS{
    uint16_t RESET          :1; // Reset
    uint16_t BC_MT_ST       :1; // BC\MT Start 
    uint16_t IR             :1; // Intrp Reset
    uint16_t TT_RST         :1; // Time Tag Reset
    uint16_t TTTC           :1; // Time Tag Test Clock
    uint16_t BC_SOF         :1; // BC Stop On Frame
    uint16_t BT_SOM         :1; // BC\MT Stop On Message
    uint16_t RESERV         :9; // RESERV
    uint16_t padding        :16;
};

// SRR - Регистр запуска\пуска
union _1895VA1T_SRR_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_SRR_BITS bits;
};

//==================================================
// BC_CW
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_BC_CW_BITS{
    uint16_t RT_RT_F        :1; // RT to RT Format
    uint16_t BF             :1; // Broadcast Format
    uint16_t MCF            :1; // Mode Code Format
    uint16_t _1553_A_B_S    :1; // 1553A\B Select
    uint16_t EOM_IE         :1; // EOM Intrp Enable
    uint16_t MBB            :1; // Mask Broadcast Bit
    uint16_t OLST           :1; // Off Line Self Test
    uint16_t BC_A_B         :1; // Bus Chanal A\B
    uint16_t CW_RE          :1; // Retry Enable
    uint16_t RBM            :1; // Reserved Bit Mask
    uint16_t TFBM           :1; // Terminal Flag Bit Mask
    uint16_t SFBM           :1; // Subsys Flag Bit Mask
    uint16_t SBBM           :1; // Subsys Busy Bit Mask
    uint16_t SRBM           :1; // Service Request Bit Mask
    uint16_t MEM            :1; // Message Error Mask
    uint16_t RESERV         :1; // RESERV
    uint16_t padding        :16;
};

// BC_CW - Регистр слова управления сообщения КШ
union _1895VA1T_BC_CW_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_BC_CW_BITS bits;
};

//==================================================
// RT_CW
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_RT_CW_BITS{
    uint16_t BCST_MM        :3; // BCST MEM Management
    uint16_t BSCT_CBI_I     :1; // BCST Circ Buf Intrp
    uint16_t BSCT_EOM_I     :1; // BCST EOM Intrp
    uint16_t RX_MM          :3; // RX MEM Management
    uint16_t RX_CBI         :1; // RX Circ Buf Intrp
    uint16_t RX_EOM_I       :1; // RX EOM Intrp
    uint16_t TX_MM          :3; // TX MEM Management
    uint16_t TX_CBI         :1; // TX Circ Buf Intrp
    uint16_t TX_EOM_I       :1; // TX EOM Intrp
    uint16_t RX_DBE         :1; // RX Doube Buffer Enable
    uint16_t padding        :16;
};

// RT_CW - Регистр слова управления сообщения ОУ
union _1895VA1T_RT_CW_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_RT_CW_BITS bits;
};

//==================================================
// ISR
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_ISR_BITS{
    uint16_t EOM        :1; // End of Message
    uint16_t SS_MC_PT   :1; // Status Set\Mode Code\Pattern Trigger
    uint16_t FE         :1; // Format Error
    uint16_t BC_EOF     :1; // BC End Of Frame
    uint16_t SCW_E      :1; // RT Subaddres Cotrol Word EOM\BC Selective EOM
    uint16_t RT_CBR     :1; // RT Circular Buffer Rollover
    uint16_t TT_ROL     :1; // Time Tag Rollover
    uint16_t RT_APE     :1; // RT Address Parity Error
    uint16_t BC_R       :1; // BC Retry
    uint16_t HF         :1; // Hadnshake Failure
    uint16_t MT_DSR     :1; // MT Data Stack Rollover
    uint16_t MT_CSR     :1; // MT Command Stack Rollover
    uint16_t BT_CSR     :1; // BC\RT Command Stack Rollover
    uint16_t BT_TT      :1; // BC\RT Transmiter Timeout
    uint16_t RP_ER      :1; // RAM Parity Error
    uint16_t MI         :1; // Master Intrp
    uint16_t padding    :16;
};

// ISR - Регистр состояния прерываний 
union _1895VA1T_ISR_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_ISR_BITS bits;
};

//==================================================
// CFG3
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_CFG3_BITS{
    uint16_t EMCH       :1; // Enhanced Mode Code Handling
    uint16_t _1553A_MCE :1; // 1553 Mode Code Enable
    uint16_t RT_F_WE    :1; // RT Fail\Flag Wrap Enable
    uint16_t B_RX_TD    :1; // Busy Rx transfer Disable
    uint16_t I_RX_TD    :1; // Illegal RX transfer Disable
    uint16_t ASWE       :1; // Alternate Status Word Enable
    uint16_t OME        :1; // Override Mode T\R Error
    uint16_t ID         :1; // Illegalization Disable
    uint16_t MT_DSZ     :3; // MT Data Stack Size
    uint16_t MT_CSZ     :2; // MT Command Stakc Size
    uint16_t BT_CSZ     :2; // BC\RT Command Stack Size
    uint16_t EME        :1; // Enhanced Mode Enable
    uint16_t padding    :16;
};

// CFG3 - Регистр конфигурации 3
union _1895VA1T_CFG3_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_CFG3_BITS bits;
};

//==================================================
// CFG4
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_CFG4_BITS{
    uint16_t TM             :3; // Test Mode
    uint16_t L_RT_AWCR5     :1; // Latch RT Addr With Confg Reg 5
    uint16_t MTGO           :1; // MT TAG GAP Option
    uint16_t V_B_ND         :1; // Valid Busy\No Data
    uint16_t V_ME_ND        :1; // Valid ME\No Data
    uint16_t _2R_ASB        :1; // Second Retry Alt\Same Bus
    uint16_t _1R_ASB        :1; // First Retry Alt\Same Bus
    uint16_t RI_SS          :1; // Retry If Status Set
    uint16_t RI_AAME        :1; // Retry if 1553A And ME
    uint16_t BM_EX          :1; // Broadcast Mask ENA\XOr
    uint16_t E_BC_CWE       :1; // Expanded BC Control Word Enable
    uint16_t MCOB           :1; // Mode Cobe Override Busy
    uint16_t IBWIB          :1; // Inhibit Bit Word If Busy
    uint16_t EBWE           :1; // External Bit Word Enable
    uint16_t padding        :16;
};

// CFG4 - Регистр конфигурации 4
union _1895VA1T_CFG4_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_CFG4_BITS bits;
};

//==================================================
// CFG5
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_CFG5_BITS{
    uint16_t RT_A_P     :1; // RT Address Parity
    uint16_t RT_A       :5; // RT Address
    uint16_t RT_AL_T    :1; // RT Address Latch
    uint16_t BD         :1; // Broadcast Disable
    uint16_t GCE        :1; // Gap Check Enable
    uint16_t RTS        :2; // Response Time Out Select
    uint16_t ECE        :1; // Expanded Crossing Enabled
    uint16_t E_TX_IB    :1; // Extrenal TX Inhibit A
    uint16_t E_TX_IA    :1; // Extrenal TX Inhibit B
    uint16_t SES        :1; // Single Ended Select
    uint16_t _12MHZ     :1; // 12 Clock Enable
    uint16_t padding    :16;
};

// CFG5 - Регистр конфигурации 5
union _1895VA1T_CFG5_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_CFG5_BITS bits;
};

//==================================================
// RT_SW
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_RT_SW_BITS{
    uint16_t TF         :1; // Terminal Flag
    uint16_t S_DBCA     :1; // Dynamic Bus Control Accept
    uint16_t S_SF       :1; // Subsystem Flag
    uint16_t BUSY       :1; // Busy
    uint16_t BCR        :1; // Bradcast Commnad Recived
    uint16_t RESERV1    :1; // -
    uint16_t RESERV2    :1; // -
    uint16_t RESERV3    :1; // -
    uint16_t S_SR       :1; // Service Request
    uint16_t INSTR      :1; // Instrumentation
    uint16_t ME         :1; // Message Error
    uint16_t RESERV4    :5; // -
    uint16_t padding    :16;
};

// RT_SW - Регистр ответного слова
union _1895VA1T_RT_SW_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_RT_SW_BITS bits;
};

//==================================================
// RT_BIT_W
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_RT_BIT_W_BITS{
    uint16_t CWCE           :1; // Comand Word Contents Error
    uint16_t RT_2CWE        :1; // RT-RT 2nd Command Error
    uint16_t RTG_S_AE       :1; // RT-RT No Respons Error
    uint16_t INV_DW         :1; // RT-RT Gap\Sync\Address Error
    uint16_t INC_SYN_REC    :1; // Incorrect Sync Type Received
    uint16_t LWC            :1; // Low Word Count
    uint16_t HWC            :1; // High Word Count
    uint16_t C_B_A          :1; // Channel A\B
    uint16_t TFI            :1; // Terminal Flag Inhibit
    uint16_t TSB            :1; // Transmitter Shutdown B
    uint16_t TSA            :1; // Transmitter Shutdown A
    uint16_t HF             :1; // Handshake Failure
    uint16_t LTFA           :1; // Loop Test Failure A
    uint16_t LTFB           :1; // Loop Test Failure B
    uint16_t TT             :1; // Transmitter Timeout
    uint16_t padding        :16;
};

// RT_BIT_W - Слово Встроенного Теста ОУ
union _1895VA1T_RT_BIT_W_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_RT_BIT_W_BITS bits;
};

//==================================================
// CFG6
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_CFG6_BITS{
    uint16_t RESERV1    :13; // -
    uint16_t ICOE       :1; // Incriment SCP On EOM
    uint16_t ECA        :1; // Enhanced CPU Access
    uint16_t RESERV2    :1; // -
    uint16_t padding    :16;
};

// CFG6 - Регистр конфигурации 6
union _1895VA1T_CFG6_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_CFG6_BITS bits;
};

//==================================================
// STATE_WORD_BLOCK
//==================================================

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_STATE_WORD_BLOCK_RT_BITS{
    uint16_t CWCE       :1; // Command Word Content Error
    uint16_t RT_2CWE    :1; // RT-RT 2nd Command error
    uint16_t RTG_S_AE   :1; // RT-RT GAP/Sync/Address Error
    uint16_t IW         :1; // Invalid Word
    uint16_t IDS        :1; // Incorrect Data Sync
    uint16_t WCE        :1; // Word Count Error
    uint16_t ICW        :1; // Illegal Command Error
    uint16_t CBR        :1; // Circular Buffer Rollover
    uint16_t LTF        :1; // Loop Test Fail
    uint16_t RTO        :1; // Response Time Out
    uint16_t FE         :1; // Format Error
    uint16_t RT_RT_F    :1; // RT-to-RT Format
    uint16_t EF         :1; // Error Flag
    uint16_t CH_A_B     :1; // Channel A/B
    uint16_t SOM        :1; // Start Of Message
    uint16_t EOM        :1; // End Of Message
    uint16_t padding    :16;
};

// bits  description
struct __attribute__((packed,aligned(4))) _1895VA1T_STATE_WORD_BLOCK_BC_BITS{
    uint16_t IW         :1; // Invalid Word
    uint16_t IST        :1; // Incorrect Sync Type
    uint16_t WCE        :1; // Wrong Count Error
    uint16_t WCA_NG     :1; // Wrong Status Address
    uint16_t GDBT       :1; // Good Data Block Transfer
    uint16_t RE_CO      :2; // Retry Count
    uint16_t MSS        :1; // Masked Status Set
    uint16_t LTF        :1; // Loop Test Fail
    uint16_t RTO        :1; // Response Time Out
    uint16_t FE         :1; // Format Error
    uint16_t SS         :1; // Status Set
    uint16_t EF         :1; // Error Flag
    uint16_t CH_A_B     :1; // Channel A/B
    uint16_t SOM        :1; // Start Of Message
    uint16_t EOM        :1; // End Of Message
    uint16_t padding    :16;
};

// STATE_WORD_BLOCK - Слово состояние блока сообщения
union _1895VA1T_STATE_WORD_BLOCK_REG
{
    uint16_t word;
    uint32_t data;
    struct _1895VA1T_STATE_WORD_BLOCK_RT_BITS   bits_rt;
    struct _1895VA1T_STATE_WORD_BLOCK_BC_BITS   bits_bc;
};

//==============================================================================
// 1895VA1T структура
//==============================================================================
typedef volatile struct 
{
    union _1895VA1T_IMR_REG     IMR;     // Регистр максирования прерываний
    union _1895VA1T_CFG1_REG    CFG1;    // Первый конфигурационный регистр
    union _1895VA1T_CFG2_REG    CFG2;    // Второй конфигурационный регистр
    union
    {
        union _1895VA1T_SRR_REG     SRR;    // Запись    
        union _1895VA1T_DATA_REG    CSP;    // Чтение
    };
    union
    {
        union _1895VA1T_BC_CW_REG   BC_CW;  // Режим КШ
        union _1895VA1T_RT_CW_REG   RT_CW;  // Режим ОУ
    };
    union _1895VA1T_DATA_REG        TT_REG;             // Регистр счетчика метки времени
    union _1895VA1T_ISR_REG         ISR;                // Регистр состояния прерывания
    union _1895VA1T_CFG3_REG        CFG3;               // Третий конфигурационный регистр
    union _1895VA1T_CFG4_REG        CFG4;               // Четвертый конфигурационный регистр
    union _1895VA1T_CFG5_REG        CFG5;               // Пятый конфигурационный регистр
    union _1895VA1T_DATA_REG        RM_DSA;             // Регистр указателя буфера данных
    union _1895VA1T_DATA_REG        BC_FTR;             // Регистр остатка времени кадра КШ
    union _1895VA1T_DATA_REG        BC_TRNM;            // Регистр остатка текущего сообщения КШ
    union _1895VA1T_DATA_REG        BCFT_RTLC_MTTW;     // Регистр длительности кадра КШ\Командного слова ОУ\Слова срабатывания
    union _1895VA1T_RT_SW_REG       RT_SW;              // Регистр ответного слова
    union _1895VA1T_RT_BIT_W_REG    RT_BIT_W;           // Регистр ВСК
    union _1895VA1T_DATA_REG        NOTHING[8];         // -
    union _1895VA1T_CFG6_REG        CFG6;               // Шестой конфигурационный регистр
} _1895VA1T_REGS_TYPE;

//==================================================
//	Макросы
//==================================================

#define _h1895VA1T_RegisterVrtlAddr(Y, X)  (Y = ((X) & 0xffff0000))

//==============================================================================
// 1895VA1T Структура Стека
//==============================================================================
typedef volatile struct
{
    union _1895VA1T_STATE_WORD_BLOCK_REG    WORD_OF_MESSAGE;    // Слово состояния блока сообщения
    union _1895VA1T_DATA_REG                TIME_TAG;           // Слово метки времени
    union _1895VA1T_BLOCK_DATA              *PTR_DATA_WORD;     // Указатель на блок данных
    union _1895VA1T_DATA_REG                COMMAND_WORD;       // Полученное командное слово
} _1895VA1T_FRAME_STACK_TYPE;

//==============================================================================
// 1895VA1T Структура Памяти - Расширенный режим
//==============================================================================
typedef volatile struct
{
    _1895VA1T_FRAME_STACK_TYPE  COMMAND_STACK_A[64];       // Стэк команд области А
    _1895VA1T_FRAME_STACK_TYPE  *PTR_COMMAND_STACK_A;      // Указатель на стэк команд А
    union _1895VA1T_DATA_REG    NONE1[3];                  // -
    _1895VA1T_FRAME_STACK_TYPE  *PTR_COMMAND_STACK_B;      // Указатель на стэк команд B
    union _1895VA1T_DATA_REG    NONE2[3];                  // -
    union _1895VA1T_DATA_REG    TLB_INTRP_SELECT_WORD[8];  // Таблица прерываний для избранных
    union _1895VA1T_DATA_REG    TLB_DATA_SELECT_WORD[48];  // Таблица данных для избранных
    union _1895VA1T_DATA_REG    TLB_SUBADR_RX_RT_A[32];    // Поискова таблица для подадресов А rx
    union _1895VA1T_DATA_REG    TLB_SUBADR_TX_RT_A[32];    // Поискова таблица для подадресов А tx
    union _1895VA1T_DATA_REG    TLB_SUBADR_BCST_RT_A[32];  // Поискова таблица для подадресов А bcst
    union _1895VA1T_DATA_REG    TLB_SUBADR_SACW_RT_A[32];  // Поискова таблица для подадресов А sacw
    union _1895VA1T_DATA_REG    TLB_SUBADR_RX_RT_B[32];    // Поискова таблица для подадресов B rx
    union _1895VA1T_DATA_REG    TLB_SUBADR_TX_RT_B[32];    // Поискова таблица для подадресов B tx
    union _1895VA1T_DATA_REG    TLB_SUBADR_BCST_RT_B[32];  // Поискова таблица для подадресов B bcst
    union _1895VA1T_DATA_REG    TLB_SUBADR_SACW_RT_B[32];  // Поискова таблица для подадресов B sacw
    union _1895VA1T_DATA_REG    TLB_SUBADR_BUSY[8];        // Таблица занятости
    union _1895VA1T_DATA_REG    NONE3[24];                 // -
    union _1895VA1T_BLOCK_DATA  RAM_BLK_DATA_S[5];         // Блоки данных
    union _1895VA1T_DATA_REG    TLB_SUBADR_ILLEGAL[256];   // Таблица допустимости
    union _1895VA1T_BLOCK_DATA  RAM_BLK_DATA_L[96];        // Блоки данных
} _1895VA1T_MEMORY_RT_TYPE;

#define _h1895VA1T_RegisterVrtlAddr_mem(Y, X)  (Y = (((X) & 0xffff0000) + 0x40000))

//==============================================================================
// Слово определения допустиомсти КС
//==============================================================================

#define _h1895VA1T_index_illegal_tlb(OWNADDR, TX, SA, WC4) (((OWNADDR & 0x1) << 7) |   \
                                                            ((TX & 0x1) << 6) |        \
                                                            ((SA & 0x1f) << 1) |       \
                                                            ((WC4) & 0x1))

//==============================================================================
// Слово определения допустиомсти КС
//==============================================================================

#define _h1895VA1T_index_busy_tlb(OWNADDR, TX, SA, WC4) (((OWNADDR & 0x1) << 2) |   \
                                                            ((TX & 0x1) << 1) |     \
                                                            ((SA4) & 0x1))

//==============================================================================
// Перевод внутреннего аддреса во внешний
//==============================================================================

#define _TO_H1895VA1T_ADDR(__ADDR__)    (((__ADDR__) >> 2) & 0xffff)

//==============================================================================
// Перевод внешнего аддреса во внутренний
//==============================================================================

#define _FROM_H1895VA1T_ADDR(__ADDR__, __DEVICE__)  ((((__ADDR__) & 0xffff) << 2) + \
                                                    ((uint32_t)(__DEVICE__)->ram))

//==============================================================================
// Структура обращения к устрйству
//==============================================================================

typedef struct {
    _1895VA1T_REGS_TYPE         *regs;
    _1895VA1T_MEMORY_RT_TYPE    *ram;
} DEVICE_1895VA1T;

//==============================================================================
// Объявление функций
//==============================================================================

/* Function to init device 
    @param device (DEVICE_1895VA1T *) ptr of device struct
    @param vaddr (uint32_t) device addr in system
    */
void device_1895va1t_init(DEVICE_1895VA1T * device, uint32_t vaddr);

/* Deinit device 1895va1t
    @param device (DEVICE_1895VA1T *) ptr of device struct
 */
void device_1895va1t_deinit(DEVICE_1895VA1T * device);

/* Handler for device 1895va1t
    @param device (DEVICE_1895VA1T *) ptr of device struct
 */
void device_1895va1t_itrp_hdlr(DEVICE_1895VA1T * device);

/* Function to put data in correct cells
    @param device (DEVICE_1895VA1T *)   ptr of device struct;
    @param msg_t (_1895VA1T_MSG_t)      msg type;
    @param sub_addr (uint16_t)          sub addr of RT device;
    @param size_data (uint16_t)         size of data;
    @param *ptr_data (uint16_t)         ptr to data;
    @return _1895VA1T_CONDITION_t - status of operation;
 */
_1895VA1T_CONDITION_t device_1895va1t_put_data(DEVICE_1895VA1T * device,
                                                _1895VA1T_MSG_t msg_t, 
                                                uint16_t sub_addr, 
                                                uint16_t size_data, 
                                                uint16_t *ptr_data);

/* Function for drop data from device ram to array
    @param device (DEVICE_1895VA1T *)   ptr of device struct;
    @param msg_t (_1895VA1T_MSG_t)      msg type;
    @param sub_addr (uint16_t)          sub addr of RT device;
    @param size_data (uint16_t)         size of data;
    @param *ptr_data (uint16_t)         ptr to data;
    @return _1895VA1T_CONDITION_t - status of operation;
 */
_1895VA1T_CONDITION_t device_1895va1t_get_data(DEVICE_1895VA1T * device,
                                                _1895VA1T_MSG_t msg_t, 
                                                uint16_t sub_addr, 
                                                uint16_t size_data, 
                                                uint16_t *ptr_data);


#endif //__1895VA1T_H
