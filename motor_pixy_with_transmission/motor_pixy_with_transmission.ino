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
  //pixy.init();
 
 Serial.print("Steering test\n");
 //STEERING TEST
  motor2.setSpeed(200);
  motor2.run(FORWARD);    // FORWARD = left, RELEASE = none, BACKWARD = right
  delay(1000);
  motor2.run(BACKWARD);    // FORWARD = left, RELEASE = none, BACKWARD = right
  delay(1000);
  motor2.run(RELEASE);

  Serial.print("Transmission Test\n");
  //Start up motor
  //TRANSMISSION TEST (TESTING DIFFERENT SPEEDS)
  motor.setSpeed(250);     // 100 = slow, 200 = medium, 250 = fast 
  motor.run(FORWARD);      // turn it on going forward
  delay(2000);
  motor.setSpeed(100);
  delay(2000);
  motor.setSpeed(70);
  delay(2000);
  motor.setSpeed(150);
  delay(2000);
  motor.run(RELEASE);
  
  Serial.print("before pixy.init\n");
  pixy.init(); //Makes the speed go up.... That is why you don't have control with speed.
  //motor.run(RELEASE);
  Serial.print("after pixy.init\n");
  
   Serial.print("Begin the Loop\n\n");
}
void loop() //assume that this runs every (1 + small amount) seconds
{ 
//  Serial.print("before transmission test\n");
//  motor.setSpeed(200);     // 100 = slow, 200 = medium, 250 = fast 
//  motor.run(FORWARD);      // turn it on going forward
//  delay(2000);
//  motor.setSpeed(100);
//  delay(2000);
//  motor.setSpeed(70);
//  delay(2000);
//  motor.setSpeed(150);
//  delay(2000);
//  Serial.print("after transmission test\n\n");

  
  /*
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
        
        
        
        //STEERING
//        if(pixy.blocks[j].x > 0 && pixy.blocks[j].x < 132)
//        {
//          //left steering = FORWARD on motor 2 
//          Serial.print("turn left\n");
//          motor2.run(FORWARD); 
//        }
//        else if (pixy.blocks[j].x > 188 && pixy.blocks[j].x < 320)
//        {
//          //right steering
//          Serial.print("turn right\n");
//          motor2.run(BACKWARD);
//        }
//        else
//        {
//          Serial.print("turn straight\n");
//          motor2.run(RELEASE);
//        }
        
        
        //TRANSMISSION
        if(pixy.blocks[j].width > 100 && pixy.blocks[j].height > 100 && pixy.blocks[j].width < 320 && pixy.blocks[j].height < 200 )
        {
          //set to slower speed
          Serial.print("slower\n");
          //delay(1000);
          motor.setSpeed(130);
          //motor.run(FORWARD);
          
          
        }
        else if(pixy.blocks[j].width <= 100 && pixy.blocks[j].height <= 100 && pixy.blocks[j].width >= 20 && pixy.blocks[j].height >= 10)
        {
          //set to faster speed
          Serial.print("faster\n");
          //delay(1000);
          motor.setSpeed(200);
          //motor.run(FORWARD);
          
          
        }
        else
        {
          //delay(1000);
          motor.setSpeed(70);
          Serial.print("no transmission\n");
        }
        
        
        
      } //rof
      
        
    } //fi

    
  } //if block

//This will make it go back ... but now it keeps going back LOL ... try using a conuter to see how long it doesn't detect a block for.
  /*int counter = 0;
  if (!blocks){
    counter += 1;
    if (counter > 10){
    Serial.print("it sees nothing");
    motor2.run(RELEASE);
    counter = 0;
    }
  }*/
  // camera threshold box = 56 x 35
  

  


} //eof loop() void
