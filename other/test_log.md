# Test Log - Team COR WRO 2026

## Testing Protocol
1. Place robot in designated start zone
2. Power on EV3 brick
3. Press center button to load program
4. Press right arrow button to start
5. Record lap times, completion, wall contacts

## Test Results Summary

### Version 1.0 (January 2026) - Large Motor Drive
| Run | Lap 1 | Lap 2 | Lap 3 | Complete | Wall Hits | Notes |
|-----|-------|-------|-------|----------|-----------|-------|
| 1   | 14.2s | DNF   | -     | No       | 3         | Robot too heavy, front wheels lost grip |
| 2   | 13.8s | 15.1s | DNF   | No       | 2         | Oversteered on 3rd corner |
| 3   | 13.5s | 14.3s | 14.8s | Yes      | 1         | First complete run |

### Version 2.0 (March 2026) - Dual Medium Motor Drive
| Run | Lap 1 | Lap 2 | Lap 3 | Complete | Wall Hits | Notes |
|-----|-------|-------|-------|----------|-----------|-------|
| 1   | 11.2s | 11.5s | 11.8s | Yes      | 0         | Much faster, better balance |
| 2   | 10.8s | 11.0s | 11.3s | Yes      | 0         | PID tuning improved |
| 3   | 10.5s | 10.7s | 11.0s | Yes      | 1         | Minor wall touch on corner 7 |
| 4   | 10.3s | 10.5s | 10.8s | Yes      | 0         | Best run |

### Version 3.0 (April 2026) - Speed Optimization
| Run | Lap 1 | Lap 2 | Lap 3 | Complete | Wall Hits | Notes |
|-----|-------|-------|-------|----------|-----------|-------|
| 1   | 9.8s  | 10.1s | 10.3s | Yes      | 0         | Speed increased to 80% |
| 2   | 9.5s  | 9.8s  | 10.0s | Yes      | 0         | Best time achieved |
| 3   | 9.7s  | 10.0s | 10.2s | Yes      | 0         | Consistent performance |
| 4   | 9.9s  | DNF   | -     | No       | 2         | Speed at 90% - too fast |
| 5   | 9.6s  | 9.9s  | 10.1s | Yes      | 0         | Back to 80% - stable |

## Key Findings
- V1 to V2: Switching from 1 Large Motor to 2 Medium Motors reduced weight by 40g and improved lap times by ~25%
- Optimal speed is 75-80% power. Above 85% the robot becomes unreliable on turns
- PID gains Kp=1.8, Ki=0.02, Kd=0.5 provide best balance of speed and stability
- Gyro drift correction at each turn line keeps heading accurate across all 3 laps
