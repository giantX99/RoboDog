import time
import board
import busio
from adafruit_pca9685 import PCA9685
import rclpy
from rclpy.node import Node

class MotorControlNode(Node):
    def __init__(self):
        super().__init__('motor_control_node')
        # Initialize I2C
        self.i2c = busio.I2C(board.SCL, board.SDA)
        self.pca = PCA9685(self.i2c)
        self.pca.frequency = 60

        # Set servo to initial position
        self.set_servo_angle(0, 90)  # Channel 0, 90 degrees

    def set_servo_angle(self, channel, angle):
        pulse_width = int((angle / 180.0) * 2000 + 500)  # Convert angle to pulse width
        self.pca.channels[channel].duty_cycle = pulse_width

def main(args=None):
    rclpy.init(args=args)
    motor_control_node = MotorControlNode()
    rclpy.spin(motor_control_node)
    motor_control_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
