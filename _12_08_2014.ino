//This version uses ADC with prescale of 8 without changing
//enable ADC High Speed Mode

// include the library code:
#include <LiquidCrystal.h>
#include <avr/io.h>
#include <math.h>

#define F_CPU 16000000L 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//const int ledPin = 9;
double Vcc = 4.95;

int lcd_start() 
{
  // set up the LCD's number of columns and rows: 
  lcd.begin(16,2);
  // Print a message to the LCD.
  lcd.print("hello, world!!");
  //pinMode(ledPin, OUTPUT);
  ADCSRA = ADCSRA & 0xF8;//clear ADC Prescale
}


int adc_decay_start() //setup ADC7(A0) with normal conversion
{
  ADCSRA |= (1<<ADPS2);  //prescalar=16; ADC clk freq=1MHz;
                         //1 ADC clock = 1us; 
  ADCSRB |= (1<<ADHSM);  //enable ADC high speed mode
  ADMUX |= 0x47;    //AVcc with external capacitor on AREF pin. right adjustment to maximize 10 bit.
                    //set ADC7 as input channel
  ADCSRA |= (1<<ADEN);  //ADC enable
  ADCSRA |= (1<<ADSC);  //ADC start conversion
  //normal conversion does not manipulate ADCSRB
}

//double adc_normal()
//{
//  int sum = 0;  //use to average normal_ADC reading
//  adc_decay_start();
//  for (int i=0; i<9; i++)
//  {
//    while(ADCSRA & (1<<ADSC));  //wait till ADC complete
//    sum = sum+ADC;
//    ADCSRA |= (1<<ADSC);
//  }  
//  while(ADCSRA & (1<<ADSC)); 
//  sum = sum+ADC;
//  //ADCSRA &= ~(1<<ADEN);  //don't need to shut down ADC
//  double normal_ADC_ave = sum/10.0/1023.0*1000*Vcc;
//  return normal_ADC_ave;
//}

int main (void)  
{
lcd_start();
DDRB |= (1<<5);  //setting Pin 9 as LED output
TCCR1B |= (1<<CS11);  //prescalar 8, initializing Timer/counter1
for (;;)
{
double tau_sum = 0;
double tau_ave = 0;
for (int freq = 0; freq < 1500; freq++)
{
  double normal_ave = 0;
  double decay_2us = 0;//actually it's 1.5us
  double tau = 0; 
  int LED_flag = 0;
  TCNT1 =0;
  while (LED_flag ==0)  //LED dark
  {
    if (TCNT1 >= 100)  //counting
    {
      PORTB |= (1<<5);  //LED light up
      TCNT1 = 0;  //Reset timer value
      LED_flag = 1;  
    }
  }
  while (LED_flag == 1)  //LED light up
  {
    if (TCNT1 >=40 & TCNT1 < 70)
    {adc_decay_start();
      while(ADCSRA & (1<<ADSC));  //wait till ADC complete
     normal_ave  = ADC/1023.0*1000*Vcc;
    }
    else if (TCNT1 >= 100)
    {
      PORTB &= ~(1<<5);  //LED shut down
      adc_decay_start();
      while(ADCSRA & (1<<ADSC));  //wait till ADC complete
      decay_2us = ADC/1023.0*1000*Vcc;
      //Serial.println(decay_2us);
      LED_flag =0;
      TCNT1 = 0;  //reset timer value
      tau = (0.0-1.5)/(log(decay_2us/normal_ave));
      tau_sum = tau_sum + tau; 
    }
  }
}
tau_ave = tau_sum/150.0;
lcd.setCursor(0,1);
lcd.print(tau_ave);
//lcd.print(normal_ave);
lcd.print("us     ");
}
}

//}  
    

