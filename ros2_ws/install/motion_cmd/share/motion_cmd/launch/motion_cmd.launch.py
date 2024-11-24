from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, GroupAction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.conditions import IfCondition
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    # Declare the arguments for the launch file
    return LaunchDescription([
        # DeclareLaunchArgument(
        #     'run_standalone',
        #     default_value='false',
        #     description='Run without i2cpwm_controller node'
        # ),
        DeclareLaunchArgument(
            'debug_mode',
            default_value='false',
            description='Enable debug mode'
        ),
        DeclareLaunchArgument(
            'run_lcd',
            default_value='false',
            description='Run LCD monitor node'
        ),

        # # i2cpwm_controller node (only runs if run_standalone is false)
        # Node(
        #     package='i2cpwm_controller',
        #     executable='i2cpwm_controller_node',
        #     name='i2cpwm_controller_node',
        #     output='screen',
        #     condition=IfCondition(LaunchConfiguration('run_standalone'))
        # ),

        # Spot Micro Motion Command node
        Node(
            package='motion_cmd',
            executable='motion_cmd_node',
            name='motion_cmd_node',
            output='screen',
            parameters=[
                # os.path.join(
                #     get_package_share_directory('motion_cmd'),
                #     'config',
                #     'motion_cmd.yaml'
                # ),
                {
                    'debug_mode': LaunchConfiguration('debug_mode'),
                    # 'run_standalone': LaunchConfiguration('run_standalone')
                }
            ]
        ),

        # LCD monitor node (only runs if run_lcd is true)
        GroupAction([
            Node(
                package='lcd_monitor',
                executable='lcd_monitor',
                name='lcd_monitor_node',
                output='screen'
            )
        ], condition=IfCondition(LaunchConfiguration('run_lcd')))
    ])
