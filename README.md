# RoboCup junior 2025 - Soccer Lightweight 
This file provides a detailed explanation of the team, the mechanical, electrical, and software design of the Galilei Robotics Team robots in order to compete in the European RoboCupJunior 2025 in Italy. 

## Introduction
### SPQR Team
SPQR Robotics Team is a project born in 2009 at ITIS Galileo Galilei of Rome, a technical high school where students are used to come to build robots to compete in the local championships, RomeCup, and RoboCupJunior. We’ve been taking part in competitions since 2010, we were undefeated on national level; in 2023, we have celebrated our 13th victory in a row in Italy with the RomeCup competition. Playing in the RoboCup since 2010, our history in the competition was more than positive.

However, in 2023, after our winning in the European RoboCup Junior in Varaždin, Croatia, our Headmistress has cut our funds and the laboratory was closed for more than one year. Therefore, in the 2024 RoboCup competition no one has been taking part under the name “S.P.Q.R.”.

### Galilei Team
In the last S.P.Q.R. Robotic Team there were two member who were in their third year with so much passion that, after more than one year of closure, in 2025, with the new headmistress, they reopened the Robotics Labs in a new project, taking the old student like tutor to teach to the new one the S.P.Q.R. Robotic Team’s know-how. However, the opening was very late and the first team haven’t so much time to prepare his robots.

The new team took the second place both at the RoboCup Junior Academy and at the RomeCup qualifying itself at the European RoboCup Junior in Bari, Itay. 

The team for 2025 consists of three people: one software and hardware engineer Luca Dell’Aversana, a mechanical engineer and PCB assembler Daniele Ricci and a new mechanical engineer Filippo Belli.

### 2025 Highlights
The two robots are the same hardware side, but not in the software and mechanic. This year we have produced two completely new Main Board one with a Teensy 4.1 and an ATMEGA 32, and one with a STM Blue Pill and an ESP 32. However, we have serious trouble with the first one, so we have installed the second one. We have decided to have an offensive robot (striker), and a defensive one (keeper) with some improvements like the new omni-wheels, the new-gen code and a Roller. All the robot design was made with Eagle CAD, Fusion 360 and AutoCAD.

## Mechanics
### Chassis
The new robot’s chassis was designed using CAD software such like AutoCAD, and is split in two parts, the motor base and the upper base. The motor base holds in place all the line sensor, the motors and the kicker while the upper base supports the main PCB and the support for the mirror. Both take care of ball presence sensor. These bases are made from a carbon fiber sheet with 1,5mm of thickness which we cut on our CNC milling machine.

A motor base on the CNC bed on the right and a completed motor base on the left

Last generation chassis, which can be seen on our 2023 keeper, was made of fiberglass, which was very strong but at the same type also heavy relative to the new one. Using carbon fiber and a new design we saved about 25 gr per base. From the 2023 we have thickened and strengthen the old carbon fiber chassis. This modification strengthens the robots leaving them light.

We also used FEA (Finite Element Analysis) with CAE software (Computer Aided Engineering) trying to simulate a frontal crash with another robot and see which zones on each base were the most stressed and proceeding to fix them.

### Dribbler 
This year we have designed a new type of tilting dribbler whit only one wheel in silicone rubber shaped to follow the exactly profile of the game ball in order to catch it with the maximum friction force. Moreover, in substitution of the TRX 200, we have installed the outrunner SPITZ C2822-25 which is bigger than the previous one, but it was very difficult to put on the dribbler chassis. In order to make it possible, we have to increase the height of our main board and we have to redesign completely the Fiberglass chassis (FR-4). As in the past year the transmission is entrusted to two pulley whit the relative belt.
To be sure of the resistance of the chassis we have used, such us in the carbon fibre chassis, FEA to simulate a frontal crash.
In order to produce the single silicone rubber wheel, we have printed in PLA a mould thanks to our 3D printer.

### Omni-Wheels
During the previous year we felt the need of new wheels that could be able of applying on the field the maximum potential of our Maxon motors and after the 2021 Robocup we started experimenting a new prototype of omni-wheels. We had in mind to apply the potential of a high friction material on the wheels with a wide surface of contact on the field, the design and test took weeks but at the end we were very proud about this innovation on the robot. The final result was impressive, the robot acceleration increased so much that was lacking of control near lines and we had to slow it down via software at first. We then changed approach for line handling to have better control on the robot.

To achieve this friction, we used silicone rubber and a particular design for each omni-element that we jokingly called “peanut”, given the shape. The wheels (or as we call them “peanut- wheels”) have only six omni-elements allowing an high contact surface on the field, the weird design of the wheels allows a good movement trough the perpendicular axis of rotation relatives to the axis of the motor because the length from a crest of the “peanut” and the crest of the next one is the same as the length of the two crests in the same “peanut”, while at the same time the shape of every crest helps the Maxon motor to unload on the field the maximum torque possible in the shortest time increasing robot’s acceleration and driving force. Moreover, this year, to increase the force transmitted from the motors, we reduce the diameter of the wheels by some millimetres.

