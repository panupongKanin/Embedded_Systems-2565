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

### Q102 Node-RED เพื่อควบคุมสวิตซ์กดแบบ กดติด กดดับ {Switch-LED 1 คู่}
#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q102/Using%20Node-RED%20(press%20to%20turn%20on%20press%20to%20turn%20off%201LED%20and%201Switch)%20/w03-w04-Quiz_102_0101.png" />

#### Node-RED Code ที่ใช้
```
[
    {
        "id": "51676f5ae1675c99",
        "type": "tab",
        "label": "Q102-0101",
        "disabled": false,
        "info": "Using Node-RED (press to turn on press to turn off 1LED and 1Switch) ",
        "env": []
    },
    {
        "id": "eec1119ce2081360",
        "type": "rpi-gpio in",
        "z": "51676f5ae1675c99",
        "name": "Switch 1",
        "pin": "26",
        "intype": "up",
        "debounce": "25",
        "read": false,
        "bcm": true,
        "x": 220,
        "y": 300,
        "wires": [
            [
                "016c3e9be89901e3"
            ]
        ]
    },
    {
        "id": "06cb6823737d2dfc",
        "type": "rpi-gpio out",
        "z": "51676f5ae1675c99",
        "name": "LED 1",
        "pin": "19",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 710,
        "y": 300,
        "wires": []
    },
    {
        "id": "016c3e9be89901e3",
        "type": "function",
        "z": "51676f5ae1675c99",
        "name": "State Control",
        "func": "context.state = context.state | false;\ncontext.state = !context.state\n\nvar myContext = context.state;\nvar count = context.get(\"count\")||0;\ncount += 1;\ncontext.set(\"count\",count);\nmsg.count = count;\n\nfunction isOdd(num) { \n    return num % 2;\n}\n\nif(myContext === true && isOdd((count+1)/2) ===1){\n    msg.payload = 1;\n    return msg;\n} else if (myContext === true && isOdd((count+1)/2) ===0){\n    msg.payload = 0;\n    return msg;\n}",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 450,
        "y": 300,
        "wires": [
            [
                "06cb6823737d2dfc"
            ]
        ]
    }
]
```

#### การต่อวงจร

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q102/Using%20Node-RED%20(press%20to%20turn%20on%20press%20to%20turn%20off%201LED%20and%201Switch)%20/w03-w04-Quiz_102_0102.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q102/Using%20Node-RED%20(press%20to%20turn%20on%20press%20to%20turn%20off%201LED%20and%201Switch)%20/w03-w04-Quiz_102_0103.png" />

### Q102 Node-RED เพื่อควบคุมสวิตซ์กดแบบ กดติด กดดับ 2 คู่
#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q102/Using%20Node-RED%20(press%20to%20turn%20on%20press%20to%20turn%20off%202LED%20and%202Switch)%20/w03-w04-Quiz_102_0201.png" />

#### Node-RED Code ที่ใช้
```
[
    {
        "id": "7fc9ea12076b5d25",
        "type": "tab",
        "label": "Q102-0102",
        "disabled": false,
        "info": "Using Node-RED (press to turn on press to turn off 2LED and 2Switch) ",
        "env": []
    },
    {
        "id": "5e0e47b70cfa15b3",
        "type": "rpi-gpio in",
        "z": "7fc9ea12076b5d25",
        "name": "Switch 1",
        "pin": "26",
        "intype": "up",
        "debounce": "25",
        "read": false,
        "bcm": true,
        "x": 220,
        "y": 300,
        "wires": [
            [
                "e9a1afc0ccd95ad2"
            ]
        ]
    },
    {
        "id": "ece0b86753b4806e",
        "type": "rpi-gpio out",
        "z": "7fc9ea12076b5d25",
        "name": "LED 1",
        "pin": "19",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 690,
        "y": 300,
        "wires": []
    },
    {
        "id": "e9a1afc0ccd95ad2",
        "type": "function",
        "z": "7fc9ea12076b5d25",
        "name": "State Control",
        "func": "context.state = context.state | false;\ncontext.state = !context.state\n\nvar myContext = context.state;\nvar count = context.get(\"count\")||0;\ncount += 1;\ncontext.set(\"count\",count);\nmsg.count = count;\n\nfunction isOdd(num) { \n    return num % 2;\n}\n\nif(myContext === true && isOdd((count+1)/2) ===1){\n    msg.payload = 1;\n    return msg;\n} else if (myContext === true && isOdd((count+1)/2) ===0){\n    msg.payload = 0;\n    return msg;\n}",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 450,
        "y": 300,
        "wires": [
            [
                "ece0b86753b4806e"
            ]
        ]
    },
    {
        "id": "0c4853c44002d61b",
        "type": "rpi-gpio out",
        "z": "7fc9ea12076b5d25",
        "name": "LED 2",
        "pin": "16",
        "set": "",
        "level": "0",
        "freq": "",
        "out": "out",
        "bcm": true,
        "x": 690,
        "y": 400,
        "wires": []
    },
    {
        "id": "6efb796920ac0f04",
        "type": "rpi-gpio in",
        "z": "7fc9ea12076b5d25",
        "name": "Switch 2",
        "pin": "21",
        "intype": "up",
        "debounce": "25",
        "read": false,
        "bcm": true,
        "x": 220,
        "y": 400,
        "wires": [
            [
                "aad96eb4d550ef39"
            ]
        ]
    },
    {
        "id": "aad96eb4d550ef39",
        "type": "function",
        "z": "7fc9ea12076b5d25",
        "name": "State Control",
        "func": "context.state = context.state | false;\ncontext.state = !context.state\nvar myContext = context.state;\nvar count = context.get(\"count\")||0;\ncount += 1;\ncontext.set(\"count\",count);\nmsg.count = count;\nfunction isOdd(num) { return num % 2;}\n\nif(myContext === true && isOdd((count+1)/2) ===1){\n    msg.payload = 1;\n    return msg;\n} else if (myContext === true && isOdd((count+1)/2) ===0){\n    msg.payload = 0;\n    return msg;\n}",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 450,
        "y": 400,
        "wires": [
            [
                "0c4853c44002d61b"
            ]
        ]
    }
]
```

#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q102/Using%20Node-RED%20(press%20to%20turn%20on%20press%20to%20turn%20off%202LED%20and%202Switch)%20/w03-w04-Quiz_102_0202.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q102/Using%20Node-RED%20(press%20to%20turn%20on%20press%20to%20turn%20off%202LED%20and%202Switch)%20/w03-w04-Quiz_102_0203.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q102/Using%20Node-RED%20(press%20to%20turn%20on%20press%20to%20turn%20off%202LED%20and%202Switch)%20/w03-w04-Quiz_102_0204.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q102/Using%20Node-RED%20(press%20to%20turn%20on%20press%20to%20turn%20off%202LED%20and%202Switch)%20/w03-w04-Quiz_102_0205.png" />

### Q102 Node-RED เพื่ออ่าน DHT-22 Sensor
#### โปรแกรมที่ใช้ทดสอบ

#### code ที่ใช้
#### การต่อวงจร
