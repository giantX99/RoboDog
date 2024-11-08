from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description(): 

    return LaunchDescription([
        Node(
            package='i2cpwm_controller',
            executable='i2cpwm_controller_node',
            name='i2cpwm_controller_node',
            output='screen',
        )
    ])
