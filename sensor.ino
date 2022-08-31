//-----------------------------------
//      VARIABLES QUE PUEDES CAMBIAR
//-----------------------------------
byte pin_bomba_acida = 13;
byte pin_bomba_alcalina = 12;

//Debe ser un pin análogo
byte pin_phimetro = A0;
//milisegundos entre cada lectura que va a promediarse
int ms_para_muestreo = 100;

float segundos_bombeo = 0.001;
float segundos_espera = 3.0;

//Rango de PH en el que las bombas no operan
float voltaje_ph_maximo = 3.5;  // Mayor voltaje es igual a mayor acidez
float voltaje_ph_minimo = 3.0;  // Menor Voltaje es igual a mayor alcalinidad
//-----------------------------------
//-----------------------------------


void setup() {
    pinMode(pin_phimetro, INPUT);
    pinMode(pin_bomba_acida, OUTPUT);
    pinMode(pin_bomba_alcalina, OUTPUT);
    Serial.begin(9600);
}


void loop() {
    digitalWrite(pin_bomba_acida, HIGH);
    digitalWrite(pin_bomba_alcalina, HIGH);
    delay(segundos_espera * 1000);
    float lectura_raw_promedio = 0;
    for (int i=0; i < 10; i++) {
        lectura_raw_promedio += analogRead(pin_phimetro);
        delay(ms_para_muestreo);
    }
    lectura_raw_promedio /= 10;
    float voltaje_phimetro = lectura_raw_promedio/1023*5;
    float ph = (1-(voltaje_phimetro/5))*14;
    String estado = "neutro";
    if (ph < 7) {
        estado = "ácido";
    } else if (ph > 7) {
        estado = "alcalino";
    }
    Serial.println("----------------------------------------");
    Serial.println("Voltaje PHímetro: " + String(voltaje_phimetro) + "V");
    Serial.println("PH: " + String(ph) + "    Entorno " + estado);
    if (voltaje_phimetro > voltaje_ph_maximo || voltaje_phimetro < voltaje_ph_minimo) {
        
        Serial.println("\nVoltaje deseado: " + String(voltaje_ph_minimo) + "V - " + String(voltaje_ph_maximo) + "V");
        if (voltaje_phimetro < voltaje_ph_minimo) {
            Serial.println("Enciende bomba ácida.");
            digitalWrite(pin_bomba_acida, LOW);
        } else if (voltaje_phimetro > voltaje_ph_maximo) {
            Serial.println("Enciende bomba alcalina.");
            digitalWrite(pin_bomba_alcalina, LOW);
        }

        delay(segundos_bombeo * 1000);
        Serial.println("Para bomba.");
    } else {
        Serial.println("\nPH dentro del rango.");
    }
    Serial.println("----------------------------------------");
} 
