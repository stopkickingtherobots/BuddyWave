// assign pins
int ledRed = D0;
int boardLed = D7;
int motion = D4;
int val = 0;

void setup() {
  // This part is mostly the same:
  pinMode(ledRed,OUTPUT); // Our LED pin is output (lighting up the LED)
  pinMode(boardLed,OUTPUT); // Our on-board LED is output as well
  pinMode(motion,INPUT_PULLUP);  // Our motion detector pin is input (reading the motion detector)

  // Here we are going to subscribe to your buddy's event using Particle.subscribe
  Particle.subscribe("Deakin_RIOT_SIT210_Photon_Buddy", myHandler);
  // Subscribe will listen for the event buddy_unique_event_name and, when it finds it, will run the function myHandler()
  // (Remember to replace buddy_unique_event_name with your buddy's actual unique event name that they have in their firmware.)
  // myHandler() is declared later in this app.
}

void loop() {
    
    delay(2000);
    
    // read sensor output
    readTheSensor();
    
    // control statement which publishes event when motion detected
    if (val == HIGH) {
        Particle.publish("Buddy_Franklin_Zeppelin_Event", "wave_back");

        digitalWrite(ledRed, HIGH);
        delay(300);
        digitalWrite(ledRed, LOW);
        delay(300);
        digitalWrite(ledRed, HIGH);
        delay(300);
        digitalWrite(ledRed, LOW);
    }
}

// function to read sensor output
void readTheSensor() {
    val = digitalRead(motion);
}

// Now for the myHandler function, which is called when the cloud tells us that our buddy's event is published.
void myHandler(const char *event, const char *data)
{
  /* Particle.subscribe handlers are void functions, which means they don't return anything.
  They take two variables-- the name of your event, and any data that goes along with your event.
  In this case, the event will be "buddy_unique_event_name" and the data will be "intact" or "broken"

  Since the input here is a char, we can't do
     data=="intact"
    or
     data=="broken"

  chars just don't play that way. Instead we're going to strcmp(), which compares two chars.
  If they are the same, strcmp will return 0.
  */

  if (strcmp(data,"wave")==0) {
    digitalWrite(boardLed,HIGH);
  }
  else {
    digitalWrite(boardLed,LOW);
  }
}