# Activity 1
1. For each of the cases, use an oscilloscope to measure jitter and drift of the time keeping method.
    1. Read through the code, see what it does.
    2. Load the code onto your board (e.g. `pio run -t upload -e sleep`)
    3. Measure the jitter (see instructions below)
    4. Once you are finished, modify the code - introduce a k_busy_wait call after the GPIO is toggled. 1.Busy wait sets the processor in a tight loop (usually a counter loop with a noop body). 1. Measure the jitter with several delay values.
2. Measure the jitter of the Agilent function generator operating at the same frequency for comparison.



# Activity 2
1. Set source to the appropriate channel
2. Press the "Meas" button.
3. Select "Meas. Place" and select 1 to add a first measurement.
4. Set "Type" to "Period"
5. Set "Statistics" to on (should be blue)
6. Set "Measure X" to on if it isn't.
7. Statistics for current, min, max, mean, stddev, and count should be shown.
8. Select "Meas. Place" and select 2 to add a second measurement.
9. Add another measurement for frequency.
10. Add another measurement for duty cycle.
11. Using these measurements, calculate the drift over a 1 hour period.

busy_wait requires much more power


(sleep call, kernel based functionality), sleep is scheduluer
| Sleep      | Min                 | Max         | Mean        | StdDev     |
| ---------- | ------------------- | ----------- | ----------- | ---------- |
| Period     | 220.36 $\mu$seconds | 220.5102    | 220.455     | 18.814 ns  |
| Frequency  | 4.53498 kHz         | 4.53799 kHz | 4.53616 kHz | 382.58 mHz |
| Duty Cycle | 49.79%              | 49.8%       | 49.79%      | 0%         |

Kernel (kernel timer (software based timer)), sleep is scheduler
| Kernel      | Min                  | Max         | Mean                  | StdDev             |
| ---------- | -------------------- | ----------- | --------------------- | ------------------ |
| Period     | 400.798 microseconds | 400.9636    | 400.8716 microseconds | 29.808 nanoseconds |
| Frequency  | 2.49394 kHz          | 2.49513 kHz | 2.494522 kHz          | 203 mHz            |
| Duty Cycle | 49.89%               | 49.92%      | 49.9%                 | 0%                 | 


# Activity 3

1. To save to a flash drive inserted into the front panel
    1. You can save the complete capture history, though this can be a lot of data. It's easier to capture the current display data.
        1. Set a large display by setting the horizontal scale to 100s
        2. Wait a while.
    2. Stop acquisition with "Run Stop" in the Trigger section
    3. Press "Save Load" in the Action section.
    4. Select "Waveforms" from the touchscreen.
    5. Change "Points" to "Display data"
    6. CSV is a good file format for use with other tools.
2. Transfer files with MTP.
    1. Connect the USB cable from the rear of the scope to your computer.
    2. If you are on a Windows or Linux machine, it should appear as an attached drive.
        1. Apple still refuses to implement MTP in OSX natively. I wasn't able to get OpenMTP working, your mileage may vary.
    3. Data should be "Live Data/Channel/Acquisition Memory"


# Activity 4
1. Review and run the code `gpio_interrupt.c`
2. Attach the Sync output from the signal generator to the oscilloscope and use as the trigger.
3. Drive the board with the signal generator output on pin A1.
    1. **Make sure to check the output voltages on the oscilloscope before attaching it to your board or you'll let the magic smoke out!** Set amplitude HiLevel to 3.3V, LoLevel to 0.0 V.
4. Measure the delay between the sync signal and the output from the board.
5. Increase the delay using a busy wait loop as before.


# Activity 5
1. Modify the interrupt handler by adding in a message queue.
2. From the interrupt handler send a message.
3. Create a new thread that reads messages from the queue and toggles the output pin when a message is received.
4. Measure the latency again.
5. Add a busy wait delay to the message handler.