
/*
 * drv_timer.h
 *
 *  Created on: 27-Jul-2024
 *      Author: basat
 */

#ifndef DRV_TIMER_H_
#define DRV_TIMER_H_

#include <stdint.h>
/*
 * timer_init()
 * timer_start()
 * timer_stop()
 * timer_enable()
 * timer_disable()
 *
 */

/*
16/32-bit Timer 0: 0x40030000
16/32-bit Timer 1: 0x40031000
16/32-bit Timer 2: 0x40032000
16/32-bit Timer 3: 0x40033000
16/32-bit Timer 4: 0x40034000
16/32-bit Timer 5: 0x40035000

32/64-bit Wide Timer 0: 0x4003.6000
32/64-bit Wide Timer 1: 0x4003.7000
32/64-bit Wide Timer 2: 0x4004.C000
32/64-bit Wide Timer 3: 0x4004.D000
32/64-bit Wide Timer 4: 0x4004.E000
32/64-bit Wide Timer 5: 0x4004.F000
 *
 */
#define TIMER_0_BASE_ADDRESS (0x40030000)
#define TIMER_1_BASE_ADDRESS (0x40031000)
#define TIMER_2_BASE_ADDRESS (0x40032000)
#define TIMER_3_BASE_ADDRESS (0x40033000)
#define TIMER_4_BASE_ADDRESS (0x40034000)
#define TIMER_5_BASE_ADDRESS (0x40035000)

#define WTIMER_0_BASE_ADDRESS (0x40036000)
#define WTIMER_1_BASE_ADDRESS (0x40037000)
#define WTIMER_2_BASE_ADDRESS (0x4003C000)
#define WTIMER_3_BASE_ADDRESS (0x4003D000)
#define WTIMER_4_BASE_ADDRESS (0x4003E000)
#define WTIMER_5_BASE_ADDRESS (0x4003F000)

#define TIMER_0 ((timer_regs_t *)TIMER_0_BASE_ADDRESS)
#define TIMER_1 ((timer_regs_t *)TIMER_1_BASE_ADDRESS)
#define TIMER_2 ((timer_regs_t *)TIMER_2_BASE_ADDRESS)
#define TIMER_3 ((timer_regs_t *)TIMER_3_BASE_ADDRESS)
#define TIMER_4 ((timer_regs_t *)TIMER_4_BASE_ADDRESS)
#define TIMER_5 ((timer_regs_t *)TIMER_5_BASE_ADDRESS)

#define WTIMER_0 ((timer_regs_t *)WTIMER_0_BASE_ADDRESS)
#define WTIMER_1 ((timer_regs_t *)WTIMER_1_BASE_ADDRESS)
#define WTIMER_2 ((timer_regs_t *)WTIMER_2_BASE_ADDRESS)
#define WTIMER_3 ((timer_regs_t *)WTIMER_3_BASE_ADDRESS)
#define WTIMER_4 ((timer_regs_t *)WTIMER_4_BASE_ADDRESS)
#define WTIMER_5 ((timer_regs_t *)WTIMER_5_BASE_ADDRESS)

// 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control (RCGCTIMER)
// Base 0x400F.E000
// Offset 0x604

// 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control (RCGCWTIMER)
// Base 0x400F.E000
// Offset 0x65C

#define RCGCTIMER (0x400FE000 + 0x604)
#define RCGCWTIMER (0x400FE000 + 0x65C)

#define TIMER_RES_A 1
#define TIMER_RES_B 2
#define TIMER_RES_BOTH 3

#define TIMER_MODE_ONE_SHOT 1
#define TIMER_MODE_PERIODIC 2

#define COUNTER_MODE_UP 1
#define COUNTER_MODE_DOWN 0

typedef volatile uint32_t vu32_t;

