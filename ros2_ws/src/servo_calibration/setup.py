from setuptools import find_packages, setup

package_name = 'servo_calibration'

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
    description='Package for servo calibration, keyboard controlled',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            # 'servo_calib_node = servo_calibration.servo_move_keyboard:main' # Move Servos Script
            # 'servo_calib_node = servo_calibration.servo_calib_test:main' # Calibration Script
            'servo_calib_node = servo_calibration.calibrate:main' # Utilized calibration script 
        ],
    },
)
