
#include <SPI.h>  
#include <Pixy.h>
#include <AFMotor.h>

AF_DCMotor motor(4, MOTOR12_2KHZ); // create motor #1, 2KHz pwm
AF_DCMotor motor2(2, MOTOR12_2KHZ); // Steering motor

Pixy pixy; // This is the main Pixy object 

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");
 
 Serial.print("Steering test\n");
 //STEERING TEST
  motor2.setSpeed(250);
  motor2.run(FORWARD);    // FORWARD = left, RELEASE = none, BACKWARD = right
  delay(1000);
  motor2.run(BACKWARD);    // FORWARD = left, RELEASE = none, BACKWARD = right
  delay(1000);
  motor2.run(RELEASE);

  Serial.print("Transmission Test\n");
 // Start up motor
 // TRANSMISSION TEST (TESTING DIFFERENT SPEEDS)
  motor.setSpeed(250);     // 100 = slow, 200 = medium, 250 = fast 
  motor.run(FORWARD);      // turn it on going forward
  delay(2000);
  motor.setSpeed(100);
  delay(2000);
  motor.setSpeed(70);
  delay(2000);
  
  motor.setSpeed(250); 
  delay(2000);
  
  
  Serial.print("pixy init\n");
  pixy.init();
  

 
 
  

  
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
     
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);

        pixy.blocks[j].print();
        
        
        /*
        if (pixy.blocks[j].width>100)
        {
          Serial.print("big box -> left\n\n");
          
          motor2.run(FORWARD);  //left
          
        }
        
        if(pixy.blocks[j].width>0 && pixy.blocks[j].width < 100)
        {
          Serial.print("big box -> right\n\n");
          motor2.run(BACKWARD);  //right
          //motor2.setSpeed(100);
          
          
        }
        */
        
        //STEERING
        if(pixy.blocks[j].x >= 0 && pixy.blocks[j].x < 132)
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
        
        else if (pixy.blocks[j].x >= 132 && pixy.blocks[j].x <= 188)
        {
          Serial.print("turn straight\n");
          motor2.run(RELEASE);
        }
        
        
        
        //TRANSMISSION
        if(pixy.blocks[j].width > 100 && pixy.blocks[j].height > 100 && pixy.blocks[j].width < 321 && pixy.blocks[j].height < 201 )
        {
          //set to slower speed
          Serial.print("slower\n");
          motor.setSpeed(150);
          motor.run(FORWARD);
          motor2.run(BACKWARD);    // FORWARD = left, RELEASE = none, BACKWARD = right
          
        }
        else if(pixy.blocks[j].width <= 100 && pixy.blocks[j].height <= 100 && pixy.blocks[j].width >= 20 && pixy.blocks[j].height >= 10)
        {
          //set to faster speed
          Serial.print("faster\n");
          motor.setSpeed(250);
          motor.run(FORWARD);
          motor2.run(FORWARD);    // FORWARD = left, RELEASE = none, BACKWARD = right
          
          
        }
        
        
      } //rof
      
        
    } //fi

    
  } //fi block
  
  /*
  // camera threshold box = 56 x 35
  
  */


  


} //eof void
