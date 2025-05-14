## NEMO
NEMO is a Raspberry Pi Pico-based robotics project designed for demonstrations and educational purposes. It integrates hardware and open source software components to create an interactive robotic system controllable by a Web Application.

<img src="https://github.com/tiagomiguelcs/NEMO/blob/master/frontend/public/NEMO.png?raw=true" width="25%"/>

This project is organized into distinct directories:
- `backend`: Contains the core logic and express Web services for the robot, including a Python script that establishes a Bluetooth communication and sends control commands.
- `frontend`: Houses React components to control the robot.
- `rpiw`: Includes MicroPython code for the Raspberry Pi Zero that facilitates communication between the robotic platform and the Raspberry Pi, enabling motor control.

### Hardware

- [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/)
- [Kitronik-Pico-Robotics-Board](https://github.com/tiagomiguelcs/NEMO/blob/master/rpiw/datasheet.pdf)
