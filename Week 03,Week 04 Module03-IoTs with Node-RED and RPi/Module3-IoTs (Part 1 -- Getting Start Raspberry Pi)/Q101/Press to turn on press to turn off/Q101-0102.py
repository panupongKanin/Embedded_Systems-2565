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
