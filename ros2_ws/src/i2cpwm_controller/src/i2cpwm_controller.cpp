#include "i2cpwm_controller.h"
#include <cstdio>

// Global variables
#define MAX_BOARDS 62
#define MAX_SERVOS (16 * MAX_BOARDS)

// UTILS:

// Enums for drive modes and positions
enum drive_modes {
    MODE_UNDEFINED = 0,
    MODE_ACKERMAN = 1,
    MODE_DIFFERENTIAL = 2,
    MODE_MECANUM = 3,
    MODE_INVALID = 4
};

enum drive_mode_positions {
    POSITION_UNDEFINED = 0,
    POSITION_LEFTFRONT = 1,
    POSITION_RIGHTFRONT = 2,
    POSITION_LEFTREAR = 3,
    POSITION_RIGHTREAR = 4,
    POSITION_INVALID = 5
};

// Constants
#define _BASE_ADDR 0x40
#ifndef _PI
#define _PI 3.14159265358979323846
#endif
#define _CONST(s) ((char*)(s))

// Enum for PWM registers
enum pwm_regs {
    __MODE1 = 0x00,
    __MODE2 = 0x01,
    __SUBADR1 = 0x02,
    __SUBADR2 = 0x03,
    __SUBADR3 = 0x04,
    __PRESCALE = 0xFE,
    __CHANNEL_ON_L = 0x06,
    __CHANNEL_ON_H = 0x07,
    __CHANNEL_OFF_L = 0x08,
    __CHANNEL_OFF_H = 0x09,
    __ALL_CHANNELS_ON_L = 0xFA,
    __ALL_CHANNELS_ON_H = 0xFB,
    __ALL_CHANNELS_OFF_L = 0xFC,
    __ALL_CHANNELS_OFF_H = 0xFD,
    __RESTART = 0x80,
    __SLEEP = 0x10,
    __ALLCALL = 0x01,
    __INVRT = 0x10,
    __OUTDRV = 0x04
};


//* ------------------------------------------------------------------------------------------------------------------------------------
// local private methods
//* ------------------------------------------------------------------------------------------------------------------------------------

// Utility functions
static float _abs(float v1) {
    return v1 < 0 ? -v1 : v1;
}

static float _min(float v1, float v2) {
    return v1 > v2 ? v2 : v1;
}

static float _max(float v1, float v2) {
    return v1 < v2 ? v2 : v1;
}

static float _absmin(float v1, float v2) {
    float a1 = _abs(v1);
    float a2 = _abs(v2);
    return a1 > a2 ? v2 : v1;
}

static float _absmax(float v1, float v2) {
    float a1 = _abs(v1);
    float a2 = _abs(v2);
    return a1 < a2 ? v2 : v1;
}
/////////////////////////////////////////////////////////////////////////////////////



