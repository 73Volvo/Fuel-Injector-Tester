
// enter two of the three variables bellow. If all three are entered, only pulse and duty cycle will be used.
float pulse = 2.35; // pulse width in miliseconds
int RPM = 0; // RPM of smulation
float dutyCycle = 50; // duty cycle of injector
int continuous = 0; // if 1, injector will fire continuously

// enter the duration of test run
long duration = 2.5; // total running time in seconds

long durationMilli = 0;
int pulseMilli = 0; // pulse in milliseconds, caluclated by program
int pulseMicro = 0; // pulse in microseconds, calculated by program
float pause = 0; // pause between pulses, caluclated by program
int pauseMilli = 0; // pause in milliseconds, caluclated by program
int pauseMicro = 0; // pause in microseconds, caluclated by program
float cycle = 0.0; // time per on/off cycle, caluclated by program

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode (53, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

// if pulse width has been entered
  if (pulse != 0 ){
    pulseMilli = pulse;
    pulseMicro = (pulse-pulseMilli)*1000;
    // if duty cycle has been entered
      if (dutyCycle != 0) {
        cycle = pulse * (100/dutyCycle);
        pause = cycle-pulse;
        RPM = (60000/cycle) * 2;
      }
      // if RPM has been entered
      else if (RPM != 0 ) {
        pause = (60000 - ((RPM/2) * pulseMilli))/(RPM/2);
        cycle = pause+pulse;
        dutyCycle = (pulse/cycle)*100;
      }
    }
// if duty cycle and RPM has been entered, but not pulse width
 else {
    if ((dutyCycle != 0) && (RPM != 0 )) {
    pulse = ( 60000/ (RPM/2)) * (dutyCycle/100);
    pulseMilli = pulse;
    pulseMicro = (pulse-pulseMilli)*1000;
    pause = ( 60000/ (RPM/2)) * ((100-dutyCycle)/100);
    cycle = pulse + pause;
   }   
 }

  pauseMilli = pause;
  pauseMicro = (pause-pauseMilli)*1000;

  Serial.begin(9600); // open the serial port at 9600 bps:
  Serial.println();
  Serial.println("RUNNING TEST");
  Serial.print("fuel pulse in milliseconds: ");
  Serial.println(pulse);
  Serial.print("duty cycle : ");
  Serial.print(dutyCycle);
  Serial.println("%");
  Serial.print("each total cycle in milliseconds: ");
  Serial.println(cycle);
  Serial.print("RPM: ");
  Serial.println(RPM);
  Serial.print("test duration in seconds: ");
  Serial.println(duration);
  Serial.println();
}

// the loop function runs over and over again forever
void loop() {

if ( continuous == 1 ) {

  if ( duration > millis() /1000 ) {
  durationMilli = (duration * 1000);
  digitalWrite(53, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("duration: ");
    Serial.println(duration);
    Serial.print("millis / 1000: ");
    Serial.println( millis() /1000 );
  delay(durationMilli);
  digitalWrite(53, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  }
}

else if ( duration >= (millis()/1000) ) {

  // digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(53, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(pulseMilli);
  delayMicroseconds(pulseMicro);

  // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LO
  digitalWrite(53, LOW);
  digitalWrite(LED_BUILTIN, LOW);  
  delay(pauseMilli);
  delayMicroseconds(pauseMicro);

}  
}
