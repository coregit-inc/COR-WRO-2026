/**
 * ============================================================
 * Team COR - WRO 2026 Future Engineers
 * Open Challenge - Main Program
 * Language: CLeV3R (C-like language for EV3)
 * ============================================================
 *
 * This program controls the autonomous vehicle during the
 * Open Challenge rounds. The robot must complete 3 laps
 * around the track with randomly placed inner walls.
 *
 * Strategy:
 * 1. Use gyro PID to drive straight
 * 2. Detect orange/blue lines with color sensor to determine turns
 * 3. Use ultrasonic sensors for wall distance monitoring
 * 4. Count 24 sections (8 per lap x 3 laps)
 * 5. Stop in the finish section after 3 laps
 *
 * Hardware:
 *   Motor A  - Steering (Medium Motor)
 *   Motor B  - Drive Left (Medium Motor)
 *   Motor C  - Drive Right (Medium Motor)
 *   Sensor 1 - Ultrasonic Left (distance to walls)
 *   Sensor 2 - Gyro (heading angle)
 *   Sensor 3 - Color (line detection)
 *   Sensor 4 - Ultrasonic Right (distance to walls)
 */

// ============================================================
// CONSTANTS
// ============================================================

// PID Controller gains (tuned through iterative testing)
// We started with Kp only, then added Kd to reduce oscillation,
// and finally Ki to eliminate steady-state drift error.
#define KP 1.8    // Proportional gain - main correction force
#define KI 0.02   // Integral gain - corrects accumulated error
#define KD 0.5    // Derivative gain - dampens oscillation

// Motor speed settings
// We chose 75% power after testing showed that 100% power
// caused missed turns and wall collisions. At 75%, lap times
// actually improved due to fewer recovery maneuvers needed.
#define DRIVE_SPEED 75       // Normal driving speed (%)
#define TURN_SPEED 50        // Speed during turns (%)
#define SLOW_SPEED 40        // Speed when approaching walls

// Sensor thresholds (calibrated on competition field)
#define ORANGE_THRESHOLD 55  // Color sensor value for orange line
#define BLUE_THRESHOLD 20    // Color sensor value for blue line
#define WALL_CLOSE 100       // Ultrasonic distance (mm) - too close to wall
#define WALL_FAR 400         // Ultrasonic distance (mm) - far from wall

// Track geometry constants
#define SECTIONS_PER_LAP 8   // 4 straight + 4 corner sections
#define TOTAL_LAPS 3
#define TOTAL_SECTIONS (SECTIONS_PER_LAP * TOTAL_LAPS)  // 24 sections

// Steering limits
#define STEER_CENTER 0       // Straight ahead
#define STEER_LEFT -35       // Maximum left turn angle
#define STEER_RIGHT 35       // Maximum right turn angle

// ============================================================
// GLOBAL VARIABLES
// ============================================================

int targetHeading = 0;       // Desired gyro heading angle
int sectionCount = 0;        // Number of sections completed
int lapCount = 0;            // Number of complete laps
int driveDirection = 0;      // 1 = CW, -1 = CCW (set by first line)
float integralError = 0.0;   // Accumulated PID integral error
int previousError = 0;       // Previous PID error for derivative

// State machine states
#define STATE_INIT 0
#define STATE_DRIVE_STRAIGHT 1
#define STATE_DETECT_TURN 2
#define STATE_EXECUTE_TURN 3
#define STATE_FINISH 4

int currentState = STATE_INIT;

// ============================================================
// SENSOR READING FUNCTIONS
// ============================================================

/**
 * Read the current heading angle from the gyro sensor.
 * The gyro is on Sensor Port 2.
 * Returns: angle in degrees (positive = clockwise rotation)
 */
int readGyroAngle() {
    return SensorValue(S2);
}

/**
 * Read reflected light intensity from the color sensor.
 * The color sensor is on Sensor Port 3, facing downward.
 * Returns: light intensity value (0-100)
 */
int readColorSensor() {
    return SensorValue(S3);
}

/**
 * Read distance from the left ultrasonic sensor.
 * Located on Sensor Port 1, front-left of vehicle.
 * Returns: distance in mm
 */
int readUltrasonicLeft() {
    return SensorValue(S1);
}

