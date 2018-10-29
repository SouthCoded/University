
#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header
#include "simulator.h"

int turn;                                  

void right_turn(){
  
  drive_goto(25,-25); //Turn right angle

}

void left_turn(){
  
  drive_goto(-25,25); //Turn left angle

}
void inRange(){
  while(ping_cm(8) > 10){
    drive_ramp(ping_cm(8),ping_cm(8));
  }
  while(ping_cm(8) < 12){
    drive_ramp(-ping_cm(8),-ping_cm(8));
  }
}

int main()                                   
{
  drive_setRampStep(10);  
  int irLeft, irRight;
  int last_turn = 0;

  simulator_startNewSmokeTrail();
  
   while(1){

    freqout(11, 1, 38000);                      
    irLeft = input(10);

    freqout(1, 1, 38000);
    irRight = input(2);

    if(irRight == 1 && irLeft == 1)             
      while(irRight == 1 || irLeft == 1){
        if(last_turn == 1){
          drive_goto(2,-2);
        }
        else{
          drive_goto(-2,2);
        }
      }                 

    else if((irLeft == 0 && ping_cm(8) < 8) || (irRight == 0 && ping_cm(8) < 8)){
      while(ping_cm(8) < 5){
        drive_ramp(-ping_cm(8),-ping_cm(8));
      }
      break;
    }

    else if(irLeft == 0 && irRight == 0 && ping_cm(8) > 25)        
      drive_rampStep(15, 15);               
    
    else if(irRight == 0){
      last_turn = 1;
      simulator_stopSmokeTrail();
      right_turn();
      inRange();
      left_turn();
      simulator_startNewSmokeTrail();
      drive_ramp(15,15);
    }                  
    else if(irLeft == 0){        
      last_turn = 2;
      simulator_stopSmokeTrail();             
      left_turn();
      inRange();
      right_turn();
      simulator_startNewSmokeTrail();
      drive_ramp(15,15);
    }    
    

    sleep(1);

  }  
              
}
