           ORG         $14000
MyISRL:    MOVEM.L     D0-D3/A1/A3,-(A7)
           CLR.L       D0
           MOVE.B      $E003,D0
           ROL.B       #1,D0
           MOVE.B      D0,$E003
           MOVEM.L     (A7)+,D0-D3/A1/A3
           RTE

MyISRR:    MOVEM.L     D0-D3/A1/A3,-(A7)
           CLR.L       D0
           MOVE.B      $E003,D0
           ROR.B       #1,D0
           MOVE.B      D0,$E003
           MOVEM.L     (A7)+,D0-D3/A1/A3
           RTE

           ORG         $9000
SUPERSTACK DS.L        $1000
           ORG         $10000
USERSTACK  DS.L        $1000

           ORG         $15000
MAIN:      TRAP        #15
           DC.W        32
           MOVE.L      #MyISRL,$006C
           MOVE.L      #MyISRR,$0070
           MOVE.B      #$08,$E003
           ANDI        #$2000,SR

           MOVE.L      #123,$8000

           MOVE.L      SUPERSTACK,A7
           MOVE.L      USERSTACK,A0
           MOVE        A0,USP
           ANDI        #$DFFF,SR

           MOVE.L      $8000,D0
           MOVE.L      #412,$8000
           MOVE.L      $8000,D0

           BRA         SUBLOOP

SUBLOOP:   BRA         *


           STOP        #$2000
           END         MAIN

