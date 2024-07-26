/* Solidification of Matter_Plugin_0.h */
/********************************************************************\
* Generated code, don't edit                                         *
\********************************************************************/
#include "be_constobj.h"
extern const bclass be_class_Matter_Plugin;
// compact class 'Matter_Plugin' ktab size: 62, total: 103 (saved 328 bytes)
static const bvalue be_ktab_class_Matter_Plugin[62] = {
  /* K0   */  be_nested_str_weak(tick),
  /* K1   */  be_nested_str_weak(device),
  /* K2   */  be_nested_str_weak(json),
  /* K3   */  be_nested_str_weak(node_label),
  /* K4   */  be_nested_str_weak(_X2C_X22Name_X22_X3A_X25s),
  /* K5   */  be_nested_str_weak(dump),
  /* K6   */  be_nested_str_weak(),
  /* K7   */  be_nested_str_weak(append_state_json),
  /* K8   */  be_nested_str_weak(_X7B_X22Ep_X22_X3A_X25i_X25s_X25s_X7D),
  /* K9   */  be_nested_str_weak(endpoint),
  /* K10  */  be_nested_str_weak(msg),
  /* K11  */  be_nested_str_weak(message_handler),
  /* K12  */  be_nested_str_weak(im),
  /* K13  */  be_nested_str_weak(send_ack_now),
  /* K14  */  be_nested_str_weak(update_next),
  /* K15  */  be_nested_str_weak(matter),
  /* K16  */  be_nested_str_weak(jitter),
  /* K17  */  be_nested_str_weak(UPDATE_TIME),
  /* K18  */  be_nested_str_weak(tasmota),
  /* K19  */  be_nested_str_weak(time_reached),
  /* K20  */  be_nested_str_weak(update_shadow),
  /* K21  */  be_nested_str_weak(millis),
  /* K22  */  be_nested_str_weak(events),
  /* K23  */  be_nested_str_weak(publish_event),
  /* K24  */  be_nested_str_weak(attribute_updated),
  /* K25  */  be_const_class(be_class_Matter_Plugin),
  /* K26  */  be_nested_str_weak(ARG),
  /* K27  */  be_nested_str_weak(ARG_TYPE),
  /* K28  */  be_nested_str_weak(clusters),
  /* K29  */  be_nested_str_weak(get_clusters),
  /* K30  */  be_nested_str_weak(parse_configuration),
  /* K31  */  be_nested_str_weak(find),
  /* K32  */  be_nested_str_weak(name),
  /* K33  */  be_nested_str_weak(BRIDGE),
  /* K34  */  be_nested_str_weak(UPDATE_COMMANDS),
  /* K35  */  be_nested_str_weak(k2l),
  /* K36  */  be_const_int(0),
  /* K37  */  be_const_int(1),
  /* K38  */  be_nested_str_weak(_X25s_X3A_X25s),
  /* K39  */  be_nested_str_weak(_X25s_X2C_X25s_X3A_X25s),
  /* K40  */  be_nested_str_weak(publish_command),
  /* K41  */  be_nested_str_weak(MtrReceived),
  /* K42  */  be_nested_str_weak(CLUSTERS),
  /* K43  */  be_nested_str_weak(contains),
  /* K44  */  be_nested_str_weak(TLV),
  /* K45  */  be_nested_str_weak(cluster),
  /* K46  */  be_nested_str_weak(attribute),
  /* K47  */  be_nested_str_weak(Matter_TLV_array),
  /* K48  */  be_nested_str_weak(TYPES),
  /* K49  */  be_nested_str_weak(keys),
  /* K50  */  be_nested_str_weak(add_struct),
  /* K51  */  be_nested_str_weak(add_TLV),
  /* K52  */  be_nested_str_weak(U2),
  /* K53  */  be_nested_str_weak(stop_iteration),
  /* K54  */  be_nested_str_weak(get_cluster_list_sorted),
  /* K55  */  be_nested_str_weak(U4),
  /* K56  */  be_const_int(2),
  /* K57  */  be_const_int(3),
  /* K58  */  be_nested_str_weak(set),
  /* K59  */  be_nested_str_weak(get_attribute_list),
  /* K60  */  be_nested_str_weak(FEATURE_MAPS),
  /* K61  */  be_nested_str_weak(CLUSTER_REVISIONS),
};


extern const bclass be_class_Matter_Plugin;

