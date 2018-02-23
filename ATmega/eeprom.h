#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

//eeprom read, from usb1286 datasheet
unsigned char eeprom_read(unsigned int uiAddress);
//eeprom write, from usb1286 datasheet
void eeprom_write(unsigned int uiAddress, unsigned char ucData);

#endif // EEPROM_H_INCLUDED
