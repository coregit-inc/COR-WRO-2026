# Wiring Diagram - Team COR WRO 2026

## EV3 Brick Port Mapping

```
                    ┌─────────────────────────────────┐
                    │          EV3 BRICK               │
                    │                                   │
                    │   MOTOR PORTS      SENSOR PORTS   │
                    │   ┌──┬──┬──┬──┐   ┌──┬──┬──┬──┐  │
                    │   │ A│ B│ C│ D│   │ 1│ 2│ 3│ 4│  │
                    │   └─┬┘└─┬┘└─┬┘└──┘└─┬┘└─┬┘└─┬┘└──┘  │
                    │     │   │   │       │   │   │        │
                    └─────┼───┼───┼───────┼───┼───┼────────┘
                          │   │   │       │   │   │
                          ▼   ▼   ▼       ▼   ▼   ▼

    Motor A ──────► STEERING MOTOR (Medium Motor)
                    Front center, rack-and-pinion mechanism

    Motor B ──────► DRIVE MOTOR LEFT (Medium Motor)
                    Rear left, connected to rear axle via gear train

    Motor C ──────► DRIVE MOTOR RIGHT (Medium Motor)
                    Rear right, connected to rear axle via gear train

    Motor D ──────► (unused)

    Sensor 1 ────► ULTRASONIC SENSOR LEFT
                    Front-left, facing forward

    Sensor 2 ────► ULTRASONIC SENSOR RIGHT
                    Front-right, facing forward

    Sensor 3 ────► GYRO SENSOR
                    Center, mounted on EV3 brick

    Sensor 4 ────► (unused)
```

## Physical Layout (Top View)

```
    FRONT OF ROBOT
    ──────────────

    [Small Wheel]           [Small Wheel]
         │                       │
         └───── Steering Bar ────┘
                    │
              [Steering Motor A]
                    │
    ┌───────────────────────────────────┐
    │                                   │
    │  [Ultrasonic L]    [Ultrasonic R] │   ◄── Ports 1 & 2
    │    (front-left)     (front-right) │
    │                                   │
    │    ┌──────────────────────┐       │
    │    │                      │       │
    │    │     EV3 BRICK        │       │
    │    │   [Gyro Sensor]      │       │   ◄── Port 3
    │    │                      │       │
    │    │  Motor Ports: A B C  │       │
    │    │  Sensor Ports: 1 2 3 │       │
    │    └──────────────────────┘       │
    │                                   │
    │  [Drive Motor B]  [Drive Motor C] │   ◄── Ports B & C
    │       (left)          (right)     │
    │         │                │        │
    │         └──── Gear ──────┘        │
    │              Train               │
    │         ┌────────────┐            │
    │         │  Rear Axle │            │
    └─────────┼────────────┼────────────┘
              │            │
    [Large Wheel]    [Large Wheel]

    REAR OF ROBOT
    ─────────────
```

## Power Distribution

```
    ┌─────────────────────┐
    │  EV3 Li-ion Battery │
    │  10V / 2050mAh      │
    └─────────┬───────────┘
              │
              ▼
    ┌─────────────────────┐
    │  EV3 Brick          │
    ├─────────────────────┤
    │  7.2-10V ───► Motor A (Steering)    ~300mA peak
    │           ───► Motor B (Drive L)    ~350mA at 80%
    │           ───► Motor C (Drive R)    ~350mA at 80%
    │
    │  5V reg  ───► Sensor 1 (US Left)    ~15mA
    │          ───► Sensor 2 (US Right)   ~15mA
    │          ───► Sensor 3 (Gyro)       ~20mA
    │
    │  CPU     ───► EV3 Processor         ~200mA
    └─────────────────────┘
    Total Peak: ~1250 mA
    Battery Life: ~98 minutes
```