/**
 * Read distance from the right ultrasonic sensor.
 * Located on Sensor Port 4, front-right of vehicle.
 * Returns: distance in mm
 */
int readUltrasonicRight() {
    return SensorValue(S4);
}

// ============================================================
// MOTOR CONTROL FUNCTIONS
// ============================================================

/**
 * Set the steering angle using Motor A.
 * The steering motor controls a rack-and-pinion mechanism.
 *
 * @param angle: target angle (-35 to +35 degrees)
 *               negative = left, positive = right
 */
void setSteering(int angle) {
    // Clamp angle to valid range
    if (angle < STEER_LEFT) angle = STEER_LEFT;
    if (angle > STEER_RIGHT) angle = STEER_RIGHT;

    // Move steering motor to target position
    MotorRotateToPosition(MA, 30, angle);
}

/**
 * Set drive motor speeds for both rear motors.
 * Motors B and C are mechanically linked to the rear axle.
 *
 * @param speed: motor power percentage (-100 to 100)
 *               positive = forward, negative = reverse
 */
void setDriveSpeed(int speed) {
    MotorSpeed(MB, speed);
    MotorSpeed(MC, speed);
}

/**
 * Stop all motors immediately.
 */
void stopAllMotors() {
    MotorStop(MA, true);  // Brake steering
    MotorStop(MB, true);  // Brake drive left
    MotorStop(MC, true);  // Brake drive right
}

// ============================================================
// PID CONTROLLER
// ============================================================

/**
 * Calculate PID steering correction based on gyro heading error.
 *
 * The PID controller keeps the robot driving straight by
 * continuously correcting deviations from the target heading.
 *
 * Tuning process:
 * 1. Set Ki=0, Kd=0, increase Kp until slight oscillation (Kp=2.0)
 * 2. Reduce Kp slightly (Kp=1.8) and add Kd to dampen (Kd=0.5)
 * 3. Add small Ki to fix persistent drift (Ki=0.02)
 *
 * @return: steering correction value
 */
int calculatePID() {
    int currentAngle = readGyroAngle();
    int error = targetHeading - currentAngle;

    // Proportional term
    float P = KP * error;

    // Integral term (with anti-windup clamp)
    integralError += error;
    if (integralError > 100) integralError = 100;
    if (integralError < -100) integralError = -100;
    float I = KI * integralError;

    // Derivative term
    float D = KD * (error - previousError);
    previousError = error;

    // Combined PID output
    int correction = (int)(P + I + D);

    return correction;
}

// ============================================================
// LINE DETECTION
// ============================================================

/**
 * Check if the color sensor detects an orange or blue line.
 * Orange lines indicate CW direction turns.
 * Blue lines indicate CCW direction turns.
 *
 * @return: 1 if orange detected, -1 if blue detected, 0 if neither
 */
int detectLine() {
    int colorValue = readColorSensor();

    if (colorValue >= ORANGE_THRESHOLD) {
        return 1;   // Orange line - clockwise turn
    } else if (colorValue <= BLUE_THRESHOLD) {
        return -1;  // Blue line - counter-clockwise turn
    }

    return 0;  // No line detected
}

// ============================================================
// TURN EXECUTION
// ============================================================

/**
 * Execute a 90-degree turn in the specified direction.
 *
 * The turn is guided by the gyro sensor. We set a new target
 * heading that is 90 degrees offset from the current heading
 * and use the PID controller to reach it.
 *
 * @param direction: 1 for right turn, -1 for left turn
 */
void executeTurn(int direction) {
    // Calculate new target heading (90 degrees from current)
    targetHeading += (90 * direction);

    // Reduce speed during turn for accuracy
    setDriveSpeed(TURN_SPEED);

    // Set full steering in turn direction
    setSteering(STEER_RIGHT * direction);

    // Wait until gyro reaches target (within 5 degree tolerance)
    int gyroAngle = readGyroAngle();
    while (abs(targetHeading - gyroAngle) > 5) {
        gyroAngle = readGyroAngle();
        Wait(10);
    }

    // Straighten steering
    setSteering(STEER_CENTER);

    // Resume normal speed
    setDriveSpeed(DRIVE_SPEED);

    // Increment section counter
    sectionCount++;

    // Check if a full lap is completed (8 sections)
    if (sectionCount % SECTIONS_PER_LAP == 0) {
        lapCount++;
    }
}