// Constructor
I2cPwmController::I2cPwmController(const rclcpp::NodeOptions &options)
    : Node("i2cpwm_controller", options) {

    /* initialize all of the global data objects */
    for (int i=0; i<MAX_BOARDS;i++)
        _pwm_boards[i] = -1;
    _active_board = -1;

    // Initialize all servo configurations to default values
    for (int i = 0; i < MAX_SERVOS; ++i) {
        _servo_configs[i].center = -1;
        _servo_configs[i].range = -1;
        _servo_configs[i].direction = 1;
        _servo_configs[i].mode_pos = -1;
    }
    _last_servo = -1;

    // Initialize drive mode with undefined values
    _active_drive.mode = MODE_UNDEFINED;
    _active_drive.rpm = -1.0;
    _active_drive.radius = -1.0;
    _active_drive.track = -1.0;
    _active_drive.scale = -1.0;

    
    // Try to Load parameters from configuration
    try {
        load_configuration_from_parameters();
    } catch (const std::runtime_error &e) {
        RCLCPP_ERROR(get_logger(), "Initialization failed: %s", e.what());
        throw;
    }

    // Initialize subscriptions
    servos_absolute_sub_ = this->create_subscription<i2cpwm_controller::msg::ServoArray>(
        "servos_absolute", 500, std::bind(&I2cPwmController::servos_absolute, this, std::placeholders::_1));

    servos_proportional_sub_ = this->create_subscription<i2cpwm_controller::msg::ServoArray>(
        "servos_proportional", 500, std::bind(&I2cPwmController::servos_proportional, this, std::placeholders::_1));

    servos_drive_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
        "servos_drive", 500, std::bind(&I2cPwmController::servos_drive, this, std::placeholders::_1));

    // Initialize services
    set_pwm_frequency_srv_ = this->create_service<i2cpwm_controller::srv::IntValue>(
        "set_pwm_frequency", std::bind(&I2cPwmController::set_pwm_frequency, this, std::placeholders::_1, std::placeholders::_2));

    config_servos_srv_ = this->create_service<i2cpwm_controller::srv::ServosConfig>(
        "config_servos", std::bind(&I2cPwmController::config_servos, this, std::placeholders::_1, std::placeholders::_2));

    config_drive_mode_srv_ = this->create_service<i2cpwm_controller::srv::DriveMode>(
        "config_drive_mode", std::bind(&I2cPwmController::config_drive_mode, this, std::placeholders::_1, std::placeholders::_2));

    stop_servos_srv_ = this->create_service<std_srvs::srv::Empty>(
        "stop_servos", std::bind(&I2cPwmController::stop_servos, this, std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(get_logger(), "I2cPwmController initialized.");
}

// Destructor
I2cPwmController::~I2cPwmController() {
    if (_controller_io_handle >= 0) {
        close(_controller_io_handle);
        RCLCPP_INFO(get_logger(), "I2C handle closed successfully.");
    } else {
        RCLCPP_WARN(get_logger(), "I2C handle was already closed or invalid.");
    }
}

// Callback: Absolute Servo Movement
void I2cPwmController::servos_absolute(const i2cpwm_controller::msg::ServoArray::SharedPtr msg) {
    for (const auto &servo : msg->servos) {
        int value = servo.value;
        if (value < 0 || value > 4096) {
            RCLCPP_ERROR(get_logger(), "Invalid PWM value %d. Must be between 0 and 4096", value);
            continue;
        }
        _set_pwm_interval(servo.servo, 0, value);
        RCLCPP_DEBUG(get_logger(),"servo[%d] = %d", servo.servo, value);
    }
}

// Callback: Proportional Servo Movement
void I2cPwmController::servos_proportional(const i2cpwm_controller::msg::ServoArray::SharedPtr msg) {
    for (const auto &servo : msg->servos) {
        float value = servo.value;
        _set_pwm_interval_proportional(servo.servo, value);
    }
}

// Callback: Drive Servo Control
void I2cPwmController::servos_drive(const geometry_msgs::msg::Twist::SharedPtr msg) {
    /* this subscription works on the active_board */
	int i;
	float delta, range, ratio;
	float temp_x, temp_y, temp_r;
	float dir_x, dir_y, dir_r;
	float speed[4];
	
	/* msg is a pointer to a Twist message: msg->linear and msg->angular each of which have members .x .y .z */
	/* the subscriber uses the maths from: http://robotsforroboticists.com/drive-kinematics/ */	

	RCLCPP_DEBUG(get_logger(), "servos_drive Twist = [%5.2f %5.2f %5.2f] [%5.2f %5.2f %5.2f]", 
			 msg->linear.x, msg->linear.y, msg->linear.z, msg->angular.x, msg->angular.y, msg->angular.z);

	if (_active_drive.mode == MODE_UNDEFINED) {
		RCLCPP_ERROR(get_logger(), "drive mode not set");
		throw std::runtime_error("drive mode not set");
	}
	if ((_active_drive.mode < MODE_UNDEFINED) || (_active_drive.mode >= MODE_INVALID)) {
		RCLCPP_ERROR(get_logger(), "unrecognized drive mode set %d", _active_drive.mode);
		throw std::runtime_error("unrecognized drive mode set");
	}

	dir_x = ((msg->linear.x  < 0) ? -1 : 1);
	dir_y = ((msg->linear.y  < 0) ? -1 : 1);
	dir_r = ((msg->angular.z < 0) ? -1 : 1);

	temp_x = _active_drive.scale * _abs(msg->linear.x);
	temp_y = _active_drive.scale * _abs(msg->linear.y);
	temp_r = _abs(msg->angular.z);	// radians
		
	// temp_x = _smoothing (temp_x);
	// temp_y = _smoothing (temp_y);
	// temp_r = _smoothing (temp_r) / 2;

	// the differential rate is the robot rotational circumference / angular velocity
	// since the differential rate is applied to both sides in opposite amounts it is halved
	delta = (_active_drive.track / 2) * temp_r;
	// delta is now in meters/sec

	// determine if we will over-speed the motor and scal accordingly
	ratio = _convert_mps_to_proportional(temp_x + delta);
	if (ratio > 1.0)
		temp_x /= ratio;

	
	switch (_active_drive.mode) {

	case MODE_ACKERMAN:
		/*
		  with ackerman drive, steering is handled by a separate servo
		  we drive assigned servos exclusively by the linear.x
		*/
		speed[0] = temp_x * dir_x;
		speed[0] = _convert_mps_to_proportional(speed[0]);
		if (_abs(speed[0]) > 1.0)
			speed[0] = 1.0 * dir_x;
		
		RCLCPP_DEBUG(get_logger(), "ackerman drive mode speed=%6.4f", speed[0]);
		break;

	case MODE_DIFFERENTIAL:
		/*
		  with differential drive, steering is handled by the relative speed of left and right servos
		  we drive assigned servos by mixing linear.x and angular.z
		  we compute the delta for left and right components
		  we use the sign of the angular velocity to determine which is the faster / slower
		*/

		/* the delta is the angular velocity * half the drive track */
		
		if (dir_r > 0) {	// turning right
			speed[0] = (temp_x + delta) * dir_x;
			speed[1] = (temp_x - delta) * dir_x;
		} else {		// turning left
			speed[0] = (temp_x - delta) * dir_x;
			speed[1] = (temp_x + delta) * dir_x;
		}

		RCLCPP_DEBUG(get_logger(), "computed differential drive mode speed left=%6.4f right=%6.4f", speed[0], speed[1]);

		/* if any of the results are greater that 1.0, we need to scale all the results down */
		range = _max (_abs(speed[0]), _abs(speed[1]));
		
		ratio = _convert_mps_to_proportional(range);
		if (ratio > 1.0) {
			speed[0] /= ratio;
			speed[1] /= ratio;
		}
		RCLCPP_DEBUG(get_logger(), "adjusted differential drive mode speed left=%6.4f right=%6.4f", speed[0], speed[1]);

		speed[0] = _convert_mps_to_proportional(speed[0]);
		speed[1] = _convert_mps_to_proportional(speed[1]);

		RCLCPP_DEBUG(get_logger(), "differential drive mode speed left=%6.4f right=%6.4f", speed[0], speed[1]);
		break;

	case MODE_MECANUM:
		/*
		  with mecanum drive, steering is handled by the relative speed of left and right servos
		  with mecanum drive, lateral motion is handled by the rotation of front and rear servos
		  we drive assigned servos by mixing linear.x and angular.z  and linear.y
		*/

		if (dir_r > 0) {	// turning right
			speed[0] = speed[2] = (temp_x + delta) * dir_x;
			speed[1] = speed[3] = (temp_x - delta) * dir_x;
		} else {		// turning left
			speed[0] = speed[2] = (temp_x - delta) * dir_x;
			speed[1] = speed[3] = (temp_x + delta) * dir_x;
		}

		speed[0] += temp_y * dir_y;
		speed[3] += temp_y * dir_y;
		speed[1] -= temp_y * dir_y;
		speed[2] -= temp_y * dir_y;
		RCLCPP_DEBUG(get_logger(), "computed mecanum drive mode speed leftfront=%6.4f rightfront=%6.4f leftrear=%6.4f rightreer=%6.4f", speed[0], speed[1], speed[2], speed[3]);

		range = _max (_max (_max (_abs(speed[0]), _abs(speed[1])), _abs(speed[2])), _abs(speed[3]));
		ratio = _convert_mps_to_proportional(range);
		if (ratio > 1.0) {
			speed[0] /= ratio;
			speed[1] /= ratio;
			speed[2] /= ratio;
			speed[3] /= ratio;
		}
		RCLCPP_DEBUG(get_logger(), "adjusted mecanum drive mode speed leftfront=%6.4f rightfront=%6.4f leftrear=%6.4f rightreer=%6.4f", speed[0], speed[1], speed[2], speed[3]);

		speed[0] = _convert_mps_to_proportional(speed[0]);
		speed[1] = _convert_mps_to_proportional(speed[1]);
		speed[2] = _convert_mps_to_proportional(speed[2]);
		speed[3] = _convert_mps_to_proportional(speed[3]);

		RCLCPP_DEBUG(get_logger(), "mecanum drive mode speed leftfront=%6.4f rightfront=%6.4f leftrear=%6.4f rightreer=%6.4f", speed[0], speed[1], speed[2], speed[3]);
		break;

	default:
		break;

	}
	
	/* find all drive servos and set their new speed */
	for (i=0; i<(_last_servo); i++) {
		// we use 'fall thru' on the switch statement to allow all necessary servos to be controlled
		switch (_active_drive.mode) {
		case MODE_MECANUM:
			if (_servo_configs[i].mode_pos == POSITION_RIGHTREAR)
				_set_pwm_interval_proportional (i+1, speed[3]);
			if (_servo_configs[i].mode_pos == POSITION_LEFTREAR)
				_set_pwm_interval_proportional (i+1, speed[2]);
		case MODE_DIFFERENTIAL:
			if (_servo_configs[i].mode_pos == POSITION_RIGHTFRONT)
			    _set_pwm_interval_proportional (i+1, speed[1]);
		case MODE_ACKERMAN:
			if (_servo_configs[i].mode_pos == POSITION_LEFTFRONT)
				_set_pwm_interval_proportional (i+1, speed[0]);
		}
	}
}

// Service Callback: Set PWM Frequency
bool I2cPwmController::set_pwm_frequency(const std::shared_ptr<i2cpwm_controller::srv::IntValue::Request> req,
                                         std::shared_ptr<i2cpwm_controller::srv::IntValue::Response> res) {
    int freq = req->value;
    if (freq < 12 || freq > 1024) {
        RCLCPP_ERROR(get_logger(), "Invalid PWM frequency %d. Must be between 12 and 1024", freq);
        freq = 50;  // Set to default if invalid
    }
    _set_pwm_frequency(freq);
    res->error = freq;
    return true;
}

// Service Callback: Configure Servos
bool I2cPwmController::config_servos(const std::shared_ptr<i2cpwm_controller::srv::ServosConfig::Request> req,
                                     std::shared_ptr<i2cpwm_controller::srv::ServosConfig::Response> res) {
    
    res->error = 0;
	if ((_active_board<1) || (_active_board>62)) {
		RCLCPP_ERROR(get_logger(), "Internal error - invalid board number %d :: PWM board numbers must be between 1 and 62", _active_board);
		res->error = -1;
		return true;
	}

    for (const auto &servo_config : req->servos) {
        _config_servo(servo_config.servo, servo_config.center, servo_config.range, servo_config.direction);
    }
    return true;
}

// Service Callback: Configure Drive Mode
bool I2cPwmController::config_drive_mode(const std::shared_ptr<i2cpwm_controller::srv::DriveMode::Request> req,
                                         std::shared_ptr<i2cpwm_controller::srv::DriveMode::Response> res) {
    // Initialize the response error code
    res->error = 0;

    // Configure the drive mode (mode, rpm, radius, track, scale)
    int error = _config_drive_mode(req->mode, req->rpm, req->radius, req->track, req->scale);
    if (error != 0) {
        res->error = error;
        RCLCPP_ERROR(get_logger(), "Failed to configure drive mode");
        return true;  // Error occurred, returning early
    }

    // Iterate over the servos and configure their positions
    for (size_t i = 0; i < req->servos.size(); ++i) {
        int servo = req->servos[i].servo;
        int position = req->servos[i].position;

        // Attempt to configure each servo's position
        if (_config_servo_position(servo, position) != 0) {
            // If configuration fails, log the error and set the response error to the servo number
            RCLCPP_ERROR(get_logger(), "Failed to configure servo #%d to position %d", servo, position);
            res->error = servo;  // Set error to the failing servo ID
        }
    }

    // Return true indicating the service execution is complete
    return true;
}

// Service Callback: Stop All Servos
bool I2cPwmController::stop_servos(const std::shared_ptr<std_srvs::srv::Empty::Request> req,
                                   std::shared_ptr<std_srvs::srv::Empty::Response> res) {
    int save_active = _active_board;

    for (int i = 0; i < MAX_BOARDS; ++i) {
        if (_pwm_boards[i] > 0) {
            _set_active_board(i + 1); // Boards are 1-based
            _set_pwm_interval_all(0, 0);
        }
    }
    _set_active_board (save_active);
    return true;
}



// Private methods:

/**
 \private method to smooth a speed value
 
 we calculate each speed using a cosine 'curve',  this results in the output curve 
 being shallow at 'stop', full forward, and full reverse and becoming 
 more aggressive in the middle or each direction

 @param speed an int value (±1.0) indicating original speed
 @returns an integer value (±1.0) smoothed for more gentle acceleration
 */
int I2cPwmController::_smoothing (float speed)
{
	/* if smoothing is desired, then remove the commented code  */
	// speed = (cos(_PI*(((float)1.0 - speed))) + 1) / 2;
	return speed;
}


/**
   \private method to convert meters per second to a proportional value in the range of ±1.0
 
   @param speed float requested speed in meters per second
   @returns float value (±1.0) for servo speed
 */
float I2cPwmController::_convert_mps_to_proportional (float speed)
{
	/* we use the drive mouter output rpm and wheel radius to compute the conversion */

	float initial, max_rate;	// the max m/s is ((rpm/60) * (2*PI*radius))

	initial = speed;
	
	if (_active_drive.rpm <= 0.0) {
        RCLCPP_ERROR(get_logger(), "Invalid active drive mode RPM %6.4f :: RPM must be greater than 0", _active_drive.rpm);
		return 0.0;
	}
	if (_active_drive.radius <= 0.0) {
        RCLCPP_ERROR(get_logger(), "Invalid active drive mode radius %6.4f :: wheel radius must be greater than 0", _active_drive.radius);
		return 0.0;
	}

	max_rate = (_active_drive.radius * _PI * 2) * (_active_drive.rpm / 60.0);

	speed = speed / max_rate;
	// speed = _absmin (speed, 1.0);

	RCLCPP_DEBUG(get_logger(), "%6.4f = convert_mps_to_proportional ( speed(%6.4f) / ((radus(%6.4f) * pi(%6.4f) * 2) * (rpm(%6.4f) / 60.0)) )", speed, initial, _active_drive.radius, _PI, _active_drive.rpm);
	return speed;
}


/**
 * \private method to set a pulse frequency
 *
 *The pulse defined by start/stop will be active on all channels until any subsequent call changes it.
 *@param frequency an int value (1..15000) indicating the pulse frequency where 50 is typical for RC servos
 *Example _set_frequency (68)  // set the pulse frequency to 68Hz
 */ // PWM Control Logic
void I2cPwmController::_set_pwm_frequency(int freq) {
    // Direct conversion of PWM frequency setting logic from ROS 1
    // This should include the calculation of the prescale value and interaction with I2C
    int prescale;
    char oldmode, newmode;
    int res;

    I2cPwmController::_pwm_frequency = freq;   // save to global
    
	RCLCPP_DEBUG(get_logger(), "_set_pwm_frequency prescale");
    float prescaleval = 25000000.0; // 25MHz
    prescaleval /= 4096.0;
    prescaleval /= (float)freq;
    prescaleval -= 1.0;
    //RCLCPP_INFO(get_logger(), "Estimated pre-scale: %6.4f", prescaleval);
    prescale = floor(prescaleval + 0.5);
    // RCLCPP_INFO(get_logger(), "Final pre-scale: %d", prescale);


	RCLCPP_INFO(get_logger(), "Setting PWM frequency to %d Hz", freq);
    printf("Setting PWM frequency to %d Hz\n", freq);

    nanosleep ((const struct timespec[]){{1, 000000L}}, NULL); 


    oldmode = i2c_smbus_read_byte_data (_controller_io_handle, __MODE1);
    newmode = (oldmode & 0x7F) | 0x10; // sleep

    if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __MODE1, newmode) && DEBUG_MODE==false) // go to sleep
        RCLCPP_ERROR(get_logger(), "Unable to set PWM controller to sleep mode"); 
    else
        printf("Sent sleep mode byte data (%x) to address %x\n", newmode, __MODE1);

    if (0 >  i2c_smbus_write_byte_data(_controller_io_handle, __PRESCALE, (int)(floor(prescale))) && DEBUG_MODE==false)
        RCLCPP_ERROR(get_logger(), "Unable to set PWM controller prescale"); 
    else
        printf("Sent prescale data (%d) to address %x\n", (int)(floor(prescale)), __PRESCALE);

    if (0 > i2c_smbus_write_byte_data(_controller_io_handle, __MODE1, oldmode) && DEBUG_MODE==false)
        RCLCPP_ERROR(get_logger(), "Unable to set PWM controller to active mode"); 
    else
        printf("Sent active mode byte data (%x) to address %x\n", oldmode, __MODE1);


    nanosleep((const struct timespec[]){{0, 5000000L}}, NULL);   //sleep 5microsec,

    if (0 > i2c_smbus_write_byte_data(_controller_io_handle, __MODE1, oldmode | 0x80) && DEBUG_MODE==false)
        RCLCPP_ERROR(get_logger(), "Unable to restore PWM controller to active mode");
    else
        printf("Sent active mode byte data (%x) to address %x\n", (oldmode | 0x80), __MODE1);

}


