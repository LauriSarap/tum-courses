// Pi Hexadezimal, vgl. https://robertlovespi.net/2014/06/09/the-beginning-of-the-number-pi-in-binary-through-hexadecimal-etc/
// 3.243F6 A8885 A308D 31319 8A2E0 37073 44A40 93822 299F3 1D008 2EFA9 8EC4E 6C894 52821 E638D 01377 BE546 6CF34 E90C6 CC0AC

// Umwandlung in binär; "-" als Trenner zwischen den Blöcken
// 11.0010 0100 0011 1111 0110 - 1010 1000 1000 1000 0101 - 1010 0011 0000 1000 1101 - 0011 0001 0011 0001 1001 - 1000 1010 0010 1110 0000 - 0011 0111 0000 0111 0011 - 

// Ins Format 1.f bringen und Bits in 4er-Gruppen anordnen
// 64 Bit Gleitkommazahl hat Fraction f in den  Bits 51...0 => 52 Bits f
// 52 Bits f => 52/4 = 13 Hex-Stellen für f
//
// |--------------------------- pi_high ----------------------------|   |----------------------------- pi_low --------------------- ...
// 1.------------------------------ f -------------------------------
// 1 1001 0010 0001 1111 1011 0101 0100 0100 0100 0010 1101 0001 1000 = 0100 0110 1001 1000 1001 1000 1100 1100 0101 0001 0111 0000 0001 1011 1000 0011 10011 - 
//      9    2    1    F    B    5    4    4    4    2    D    1    8
//
// => 0x921FB54442D18 ist der f-Teil von pi_high
// für pi: e - k = 1 => e = k + 1 = 1023 + 1 = 1024
// für 2*p: e = 1025
// two_pi_high = 0x401 (Vorzeichen und e) mit 0x921FB54442D18 (f) vereinigt
//
// => two_pi_high = 0x401921FB54442D18
//    ================================
//
// Die restlichen Bits (pi_low)
// 0100 0110 1001 1000 1001 1000 1100 1100 0101 0001 0111 0000 0001 1011 1000 0011 10011
//
// pi_low in die Form 1.f bringen:
//
// 01 0001 1010 0110 0010 0110 0011 0011 0001 0100 0101 1100 0000 0110 1110 0000 1110 011
//       1    A    6    2    6    3    3    1    4    5    C    0    6    E    0    E
// f hat 52/4 = 13 hex-Stellen
//
// => 0x1A62633145C06 ist der f-Teil von pi_low
// für pi: e - k = -53 => e = k - 53 = 1023 - 53 = 970 = 0x3CA
// für 2*pi: 971 = 0x3CB
// two_pi_low = 0x3CB (Vorzeichen und e) vereinigt mit 0x1A62633145C06 (f)
//
// => two_pi_low = 0x3CB1A62633145C06
//    ===============================