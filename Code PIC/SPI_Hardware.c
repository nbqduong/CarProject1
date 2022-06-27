#include <16F887.h>
#FUSES NOWDT, HS, NOPROTECT
#use delay(clock=20000000)

      // DECLARE PLACE
#byte PORTA=0x05
#byte motor_port=0x06
#byte portd=0x08
#byte PORTC=0x07

 //Declare Pin's function
 
 //Matrix led
#define CS_Pin       pin_a1
#define MOSI_Pin     pin_a2
#define CLK_Pin      pin_a0
#define POWER_Pin    pin_a3
#define DECODE_MODE  9
#define INTENSITY    10
#define SCAN_LIMIT   11
#define SHUTDOWN     12
#define DISPLAY_TEST 16

      //GLOBAL VARIABLE PLACE
//Motor

//motor move forward
int m1_f=1<<7, m2_f=1<<5, m3_f=1<<3, m4_f=1<<1,
   ///motor move backward
   m1_b=1<<6, m2_b=1<<4, m3_b=1<< 2, m4_b=1<< 0;

int flag =0, trig=0;


         //FUNCTION PLACE
//connect with ledmatrix
void SPI_Write_Byte(unsigned char num);
void send_data(unsigned char address,unsigned char value);
void MAX7219_INIT();


//display face
void normal_();
void scare();
void funny();

//Move car
void go_for( int times);
void go_back(int times);
void turn_left(int times);
void turn_right(int times);
void stop(int times);

//Check status
void check_status(int check_times)
{
   for (int i=0; i < check_times; i++) 
   {
      delay_ms(10);
   }
}

//setup
void setup();
void setup0()
{
   SET_TRIS_D(0);
   SET_TRIS_C(0b11111111);
   SET_TRIS_B(0);
   output_high(POWER_Pin);
   portd=~(1<<7);
   portc=0;
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT);
   ext_int_edge(H_to_L);
}

#INT_EXT
   void plus_flag()
   {
      flag=1;
      trig++;
   }
   
   
void main()
{
 
   setup();
   setup0(); 
   for (int i=1; i<9; i++) send_data(i,0b00000000);
  
   while(1)
   { 
      normal_();
      
     
      
   }
}
      //CHECK


      //MOTOR MOVE
void go_for(int times)
{
   motor_port=(m1_f|m2_f|m3_f|m4_f);   check_status(times);
}

void go_back(int times)
{
   motor_port = (m1_b|m2_b|m3_b|m4_b);   check_status(times);
}

void turn_left(int times)
{
   motor_port = (m1_f|m3_f);   check_status(times);
}

void turn_right(int times)
{
   motor_port = (m2_f|m4_f);      check_status(times);
}

void stop(int times)
{
   motor_port =0;    check_status(times);
}

void normal_() 
{     
      send_data(1,0b11111111); //ve hang 1
      send_data(8,0b11111111); // hang 8
      
      for (int i=2; i<8; i++) 
      {  
         switch (i)
         {
            case 3: send_data(i, (0b10000101 ) ); break;
            case 4: send_data(i, (0b10100001 ) ); break;
            case 6: send_data(i, (0b10000101 ) ); break;
            default: send_data(i, (1 | 1<<7) ); break;           
         }                            
      }
      check_status(10);

      for (int z=1; z<100; z++);
      for (int i=2; i<8; i++) 
      {  
         switch (i)
         {
            case 3: send_data(i, (0b10000101 ) ); break;
            case 4: send_data(i, (0b10100001 ) ); break;
            case 5: send_data(i, (0b10100001 ) ); break;
            case 6: send_data(i, (0b10000101 ) ); break;
            default: send_data(i, (1 | 1<<7) ); break;           
         }                            
      }
      check_status(10);

    
     for (int i=2; i<8; i++) 
      {  
         switch (i)
         {
            case 3: send_data(i, (0b10100101 ) ); break;
            case 4: send_data(i, (0b10100001 ) ); break;
            case 5: send_data(i, (0b10100001 ) ); break;
            case 6: send_data(i, (0b10100101 ) ); break;
            default: send_data(i, (1 | 1<<7) ); break;           
         }                            
      }
      check_status(10);

}

