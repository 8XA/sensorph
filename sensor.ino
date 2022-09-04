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
float ph_maximo = 7.5;
float ph_minimo = 7.0;
//-----------------------------------
//      CALIBRACIÓN
//-----------------------------------
float muestra1_ph = 4.0;
float muestra1_valor = 1000;

float muestra2_ph = 10.0;
float muestra2_valor = 400;
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

    float sum_signal_value = 0;
    for (int i=0; i < 10; i++) {
        sum_signal_value += analogRead(pin_phimetro);
        delay(ms_para_muestreo);
    }
    float avg_signal_value = sum_signal_value/10;
    
    float m = (muestra2_ph - muestra1_ph)/(muestra2_valor - muestra1_valor);
    float offset = muestra1_ph - m * muestra1_valor;
    float pH = m * avg_signal_value + offset;

    String estado = "neutro";
    if (pH < 7) {
        estado = "ácido";
    } else if (pH > 7) {
        estado = "alcalino";
    }
    
    Serial.println("----------------------------------------");
    Serial.println("pH: " + String(pH) + "    Entorno " + estado);
    if (pH > ph_maximo || pH < ph_minimo) {
        
        Serial.println("\npH deseado: " + String(ph_minimo) + " - " + String(ph_maximo));
        if (pH < ph_minimo) {
            Serial.println("Enciende bomba alcalina.");
            digitalWrite(pin_bomba_alcalina, LOW);
        } else if (pH > ph_maximo) {
            Serial.println("Enciende bomba ácida.");
            digitalWrite(pin_bomba_acida, LOW);
        }

        delay(segundos_bombeo * 1000);
        Serial.println("Para bomba.");
    } else {
        Serial.println("\nPH dentro del rango.");
    }
    Serial.println("----------------------------------------");
} 
