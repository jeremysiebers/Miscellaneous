##############################################################################
#
#     FILE: readme.txt
#  PURPOSE: File descriptions
#
##############################################################################

hex2eedata.awk -- Awk program for translating Intel HEX into __EEPROM_DATA()
                  lines.  See the program's header comment for documentation.

eeprom.hex     -- Test Intel HEX input file.

eeprom_data.c  -- Result of gawk -f hex2eedata.awk eeprom.hex > eeprom_data.c

gawk.exe       -- A standalone Win32 implementation of the GNU awk
                  interpreter from http://unxutils.sourceforge.net/

intelhex.txt   -- Intel HEX file format specification.

readme.txt     -- This file.