void scare()
{
      send_data(1,0b00111100); send_data(8,0b00111100);
      send_data(2,0b01000010);  send_data(7,0b01000010);
      
       for (int i=3; i<7; i++) 
         switch (i)
         {
            case 3: send_data(i, (0b10100101 ) ); break;
            case 4: send_data(i, (0b10010001 ) ); break;
            case 5: send_data(i, (0b10010001 ) ); break;
            case 6: send_data(i, (0b10100101 ) ); break;
            default: send_data(i, (1 | 1<<7) ); break;           
         }      
      delay_ms(50);
      
      for (int i=2; i<7; i++) 
         switch (i)
         {
            case 2: send_data(i,  0b01001010);       break;
            case 3: send_data(i, (0b10100101 ) ); break;
            case 4: send_data(i, (0b10010001 ) ); break;
            case 5: send_data(i, (0b10010001 ) ); break;
            case 6: send_data(i, (0b10100101 ) ); break;
            default: send_data(i, (1 | 1<<7) ); break;           
         }      
      delay_ms(150);
      
      for (int i=2; i<7; i++) 
         switch (i)
         {
            case 2: send_data(i,  0b01000010);       break;
            case 3: send_data(i, (0b10000101 ) ); break;
            case 4: send_data(i, (0b10100001 ) ); break;
//!            case 5: send_data(i, (0b10100001 ) ); break;
            case 6: send_data(i, (0b10000101 ) ); break;
            default: send_data(i, (1 | 1<<7) ); break;           
         }      
      delay_ms(100);
      
      for (int i=3; i<7; i++) 
         switch (i)
         {
            case 3: send_data(i, (0b10000101 ) ); break;
            case 4: send_data(i, (0b10100001 ) ); break;
            case 5: send_data(i, (0b10100001 ) ); break;
            case 6: send_data(i, (0b10000101 ) ); break;
            default: send_data(i, (1 | 1<<7) ); break;           
         }      
      delay_ms(100);
}

void funny()
{
      send_data(1,0b00111100); send_data(8,0b00111100);
      send_data(2,0b01000010);  send_data(7,0b01000010);
      
       for (int i=2; i<8; i++) 
         switch (i)
         {
            case 2: send_data(i,  0b01010010);  break;
            case 3: send_data(i, (0b10100101 ) ); break;
            case 4: send_data(i, (0b10100001 ) ); break;
            case 5: send_data(i, (0b10100001 ) ); break;
            case 6: send_data(i, (0b10100101 ) ); break;
            case 7: send_data(i,  0b01010010);  break;          
         }      
      delay_ms(200);
}      

void SPI_Write_Byte(unsigned char num) // gui 1 byte toi slave theo chuan SPI
{
    unsigned long t, Mask, Flag;
    output_low(CLK_Pin);
    Mask = 128;
    for (t=0; t<8; t++){
        Flag = num & Mask;
        if(Flag == 0) output_low(MOSI_Pin);
        else output_high(MOSI_Pin);
        output_high(CLK_Pin);
        output_low(CLK_Pin);
        Mask = Mask >> 1;
      }
}

void send_data(unsigned char address,unsigned char value) // gui thong tin toi slave gom: adress , value
{
   output_low(CS_Pin);  // chon slave
   SPI_Write_Byte(address);
   SPI_Write_Byte(value);
   output_high(CS_Pin);       // ket thuc
}


void setup() // cai dat truoc khi truyen du lieu. nguon tham klhao
{
   set_tris_c(0x00); // reset cong C
   output_high(pin_c2); // Chon Max7219 lam slave
   delay_ms(100);
   
   MAX7219_INIT(); //Khoi dong Max7219
   
   //Cai dat SPI phu hop voi LED 8x8
   send_data(DISPLAY_TEST,0x01);
   send_data(DECODE_MODE,0x00);
   send_data(INTENSITY,0x00);
   send_data(SCAN_LIMIT,0x0f);
   send_data(SHUTDOWN,0x01);
}

void MAX7219_INIT() { //cai dat cau hinh cho MAX7219 
  // Tat che do Shutdown
  output_low(CS_Pin);              // CS pin is pulled LOW
  SPI_Write_Byte(0x0C);    // Select Shutdown register
  SPI_Write_Byte(0x01);    // Set D0 bit to return to normal operation
  output_high(CS_Pin);              // CS pin is pulled HIGH

  // Set BCD decode mode for digits DIG0-DIG3
  output_low(CS_Pin);              // CS pin is pulled LOW
  SPI_Write_Byte(0x09);    // Select Decode Mode register
  SPI_Write_Byte(0x0F);    // Select BCD mode for digits DIG0-DIG3
  output_high(CS_Pin);              // CS pin is pulled HIGH

  // Set display brighness
  output_low(CS_Pin);          // CS pin is pulled LOW
  SPI_Write_Byte(0x0A);    // Select Intensity register
  SPI_Write_Byte(0x0F);    // Set maximum brightness
  output_high(CS_Pin);              // CS pin is pulled HIGH

   // Set display refresh
  output_low(CS_Pin);              // CS pin is pulled LOW
  SPI_Write_Byte(0x0B);    // Select Scan-Limit register
  SPI_Write_Byte(0x03);    // Select digits DIG0-DIG3
  output_high(CS_Pin);              // CS pin is pulled HIGH

 // Enable Display-Test
  output_low(CS_Pin); ;              // CS pin is pulled LOW
  SPI_Write_Byte(0x0F);    // Select Display-Test register
  SPI_Write_Byte(0x01);    // Enable Display-Test
  output_high(CS_Pin);              // CS pin is pulled HIGH

  Delay_ms(100);
 // Disable Display-Test
  output_low(CS_Pin);              // CS pin is pulled LOW
  SPI_Write_Byte(0x0F);    // Select Display-Test register
  SPI_Write_Byte(0x00);    // Disable Display-Test
  output_high(CS_Pin); ;             // CS pin is pulled HIGH

}
