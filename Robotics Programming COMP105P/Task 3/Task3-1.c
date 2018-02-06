
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
    int irLeft, irRight,right,left;
    int last_turn = 0;

    simulator_startNewSmokeTrail();
    
     while(1){

      irLeft = 0;
      irRight = 0;

      right = 15;
      left = 15;

      for(int dacVal = 0; dacVal < 160; dacVal += 8)  {                                               
        dac_ctr(26, 0, dacVal);                       
        freqout(11, 1, 38000);                        
        irLeft += input(10);           

        dac_ctr(27, 1, dacVal);                      
        freqout(1, 1, 38000);
        irRight += input(2);                          
      }                      

      if(irLeft < 5){
        //right turn
        int temp = 5 - irLeft;
        left -= (2 * temp);
        right += (2 * temp);
        drive_ramp(right,left);
       }
      
      else if(irLeft > 5){
        // left turn
        int temp = irLeft - 5;
        right -= (2 * temp);
        left += (2 * temp);
        drive_ramp(right,left);
       }
       else{
        right = 20;
        left = 20;
        drive_ramp(right,left);
      }
       

       
     }                       


  }
