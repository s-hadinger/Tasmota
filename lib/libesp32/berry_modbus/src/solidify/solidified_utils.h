/* Solidification of utils.h */
/********************************************************************\
* Generated code, don't edit                                         *
\********************************************************************/
#include "be_constobj.h"

/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x541203E7,  //  0003  LDINT	R4	1000
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 5]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_nested_str_weak(trimToLimits),
    /* K3   */  be_const_real_hex(0x3C23D70B),
    /* K4   */  be_const_real_hex(0x3F7D70A5),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[12]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0xB80E0000,  //  0002  GETNGBL	R3	K0
      0x8C0C0702,  //  0003  GETMET	R3	R3	K2
      0x5C140000,  //  0004  MOVE	R5	R0
      0x58180003,  //  0005  LDCONST	R6	K3
      0x581C0004,  //  0006  LDCONST	R7	K4
      0x7C0C0800,  //  0007  CALL	R3	4
      0x54120063,  //  0008  LDINT	R4	100
      0x5416001F,  //  0009  LDINT	R5	32
      0x7C040800,  //  000A  CALL	R1	4
      0x80040200,  //  000B  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    2,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_const_int(0),
    /* K1   */  be_const_int(1),
    /* K2   */  be_const_int(2),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[25]) {  /* code */
      0x58080000,  //  0000  LDCONST	R2	K0
      0x580C0001,  //  0001  LDCONST	R3	K1
      0x24100100,  //  0002  GT	R4	R0	K0
      0x78120012,  //  0003  JMPF	R4	#0017
      0x24100300,  //  0004  GT	R4	R1	K0
      0x78120010,  //  0005  JMPF	R4	#0017
      0x10100102,  //  0006  MOD	R4	R0	K2
      0x1C100901,  //  0007  EQ	R4	R4	K1
      0x78120003,  //  0008  JMPF	R4	#000D
      0x10100302,  //  0009  MOD	R4	R1	K2
      0x1C100901,  //  000A  EQ	R4	R4	K1
      0x78120000,  //  000B  JMPF	R4	#000D
      0x00080403,  //  000C  ADD	R2	R2	R3
      0x080C0702,  //  000D  MUL	R3	R3	K2
      0x60100009,  //  000E  GETGBL	R4	G9
      0x0C140102,  //  000F  DIV	R5	R0	K2
      0x7C100200,  //  0010  CALL	R4	1
      0x5C000800,  //  0011  MOVE	R0	R4
      0x60100009,  //  0012  GETGBL	R4	G9
      0x0C140302,  //  0013  DIV	R5	R1	K2
      0x7C100200,  //  0014  CALL	R4	1
      0x5C040800,  //  0015  MOVE	R1	R4
      0x7001FFEA,  //  0016  JMP		#0002
      0x20100500,  //  0017  NE	R4	R2	K0
      0x80040800,  //  0018  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(real),
    /* K1   */  be_nested_str_weak(int),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[16]) {  /* code */
      0x4C040000,  //  0000  LDNIL	R1
      0x20040001,  //  0001  NE	R1	R0	R1
      0x78060009,  //  0002  JMPF	R1	#000D
      0x60040004,  //  0003  GETGBL	R1	G4
      0x5C080000,  //  0004  MOVE	R2	R0
      0x7C040200,  //  0005  CALL	R1	1
      0x1C040300,  //  0006  EQ	R1	R1	K0
      0x74060005,  //  0007  JMPT	R1	#000E
      0x60040004,  //  0008  GETGBL	R1	G4
      0x5C080000,  //  0009  MOVE	R2	R0
      0x7C040200,  //  000A  CALL	R1	1
      0x1C040301,  //  000B  EQ	R1	R1	K1
      0x74060000,  //  000C  JMPT	R1	#000E
      0x50040001,  //  000D  LDBOOL	R1	0	1
      0x50040200,  //  000E  LDBOOL	R1	1	0
      0x80040200,  //  000F  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_const_real_hex(0x3ECCCCCD),
    /* K1   */  be_const_real_hex(0x4426ECCD),
    /* K2   */  be_const_real_hex(0x3F800000),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[13]) {  /* code */
      0x58040000,  //  0000  LDCONST	R1	K0
      0x540A05DB,  //  0001  LDINT	R2	1500
      0x580C0001,  //  0002  LDCONST	R3	K1
      0x60100007,  //  0003  GETGBL	R4	G7
      0x5C140000,  //  0004  MOVE	R5	R0
      0x7C100200,  //  0005  CALL	R4	1
      0x08120404,  //  0006  MUL	R4	K2	R4
      0x04100802,  //  0007  SUB	R4	R4	R2
      0x0C100803,  //  0008  DIV	R4	R4	R3
      0x0C100801,  //  0009  DIV	R4	R4	R1
      0x54160009,  //  000A  LDINT	R5	10
      0x08140805,  //  000B  MUL	R5	R4	R5
      0x80040A00,  //  000C  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 4]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_nested_str_weak(trimToLimits),
    /* K3   */  be_const_int(0),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[12]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0xB80E0000,  //  0002  GETNGBL	R3	K0
      0x8C0C0702,  //  0003  GETMET	R3	R3	K2
      0x5C140000,  //  0004  MOVE	R5	R0
      0x58180003,  //  0005  LDCONST	R6	K3
      0x541E0063,  //  0006  LDINT	R7	100
      0x7C0C0800,  //  0007  CALL	R3	4
      0x541203E7,  //  0008  LDINT	R4	1000
      0x5416001F,  //  0009  LDINT	R5	32
      0x7C040800,  //  000A  CALL	R1	4
      0x80040200,  //  000B  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 6]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(calculate_mean),
    /* K2   */  be_const_real_hex(0x00000000),
    /* K3   */  be_nested_str_weak(stop_iteration),
    /* K4   */  be_nested_str_weak(math),
    /* K5   */  be_nested_str_weak(sqrt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[27]) {  /* code */
      0x6004000C,  //  0000  GETGBL	R1	G12
      0x5C080000,  //  0001  MOVE	R2	R0
      0x7C040200,  //  0002  CALL	R1	1
      0xB80A0000,  //  0003  GETNGBL	R2	K0
      0x8C080501,  //  0004  GETMET	R2	R2	K1
      0x5C100000,  //  0005  MOVE	R4	R0
      0x7C080400,  //  0006  CALL	R2	2
      0x580C0002,  //  0007  LDCONST	R3	K2
      0x60100010,  //  0008  GETGBL	R4	G16
      0x5C140000,  //  0009  MOVE	R5	R0
      0x7C100200,  //  000A  CALL	R4	1
      0xA8020006,  //  000B  EXBLK	0	#0013
      0x5C140800,  //  000C  MOVE	R5	R4
      0x7C140000,  //  000D  CALL	R5	0
      0x04180A02,  //  000E  SUB	R6	R5	R2
      0x041C0A02,  //  000F  SUB	R7	R5	R2
      0x08180C07,  //  0010  MUL	R6	R6	R7
      0x000C0606,  //  0011  ADD	R3	R3	R6
      0x7001FFF8,  //  0012  JMP		#000C
      0x58100003,  //  0013  LDCONST	R4	K3
      0xAC100200,  //  0014  CATCH	R4	1	0
      0xB0080000,  //  0015  RAISE	2	R0	R0
      0xB8120800,  //  0016  GETNGBL	R4	K4
      0x8C100905,  //  0017  GETMET	R4	R4	K5
      0x0C180601,  //  0018  DIV	R6	R3	R1
      0x7C100400,  //  0019  CALL	R4	2
      0x80040800,  //  001A  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120009,  //  0003  LDINT	R4	10
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    1,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    0,                          /* has constants */
    NULL,                       /* no const */
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 1]) {  /* code */
      0x80000000,  //  0000  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x58140002,  //  0004  LDCONST	R5	K2
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    2,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    0,                          /* has constants */
    NULL,                       /* no const */
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 4]) {  /* code */
      0x14080001,  //  0000  LT	R2	R0	R1
      0x780A0000,  //  0001  JMPF	R2	#0003
      0x80040000,  //  0002  RET	1	R0
      0x80040200,  //  0003  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    10,                          /* nstack */
    3,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 5]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(trimToBits),
    /* K2   */  be_nested_str_weak(math),
    /* K3   */  be_nested_str_weak(floor),
    /* K4   */  be_nested_str_weak(tostring),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[27]) {  /* code */
      0x5C0C0000,  //  0000  MOVE	R3	R0
      0x740E0001,  //  0001  JMPT	R3	#0004
      0x4C0C0000,  //  0002  LDNIL	R3
      0x80040600,  //  0003  RET	1	R3
      0x600C0007,  //  0004  GETGBL	R3	G7
      0x5C100000,  //  0005  MOVE	R4	R0
      0x7C0C0200,  //  0006  CALL	R3	1
      0x4C100000,  //  0007  LDNIL	R4
      0x1C100604,  //  0008  EQ	R4	R3	R4
      0x78120001,  //  0009  JMPF	R4	#000C
      0x4C100000,  //  000A  LDNIL	R4
      0x80040800,  //  000B  RET	1	R4
      0x60100012,  //  000C  GETGBL	R4	G18
      0x7C100000,  //  000D  CALL	R4	0
      0xB8160000,  //  000E  GETNGBL	R5	K0
      0x8C140B01,  //  000F  GETMET	R5	R5	K1
      0xB81E0400,  //  0010  GETNGBL	R7	K2
      0x8C1C0F03,  //  0011  GETMET	R7	R7	K3
      0x08240601,  //  0012  MUL	R9	R3	R1
      0x7C1C0400,  //  0013  CALL	R7	2
      0x5C200400,  //  0014  MOVE	R8	R2
      0x50240200,  //  0015  LDBOOL	R9	1	0
      0x7C140800,  //  0016  CALL	R5	4
      0x40140805,  //  0017  CONNECT	R5	R4	R5
      0x8C140904,  //  0018  GETMET	R5	R4	K4
      0x7C140200,  //  0019  CALL	R5	1
      0x80040A00,  //  001A  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120063,  //  0003  LDINT	R4	100
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    7,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[12]) {     /* constants */
    /* K0   */  be_const_int(0),
    /* K1   */  be_nested_str_weak(string),
    /* K2   */  be_nested_str_weak(find),
    /* K3   */  be_nested_str_weak(connecting),
    /* K4   */  be_const_int(1),
    /* K5   */  be_nested_str_weak(connected),
    /* K6   */  be_const_int(2),
    /* K7   */  be_nested_str_weak(disconnected),
    /* K8   */  be_const_int(3),
    /* K9   */  be_nested_str_weak(format),
    /* K10  */  be_nested_str_weak(_X25i),
    /* K11  */  be_nested_str_weak(tostring),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[43]) {  /* code */
      0x58040000,  //  0000  LDCONST	R1	K0
      0xB80A0200,  //  0001  GETNGBL	R2	K1
      0x8C080502,  //  0002  GETMET	R2	R2	K2
      0x5C100000,  //  0003  MOVE	R4	R0
      0x58140003,  //  0004  LDCONST	R5	K3
      0x7C080600,  //  0005  CALL	R2	3
      0x4C0C0000,  //  0006  LDNIL	R3
      0x20080403,  //  0007  NE	R2	R2	R3
      0x780A0001,  //  0008  JMPF	R2	#000B
      0x58040004,  //  0009  LDCONST	R1	K4
      0x70020014,  //  000A  JMP		#0020
      0xB80A0200,  //  000B  GETNGBL	R2	K1
      0x8C080502,  //  000C  GETMET	R2	R2	K2
      0x5C100000,  //  000D  MOVE	R4	R0
      0x58140005,  //  000E  LDCONST	R5	K5
      0x7C080600,  //  000F  CALL	R2	3
      0x4C0C0000,  //  0010  LDNIL	R3
      0x20080403,  //  0011  NE	R2	R2	R3
      0x780A0001,  //  0012  JMPF	R2	#0015
      0x58040006,  //  0013  LDCONST	R1	K6
      0x7002000A,  //  0014  JMP		#0020
      0xB80A0200,  //  0015  GETNGBL	R2	K1
      0x8C080502,  //  0016  GETMET	R2	R2	K2
      0x5C100000,  //  0017  MOVE	R4	R0
      0x58140007,  //  0018  LDCONST	R5	K7
      0x7C080600,  //  0019  CALL	R2	3
      0x4C0C0000,  //  001A  LDNIL	R3
      0x20080403,  //  001B  NE	R2	R2	R3
      0x780A0001,  //  001C  JMPF	R2	#001F
      0x58040008,  //  001D  LDCONST	R1	K8
      0x70020000,  //  001E  JMP		#0020
      0x58040000,  //  001F  LDCONST	R1	K0
      0x60080012,  //  0020  GETGBL	R2	G18
      0x7C080000,  //  0021  CALL	R2	0
      0xB80E0200,  //  0022  GETNGBL	R3	K1
      0x8C0C0709,  //  0023  GETMET	R3	R3	K9
      0x5814000A,  //  0024  LDCONST	R5	K10
      0x5C180200,  //  0025  MOVE	R6	R1
      0x7C0C0600,  //  0026  CALL	R3	3
      0x400C0403,  //  0027  CONNECT	R3	R2	R3
      0x8C0C050B,  //  0028  GETMET	R3	R2	K11
      0x7C0C0200,  //  0029  CALL	R3	1
      0x80040600,  //  002A  RET	1	R3
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120063,  //  0003  LDINT	R4	100
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120009,  //  0003  LDINT	R4	10
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    7,                          /* nstack */
    2,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(calculate_covariance),
    /* K2   */  be_nested_str_weak(calculate_standard_deviation),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[25]) {  /* code */
      0x60080000,  //  0000  GETGBL	R2	G0
      0x600C000C,  //  0001  GETGBL	R3	G12
      0x5C100000,  //  0002  MOVE	R4	R0
      0x7C0C0200,  //  0003  CALL	R3	1
      0x6010000C,  //  0004  GETGBL	R4	G12
      0x5C140200,  //  0005  MOVE	R5	R1
      0x7C100200,  //  0006  CALL	R4	1
      0x1C0C0604,  //  0007  EQ	R3	R3	R4
      0x7C080200,  //  0008  CALL	R2	1
      0xB80A0000,  //  0009  GETNGBL	R2	K0
      0x8C080501,  //  000A  GETMET	R2	R2	K1
      0x5C100000,  //  000B  MOVE	R4	R0
      0x5C140200,  //  000C  MOVE	R5	R1
      0x7C080600,  //  000D  CALL	R2	3
      0xB80E0000,  //  000E  GETNGBL	R3	K0
      0x8C0C0702,  //  000F  GETMET	R3	R3	K2
      0x5C140000,  //  0010  MOVE	R5	R0
      0x7C0C0400,  //  0011  CALL	R3	2
      0xB8120000,  //  0012  GETNGBL	R4	K0
      0x8C100902,  //  0013  GETMET	R4	R4	K2
      0x5C180200,  //  0014  MOVE	R6	R1
      0x7C100400,  //  0015  CALL	R4	2
      0x08140604,  //  0016  MUL	R5	R3	R4
      0x0C140405,  //  0017  DIV	R5	R2	R5
      0x80040A00,  //  0018  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    7,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 4]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    /* K2   */  be_const_int(1),
    /* K3   */  be_nested_str_weak(_X25s_X2E_X25s_X2E_X25s),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[20]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x60080018,  //  0006  GETGBL	R2	G24
      0x580C0003,  //  0007  LDCONST	R3	K3
      0x54120EFF,  //  0008  LDINT	R4	3840
      0x2C100204,  //  0009  AND	R4	R1	R4
      0x54160007,  //  000A  LDINT	R5	8
      0x3C100805,  //  000B  SHR	R4	R4	R5
      0x541600EF,  //  000C  LDINT	R5	240
      0x2C140205,  //  000D  AND	R5	R1	R5
      0x541A0003,  //  000E  LDINT	R6	4
      0x3C140A06,  //  000F  SHR	R5	R5	R6
      0x541A000E,  //  0010  LDINT	R6	15
      0x2C180206,  //  0011  AND	R6	R1	R6
      0x7C080800,  //  0012  CALL	R2	4
      0x80040400,  //  0013  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120063,  //  0003  LDINT	R4	100
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    10,                          /* nstack */
    3,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 8]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(trimToBits),
    /* K2   */  be_nested_str_weak(math),
    /* K3   */  be_nested_str_weak(floor),
    /* K4   */  be_const_int(0),
    /* K5   */  be_nested_str_weak(pow),
    /* K6   */  be_const_int(2),
    /* K7   */  be_nested_str_weak(tostring),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[46]) {  /* code */
      0x5C0C0000,  //  0000  MOVE	R3	R0
      0x740E0001,  //  0001  JMPT	R3	#0004
      0x4C0C0000,  //  0002  LDNIL	R3
      0x80040600,  //  0003  RET	1	R3
      0x600C0007,  //  0004  GETGBL	R3	G7
      0x5C100000,  //  0005  MOVE	R4	R0
      0x7C0C0200,  //  0006  CALL	R3	1
      0x4C100000,  //  0007  LDNIL	R4
      0x1C100604,  //  0008  EQ	R4	R3	R4
      0x78120001,  //  0009  JMPF	R4	#000C
      0x4C100000,  //  000A  LDNIL	R4
      0x80040800,  //  000B  RET	1	R4
      0xB8120000,  //  000C  GETNGBL	R4	K0
      0x8C100901,  //  000D  GETMET	R4	R4	K1
      0xB81A0400,  //  000E  GETNGBL	R6	K2
      0x8C180D03,  //  000F  GETMET	R6	R6	K3
      0x08200601,  //  0010  MUL	R8	R3	R1
      0x7C180400,  //  0011  CALL	R6	2
      0x5C1C0400,  //  0012  MOVE	R7	R2
      0x50200000,  //  0013  LDBOOL	R8	0	0
      0x7C100800,  //  0014  CALL	R4	4
      0x5C0C0800,  //  0015  MOVE	R3	R4
      0x24120803,  //  0016  GT	R4	K4	R3
      0x78120009,  //  0017  JMPF	R4	#0022
      0xB8120400,  //  0018  GETNGBL	R4	K2
      0x8C100903,  //  0019  GETMET	R4	R4	K3
      0xB81A0400,  //  001A  GETNGBL	R6	K2
      0x8C180D05,  //  001B  GETMET	R6	R6	K5
      0x58200006,  //  001C  LDCONST	R8	K6
      0x5C240400,  //  001D  MOVE	R9	R2
      0x7C180600,  //  001E  CALL	R6	3
      0x00180C03,  //  001F  ADD	R6	R6	R3
      0x7C100400,  //  0020  CALL	R4	2
      0x5C0C0800,  //  0021  MOVE	R3	R4
      0x60100012,  //  0022  GETGBL	R4	G18
      0x7C100000,  //  0023  CALL	R4	0
      0xB8160000,  //  0024  GETNGBL	R5	K0
      0x8C140B01,  //  0025  GETMET	R5	R5	K1
      0x5C1C0600,  //  0026  MOVE	R7	R3
      0x5C200400,  //  0027  MOVE	R8	R2
      0x50240200,  //  0028  LDBOOL	R9	1	0
      0x7C140800,  //  0029  CALL	R5	4
      0x40140805,  //  002A  CONNECT	R5	R4	R5
      0x8C140907,  //  002B  GETMET	R5	R4	K7
      0x7C140200,  //  002C  CALL	R5	1
      0x80040A00,  //  002D  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    3,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    0,                          /* has constants */
    NULL,                       /* no const */
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[13]) {  /* code */
      0x600C0007,  //  0000  GETGBL	R3	G7
      0x5C100000,  //  0001  MOVE	R4	R0
      0x7C0C0200,  //  0002  CALL	R3	1
      0x24100203,  //  0003  GT	R4	R1	R3
      0x78120001,  //  0004  JMPF	R4	#0007
      0x80040200,  //  0005  RET	1	R1
      0x70020004,  //  0006  JMP		#000C
      0x14100403,  //  0007  LT	R4	R2	R3
      0x78120001,  //  0008  JMPF	R4	#000B
      0x80040400,  //  0009  RET	1	R2
      0x70020000,  //  000A  JMP		#000C
      0x80040600,  //  000B  RET	1	R3
      0x80000000,  //  000C  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120063,  //  0003  LDINT	R4	100
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 4]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_nested_str_weak(trimToLimits),
    /* K3   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[12]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0xB80E0000,  //  0002  GETNGBL	R3	K0
      0x8C0C0702,  //  0003  GETMET	R3	R3	K2
      0x5C140000,  //  0004  MOVE	R5	R0
      0x58180003,  //  0005  LDCONST	R6	K3
      0x541E0009,  //  0006  LDINT	R7	10
      0x7C0C0800,  //  0007  CALL	R3	4
      0x58100003,  //  0008  LDCONST	R4	K3
      0x5416001F,  //  0009  LDINT	R5	32
      0x7C040800,  //  000A  CALL	R1	4
      0x80040200,  //  000B  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x541203E7,  //  0003  LDINT	R4	1000
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    11,                          /* nstack */
    3,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 7]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(trimToLimits),
    /* K2   */  be_const_int(0),
    /* K3   */  be_nested_str_weak(math),
    /* K4   */  be_nested_str_weak(pow),
    /* K5   */  be_const_int(2),
    /* K6   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[32]) {  /* code */
      0x780A000C,  //  0000  JMPF	R2	#000E
      0xB80E0000,  //  0001  GETNGBL	R3	K0
      0x8C0C0701,  //  0002  GETMET	R3	R3	K1
      0x5C140000,  //  0003  MOVE	R5	R0
      0x58180002,  //  0004  LDCONST	R6	K2
      0xB81E0600,  //  0005  GETNGBL	R7	K3
      0x8C1C0F04,  //  0006  GETMET	R7	R7	K4
      0x58240005,  //  0007  LDCONST	R9	K5
      0x5C280200,  //  0008  MOVE	R10	R1
      0x7C1C0600,  //  0009  CALL	R7	3
      0x041C0F06,  //  000A  SUB	R7	R7	K6
      0x7C0C0800,  //  000B  CALL	R3	4
      0x80040600,  //  000C  RET	1	R3
      0x70020010,  //  000D  JMP		#001F
      0xB80E0000,  //  000E  GETNGBL	R3	K0
      0x8C0C0701,  //  000F  GETMET	R3	R3	K1
      0x5C140000,  //  0010  MOVE	R5	R0
      0xB81A0600,  //  0011  GETNGBL	R6	K3
      0x8C180D04,  //  0012  GETMET	R6	R6	K4
      0x58200005,  //  0013  LDCONST	R8	K5
      0x04240306,  //  0014  SUB	R9	R1	K6
      0x7C180600,  //  0015  CALL	R6	3
      0x44180C00,  //  0016  NEG	R6	R6
      0xB81E0600,  //  0017  GETNGBL	R7	K3
      0x8C1C0F04,  //  0018  GETMET	R7	R7	K4
      0x58240005,  //  0019  LDCONST	R9	K5
      0x04280306,  //  001A  SUB	R10	R1	K6
      0x7C1C0600,  //  001B  CALL	R7	3
      0x041C0F06,  //  001C  SUB	R7	R7	K6
      0x7C0C0800,  //  001D  CALL	R3	4
      0x80040600,  //  001E  RET	1	R3
      0x80000000,  //  001F  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_const_int(0),
    /* K1   */  be_nested_str_weak(stop_iteration),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[19]) {  /* code */
      0x58040000,  //  0000  LDCONST	R1	K0
      0x60080010,  //  0001  GETGBL	R2	G16
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x7C080200,  //  0003  CALL	R2	1
      0xA8020003,  //  0004  EXBLK	0	#0009
      0x5C0C0400,  //  0005  MOVE	R3	R2
      0x7C0C0000,  //  0006  CALL	R3	0
      0x00040203,  //  0007  ADD	R1	R1	R3
      0x7001FFFB,  //  0008  JMP		#0005
      0x58080001,  //  0009  LDCONST	R2	K1
      0xAC080200,  //  000A  CATCH	R2	1	0
      0xB0080000,  //  000B  RAISE	2	R0	R0
      0x6008000A,  //  000C  GETGBL	R2	G10
      0x600C000C,  //  000D  GETGBL	R3	G12
      0x5C100000,  //  000E  MOVE	R4	R0
      0x7C0C0200,  //  000F  CALL	R3	1
      0x7C080200,  //  0010  CALL	R2	1
      0x0C080202,  //  0011  DIV	R2	R1	R2
      0x80040400,  //  0012  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x54160007,  //  0004  LDINT	R5	8
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_const_int(1),
    /* K1   */  be_const_int(0),
    /* K2   */  be_nested_str_weak(stop_iteration),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[29]) {  /* code */
      0x60040010,  //  0000  GETGBL	R1	G16
      0x6008000C,  //  0001  GETGBL	R2	G12
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x7C080200,  //  0003  CALL	R2	1
      0x04080500,  //  0004  SUB	R2	R2	K0
      0x400A0002,  //  0005  CONNECT	R2	K0	R2
      0x7C040200,  //  0006  CALL	R1	1
      0xA8020010,  //  0007  EXBLK	0	#0019
      0x5C080200,  //  0008  MOVE	R2	R1
      0x7C080000,  //  0009  CALL	R2	0
      0x940C0002,  //  000A  GETIDX	R3	R0	R2
      0x5C100400,  //  000B  MOVE	R4	R2
      0x24140901,  //  000C  GT	R5	R4	K1
      0x78160008,  //  000D  JMPF	R5	#0017
      0x04140900,  //  000E  SUB	R5	R4	K0
      0x94140005,  //  000F  GETIDX	R5	R0	R5
      0x24140A03,  //  0010  GT	R5	R5	R3
      0x78160004,  //  0011  JMPF	R5	#0017
      0x04140900,  //  0012  SUB	R5	R4	K0
      0x94140005,  //  0013  GETIDX	R5	R0	R5
      0x98000805,  //  0014  SETIDX	R0	R4	R5
      0x04100900,  //  0015  SUB	R4	R4	K0
      0x7001FFF4,  //  0016  JMP		#000C
      0x98000803,  //  0017  SETIDX	R0	R4	R3
      0x7001FFEE,  //  0018  JMP		#0008
      0x58040002,  //  0019  LDCONST	R1	K2
      0xAC040200,  //  001A  CATCH	R1	1	0
      0xB0080000,  //  001B  RAISE	2	R0	R0
      0x80040000,  //  001C  RET	1	R0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120009,  //  0003  LDINT	R4	10
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120009,  //  0003  LDINT	R4	10
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    7,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[10]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    /* K2   */  be_const_int(1),
    /* K3   */  be_nested_str_weak(UNKNOWN),
    /* K4   */  be_nested_str_weak(LTS_X2DRefractometer),
    /* K5   */  be_const_int(2),
    /* K6   */  be_nested_str_weak(LTS_X2DSupervisor),
    /* K7   */  be_nested_str_weak(LTE),
    /* K8   */  be_nested_str_weak(LTF),
    /* K9   */  be_nested_str_weak(_X25s_X20_X28_X25i_X29),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[30]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x58080003,  //  0006  LDCONST	R2	K3
      0x1C0E0401,  //  0007  EQ	R3	K2	R1
      0x780E0001,  //  0008  JMPF	R3	#000B
      0x58080004,  //  0009  LDCONST	R2	K4
      0x7002000C,  //  000A  JMP		#0018
      0x1C0E0A01,  //  000B  EQ	R3	K5	R1
      0x780E0001,  //  000C  JMPF	R3	#000F
      0x58080006,  //  000D  LDCONST	R2	K6
      0x70020008,  //  000E  JMP		#0018
      0x540E000F,  //  000F  LDINT	R3	16
      0x1C0C0601,  //  0010  EQ	R3	R3	R1
      0x780E0001,  //  0011  JMPF	R3	#0014
      0x58080007,  //  0012  LDCONST	R2	K7
      0x70020003,  //  0013  JMP		#0018
      0x540E001F,  //  0014  LDINT	R3	32
      0x1C0C0601,  //  0015  EQ	R3	R3	R1
      0x780E0000,  //  0016  JMPF	R3	#0018
      0x58080008,  //  0017  LDCONST	R2	K8
      0x600C0018,  //  0018  GETGBL	R3	G24
      0x58100009,  //  0019  LDCONST	R4	K9
      0x5C140400,  //  001A  MOVE	R5	R2
      0x5C180200,  //  001B  MOVE	R6	R1
      0x7C0C0600,  //  001C  CALL	R3	3
      0x80040600,  //  001D  RET	1	R3
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 5]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterInt),
    /* K2   */  be_nested_str_weak(trimToLimits),
    /* K3   */  be_const_int(2147483647),
    /* K4   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[12]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0xB80E0000,  //  0002  GETNGBL	R3	K0
      0x8C0C0702,  //  0003  GETMET	R3	R3	K2
      0x5C140000,  //  0004  MOVE	R5	R0
      0x541A018F,  //  0005  LDINT	R6	400
      0x581C0003,  //  0006  LDCONST	R7	K3
      0x7C0C0800,  //  0007  CALL	R3	4
      0x58100004,  //  0008  LDCONST	R4	K4
      0x5416001F,  //  0009  LDINT	R5	32
      0x7C040800,  //  000A  CALL	R1	4
      0x80040200,  //  000B  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120063,  //  0003  LDINT	R4	100
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_const_int(1000000),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x541203E7,  //  0003  LDINT	R4	1000
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120009,  //  0003  LDINT	R4	10
      0x54160007,  //  0004  LDINT	R5	8
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120009,  //  0003  LDINT	R4	10
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x541203E7,  //  0003  LDINT	R4	1000
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    1,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    0,                          /* has constants */
    NULL,                       /* no const */
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 1]) {  /* code */
      0x80040000,  //  0000  RET	1	R0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 4]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_nested_str_weak(trimToLimits),
    /* K3   */  be_const_int(0),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[12]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0xB80E0000,  //  0002  GETNGBL	R3	K0
      0x8C0C0702,  //  0003  GETMET	R3	R3	K2
      0x5C140000,  //  0004  MOVE	R5	R0
      0x58180003,  //  0005  LDCONST	R6	K3
      0x541E007E,  //  0006  LDINT	R7	127
      0x7C0C0800,  //  0007  CALL	R3	4
      0x54120009,  //  0008  LDINT	R4	10
      0x5416001F,  //  0009  LDINT	R5	32
      0x7C040800,  //  000A  CALL	R1	4
      0x80040200,  //  000B  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 4]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_nested_str_weak(trimToLimits),
    /* K3   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[12]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0xB80E0000,  //  0002  GETNGBL	R3	K0
      0x8C0C0702,  //  0003  GETMET	R3	R3	K2
      0x5C140000,  //  0004  MOVE	R5	R0
      0x58180003,  //  0005  LDCONST	R6	K3
      0x541E0009,  //  0006  LDINT	R7	10
      0x7C0C0800,  //  0007  CALL	R3	4
      0x54120009,  //  0008  LDINT	R4	10
      0x5416001F,  //  0009  LDINT	R5	32
      0x7C040800,  //  000A  CALL	R1	4
      0x80040200,  //  000B  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    15,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[10]) {     /* constants */
    /* K0   */  be_nested_str_weak(),
    /* K1   */  be_const_int(1),
    /* K2   */  be_const_int(2),
    /* K3   */  be_const_int(0),
    /* K4   */  be_nested_str_weak(string),
    /* K5   */  be_nested_str_weak(format),
    /* K6   */  be_nested_str_weak(_X25s_X25_X2E4x),
    /* K7   */  be_nested_str_weak(sub),
    /* K8   */  be_nested_str_weak(stop_iteration),
    /* K9   */  be_nested_str_weak(tostring),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[45]) {  /* code */
      0x58040000,  //  0000  LDCONST	R1	K0
      0x60080012,  //  0001  GETGBL	R2	G18
      0x7C080000,  //  0002  CALL	R2	0
      0x400C0501,  //  0003  CONNECT	R3	R2	K1
      0x540E0005,  //  0004  LDINT	R3	6
      0x400C0403,  //  0005  CONNECT	R3	R2	R3
      0x400C0502,  //  0006  CONNECT	R3	R2	K2
      0x600C0010,  //  0007  GETGBL	R3	G16
      0x6010000C,  //  0008  GETGBL	R4	G12
      0x5C140400,  //  0009  MOVE	R5	R2
      0x7C100200,  //  000A  CALL	R4	1
      0x04100901,  //  000B  SUB	R4	R4	K1
      0x40120604,  //  000C  CONNECT	R4	K3	R4
      0x7C0C0200,  //  000D  CALL	R3	1
      0xA8020010,  //  000E  EXBLK	0	#0020
      0x5C100600,  //  000F  MOVE	R4	R3
      0x7C100000,  //  0010  CALL	R4	0
      0xB8160800,  //  0011  GETNGBL	R5	K4
      0x8C140B05,  //  0012  GETMET	R5	R5	K5
      0x581C0006,  //  0013  LDCONST	R7	K6
      0x5C200200,  //  0014  MOVE	R8	R1
      0x60240007,  //  0015  GETGBL	R9	G7
      0xB82A0800,  //  0016  GETNGBL	R10	K4
      0x8C281507,  //  0017  GETMET	R10	R10	K7
      0x5C300000,  //  0018  MOVE	R12	R0
      0x5C340800,  //  0019  MOVE	R13	R4
      0x00380901,  //  001A  ADD	R14	R4	K1
      0x7C280800,  //  001B  CALL	R10	4
      0x7C240200,  //  001C  CALL	R9	1
      0x7C140800,  //  001D  CALL	R5	4
      0x5C040A00,  //  001E  MOVE	R1	R5
      0x7001FFEE,  //  001F  JMP		#000F
      0x580C0008,  //  0020  LDCONST	R3	K8
      0xAC0C0200,  //  0021  CATCH	R3	1	0
      0xB0080000,  //  0022  RAISE	2	R0	R0
      0x600C0012,  //  0023  GETGBL	R3	G18
      0x7C0C0000,  //  0024  CALL	R3	0
      0x60100007,  //  0025  GETGBL	R4	G7
      0x5C140200,  //  0026  MOVE	R5	R1
      0x541A000F,  //  0027  LDINT	R6	16
      0x7C100400,  //  0028  CALL	R4	2
      0x40100604,  //  0029  CONNECT	R4	R3	R4
      0x8C100709,  //  002A  GETMET	R4	R3	K9
      0x7C100200,  //  002B  CALL	R4	1
      0x80040800,  //  002C  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x541203E7,  //  0003  LDINT	R4	1000
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 6]) {     /* constants */
    /* K0   */  be_nested_str_weak(instance),
    /* K1   */  be_nested_str_weak(contains),
    /* K2   */  be_nested_str_weak(ModbusReceived),
    /* K3   */  be_nested_str_weak(find),
    /* K4   */  be_nested_str_weak(Values),
    /* K5   */  be_const_int(0),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[23]) {  /* code */
      0x4C040000,  //  0000  LDNIL	R1
      0x60080004,  //  0001  GETGBL	R2	G4
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x7C080200,  //  0003  CALL	R2	1
      0x1C080500,  //  0004  EQ	R2	R2	K0
      0x780A000F,  //  0005  JMPF	R2	#0016
      0x8C080101,  //  0006  GETMET	R2	R0	K1
      0x58100002,  //  0007  LDCONST	R4	K2
      0x7C080400,  //  0008  CALL	R2	2
      0x780A000B,  //  0009  JMPF	R2	#0016
      0x94080102,  //  000A  GETIDX	R2	R0	K2
      0x8C0C0503,  //  000B  GETMET	R3	R2	K3
      0x58140004,  //  000C  LDCONST	R5	K4
      0x7C0C0400,  //  000D  CALL	R3	2
      0x780E0006,  //  000E  JMPF	R3	#0016
      0x94040504,  //  000F  GETIDX	R1	R2	K4
      0x600C000C,  //  0010  GETGBL	R3	G12
      0x5C100200,  //  0011  MOVE	R4	R1
      0x7C0C0200,  //  0012  CALL	R3	1
      0x1C0C0705,  //  0013  EQ	R3	R3	K5
      0x780E0000,  //  0014  JMPF	R3	#0016
      0x4C040000,  //  0015  LDNIL	R1
      0x80040200,  //  0016  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[11]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(is_number),
    /* K2   */  be_nested_str_weak(value),
    /* K3   */  be_nested_str_weak(error),
    /* K4   */  be_nested_str_weak(level_flags),
    /* K5   */  be_const_int(0),
    /* K6   */  be_nested_str_weak(level_ultrasonic_not_available),
    /* K7   */  be_const_int(1),
    /* K8   */  be_nested_str_weak(level_air_leak),
    /* K9   */  be_nested_str_weak(air_pressure),
    /* K10  */  be_nested_str_weak(level_error),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[40]) {  /* code */
      0x4C080000,  //  0000  LDNIL	R2
      0x1C080002,  //  0001  EQ	R2	R0	R2
      0x740A0004,  //  0002  JMPT	R2	#0008
      0xB80A0000,  //  0003  GETNGBL	R2	K0
      0x8C080501,  //  0004  GETMET	R2	R2	K1
      0x88100102,  //  0005  GETMBR	R4	R0	K2
      0x7C080400,  //  0006  CALL	R2	2
      0x740A0002,  //  0007  JMPT	R2	#000B
      0x88080303,  //  0008  GETMBR	R2	R1	K3
      0x88080504,  //  0009  GETMBR	R2	R2	K4
      0x80040400,  //  000A  RET	1	R2
      0x88080102,  //  000B  GETMBR	R2	R0	K2
      0x540E007F,  //  000C  LDINT	R3	128
      0x2C0C0403,  //  000D  AND	R3	R2	R3
      0x200C0705,  //  000E  NE	R3	R3	K5
      0x780E0002,  //  000F  JMPF	R3	#0013
      0x880C0303,  //  0010  GETMBR	R3	R1	K3
      0x880C0706,  //  0011  GETMBR	R3	R3	K6
      0x80040600,  //  0012  RET	1	R3
      0x2C0C0507,  //  0013  AND	R3	R2	K7
      0x200C0705,  //  0014  NE	R3	R3	K5
      0x780E0002,  //  0015  JMPF	R3	#0019
      0x880C0303,  //  0016  GETMBR	R3	R1	K3
      0x880C0708,  //  0017  GETMBR	R3	R3	K8
      0x80040600,  //  0018  RET	1	R3
      0x540E0007,  //  0019  LDINT	R3	8
      0x2C0C0403,  //  001A  AND	R3	R2	R3
      0x200C0705,  //  001B  NE	R3	R3	K5
      0x780E0002,  //  001C  JMPF	R3	#0020
      0x880C0303,  //  001D  GETMBR	R3	R1	K3
      0x880C0709,  //  001E  GETMBR	R3	R3	K9
      0x80040600,  //  001F  RET	1	R3
      0x540E00FD,  //  0020  LDINT	R3	254
      0x2C0C0403,  //  0021  AND	R3	R2	R3
      0x200C0705,  //  0022  NE	R3	R3	K5
      0x780E0002,  //  0023  JMPF	R3	#0027
      0x880C0303,  //  0024  GETMBR	R3	R1	K3
      0x880C070A,  //  0025  GETMBR	R3	R3	K10
      0x80040600,  //  0026  RET	1	R3
      0x80000000,  //  0027  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    10,                          /* nstack */
    2,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 5]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(calculate_mean),
    /* K2   */  be_const_real_hex(0x00000000),
    /* K3   */  be_const_int(0),
    /* K4   */  be_nested_str_weak(stop_iteration),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[42]) {  /* code */
      0x60080000,  //  0000  GETGBL	R2	G0
      0x600C000C,  //  0001  GETGBL	R3	G12
      0x5C100000,  //  0002  MOVE	R4	R0
      0x7C0C0200,  //  0003  CALL	R3	1
      0x6010000C,  //  0004  GETGBL	R4	G12
      0x5C140200,  //  0005  MOVE	R5	R1
      0x7C100200,  //  0006  CALL	R4	1
      0x1C0C0604,  //  0007  EQ	R3	R3	R4
      0x7C080200,  //  0008  CALL	R2	1
      0x6008000C,  //  0009  GETGBL	R2	G12
      0x5C0C0000,  //  000A  MOVE	R3	R0
      0x7C080200,  //  000B  CALL	R2	1
      0xB80E0000,  //  000C  GETNGBL	R3	K0
      0x8C0C0701,  //  000D  GETMET	R3	R3	K1
      0x5C140000,  //  000E  MOVE	R5	R0
      0x7C0C0400,  //  000F  CALL	R3	2
      0xB8120000,  //  0010  GETNGBL	R4	K0
      0x8C100901,  //  0011  GETMET	R4	R4	K1
      0x5C180200,  //  0012  MOVE	R6	R1
      0x7C100400,  //  0013  CALL	R4	2
      0x58140002,  //  0014  LDCONST	R5	K2
      0x60180010,  //  0015  GETGBL	R6	G16
      0x601C000C,  //  0016  GETGBL	R7	G12
      0x5C200000,  //  0017  MOVE	R8	R0
      0x7C1C0200,  //  0018  CALL	R7	1
      0x401E0607,  //  0019  CONNECT	R7	K3	R7
      0x7C180200,  //  001A  CALL	R6	1
      0xA8020008,  //  001B  EXBLK	0	#0025
      0x5C1C0C00,  //  001C  MOVE	R7	R6
      0x7C1C0000,  //  001D  CALL	R7	0
      0x94200007,  //  001E  GETIDX	R8	R0	R7
      0x04201003,  //  001F  SUB	R8	R8	R3
      0x94240207,  //  0020  GETIDX	R9	R1	R7
      0x04241204,  //  0021  SUB	R9	R9	R4
      0x08201009,  //  0022  MUL	R8	R8	R9
      0x00140A08,  //  0023  ADD	R5	R5	R8
      0x7001FFF6,  //  0024  JMP		#001C
      0x58180004,  //  0025  LDCONST	R6	K4
      0xAC180200,  //  0026  CATCH	R6	1	0
      0xB0080000,  //  0027  RAISE	2	R0	R0
      0x0C180A02,  //  0028  DIV	R6	R5	R2
      0x80040C00,  //  0029  RET	1	R6
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    11,                          /* nstack */
    3,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[12]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterValue),
    /* K2   */  be_const_int(0),
    /* K3   */  be_nested_str_weak(math),
    /* K4   */  be_nested_str_weak(floor),
    /* K5   */  be_nested_str_weak(trimToBits),
    /* K6   */  be_nested_str_weak(pow),
    /* K7   */  be_const_int(2),
    /* K8   */  be_const_int(1),
    /* K9   */  be_nested_str_weak(string),
    /* K10  */  be_nested_str_weak(format),
    /* K11  */  be_nested_str_weak(_X25f),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[38]) {  /* code */
      0xB80E0000,  //  0000  GETNGBL	R3	K0
      0x8C0C0701,  //  0001  GETMET	R3	R3	K1
      0x5C140000,  //  0002  MOVE	R5	R0
      0x7C0C0400,  //  0003  CALL	R3	2
      0x4C100000,  //  0004  LDNIL	R4
      0x1C100604,  //  0005  EQ	R4	R3	R4
      0x78120001,  //  0006  JMPF	R4	#0009
      0x4C100000,  //  0007  LDNIL	R4
      0x80040800,  //  0008  RET	1	R4
      0x940C0702,  //  0009  GETIDX	R3	R3	K2
      0xB8120600,  //  000A  GETNGBL	R4	K3
      0x8C100904,  //  000B  GETMET	R4	R4	K4
      0xB81A0000,  //  000C  GETNGBL	R6	K0
      0x8C180D05,  //  000D  GETMET	R6	R6	K5
      0x5C200600,  //  000E  MOVE	R8	R3
      0x5C240400,  //  000F  MOVE	R9	R2
      0x50280200,  //  0010  LDBOOL	R10	1	0
      0x7C180800,  //  0011  CALL	R6	4
      0x7C100400,  //  0012  CALL	R4	2
      0xB8160600,  //  0013  GETNGBL	R5	K3
      0x8C140B06,  //  0014  GETMET	R5	R5	K6
      0x581C0007,  //  0015  LDCONST	R7	K7
      0x04200508,  //  0016  SUB	R8	R2	K8
      0x7C140600,  //  0017  CALL	R5	3
      0x18140A04,  //  0018  LE	R5	R5	R4
      0x78160005,  //  0019  JMPF	R5	#0020
      0xB8160600,  //  001A  GETNGBL	R5	K3
      0x8C140B06,  //  001B  GETMET	R5	R5	K6
      0x581C0007,  //  001C  LDCONST	R7	K7
      0x5C200400,  //  001D  MOVE	R8	R2
      0x7C140600,  //  001E  CALL	R5	3
      0x04100805,  //  001F  SUB	R4	R4	R5
      0xB8161200,  //  0020  GETNGBL	R5	K9
      0x8C140B0A,  //  0021  GETMET	R5	R5	K10
      0x581C000B,  //  0022  LDCONST	R7	K11
      0x0C200801,  //  0023  DIV	R8	R4	R1
      0x7C140600,  //  0024  CALL	R5	3
      0x80040A00,  //  0025  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120009,  //  0003  LDINT	R4	10
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120063,  //  0003  LDINT	R4	100
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    9,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 9]) {     /* constants */
    /* K0   */  be_nested_str_weak(),
    /* K1   */  be_nested_str_weak(utils),
    /* K2   */  be_nested_str_weak(getterValue),
    /* K3   */  be_const_int(0),
    /* K4   */  be_const_int(1),
    /* K5   */  be_nested_str_weak(string),
    /* K6   */  be_nested_str_weak(format),
    /* K7   */  be_nested_str_weak(_X25x),
    /* K8   */  be_nested_str_weak(stop_iteration),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[32]) {  /* code */
      0x58040000,  //  0000  LDCONST	R1	K0
      0xB80A0200,  //  0001  GETNGBL	R2	K1
      0x8C080502,  //  0002  GETMET	R2	R2	K2
      0x5C100000,  //  0003  MOVE	R4	R0
      0x7C080400,  //  0004  CALL	R2	2
      0x4C0C0000,  //  0005  LDNIL	R3
      0x1C0C0403,  //  0006  EQ	R3	R2	R3
      0x780E0001,  //  0007  JMPF	R3	#000A
      0x600C0008,  //  0008  GETGBL	R3	G8
      0x80040600,  //  0009  RET	1	R3
      0x600C0010,  //  000A  GETGBL	R3	G16
      0x6010000C,  //  000B  GETGBL	R4	G12
      0x5C140400,  //  000C  MOVE	R5	R2
      0x7C100200,  //  000D  CALL	R4	1
      0x04100904,  //  000E  SUB	R4	R4	K4
      0x40120604,  //  000F  CONNECT	R4	K3	R4
      0x7C0C0200,  //  0010  CALL	R3	1
      0xA8020009,  //  0011  EXBLK	0	#001C
      0x5C100600,  //  0012  MOVE	R4	R3
      0x7C100000,  //  0013  CALL	R4	0
      0xB8160A00,  //  0014  GETNGBL	R5	K5
      0x8C140B06,  //  0015  GETMET	R5	R5	K6
      0x601C0008,  //  0016  GETGBL	R7	G8
      0x001C0F07,  //  0017  ADD	R7	R7	K7
      0x94200404,  //  0018  GETIDX	R8	R2	R4
      0x7C140600,  //  0019  CALL	R5	3
      0x5C040A00,  //  001A  MOVE	R1	R5
      0x7001FFF5,  //  001B  JMP		#0012
      0x580C0008,  //  001C  LDCONST	R3	K8
      0xAC0C0200,  //  001D  CATCH	R3	1	0
      0xB0080000,  //  001E  RAISE	2	R0	R0
      0x80040200,  //  001F  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120063,  //  0003  LDINT	R4	100
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    1,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    0,                          /* has constants */
    NULL,                       /* no const */
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 1]) {  /* code */
      0x80000000,  //  0000  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x54160007,  //  0004  LDINT	R5	8
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 5]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    /* K2   */  be_nested_str_weak(trimToLimits),
    /* K3   */  be_const_int(0),
    /* K4   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[12]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0xB80E0000,  //  0002  GETNGBL	R3	K0
      0x8C0C0702,  //  0003  GETMET	R3	R3	K2
      0x5C140000,  //  0004  MOVE	R5	R0
      0x58180003,  //  0005  LDCONST	R6	K3
      0x541E0FFE,  //  0006  LDINT	R7	4095
      0x7C0C0800,  //  0007  CALL	R3	4
      0x58100004,  //  0008  LDCONST	R4	K4
      0x5416001F,  //  0009  LDINT	R5	32
      0x7C040800,  //  000A  CALL	R1	4
      0x80040200,  //  000B  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 1]) {     /* constants */
    /* K0   */  be_const_real_hex(0x411CCCCD),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0x58040000,  //  0000  LDCONST	R1	K0
      0x540A0063,  //  0001  LDINT	R2	100
      0x08080002,  //  0002  MUL	R2	R0	R2
      0x540E03E4,  //  0003  LDINT	R3	997
      0x0C100403,  //  0004  DIV	R4	R2	R3
      0x0C100801,  //  0005  DIV	R4	R4	R1
      0x80040800,  //  0006  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    9,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 7]) {     /* constants */
    /* K0   */  be_const_int(0),
    /* K1   */  be_const_int(1),
    /* K2   */  be_nested_str_weak(push),
    /* K3   */  be_nested_str_weak(string),
    /* K4   */  be_nested_str_weak(byte),
    /* K5   */  be_nested_str_weak(stop_iteration),
    /* K6   */  be_nested_str_weak(tostring),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[29]) {  /* code */
      0x5C040000,  //  0000  MOVE	R1	R0
      0x74060001,  //  0001  JMPT	R1	#0004
      0x4C040000,  //  0002  LDNIL	R1
      0x80040200,  //  0003  RET	1	R1
      0x60040012,  //  0004  GETGBL	R1	G18
      0x7C040000,  //  0005  CALL	R1	0
      0x60080010,  //  0006  GETGBL	R2	G16
      0x600C000C,  //  0007  GETGBL	R3	G12
      0x5C100000,  //  0008  MOVE	R4	R0
      0x7C0C0200,  //  0009  CALL	R3	1
      0x040C0701,  //  000A  SUB	R3	R3	K1
      0x400E0003,  //  000B  CONNECT	R3	K0	R3
      0x7C080200,  //  000C  CALL	R2	1
      0xA8020008,  //  000D  EXBLK	0	#0017
      0x5C0C0400,  //  000E  MOVE	R3	R2
      0x7C0C0000,  //  000F  CALL	R3	0
      0x8C100302,  //  0010  GETMET	R4	R1	K2
      0xB81A0600,  //  0011  GETNGBL	R6	K3
      0x8C180D04,  //  0012  GETMET	R6	R6	K4
      0x94200003,  //  0013  GETIDX	R8	R0	R3
      0x7C180400,  //  0014  CALL	R6	2
      0x7C100400,  //  0015  CALL	R4	2
      0x7001FFF6,  //  0016  JMP		#000E
      0x58080005,  //  0017  LDCONST	R2	K5
      0xAC080200,  //  0018  CATCH	R2	1	0
      0xB0080000,  //  0019  RAISE	2	R0	R0
      0x8C080306,  //  001A  GETMET	R2	R1	K6
      0x7C080200,  //  001B  CALL	R2	1
      0x80040400,  //  001C  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    7,                          /* nstack */
    3,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 4]) {     /* constants */
    /* K0   */  be_nested_str_weak(),
    /* K1   */  be_const_int(0),
    /* K2   */  be_const_int(1),
    /* K3   */  be_nested_str_weak(stop_iteration),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[23]) {  /* code */
      0x580C0000,  //  0000  LDCONST	R3	K0
      0x60100010,  //  0001  GETGBL	R4	G16
      0x6014000C,  //  0002  GETGBL	R5	G12
      0x60180008,  //  0003  GETGBL	R6	G8
      0x7C140200,  //  0004  CALL	R5	1
      0x04140B02,  //  0005  SUB	R5	R5	K2
      0x40160205,  //  0006  CONNECT	R5	K1	R5
      0x7C100200,  //  0007  CALL	R4	1
      0xA8020009,  //  0008  EXBLK	0	#0013
      0x5C140800,  //  0009  MOVE	R5	R4
      0x7C140000,  //  000A  CALL	R5	0
      0x94180005,  //  000B  GETIDX	R6	R0	R5
      0x1C180206,  //  000C  EQ	R6	R1	R6
      0x781A0001,  //  000D  JMPF	R6	#0010
      0x000C0602,  //  000E  ADD	R3	R3	R2
      0x70020001,  //  000F  JMP		#0012
      0x94180005,  //  0010  GETIDX	R6	R0	R5
      0x000C0606,  //  0011  ADD	R3	R3	R6
      0x7001FFF5,  //  0012  JMP		#0009
      0x58100003,  //  0013  LDCONST	R4	K3
      0xAC100200,  //  0014  CATCH	R4	1	0
      0xB0080000,  //  0015  RAISE	2	R0	R0
      0x80040600,  //  0016  RET	1	R3
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(get_component),
    /* K1   */  be_nested_str_weak(protocol_module),
    /* K2   */  be_nested_str_weak(LEVEL_BOARD_STATE),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[11]) {  /* code */
      0x78020006,  //  0000  JMPF	R0	#0008
      0x8C040100,  //  0001  GETMET	R1	R0	K0
      0x880C0101,  //  0002  GETMBR	R3	R0	K1
      0x880C0702,  //  0003  GETMBR	R3	R3	K2
      0x7C040400,  //  0004  CALL	R1	2
      0x4C080000,  //  0005  LDNIL	R2
      0x20040202,  //  0006  NE	R1	R1	R2
      0x74060000,  //  0007  JMPT	R1	#0009
      0x50040001,  //  0008  LDBOOL	R1	0	1
      0x50040200,  //  0009  LDBOOL	R1	1	0
      0x80040200,  //  000A  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x541203E7,  //  0003  LDINT	R4	1000
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    9,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 9]) {     /* constants */
    /* K0   */  be_nested_str_weak(),
    /* K1   */  be_nested_str_weak(utils),
    /* K2   */  be_nested_str_weak(getterValue),
    /* K3   */  be_const_int(0),
    /* K4   */  be_const_int(1),
    /* K5   */  be_nested_str_weak(string),
    /* K6   */  be_nested_str_weak(format),
    /* K7   */  be_nested_str_weak(_X25c),
    /* K8   */  be_nested_str_weak(stop_iteration),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[32]) {  /* code */
      0x58040000,  //  0000  LDCONST	R1	K0
      0xB80A0200,  //  0001  GETNGBL	R2	K1
      0x8C080502,  //  0002  GETMET	R2	R2	K2
      0x5C100000,  //  0003  MOVE	R4	R0
      0x7C080400,  //  0004  CALL	R2	2
      0x4C0C0000,  //  0005  LDNIL	R3
      0x1C0C0403,  //  0006  EQ	R3	R2	R3
      0x780E0001,  //  0007  JMPF	R3	#000A
      0x600C0008,  //  0008  GETGBL	R3	G8
      0x80040600,  //  0009  RET	1	R3
      0x600C0010,  //  000A  GETGBL	R3	G16
      0x6010000C,  //  000B  GETGBL	R4	G12
      0x5C140400,  //  000C  MOVE	R5	R2
      0x7C100200,  //  000D  CALL	R4	1
      0x04100904,  //  000E  SUB	R4	R4	K4
      0x40120604,  //  000F  CONNECT	R4	K3	R4
      0x7C0C0200,  //  0010  CALL	R3	1
      0xA8020009,  //  0011  EXBLK	0	#001C
      0x5C100600,  //  0012  MOVE	R4	R3
      0x7C100000,  //  0013  CALL	R4	0
      0xB8160A00,  //  0014  GETNGBL	R5	K5
      0x8C140B06,  //  0015  GETMET	R5	R5	K6
      0x601C0008,  //  0016  GETGBL	R7	G8
      0x001C0F07,  //  0017  ADD	R7	R7	K7
      0x94200404,  //  0018  GETIDX	R8	R2	R4
      0x7C140600,  //  0019  CALL	R5	3
      0x5C040A00,  //  001A  MOVE	R1	R5
      0x7001FFF5,  //  001B  JMP		#0012
      0x580C0008,  //  001C  LDCONST	R3	K8
      0xAC0C0200,  //  001D  CATCH	R3	1	0
      0xB0080000,  //  001E  RAISE	2	R0	R0
      0x80040200,  //  001F  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    /* K2   */  be_const_int(1),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 4]) {     /* constants */
    /* K0   */  be_nested_str_weak(get_component),
    /* K1   */  be_nested_str_weak(protocol_module),
    /* K2   */  be_nested_str_weak(FLOWMETER_VOLUME),
    /* K3   */  be_nested_str_weak(value),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[13]) {  /* code */
      0x4C040000,  //  0000  LDNIL	R1
      0x1C040001,  //  0001  EQ	R1	R0	R1
      0x78060000,  //  0002  JMPF	R1	#0004
      0x80000200,  //  0003  RET	0
      0x8C040100,  //  0004  GETMET	R1	R0	K0
      0x880C0101,  //  0005  GETMBR	R3	R0	K1
      0x880C0702,  //  0006  GETMBR	R3	R3	K2
      0x7C040400,  //  0007  CALL	R1	2
      0x78060001,  //  0008  JMPF	R1	#000B
      0x88080303,  //  0009  GETMBR	R2	R1	K3
      0x80040400,  //  000A  RET	1	R2
      0x4C080000,  //  000B  LDNIL	R2
      0x80040400,  //  000C  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 3]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterInt),
    /* K2   */  be_const_int(1000000),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x58100002,  //  0003  LDCONST	R4	K2
      0x5416001F,  //  0004  LDINT	R5	32
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    2,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    0,                          /* has constants */
    NULL,                       /* no const */
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 4]) {  /* code */
      0x24080001,  //  0000  GT	R2	R0	R1
      0x780A0000,  //  0001  JMPF	R2	#0003
      0x80040000,  //  0002  RET	1	R0
      0x80040200,  //  0003  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    12,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 7]) {     /* constants */
    /* K0   */  be_nested_str_weak(string),
    /* K1   */  be_nested_str_weak(format),
    /* K2   */  be_nested_str_weak(_X25_X2E4x),
    /* K3   */  be_nested_str_weak(sub),
    /* K4   */  be_const_int(1),
    /* K5   */  be_nested_str_weak(_X25s_X25s_X25s),
    /* K6   */  be_nested_str_weak(tostring),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[52]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x580C0002,  //  0002  LDCONST	R3	K2
      0x60100007,  //  0003  GETGBL	R4	G7
      0xB8160000,  //  0004  GETNGBL	R5	K0
      0x8C140B03,  //  0005  GETMET	R5	R5	K3
      0x5C1C0000,  //  0006  MOVE	R7	R0
      0x58200004,  //  0007  LDCONST	R8	K4
      0x54260003,  //  0008  LDINT	R9	4
      0x7C140800,  //  0009  CALL	R5	4
      0x7C100200,  //  000A  CALL	R4	1
      0x7C040600,  //  000B  CALL	R1	3
      0xB80A0000,  //  000C  GETNGBL	R2	K0
      0x8C080501,  //  000D  GETMET	R2	R2	K1
      0x58100002,  //  000E  LDCONST	R4	K2
      0x60140007,  //  000F  GETGBL	R5	G7
      0xB81A0000,  //  0010  GETNGBL	R6	K0
      0x8C180D03,  //  0011  GETMET	R6	R6	K3
      0x5C200000,  //  0012  MOVE	R8	R0
      0x54260004,  //  0013  LDINT	R9	5
      0x542A0005,  //  0014  LDINT	R10	6
      0x7C180800,  //  0015  CALL	R6	4
      0x7C140200,  //  0016  CALL	R5	1
      0x7C080600,  //  0017  CALL	R2	3
      0xB80E0000,  //  0018  GETNGBL	R3	K0
      0x8C0C0701,  //  0019  GETMET	R3	R3	K1
      0x58140002,  //  001A  LDCONST	R5	K2
      0x60180007,  //  001B  GETGBL	R6	G7
      0xB81E0000,  //  001C  GETNGBL	R7	K0
      0x8C1C0F03,  //  001D  GETMET	R7	R7	K3
      0x5C240000,  //  001E  MOVE	R9	R0
      0x542A0006,  //  001F  LDINT	R10	7
      0x542E0007,  //  0020  LDINT	R11	8
      0x7C1C0800,  //  0021  CALL	R7	4
      0x7C180200,  //  0022  CALL	R6	1
      0x7C0C0600,  //  0023  CALL	R3	3
      0x60100012,  //  0024  GETGBL	R4	G18
      0x7C100000,  //  0025  CALL	R4	0
      0x60140007,  //  0026  GETGBL	R5	G7
      0xB81A0000,  //  0027  GETNGBL	R6	K0
      0x8C180D01,  //  0028  GETMET	R6	R6	K1
      0x58200005,  //  0029  LDCONST	R8	K5
      0x5C240200,  //  002A  MOVE	R9	R1
      0x5C280400,  //  002B  MOVE	R10	R2
      0x5C2C0600,  //  002C  MOVE	R11	R3
      0x7C180A00,  //  002D  CALL	R6	5
      0x541E000F,  //  002E  LDINT	R7	16
      0x7C140400,  //  002F  CALL	R5	2
      0x40140805,  //  0030  CONNECT	R5	R4	R5
      0x8C140906,  //  0031  GETMET	R5	R4	K6
      0x7C140200,  //  0032  CALL	R5	1
      0x80040A00,  //  0033  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x541203E7,  //  0003  LDINT	R4	1000
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_const_real_hex(0x41A00000),
    /* K1   */  be_const_real_hex(0x3951B718),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 6]) {  /* code */
      0x58080000,  //  0000  LDCONST	R2	K0
      0x580C0001,  //  0001  LDCONST	R3	K1
      0x04100202,  //  0002  SUB	R4	R1	R2
      0x08100604,  //  0003  MUL	R4	R3	R4
      0x04100004,  //  0004  SUB	R4	R0	R4
      0x80040800,  //  0005  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x54120009,  //  0003  LDINT	R4	10
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    11,                          /* nstack */
    3,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 9]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(getterValue),
    /* K2   */  be_const_int(0),
    /* K3   */  be_nested_str_weak(math),
    /* K4   */  be_nested_str_weak(floor),
    /* K5   */  be_nested_str_weak(trimToBits),
    /* K6   */  be_nested_str_weak(string),
    /* K7   */  be_nested_str_weak(format),
    /* K8   */  be_nested_str_weak(_X25f),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[25]) {  /* code */
      0xB80E0000,  //  0000  GETNGBL	R3	K0
      0x8C0C0701,  //  0001  GETMET	R3	R3	K1
      0x5C140000,  //  0002  MOVE	R5	R0
      0x7C0C0400,  //  0003  CALL	R3	2
      0x4C100000,  //  0004  LDNIL	R4
      0x1C100604,  //  0005  EQ	R4	R3	R4
      0x78120001,  //  0006  JMPF	R4	#0009
      0x4C100000,  //  0007  LDNIL	R4
      0x80040800,  //  0008  RET	1	R4
      0x940C0702,  //  0009  GETIDX	R3	R3	K2
      0xB8120600,  //  000A  GETNGBL	R4	K3
      0x8C100904,  //  000B  GETMET	R4	R4	K4
      0xB81A0000,  //  000C  GETNGBL	R6	K0
      0x8C180D05,  //  000D  GETMET	R6	R6	K5
      0x5C200600,  //  000E  MOVE	R8	R3
      0x5C240400,  //  000F  MOVE	R9	R2
      0x50280200,  //  0010  LDBOOL	R10	1	0
      0x7C180800,  //  0011  CALL	R6	4
      0x7C100400,  //  0012  CALL	R4	2
      0xB8160C00,  //  0013  GETNGBL	R5	K6
      0x8C140B07,  //  0014  GETMET	R5	R5	K7
      0x581C0008,  //  0015  LDCONST	R7	K8
      0x0C200801,  //  0016  DIV	R8	R4	R1
      0x7C140600,  //  0017  CALL	R5	3
      0x80040A00,  //  0018  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(utils__anonymous_,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str_weak(utils),
    /* K1   */  be_nested_str_weak(setterUInt),
    }),
    be_str_weak(_anonymous_),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x541203E7,  //  0003  LDINT	R4	1000
      0x5416000F,  //  0004  LDINT	R5	16
      0x7C040800,  //  0005  CALL	R1	4
      0x80040200,  //  0006  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified module: utils
