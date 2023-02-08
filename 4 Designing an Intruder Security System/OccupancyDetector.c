/*
 * OccupancyDetector.c
 *
 *  Created on: Feb 1, 2023
 *      Author: Allison Hagan
 */

#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

// Put some initialization here
void gpioInit();        // Initialize all GPIO pins


char state = ARMED_STATE;

while(1)
{
  switch (state) {
    case ARMED_STATE:
    {
      // Do something in the ARMED state
        if !(P2IN & BIT3)               // If S2 (P2.3) is not pressed
                P6OUT &= ~BIT6;         // Turn on green LED
        if else !(P4IN & BIT1)          // If S1 (P4.1) is not pressed
                P6OUT &= ~BIT6;         // Turn on green LED
        else
            state = WARNING_STATE;      // If either of the buttons are pressed, change state to Warning

      // If something happens, you can move into the WARNING_STATE
      // state = WARNING_STATE
    }
    case WARNING_STATE:
    {
      // Do something in the WARNING_STATE
        if (P2IN & BIT3)                // If S2 (P2.3) is pressed
                P1OUT ^= BIT0;         // Turn on red LED
        if else (P4IN & BIT1)           // If S1 (P4.1) is pressed
                P1OUT ^= BIT0;         // Turn on red LED
        __delay_cycles(100000);         // Delay for 100000*(1/MCLK)=0.1s
    }
  }
}

void gpioInit()
{
   // Setting Directions of Pins

       P1DIR |= BIT0;              // Configure P1.0 to an Output
       P6DIR |= BIT6;              // Configure P6.6 to an Output
       P2DIR &= ~BIT3;             // Configure P2.3 to an Input
       P4DIR &= ~BIT1;             // Configure P4.1 to an Input

       P2REN |= BIT3;               // Enable Resistor on P2.3
       P2OUT |= BIT3;               // Configure Resistor on P2.3 to be Pullup

       P4REN |= BIT1;               // Enable Resistor on P4.1
       P4OUT |= BIT1;               // Configure Resistor on P4.1 to be Pullup
}


