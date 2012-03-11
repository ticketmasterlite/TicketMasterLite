/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.4 --- 2/15/2012 21:24:5 PST
*/

#include "rims.h"

unsigned char SM_Clk;
void TimerISR() {
   SM_Clk = 1;
}

enum SM_States { SM_reset, SM_incr, SM_wait, SM_decr } SM_State;

SM_Tick() {
   switch(SM_State) { // Transitions
      case -1:
         SM_State = SM_reset;
         break;
         case SM_reset:
         if (((PINA & 0x01) == 0) && ((PINA & 0x02) == 1)) {
            SM_State = SM_incr;
         }
         else if (((PINA & 0x01) == 1) && ((PINA & 0x02) == 0)) {
            SM_State = SM_decr;
         }
         break;
      case SM_incr:
         if (((PINA & 0x01) == 0) && ((PINA & 0x02) == 1)) {
            SM_State = SM_incr;
         }
         else if (((PINA & 0x01) == 1) && ((PINA & 0x02) == 1)) {
            SM_State = SM_wait;
         }
         else if (((PINA & 0x01) == 0) && ((PINA & 0x02) == 0)) {
            SM_State = SM_reset;
         }
         break;
      case SM_wait:
         if (((PINA & 0x01) == 0) && ((PINA & 0x02) == 1)) {
            SM_State = SM_incr;
         }
         else if (((PINA & 0x01) == 1) && ((PINA & 0x02) == 0)) {
            SM_State = SM_decr;
         }
         else if (((PINA & 0x01) == 0) && ((PINA & 0x02) == 0)) {
            SM_State = SM_reset;
         }
         break;
      case SM_decr:
         if (((PINA & 0x01) == 1) && ((PINA & 0x02) == 0)) {
            SM_State = SM_decr;
         }
         else if (((PINA & 0x01) == 1) && ((PINA & 0x02) == 1)) {
            SM_State = SM_wait;
         }
         else if (((PINA & 0x01) == 0) && ((PINA & 0x02) == 0)) {
            SM_State = SM_reset;
         }
         break;
      default:
         SM_State = SM_reset;
   } // Transitions

   switch(SM_State) { // State actions
      case SM_reset:
         Write7Seg(0);
         PORTC = 0x00;
         break;
      case SM_incr:
         unsigned char disp = PINC;
         if (disp < 9)
         {
         disp++;
         Write7Seg(disp);
         }
         break;
      case SM_wait:
         break;
      case SM_decr:
         unsigned char disp = PINC;
         if (disp >= 9)
         {
         disp++;
         Write7Seg(disp);
         }
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int SM_Period = 1000; // 1000 ms default
   TimerSet(SM_Period);
   TimerOn();
   
   SM_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      SM_Tick();
      while(!SM_Clk);
      SM_Clk = 0;
   } // while (1)
} // Main