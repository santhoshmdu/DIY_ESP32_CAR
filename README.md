# RC Car Circuit Diagram
## https://www.instagram.com/reel/DP4XxTVE8pj/?igsh=dnBqNXNpYWpiYTY2

## Circuit Diagram

```mermaid
graph TB
    subgraph Power["Power Supply"]
        BAT[12V Battery<br/>LiPo 3S or Lead Acid]
        SW[Power Switch<br/>SPST 10A]
        BAT -->|12V| SW
    end
    
    subgraph BuckConverter["Buck Converter Module"]
        BUCK[LM2596 or XL4015<br/>Step Down Buck<br/>12V → 3.3V<br/>3A Rating]
    end
    
    subgraph MCU["Microcontroller"]
        ESP[ESP32 DevKit<br/>3.3V Power<br/>WiFi/BLE Control]
        ESP_GND[ESP32 GND]
    end
    
    subgraph MotorDriver["L298N Motor Driver"]
        L298[L298N Module]
        L298_12V[12V Input]
        L298_5V[5V Output]
        L298_GND[GND]
        L298_ENA[ENA - Enable A]
        L298_IN1[IN1 - Motor A Dir 1]
        L298_IN2[IN2 - Motor A Dir 2]
        L298_ENB[ENB - Enable B]
        L298_IN3[IN3 - Motor B Dir 1]
        L298_IN4[IN4 - Motor B Dir 2]
        L298_OUT1[OUT1 - Motor A+]
        L298_OUT2[OUT2 - Motor A-]
        L298_OUT3[OUT3 - Motor B+]
        L298_OUT4[OUT4 - Motor B-]
    end
    
    subgraph Motors["DC Motors"]
        MA[Motor A<br/>Left/Right]
        MB[Motor B<br/>Front/Rear]
    end
    
    %% Power Connections
    SW -->|12V| BUCK
    SW -->|12V| L298_12V
    BUCK -->|3.3V| ESP
    
    %% Ground Connections
    BAT -->|GND| GND_COMMON[Common Ground]
    GND_COMMON --> BUCK
    GND_COMMON --> ESP_GND
    GND_COMMON --> L298_GND
    
    %% ESP32 to L298N Control
    ESP -->|GPIO 25 PWM| L298_ENA
    ESP -->|GPIO 26| L298_IN1
    ESP -->|GPIO 27| L298_IN2
    ESP -->|GPIO 14 PWM| L298_ENB
    ESP -->|GPIO 12| L298_IN3
    ESP -->|GPIO 13| L298_IN4
    
    %% L298N to Motors
    L298_OUT1 --> MA
    L298_OUT2 --> MA
    L298_OUT3 --> MB
    L298_OUT4 --> MB
    
    style BAT fill:#f96,stroke:#333,stroke-width:2px
    style SW fill:#ff9,stroke:#333,stroke-width:2px
    style BUCK fill:#9cf,stroke:#333,stroke-width:2px
    style ESP fill:#9f9,stroke:#333,stroke-width:2px
    style L298 fill:#f9f,stroke:#333,stroke-width:2px
    style MA fill:#fc9,stroke:#333,stroke-width:2px
    style MB fill:#fc9,stroke:#333,stroke-width:2px
    style GND_COMMON fill:#ccc,stroke:#333,stroke-width:2px
```

## Components List

- 12V Battery (LiPo 3S or Lead Acid)
- Power Switch (SPST, 10A)
- Buck Converter (LM2596/XL4015, 12V→3.3V, 3A)
- ESP32 DevKit
- L298N Motor Driver Module
- 2x DC Motors (6-12V)
- Wires & Connectors

## Wiring Connections

### Power System
- **Battery (+)** → **Power Switch** → **Buck Converter IN** & **L298N 12V**
- **Battery (-)** → **Common Ground**
- **Buck Converter OUT (3.3V)** → **ESP32 3.3V Pin**

### ESP32 → L298N Control Pins
| ESP32 GPIO | L298N Pin | Function |
|------------|-----------|----------|
| GPIO 25    | ENA       | Motor A Speed (PWM) |
| GPIO 26    | IN1       | Motor A Direction 1 |
| GPIO 27    | IN2       | Motor A Direction 2 |
| GPIO 14    | ENB       | Motor B Speed (PWM) |
| GPIO 12    | IN3       | Motor B Direction 1 |
| GPIO 13    | IN4       | Motor B Direction 2 |

### L298N → Motors
- **OUT1 & OUT2** → Motor A
- **OUT3 & OUT4** → Motor B

### Ground Connections
Connect all grounds together:
- Battery (-)
- Buck Converter GND
- ESP32 GND
- L298N GND

## Setup Instructions

1. **Adjust Buck Converter First:**
   - Connect 12V input to buck converter
   - Measure output voltage with multimeter
   - Adjust potentiometer to exactly **3.3V**
   - ⚠️ Never exceed 3.6V or ESP32 will be damaged

2. **Wire Power System:**
   - Install power switch between battery and circuits
   - Connect buck converter and L298N to switched 12V
   - Establish common ground connection

3. **Connect Control Signals:**
   - Wire ESP32 GPIOs to L298N as per table above
   - Keep signal wires short and away from motor wires

4. **Connect Motors:**
   - Connect motors to L298N output terminals
   - Test polarity and swap wires if needed for correct direction

## Motor Control Logic

**Direction Control:**
- IN1=HIGH, IN2=LOW → Forward
- IN1=LOW, IN2=HIGH → Reverse
- IN1=LOW, IN2=LOW → Stop

**Speed Control:**
- PWM on ENA/ENB pins (0-255)
- 0 = stopped, 255 = full speed

## Safety Notes

⚠️ **Important:**
- Verify buck converter voltage before connecting ESP32
- Never reverse battery polarity
- Add 5-10A fuse on battery positive line
- Ensure all grounds are connected properly
- L298N may get warm during operation (normal)

## Testing

1. Power on and verify ESP32 LED lights up
2. Upload test code to ESP32
3. Test motors individually
4. Check for smooth operation and correct directions

---

**Power Requirements:** ~1-5A depending on motor load  
**Recommended Battery:** 2000-5000mAh for 30min-2hr runtime
