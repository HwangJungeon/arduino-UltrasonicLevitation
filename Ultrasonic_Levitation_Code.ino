//Source of source code - makezine.com
//Korean comments - 전깃줄 Electric Cable(HwangJungeon)

byte TP = 0b10101010; //모든 포트들를 반전된 신호를 수신하도록 설정
void setup() {
  DDRC = 0b11111111; //모든 아날로그 포트를 출력모드로 설정

  //이하 내용은 ATmega PWM 레지스터를 이용하여 80kHz square signal을 40kHz의 full wave cycling로 변환하는 내용
  // Initialize Timer1
  noInterrupts(); //interrupts disabled
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 200; // Set compare register (16MHz / 200 = 80kHz square wave -> 40kHz full wave)
  
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS10); // Set prescaler to 1 ==> no prescaling
  TIMSK1 |= (1 << OCIE1A); // Enable compare timer interrupt
  
  interrupts(); //interrupts abled
}
ISR(TIMER1_COMPA_vect) {
  PORTC = TP; // Send the value of TP to the outputs
  TP = ~TP; // Invert TP for the next run
}
void loop() {
  //내용없음
}
