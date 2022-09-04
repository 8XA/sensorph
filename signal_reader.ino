
byte pin_phimetro = A0;
int ms_para_muestreo = 500;


void setup() {
    Serial.begin(9600);
    pinMode(pin_phimetro, INPUT);
}


void loop() {
    Serial.println(String(analogRead(pin_phimetro)));
    delay(ms_para_muestreo);
}

