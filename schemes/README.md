# Electrical Schemes and Wiring Diagrams

This folder contains:

- `wiring_diagram.png` - Complete wiring diagram showing all connections between EV3 brick, motors, and sensors
- `port_mapping.png` - Visual port mapping reference
- `power_distribution.png` - Power distribution diagram

## Port Mapping

```
EV3 Brick:
  Motor Port A  ->  Steering Motor (Medium Motor)
  Motor Port B  ->  Drive Motor Left (Medium Motor)
  Motor Port C  ->  Drive Motor Right (Medium Motor)

  Sensor Port 1 ->  Ultrasonic Sensor (front-facing)
  Sensor Port 2 ->  Gyro Sensor (center-mounted)
  Sensor Port 3 ->  Color Sensor (front-bottom, 12mm above ground)
  Sensor Port 4 ->  Pixy2 Camera (I2C, front-top, 120mm height)
```

## Power Budget

| Component | Voltage | Current (mA) |
|-----------|---------|-------------|
| EV3 Brick | 7.2-10V | 200 |
| Drive Motor x2 | 7.2-10V | 800 (total) |
| Steering Motor | 7.2-10V | 300 (peak) |
| Gyro Sensor | 5V | 20 |
| Color Sensor | 5V | 20 |
| Ultrasonic Sensor | 5V | 15 |
| Pixy2 Camera | 5V | 140 |
| **Total Peak** | | **~1495** |
