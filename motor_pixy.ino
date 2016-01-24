#include <SPI.h>  
#include <Pixy.h>
#include <AFMotor.h>

AF_DCMotor motor(1, MOTOR12_2KHZ); // create motor #1, 2KHz pwm
AF_DCMotor motor2(2, MOTOR12_2KHZ); // Steering motor

Pixy pixy; // This is the main Pixy object 

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");
 
  motor2.setSpeed(200);
  motor2.run(FORWARD);    // FORWARD = left, RELEASE = none, BACKWARD = right
  delay(1000);
  motor2.run(BACKWARD);    // FORWARD = left, RELEASE = none, BACKWARD = right
  delay(1000);
  motor2.run(RELEASE);
/*
 // Start up motor
  motor.setSpeed(250);     // 150 = slow, 200 = medium, 250 = fast 
  motor.run(FORWARD);      // turn it on going forward
  delay(1000);
  */
  Serial.print("before pixy.init\n");
  pixy.init();

  Serial.print("after pixy.init\n");
// Steering Testing
 // motor2.setSpeed(200);
  //motor2.run(RELEASE);    // FORWARD = left, RELEASE = none, BACKWARD = right
}

void loop() //assume that this runs every (1 + small amount) seconds
{ 
  
  static int i = 0, index = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%5==0)
    {
      Serial.print("loop entered\n");
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        //Serial.print(buf); 
        pixy.blocks[j].print();
        
        if(pixy.blocks[j].x > 0 && pixy.blocks[j].x < 132)
        {
          //left steering = FORWARD on motor 2 
          Serial.print("turn left\n");
          motor2.run(FORWARD); 
        }
        else if (pixy.blocks[j].x > 188 && pixy.blocks[j].x < 320)
        {
          //right steering
          Serial.print("turn right\n");
          motor2.run(BACKWARD);
        }
        else
        {
          Serial.print("turn straight\n");
          motor2.run(RELEASE);
        }
        
        
      } //rof
      
        
    } //fi

    
  } //fi block
  
  /*
  // camera threshold box = 56 x 35
  if(pixy.blocks[index].width > 56 && pixy.blocks[index].height > 32)
  {
    //set to slower speed
    motor.setSpeed(150); 
  }
  else if(pixy.blocks[index].width < 56 && pixy.blocks[index].height < 32)
  {
    //set to faster speed
    motor.setSpeed(250); 
  }
  */


  


} //eof void
