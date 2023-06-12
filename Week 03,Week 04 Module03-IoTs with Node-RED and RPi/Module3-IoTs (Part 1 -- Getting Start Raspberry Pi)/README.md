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
ddsfsef
```
#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20press%20to%20turn%20off/w03-w04-Quiz_101_0203.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%201%20--%20Getting%20Start%20Raspberry%20Pi)/Q101/Press%20to%20turn%20on%20press%20to%20turn%20off/w03-w04-Quiz_101_0204.png" />
