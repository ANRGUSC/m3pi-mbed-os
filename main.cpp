// Copyright (c) 2016, Autonomous Networks Research Group. All rights reserved.
// contributor: Pradipta Ghosh
// read license file in main directory for more details

#include "m3pi.h"
#include "mbed.h"
#include "rtos.h"
#include <string.h>
#include <stdlib.h>  
#include <math.h>
#define PESSIMISTIC 1
#define BASELINE 1
#define MOVEMENT 1
#define INTERVAL 10


Mutex data_mutex; 
Mutex control_mutex; 
static bool start_flag=1;
Thread        *RX_THREAD_POINTER;
Thread        *CONT_THREAD_POINTER;
Thread        *LQG_THREAD_POINTER;
Thread        *RECV_THREAD_POINTER;

m3pi m3pi;


DigitalOut myled(LED1); //to notify when a character was received on mbed
DigitalOut myled2(LED2); //to notify when a character was received on mbed

Serial xbee(p28, p27); //used to connected the mbed to the xbee over Serial UART comm.


char current[32]; //holds the value of the character that was read

float speed = 0.2;
float correction = 0.1;   
float threshold = 0.5;

int delta_t=200; //Movement Granurarity

/* This Function Handles the interrupt from the Xbee*/
void getdata()
{ 
        LPC_UART2->IER = 0;   // Disable Rx interrupt  UART2 is for pin 28,27
        (*RX_THREAD_POINTER).signal_set(0x1); // Send signl to the reading thread 
                                            // rx_thread 
}

/* This is the code for getting instruction from the Xbee receiver*/
void rx_thread(void const *argument){
    
    while (true) 
    {
        myled2=!myled2;
        // Signal flags that are reported as event are automatically cleared.
        Thread::signal_wait(0x1);

        if(xbee.readable()) //Check If there is somethig to read in the serial
        {
            xbee.gets(current,32); // Get the command
        }


        if(current[0]=='w')
        {
            m3pi.forward(speed);
            Thread::wait(delta_t);
            m3pi.stop();
        }    
        else if (current[0]=='a')
        {
            m3pi.left(speed);
            Thread::wait(delta_t);
            m3pi.stop();
        }   
        else if (current[0]=='s')
        {
            m3pi.backward(speed);
            Thread::wait(delta_t);
            m3pi.stop();
        }
        else if (current[0]=='d')
        {
            m3pi.right(speed);
            Thread::wait(delta_t);
            m3pi.stop();
        }
        else
        {
        //   
        }


        /* Re-Enable the Receiver Interrupt */
        LPC_UART2->IER = 1;    
    }
}

int main() 
{
    Thread t_rx(rx_thread); // Thread for Serial-in from Openmote
    RX_THREAD_POINTER = &t_rx; 
    
    void (*fpointer)(void) = &getdata;
    xbee.baud(115200);
    xbee.attach(fpointer,Serial::RxIrq); // RxIrq sets interrupt on reception
    
    m3pi.locate(0,1);
    m3pi.printf("Rmt Control");
    m3pi.sensor_auto_calibrate();


    while (true)
    {
        myled = !myled;
        Thread::wait(300);
    }
}