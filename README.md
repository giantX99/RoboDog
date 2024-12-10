
# RoboDog Project

Welcome to the RoboDog Project repository, developed as part of the Electrical & Computer Engineering Capstone Project for FY2024. This project involves the design and implementation of a robotic dog controlled by a Raspberry Pi 4 running Ubuntu 22.04 and ROS 2 Humble Hawksbill.

## Table of Contents

- [Project Overview](#project-overview)
- [Hardware Setup](#hardware-setup)
- [Software Installation](#software-installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Project Overview

The RoboDog Project aims to create an agile and responsive quadruped robot capable of performing various movements and tasks. The system leverages the Robot Operating System (ROS) 2 framework for modularity and scalability, enabling advanced functionalities to be implemented such as autonomous navigation and obstacle avoidance.

## Software Installation

1. **Install Ubuntu 22.04 on Raspberry Pi 4**:
   - Download the Ubuntu 22.04 image for Raspberry Pi from the official Ubuntu website.
   - Flash the image to an SD card using tools like `Raspberry Pi Imager` or `balenaEtcher`.
   - Insert the SD card into the Raspberry Pi and power it on.

2. **Set Up ROS 2 Humble Hawksbill**:
   - Follow the official ROS 2 installation guide for Ubuntu 22.04 to install the Humble Hawksbill distribution.
   - Ensure that the ROS 2 environment is properly sourced by adding the following line to your `.bashrc` file:
     ```bash
     source /opt/ros/humble/setup.bash
     ```

3. **Clone the RoboDog Repository**:
   - Open a terminal and execute:
     ```bash
     git clone https://github.com/giantX99/RoboDog.git
     cd RoboDog/ros2_ws
     ```

4. **Install Dependencies**:
   - Use `rosdep` to install necessary dependencies:
     ```bash
     sudo apt update
     rosdep update
     rosdep install --from-paths src --ignore-src -r -y
     ```

5. **Build the Workspace**:
   - Compile the ROS 2 packages:
     ```bash
     colcon build
     ```
   - Source the workspace:
     ```bash
     source install/setup.bash
     ```

## Usage

1. **Launching the RoboDog Nodes**:
   - After building the workspace and sourcing the setup file, launch the main 2 RoboDog packages in 2 different terminals:
     ```bash
     ros2 launch i2cpwm_controller i2cpwm_controller.launch.py
     ```
     ```bash
     ros2 launch motion_cmd motion_cmd.launch.py
     ```
   - This command initializes the core nodes responsible for controlling the RoboDog's movements and sensor data processing.

2. **Controlling the RoboDog**:
   - Utilize ROS 2 topics and services to send commands to the RoboDog.
   - For manual control, you can use a joystick or keyboard teleoperation node:
     ```bash
     ros2 run keyboard_teleop keyboard_teleop_node
     ```

## Contributing

Contributions to the RoboDog Project are welcome. To contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Create a new Pull Request.

For more detailed documentation, please refer to the `docs` directory within this repository.
