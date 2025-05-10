# References
# https://github.com/KitronikLtd/Kitronik-Pico-Robotics-Board-MicroPython
from machine import Pin
import ubluetooth
import PicoRobotics
import time
board = PicoRobotics.KitronikPicoRobotics()
motors = [1,2]
led = Pin("LED", Pin.OUT)

class BLEController:
    def __init__(self):
        led.off()
        self.ble = ubluetooth.BLE()
        self.ble.active(True)
        self.ble.irq(self.bt_irq)
        UART_UUID = ubluetooth.UUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E")
        TX = (ubluetooth.UUID("6E400003-B5A3-F393-E0A9-E50E24DCCA9E"), ubluetooth.FLAG_NOTIFY)
        RX = (ubluetooth.UUID("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"), ubluetooth.FLAG_WRITE)
        UART_SERVICE = (UART_UUID, (TX, RX))
        ((self.tx, self.rx), ) = self.ble.gatts_register_services((UART_SERVICE, ))
        self.ble.gap_advertise(100, adv_data=self.advertise("PicoW-BLE"))
        print("BLE advertising as PicoW-BLE")
    def drive(self, dir, speed=100):
        print(dir)
        if (dir == "f"):
            board.motorOn(motors[0], "f", speed)
            board.motorOn(motors[1], "f", speed)
        elif (dir == "b"):
            board.motorOn(motors[0], "r", speed)
            board.motorOn(motors[1], "r", speed)       
        elif (dir == "r"):
            board.motorOn(motors[0], "f", speed)
            board.motorOff(motors[1])       
        elif (dir == "l"):
            board.motorOn(motors[1], "f", speed)
            board.motorOff(motors[0])
        elif (dir == "s"):
            board.motorOff(motors[0])
            board.motorOff(motors[1])

    def advertise(self, name):
        return bytes([len(name) + 1, 0x09]) + name.encode()

    # Handle commands received
    def bt_irq(self, event, data):
        if event == 3:  # Write
            buffer = self.ble.gatts_read(self.rx).decode().strip()
            print("Received:", buffer)
            if buffer == "f":
                print("Forward")
                led.on()
                self.drive("f")
                time.sleep(3)
                self.drive("s")
                led.off()
            elif buffer == "b":
                print("Backward")
                led.on()
                self.drive("b")
                time.sleep(3)
                self.drive("s")
                led.off()
            elif buffer == "LED_ON":
                led.on()
            elif buffer == "LED_OFF":
                led.off()

BLEController()
while True:
    time.sleep(1)
