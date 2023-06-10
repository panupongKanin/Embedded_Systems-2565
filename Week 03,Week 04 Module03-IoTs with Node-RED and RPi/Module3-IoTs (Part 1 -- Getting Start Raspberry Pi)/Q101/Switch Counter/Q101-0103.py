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
