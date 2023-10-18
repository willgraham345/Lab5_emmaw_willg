#include <zephyr.h>
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#define DEV_IN DT_NODELABEL(gpioa)
#define DEV_OUT DT_NODELABEL(gpioa)
#define PIN_OUT 0
#define PIN_IN 1
#define MY_STACK_SIZE 2000


struct gpio_callback callback;
const struct device *dev_in, *dev_out;

// MESSAGE QUEUE
//Define message queue with data_item_type description
K_MSGQ_DEFINE(msgq, sizeof(int), 4, 2);

// LISTENER
K_THREAD_STACK_DEFINE(listener_stack, MY_STACK_SIZE);
struct k_thread listener_thread;






void pin_interrupt(const struct device *port,
                   struct gpio_callback *cb,
                   gpio_port_pins_t pins_)
{
    //Commented out, left from activity 1
    // Adding a busy wait to test delay increase
    // k_busy_wait(200);
    // gpio_pin_toggle(dev_out, PIN_OUT);

    // Send message 
    //Write one message to the message queue
    int data_item = 1;
    while (k_msgq_put(&msgq, &data_item, K_NO_WAIT) != 0) {
        k_msgq_purge(&msgq); //purges old data if whlie loop conditional doesn't run correctly :)
    } 
}

void listener_thread_entry_point(void){
//TODO: Implement listener thread entry point.
// Should: read message from queue and toggle output pin upon message receive. 
    int int_signal = 0;
    while (1) {
        // Reads the message
        while (k_msgq_get(&msgq, &int_signal, K_FOREVER) != 0){
            // Do nothing
        }
        // Toggle output pin upon message receiving
        gpio_pin_toggle(dev_out, PIN_OUT);

    }
}

void interrupt_main(void)
{
    // Getting pin device from memory
    dev_in = device_get_binding(DT_LABEL(DEV_IN));
    dev_out = device_get_binding(DT_LABEL(DEV_OUT));


    // Set correct input/output pin relationships
    gpio_pin_configure(dev_out, PIN_OUT, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure(dev_in, PIN_IN, GPIO_INPUT);
    // Set input pin to listen to interrupt on rising edge
    gpio_pin_interrupt_configure(dev_in, PIN_IN, GPIO_INT_EDGE_RISING);
    
    // Set the callback to be performed upon rising edge
    gpio_init_callback(&callback, pin_interrupt, 1 << PIN_IN);
    gpio_add_callback(dev_in, &callback);


    // dedicate memory and stack for new thread
    k_thread_create(&listener_thread, listener_stack, MY_STACK_SIZE, (k_thread_entry_t) listener_thread_entry_point, NULL, NULL, NULL, K_PRIO_COOP(7), 0, K_NO_WAIT);


    k_sleep(K_FOREVER);
}