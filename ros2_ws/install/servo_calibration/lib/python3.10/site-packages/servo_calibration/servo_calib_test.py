#!/usr/bin/python

"""
Class for testing control of 12 servos. It assumes i2cpwm_controller has been
installed
"""
import rclpy
from rclpy.node import Node
import sys, select, termios, tty # For terminal keyboard key press reading
from i2cpwm_controller.msg import Servo, ServoArray, ServoConfig, ServoConfigArray
from i2cpwm_controller.srv import ServosConfig

# Global variable for number of servos
numServos = 1

msg = """
Servo Control Module for 12 Servos.

Enter one of the following options:
-----------------------------
quit: stop and quit the program
oneServo: Move one servo manually, all others will be commanded to their center position
allServos: Move all servo's manually together

Keyboard commands for One Servo Control 
---------------------------
   q            t   y   u
            f   g       j   k
                b   n   m

  q: Quit current command mode and go back to Option Select
  t: Command servo min value
  y: Command servo center value
  u: Command servo max value
  f: Manually decrease servo command value by 10
  g: Manually decrease servo command value by 1
  j: Manually increase servo command value by 1
  k: Manually increase servo command value by 10
  b: Save new min command value
  n: Save new center command value
  m: Save new max command value


  anything else : Prompt again for command


CTRL-C to quit
"""
# Dictionary with anonomous helper functions to execute key commands
keyDict = {
    'q': None,
    't': lambda x: x.set_value(x._min),
    'y': lambda x: x.set_value(x._center),
    'u': lambda x: x.set_value(x._max),
    'f': lambda x: x.set_value(x.value - 0.01),
    'g': lambda x: x.set_value(x.value - 0.1),
    'j': lambda x: x.set_value(x.value + 0.1),
    'k': lambda x: x.set_value(x.value + 0.01),
    'b': lambda x: x.set_min(x.value),
    'n': lambda x: x.set_center(x.value),
    'm': lambda x: x.set_max(x.value),
}

validCmds = ['quit','oneServo','allServos']

class ServoConvert():
    '''
    ServoConvert Class encapsulates a servo 
    Servo has a center value, and range, and is commanded by a value between 0 and 4095.
    This coorsponds to the duty cycle in a 12 bit pwm cycle. Nominally, a servo is commanded with pulses of
    1 to 2 ms in a 20 ms cycle, with 1.5 ms being the value for center position. 
    These nominal values would coorespond to integer values of approximately 204, 306, and 409
    for 1 ms, 1.5 ms, and 2 ms, respectively
    '''
    def __init__(self, id=1, center_value=0, direction=1):
        self.value      = float(center_value)
        self._center    = float(center_value)
        self._min       = float(-1)
        self._max       = float(1)
        self._dir       = float(direction)
        self.id         = id

    def set_value(self, value_in):
        '''
        Set Servo value
        Input: Value between 0 and 4095
        '''
        if False:
            print('Servo value not in range [0,4095]')
        else:
            self.value = value_in

    def set_center(self,center_val):
        '''
        Set Servo center value
        Input: Value between 0 and 4095
        '''
        if False:
            print('Servo value not in range [0,4095]')
        else:
            self._center = center_val
            print('Servo %2i center set to %4i'%(self.id+1,center_val))

    def set_max(self,max_val):
        '''
        Set Servo max value
        Input: Value between 0 and 4095
        '''
        if False:
            print('Servo value not in range [0,4095]')
        else:
            self._max = max_val
            print('Servo %2i max set to %4i'%(self.id+1,max_val))

    def set_min(self,min_val):
        '''
        Set Servo min value
        Input: Value between 0 and 4095
        '''
        if False:
            print('Servo value not in range [0,4095]')
        else:
            self._min = min_val
            print('Servo %2i min set to %4i'%(self.id+1,min_val))