/**
 * \private method to set a common value for all PWM channels on the active board
 *
 *The pulse defined by start/stop will be active on all channels until any subsequent call changes it.
 *@param start an int value (0..4096) indicating when the pulse will go high sending power to each channel.
 *@param end an int value (0..4096) indicating when the pulse will go low stoping power to each channel.
 *Example _set_pwm_interval_all (0, 108)   // set all servos with a pulse width of 105
 */
void I2cPwmController::_set_pwm_interval_all (int start, int end)
{
    // the public API is ONE based and hardware is ZERO based
    if ((_active_board<1) || (_active_board>62)) {
        RCLCPP_ERROR(get_logger(),"Internal error - invalid active board number %d :: PWM board numbers must be between 1 and 62", _active_board);
        throw std::runtime_error("Internal error - invalid active board number.");
    }
    int board = _active_board - 1;

    if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __ALL_CHANNELS_ON_L, start & 0xFF) && DEBUG_MODE==false)
        RCLCPP_ERROR (get_logger(), "Error setting PWM start low byte for all servos on board %d", _active_board);
    else
        printf("Sent PWM start LOW byte (%x) to all servos on board, address = %x\n", (start & 0xFF), __ALL_CHANNELS_ON_L);

    if (0 >  i2c_smbus_write_byte_data (_controller_io_handle, __ALL_CHANNELS_ON_H, start  >> 8) && DEBUG_MODE==false)
        RCLCPP_ERROR (get_logger(), "Error setting PWM start high byte for all servos on board %d", _active_board);
    else
        printf("Sent PWM start HIGH byte (%x) to all servos on board, address = %x\n", (start >> 8), __ALL_CHANNELS_ON_H);
    
    if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __ALL_CHANNELS_OFF_L, end & 0xFF) && DEBUG_MODE==false)
        RCLCPP_ERROR (get_logger(), "Error setting PWM end low byte for all servos on board %d", _active_board);
    else
        printf("Sent PWM end LOW byte (%x) to all servos on board, address = %x\n", (end & 0xFF), __ALL_CHANNELS_OFF_L);
    
    if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __ALL_CHANNELS_OFF_H, end >> 8) && DEBUG_MODE==false)
        RCLCPP_ERROR (get_logger(), "Error setting PWM end high byte for all servos on board %d", _active_board);
    else
        printf("Sent PWM end HIGH byte (%x) to all servos on board, address = %x\n", (end >> 8), __ALL_CHANNELS_OFF_H);
}


