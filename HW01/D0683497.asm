WORK1	START           1000
INLP	TD              INDEV
	    JEQ             INLP
	    RD              INDEV
	    STCH            DATA

OUTLP	TD              OUTDEV
	    JEQ             OUTLP
	    LDCH            DATA
	    JSUB            TOUP
	    WD              OUTDEV
	    COMP            DOLLAR
	    JEQ             EXIT
	    J               INLP

TOUP	COMP            LOWA
	    JLT             RETURN
	    COMP            LOWZ
	    JGT             RETURN
	    SUB             #32
	    STCH            DATA
	    RSUB

RETURN	RSUB

INDEV	BYTE            X'F1'
OUTDEV	BYTE            X'F2'
DATA	RESB            1
DOLLAR	WORD            X'000024'
LOWA	WORD            X'000061'
LOWZ	WORD            X'00007A'

EXIT	END             INLP