The frame and the cover of the wheel are CNC cut, making all the omni-elements in rubber was a bit harder, we tried different methods but at last we decided to 3D print moulds to pour the silicone rubber.

A side effect of this particular design was the number of spokes: the old wheels had 4 spokes while the new one has 3, we could edit the new wheels to have 4 spokes but we needed to save weight on the hubs, for these reasons we decided to make custom hubs ourselves cutting a blank of aluminium with our CNC, then proceeding with drilling the hole on the side that holds the grub screw and manually tap every hole.

### Conic mirror
We are using a conic mirror to obtain a complete 360 view of the field. Instead of using a reflective paper, we have chosen to make them from a blank of aluminium machined with our lathe machine and then polishing the view surface. Whit this mirror the robot sees better, but in this way, we have increased the weight of the robot.

## Hardware
### Main Board
The design of the main board is very similar to the one we used in the last competition. There are although some updates: we have cut the front of both PCB in order to instal the dribbler easier and all the connectors were moved to make the total assembly and disassembly easier.

### Motors
Our motors are produced by Maxon, we feature four DCX16L motors with GPX16HP 2-stage gears. The motors have a high-power density while being really quiet, small and robust, with a dedicated brush protection (spark suppression – CLL) and ball bearings. Paired with the gears, which feature an extremely high-power transmission with a very short construction and a reinforced output, they have made our movement evolve.

### VNH7070AS Motor Driver
We now use four VNH7070AS motor drivers by ST to drive our motors; this was ultimately the biggest change, since we can now use a single board with everything, we need instead of a motor dedicated one. It's a full H bridge motor driver with no breakout board, but it can also work in halfbridge mode. The input signals INA and INB can directly interface the microcontroller to select the motor direction and the brake condition. A SEL0 pin is available to address the information available on the CS to the microcontroller. The CS diagnostic pin manages the motor current by delivering a current proportional to the motor current value. The PWM, up to 20 kHz, allows control of the speed of the motor in all possible conditions. In all cases, a low-level state on the PWM pin turns off both the LSA and LSB switches. They also are very secure, with a UVLO, short and thermal shutdown and current limitation.

### STM32F103C8T6 – Blue Pill
A lightweight, yet powerful microcontroller to work with and compatible with the Arduino’s Libraries thanks to the STM32duino core. It's the robot's mind, it decides what to do based on the detected inputs. Our STM32F103C8T6 mounts an Arm Cortex M3 processor, it can go up to a clock of 72 MHz with, 64 kB of Flash Memory and 20 kB RAM. It provides I2C, UART and SPI communication protocols. Every digital I/O has its 3.3V tolerance and an Interrupt capability, that makes it very versatile, because there are 37 of them. Some pins are also multifunctional, there are 15 PWM pins and 10 Analog pins with a 12-bit resolution. More I/O pins are available at small surface mount pads on the back side. They're not as easy to access as the main 34 through hole pins on the outside edge, so we don't use them. It required an External Programmer.

### ESP32-WROOM-32
As a slave microcontroller we use an ESP32-WROOM-32. We figured it was more compact and space efficient than a full board. We use it to manage the ball reading, interpolating the sensors data and sending it back to the master via UART. It contains two low-power Xtensa 32-bit LX6 microcontroller featuring 448 kB ROM, 520 kB SRAM, 8 kB SRAM – RTC FAST Memory, 8 kB SRAM – RTC SLOW Memory and 1kBit eFuse. It required an External Programmer.

### OpenMV H7
The OpenMV H7 Cam is a very powerful, valuable and affordable camera. We mount one of them on each robot, with a conic shaped mirror to see the entire field and to track the goalposts by color. It's based on the ARM Cortex H7 processor running at 216 MHz with 512KB of RAM and 2 MB of flash, it also features a floating-point unit (FPU) which
supports Arm double-precision and single-precision data- processing instructions and data types. It also implements a full set of DSP instructions and a memory protection unit (MPU) which enhances the application security. This makes it mount a microSD Card socket for video recording, SPI, Serial and I2C ports. This camera is also really flexible for all needs, with its OV7725 image sensor, and the lens is unmountable and it can be changed with other ones.

### AdaFruit BNO055
The BNO055 is an intelligent 9-axis absolute sensor. It has an embedded Cortex M0 ARM processor to perform the 9-axis sensor fusion, as well as an accelerometer, a gyroscope and a magnetometer to orient itself. No external magnetometer and no microcontroller processing is required; the quaternions, linear acceleration, gravity vector, and heading information are directly readable from the BNO-055 registers. This is a compact and powerful motion sensing solution that makes absolute orientation and sophisticated motion control available also for an Arduino board. This small-form-factor board is hardwired for I2C communication with 4K7 pull- up resistors on the board.
Our software programs the BNO-055 in IMU-PLUS Mode, and it's mounted upside-down to save some PCB space, so we use the P7 configuration. We have a way to control it through a command line interface created by us.