/**
 * \private method to set the active board
 *
 *@param board an int value (1..62) indicating which board to activate for subsequent service and topic subscription activity where 1 coresponds to the default board address of 0x40 and value increment up
 *Example _set_active_board (68)   // set the pulse frequency to 68Hz
 */
void I2cPwmController::_set_active_board (int board)
{
	char mode1res;

	if ((board<1) || (board>62)) {
        RCLCPP_ERROR(get_logger(), "Internal error :: invalid board number %d :: board numbers must be between 1 and 62", board);
        throw std::runtime_error("Internal error :: invalid board number");
    }
    if (_active_board != board) {
        _active_board = board;   // save to global
        
        // the public API is ONE based and hardware is ZERO based
        board--;
        
        if (0 > ioctl (_controller_io_handle, I2C_SLAVE, (_BASE_ADDR+(board))) && DEBUG_MODE==false) {
            RCLCPP_FATAL (get_logger(), "Failed to acquire bus access and/or talk to I2C slave at address 0x%02X", (_BASE_ADDR+board));
            throw std::runtime_error("Failed to acquire bus access and/or talk to I2C slave"); /* exit(1) */   /* additional ERROR HANDLING information is available with 'errno' */
        }

        if (_pwm_boards[board]<0) {
            _pwm_boards[board] = 1;

            /* this is guess but I believe the following needs to be done on each board only once */

            if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __MODE2, __OUTDRV) && DEBUG_MODE==false)
                RCLCPP_ERROR (get_logger(), "Failed to enable PWM outputs for totem-pole structure");
            else
                printf("Enabled PWM outputs for totem-pole structure; data_sent= %x ; address= %x\n", __OUTDRV, __MODE2);

            if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __MODE1, __ALLCALL) && DEBUG_MODE==false)
                RCLCPP_ERROR (get_logger(), "Failed to enable ALLCALL for PWM channels");
            else
                printf("Enabled ALLCALL for PWM channels; data_sent= %x ; address= %x\n", __ALLCALL, __MODE1);

            nanosleep ((const struct timespec[]){{0, 5000000L}}, NULL);   //sleep 5microsec, wait for osci


            mode1res = i2c_smbus_read_byte_data (_controller_io_handle, __MODE1);
            mode1res = mode1res & ~__SLEEP; //                 # wake up (reset sleep)

            if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __MODE1, mode1res) && DEBUG_MODE==false)
                RCLCPP_ERROR (get_logger(), "Failed to recover from low power mode");
            else
                printf("Enabled recover from low power mode; data_sent= %x ; address= %x\n", mode1res, __MODE1);
            
            nanosleep((const struct timespec[]){{0, 5000000L}}, NULL);   //sleep 5microsec, wait for osci

            // the first time we activate a board, we mark it and set all of its servo channels to 0
            _set_pwm_interval_all (0, 0);
        }
    }
}


