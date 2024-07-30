/*
 * drv_timer.c
 *
 *  Created on: 27-Jul-2024
 *      Author: basat
 */

#include "drv_timer.h"

void timer_clk_enable(timer_regs_t* timerx)
{
//    WRITE_TO_REG_BIT(RCGCTIMER, 1, 1);

if(timerx == TIMER_0)
{
    WRITE_TO_REG_BIT(RCGCTIMER, 0, 1);
}
else if (timerx == TIMER_1)
{
    WRITE_TO_REG_BIT(RCGCTIMER, 1, 1);

}
else if (timerx == TIMER_2)
{
    WRITE_TO_REG_BIT(RCGCTIMER, 2, 1);

}
else if (timerx == TIMER_3)
{
    WRITE_TO_REG_BIT(RCGCTIMER, 3, 1);

}
else if (timerx == TIMER_4)
{
    WRITE_TO_REG_BIT(RCGCTIMER, 4, 1);

}
else if (timerx == TIMER_5)
{
    WRITE_TO_REG_BIT(RCGCTIMER, 5, 1);

}
else if (timerx == WTIMER_0)
{
    WRITE_TO_REG_BIT(RCGCWTIMER, 0, 1);

}
else if (timerx == WTIMER_1)
{
    WRITE_TO_REG_BIT(RCGCWTIMER, 1, 1);

}
else if (timerx == WTIMER_2)
{
    WRITE_TO_REG_BIT(RCGCTIMER, 2, 1);

}
else if (timerx == WTIMER_3)
{
    WRITE_TO_REG_BIT(RCGCWTIMER, 3, 1);

}
else if (timerx == TIMER_4)
{
    WRITE_TO_REG_BIT(RCGCWTIMER, 4, 1);

}
else if (timerx == TIMER_5)
{
    WRITE_TO_REG_BIT(RCGCWTIMER, 5, 1);

}
else
{
// return error;
}

}

void timer_disable(timer_handle_t* timer_handle)
{
    if(timer_handle->config.resolution == TIMER_RES_A)
        timer_handle->reg->GPTMCTL &= ~( 1<<0);
    else if(timer_handle->config.resolution == TIMER_RES_B)
        timer_handle->reg->GPTMCTL &= ~(1<<8);
    else
        timer_handle->reg->GPTMCTL &= ~((1<<8) | (1<<0)); //both a and b willbe disabled



}

void timer_enable(timer_handle_t* timer_handle)   //enable timer
{
    if(timer_handle->config.resolution == TIMER_RES_A)
        timer_handle->reg->GPTMCTL |= ( 1<<0);
    else if(timer_handle->config.resolution == TIMER_RES_B)
        timer_handle->reg->GPTMCTL |= (1<<8);
    else
        timer_handle->reg->GPTMCTL |= ((1<<8) | (1<<0)); //both a and b willbe enabled
}


void timer_resol_sel(timer_handle_t* timer_handle)
{
    if(timer_handle->config.resolution == TIMER_RES_A || timer_handle->config.resolution == TIMER_RES_B)
    {
        timer_handle->reg->GPTMCFG = 0x04; //16 bit for normal timer and 32 bit for wide timer
    }
    else
        timer_handle->reg->GPTMCFG = 0x00; //32 bit for normal timer and 64 bit for wide timer

}


void timer_mode_and_load(timer_handle_t* timer_handle)
{
    if(timer_handle->config.resolution == TIMER_RES_A)
    {
        timer_handle->reg->GPTMTAMR |= ((timer_handle->config.timer_mode));
        timer_handle->reg->GPTMTAMR |= ((timer_handle->config.counter_mode)<<4);

        /*
         * GPTM Timer A Mode
The TAMR values are defined as follows:
Value Description
0x0 Reserved
0x1 One-Shot Timer mode
0x2 Periodic Timer mode
0x3 Capture mode
         */
//        timer_handle->reg->GPTMTAMR |= 0x02;
//        timer_handle->reg->GPTMTAILR = timer_handle->config.load_value;
        timer_handle->reg->GPTMTAILR = timer_handle->config.load_value;

    }
    else if(timer_handle->config.resolution == TIMER_RES_B)
    {
        timer_handle->reg->GPTMTBMR |= ((timer_handle->config.timer_mode));
        timer_handle->reg->GPTMTBMR |= ((timer_handle->config.counter_mode)<<4);
        timer_handle->reg->GPTMTBILR = timer_handle->config.load_value;
    }
    else
    {
            // FOR NOW LEAVE THIS PART
        timer_handle->reg->GPTMTAILR = timer_handle->config.load_value;
    }

}

void timer_clear_int(timer_handle_t* timer_handle){
    if(timer_handle->config.resolution == TIMER_RES_A)
    timer_handle->reg->GPTMICR &= ~(1<<1);

    else if(timer_handle->config.resolution == TIMER_RES_B)
    timer_handle->reg->GPTMICR &= ~(1<<9);

    else{
        //leave it for now
    }
}


void timer_mask_int(timer_handle_t* timer_handle){
    if(timer_handle->config.resolution == TIMER_RES_A)
        timer_handle->reg->GPTMIMR |= (1<<0);
    else
        timer_handle->reg->GPTMIMR |= (1<<8);

}


void timer_init(timer_handle_t* timer){



    timer_clk_enable(timer->reg);

    timer_disable(timer);   //disable timera and timerb for noe

    timer_resol_sel(timer);  // select the resolution 16/32 and 32/64

    timer_mode_and_load(timer);     // select periodic or one shot and up or down and load with the value

    timer_clear_int(timer);


    timer_mask_int(timer);

}



void timer_start(timer_handle_t* timer){
    timer_enable(timer);

}

void timer_stop(timer_handle_t* timer){
    timer_disable(timer);
}