class SpotMicroServoControl(Node):
    def __init__(self):
        super().__init__('test_servo_control')

        # Create a ServoConfig messag for one servo
        self._servo_config_msg = ServoConfigArray()
        self._servo1_config = ServoConfig()

        self._servo1_config.center = 300
        self._servo1_config.range = 400
        self._servo1_config.servo = 1
        self._servo1_config.direction = 1

        self._servo_config_msg.servos.append(self._servo1_config)

        self.get_logger().info("> Waiting for config_servos service...")
        print('test1')

        # Wait for the config_servos service to be available
        self.servos_config_client = self.create_client(ServosConfig, 'config_servos')
        while not self.servos_config_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.get_logger().info("> Config_servos service found!")
        
        print('test2')
        # Call the service
        try:
            request = ServosConfig.Request()
            request.servos = self._servo_config_msg.servos
            future = self.servos_config_client.call_async(request)
            rclpy.spin_until_future_complete(self, future)
            if future.result() is not None:
                self.get_logger().info("Config servos done!!")
            else:
                self.get_logger().error("Failed to call service config_servos")
        except Exception as e:
            self.get_logger().error(f"Service call failed: {e}")

        
        self.get_logger().info("Setting Up the Spot Micro Servo Control Node...")

        # Create a servo dictionary with 12 ServoConvert objects
        # keys: integers 0 through 11
        # values: ServoConvert objects
        self.servos = {i : ServoConvert(id=i) for i in range(numServos)}
        self.get_logger().info("> Servos correctly initialized")

        # Create empty ServoArray message with n number of Servos in its array
        self._servo_array_msg = ServoArray()
        self._servo_array_msg.servos = [Servo() for _ in range(numServos)]
        
        # Create the servo array publisher
        self.ros_pub_servo_array = self.create_publisher(ServoArray, "/servos_proportional", 1)
        self.get_logger().info("> Publisher corrrectly initialized")

        self.get_logger().info("Initialization complete")

        # Setup terminal input reading, taken from teleop_twist_keyboard
        self.settings = termios.tcgetattr(sys.stdin)


    def send_servo_msg(self):
        for servo_key, servo_obj in self.servos.items():
            self._servo_array_msg.servos[servo_obj.id].servo = servo_obj.id + 1
            self._servo_array_msg.servos[servo_obj.id].value = servo_obj.value
            self.get_logger().info(f"Sending to {servo_key} command {servo_obj.value}")

        self.ros_pub_servo_array.publish(self._servo_array_msg)

    def reset_all_servos_center(self):
        '''
        Reset all servos to their center value
        '''
        for s in self.servos:
            self.servos[s].value = self.servos[s]._center
    
    def getKey(self):
        tty.setraw(sys.stdin.fileno())
        select.select([sys.stdin], [], [], 0)
        key = sys.stdin.read(1)
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, self.settings)
        return key

    def run(self):

        # Set all servos to their center values
        self.reset_all_servos_center()
        self.send_servo_msg()

        # Prompt user with keyboard command information
        # Ability to control individual servo to find limits and center values
        # and ability to control all servos together
        
        while rclpy.ok():
            print(msg)
            userInput = input("Command?: ")

            if userInput not in validCmds:
                print('Valid command not entered, try again...')
            
            else:
                if userInput == 'quit':
                    print("Ending program...")
                    print('Final Servo Values')
                    print('--------------------')
                    for i in range(numServos):
                        servo = self.servos[i]
                        print(f"Servo {i + 1}:   Min: {servo._min},   Center: {servo._center},   Max: {servo._max}")                    
                    break

                elif userInput == 'oneServo':
                    # Reset all servos to center value, and send command
                    self.reset_all_servos_center()
                    self.send_servo_msg()

                    # First get servo number to command
                    nSrv = -1
                    while (1):
                        userInput = int( input('Which servo to control? Enter a number 1 through 12: ') )
                        
                        if userInput not in range(1, numServos + 1):
                            print("Invalid servo number entered, try again")
                        else:
                            nSrv = userInput - 1
                            break

                    # Loop and act on user command
                    print('Enter command, q to go back to option select: ')
                    while (1):
                       
                        userInput = self.getKey()

                        if userInput == 'q':
                            break
                        elif userInput not in keyDict:
                            print('Key not in valid key commands, try again')
                        else:
                            keyDict[userInput](self.servos[nSrv])
                            print(f"Servo {nSrv + 1} cmd: {self.servos[nSrv].value}")
                            self.send_servo_msg()

                elif userInput == 'allServos':
                    # Reset all servos to center value, and send command
                    self.reset_all_servos_center()
                    self.send_servo_msg()

                    print('Enter command, q to go back to option select: ')                   
                    while (1):

                        userInput = self.getKey()

                        if userInput == 'q':
                            break
                        elif userInput not in keyDict:
                            print('Key not in valid key commands, try again')
                        elif userInput in ('b','n','m'):
                            print('Saving values not supported in all servo control mode')
                        else:
                            for s in self.servos.values():
                                keyDict[userInput](s)
                            print('All Servos Commanded')
                            self.send_servo_msg()
                                
            # Set the control rate in Hz
            rclpy.spin_once(self, timeout_sec=0.1)


def main(args=None):
    rclpy.init(args=args)
    smsc = SpotMicroServoControl()
    try:
        smsc.run()
        smsc.destroy_node()
        rclpy.shutdown()
    except KeyboardInterrupt:
        print("KeyboardInterrupt received! Shutting down...")
    finally:
        smsc.destroy_node()
        rclpy.shutdown()

if __name__ == "__main__":
    main()