/**
 * \private method to set a value for a PWM channel on the active board
 *
 *The pulse defined by start/stop will be active on the specified servo channel until any subsequent call changes it.
 *@param servo an int value (1..16) indicating which channel to change power
 *@param start an int value (0..4096) indicating when the pulse will go high sending power to each channel.
 *@param end an int value (0..4096) indicating when the pulse will go low stoping power to each channel.
 *Example _set_pwm_interval (3, 0, 350)    // set servo #3 (fourth position on the hardware board) with a pulse of 350
 */
void I2cPwmController::_set_pwm_interval (int servo, int start, int end)
{
	RCLCPP_DEBUG(get_logger(), "_set_pwm_interval enter");

    if ((servo<1) || (servo>(MAX_SERVOS))) {
        RCLCPP_ERROR(get_logger(), "Invalid servo number %d :: servo numbers must be between 1 and %d", servo, MAX_BOARDS);
        throw std::runtime_error("Invalid servo number");
    }

	int board = ((int)((servo-1)/16))+1;	// servo 1..16 is board #1, servo 17..32 is board #2, etc.
	_set_active_board(board);

	servo = ((servo-1) % 16) + 1;			// servo numbers are 1..16


    // the public API is ONE based and hardware is ZERO based
    board = _active_board - 1;				// the hardware enumerates boards as 0..61
    int channel = servo - 1;				// the hardware enumerates servos as 0..15
	RCLCPP_DEBUG(get_logger(), "_set_pwm_interval board=%d servo=%d", board, servo);
    printf("_set_pwm_interval board=%d servo=%d\n", board, servo);
    
    if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __CHANNEL_ON_L+4*channel, start & 0xFF) && DEBUG_MODE==false)
        RCLCPP_ERROR (get_logger(), "Error setting PWM start low byte on servo %d on board %d", servo, _active_board);
    else
        printf("Sent PWM start LOW byte (%x) to servo %d, address = %x\n", (start & 0xFF), servo, (__CHANNEL_ON_L+4*channel));

    if (0 >  i2c_smbus_write_byte_data (_controller_io_handle, __CHANNEL_ON_H+4*channel, start  >> 8) && DEBUG_MODE==false)
        RCLCPP_ERROR (get_logger(), "Error setting PWM start high byte on servo %d on board %d", servo, _active_board);
    else
        printf("Sent PWM start HIGH byte (%x) to servo %d, address = %x\n", (start >> 8), servo, (__CHANNEL_ON_H+4*channel));

    if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __CHANNEL_OFF_L+4*channel, end & 0xFF) && DEBUG_MODE==false)
        RCLCPP_ERROR (get_logger(), "Error setting PWM end low byte on servo %d on board %d", servo, _active_board);
    else
        printf("Sent PWM end LOW byte (%x) to servo %d, address = %x\n", (end & 0xFF), servo, (__CHANNEL_OFF_L+4*channel));

    if (0 > i2c_smbus_write_byte_data (_controller_io_handle, __CHANNEL_OFF_H+4*channel, end >> 8) && DEBUG_MODE==false)
        RCLCPP_ERROR (get_logger(), "Error setting PWM end high byte on servo %d on board %d", servo, _active_board);
    else
        printf("Sent PWM end HIGH byte (%x) to servo %d, address = %x\n", (end >> 8), servo, (__CHANNEL_OFF_H+4*channel));
}


