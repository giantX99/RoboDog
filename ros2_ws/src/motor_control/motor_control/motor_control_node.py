import time
import board    # Library from Adafruit to simplify access to raspberry pi GPIO pins
import busio    # Library from Adafruit to simplify access I2C, SPI, and UART
from adafruit_pca9685 import PCA9685    # Library from Adafruit for the PCA9685 Board to send PWM signals 
import rclpy
from rclpy.node import Node

class MotorControlNode(Node):
    def __init__(self):
        super().__init__('motor_control_node')
        # Initialize I2C
        self.i2c = busio.I2C(board.SCL, board.SDA)  # SCL and SDA are pins GPIO2 and GPIO3 respectively in the Pi
        self.pca = PCA9685(self.i2c)                # Sets the Pi pins id to the PCA9685 Board
        self.pca.frequency = 60                     # Determines the PWM signal frequency

        # Set servo to initial position
        self.set_servo_angle(0, 90)  # Channel 0, 90 degrees

    def set_servo_angle(self, channel, angle):
        pulse_width = int((angle / 180.0) * 2000 + 500)  # Convert angle to pulse width acceptable to the PCA board
        self.pca.channels[channel].duty_cycle = pulse_width


def main(args=None):
    # Initialize Node
    rclpy.init(args=args)
    motor_control_node = MotorControlNode()

    # Implement Logic Here
    try:
        while rclpy.ok():
            rclpy.spin_once(motor_control_node) # process callback
            # Implement Logic Here

    except KeyboardInterrupt:
        pass
    
    # Destroy Node
    motor_control_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