********************************************************************/
be_local_module(utils,
    "utils",
    be_nested_map(76,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(mpx2100db_mBar, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt16_1, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt32_1000, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterDeviceInfoName, 53), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_1000_ceil_0_100, 33), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt32_1000, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt16_1000, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_10_ceil_0_127, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt16_10, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(brix_temperature_compensation, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_1_ceil_1_10, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(calculate_correlation, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt32_10, 23), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(char_replace, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt8_10, 47), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_100_ceil_001_099, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_1000, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterInt32_1000000, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt16_1000, 6), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterInt16_1000, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_10, 25), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterInt32_1000, 52), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(max, 29), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(trimToLimits, 39), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(calculate_covariance, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt32_1000000, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterFirmware, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt32_1, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterStr, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterInt32_10, 14), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterHex, 9), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt16_1000, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(is_level_available, 67), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(dateSetter, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_100, 56), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterStr, 46), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(calculate_standard_deviation, 72), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(is_level_flag_valid, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(mBar2m, 44), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt16_1, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt1_1, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterInt32_1_ceil_400_2147483647, 8), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_1, 48), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_1_ceil_0_4096, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt16_1, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt8_1, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterLtlPressureSensorType, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(timeSetter, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt16_100, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt32_10, 74), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt32_100, 63), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterInt32_100, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt32_100, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(get_flow_volume, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterValue, 73), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(bitand, 61), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt32_1, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(is_number, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt16_100, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt32_10_ceil_1_10, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterUInt, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(makeColonPixelArray, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(trimToBits, 10), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterHexVersionWithDots, 36), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterInt32_1, 69), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterInt16_100, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterInt16_10, 32), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(list_sort, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt8, 66), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterInt, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(calculate_mean, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(getterUInt16_10, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(setterAMQPConnectionState, -1), be_const_closure(utils__anonymous__closure) },
        { be_const_key_weak(min, 28), be_const_closure(utils__anonymous__closure) },
    }))
);
BE_EXPORT_VARIABLE be_define_const_native_module(utils);
/********************************************************************/
/********************************************************************/
/* End of solidification */