// ============================================================
// WALL AVOIDANCE
// ============================================================

/**
 * Check if the robot is too close to a wall and adjust speed.
 * This prevents collisions when approaching corners.
 *
 * Uses both ultrasonic sensors to monitor left and right distances.
 */
void checkWallDistance() {
    int leftDist = readUltrasonicLeft();
    int rightDist = readUltrasonicRight();

    // If either sensor detects close wall, reduce speed
    if (leftDist < WALL_CLOSE || rightDist < WALL_CLOSE) {
        setDriveSpeed(SLOW_SPEED);
    }
}

// ============================================================
// MAIN PROGRAM
// ============================================================

/**
 * Main entry point for the Open Challenge program.
 *
 * State machine flow:
 * INIT -> DRIVE_STRAIGHT -> DETECT_TURN -> EXECUTE_TURN -> DRIVE_STRAIGHT
 *                                                              |
 *                                        (after 24 sections) FINISH
 */
task main() {
    // ---- STATE: INIT ----
    // Initialize sensors and wait for start button

    // Configure sensor modes
    SetSensorMode(S1, UltrasonicCM);  // Ultrasonic left
    SetSensorMode(S2, GyroAngle);      // Gyro
    SetSensorMode(S3, ColorReflect);   // Color sensor
    SetSensorMode(S4, UltrasonicCM);  // Ultrasonic right

    // Reset gyro to zero
    ResetGyro(S2);
    Wait(3000);  // Wait 3 seconds for gyro stabilization

    // Reset motor encoders
    ResetMotorEncoder(MA);
    ResetMotorEncoder(MB);
    ResetMotorEncoder(MC);

    // Display ready status
    DrawText(0, 50, "COR - READY");
    DrawText(0, 30, "Press RIGHT to START");

    // Wait for start button (right arrow on EV3)
    while (!ButtonPressed(BtnRight)) {
        Wait(50);
    }

    // Clear display and start
    ClearScreen();
    DrawText(0, 50, "RUNNING...");

    // Initialize variables
    sectionCount = 0;
    lapCount = 0;
    driveDirection = 0;
    integralError = 0;
    previousError = 0;
    targetHeading = 0;

    // Start driving forward
    setDriveSpeed(DRIVE_SPEED);
    currentState = STATE_DRIVE_STRAIGHT;

    // ---- MAIN LOOP ----
    while (currentState != STATE_FINISH) {

        switch (currentState) {

            case STATE_DRIVE_STRAIGHT:
                // Apply PID correction to maintain heading
                {
                    int correction = calculatePID();
                    setSteering(correction);
                }

                // Check wall distance for speed adjustment
                checkWallDistance();

                // Check for line detection (turn trigger)
                {
                    int line = detectLine();
                    if (line != 0) {
                        // First line detection sets driving direction
                        if (driveDirection == 0) {
                            driveDirection = line;
                        }
                        currentState = STATE_EXECUTE_TURN;
                    }
                }
                break;

            case STATE_EXECUTE_TURN:
                // Execute 90-degree turn based on driving direction
                executeTurn(driveDirection);

                // Check if all 3 laps are complete
                if (sectionCount >= TOTAL_SECTIONS) {
                    currentState = STATE_FINISH;
                } else {
                    currentState = STATE_DRIVE_STRAIGHT;
                }
                break;
        }

        // Display current status on EV3 screen
        ClearScreen();
        DrawText(0, 60, "Sections: %d", sectionCount);
        DrawText(0, 40, "Laps: %d", lapCount);
        DrawText(0, 20, "Heading: %d", readGyroAngle());

        Wait(20);  // 50Hz control loop (20ms period)
    }

    // ---- STATE: FINISH ----
    // Stop the vehicle in the finish section
    stopAllMotors();

    // Display completion message
    ClearScreen();
    DrawText(0, 50, "FINISHED!");
    DrawText(0, 30, "Laps: %d", lapCount);
    DrawText(0, 10, "Sections: %d", sectionCount);

    // Keep display on for 30 seconds
    Wait(30000);
}