### Line Sensors
We designed our new line sensors to be smaller and lightweight compared to those we have used in the last competition on the offensive robot.
They are made with:
    1. Six power white LEDs
    2. Six phototransistors
    3. Six capacitors
    4. Six resistors

These line sensors are analog, which means that we can decide how to manage them. We decided to put them 90° apart from each other and between the motors forming a cross to decrease the odds of going out of bounds.

### Ball Sensors
We use IR sensors to find the ball in the field, so we opted for 16 Vishay TSSP4038. They are divided in 4 groups, each group with a RC filter to make the supply more stable. These sensors are less sensitive than the ones we used two years ago, so we can avoid mounting pipes for each one because the reading is already precise enough.

### Ball Presence sensors
The ball presence sensor is composed by two boards, one with two LEDs (emitter) and the other with one photo-transistors (receiver), to know when the ball is in the robot’s mouth to interact with the kicker, when the ball enters the robot’s mouth it stops the LED light, and the photo- transistor signal gets low, in front of the photo-transistor there is a small glass IR filter that we use to prevent the ball infrared 38kHz from interfering with the sensor. We made it from scratch and in-house with the photo etching technique, since our school has a little room dedicated to photo-etching, with a self-made bromograph.
Receiver board	Emitter board

### Power supply
The main power supply is 12V, 3 cells, LiPo battery and 2Ah of capacity. We use a LM2576 switching voltage regulator which lowers the voltage to 3,3V from 12 to power the all the main board. It has a high current resistance and required a separate inductor. We paired it with many capacitors for tension stability and every component has its own little voltage filter to guarantee a constant voltage. 

### Kicker
Solenoid
We choose the solenoid CB1037 that can operate with a nominal voltage of 12V and has a low impedance of 10 Ω.

### Kicker-driver PCB
In order to reach a strong kick and push the ball with
enough strength we must be able to power the solenoid with a high impulsive current. Since the greater the variation of the current flowing through it, the greater the magnetic field generated by the inductor; we needed to power the solenoid with a voltage higher than 12V. We bought a commercial step-up dc converter and modified its feedback divider to get up to max 47V output. But there was another problem: we couldn’t switch directly the high voltage from a step-up converter to the solenoid because our converter has an internal regulation of the maximum output current which blocks the impulsive current trough the solenoid that we actually need. For that reason, we have designed a self-made solenoid-driver PCB able to drive a high voltage to the solenoid with a great impulsive current thanks to a big electrolytic capacitor (63v 2200uF). It was designed with eagle CAD and then we have realized it by photo-etching technique with our self-made bromograph. It uses three small n-channel MOSFET to drive properly other two power p-channel MOSFET, which allow charging and complete discharging of the capacitor on our solenoid.

### Voltmeter
Since batteries, during the match, are stressed and of course decrease their voltage. We have decided to put a little voltmeter near the main switches that show us the voltage of the battery. So, we can change the battery when his charge is low to avoid their swelling.
        
## Software

### Software introduction
To program our robots, we used the Visual Studio Code (VSCode) IDE alongside the PlatformIO library. This combination was chosen not only due to my familiarity with both tools but also because it offers the best of both worlds: the user-friendly features of VSCode while maintaining the compatibility typically associated with the Arduino IDE.

### Program Structure
The code is organized into four main modules for better readability and functionality:
- Sensor: Handles all sensor-related operations, including reading and processing data from line sensors, ball infrared sensors, the camera, etc.
- Actuator: Manages interactions with the environment through motors, the kicker and the dribbler.
- Control: Contains auxiliary code unrelated to sensors, actuators, or behavior, such as movement logic and coordinate system calculations.
- Behavior: Implements the robot’s decision-making logic (e.g., striker and keeper roles).

The program follows an object-oriented design, with classes structuring the attributes and methods for each robot component.

### Robot Strategy 
Each robot has a dedicated role: either striker or goalkeeper, to streamline development and optimization. Both roles utilize state machines to determine behavior.

### Lines system
We use line sensors to determine whether the robot is almost outside of bounds and make it enter accordingly, using a trigonometric function.

### Kick strategy
The kicker is now even more important, as it’s necessary to effectively use the dribbler. To determine when the robot should “kick” the ball, we calculate the area of the goal we are attacking and use it to roughly determine how far we are from it, while also using sensor to determine when we have the ball in the robots’ mouth.

### Dribbler
By leveraging the Servo.h library, we precisely control the dribbler motor’s speed via pulse width modulation (in microseconds). To prevent damage, the dribbler’s speed is gradually increased rather than set abruptly.

### Position system
Using the color tracking function of our camera, we are using a position system based on the goals’ angles and through a trigonometric algorithm we can calculate the cartesian coordinates of the robot in a virtual plane where:
- The center of the playing field is at (0, 0).
- The two goals are at (0, 100) and (0, -100). 
The robot’s coordinates are derived using the slopes of the angles from the robot to each goal:

The point of intersection between the two lines a and b is equal to the position of the robot in the field.
It is possible to calculate the coordinates of this point by obtaining the “m” of the two lines and by using these two formulas:
