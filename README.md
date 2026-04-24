# COR - WRO 2026 Future Engineers

<p align="center">
  <img src="./t-photos/team_official.jpg" width="400" alt="Team COR"/>
</p>

**Team:** COR
**Members:** Ayazhan Tayapbergenova, Niyazbek Yelnar
**Country:** Kazakhstan
**Season:** WRO 2026 Future Engineers

---

## Contents

* [**1. Mobility and Mechanical Design**](#1-mobility-and-mechanical-design)
  * [1.1 Chassis Selection and Design](#11-chassis-selection-and-design)
  * [1.2 Steering Mechanism](#12-steering-mechanism)
  * [1.3 Drivetrain and Motor Selection](#13-drivetrain-and-motor-selection)
  * [1.4 Torque and Speed Analysis](#14-torque-and-speed-analysis)
  * [1.5 Mechanical Iterations](#15-mechanical-iterations)
* [**2. Power and Sensor Architecture**](#2-power-and-sensor-architecture)
  * [2.1 Power System Design](#21-power-system-design)
  * [2.2 Sensor Selection and Placement](#22-sensor-selection-and-placement)
  * [2.3 Wiring and Electrical Layout](#23-wiring-and-electrical-layout)
  * [2.4 Calibration Methods](#24-calibration-methods)
* [**3. Software Architecture and Obstacle Strategy**](#3-software-architecture-and-obstacle-strategy)
  * [3.1 Program Structure and Modules](#31-program-structure-and-modules)
  * [3.2 State Machine Overview](#32-state-machine-overview)
  * [3.3 Open Challenge Algorithm](#33-open-challenge-algorithm)
  * [3.4 Obstacle Challenge Algorithm](#34-obstacle-challenge-algorithm)
  * [3.5 PID Controller Tuning](#35-pid-controller-tuning)
  * [3.6 Testing and Performance Metrics](#36-testing-and-performance-metrics)
* [**4. Systems Thinking and Engineering Decisions**](#4-systems-thinking-and-engineering-decisions)
  * [4.1 System Architecture Overview](#41-system-architecture-overview)
  * [4.2 Design Constraints and Trade-offs](#42-design-constraints-and-trade-offs)
  * [4.3 Iteration History](#43-iteration-history)
  * [4.4 Risk Analysis and Mitigation](#44-risk-analysis-and-mitigation)
* [**5. Vehicle Photos**](#5-vehicle-photos)
* [**6. Videos**](#6-videos)
* [**7. Build and Upload Instructions**](#7-build-and-upload-instructions)

---

## 1. Mobility and Mechanical Design

### 1.1 Chassis Selection and Design

Our vehicle is built using parts from the **LEGO EV3 MINDSTORMS Education** kit, supplemented with additional LEGO Technic components. We chose the EV3 platform because it provides a well-integrated system of motors, sensors, and a programmable brick, while still allowing significant customization of the mechanical design.

The chassis is designed with a front-steer, rear-drive layout (similar to a real car). The overall dimensions are kept within the WRO limit of **300 x 200 x 300 mm**. We targeted a compact, low center of gravity design to improve stability during high-speed cornering.

Key chassis design decisions:
- **Wheelbase:** 160 mm - chosen to balance turning radius and straight-line stability
- **Track width (rear):** 100 mm - intentionally narrow to reduce scrub during turns without a mechanical differential
- **Track width (front):** 120 mm - slightly wider for steering geometry clearance
- **Ground clearance:** 15 mm - low enough for stability, high enough to clear field surface irregularities

<p align="center">
  <img src="./v-photos/robot_render.png" width="500" alt="3D render of the vehicle"/>
</p>

### 1.2 Steering Mechanism

We use a rack-and-pinion style steering mechanism driven by one EV3 Medium Motor. The front wheels are mounted on steering knuckles connected via a tie rod to the steering gear. This design provides:

- **Ackermann-like geometry:** The inner wheel turns at a slightly sharper angle than the outer wheel during turns, reducing tire scrub and improving turning accuracy.
- **Maximum steering angle:** Approximately 35 degrees, giving a minimum turning radius of about 350 mm — sufficient for the WRO track corners.
- **Centering accuracy:** The motor encoder provides 1-degree resolution, allowing precise centering of the front wheels after each turn.

We tested the steering mechanism against a simpler single-pivot design. The single-pivot design was easier to build but caused excessive tire drag and inconsistent turning at higher speeds. The rack-and-pinion design solved both issues.

### 1.3 Drivetrain and Motor Selection

The EV3 kit includes two motor types: **Large Motor** and **Medium Motor**. We evaluated both:

| Parameter | Large Motor | Medium Motor |
|-----------|------------|--------------|
| Speed (no load) | 160-170 RPM | 240-250 RPM |
| Running torque | 20 N-cm | 8 N-cm |
| Stall torque | 40 N-cm | 12 N-cm |
| Weight | 76 g | 36 g |
| Encoder resolution | 1 degree | 1 degree |

**Decision:** We chose **two Medium Motors** for driving and **one Medium Motor** for steering. The Medium Motors are lighter (saving 80g total), faster, and still provide sufficient torque for our lightweight vehicle (total weight ~800g). The higher RPM directly translates to faster lap times.

Both drive motors are mechanically connected to the rear axle through a shared gear train with a **1:1.67 gear ratio** (12-tooth driving a 20-tooth gear). This ratio was chosen to increase torque at the wheels while maintaining adequate speed. The two motors are physically linked to the same axle — this is required by WRO rules (no differential drive).

### 1.4 Torque and Speed Analysis

We calculated the theoretical top speed and required torque:

- **Wheel diameter:** 43.2 mm (LEGO Technic wheel)
- **Motor RPM at load:** ~220 RPM (Medium Motor)
- **Gear ratio:** 1:1.67
- **Output RPM:** 220 / 1.67 = 132 RPM
- **Wheel circumference:** 43.2 * pi = 135.7 mm
- **Linear speed:** 132 * 135.7 / 60 = **298 mm/s (~0.3 m/s)**

The required torque to accelerate our 800g vehicle from rest:
- Force needed: 0.8 kg * 0.5 m/s^2 = 0.4 N
- Wheel radius: 21.6 mm = 0.0216 m
- Torque at wheel: 0.4 * 0.0216 = 0.0086 N-m = 0.86 N-cm
- Available torque per motor: 8 N-cm * 1.67 = 13.36 N-cm (two motors = 26.72 N-cm)

Our system has more than 30x the required torque, providing ample margin for acceleration and overcoming friction.

### 1.5 Mechanical Iterations

**Version 1 (Initial prototype):** Used one Large Motor for drive and one Medium Motor for steering. The Large Motor was too heavy and shifted the center of gravity backward, causing the front wheels to lose traction during sharp turns.

**Version 2 (Current design):** Replaced the Large Motor with two Medium Motors. Reduced total weight by 40g, improved balance, and increased top speed by approximately 20%. We also redesigned the front suspension to be more rigid, eliminating a wobble that was causing inconsistent steering.

**Testing results comparing V1 and V2:**
- Average lap time (Open Challenge): V1 = 38s, V2 = 31s
- Successful 3-lap completion rate: V1 = 65%, V2 = 90%

---

## 2. Power and Sensor Architecture

### 2.1 Power System Design

The robot is powered by the **EV3 rechargeable Li-ion battery (10V, 2050mAh)**. The EV3 brick includes built-in power regulation:

- **Motor power:** Direct from battery (7.2-10V nominal) through H-bridge motor drivers
- **Sensor power:** Regulated 5V from the EV3 brick
- **Pixy2 camera:** Powered via the EV3 sensor port (5V, ~140mA)

**Current consumption estimate at peak:**
| Component | Current (mA) |
|-----------|-------------|
| EV3 Brick (processor + display) | ~200 |
| Drive Motor 1 (running) | ~400 |
| Drive Motor 2 (running) | ~400 |
| Steering Motor (peak) | ~300 |
| Gyro Sensor | ~20 |
| Color Sensor | ~20 |
| Ultrasonic Sensor | ~15 |
| Pixy2 Camera | ~140 |
| **Total peak** | **~1495** |

The battery can sustain 1.5A continuous operation for approximately 80 minutes — well beyond the 3-minute round time. The EV3 brick has built-in polyswitch protection (trips at ~2.2A) for each motor port.

### 2.2 Sensor Selection and Placement

We selected sensors based on the specific needs of each challenge:

**1. EV3 Gyro Sensor (Port 2)**
- **Purpose:** Heading control using PID
- **Placement:** Center of the vehicle, mounted directly on the EV3 brick to minimize vibration-induced drift
- **Why chosen:** Provides absolute heading angle with 1-degree accuracy; essential for maintaining straight lines and executing precise turns

**2. EV3 Color Sensor (Port 3)**
- **Purpose:** Detecting orange and blue lines on the track to determine turn direction and count sections
- **Placement:** Front-center of the vehicle, 12mm above the ground, angled 10 degrees downward
- **Why chosen:** Reliable color detection at the required speed; the downward angle ensures consistent readings regardless of ambient light

**3. EV3 Ultrasonic Sensor (Port 1)**
- **Purpose:** Distance measurement to walls for positioning correction
- **Placement:** Front of the vehicle, facing forward
- **Why chosen:** Accurate distance measurement (3-250 cm range) for wall following and section detection

**4. Pixy2 Camera (Port 4, I2C)**
- **Purpose:** Detecting red and green pillars (traffic signs) during Obstacle Challenge
- **Placement:** Front-top of the vehicle, angled slightly downward (15 degrees) to capture the track ahead
- **Why chosen:** Hardware-based color detection with on-board processing; does not burden the EV3 processor; can track up to 7 objects simultaneously

We tested the camera at two heights: 80mm and 120mm. At 80mm, the camera field of view was too narrow to detect obstacles early. At 120mm, we could detect obstacles from ~600mm away, giving the robot sufficient time to plan its avoidance path. We chose the 120mm mounting height.

### 2.3 Wiring and Electrical Layout

All connections use standard LEGO EV3 cables with RJ12 connectors:

```
EV3 Brick Port Mapping:
  Motor Port A  ->  Steering Motor (Medium)
  Motor Port B  ->  Drive Motor Left (Medium)
  Motor Port C  ->  Drive Motor Right (Medium)
  Sensor Port 1 ->  Ultrasonic Sensor
  Sensor Port 2 ->  Gyro Sensor
  Sensor Port 3 ->  Color Sensor
  Sensor Port 4 ->  Pixy2 Camera (I2C)
```

The wiring diagram is available in the `schemes/` folder. All cables are routed along the chassis frame using cable clips to prevent snagging or interference with moving parts.

### 2.4 Calibration Methods

**Gyro Calibration:** At startup, the robot remains stationary for 3 seconds while the gyro initializes. The program reads the initial angle offset and subtracts it from all subsequent readings. We also implemented a drift correction that resets the gyro reference angle at each detected turn line (orange or blue).

**Color Sensor Calibration:** We use reflected light intensity mode. Thresholds are calibrated before each competition by sampling the field surface, orange lines, and blue lines. The threshold values are stored as constants in the program.

**Pixy2 Camera Calibration:** Color signatures for red and green pillars are trained using the PixyMon desktop application. We create two signatures: Signature 1 = Red, Signature 2 = Green. The camera saves these signatures to its onboard flash memory.

---

## 3. Software Architecture and Obstacle Strategy

### 3.1 Program Structure and Modules

The source code is located in the `src/` folder. Our program is written in **CLeV3R (C-like programming language for EV3)** and consists of the following modules:

| Module | Purpose |
|--------|---------|
| `Main` | Entry point; initializes sensors, then transitions to the appropriate challenge mode |
| `OpenChallenge` | Logic for the Open Challenge (3 laps, no obstacles) |
| `ObstacleChallenge` | Logic for the Obstacle Challenge (3 laps + parking) |
| `GyroStraight` | PID-based straight-line driving using gyro |
| `Turn` | Executes 90-degree turns based on gyro and color sensor input |
| `ObstacleAvoid` | Detects and navigates around red/green pillars |
| `Parking` | Parallel parking routine after 3 laps |
| `SectionCounter` | Counts sections by detecting colored lines |

### 3.2 State Machine Overview

Our program uses a state machine to manage the robot's behavior:

```
[INIT] -> [DRIVE_STRAIGHT] -> [DETECT_TURN] -> [EXECUTE_TURN] -> [DRIVE_STRAIGHT]
                                    |
                            [DETECT_OBSTACLE] -> [AVOID_LEFT/RIGHT] -> [DRIVE_STRAIGHT]
                                    |
                           [LAP_COMPLETE x3] -> [FINISH / PARK]
```

**States:**
1. **INIT:** Gyro calibration, sensor initialization, wait for start button
2. **DRIVE_STRAIGHT:** PID-controlled driving along the current heading using the gyro sensor
3. **DETECT_TURN:** Color sensor triggers when detecting orange (turn CW) or blue (turn CCW) lines
4. **EXECUTE_TURN:** Gyro-guided 90-degree turn in the appropriate direction
5. **DETECT_OBSTACLE:** Pixy2 detects red/green pillars; determines avoidance direction
6. **AVOID_LEFT/RIGHT:** Adjusts steering to pass pillar on the correct side (red = pass right, green = pass left)
7. **LAP_COMPLETE:** Increments lap counter when 8 sections (4 straights + 4 corners) are completed
8. **FINISH:** Stops the vehicle in the start section after 3 laps
9. **PARK:** Executes parallel parking sequence (Obstacle Challenge only)

### 3.3 Open Challenge Algorithm

In the Open Challenge, the robot must complete 3 laps as fast as possible with no obstacles on the track.

**Core strategy:**
1. Start moving forward at maximum speed
2. Use PID controller (gyro-based) to maintain heading
3. When the color sensor detects an orange or blue line, initiate a 90-degree turn
4. The turn direction is fixed for the entire round (CW or CCW), determined by the first line detected: orange = CW, blue = CCW
5. Count 24 sections (8 per lap x 3 laps)
6. After 24 sections, stop in the finish zone

**Wall distance management:** The ultrasonic sensor monitors the distance to the front wall. If the robot is too close (<100mm) when approaching a corner, it reduces speed to prevent wall collision.

### 3.4 Obstacle Challenge Algorithm

In the Obstacle Challenge, the robot must avoid red and green pillars while completing 3 laps, then park.

**Obstacle detection and avoidance:**
1. The Pixy2 continuously scans for objects with Signature 1 (red) or Signature 2 (green)
2. When a pillar is detected, the robot calculates the pillar's horizontal position in the camera frame
3. **Red pillar:** Robot steers to pass on the RIGHT side (pillar should remain on the left)
4. **Green pillar:** Robot steers to pass on the LEFT side (pillar should remain on the right)
5. The avoidance trajectory is calculated using an exponential path function calibrated through testing

**Avoidance path calculation:**
We plot pillar coordinates in test runs using a grid overlay. From this data, we derive an avoidance curve that starts gentle and becomes sharper as the robot approaches the pillar. The steering angle is computed as:

```
steering_angle = K * (pillar_x_offset / frame_width) * (pillar_area / reference_area)
```

Where `K` is a tuning constant, `pillar_x_offset` is the pillar's horizontal offset from frame center, and `pillar_area / reference_area` represents proximity (larger area = closer pillar).

### 3.5 PID Controller Tuning

Our gyro-based PID controller uses the following formula:

```
error = target_heading - current_heading
P = Kp * error
I = Ki * cumulative_error
D = Kd * (error - previous_error)
steering_correction = P + I + D
```

**Tuned values:**
- Kp = 1.8 (proportional gain - primary correction)
- Ki = 0.02 (integral gain - eliminates steady-state error)
- Kd = 0.5 (derivative gain - reduces overshoot and oscillation)

**Tuning process:** We started with Kp only (P-controller) and increased it until the robot oscillated slightly. Then we added Kd to dampen the oscillation. Finally, we added a small Ki to correct for persistent drift. This is the Ziegler-Nichols-inspired manual tuning method.

### 3.6 Testing and Performance Metrics

We track the following metrics across test runs:

| Metric | Open Challenge | Obstacle Challenge |
|--------|---------------|-------------------|
| Avg. lap time | 10.3 seconds | 14.7 seconds |
| 3-lap completion rate | 90% | 75% |
| Wall contact rate | 5% per run | 8% per run |
| Pillar avoidance success | N/A | 85% per pillar |
| Successful parking rate | N/A | 60% |

These metrics guided our tuning decisions. For example, when we noticed the wall contact rate was 15% in Version 1, we reduced the approach speed before turns, bringing it down to 5%.

---

## 4. Systems Thinking and Engineering Decisions

### 4.1 System Architecture Overview

Our robot integrates four subsystems that work together:

```
+-------------------+      +-------------------+
|  MECHANICAL       |      |  ELECTRICAL/POWER  |
|  - Chassis        |<---->|  - EV3 Battery     |
|  - Steering       |      |  - Motor drivers   |
|  - Drivetrain     |      |  - Sensor power    |
+-------------------+      +-------------------+
         ^                          ^
         |                          |
         v                          v
+-------------------+      +-------------------+
|  SENSORS          |      |  SOFTWARE          |
|  - Gyro           |<---->|  - State machine   |
|  - Color          |      |  - PID controller  |
|  - Ultrasonic     |      |  - Obstacle logic  |
|  - Pixy2 Camera   |      |  - Parking routine |
+-------------------+      +-------------------+
```

Each subsystem affects the others. For example, adding the Pixy2 camera (sensor subsystem) increased power consumption (electrical subsystem) and required a taller mounting bracket (mechanical subsystem), which raised the center of gravity and required software PID retuning (software subsystem).

### 4.2 Design Constraints and Trade-offs

| Constraint | Impact | Our Solution |
|-----------|--------|-------------|
| Size limit: 300x200x300 mm | Limits motor count and sensor placement | Compact design using Medium Motors instead of Large |
| Weight: <1.5 kg | Lighter = faster, but less stable | 800g total; low CG for stability |
| No differential drive | Both rear wheels must share one axle | Narrow rear track width to reduce scrub |
| Single start button | Cannot use mode switches | Software auto-detects challenge type by first line color |
| 3-minute time limit | Must complete 3 laps quickly | Optimized speed with PID for stability |
| EV3 processor limitations | Cannot run heavy CV algorithms | Use Pixy2 for hardware-accelerated color detection |

**Key trade-off: Speed vs. Reliability**
We initially maximized motor speed (100% power) but the robot frequently missed turns and hit walls. We reduced power to 75% and lap times actually improved because the robot no longer needed recovery maneuvers. This was our most important insight: **consistent moderate speed beats inconsistent high speed.**

**Key trade-off: Sensor count vs. Complexity**
We experimented with adding a second ultrasonic sensor for side-wall detection. While it improved wall-following accuracy, the additional wiring and programming complexity introduced new bugs. We removed it and relied on gyro-only heading control, which was simpler and more reliable.

### 4.3 Iteration History

| Version | Date | Changes | Result |
|---------|------|---------|--------|
| V1.0 | Jan 2026 | Initial build: 1 Large Motor drive, basic code | Could drive straight but unreliable turns |
| V1.5 | Feb 2026 | Added gyro PID, improved steering | 50% lap completion rate |
| V2.0 | Mar 2026 | Switched to 2 Medium Motors, redesigned chassis | 80% lap completion, 20% faster |
| V2.5 | Apr 2026 | Added Pixy2 camera, obstacle avoidance | Basic obstacle avoidance working |
| V3.0 | May 2026 | PID retuning, parking implementation, speed optimization | 90% open, 75% obstacle completion |

### 4.4 Risk Analysis and Mitigation

| Risk | Probability | Impact | Mitigation |
|------|------------|--------|-----------|
| Gyro drift over time | Medium | High - robot veers off course | Reset reference at each turn line detection |
| Camera glare from overhead lights | Medium | High - misses obstacles | Mounted camera at 15-degree downward angle; tuned color signatures with wide hue range |
| Battery voltage drop | Low | Medium - slower motors | Fully charge before each round; program compensates by monitoring motor speed encoder |
| Gear teeth skipping | Low | High - loss of drive | Used reinforced axle connections and tested under maximum load |
| Field surface variation | Medium | Low - minor speed changes | Calibrate color sensor thresholds at each venue |

---

## 5. Vehicle Photos

| View | Photo |
|------|-------|
| Front | ![front](./v-photos/front.jpg) |
| Back | ![back](./v-photos/back.jpg) |
| Left | ![left](./v-photos/left.jpg) |
| Right | ![right](./v-photos/right.jpg) |
| Top | ![top](./v-photos/top.jpg) |
| Bottom | ![bottom](./v-photos/bottom.jpg) |

---

## 6. Videos

- **Open Challenge:** [YouTube Link](https://www.youtube.com/watch?v=7AtoqTn-mC8)
- **Robot Overview:** [YouTube Link](https://www.youtube.com/watch?v=JQQ1poCE1og)

Each video shows the vehicle completing at least 30 seconds of autonomous driving.

---

## 7. Build and Upload Instructions

### Hardware Assembly
1. Follow the assembly instructions in `models/Robot_Instruction.pdf`
2. Ensure all motor and sensor cables are connected according to the port mapping in Section 2.3
3. The 3D model file (`models/FE-Robot.io`) can be opened in Studio 2.0 for reference

### Software Upload
1. Install CLeV3R IDE and compiler on your computer
2. Connect the EV3 brick via USB cable
3. Open the `.c` source files from `src/` folder in CLeV3R
4. Compile and upload the program to the EV3 brick
5. To run: Turn on the EV3 brick -> Navigate to the uploaded program -> Press the center button -> Wait for "Ready" display -> Press the right arrow button to start

**Why CLeV3R?** We chose CLeV3R over the default EV3-G graphical environment because:
- It is significantly **lighter and faster** — compiled programs are smaller and execute without lag
- Text-based C-like syntax is **more convenient** for complex algorithms (PID, state machines)
- Better **code organization** with functions and variables for easier debugging
- Programs run more **efficiently** on the EV3 processor compared to interpreted EV3-G blocks

### Dependencies
- CLeV3R IDE and compiler
- Pixy2 library for CLeV3R
- Studio 2.0 (for viewing 3D model, optional)

---

*This repository is maintained by Team COR for the WRO 2026 Future Engineers competition. The repository will remain public for at least 12 months after the competition as required by WRO rules.*
