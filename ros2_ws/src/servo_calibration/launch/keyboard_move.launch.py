# servo_calibration/launch/servo_calibration_launch.py
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, LogInfo
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    # Declare launch argument
    run_i2c_pwmcontroller = DeclareLaunchArgument(
        'run_i2c_pwmcontroller', 
        default_value='false',
        description='Whether to run the i2cpwm_controller node'
    )
    
    # Define nodes to launch
    servo_move_keyboard_node = Node(
        package='servo_calibration',  # updated package name
        executable='servoMoveKeyboard.py',
        name='servo_move_keyboard_node',
        output='screen'
    )

    i2cpwm_board_node = Node(
        package='i2cpwm_controller',
        executable='i2cpwm_controller_node',
        name='i2cpwm_controller_node',
        output='screen',
        condition=IfCondition(LaunchConfiguration('run_i2c_pwmcontroller'))
    )

    # Launch description
    return LaunchDescription([
        run_i2c_pwmboard,
        LogInfo(condition=IfCondition(LaunchConfiguration('run_i2c_pwmcontroller')),
                msg="Running i2cpwm_controller node..."),
        servo_move_keyboard_node,
        i2cpwm_board_node
    ])
