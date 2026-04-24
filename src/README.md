# Source Code

This folder contains the source code for the COR WRO 2026 Future Engineers vehicle.

## Program Structure

The code is written in **CLeV3R** (C-like programming language for EV3). We chose CLeV3R because it is lighter, faster, and more convenient for complex algorithms compared to the default EV3-G graphical environment.

### Files

- `OpenChallenge.c` - Main program for the Open Challenge rounds
- `ObstacleChallenge.c` - Main program for the Obstacle Challenge rounds

### Module Descriptions

| Module | Description |
|--------|-------------|
| `Main` | Entry point: sensor initialization, start button wait, challenge mode selection |
| `GyroStraight` | PID controller for gyro-based straight-line driving |
| `Turn` | 90-degree turn execution using gyro + color sensor feedback |
| `ObstacleAvoid` | Pixy2-based obstacle detection and avoidance path calculation |
| `Parking` | Parallel parking sequence after 3 laps in Obstacle Challenge |
| `SectionCounter` | Section counting via color line detection (orange/blue) |

### How to Upload

1. Install CLeV3R IDE and compiler
2. Connect EV3 via USB
3. Open the `.c` source file in CLeV3R
4. Compile and upload to EV3 Brick

### PID Constants

```
Kp = 1.8   (proportional - primary correction force)
Ki = 0.02  (integral - eliminates steady-state offset)
Kd = 0.5   (derivative - dampens oscillation)
```

### Code Comments

All code blocks are annotated with comments explaining:
- What each block does
- Why specific values were chosen
- How sensor data flows through the logic
