from setuptools import find_packages, setup

package_name = 'keyboard_teleop'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='robodog',
    maintainer_email='gat7hb@umsystem.edu',
    description='ROS 2 package for keyboard teleop for RoboDog interacting with motion_cmd package',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'keyboard_teleop_node = keyboard_teleop.keyboard_control:main'
        ],
    },
)
