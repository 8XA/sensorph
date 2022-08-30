//-----------------------------------
//      VARIABLES QUE PUEDES CAMBIAR
//-----------------------------------
byte pin_bomba_acida = 13;
byte pin_bomba_alcalina = 12;

//Debe ser un pin análogo
byte pin_phimetro = A0;

//Los segundos deben ser enteros
int segundos_bombeo = 2;
int segundos_espera = 3;

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
    int lectura_phimetro = analogRead(pin_phimetro);
    float voltaje_phimetro = float(lectura_phimetro)/1023*5;
    Serial.println("----------------------------------------");
    Serial.println("Voltaje PHímetro: " + String(voltaje_phimetro));
    if (voltaje_phimetro > voltaje_ph_maximo || voltaje_phimetro < voltaje_ph_minimo) {
        
        if (voltaje_phimetro < voltaje_ph_minimo) {
            Serial.println("\nEncendiendo bomba ácida...");
            digitalWrite(pin_bomba_acida, LOW);
        } else if (voltaje_phimetro > voltaje_ph_maximo) {
            Serial.println("\nEncendiendo bomba alcalina...");
            digitalWrite(pin_bomba_alcalina, LOW);
        }

        delay(segundos_bombeo * 1000);
        Serial.println("Deteniendo bomba...");
    } else {
        Serial.println("\nPH dentro del rango.");
    }
    Serial.println("----------------------------------------");
} 
