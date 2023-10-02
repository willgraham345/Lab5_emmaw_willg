# Activity 1
1. For each of the cases, use an oscilloscope to measure jitter and drift of the time keeping method.
    1. Read through the code, see what it does.
    2. Load the code onto your board (e.g. `pio run -t upload -e sleep`)
    3. Measure the jitter (see instructions below)
    4. Once you are finished, modify the code - introduce a k_busy_wait call after the GPIO is toggled. 1.Busy wait sets the processor in a tight loop (usually a counter loop with a noop body). 1. Measure the jitter with several delay values.
2. Measure the jitter of the Agilent function generator operating at the same frequency for comparison.


# Activity 2
1. Review and run the code `gpio_interrupt.c`
2. Attach the Sync output from the signal generator to the oscilloscope and use as the trigger.
3. Drive the board with the signal generator output on pin A1.
    1. **Make sure to check the output voltages on the oscilloscope before attaching it to your board or you'll let the magic smoke out!** Set amplitude HiLevel to 3.3V, LoLevel to 0.0 V.
4. Measure the delay between the sync signal and the output from the board.
5. Increase the delay using a busy wait loop as before.


# Activity 3
1. Modify the interrupt handler by adding in a message queue.
2. From the interrupt handler send a message.
3. Create a new thread that reads messages from the queue and toggles the output pin when a message is received.
4. Measure the latency again.
5. Add a busy wait delay to the message handler.