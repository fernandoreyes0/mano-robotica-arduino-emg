#include <Servo.h>

#define THRESHOLD 100
#define EMG_PIN 0
#define SERVO_PIN 3
#define NUM_MUESTRAS 10

Servo SERVO_1;

unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 20;

int lecturas[NUM_MUESTRAS];
int indiceLectura = 0;

void setup() {
  Serial.begin(9600);
  SERVO_1.attach(SERVO_PIN);

  for (int i = 0; i < NUM_MUESTRAS; i++) {
    lecturas[i] = 0;
  }
}

void loop() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;

    int value = analogRead(EMG_PIN);

    lecturas[indiceLectura] = value;
    indiceLectura++;

    if (indiceLectura >= NUM_MUESTRAS) {
      indiceLectura = 0;
    }

    int contadorMayores = 0;
    for (int i = 0; i < NUM_MUESTRAS; i++) {
      if (lecturas[i] > THRESHOLD) {
        contadorMayores++;
      }
    }

    if (contadorMayores > NUM_MUESTRAS / 2) {
      SERVO_1.write(10);
      Serial.print("Servo: 10 | ");
    } else {
      SERVO_1.write(150);
      Serial.print("Servo: 150 | ");
    }

    Serial.print("Valor actual: ");
    Serial.print(value);
    Serial.print(" | Mayores: ");
    Serial.print(contadorMayores);
    Serial.print("/");
    Serial.println(NUM_MUESTRAS);
  }
}
