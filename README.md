 * Below program demonstrates the usage timer_driver
 * Initially red led will blink for 10 times and then stops blinking. It will remain lit.

*
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