/**
 * \private method to set a value for a PWM channel, based on a range of ±1.0, on the active board
 *
 *The pulse defined by start/stop will be active on the specified servo channel until any subsequent call changes it.
 *@param servo an int value (1..16) indicating which channel to change power
 *@param value an int value (±1.0) indicating when the size of the pulse for the channel.
 *Example _set_pwm_interval (3, 0, 350)    // set servo #3 (fourth position on the hardware board) with a pulse of 350
 */
void I2cPwmController::_set_pwm_interval_proportional (int servo, float value)
{
	// need a little wiggle room to allow for accuracy of a floating point value
	if ((value < -1.0001) || (value > 1.0001)) {
		RCLCPP_ERROR(get_logger(), "Invalid proportion value %f :: proportion values must be between -1.0 and 1.0", value);
		throw std::runtime_error("Invalid proportion value");
	}

	servo_config* configp = &(_servo_configs[servo-1]);
	
	if ((configp->center < 0) ||(configp->range < 0)) {
		RCLCPP_ERROR(get_logger(), "Missing servo configuration for servo[%d]", servo);
		throw std::runtime_error("Missing servo configuration");
	}

	int pos = (configp->direction * (((float)(configp->range) / 2) * value)) + configp->center;
        
	if ((pos < 0) || (pos > 4096)) {
		RCLCPP_ERROR(get_logger(), "Invalid computed position servo[%d] = (direction(%d) * ((range(%d) / 2) * value(%6.4f))) + %d = %d", servo, configp->direction, configp->range, value, configp->center, pos);
		throw std::runtime_error("Invalid computed position");
	}
	_set_pwm_interval (servo, 0, pos);
	RCLCPP_DEBUG(get_logger(), "servo[%d] = (direction(%d) * ((range(%d) / 2) * value(%6.4f))) + %d = %d", servo, configp->direction, configp->range, value, configp->center, pos);
}


