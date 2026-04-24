# Changelog - Team COR WRO 2026

## v3.0 (April 2026)
- Optimized drive speed from 65% to 75% based on test data
- Fine-tuned PID derivative gain (Kd: 0.3 -> 0.5) to reduce corner oscillation
- Added wall distance speed reduction (slow down when <100mm from wall)
- Average lap time: 9.8 seconds
- 3-lap completion rate: 90%

## v2.0 (March 2026)
- **Major change:** Replaced 1x Large Motor with 2x Medium Motors for drive
- Reduced vehicle weight by 40g (improved acceleration)
- Increased top speed by ~20%
- Redesigned rear axle gear train (1:1.67 ratio)
- Added integral term to PID (Ki=0.02) to fix persistent drift
- Average lap time: 10.8 seconds

## v1.5 (February 2026)
- Implemented gyro-based PID controller (P-only initially, Kp=2.0)
- Added color sensor line detection for automatic turn triggering
- First successful 3-lap completion achieved
- Identified front wheel traction issue due to rear-heavy weight

## v1.0 (January 2026)
- Initial prototype build using EV3 MINDSTORMS Education kit
- 1x Large Motor for drive, 1x Medium Motor for steering
- Basic forward driving with manual turn timing
- Chassis design: front-steer, rear-drive, 4 wheels