/********************************************************************
** Solidified function: update_shadow
********************************************************************/
be_local_closure(class_Matter_Plugin_update_shadow,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(update_shadow),
    &be_const_str_solidified,
    ( &(const binstruction[ 4]) {  /* code */
      0x88040101,  //  0000  GETMBR	R1	R0	K1
      0x88040300,  //  0001  GETMBR	R1	R1	K0
      0x90020001,  //  0002  SETMBR	R0	K0	R1
      0x80000000,  //  0003  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: state_json
********************************************************************/
be_local_closure(class_Matter_Plugin_state_json,   /* name */
  be_nested_proto(
    9,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(state_json),
    &be_const_str_solidified,
    ( &(const binstruction[25]) {  /* code */
      0xA4060400,  //  0000  IMPORT	R1	K2
      0x88080103,  //  0001  GETMBR	R2	R0	K3
      0x780A0006,  //  0002  JMPF	R2	#000A
      0x60080018,  //  0003  GETGBL	R2	G24
      0x580C0004,  //  0004  LDCONST	R3	K4
      0x8C100305,  //  0005  GETMET	R4	R1	K5
      0x88180103,  //  0006  GETMBR	R6	R0	K3
      0x7C100400,  //  0007  CALL	R4	2
      0x7C080400,  //  0008  CALL	R2	2
      0x70020000,  //  0009  JMP		#000B
      0x58080006,  //  000A  LDCONST	R2	K6
      0x8C0C0107,  //  000B  GETMET	R3	R0	K7
      0x7C0C0200,  //  000C  CALL	R3	1
      0x780E0007,  //  000D  JMPF	R3	#0016
      0x60100018,  //  000E  GETGBL	R4	G24
      0x58140008,  //  000F  LDCONST	R5	K8
      0x88180109,  //  0010  GETMBR	R6	R0	K9
      0x5C1C0400,  //  0011  MOVE	R7	R2
      0x5C200600,  //  0012  MOVE	R8	R3
      0x7C100800,  //  0013  CALL	R4	4
      0x80040800,  //  0014  RET	1	R4
      0x70020001,  //  0015  JMP		#0018
      0x4C100000,  //  0016  LDNIL	R4
      0x80040800,  //  0017  RET	1	R4
      0x80000000,  //  0018  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: ack_request
********************************************************************/
be_local_closure(class_Matter_Plugin_ack_request,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(ack_request),
    &be_const_str_solidified,
    ( &(const binstruction[13]) {  /* code */
      0x8808030A,  //  0000  GETMBR	R2	R1	K10
      0x4C0C0000,  //  0001  LDNIL	R3
      0x200C0403,  //  0002  NE	R3	R2	R3
      0x780E0005,  //  0003  JMPF	R3	#000A
      0x880C0101,  //  0004  GETMBR	R3	R0	K1
      0x880C070B,  //  0005  GETMBR	R3	R3	K11
      0x880C070C,  //  0006  GETMBR	R3	R3	K12
      0x8C0C070D,  //  0007  GETMET	R3	R3	K13
      0x5C140400,  //  0008  MOVE	R5	R2
      0x7C0C0400,  //  0009  CALL	R3	2
      0x4C0C0000,  //  000A  LDNIL	R3
      0x90061403,  //  000B  SETMBR	R1	K10	R3
      0x80000000,  //  000C  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: write_attribute
********************************************************************/
be_local_closure(class_Matter_Plugin_write_attribute,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    4,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(write_attribute),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x4C100000,  //  0000  LDNIL	R4
      0x80040800,  //  0001  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: invoke_request
********************************************************************/
be_local_closure(class_Matter_Plugin_invoke_request,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    4,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(invoke_request),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x4C100000,  //  0000  LDNIL	R4
      0x80040800,  //  0001  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: append_state_json
********************************************************************/
be_local_closure(class_Matter_Plugin_append_state_json,   /* name */
  be_nested_proto(
    1,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(append_state_json),
    &be_const_str_solidified,
    ( &(const binstruction[ 1]) {  /* code */
      0x80060C00,  //  0000  RET	1	K6
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: every_250ms
********************************************************************/
be_local_closure(class_Matter_Plugin_every_250ms,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(every_250ms),
    &be_const_str_solidified,
    ( &(const binstruction[28]) {  /* code */
      0x8804010E,  //  0000  GETMBR	R1	R0	K14
      0x4C080000,  //  0001  LDNIL	R2
      0x1C040202,  //  0002  EQ	R1	R1	R2
      0x78060005,  //  0003  JMPF	R1	#000A
      0xB8061E00,  //  0004  GETNGBL	R1	K15
      0x8C040310,  //  0005  GETMET	R1	R1	K16
      0x880C0111,  //  0006  GETMBR	R3	R0	K17
      0x7C040400,  //  0007  CALL	R1	2
      0x90021C01,  //  0008  SETMBR	R0	K14	R1
      0x70020010,  //  0009  JMP		#001B
      0xB8062400,  //  000A  GETNGBL	R1	K18
      0x8C040313,  //  000B  GETMET	R1	R1	K19
      0x880C010E,  //  000C  GETMBR	R3	R0	K14
      0x7C040400,  //  000D  CALL	R1	2
      0x7806000B,  //  000E  JMPF	R1	#001B
      0x88040100,  //  000F  GETMBR	R1	R0	K0
      0x88080101,  //  0010  GETMBR	R2	R0	K1
      0x88080500,  //  0011  GETMBR	R2	R2	K0
      0x20040202,  //  0012  NE	R1	R1	R2
      0x78060001,  //  0013  JMPF	R1	#0016
      0x8C040114,  //  0014  GETMET	R1	R0	K20
      0x7C040200,  //  0015  CALL	R1	1
      0xB8062400,  //  0016  GETNGBL	R1	K18
      0x8C040315,  //  0017  GETMET	R1	R1	K21
      0x880C0111,  //  0018  GETMBR	R3	R0	K17
      0x7C040400,  //  0019  CALL	R1	2
      0x90021C01,  //  001A  SETMBR	R0	K14	R1
      0x80000000,  //  001B  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: publish_event
********************************************************************/
be_local_closure(class_Matter_Plugin_publish_event,   /* name */
  be_nested_proto(
    17,                          /* nstack */
    7,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(publish_event),
    &be_const_str_solidified,
    ( &(const binstruction[13]) {  /* code */
      0x881C0101,  //  0000  GETMBR	R7	R0	K1
      0x881C0F16,  //  0001  GETMBR	R7	R7	K22
      0x8C1C0F17,  //  0002  GETMET	R7	R7	K23
      0x88240109,  //  0003  GETMBR	R9	R0	K9
      0x5C280200,  //  0004  MOVE	R10	R1
      0x5C2C0400,  //  0005  MOVE	R11	R2
      0x50300200,  //  0006  LDBOOL	R12	1	0
      0x5C340600,  //  0007  MOVE	R13	R3
      0x5C380800,  //  0008  MOVE	R14	R4
      0x5C3C0A00,  //  0009  MOVE	R15	R5
      0x5C400C00,  //  000A  MOVE	R16	R6
      0x7C1C1200,  //  000B  CALL	R7	9
      0x80000000,  //  000C  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: set_name
********************************************************************/
be_local_closure(class_Matter_Plugin_set_name,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(set_name),
    &be_const_str_solidified,
    ( &(const binstruction[ 9]) {  /* code */
      0x88080103,  //  0000  GETMBR	R2	R0	K3
      0x20080202,  //  0001  NE	R2	R1	R2
      0x780A0003,  //  0002  JMPF	R2	#0007
      0x8C080118,  //  0003  GETMET	R2	R0	K24
      0x54120038,  //  0004  LDINT	R4	57
      0x54160004,  //  0005  LDINT	R5	5
      0x7C080600,  //  0006  CALL	R2	3
      0x90020601,  //  0007  SETMBR	R0	K3	R1
      0x80000000,  //  0008  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: <lambda>
********************************************************************/
be_local_closure(class_Matter_Plugin__X3Clambda_X3E,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    1,                          /* argc */
    8,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(_X3Clambda_X3E),
    &be_const_str_solidified,
    ( &(const binstruction[ 4]) {  /* code */
      0x60040008,  //  0000  GETGBL	R1	G8
      0x5C080000,  //  0001  MOVE	R2	R0
      0x7C040200,  //  0002  CALL	R1	1
      0x80040200,  //  0003  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: ui_string_to_conf
********************************************************************/
be_local_closure(class_Matter_Plugin_ui_string_to_conf,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    3,                          /* argc */
    12,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(ui_string_to_conf),
    &be_const_str_solidified,
    ( &(const binstruction[10]) {  /* code */
      0x580C0019,  //  0000  LDCONST	R3	K25
      0x8810011A,  //  0001  GETMBR	R4	R0	K26
      0x8814011B,  //  0002  GETMBR	R5	R0	K27
      0x780A0004,  //  0003  JMPF	R2	#0009
      0x78120003,  //  0004  JMPF	R4	#0009
      0x5C180A00,  //  0005  MOVE	R6	R5
      0x5C1C0400,  //  0006  MOVE	R7	R2
      0x7C180200,  //  0007  CALL	R6	1
      0x98040806,  //  0008  SETIDX	R1	R4	R6
      0x80040200,  //  0009  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: timed_request
********************************************************************/
be_local_closure(class_Matter_Plugin_timed_request,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    4,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(timed_request),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x4C100000,  //  0000  LDNIL	R4
      0x80040800,  //  0001  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Matter_Plugin_init,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    4,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(init),
    &be_const_str_solidified,
    ( &(const binstruction[14]) {  /* code */
      0x90020201,  //  0000  SETMBR	R0	K1	R1
      0x90021202,  //  0001  SETMBR	R0	K9	R2
      0x8C10011D,  //  0002  GETMET	R4	R0	K29
      0x7C100200,  //  0003  CALL	R4	1
      0x90023804,  //  0004  SETMBR	R0	K28	R4
      0x8C10011E,  //  0005  GETMET	R4	R0	K30
      0x5C180600,  //  0006  MOVE	R6	R3
      0x7C100400,  //  0007  CALL	R4	2
      0x8C10071F,  //  0008  GETMET	R4	R3	K31
      0x58180020,  //  0009  LDCONST	R6	K32
      0x581C0006,  //  000A  LDCONST	R7	K6
      0x7C100600,  //  000B  CALL	R4	3
      0x90020604,  //  000C  SETMBR	R0	K3	R4
      0x80000000,  //  000D  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: is_local_device
********************************************************************/
be_local_closure(class_Matter_Plugin_is_local_device,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(is_local_device),
    &be_const_str_solidified,
    ( &(const binstruction[ 5]) {  /* code */
      0x88040121,  //  0000  GETMBR	R1	R0	K33
      0x78060000,  //  0001  JMPF	R1	#0003
      0x50040001,  //  0002  LDBOOL	R1	0	1
      0x50040200,  //  0003  LDBOOL	R1	1	0
      0x80040200,  //  0004  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: consolidate_update_commands
********************************************************************/
be_local_closure(class_Matter_Plugin_consolidate_update_commands,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(consolidate_update_commands),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x88040122,  //  0000  GETMBR	R1	R0	K34
      0x80040200,  //  0001  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: update_shadow_lazy
********************************************************************/
be_local_closure(class_Matter_Plugin_update_shadow_lazy,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(update_shadow_lazy),
    &be_const_str_solidified,
    ( &(const binstruction[11]) {  /* code */
      0x88040100,  //  0000  GETMBR	R1	R0	K0
      0x88080101,  //  0001  GETMBR	R2	R0	K1
      0x88080500,  //  0002  GETMBR	R2	R2	K0
      0x20040202,  //  0003  NE	R1	R1	R2
      0x78060004,  //  0004  JMPF	R1	#000A
      0x8C040114,  //  0005  GETMET	R1	R0	K20
      0x7C040200,  //  0006  CALL	R1	1
      0x88040101,  //  0007  GETMBR	R1	R0	K1
      0x88040300,  //  0008  GETMBR	R1	R1	K0
      0x90020001,  //  0009  SETMBR	R0	K0	R1
      0x80000000,  //  000A  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: get_cluster_list_sorted
********************************************************************/
be_local_closure(class_Matter_Plugin_get_cluster_list_sorted,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(get_cluster_list_sorted),
    &be_const_str_solidified,
    ( &(const binstruction[ 5]) {  /* code */
      0x88040101,  //  0000  GETMBR	R1	R0	K1
      0x8C040323,  //  0001  GETMET	R1	R1	K35
      0x880C011C,  //  0002  GETMBR	R3	R0	K28
      0x7C040400,  //  0003  CALL	R1	2
      0x80040200,  //  0004  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: ui_conf_to_string
********************************************************************/
be_local_closure(class_Matter_Plugin_ui_conf_to_string,   /* name */
  be_nested_proto(
    9,                          /* nstack */
    2,                          /* argc */
    12,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(ui_conf_to_string),
    &be_const_str_solidified,
    ( &(const binstruction[12]) {  /* code */
      0x58080019,  //  0000  LDCONST	R2	K25
      0x880C011A,  //  0001  GETMBR	R3	R0	K26
      0x780E0006,  //  0002  JMPF	R3	#000A
      0x60100008,  //  0003  GETGBL	R4	G8
      0x8C14031F,  //  0004  GETMET	R5	R1	K31
      0x5C1C0600,  //  0005  MOVE	R7	R3
      0x58200006,  //  0006  LDCONST	R8	K6
      0x7C140600,  //  0007  CALL	R5	3
      0x7C100200,  //  0008  CALL	R4	1
      0x70020000,  //  0009  JMP		#000B
      0x58100006,  //  000A  LDCONST	R4	K6
      0x80040800,  //  000B  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: attribute_updated
********************************************************************/
be_local_closure(class_Matter_Plugin_attribute_updated,   /* name */
  be_nested_proto(
    10,                          /* nstack */
    4,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(attribute_updated),
    &be_const_str_solidified,
    ( &(const binstruction[ 8]) {  /* code */
      0x88100101,  //  0000  GETMBR	R4	R0	K1
      0x8C100918,  //  0001  GETMET	R4	R4	K24
      0x88180109,  //  0002  GETMBR	R6	R0	K9
      0x5C1C0200,  //  0003  MOVE	R7	R1
      0x5C200400,  //  0004  MOVE	R8	R2
      0x5C240600,  //  0005  MOVE	R9	R3
      0x7C100A00,  //  0006  CALL	R4	5
      0x80000000,  //  0007  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: update_virtual
********************************************************************/
be_local_closure(class_Matter_Plugin_update_virtual,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(update_virtual),
    &be_const_str_solidified,
    ( &(const binstruction[ 1]) {  /* code */
      0x80000000,  //  0000  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: _parse_update_virtual
********************************************************************/
be_local_closure(class_Matter_Plugin__parse_update_virtual,   /* name */
  be_nested_proto(
    12,                          /* nstack */
    7,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(_parse_update_virtual),
    &be_const_str_solidified,
    ( &(const binstruction[18]) {  /* code */
      0x8C1C031F,  //  0000  GETMET	R7	R1	K31
      0x5C240400,  //  0001  MOVE	R9	R2
      0x7C1C0400,  //  0002  CALL	R7	2
      0x4C200000,  //  0003  LDNIL	R8
      0x20200E08,  //  0004  NE	R8	R7	R8
      0x7822000A,  //  0005  JMPF	R8	#0011
      0x5C200800,  //  0006  MOVE	R8	R4
      0x5C240E00,  //  0007  MOVE	R9	R7
      0x7C200200,  //  0008  CALL	R8	1
      0x5C1C1000,  //  0009  MOVE	R7	R8
      0x20200E03,  //  000A  NE	R8	R7	R3
      0x78220003,  //  000B  JMPF	R8	#0010
      0x8C200118,  //  000C  GETMET	R8	R0	K24
      0x5C280A00,  //  000D  MOVE	R10	R5
      0x5C2C0C00,  //  000E  MOVE	R11	R6
      0x7C200600,  //  000F  CALL	R8	3
      0x80040E00,  //  0010  RET	1	R7
      0x80040600,  //  0011  RET	1	R3
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: parse_configuration
********************************************************************/
be_local_closure(class_Matter_Plugin_parse_configuration,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(parse_configuration),
    &be_const_str_solidified,
    ( &(const binstruction[ 1]) {  /* code */
      0x80000000,  //  0000  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: get_name
********************************************************************/
be_local_closure(class_Matter_Plugin_get_name,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(get_name),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x88040103,  //  0000  GETMBR	R1	R0	K3
      0x80040200,  //  0001  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: get_endpoint
********************************************************************/
be_local_closure(class_Matter_Plugin_get_endpoint,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(get_endpoint),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x88040109,  //  0000  GETMBR	R1	R0	K9
      0x80040200,  //  0001  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: contains_attribute
********************************************************************/
be_local_closure(class_Matter_Plugin_contains_attribute,   /* name */
  be_nested_proto(
    7,                          /* nstack */
    3,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(contains_attribute),
    &be_const_str_solidified,
    ( &(const binstruction[22]) {  /* code */
      0x880C011C,  //  0000  GETMBR	R3	R0	K28
      0x8C0C071F,  //  0001  GETMET	R3	R3	K31
      0x5C140200,  //  0002  MOVE	R5	R1
      0x7C0C0400,  //  0003  CALL	R3	2
      0x4C100000,  //  0004  LDNIL	R4
      0x20100604,  //  0005  NE	R4	R3	R4
      0x7812000C,  //  0006  JMPF	R4	#0014
      0x58100024,  //  0007  LDCONST	R4	K36
      0x6014000C,  //  0008  GETGBL	R5	G12
      0x5C180600,  //  0009  MOVE	R6	R3
      0x7C140200,  //  000A  CALL	R5	1
      0x14140805,  //  000B  LT	R5	R4	R5
      0x78160006,  //  000C  JMPF	R5	#0014
      0x94140604,  //  000D  GETIDX	R5	R3	R4
      0x1C140A02,  //  000E  EQ	R5	R5	R2
      0x78160001,  //  000F  JMPF	R5	#0012
      0x50140200,  //  0010  LDBOOL	R5	1	0
      0x80040A00,  //  0011  RET	1	R5
      0x00100925,  //  0012  ADD	R4	R4	K37
      0x7001FFF3,  //  0013  JMP		#0008
      0x50100000,  //  0014  LDBOOL	R4	0	0
      0x80040800,  //  0015  RET	1	R4
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: subscribe_event
********************************************************************/
be_local_closure(class_Matter_Plugin_subscribe_event,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    5,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(subscribe_event),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x4C140000,  //  0000  LDNIL	R5
      0x80040A00,  //  0001  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: read_event
********************************************************************/
be_local_closure(class_Matter_Plugin_read_event,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    5,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(read_event),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x4C140000,  //  0000  LDNIL	R5
      0x80040A00,  //  0001  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: parse_sensors
********************************************************************/
be_local_closure(class_Matter_Plugin_parse_sensors,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(parse_sensors),
    &be_const_str_solidified,
    ( &(const binstruction[ 1]) {  /* code */
      0x80000000,  //  0000  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: get_attribute_list
********************************************************************/
be_local_closure(class_Matter_Plugin_get_attribute_list,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(get_attribute_list),
    &be_const_str_solidified,
    ( &(const binstruction[ 7]) {  /* code */
      0x8808011C,  //  0000  GETMBR	R2	R0	K28
      0x8C08051F,  //  0001  GETMET	R2	R2	K31
      0x5C100200,  //  0002  MOVE	R4	R1
      0x60140012,  //  0003  GETGBL	R5	G18
      0x7C140000,  //  0004  CALL	R5	0
      0x7C080600,  //  0005  CALL	R2	3
      0x80040400,  //  0006  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: publish_command
********************************************************************/
be_local_closure(class_Matter_Plugin_publish_command,   /* name */
  be_nested_proto(
    16,                          /* nstack */
    7,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(publish_command),
    &be_const_str_solidified,
    ( &(const binstruction[46]) {  /* code */
      0xA41E0400,  //  0000  IMPORT	R7	K2
      0x60200018,  //  0001  GETGBL	R8	G24
      0x58240026,  //  0002  LDCONST	R9	K38
      0x8C280F05,  //  0003  GETMET	R10	R7	K5
      0x5C300200,  //  0004  MOVE	R12	R1
      0x7C280400,  //  0005  CALL	R10	2
      0x8C2C0F05,  //  0006  GETMET	R11	R7	K5
      0x5C340400,  //  0007  MOVE	R13	R2
      0x7C2C0400,  //  0008  CALL	R11	2
      0x7C200600,  //  0009  CALL	R8	3
      0x4C240000,  //  000A  LDNIL	R9
      0x20240609,  //  000B  NE	R9	R3	R9
      0x7826000A,  //  000C  JMPF	R9	#0018
      0x60240018,  //  000D  GETGBL	R9	G24
      0x58280027,  //  000E  LDCONST	R10	K39
      0x5C2C1000,  //  000F  MOVE	R11	R8
      0x8C300F05,  //  0010  GETMET	R12	R7	K5
      0x5C380600,  //  0011  MOVE	R14	R3
      0x7C300400,  //  0012  CALL	R12	2
      0x8C340F05,  //  0013  GETMET	R13	R7	K5
      0x5C3C0800,  //  0014  MOVE	R15	R4
      0x7C340400,  //  0015  CALL	R13	2
      0x7C240800,  //  0016  CALL	R9	4
      0x5C201200,  //  0017  MOVE	R8	R9
      0x4C240000,  //  0018  LDNIL	R9
      0x20240A09,  //  0019  NE	R9	R5	R9
      0x7826000A,  //  001A  JMPF	R9	#0026
      0x60240018,  //  001B  GETGBL	R9	G24
      0x58280027,  //  001C  LDCONST	R10	K39
      0x5C2C1000,  //  001D  MOVE	R11	R8
      0x8C300F05,  //  001E  GETMET	R12	R7	K5
      0x5C380A00,  //  001F  MOVE	R14	R5
      0x7C300400,  //  0020  CALL	R12	2
      0x8C340F05,  //  0021  GETMET	R13	R7	K5
      0x5C3C0C00,  //  0022  MOVE	R15	R6
      0x7C340400,  //  0023  CALL	R13	2
      0x7C240800,  //  0024  CALL	R9	4
      0x5C201200,  //  0025  MOVE	R8	R9
      0xB8261E00,  //  0026  GETNGBL	R9	K15
      0x8C241328,  //  0027  GETMET	R9	R9	K40
      0x582C0029,  //  0028  LDCONST	R11	K41
      0x88300109,  //  0029  GETMBR	R12	R0	K9
      0x88340103,  //  002A  GETMBR	R13	R0	K3
      0x5C381000,  //  002B  MOVE	R14	R8
      0x7C240A00,  //  002C  CALL	R9	5
      0x80000000,  //  002D  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: get_clusters
********************************************************************/
be_local_closure(class_Matter_Plugin_get_clusters,   /* name */
  be_nested_proto(
    2,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(get_clusters),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x8804012A,  //  0000  GETMBR	R1	R0	K42
      0x80040200,  //  0001  RET	1	R1
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: contains_cluster
********************************************************************/
be_local_closure(class_Matter_Plugin_contains_cluster,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    2,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(contains_cluster),
    &be_const_str_solidified,
    ( &(const binstruction[ 5]) {  /* code */
      0x8808011C,  //  0000  GETMBR	R2	R0	K28
      0x8C08052B,  //  0001  GETMET	R2	R2	K43
      0x5C100200,  //  0002  MOVE	R4	R1
      0x7C080400,  //  0003  CALL	R2	2
      0x80040400,  //  0004  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: read_attribute
********************************************************************/
be_local_closure(class_Matter_Plugin_read_attribute,   /* name */
  be_nested_proto(
    17,                          /* nstack */
    4,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(read_attribute),
    &be_const_str_solidified,
    ( &(const binstruction[161]) {  /* code */
      0xB8121E00,  //  0000  GETNGBL	R4	K15
      0x8810092C,  //  0001  GETMBR	R4	R4	K44
      0x8814052D,  //  0002  GETMBR	R5	R2	K45
      0x8818052E,  //  0003  GETMBR	R6	R2	K46
      0x541E001C,  //  0004  LDINT	R7	29
      0x1C1C0A07,  //  0005  EQ	R7	R5	R7
      0x781E0050,  //  0006  JMPF	R7	#0058
      0x1C1C0D24,  //  0007  EQ	R7	R6	K36
      0x781E001B,  //  0008  JMPF	R7	#0025
      0x8C1C092F,  //  0009  GETMET	R7	R4	K47
      0x7C1C0200,  //  000A  CALL	R7	1
      0x88200130,  //  000B  GETMBR	R8	R0	K48
      0x60240010,  //  000C  GETGBL	R9	G16
      0x8C281131,  //  000D  GETMET	R10	R8	K49
      0x7C280200,  //  000E  CALL	R10	1
      0x7C240200,  //  000F  CALL	R9	1
      0xA802000E,  //  0010  EXBLK	0	#0020
      0x5C281200,  //  0011  MOVE	R10	R9
      0x7C280000,  //  0012  CALL	R10	0
      0x8C2C0F32,  //  0013  GETMET	R11	R7	K50
      0x7C2C0200,  //  0014  CALL	R11	1
      0x8C301733,  //  0015  GETMET	R12	R11	K51
      0x58380024,  //  0016  LDCONST	R14	K36
      0x883C0934,  //  0017  GETMBR	R15	R4	K52
      0x5C401400,  //  0018  MOVE	R16	R10
      0x7C300800,  //  0019  CALL	R12	4
      0x8C301733,  //  001A  GETMET	R12	R11	K51
      0x58380025,  //  001B  LDCONST	R14	K37
      0x883C0934,  //  001C  GETMBR	R15	R4	K52
      0x9440100A,  //  001D  GETIDX	R16	R8	R10
      0x7C300800,  //  001E  CALL	R12	4
      0x7001FFF0,  //  001F  JMP		#0011
      0x58240035,  //  0020  LDCONST	R9	K53
      0xAC240200,  //  0021  CATCH	R9	1	0
      0xB0080000,  //  0022  RAISE	2	R0	R0
      0x80040E00,  //  0023  RET	1	R7
      0x70020032,  //  0024  JMP		#0058
      0x1C1C0D25,  //  0025  EQ	R7	R6	K37
      0x781E0013,  //  0026  JMPF	R7	#003B
      0x8C1C092F,  //  0027  GETMET	R7	R4	K47
      0x7C1C0200,  //  0028  CALL	R7	1
      0x60200010,  //  0029  GETGBL	R8	G16
      0x8C240136,  //  002A  GETMET	R9	R0	K54
      0x7C240200,  //  002B  CALL	R9	1
      0x7C200200,  //  002C  CALL	R8	1
      0xA8020007,  //  002D  EXBLK	0	#0036
      0x5C241000,  //  002E  MOVE	R9	R8
      0x7C240000,  //  002F  CALL	R9	0
      0x8C280F33,  //  0030  GETMET	R10	R7	K51
      0x4C300000,  //  0031  LDNIL	R12
      0x88340937,  //  0032  GETMBR	R13	R4	K55
      0x5C381200,  //  0033  MOVE	R14	R9
      0x7C280800,  //  0034  CALL	R10	4
      0x7001FFF7,  //  0035  JMP		#002E
      0x58200035,  //  0036  LDCONST	R8	K53
      0xAC200200,  //  0037  CATCH	R8	1	0
      0xB0080000,  //  0038  RAISE	2	R0	R0
      0x80040E00,  //  0039  RET	1	R7
      0x7002001C,  //  003A  JMP		#0058
      0x1C1C0D38,  //  003B  EQ	R7	R6	K56
      0x781E0003,  //  003C  JMPF	R7	#0041
      0x8C1C092F,  //  003D  GETMET	R7	R4	K47
      0x7C1C0200,  //  003E  CALL	R7	1
      0x80040E00,  //  003F  RET	1	R7
      0x70020016,  //  0040  JMP		#0058
      0x1C1C0D39,  //  0041  EQ	R7	R6	K57
      0x781E0003,  //  0042  JMPF	R7	#0047
      0x8C1C092F,  //  0043  GETMET	R7	R4	K47
      0x7C1C0200,  //  0044  CALL	R7	1
      0x80040E00,  //  0045  RET	1	R7
      0x70020010,  //  0046  JMP		#0058
      0x541EFFFB,  //  0047  LDINT	R7	65532
      0x1C1C0C07,  //  0048  EQ	R7	R6	R7
      0x781E0005,  //  0049  JMPF	R7	#0050
      0x8C1C073A,  //  004A  GETMET	R7	R3	K58
      0x88240937,  //  004B  GETMBR	R9	R4	K55
      0x58280024,  //  004C  LDCONST	R10	K36
      0x7C1C0600,  //  004D  CALL	R7	3
      0x80040E00,  //  004E  RET	1	R7
      0x70020007,  //  004F  JMP		#0058
      0x541EFFFC,  //  0050  LDINT	R7	65533
      0x1C1C0C07,  //  0051  EQ	R7	R6	R7
      0x781E0004,  //  0052  JMPF	R7	#0058
      0x8C1C073A,  //  0053  GETMET	R7	R3	K58
      0x88240937,  //  0054  GETMBR	R9	R4	K55
      0x58280025,  //  0055  LDCONST	R10	K37
      0x7C1C0600,  //  0056  CALL	R7	3
      0x80040E00,  //  0057  RET	1	R7
      0x541EFFF7,  //  0058  LDINT	R7	65528
      0x1C1C0C07,  //  0059  EQ	R7	R6	R7
      0x781E0003,  //  005A  JMPF	R7	#005F
      0x8C1C092F,  //  005B  GETMET	R7	R4	K47
      0x7C1C0200,  //  005C  CALL	R7	1
      0x80040E00,  //  005D  RET	1	R7
      0x7002003F,  //  005E  JMP		#009F
      0x541EFFFA,  //  005F  LDINT	R7	65531
      0x1C1C0C07,  //  0060  EQ	R7	R6	R7
      0x781E0013,  //  0061  JMPF	R7	#0076
      0x8C1C092F,  //  0062  GETMET	R7	R4	K47
      0x7C1C0200,  //  0063  CALL	R7	1
      0x8C20013B,  //  0064  GETMET	R8	R0	K59
      0x5C280A00,  //  0065  MOVE	R10	R5
      0x7C200400,  //  0066  CALL	R8	2
      0x58240024,  //  0067  LDCONST	R9	K36
      0x6028000C,  //  0068  GETGBL	R10	G12
      0x5C2C1000,  //  0069  MOVE	R11	R8
      0x7C280200,  //  006A  CALL	R10	1
      0x1428120A,  //  006B  LT	R10	R9	R10
      0x782A0006,  //  006C  JMPF	R10	#0074
      0x8C280F33,  //  006D  GETMET	R10	R7	K51
      0x4C300000,  //  006E  LDNIL	R12
      0x88340934,  //  006F  GETMBR	R13	R4	K52
      0x94381009,  //  0070  GETIDX	R14	R8	R9
      0x7C280800,  //  0071  CALL	R10	4
      0x00241325,  //  0072  ADD	R9	R9	K37
      0x7001FFF3,  //  0073  JMP		#0068
      0x80040E00,  //  0074  RET	1	R7
      0x70020028,  //  0075  JMP		#009F
      0x541EFFF9,  //  0076  LDINT	R7	65530
      0x1C1C0C07,  //  0077  EQ	R7	R6	R7
      0x781E0003,  //  0078  JMPF	R7	#007D
      0x8C1C092F,  //  0079  GETMET	R7	R4	K47
      0x7C1C0200,  //  007A  CALL	R7	1
      0x80040E00,  //  007B  RET	1	R7
      0x70020021,  //  007C  JMP		#009F
      0x541EFFF8,  //  007D  LDINT	R7	65529
      0x1C1C0C07,  //  007E  EQ	R7	R6	R7
      0x781E0003,  //  007F  JMPF	R7	#0084
      0x8C1C092F,  //  0080  GETMET	R7	R4	K47
      0x7C1C0200,  //  0081  CALL	R7	1
      0x80040E00,  //  0082  RET	1	R7
      0x7002001A,  //  0083  JMP		#009F
      0x541EFFFB,  //  0084  LDINT	R7	65532
      0x1C1C0C07,  //  0085  EQ	R7	R6	R7
      0x781E000A,  //  0086  JMPF	R7	#0092
      0x881C013C,  //  0087  GETMBR	R7	R0	K60
      0x8C1C0F1F,  //  0088  GETMET	R7	R7	K31
      0x5C240A00,  //  0089  MOVE	R9	R5
      0x58280024,  //  008A  LDCONST	R10	K36
      0x7C1C0600,  //  008B  CALL	R7	3
      0x8C20073A,  //  008C  GETMET	R8	R3	K58
      0x88280937,  //  008D  GETMBR	R10	R4	K55
      0x5C2C0E00,  //  008E  MOVE	R11	R7
      0x7C200600,  //  008F  CALL	R8	3
      0x80041000,  //  0090  RET	1	R8
      0x7002000C,  //  0091  JMP		#009F
      0x541EFFFC,  //  0092  LDINT	R7	65533
      0x1C1C0C07,  //  0093  EQ	R7	R6	R7
      0x781E0009,  //  0094  JMPF	R7	#009F
      0x881C013D,  //  0095  GETMBR	R7	R0	K61
      0x8C1C0F1F,  //  0096  GETMET	R7	R7	K31
      0x5C240A00,  //  0097  MOVE	R9	R5
      0x58280025,  //  0098  LDCONST	R10	K37
      0x7C1C0600,  //  0099  CALL	R7	3
      0x8C20073A,  //  009A  GETMET	R8	R3	K58
      0x88280937,  //  009B  GETMBR	R10	R4	K55
      0x5C2C0E00,  //  009C  MOVE	R11	R7
      0x7C200600,  //  009D  CALL	R8	3
      0x80041000,  //  009E  RET	1	R8
      0x4C1C0000,  //  009F  LDNIL	R7
      0x80040E00,  //  00A0  RET	1	R7
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: subscribe_attribute
********************************************************************/
be_local_closure(class_Matter_Plugin_subscribe_attribute,   /* name */
  be_nested_proto(
    6,                          /* nstack */
    5,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Matter_Plugin,     /* shared constants */
    be_str_weak(subscribe_attribute),
    &be_const_str_solidified,
    ( &(const binstruction[ 2]) {  /* code */
      0x4C140000,  //  0000  LDNIL	R5
      0x80040A00,  //  0001  RET	1	R5
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Matter_Plugin
********************************************************************/
be_local_class(Matter_Plugin,
    6,
    NULL,
    be_nested_map(52,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_weak(subscribe_attribute, -1), be_const_closure(class_Matter_Plugin_subscribe_attribute_closure) },
        { be_const_key_weak(state_json, 38), be_const_closure(class_Matter_Plugin_state_json_closure) },
        { be_const_key_weak(update_shadow_lazy, -1), be_const_closure(class_Matter_Plugin_update_shadow_lazy_closure) },
        { be_const_key_weak(device, -1), be_const_var(1) },
        { be_const_key_weak(ack_request, -1), be_const_closure(class_Matter_Plugin_ack_request_closure) },
        { be_const_key_weak(UPDATE_TIME, -1), be_const_int(5000) },
        { be_const_key_weak(get_cluster_list_sorted, -1), be_const_closure(class_Matter_Plugin_get_cluster_list_sorted_closure) },
        { be_const_key_weak(write_attribute, -1), be_const_closure(class_Matter_Plugin_write_attribute_closure) },
        { be_const_key_weak(BRIDGE, -1), be_const_bool(0) },
        { be_const_key_weak(get_clusters, -1), be_const_closure(class_Matter_Plugin_get_clusters_closure) },
        { be_const_key_weak(CLUSTERS, 51), be_const_simple_instance(be_nested_simple_instance(&be_class_map, {
        be_const_map( *     be_nested_map(1,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_int(29, -1), be_const_simple_instance(be_nested_simple_instance(&be_class_list, {
        be_const_list( *     be_nested_list(10,
    ( (struct bvalue*) &(const bvalue[]) {
        be_const_int(0),
        be_const_int(1),
        be_const_int(2),
        be_const_int(3),
        be_const_int(65528),
        be_const_int(65529),
        be_const_int(65530),
        be_const_int(65531),
        be_const_int(65532),
        be_const_int(65533),
    }))    ) } )) },
    }))    ) } )) },
        { be_const_key_weak(UPDATE_COMMANDS, -1), be_const_simple_instance(be_nested_simple_instance(&be_class_list, {
        be_const_list( *     be_nested_list(0,
    ( (struct bvalue*) &(const bvalue[]) {
    }))    ) } )) },
        { be_const_key_weak(every_250ms, 0), be_const_closure(class_Matter_Plugin_every_250ms_closure) },
        { be_const_key_weak(publish_command, -1), be_const_closure(class_Matter_Plugin_publish_command_closure) },
        { be_const_key_weak(get_attribute_list, -1), be_const_closure(class_Matter_Plugin_get_attribute_list_closure) },
        { be_const_key_weak(set_name, -1), be_const_closure(class_Matter_Plugin_set_name_closure) },
        { be_const_key_weak(ARG_TYPE, -1), be_const_static_closure(class_Matter_Plugin__X3Clambda_X3E_closure) },
        { be_const_key_weak(update_virtual, -1), be_const_closure(class_Matter_Plugin_update_virtual_closure) },
        { be_const_key_weak(timed_request, -1), be_const_closure(class_Matter_Plugin_timed_request_closure) },
        { be_const_key_weak(init, -1), be_const_closure(class_Matter_Plugin_init_closure) },
        { be_const_key_weak(is_local_device, 34), be_const_closure(class_Matter_Plugin_is_local_device_closure) },
        { be_const_key_weak(COMMANDS, -1), be_const_simple_instance(be_nested_simple_instance(&be_class_map, {
        be_const_map( *     be_nested_map(1,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_int(29, -1), be_const_nil() },
    }))    ) } )) },
        { be_const_key_weak(clusters, -1), be_const_var(3) },
        { be_const_key_weak(VIRTUAL, 5), be_const_bool(0) },
        { be_const_key_weak(CLUSTER_REVISIONS, 23), be_const_simple_instance(be_nested_simple_instance(&be_class_map, {
        be_const_map( *     be_nested_map(25,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_int(8, -1), be_const_int(5) },
        { be_const_key_int(1026, -1), be_const_int(4) },
        { be_const_key_int(1027, -1), be_const_int(3) },
        { be_const_key_int(3, 20), be_const_int(4) },
        { be_const_key_int(29, 17), be_const_int(2) },
        { be_const_key_int(5, 9), be_const_int(5) },
        { be_const_key_int(56, 11), be_const_int(2) },
        { be_const_key_int(257, 10), be_const_int(7) },
        { be_const_key_int(258, 0), be_const_int(5) },
        { be_const_key_int(1030, -1), be_const_int(3) },
        { be_const_key_int(1032, -1), be_const_int(3) },
        { be_const_key_int(1031, 23), be_const_int(3) },
        { be_const_key_int(512, -1), be_const_int(4) },
        { be_const_key_int(63, 22), be_const_int(2) },
        { be_const_key_int(514, -1), be_const_int(4) },
        { be_const_key_int(40, -1), be_const_int(2) },
        { be_const_key_int(516, -1), be_const_int(2) },
        { be_const_key_int(1029, 21), be_const_int(3) },
        { be_const_key_int(768, -1), be_const_int(6) },
        { be_const_key_int(769, -1), be_const_int(4) },
        { be_const_key_int(1028, -1), be_const_int(3) },
        { be_const_key_int(4, -1), be_const_int(4) },
        { be_const_key_int(513, -1), be_const_int(6) },
        { be_const_key_int(6, -1), be_const_int(5) },
        { be_const_key_int(1024, -1), be_const_int(3) },
    }))    ) } )) },
        { be_const_key_weak(consolidate_update_commands, 6), be_const_closure(class_Matter_Plugin_consolidate_update_commands_closure) },
        { be_const_key_weak(ui_conf_to_string, -1), be_const_static_closure(class_Matter_Plugin_ui_conf_to_string_closure) },
        { be_const_key_weak(_parse_update_virtual, 36), be_const_closure(class_Matter_Plugin__parse_update_virtual_closure) },
        { be_const_key_weak(update_next, 17), be_const_var(0) },
        { be_const_key_weak(ARG_HINT, -1), be_nested_str_weak(_Not_X20used_) },
        { be_const_key_weak(parse_configuration, -1), be_const_closure(class_Matter_Plugin_parse_configuration_closure) },
        { be_const_key_weak(invoke_request, 27), be_const_closure(class_Matter_Plugin_invoke_request_closure) },
        { be_const_key_weak(node_label, -1), be_const_var(5) },
        { be_const_key_weak(update_shadow, 30), be_const_closure(class_Matter_Plugin_update_shadow_closure) },
        { be_const_key_weak(endpoint, 2), be_const_var(2) },
        { be_const_key_weak(get_name, -1), be_const_closure(class_Matter_Plugin_get_name_closure) },
        { be_const_key_weak(attribute_updated, -1), be_const_closure(class_Matter_Plugin_attribute_updated_closure) },
        { be_const_key_weak(get_endpoint, -1), be_const_closure(class_Matter_Plugin_get_endpoint_closure) },
        { be_const_key_weak(FEATURE_MAPS, -1), be_const_simple_instance(be_nested_simple_instance(&be_class_map, {
        be_const_map( *     be_nested_map(3,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key_int(258, -1), be_const_int(5) },
        { be_const_key_int(49, 2), be_const_int(4) },
        { be_const_key_int(514, -1), be_const_int(2) },
    }))    ) } )) },
        { be_const_key_weak(ARG, -1), be_nested_str_weak() },
        { be_const_key_weak(subscribe_event, -1), be_const_closure(class_Matter_Plugin_subscribe_event_closure) },
        { be_const_key_weak(TYPE, -1), be_nested_str_weak() },
        { be_const_key_weak(read_event, -1), be_const_closure(class_Matter_Plugin_read_event_closure) },
        { be_const_key_weak(publish_event, 21), be_const_closure(class_Matter_Plugin_publish_event_closure) },
        { be_const_key_weak(parse_sensors, -1), be_const_closure(class_Matter_Plugin_parse_sensors_closure) },
        { be_const_key_weak(DISPLAY_NAME, 14), be_nested_str_weak() },
        { be_const_key_weak(ui_string_to_conf, 13), be_const_static_closure(class_Matter_Plugin_ui_string_to_conf_closure) },
        { be_const_key_weak(contains_attribute, 9), be_const_closure(class_Matter_Plugin_contains_attribute_closure) },
        { be_const_key_weak(tick, -1), be_const_var(4) },
        { be_const_key_weak(contains_cluster, -1), be_const_closure(class_Matter_Plugin_contains_cluster_closure) },
        { be_const_key_weak(read_attribute, -1), be_const_closure(class_Matter_Plugin_read_attribute_closure) },
        { be_const_key_weak(append_state_json, -1), be_const_closure(class_Matter_Plugin_append_state_json_closure) },
    })),
    be_str_weak(Matter_Plugin)
);
/********************************************************************/
/* End of solidification */
