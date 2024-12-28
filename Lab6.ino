void digital_Write(byte pin, byte state) {
  asm volatile (
    //условия

    "ldi r19, 0b00000001" "\n"
    "ldi r21, 0b11111111" "\n"

    "cpi %1, 8" "\n" //если пин меньше 8
    "brlo l1" "\n"//то PORTD
    "cpi %1, 0b10100000" "\n" //если больше >=A0
    "brsh l2" "\n" //то PORTC

    //PORTB
    "sbci %1, 7" "\n"
    "in r17, 0x05" "\n"
    "cpi %0, 1" "\n"
    "breq portb_state_high" "\n"
    "cmpb: cpi %1, 0" "\n"//start PORTB - LOW
    "breq stopb1" "\n" //if equal, than branch
    "dec %1" "\n" //dec pin
    "lsl r19" "\n" //shifts r19 left
    "jmp cmpb" "\n"
    "stopb1:sub r21, r19" "\n"
    "and r17, r21" "\n"
    "out 0x05, r17""\n"
    "jmp exit" "\n"
    "portb_state_high: cpi %1, 0 " "\n" //start PORTB - HIGH
    "breq stopb2" "\n"
    "dec %1" "\n"
    "lsl r19" "\n"
    "jmp portb_state_high" "\n"
    "stopb2: or r17, r19 " "\n"
    "out 0x05, r17" "\n"
    "jmp exit" "\n"

    //PORTD
    "l1:in r17, 0x0b" "\n"
    "cpi %0, 1" "\n"
    "breq portd_state_high" "\n"
    "cmpd: cpi %1, 0" "\n"//start PORTB - LOW
    "breq stopd1" "\n" //if equal, than branch
    "dec %1" "\n" //dec pin
    "lsl r19" "\n" //shifts r19 left
    "jmp cmpd" "\n"
    "stopd1:sub r21, r19" "\n"
    "and r17, r21" "\n"
    "out 0x0b, r17""\n"
    "jmp exit" "\n"
    "portd_state_high: cpi %1, 0 " "\n" //start PORTB - HIGH
    "breq stopd2" "\n"
    "dec %1" "\n"
    "lsl r19" "\n"
    "jmp portd_state_high" "\n"
    "stopd2: or r17, r19 " "\n"
    "out 0x0b, r17" "\n"
    "jmp exit" "\n"

    //PORTC(A0)
    "l2:andi %1, 0b00001111" "\n"
    "in r17, 0x08" "\n"
    "cpi %0, 1" "\n"
    "breq portc_state_high" "\n"
    "cmpc: cpi %1, 0" "\n"//start PORTB - LOW
    "breq stopc1" "\n" //if equal, than branch
    "dec %1" "\n" //dec pin
    "lsl r19" "\n" //shifts r19 left
    "jmp cmpc" "\n"
    "stopc1:sub r21, r19" "\n"
    "and r17, r21" "\n"
    "out 0x08, r17""\n"
    "jmp exit" "\n"
    "portc_state_high: cpi %1, 0 " "\n" //start PORTB - HIGH
    "breq stopc2" "\n"
    "dec %1" "\n"
    "lsl r19" "\n"
    "jmp portb_state_high" "\n"
    "stopc2: or r17, r19 " "\n"
    "out 0x08, r17" "\n"
    "jmp exit" "\n"
    "exit: nop" "\n":: "d"(state), "d"(pin)
  );
}

void setup() {
  Serial.begin(115200);
  pinMode(A0, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
}
void loop() {
  digital_Write(0xa0, HIGH);
  digital_Write(9, LOW);
  digital_Write(8, HIGH);
  delay(5000);
  digital_Write(0xa0, LOW);
  digital_Write(9, HIGH);
  digital_Write(8, LOW);
  delay(5000);
}