/**
 * \private method to configure a servo on the active board
 *
 *@param servo an int value (1..16)
 *@param center an int value gt 1
 *@param range int value gt 1
 *@param direction an int  either -1 or 1
 *Example _config_server (1, 300, 100, -1)   // configure the first servo with a center of 300 and range of 100 and reversed direction
 */
void I2cPwmController::_config_servo (int servo, int center, int range, int direction)
{
	if ((servo < 1) || (servo > (MAX_SERVOS))) {
		RCLCPP_ERROR(get_logger(), "Invalid servo number %d :: servo numbers must be between 1 and %d", servo, MAX_SERVOS);
		throw std::runtime_error("Invalid servo number");
	}

	if ((center < 0) || (center > 4096))
		RCLCPP_ERROR(get_logger(), "Invalid center value %d :: center values must be between 0 and 4096", center);

	if ((center < 0) || (center > 4096))
		RCLCPP_ERROR(get_logger(), "Invalid range value %d :: range values must be between 0 and 4096", range);

	if (((center - (range/2)) < 0) || (((range/2) + center) > 4096))
		RCLCPP_ERROR(get_logger(), "Invalid range center combination %d ± %d :: range/2 ± center must be between 0 and 4096", center, (range/2));

	_servo_configs[servo-1].center = center;
	_servo_configs[servo-1].range = range;
	_servo_configs[servo-1].direction = direction;
	// _servo_configs[servo-1].mode_pos = POSITION_UNDEFINED;

	if (servo > _last_servo)	// used for internal optimizations
		_last_servo = servo;

	RCLCPP_INFO(get_logger(), "Servo #%d configured: center=%d, range=%d, direction=%d", servo, center, range, direction);
}


int I2cPwmController::_config_servo_position (int servo, int position)
{
	if ((servo < 1) || (servo > (MAX_SERVOS))) {
		RCLCPP_ERROR(get_logger(), "Invalid servo number %d :: servo numbers must be between 1 and %d", servo, MAX_SERVOS);
		return -1;
	}
	if ((position < POSITION_UNDEFINED) || (position > POSITION_RIGHTREAR)) {
		RCLCPP_ERROR(get_logger(), "Invalid drive mode position %d :: positions are 0 = non-drive, 1 = left front, 2 = right front, 3 = left rear, and 4 = right rear", position);
		return -1;
	}
	_servo_configs[servo-1].mode_pos = position;
	RCLCPP_INFO(get_logger(), "Servo #%d configured: position=%d", servo, position);
	return 0;
}


int I2cPwmController::_config_drive_mode (std::string mode, float rpm, float radius, float track, float scale)
{
	int mode_val = MODE_UNDEFINED;

	// assumes the parameter was provided in the proper case
	if 		(0 == strcmp (mode.c_str(), _CONST("ackerman")))
		mode_val = MODE_ACKERMAN;
	else if (0 == strcmp (mode.c_str(), _CONST("differential")))
		mode_val = MODE_DIFFERENTIAL;
	else if (0 == strcmp (mode.c_str(), _CONST("mecanum")))
		mode_val = MODE_MECANUM;
	else {
		mode_val = MODE_INVALID;
		RCLCPP_ERROR(get_logger(), "Invalid drive mode %s :: drive mode must be one of ackerman, differential, or mecanum", mode.c_str());
		return -1;
	}

	if (rpm <= 0.0) {
		RCLCPP_ERROR(get_logger(), "Invalid RPM %6.4f :: the motor's output RPM must be greater than 0.0", rpm);
		return -1;
	}

	if (radius <= 0.0) {
		RCLCPP_ERROR(get_logger(), "Invalid radius %6.4f :: the wheel radius must be greater than 0.0 meters", radius);
		return -1;
	}

	if (track <= 0.0) {
		RCLCPP_ERROR(get_logger(), "Invalid track %6.4f :: the axel track must be greater than 0.0 meters", track);
		return -1;
	}

	if (scale <= 0.0) {
		RCLCPP_ERROR(get_logger(), "Invalid scale %6.4f :: the scalar for Twist messages must be greater than 0.0", scale);
		return -1;
	}

	_active_drive.mode = mode_val;
	_active_drive.rpm = rpm;
	_active_drive.radius = radius;	    // the service takes the radius in meters
	_active_drive.track = track;		// the service takes the track in meters
	_active_drive.scale = scale;

	RCLCPP_INFO(get_logger(), "Drive mode configured: mode=%s, rpm=%6.4f, radius=%6.4f, track=%6.4f, scale=%6.4f", mode.c_str(), rpm, radius, track, scale);
	return 0;
}


