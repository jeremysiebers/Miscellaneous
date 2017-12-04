/* 
 * File:   eeprom_settings.h
 * Author: Jeremy Siebers
 *
 * Created on October 8, 2017, 2:54 PM
 */

#ifndef EEPROM_SETTINGS_H
#define	EEPROM_SETTINGS_H

#ifdef	__cplusplus
extern "C" {
#endif

extern unsigned int EEPROMxSTORE(void);
extern unsigned int EEPROMxREAD(void);

void Eeprom_Store(unsigned int Location, unsigned int Value);
unsigned int Eeprom_Read(unsigned int Location);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_SETTINGS_H */

