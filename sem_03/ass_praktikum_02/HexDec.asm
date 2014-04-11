* HexDec

PROG       EQU         $1000
DATA       EQU         $1200
CHARS      EQU         $1500
BUFFER     EQU         $2000
DEC        EQU         $2030
NEWLINE    EQU         0x0A
CARRETURN  EQU         0x0D

GETCH      macro
           TRAP #15
           DC.W 3
           endm

PUTCH      macro
           TRAP #15
           DC.W 1
           endm

PUTSTR     macro
           LEA.L STR,A0
           TRAP #15
           DC.W 7
           endm

RINGBELL   macro
           CLR.L D0
           MOVE.B BELL,D0
           TRAP #15
           DC.W 1
           endm

           ORG         DATA
STR        DC.B        'Enter your Hexchar:',CARRETURN,NEWLINE,0

           ORG         CHARS
NUM        DC.B        0x30
NUMM       DC.B        0x39
SMALL      DC.B        0x41
SMALLL     DC.B        0x46
BIG        DC.B        0x61
BIGG       DC.B        0x66
BELL       DC.B        0x07
MAX        DC.L        0x7FFFFFFF
READLINE   DS.B        8
READCHAR   DS.B        1

GEWICHTE:  DC.L        1000000000
           DC.L        100000000
           DC.L        10000000
           DC.L        1000000
           DC.L        100000
           DC.L        10000
           DC.L        1000
           DC.L        100
           DC.L        10
           DC.L        1

           ORG         PROG

           PUTSTR
START:
           GETCH
           BRA         CHECKNUM
           BRA         END

CHECKNUM:
           CMP.B       NUM,D0
           BLT         WRONG
           CMP.B       NUMM,D0
           BLE         RIGHTNUM
           BRA         CHECKBIG

CHECKBIG:
           CMP.B       SMALL,D0
           BLT         WRONG
           CMP.B       SMALLL,D0
           BLE         RIGHTBIG
           BRA         CHECKSMALL

CHECKSMALL:
           CMP.B       BIG,D0
           BLT         WRONG
           CMP.B       BIGG,D0
           BLE         RIGHTSMALL
           BRA         WRONG

RIGHTNUM:
           LSL.L       #4,D1
           SUB.B       #$30,D0
           BRA         RIGHT

RIGHTBIG:
           LSL.L       #4,D1
           SUB.B       #$37,D0
           BRA         RIGHT

RIGHTSMALL:
           LSL.L       #4,D1
           SUB.B       #$57,D0
           BRA         RIGHT

RIGHT:
           OR.B        D0,D1

           CMP.B       #4,D2
           BGE         RIGHTB

           LSL.L       #8,D3
           OR.B        D0,D3

           ADD.B       #1,D2
           CMP.B       #8,D2
           BGE         INITBUFF
           BRA         START

RIGHTB:
           LSL.L       #8,D4
           OR.B        D0,D4

           ADD.B       #1,D2
           CMP.B       #8,D2
           BGE         INITBUFF
           BRA         START
WRONG:
           RINGBELL
           BRA         START

INITBUFF:
           MOVE.L      MAX,D6
           CMP.L       D1,D6
           BLE         END
           LEA.L       BUFFER,A6
           MOVE.L      D3,(A6)
           MOVE.L      D4,(4,A6)
           LEA.L       DEC,A4
           LEA.L       GEWICHTE,A5
           BGE         WRITEBUFF

WRITEBUFF:
           MOVE.L      (A5),D6
           CMP.L       D1,D6
           BLE         SUB

           ADDQ        #1,A4
           ADDQ        #4,A5

           ADD.B       #1,D7
           CMP.B       #10,D7
           BGE         TOCHAR

           BRA         WRITEBUFF

SUB:
           ADD.B       #1,(A4)
           MOVE.L      (A5),D5
           SUB.L       D5,D1
           BRA         WRITEBUFF

TOCHAR:
           CLR         D7
           CLR         D2
           ADD.B       #$30,D2
           LEA.L       DEC,A4
           BRA         TOCHAR2
TOCHAR2:
           CLR         D2
           ADD.B       #$30,D2
           ADD.B       (A4),D2
           MOVE.B      D2,(A4)+

           ADD.B       #1,D7

           CMP.L       #10,D7
           BGE         OUT
           BRA         TOCHAR2

OUT:
           MOVE.B      0,(A4)
           LEA.L       DEC,A0
           TRAP        #15
           DC.W        7
           BRA         END
END:
           MOVE.B      D1,D3
           STOP        #$2000
           END         PROG