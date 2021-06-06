/PROG HUAB
/ATTR
OWNER			= MNEDITOR;
COMMENT			= "";
PROG_SIZE		= 4757;
FILE_NAME		= HUAB;
VERSION			= 0;
LINE_COUNT		= 5;
MEMORY_SIZE		= 5089;
PROTECT			= READ_WRITE;
TCD:  STACK_SIZE		= 0,
      TASK_PRIORITY		= 50,
      TIME_SLICE		= 0,
      BUSY_LAMP_OFF		= 0,
      ABORT_REQUEST		= 0,
      PAUSE_REQUEST		= 0;
DEFAULT_GROUP	= 1,*,*,*,*;
CONTROL_CODE	= 00000000 00000000;
/MN
	1:  UFRAME_NUM=0 ;
	2:  UTOOL_NUM=1 ;
	3:	;
	4:L P[1] 200mm/sec CNT60;
	5:L P[2] 200mm/sec CNT60;
	6:L P[3] 200mm/sec CNT60;
	7:L P[4] 200mm/sec CNT60;
	8:L P[5] 200mm/sec CNT60;
/POS
P[1]{
   GP1:
	UF : 0, UT : 1,		CONFIG : 'N U T, 0, 0, 0',
	X =	1.000000	mm,	Y =	2.000000	mm,	Z =	3.000000	mm,
	W =	40.150104	deg,	P =	8.838562	deg,	R =	134.298454	deg
};
P[2]{
   GP1:
	UF : 0, UT : 1,		CONFIG : 'N U T, 0, 0, 0',
	X =	1.000000	mm,	Y =	2.000000	mm,	Z =	3.000000	mm,
	W =	40.150104	deg,	P =	8.838562	deg,	R =	134.298454	deg
};
P[3]{
   GP1:
	UF : 0, UT : 1,		CONFIG : 'N U T, 0, 0, 0',
	X =	1.000000	mm,	Y =	2.000000	mm,	Z =	3.000000	mm,
	W =	40.150104	deg,	P =	8.838562	deg,	R =	134.298454	deg
};
P[4]{
   GP1:
	UF : 0, UT : 1,		CONFIG : 'N U T, 0, 0, 0',
	X =	1.000000	mm,	Y =	2.000000	mm,	Z =	3.000000	mm,
	W =	40.150104	deg,	P =	8.838562	deg,	R =	134.298454	deg
};
P[5]{
   GP1:
	UF : 0, UT : 1,		CONFIG : 'N U T, 0, 0, 0',
	X =	1.000000	mm,	Y =	2.000000	mm,	Z =	3.000000	mm,
	W =	40.150104	deg,	P =	8.838562	deg,	R =	134.298454	deg
};

/END