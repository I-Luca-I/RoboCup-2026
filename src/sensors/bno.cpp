#include "sensors/bno.h"
#include "utility/filters.h"

BNO::BNO() {
    bno = Adafruit_BNO055(55, 0x28);
    if (!bno.begin()) {
        while (true) {
            Serial.println("PORCO DIO");
        }
    }
    
    bno.setMode(OPERATION_MODE_IMUPLUS);
    bno.setExtCrystalUse(true);
    delay(1000);
    
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    STARTING_ANGLE = euler.x();
}

void BNO::read() {
    int imuCurrentEuler;
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    imuCurrentEuler = euler.x() - STARTING_ANGLE;

    if (imuCurrentEuler < 0) imuCurrentEuler += 360;

    angle = filter_angle(imuCurrentEuler, p_angle, 0.5);
    p_angle = angle;
}
