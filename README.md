# Glucose-Detector
Senior design concept. Couldn't carry out a working prototype due to limited resources. Still seeking out solution  
Goal: utilize oxygen-Ruthenium quenching decay to convert light decay signal into glucose concentration.  
Hardware:  
1. Arduino Leonardo  
2. LCD screen  
3. glucose enzyme coated ruthenium probe  
4. avalaunche photodiode

Arduino ADC rate was insufficient for micro-second level.  
My partner(Tian) and I found a way to bypass the Arduino library, so that we could access the ATMEGA chip directly.  
We changed some parameter to make the AD conversion at the fastest possible speed (13us, surely, precision was conpromised).  
It managed to pick up signal at 2us after we called ADC function (and converted it to an 8-bit digital signal in next 10us), but the avalaunche photodiode we purchased at that time had a low frequency filter, which strongly distorted the expected signal (expected signal should be a steady high voltage, and then decay potentially, but with a low freq filter, we only saw spikes).  

Since the problem was mainly about the photodiode, we instead used simple RC circuit to simulate the actual light signal, and the outcome was OK.  

Please read through FinalReport.pdf for detailed info.  
_12_08_2014.info is the code uploaded to Arduino.

Full history was stored elsewhere. Here're final for SeniorDesign.  

3/19/2016
I decided to restart this project, I saw a thread about using an external ADC attached to Arduino.  
In this way, I don't have to mess with accessing ATMEGA chip.   

3/21/2016  
Received LCD screen module from adafruit, unfortunately, I need to solder it up myself.  