typedef struct timer_regs
{
  vu32_t GPTMCFG;  // RW 0x0000.0000 GPTM Configuration 727
  vu32_t GPTMTAMR; // RW 0x0000.0000 GPTM Timer A Mode 729
  vu32_t GPTMTBMR; // RW 0x0000.0000 GPTM Timer B Mode 733
  vu32_t GPTMCTL;  // RW 0x0000.0000 GPTM Control 737
  vu32_t GPTMSYNC; // RW 0x0000.0000 GPTM Synchronize 741
  vu32_t dummy;
  vu32_t GPTMIMR;      // RW 0x0000.0000 GPTM Interrupt Mask 745
  vu32_t GPTMRIS;      // RO 0x0000.0000 GPTM Raw Interrupt Status 748
  vu32_t GPTMMIS;      // RO 0x0000.0000 GPTM Masked Interrupt Status 751
  vu32_t GPTMICR;      // W1C 0x0000.0000 GPTM Interrupt Clear 754
  vu32_t GPTMTAILR;    // RW 0xFFFF.FFFF GPTM Timer A Interval Load 756
  vu32_t GPTMTBILR;    // RW - GPTM Timer B Interval Load 757
  vu32_t GPTMTAMATCHR; // RW 0xFFFF.FFFF GPTM Timer A Match 758
  vu32_t GPTMTBMATCHR; // RW - GPTM Timer B Match 759
  vu32_t GPTMTAPR;     // RW 0x0000.0000 GPTM Timer A Prescale 760
  vu32_t GPTMTBPR;     // RW 0x0000.0000 GPTM Timer B Prescale 761
  vu32_t GPTMTAPMR;    // RW 0x0000.0000 GPTM TimerA Prescale Match 762
  vu32_t GPTMTBPMR;    // RW 0x0000.0000 GPTM TimerB Prescale Match 763
  vu32_t GPTMTAR;      // RO 0xFFFF.FFFF GPTM Timer A 764
  vu32_t GPTMTBR;      // RO - GPTM Timer B 765
  vu32_t GPTMTAV;      // RW 0xFFFF.FFFF GPTM Timer A Value 766
  vu32_t GPTMTBV;      // RW - GPTM Timer B Value 767
  vu32_t GPTMRTCPD;    // RO 0x0000.7FFF GPTM RTC Predivide 768
  vu32_t GPTMTAPS;     // RO 0x0000.0000 GPTM Timer A Prescale Snapshot 769
  vu32_t GPTMTBPS;     // RO 0x0000.0000 GPTM Timer B Prescale Snapshot 770
  vu32_t GPTMTAPV;     // RO 0x0000.0000 GPTM Timer A Prescale Value 771
  vu32_t GPTMTBPV;     // RO 0x0000.0000 GPTM Timer B Prescale Value 772
  vu32_t GPTMPP;       // RO 0x0000.0000 GPTM Peripheral Properties 773
} timer_regs_t;

typedef struct timer_config
{
  /*
   * resolution(16/32 or 32/64)
   * timer_mode(one shot or periodic)
   * counter_mode(up count or down count)
   * load value
   */

  uint8_t resolution;
  uint8_t timer_mode;
  uint8_t counter_mode;
  uint32_t load_value;

} timer_config_t;

typedef struct timer_handle
{
  timer_regs_t *reg;
  timer_config_t config;
} timer_handle_t;

void timer_init(timer_handle_t *timer);

void timer_start(timer_handle_t *timer);

void timer_stop(timer_handle_t *timer);

void timer_clk_enable(timer_regs_t *timerx);

void timer_disable(timer_handle_t *timer_handle);

void timer_resol_sel(timer_handle_t *timer_handle);

void timer_mode_and_load(timer_handle_t *timer_handle);

void timer_clear_int(timer_handle_t *timer_handle);

void timer_enable(timer_handle_t *timer_handle);

void timer_mask_int(timer_handle_t *timer);

void timer_clear_int(timer_handle_t *timer_handle);



static inline void WRITE_TO_REG_BIT(uint32_t reg_addr, uint8_t bit_pos, uint8_t val)
{
  if (val == 0)
  {
    *(volatile uint32_t *)reg_addr &= ~(1 << bit_pos);
  }
  else
    *(volatile uint32_t *)reg_addr |= (1 << bit_pos);
}

#endif /* DRV_TIMER_H_ */
