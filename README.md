# Fuel-Injector-Tester
An arduino program I made to test fuel injectors


I used an arduino connected to a MOFSET to switch an adjustable-voltage signal to the injector, it seemed to work well to test the injector dead times, etc.


You can adjust the first five variable to simulate different engine situations:


// enter two of the three variables bellow. If all three are entered, only pulse and duty cycle will be used.

float pulse = 2.35; // pulse width in miliseconds

int RPM = 0; // RPM of smulation

float dutyCycle = 50; // duty cycle of injector

int continuous = 0; // if 1, injector will fire continuously


// enter the duration of test run

long duration = 2.5; // total running time in seconds
