

/**
 * main.c
 */
/*
 *
 *
 * Below program demonstrates the usage timer_driver
 * Initially red led will blink for 10 times and then stops blinking. It will remain lit.
 *
 *
 * CREATED BY SIVAKRISHNA(EPD MTECH IISC BENGALORE)
 * Total 12 timer peripherals
 * (6 16/32 timers and 6 32/64 timers)
 * we can use 6 16/32 timers as two 16 bit timers(TIMERA and TIMER B). Same applies for 32/64 timers

 * modes:
 * 1. periodic
 * 2. One shot mode
 *
 * Counting Modes:
 * 1. Up
 * 2. Down
 *
 * Initialisation
 *
 * -> Enable clock for TIMER
 * -> Disable timer
 * -> Select Timer resolution(16/32 or 32/64)
 * -> Select Timer Mode(one shot or periodic  and up or down counting)
 * -> Set interval load register value
 * -> Clear Timeout Flag
 * -> Enable the Timer
 * -> Wait for the timeout flag to set the interrupt
 *
 *
 *  */
/*
 * this driver mainly implements 3 apis for the user
 * 1. init_timer()
 * 2. start_timer()
 * 3. stop_timer()
 *
 *///************** USAGE *************///
/*
 * 1-> Declare a variable to structure timer_handle_t
 * 2-> Assign required parameters like reolution of timer(Timer A or Timer B), Type of timer(Normal or Wide Timer)
 *     , Counting Mode(Up or Down) and Timer Mode(One shot or Periodic)
 * 3-> Pass the address of the structure variable to timer_init function.
 * 4-> And then activate the interrupt for the timer according to the datasheet(for ex TIMER1A has 21 as NVIC interrupt Number).
 * 5-> Call the start_timer function with handle address as parameter.
 * 6-> U need to define a timer handler in the main function and the function should be kept in the isr vector
 * 6-> Clear the ICR register's Interrupt bit in Timer_handler
 * 7-> We can use timer_Stop function to disable the timer.
 */




#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "drv_timer.h"
#include <stdbool.h>

volatile bool flag = 0;
volatile int cnt = 0;
volatile int timer_cnt = 0;

void init_gpio(void);

void TIMER1A_HANDLER(void)
{
    if(TIMER1_MIS_R & 0x01)
    {
        cnt++;
        if(cnt >100)
        {
        flag = (!flag);
        timer_cnt++;
        cnt =0;
        }
TIMER1_ICR_R |= 1<<0;
    }
}

timer_handle_t TIMER_x1;

int main(void)
{
    TIMER_x1.config.counter_mode = COUNTER_MODE_UP;
    TIMER_x1.reg = TIMER_1;
    TIMER_x1.config.timer_mode = TIMER_MODE_PERIODIC;
    TIMER_x1.config.resolution = TIMER_RES_A;
    TIMER_x1.config.load_value = 32000;

        timer_init(&TIMER_x1);
        timer_start(&TIMER_x1);
        NVIC_EN0_R |= 0X200000;  // NVIC interrupt 21(FOR TIMER1A)  USER NEED TO ENABLE PARTICULAR REG ON HIS OWN

        init_gpio();
        while(1)
        {
            if(flag)
            {
                GPIO_PORTF_DATA_R |= (1<<1);
                if(timer_cnt >10)
                {
                    timer_disable(&TIMER_x1);
                }
            }
            else
                GPIO_PORTF_DATA_R &= ~(1<<1);
        }
        return 0;
}



void init_gpio(void)
{
    SYSCTL_RCGCGPIO_R |= 1<<5;
    GPIO_PORTF_DEN_R |= 1<<1;
    GPIO_PORTF_DIR_R |= 1<<1;
    GPIO_PORTF_DATA_R &= ~(1<<1);
}