void I2cPwmController::load_configuration_from_parameters() {
    // Declare parameters with default values if not already set by .yaml or launch, override handled internally
    declare_parameter("i2c_device_number", 1);
    declare_parameter("pwm_frequency", 50);
    // declare_parameter("servo_config", std::vector<rclcpp::ParameterValue>());
    declare_parameter("drive_config.mode", std::string("undefined"));
    declare_parameter("drive_config.rpm", 60.0);
    declare_parameter("drive_config.radius", 0.062);
    declare_parameter("drive_config.track", 0.2);
    declare_parameter("drive_config.scale", 1.0);
    // declare_parameter("drive_config.servos", std::vector<rclcpp::ParameterValue>());

    // Load I2C device number
    get_parameter("i2c_device_number", _controller_io_device);
    std::stringstream device;
    device << "/dev/i2c-" << _controller_io_device;

    DEBUG_MODE = true;
    printf("DEBUG = %d\n", DEBUG_MODE);
    // Initialize the I2C controller
    _controller_io_handle = open(device.str().c_str(), O_RDWR);
    if (_controller_io_handle < 0 && DEBUG_MODE == false) {
        RCLCPP_FATAL(get_logger(), "Failed to open I2C bus: %s", device.str().c_str());
        throw std::runtime_error("Failed to open I2C bus");
    } else {
        RCLCPP_INFO(get_logger(), "I2C bus opened on %s", device.str().c_str());
    }

    // Load drive mode configuration
    std::string mode;
    get_parameter("drive_config.mode", mode);
    get_parameter("drive_config.rpm", _active_drive.rpm);
    get_parameter("drive_config.radius", _active_drive.radius);
    get_parameter("drive_config.track", _active_drive.track);
    get_parameter("drive_config.scale", _active_drive.scale);

    _config_drive_mode(mode, _active_drive.rpm, _active_drive.radius, _active_drive.track, _active_drive.scale);


    // Set active board to 1 and set the PWM frequency
    _set_active_board(1);
    get_parameter("pwm_frequency", _pwm_frequency);
    _set_pwm_frequency(_pwm_frequency);

    // Load servo configuration
    // std::vector<rclcpp::Parameter> servo_configs = get_parameter("servo_config").as_parameter_list();
    // if (servo_configs.empty()) {
    //     RCLCPP_WARN(get_logger(), "No servo configurations found.");
    //     throw std::runtime_error("Servo configurations empty.");
    // }
    // for (const auto &param : servo_configs) {
    //     // Assuming each 'param' is a map containing "servo", "center", "direction", and "range"
    //     auto servo_map = param.as_parameter_map();

    //     // Extract values from the map
    //     int servo_id = servo_map.at("servo").as_int();
    //     int center = servo_map.at("center").as_int();
    //     int direction = servo_map.at("direction").as_int();
    //     int range = servo_map.at("range").as_int();

    //     // Validate values
    //     if (servo_id < 1 || servo_id > MAX_SERVOS) {
    //         RCLCPP_ERROR(get_logger(), "Invalid servo ID %d :: ID must be between 1 and %d", servo_id, MAX_SERVOS);
    //         continue;
    //     }

    //     if (center < 0 || center > 4096) {
    //         RCLCPP_ERROR(get_logger(), "Invalid center value %d for servo %d :: Center must be between 0 and 4096", center, servo_id);
    //         continue;
    //     }

    //     if (range < 0 || range > 4096) {
    //         RCLCPP_ERROR(get_logger(), "Invalid range value %d for servo %d :: Range must be between 0 and 4096", range, servo_id);
    //         continue;
    //     }

    //     if (direction != 1 && direction != -1) {
    //         RCLCPP_ERROR(get_logger(), "Invalid direction %d for servo %d :: Direction must be 1 or -1", direction, servo_id);
    //         continue;
    //     }

    //     // Configure the servo with the extracted values
    //     _config_servo(servo_id, center, range, direction);
    //     RCLCPP_INFO(get_logger(), "Configured servo %d: center=%d, range=%d, direction=%d", servo_id, center, range, direction);
    // }

    // Load drive servos
    // std::vector<rclcpp::Parameter> drive_servos = get_parameter("drive_config.servos").as_parameter_list();
    // if (drive_servos.empty()) {
    //     RCLCPP_WARN(get_logger(), "No drive configurations found.");
    //     throw std::runtime_error("Drive configurations empty.");
    // }
    // for (const auto &servo_param : drive_servos) {
    //     // Each servo_param is expected to contain a structure with two fields: "servo" and "position"
    //     if (servo_param.get_type() == rclcpp::ParameterType::PARAMETER_STRING) {
    //         // The parameter might be in a serialized format (like a string), so you might need to parse it
    //         RCLCPP_ERROR(get_logger(), "Unexpected servo parameter format.");
    //         continue;
    //     }

    //     // Get the "servo" and "position" values from the current parameter
    //     auto servo_config = servo_param.as_parameter_map();
    //     int servo_id = servo_config.at("servo").as_int();
    //     int position = servo_config.at("position").as_int();

    //     // Validate the extracted servo_id and position
    //     if (servo_id < 1 || servo_id > MAX_SERVOS) {
    //         RCLCPP_ERROR(get_logger(), "Invalid servo number %d :: servo numbers must be between 1 and %d", servo_id, MAX_SERVOS);
    //         continue;
    //     }

    //     if (position < POSITION_UNDEFINED || position > POSITION_RIGHTREAR) {
    //         RCLCPP_ERROR(get_logger(), "Invalid servo position %d :: positions are 0 = non-drive, 1 = left front, 2 = right front, 3 = left rear, and 4 = right rear", position);
    //         continue;
    //     }

    //     // Configure the servo position
    //     int result = _config_servo_position(servo_id, position);
    //     if (result != 0) {
    //         RCLCPP_ERROR(get_logger(), "Failed to configure servo %d with position %d", servo_id, position);
    //     } else {
    //         RCLCPP_INFO(get_logger(), "Configured servo %d at position %d", servo_id, position);
    //     }
    // }
}
