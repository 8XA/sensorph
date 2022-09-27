byte pin_phimetro = A0;
float ms_por_muestra = 10;
float s_duracion_muestreo = 60.0;
float suma_muestras = 0;
float contador_de_muestras = 0;


void setup() {
    Serial.begin(9600);
    pinMode(pin_phimetro, INPUT);
}


void loop() {
    while (s_duracion_muestreo > 0) {
        Serial.println(String(s_duracion_muestreo) + " " + String(analogRead(pin_phimetro)));
        s_duracion_muestreo -= ms_por_muestra/1000;
        suma_muestras += analogRead(pin_phimetro);
        contador_de_muestras += 1;
        delay(ms_por_muestra);
    }
    Serial.println("Val: " + String(suma_muestras/contador_de_muestras));
    delay(60000);
}

