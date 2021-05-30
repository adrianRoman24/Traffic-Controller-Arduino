#define GREEN_ROAD_A 2
#define YELLOW_ROAD_A 3
#define RED_ROAD_A 4
#define GREEN_ROAD_B 5
#define YELLOW_ROAD_B 6
#define RED_ROAD_B 7
#define SENSOR_A_1 8
#define SENSOR_A_2 9
#define SENSOR_B_1 10
#define SENSOR_B_2 11
#define RED_DELAY 200
#define YELLOW_DELAY 2000
#define TOTAL_ITERATIONS 30
#define SENSOR_ITERATIONS 5


void set_red_a() {
  digitalWrite(RED_ROAD_A, HIGH);
  digitalWrite(YELLOW_ROAD_A, LOW);
  digitalWrite(GREEN_ROAD_A, LOW);
}

void set_yellow_a() {
  digitalWrite(RED_ROAD_A, LOW);
  digitalWrite(YELLOW_ROAD_A, HIGH);
  digitalWrite(GREEN_ROAD_A, LOW);
}

void set_green_a() {
  digitalWrite(RED_ROAD_A, LOW);
  digitalWrite(YELLOW_ROAD_A, LOW);
  digitalWrite(GREEN_ROAD_A, HIGH);
}

void set_red_b() {
  digitalWrite(RED_ROAD_B, HIGH);
  digitalWrite(YELLOW_ROAD_B, LOW);
  digitalWrite(GREEN_ROAD_B, LOW);
}

void set_yellow_b() {
  digitalWrite(RED_ROAD_B, LOW);
  digitalWrite(YELLOW_ROAD_B, HIGH);
  digitalWrite(GREEN_ROAD_B, LOW);
}

void set_green_b() {
  digitalWrite(RED_ROAD_B, LOW);
  digitalWrite(YELLOW_ROAD_B, LOW);
  digitalWrite(GREEN_ROAD_B, HIGH);
}

void setup()
{
  for(int i = GREEN_ROAD_A; i <= RED_ROAD_B; i++) {
    pinMode(i, OUTPUT);
  }
  for(int i = SENSOR_A_1; i <= SENSOR_B_2; i++) {
    pinMode(i, INPUT);
  }
  Serial.begin(9600);
}

void loop()
{
  int detected = 0;
  if(digitalRead(SENSOR_A_1) == HIGH) {
    Serial.print("Low\n");
  }
  set_green_a();
  set_red_b();
  for(int i = 1; i <= TOTAL_ITERATIONS; i++) {
    if(digitalRead(SENSOR_A_1) == HIGH &&
       digitalRead(SENSOR_A_2) == HIGH &&
       (digitalRead(SENSOR_B_1) == LOW ||
        digitalRead(SENSOR_B_2) == LOW) ) {
      detected++;
    } else {
      detected = 0;
    }
    if(detected == SENSOR_ITERATIONS)
      break;
    delay(RED_DELAY);
  }

  set_yellow_a();
  delay(YELLOW_DELAY);
  set_green_b();
  set_red_a();
  detected = 0;
  for(int i = 1; i <= TOTAL_ITERATIONS; i++) {
    if(digitalRead(SENSOR_B_1) == HIGH &&
       digitalRead(SENSOR_B_2) == HIGH &&
       (digitalRead(SENSOR_A_1) == LOW ||
        digitalRead(SENSOR_A_2) == LOW) ) {
      detected++;
    } else {
      detected = 0;
    }
    if(detected == SENSOR_ITERATIONS)
      break;
    delay(RED_DELAY);
  }

  set_yellow_b();
  delay(YELLOW_DELAY);
}
