Light Meter Logger. 

Every readInterval millis() the photocell is sampled numSamples times at sampleRate millis() 
interval, recording the samples average in an array. If the maximum log entries is reached an 
LED will blink as notification. The dump data pushbutton will dump the log to the serial port.

Connect one end of the photocell to 5V, the other end to Analog In 0. Then connect one end of 
a 10K resistor from Analog In 0 to ground. Uses LED on prototype shield for log full indicator.
Uses pushbutton on prototype shield for dump data request.

If you found this fun or interesting please make a small donation to my PayPal account at https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=GTBD7T7BXPGQY. I have many more Arduino projects in mind and appreciate your support.