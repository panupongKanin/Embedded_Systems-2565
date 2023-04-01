# Module1-IOT (Part 1)

### แนวทางการใช้งานอินเทอร์เน็ตของสรรพสิ่งในระบบการผลิต IoT Approaches to Manufacturing System
### ขื่อ-สกุล : B6304577 นายภานุพงศ์ แคนอินทร์

#### __Start with Arduino Board__

* [__Quiz_101 – กดติด กดดับ 2 ชุด__](https://github.com/panupongKanin/Embedded_Systems-2565/tree/main/Module1-IOT%20(Part%201)/Quiz_101)
  - หากต้องการให้ใช้ 1 สวิตซ์ ควบคุม 1 LED แบบกดติด-กดดับ จำนวน 2 วงจรจะต่อวงจรและเขียนโปรแกรมอย่างไร {SW-D22 -- LED-D19, SW-D23 -- LED-D18}
  
  [![2566-04-01-19-07-28.png](https://i.postimg.cc/VN7Lsvsc/2566-04-01-19-07-28.png)](https://postimg.cc/R3HzXMnP)
  
  
  __Code__
  
```c++
#define BUTTON_PIN1     22 // GIOP22 pin connected to button
#define BUTTON_PIN2     23 // GIOP23 pin connected to button

#define LED_PIN1    18  // ESP32 pin GIOP18, which connected to led
#define LED_PIN2    19  // ESP32 pin GIOP19, which connected to led
#define DEBOUNCE_TIME  50 // the debounce time in millisecond, increase this time if it still chatters

// Variables will change:
int lastSteadyState_led1 = LOW;       // the previous steady state from the input pin
int lastSteadyState_led2 = LOW;       // the previous steady state from the input pin
int lastFlickerableState_led1 = LOW;  // the previous flickerable state from the input pin
int lastFlickerableState_led2 = LOW;  // the previous flickerable state from the input pin
int currentState_led1;                // the current reading from the input pin
int currentState_led2;                // the current reading from the input pin
int led1_state = LOW;    // the current state of LED
int led2_state = LOW;    // the current state of LED

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);

  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}


void led1() {

  // read the state of the switch/button:
  currentState_led1 = digitalRead(BUTTON_PIN1);

  // If the switch/button changed, due to noise or pressing:
  if (currentState_led1 != lastFlickerableState_led1) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState_led1 = currentState_led1;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (lastSteadyState_led1 == HIGH && currentState_led1 == LOW) {
      led1_state = !led1_state;
      digitalWrite(LED_PIN1, led1_state);
    }

    // save the the last steady state
    lastSteadyState_led1 = currentState_led1;
  }
}


void led2() {
  
  // read the state of the switch/button:
  currentState_led2 = digitalRead(BUTTON_PIN2);

  if (currentState_led2 != lastFlickerableState_led2) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState_led2 = currentState_led2;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (lastSteadyState_led2 == HIGH && currentState_led2 == LOW) {
      led2_state = !led2_state;
      digitalWrite(LED_PIN2, led2_state);
    }

    // save the the last steady state
    lastSteadyState_led2 = currentState_led2;
  }

}

void loop() {

  led1();
  led2();

}
```
   

   __รูปการต่อวงจร – 1__
   
   https://postimg.cc/8JHMTLjF
   
   __รูปการต่อวงจร – 2__
   
   [![IMG-0411.jpg](https://i.postimg.cc/y6ftcq31/IMG-0411.jpg)](https://postimg.cc/c6nFGbc2)



* __Quiz_102 – ปรับการแสดงผลที่ Serial Monitor เป็นดังนี้__

  [![2566-04-01-19-11-49.png](https://i.postimg.cc/4nC3C0f7/2566-04-01-19-11-49.png)](https://postimg.cc/N24tmprB)


* __Quiz_103 – Read Sensor and Show__

  [![2566-04-01-19-13-33.png](https://i.postimg.cc/gJWFWP8P/2566-04-01-19-13-33.png)](https://postimg.cc/XZQDfms2)
