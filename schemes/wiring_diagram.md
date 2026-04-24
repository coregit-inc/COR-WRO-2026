# Wiring Diagram - Team COR WRO 2026

## EV3 Brick Port Mapping

Based on the physical robot inspection, the following port assignments are used:

```
                    ┌─────────────────────────────────┐
                    │          EV3 BRICK               │
                    │                                   │
                    │   MOTOR PORTS      SENSOR PORTS   │
                    │   ┌──┬──┬──┬──┐   ┌──┬──┬──┬──┐  │
                    │   │ A│ B│ C│ D│   │ 1│ 2│ 3│ 4│  │
                    │   └─┬┘└─┬┘└─┬┘└──┘└─┬┘└─┬┘└─┬┘└─┬┘  │
                    │     │   │   │       │   │   │   │    │
                    └─────┼───┼───┼───────┼───┼───┼───┼────┘
                          │   │   │       │   │   │   │
                          ▼   ▼   ▼       ▼   ▼   ▼   ▼

    Motor A ──────► STEERING MOTOR (Medium Motor)
                    Location: Front center, connected to rack-and-pinion steering

    Motor B ──────► DRIVE MOTOR LEFT (Medium Motor)
                    Location: Rear left, connected to rear axle via gear train

    Motor C ──────► DRIVE MOTOR RIGHT (Medium Motor)
                    Location: Rear right, connected to rear axle via gear train

    Sensor 1 ────► ULTRASONIC SENSOR #1
                    Location: Front-left, facing forward
                    Purpose: Wall distance detection (left side)

    Sensor 2 ────► GYRO SENSOR
                    Location: Center, mounted on EV3 brick
                    Purpose: Heading angle for PID straight-line control

    Sensor 3 ────► COLOR SENSOR
                    Location: Front-bottom, 12mm above ground, angled down
                    Purpose: Detecting orange/blue turn lines

    Sensor 4 ────► ULTRASONIC SENSOR #2
                    Location: Front-right, facing forward
                    Purpose: Wall distance detection (right side)
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
    │  [UltraSonic 1]  [UltraSonic 2]  │   ◄── Sensor Ports 1 & 4
    │       (front-left)  (front-right) │
    │                                   │
    │         [Color Sensor]            │   ◄── Sensor Port 3
    │          (bottom, facing down)    │
    │                                   │
    │    ┌──────────────────────┐       │
    │    │                      │       │
    │    │     EV3 BRICK        │       │
    │    │   [Gyro Sensor]      │       │   ◄── Sensor Port 2
    │    │                      │       │
    │    │  Ports: A B C D      │       │
    │    │         1 2 3 4      │       │
    │    └──────────────────────┘       │
    │                                   │
    │  [Drive Motor B]  [Drive Motor C] │   ◄── Motor Ports B & C
    │       (left)          (right)     │
    │         │                │        │
    │         └──── Gear ──────┘        │
    │              Train               │
    │         ┌────────────┐            │
    │         │  Rear Axle  │            │
    └─────────┼────────────┼────────────┘
              │            │
    [Large Wheel]    [Large Wheel]

    REAR OF ROBOT
    ─────────────
```

## Power Distribution

```
    ┌─────────────────────┐
    │  EV3 Rechargeable   │
    │  Li-ion Battery     │
    │  10V / 2050mAh      │
    └─────────┬───────────┘
              │
              ▼
    ┌─────────────────────┐
    │  EV3 Brick          │
    │  Internal Regulator  │
    ├─────────────────────┤
    │                     │
    │  7.2-10V rail ──────┼──► Motor A (Steering)  ~300mA peak
    │                     │
    │                     ├──► Motor B (Drive L)   ~400mA running
    │                     │
    │                     ├──► Motor C (Drive R)   ~400mA running
    │                     │
    │  5V regulated ──────┼──► Sensor 1 (Ultrasonic) ~15mA
    │                     │
    │                     ├──► Sensor 2 (Gyro)       ~20mA
    │                     │
    │                     ├──► Sensor 3 (Color)      ~20mA
    │                     │
    │                     ├──► Sensor 4 (Ultrasonic) ~15mA
    │                     │
    │  EV3 Processor ─────┼──► ~200mA
    │                     │
    └─────────────────────┘
              │
    Total Peak: ~1370 mA
    Battery Life at Peak: ~90 minutes
    Round Duration: 3 minutes (well within capacity)
```

## Cable Routing Notes

- All cables use standard EV3 flat cables with RJ12 connectors
- Cables are bundled with yellow rubber bands to prevent tangling (visible in photos)
- Motor cables routed along the inner frame beams
- Sensor cables routed on the outer edges to avoid motor interference
- No cable crosses over moving parts (steering mechanism, wheels)
