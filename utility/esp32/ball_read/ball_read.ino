/*
  Sensor Mapping
    Sensor  Angle Pin Port
    S1      0     A3  C3
    S2            A2  C2
    S3            A1  C1
    S4            A0  C0
    S5      90    13  B5
    S6            12  B4
    S7            11  B3
    S8            10  B2
    S9      180   9   B1
    S10           8   B0
    S11           7   D7
    S12           6   D6
    S13     270   5   D5
    S14           4   D4
    S15           3   D3
    S16           2   D2
    loop cycle duration: 3.2 millis
*/

int PIN_LED[4] = {12, 13, 22, 23};
int PIN_SENSOR[16] = {35, 34, 39, 36, 19, 18, 5, 4, 2, 15, 14, 27, 26, 25, 33, 32};

#define TX 17
#define RX 16

#define NCYCLES 700  //350
#define BROKEN ((NCYCLES * 86) / 100)
#define TOO_LOW ((NCYCLES * 17) / 100)

float SENSOR_X[16];
float SENSOR_Y[16];

int timesSeen[16];
int angle = 0, distance = 0;

HardwareSerial BallSerial(2);
static unsigned long sendTimer = 0;

void setup() {
  delay(1000);

  Serial.begin(57600);
  Serial2.begin(57600);
  BallSerial.begin(57600, SERIAL_8N1, RX, TX);

  for(int i=0; i<16; i++) {
    pinMode(PIN_SENSOR[i], INPUT);
  }

  for(int i=0; i<4; i++) {
    pinMode(PIN_LED[i], OUTPUT);
  }

  for (int i = 0; i < 16; i++) {
    SENSOR_X[i] = cos((22.5 * PI / 180) * i);
    SENSOR_Y[i] = sin((22.5 * PI / 180) * i);
  }

  digitalWrite(PIN_LED[0], HIGH);
}

void loop() {
  if (millis() - sendTimer > 40) {
    readBallInterpolation();
    // printCounters();
    // printBall();
    sendDataInterpolation();

    sendTimer = millis();
    // digitalWrite(PIN_LED[2], !digitalRead(PIN_LED[1]));    
  }
}

void readBallInterpolation() {
  for (int i=0; i<16; i++) {
    timesSeen[i] = 0;
  }

  for (int i=0; i<NCYCLES; i++) {
    for (int j=0; j<16; j++) {
      timesSeen[j] += digitalRead(PIN_SENSOR[j]);
    }
  }

  for (int i=0; i<16; i++) {
    timesSeen[i] = NCYCLES - timesSeen[i];
    if (timesSeen[i] > BROKEN || timesSeen[i] < TOO_LOW) timesSeen[i] = 0;
  }

  int maxSensorValue = 0;
  for (int i=0; i<16; i++) {
    maxSensorValue = max(maxSensorValue, timesSeen[i]);
  }

  //CHECK WHAT TO USE
  float x=0, y=0;
  float xTemp1=0, yTemp1=0;
  float xTemp2=0, yTemp2=0;
  for (int i=0; i<16; i++) {
    x += SENSOR_X[i] * timesSeen[i];
    y += SENSOR_Y[i] * timesSeen[i];
  }

  angle = atan2(y, x) * 180 / PI;
  angle = ((int)(angle + 360)) % 360;

  //distance is 0 when not seeing ball
  distance = maxSensorValue;

  digitalWrite(PIN_LED[3], distance);
}

void sendDataInterpolation() {
  String sendAngle = String(angle);
  if (sendAngle.length() == 1) sendAngle = "00" + sendAngle;
  if (sendAngle.length() == 2) sendAngle = "0" + sendAngle;

  String sendDistance = String(distance);
  if (sendDistance.length() == 1) sendDistance = "00" + sendDistance;
  if (sendDistance.length() == 2) sendDistance = "0" + sendDistance;

  String toSend = "B" + sendAngle + "-" + sendDistance + "b";
  // Serial.print(toSend);
  BallSerial.print(toSend);
}

void printBall() {
  Serial.print("Angle = ");
  Serial.print(angle);

  Serial.print(" | Distance = ");
  Serial.println(distance);
  delay(500);
}

void printCounters() {
  for (int i=0; i<16; i++) {
    Serial.print("Sensor[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(timesSeen[i]);
  }
  Serial.println("----------------------------");
  delay(500);
}

void blink() {
  for (int i=0; i<4; i++) {
    digitalWrite(PIN_LED[i], HIGH);
  }
  delay(1000);

  for (int i=0; i<4; i++) {
    digitalWrite(PIN_LED[i], LOW);
  }
  delay(1000);
}