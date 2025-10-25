# Linear-Gameboy-ROM-Disassembler

This is a personal project I created in C with C standard libraries that reads a gameboy (.gb) ROM file, converts into the Assembly instructions, and then outputs to the console or to a text file. It reads in the ROM file, parses the machine code, then outputs the assembly instructions based on the Sharp LR35902 CPU instruction set. It was tested with Tetris.gb to ensure proper functionality.

# Usage: 
Console: ./disassembler.exe Game.gb

Text File: ./disassembler.exe Game.gb > output.txt

# Limitations:
This disassembler performs linear decoding, meaning it reads and decodes instructions sequentially without analyzing control flow or data boundaries. It can handle simple ROMs like Tetris but will have issues with MBC (Memory Bank Controller) ROMs such as Pokemon Blue and Pokemon Red. This disassembler simply prints jump offsets and addresses, it does not follow program flow.

# Example Output:
Note: This is only a portion of the full output  
Title: TETRIS  
Cartridge Type: ROM ONLY  
ROM Size: 32 KiB  
RAM Size: 0 KiB  
0150: C3 0C 02 JP $020C  
0153: CD E3 29 CALL $29E3  
0156: F0 41    LDH A,($41)  
0158: E6 03    AND #03  
015A: 20 FA    JR NZ,-6 -> $0156
015C: 46       LD B,(HL)  
015D: F0 41    LDH A,($41)  
015F: E6 03    AND #03  
0161: 20 FA    JR NZ,-6 -> $015D  
0163: 7E       LD A,(HL)  
0164: A0       AND B  
0165: C9       RET   
0166: 7B       LD A,E  
0167: 86       ADD A,(HL)  
0168: 27       DAA   
0169: 22       LD (HL+),A  
016A: 7A       LD A,D  
016B: 8E       ADC A,(HL)  
016C: 27       DAA   
016D: 22       LD (HL+),A  
016E: 3E 00    LD A,#00  
0170: 8E       ADC A,(HL)  
0171: 27       DAA   
0172: 77       LD (HL),A  
0173: 3E 01    LD A,#01  
0175: E0 E0    LDH ($E0),A  
