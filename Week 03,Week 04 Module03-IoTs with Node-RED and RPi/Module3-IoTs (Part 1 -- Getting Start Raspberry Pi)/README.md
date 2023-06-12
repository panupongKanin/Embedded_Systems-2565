### Q101 Python Switch control LED >> กดติด ปล่อยดับ
#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20release%20to%20turn%20off/w03-w04-Quiz_101_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20release%20to%20turn%20off/w03-w04-Quiz_101_0102.png" />

#### code ที่ใช้
```
import RPi.GPIO as GPIO  # Add GPIO library to a Python sketch
import time     # Add time library to a Python sketch
LED_pin = 35     # Ref Board
SW_Pin = 37
GPIO.setmode(GPIO.BOARD)    #Setup GPIO using GPIO.Pin
GPIO.setup(LED_pin, GPIO.OUT)   #Setup pin to output
GPIO.setup(SW_Pin, GPIO.IN, pull_up_down = GPIO.PUD_UP)
         #Setup pin to input and Pull-Up
 
while True:
    if (GPIO.input(SW_Pin)==0):   # Read Botton pin
        GPIO.output(LED_pin,GPIO.HIGH) # Set LED pin to HIGH
        print("Input = 0, HIGH") 
    else:
        GPIO.output(LED_pin,GPIO.LOW) # Set LED pin to LOW
        print("Input = 1, LOW")
```

#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20release%20to%20turn%20off/w03-w04-Quiz_101_0103.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20release%20to%20turn%20off/w03-w04-Quiz_101_0104.png" />

### Q101 Python Switch control LED >> กดติด กดดับ
#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20press%20to%20turn%20off/w03-w04-Quiz_101_0201.png" />
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20press%20to%20turn%20off/w03-w04-Quiz_101_0202.png" />

#### code ที่ใช้
```
import RPi.GPIO as GPIO
import time

LED_pin = 35
SW_Pin = 37
SW_State = 0
debounce_time = 0.1  # Adjust this value to set the debounce time (in seconds)

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(LED_pin, GPIO.OUT)
GPIO.setup(SW_Pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def toggle_led_state():
    global SW_State
    if SW_State == 0:
        SW_State = 1
        GPIO.output(LED_pin, GPIO.HIGH)
        print("State = 1, HIGH")
    else:
        SW_State = 0
        GPIO.output(LED_pin, GPIO.LOW)
        print("State = 0, LOW")

def handle_switch_press():
    start_time = time.time()
    previous_state = GPIO.input(SW_Pin)

    while GPIO.input(SW_Pin) == previous_state:
        if time.time() - start_time >= 1.0:  # Adjust the duration as needed
            return  # Exit the function without changing the LED state
        time.sleep(0.1)

    toggle_led_state()

previous_state = GPIO.HIGH
current_state = GPIO.HIGH
state_changed_time = time.time()

while True:
    previous_state = current_state
    current_state = GPIO.input(SW_Pin)
    
    if current_state != previous_state:
        state_changed_time = time.time()
    
    if current_state == GPIO.LOW and time.time() - state_changed_time >= debounce_time:
        handle_switch_press()
```

#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20press%20to%20turn%20off/w03-w04-Quiz_101_0203.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20press%20to%20turn%20off/w03-w04-Quiz_101_0204.png" />

### Q101 Python Switch >> Switch Counter
#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Switch%20Counter/w03-w04-Quiz_101_0301.png" />

#### code ที่ใช้
```
import RPi.GPIO as GPIO
import time

SW_Pin = 37
count = 0

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(SW_Pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def button_pressed(channel):
    global count
    count += 1
    print("Count =", count)

GPIO.add_event_detect(SW_Pin, GPIO.FALLING, callback=button_pressed, bouncetime=200)

try:
    while True:
        time.sleep(1)

except KeyboardInterrupt:
    GPIO.cleanup()
```

#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Switch%20Counter/w03-w04-Quiz_101_0302.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Switch%20Counter/w03-w04-Quiz_101_0303.png" />

### Q102 Python Switch control LED >> กดติด ปล่อยดับ
