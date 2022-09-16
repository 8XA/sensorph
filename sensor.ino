
//--- INICIO DE VARIABLES MODIFICABLES ---

//===================================
//       VARIABLES PARA SET 1
//===================================
byte pin_bomba_acida_set_1 = 13;
byte pin_bomba_alcalina_set_1 = 12;

//Debe ser un pin analógico
byte pin_phimetro_set_1 = A0;
//milisegundos entre cada lectura que va a promediarse
int ms_para_muestreo_set_1 = 100;

float segundos_bombeo_set_1 = 0.001;

//Rango de PH en el que las bombas no operan
float ph_maximo_set_1 = 7.5;
float ph_minimo_set_1 = 7.0;
//-----------------------------------
//           CALIBRACIÓN
//-----------------------------------
float muestra1_ph_set_1 = 4.0;
float muestra1_valor_set_1 = 1000;

float muestra2_ph_set_1 = 10.0;
float muestra2_valor_set_1 = 400;
//===================================


//===================================
//       VARIABLES PARA SET 2
//===================================
byte pin_bomba_acida_set_2 = 11;
byte pin_bomba_alcalina_set_2 = 10;

//Debe ser un pin analógico
byte pin_phimetro_set_2 = A1;
//milisegundos entre cada lectura que va a promediarse
int ms_para_muestreo_set_2 = 100;

float segundos_bombeo_set_2 = 0.001;

//Rango de PH en el que las bombas no operan
float ph_maximo_set_2 = 7.5;
float ph_minimo_set_2 = 7.0;
//-----------------------------------
//           CALIBRACIÓN
//-----------------------------------
float muestra1_ph_set_2 = 4.0;
float muestra1_valor_set_2 = 1000;

float muestra2_ph_set_2 = 10.0;
float muestra2_valor_set_2 = 400;
//===================================


//===================================
//       VARIABLES PARA SET 3
//===================================
byte pin_bomba_acida_set_3 = 9;
byte pin_bomba_alcalina_set_3 = 8;

//Debe ser un pin analógico
byte pin_phimetro_set_3 = A2;
//milisegundos entre cada lectura que va a promediarse
int ms_para_muestreo_set_3 = 100;

float segundos_bombeo_set_3 = 0.001;

//Rango de PH en el que las bombas no operan
float ph_maximo_set_3 = 7.5;
float ph_minimo_set_3 = 7.0;
//-----------------------------------
//           CALIBRACIÓN
//-----------------------------------
float muestra1_ph_set_3 = 4.0;
float muestra1_valor_set_3 = 1000;

float muestra2_ph_set_3 = 10.0;
float muestra2_valor_set_3 = 400;
//===================================

//Segundos de espera entre cada lectura de bombas
float segundos_espera = 3.0;
//Set en turno cambia tras la ejecución de cada set.
//El programa inicia con el set definido en esta variable
int set_en_turno = 1;

//--- FIN DE VARIABLES MODIFICABLES ---

byte pin_bomba_acida;
byte pin_bomba_alcalina;
byte pin_phimetro;
int ms_para_muestreo;
float segundos_bombeo;
float ph_maximo;
float ph_minimo;
float muestra1_ph;
float muestra1_valor;
float muestra2_ph;
float muestra2_valor;
String set;


void setup() {
    // Set 1
    pinMode(pin_phimetro_set_1, INPUT);
    pinMode(pin_bomba_acida_set_1, OUTPUT);
    pinMode(pin_bomba_alcalina_set_1, OUTPUT);
    
    // Set 2
    pinMode(pin_phimetro_set_2, INPUT);
    pinMode(pin_bomba_acida_set_2, OUTPUT);
    pinMode(pin_bomba_alcalina_set_2, OUTPUT);
    
    // Set 3
    pinMode(pin_phimetro_set_3, INPUT);
    pinMode(pin_bomba_acida_set_3, OUTPUT);
    pinMode(pin_bomba_alcalina_set_3, OUTPUT);

    Serial.begin(9600);
}


void loop() {
    if (set_en_turno > 3){
        delay(segundos_espera * 1000);
        set_en_turno = 1;
    }

    if (set_en_turno == 1) {
        set = "SET 1";
        pin_bomba_acida = pin_bomba_acida_set_1;
        pin_bomba_alcalina = pin_bomba_alcalina_set_1;
        pin_phimetro = pin_phimetro_set_1;
        ms_para_muestreo = ms_para_muestreo_set_1;
        segundos_bombeo = segundos_bombeo_set_1;
        ph_maximo = ph_maximo_set_1;
        ph_minimo = ph_minimo_set_1;
        muestra1_ph = muestra1_ph_set_1;
        muestra1_valor = muestra1_valor_set_1;
        muestra2_ph = muestra2_ph_set_1;
        muestra2_valor = muestra2_valor_set_1;
    } else if (set_en_turno == 2) {
        set = "SET 2";
        pin_bomba_acida = pin_bomba_acida_set_2;
        pin_bomba_alcalina = pin_bomba_alcalina_set_2;
        pin_phimetro = pin_phimetro_set_2;
        ms_para_muestreo = ms_para_muestreo_set_2;
        segundos_bombeo = segundos_bombeo_set_2;
        ph_maximo = ph_maximo_set_2;
        ph_minimo = ph_minimo_set_2;
        muestra1_ph = muestra1_ph_set_2;
        muestra1_valor = muestra1_valor_set_2;
        muestra2_ph = muestra2_ph_set_2;
        muestra2_valor = muestra2_valor_set_2;
    } else if (set_en_turno == 3) {
        set = "SET 3";
        pin_bomba_acida = pin_bomba_acida_set_3;
        pin_bomba_alcalina = pin_bomba_alcalina_set_3;
        pin_phimetro = pin_phimetro_set_3;
        ms_para_muestreo = ms_para_muestreo_set_3;
        segundos_bombeo = segundos_bombeo_set_3;
        ph_maximo = ph_maximo_set_3;
        ph_minimo = ph_minimo_set_3;
        muestra1_ph = muestra1_ph_set_3;
        muestra1_valor = muestra1_valor_set_3;
        muestra2_ph = muestra2_ph_set_3;
        muestra2_valor = muestra2_valor_set_3;
    }

    digitalWrite(pin_bomba_acida, HIGH);
    digitalWrite(pin_bomba_alcalina, HIGH);

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
    Serial.println(set);
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
        digitalWrite(pin_bomba_acida, HIGH);
        digitalWrite(pin_bomba_alcalina, HIGH);
    } else {
        Serial.println("\nPH dentro del rango.");
    }
    Serial.println("----------------------------------------");

    set_en_turno += 1;
} 
