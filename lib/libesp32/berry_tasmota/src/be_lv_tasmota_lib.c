/********************************************************************
 * Tasmota LVGL lv_signal_bars widget
 *******************************************************************/
#include "be_constobj.h"

#ifdef USE_LVGL

extern int lv0_start(bvm *vm);

extern int lv0_register_button_encoder(bvm *vm);  // add buttons with encoder logic

extern int lv0_load_montserrat_font(bvm *vm);
extern int lv0_load_seg7_font(bvm *vm);
extern int lv0_load_robotocondensed_latin1_font(bvm *vm);
extern int lv0_load_font_embedded(bvm *vm);

extern int lv0_screenshot(bvm *vm);
extern int lv0_load_freetype_font(bvm *vm);

/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(splash_runner_init,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    1,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 2]) {     /* constants */
    /* K0   */  be_nested_str(tasmota),
    /* K1   */  be_nested_str(add_driver),
    }),
    &be_const_str_init,
    &be_const_str_solidified,
    ( &(const binstruction[ 5]) {  /* code */
      0xB8060000,  //  0000  GETNGBL	R1	K0
      0x8C040301,  //  0001  GETMET	R1	R1	K1
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x7C040400,  //  0003  CALL	R1	2
      0x80000000,  //  0004  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: display
********************************************************************/
be_local_closure(splash_runner_display,   /* name */
  be_nested_proto(
    9,                          /* nstack */
    5,                          /* argc */
    2,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 7]) {     /* constants */
    /* K0   */  be_nested_str(display),
    /* K1   */  be_nested_str(dim),
    /* K2   */  be_nested_str(started),
    /* K3   */  be_nested_str(tasmota),
    /* K4   */  be_nested_str(remove_driver),
    /* K5   */  be_nested_str(lv),
    /* K6   */  be_nested_str(splash),
    }),
    &be_const_str_display,
    &be_const_str_solidified,
    ( &(const binstruction[14]) {  /* code */
      0xA4160000,  //  0000  IMPORT	R5	K0
      0x1C180301,  //  0001  EQ	R6	R1	K1
      0x781A0009,  //  0002  JMPF	R6	#000D
      0x8C180B02,  //  0003  GETMET	R6	R5	K2
      0x7C180200,  //  0004  CALL	R6	1
      0x781A0006,  //  0005  JMPF	R6	#000D
      0xB81A0600,  //  0006  GETNGBL	R6	K3
      0x8C180D04,  //  0007  GETMET	R6	R6	K4
      0x5C200000,  //  0008  MOVE	R8	R0
      0x7C180400,  //  0009  CALL	R6	2
      0xB81A0A00,  //  000A  GETNGBL	R6	K5
      0x8C180D06,  //  000B  GETMET	R6	R6	K6
      0x7C180200,  //  000C  CALL	R6	1
      0x80000000,  //  000D  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: splash_runner
********************************************************************/
be_local_class(splash_runner,
    0,
    NULL,
    be_nested_map(2,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key(display, -1), be_const_closure(splash_runner_display_closure) },
        { be_const_key(init, 0), be_const_closure(splash_runner_init_closure) },
    })),
    be_str_literal("splash_runner")
);

/********************************************************************
** Solidified function: splash_init
********************************************************************/
be_local_closure(lv_tasmota_splash_init,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    0,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 5]) {     /* constants */
    /* K0   */  be_nested_str(display),
    /* K1   */  be_nested_str(started),
    /* K2   */  be_nested_str(lv),
    /* K3   */  be_nested_str(splash),
    /* K4   */  be_const_class(be_class_splash_runner),
    }),
    &be_const_str_splash_init,
    &be_const_str_solidified,
    ( &(const binstruction[13]) {  /* code */
      0xA4020000,  //  0000  IMPORT	R0	K0
      0x8C040101,  //  0001  GETMET	R1	R0	K1
      0x7C040200,  //  0002  CALL	R1	1
      0x78060003,  //  0003  JMPF	R1	#0008
      0xB8060400,  //  0004  GETNGBL	R1	K2
      0x8C040303,  //  0005  GETMET	R1	R1	K3
      0x7C040200,  //  0006  CALL	R1	1
      0x70020003,  //  0007  JMP		#000C
      0x58040004,  //  0008  LDCONST	R1	K4
      0xB4000004,  //  0009  CLASS	K4
      0x5C080200,  //  000A  MOVE	R2	R1
      0x7C080000,  //  000B  CALL	R2	0
      0x80000000,  //  000C  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: splash
********************************************************************/
be_local_closure(lv_tasmota_splash,   /* name */
  be_nested_proto(
    13,                          /* nstack */
    0,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    1,                          /* has sup protos */
    ( &(const struct bproto*[ 1]) {
      be_nested_proto(
        2,                          /* nstack */
        0,                          /* argc */
        0,                          /* varg */
        1,                          /* has upvals */
        ( &(const bupvaldesc[ 1]) {  /* upvals */
          be_local_const_upval(1, 1),
        }),
        0,                          /* has sup protos */
        NULL,                       /* no sub protos */
        1,                          /* has constants */
        ( &(const bvalue[ 1]) {     /* constants */
        /* K0   */  be_nested_str(del),
        }),
        &be_const_str__X3Clambda_X3E,
        &be_const_str_solidified,
        ( &(const binstruction[ 4]) {  /* code */
          0x68000000,  //  0000  GETUPV	R0	U0
          0x8C000100,  //  0001  GETMET	R0	R0	K0
          0x7C000200,  //  0002  CALL	R0	1
          0x80040000,  //  0003  RET	1	R0
        })
      ),
    }),
    1,                          /* has constants */
    ( &(const bvalue[37]) {     /* constants */
    /* K0   */  be_nested_str(display),
    /* K1   */  be_nested_str(started),
    /* K2   */  be_nested_str(lv),
    /* K3   */  be_nested_str(start),
    /* K4   */  be_nested_str(obj),
    /* K5   */  be_nested_str(scr_act),
    /* K6   */  be_nested_str(montserrat_font),
    /* K7   */  be_nested_str(color),
    /* K8   */  be_nested_str(COLOR_WHITE),
    /* K9   */  be_nested_str(set_style_bg_color),
    /* K10  */  be_const_int(0),
    /* K11  */  be_nested_str(set_style_radius),
    /* K12  */  be_nested_str(set_style_pad_all),
    /* K13  */  be_nested_str(set_style_border_width),
    /* K14  */  be_nested_str(set_size),
    /* K15  */  be_nested_str(pct),
    /* K16  */  be_nested_str(refr_pos),
    /* K17  */  be_nested_str(refr_size),
    /* K18  */  be_nested_str(img),
    /* K19  */  be_nested_str(set_tasmota_logo),
    /* K20  */  be_nested_str(set_zoom),
    /* K21  */  be_nested_str(set_style_img_recolor_opa),
    /* K22  */  be_nested_str(set_style_img_recolor),
    /* K23  */  be_nested_str(set_align),
    /* K24  */  be_nested_str(ALIGN_LEFT_MID),
    /* K25  */  be_nested_str(set_x),
    /* K26  */  be_nested_str(label),
    /* K27  */  be_nested_str(set_style_text_color),
    /* K28  */  be_nested_str(set_text),
    /* K29  */  be_nested_str(TASMOTA),
    /* K30  */  be_nested_str(set_style_text_font),
    /* K31  */  be_nested_str(driver_name),
    /* K32  */  be_nested_str(ALIGN_BOTTOM_MID),
    /* K33  */  be_const_int(16777215),
    /* K34  */  be_nested_str(refr_now),
    /* K35  */  be_nested_str(tasmota),
    /* K36  */  be_nested_str(set_timer),
    }),
    &be_const_str_splash,
    &be_const_str_solidified,
    ( &(const binstruction[143]) {  /* code */
      0xA4020000,  //  0000  IMPORT	R0	K0
      0x8C040101,  //  0001  GETMET	R1	R0	K1
      0x7C040200,  //  0002  CALL	R1	1
      0x74060000,  //  0003  JMPT	R1	#0005
      0x80000200,  //  0004  RET	0
      0xB8060400,  //  0005  GETNGBL	R1	K2
      0x8C040303,  //  0006  GETMET	R1	R1	K3
      0x7C040200,  //  0007  CALL	R1	1
      0xB8060400,  //  0008  GETNGBL	R1	K2
      0x8C040304,  //  0009  GETMET	R1	R1	K4
      0xB80E0400,  //  000A  GETNGBL	R3	K2
      0x8C0C0705,  //  000B  GETMET	R3	R3	K5
      0x7C0C0200,  //  000C  CALL	R3	1
      0x7C040400,  //  000D  CALL	R1	2
      0xB80A0400,  //  000E  GETNGBL	R2	K2
      0x8C080506,  //  000F  GETMET	R2	R2	K6
      0x5412001B,  //  0010  LDINT	R4	28
      0x7C080400,  //  0011  CALL	R2	2
      0xB80E0400,  //  0012  GETNGBL	R3	K2
      0x8C0C0707,  //  0013  GETMET	R3	R3	K7
      0xB8160400,  //  0014  GETNGBL	R5	K2
      0x88140B08,  //  0015  GETMBR	R5	R5	K8
      0x7C0C0400,  //  0016  CALL	R3	2
      0x8C100309,  //  0017  GETMET	R4	R1	K9
      0xB81A0400,  //  0018  GETNGBL	R6	K2
      0x8C180D07,  //  0019  GETMET	R6	R6	K7
      0x54220065,  //  001A  LDINT	R8	102
      0x7C180400,  //  001B  CALL	R6	2
      0x581C000A,  //  001C  LDCONST	R7	K10
      0x7C100600,  //  001D  CALL	R4	3
      0x8C10030B,  //  001E  GETMET	R4	R1	K11
      0x5818000A,  //  001F  LDCONST	R6	K10
      0x581C000A,  //  0020  LDCONST	R7	K10
      0x7C100600,  //  0021  CALL	R4	3
      0x8C10030C,  //  0022  GETMET	R4	R1	K12
      0x5818000A,  //  0023  LDCONST	R6	K10
      0x581C000A,  //  0024  LDCONST	R7	K10
      0x7C100600,  //  0025  CALL	R4	3
      0x8C10030D,  //  0026  GETMET	R4	R1	K13
      0x5818000A,  //  0027  LDCONST	R6	K10
      0x581C000A,  //  0028  LDCONST	R7	K10
      0x7C100600,  //  0029  CALL	R4	3
      0x8C10030E,  //  002A  GETMET	R4	R1	K14
      0xB81A0400,  //  002B  GETNGBL	R6	K2
      0x8C180D0F,  //  002C  GETMET	R6	R6	K15
      0x54220063,  //  002D  LDINT	R8	100
      0x7C180400,  //  002E  CALL	R6	2
      0xB81E0400,  //  002F  GETNGBL	R7	K2
      0x8C1C0F0F,  //  0030  GETMET	R7	R7	K15
      0x54260063,  //  0031  LDINT	R9	100
      0x7C1C0400,  //  0032  CALL	R7	2
      0x7C100600,  //  0033  CALL	R4	3
      0x8C100310,  //  0034  GETMET	R4	R1	K16
      0x7C100200,  //  0035  CALL	R4	1
      0x8C100311,  //  0036  GETMET	R4	R1	K17
      0x7C100200,  //  0037  CALL	R4	1
      0xB8120400,  //  0038  GETNGBL	R4	K2
      0x8C100912,  //  0039  GETMET	R4	R4	K18
      0x5C180200,  //  003A  MOVE	R6	R1
      0x7C100400,  //  003B  CALL	R4	2
      0x8C140913,  //  003C  GETMET	R5	R4	K19
      0x7C140200,  //  003D  CALL	R5	1
      0x8C140914,  //  003E  GETMET	R5	R4	K20
      0x541E0095,  //  003F  LDINT	R7	150
      0x7C140400,  //  0040  CALL	R5	2
      0x8C140915,  //  0041  GETMET	R5	R4	K21
      0x541E00FE,  //  0042  LDINT	R7	255
      0x5820000A,  //  0043  LDCONST	R8	K10
      0x7C140600,  //  0044  CALL	R5	3
      0x8C140916,  //  0045  GETMET	R5	R4	K22
      0x5C1C0600,  //  0046  MOVE	R7	R3
      0x5820000A,  //  0047  LDCONST	R8	K10
      0x7C140600,  //  0048  CALL	R5	3
      0x8C140917,  //  0049  GETMET	R5	R4	K23
      0xB81E0400,  //  004A  GETNGBL	R7	K2
      0x881C0F18,  //  004B  GETMBR	R7	R7	K24
      0x7C140400,  //  004C  CALL	R5	2
      0x8C140919,  //  004D  GETMET	R5	R4	K25
      0x541DFFF3,  //  004E  LDINT	R7	-12
      0x7C140400,  //  004F  CALL	R5	2
      0xB8160400,  //  0050  GETNGBL	R5	K2
      0x8C140B1A,  //  0051  GETMET	R5	R5	K26
      0x5C1C0200,  //  0052  MOVE	R7	R1
      0x7C140400,  //  0053  CALL	R5	2
      0x8C180B1B,  //  0054  GETMET	R6	R5	K27
      0x5C200600,  //  0055  MOVE	R8	R3
      0x5824000A,  //  0056  LDCONST	R9	K10
      0x7C180600,  //  0057  CALL	R6	3
      0x8C180B1C,  //  0058  GETMET	R6	R5	K28
      0x5820001D,  //  0059  LDCONST	R8	K29
      0x7C180400,  //  005A  CALL	R6	2
      0x4C180000,  //  005B  LDNIL	R6
      0x20180406,  //  005C  NE	R6	R2	R6
      0x781A0003,  //  005D  JMPF	R6	#0062
      0x8C180B1E,  //  005E  GETMET	R6	R5	K30
      0x5C200400,  //  005F  MOVE	R8	R2
      0x5824000A,  //  0060  LDCONST	R9	K10
      0x7C180600,  //  0061  CALL	R6	3
      0x8C180B17,  //  0062  GETMET	R6	R5	K23
      0xB8220400,  //  0063  GETNGBL	R8	K2
      0x88201118,  //  0064  GETMBR	R8	R8	K24
      0x7C180400,  //  0065  CALL	R6	2
      0x8C180B19,  //  0066  GETMET	R6	R5	K25
      0x54220029,  //  0067  LDINT	R8	42
      0x7C180400,  //  0068  CALL	R6	2
      0x8C18011F,  //  0069  GETMET	R6	R0	K31
      0x7C180200,  //  006A  CALL	R6	1
      0x4C1C0000,  //  006B  LDNIL	R7
      0x6020000C,  //  006C  GETGBL	R8	G12
      0x5C240C00,  //  006D  MOVE	R9	R6
      0x7C200200,  //  006E  CALL	R8	1
      0x2420110A,  //  006F  GT	R8	R8	K10
      0x78220012,  //  0070  JMPF	R8	#0084
      0xB8220400,  //  0071  GETNGBL	R8	K2
      0x8C20111A,  //  0072  GETMET	R8	R8	K26
      0x5C280200,  //  0073  MOVE	R10	R1
      0x7C200400,  //  0074  CALL	R8	2
      0x5C1C1000,  //  0075  MOVE	R7	R8
      0x8C200F17,  //  0076  GETMET	R8	R7	K23
      0xB82A0400,  //  0077  GETNGBL	R10	K2
      0x88281520,  //  0078  GETMBR	R10	R10	K32
      0x7C200400,  //  0079  CALL	R8	2
      0x8C200F1B,  //  007A  GETMET	R8	R7	K27
      0xB82A0400,  //  007B  GETNGBL	R10	K2
      0x8C281507,  //  007C  GETMET	R10	R10	K7
      0x58300021,  //  007D  LDCONST	R12	K33
      0x7C280400,  //  007E  CALL	R10	2
      0x582C000A,  //  007F  LDCONST	R11	K10
      0x7C200600,  //  0080  CALL	R8	3
      0x8C200F1C,  //  0081  GETMET	R8	R7	K28
      0x5C280C00,  //  0082  MOVE	R10	R6
      0x7C200400,  //  0083  CALL	R8	2
      0xB8220400,  //  0084  GETNGBL	R8	K2
      0x8C201122,  //  0085  GETMET	R8	R8	K34
      0x5828000A,  //  0086  LDCONST	R10	K10
      0x7C200400,  //  0087  CALL	R8	2
      0xB8224600,  //  0088  GETNGBL	R8	K35
      0x8C201124,  //  0089  GETMET	R8	R8	K36
      0x542A1387,  //  008A  LDINT	R10	5000
      0x842C0000,  //  008B  CLOSURE	R11	P0
      0x7C200600,  //  008C  CALL	R8	3
      0xA0000000,  //  008D  CLOSE	R0
      0x80000000,  //  008E  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(lv_tasmota_init,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[26]) {     /* constants */
    /* K0   */  be_nested_str(lv),
    /* K1   */  be_nested_str(start),
    /* K2   */  be_nested_str(splash_init),
    /* K3   */  be_nested_str(splash),
    /* K4   */  be_nested_str(font_montserrat),
    /* K5   */  be_nested_str(montserrat_font),
    /* K6   */  be_nested_str(font_seg7),
    /* K7   */  be_nested_str(seg7_font),
    /* K8   */  be_nested_str(font_embedded),
    /* K9   */  be_nested_str(load_freetype_font),
    /* K10  */  be_nested_str(register_button_encoder),
    /* K11  */  be_nested_str(screenshot),
    /* K12  */  be_nested_str(clock_icon),
    /* K13  */  be_nested_str(lv_clock_icon),
    /* K14  */  be_nested_str(signal_arcs),
    /* K15  */  be_nested_str(lv_signal_arcs),
    /* K16  */  be_nested_str(signal_bars),
    /* K17  */  be_nested_str(lv_signal_bars),
    /* K18  */  be_nested_str(wifi_arcs_icon),
    /* K19  */  be_nested_str(lv_wifi_arcs_icon),
    /* K20  */  be_nested_str(wifi_arcs),
    /* K21  */  be_nested_str(lv_wifi_arcs),
    /* K22  */  be_nested_str(wifi_bars_icon),
    /* K23  */  be_nested_str(lv_wifi_bars_icon),
    /* K24  */  be_nested_str(wifi_bars),
    /* K25  */  be_nested_str(lv_wifi_bars),
    }),
    &be_const_str_init,
    &be_const_str_solidified,
    ( &(const binstruction[41]) {  /* code */
      0xA4060000,  //  0000  IMPORT	R1	K0
      0x88080101,  //  0001  GETMBR	R2	R0	K1
      0x90060202,  //  0002  SETMBR	R1	K1	R2
      0x88080102,  //  0003  GETMBR	R2	R0	K2
      0x90060402,  //  0004  SETMBR	R1	K2	R2
      0x88080103,  //  0005  GETMBR	R2	R0	K3
      0x90060602,  //  0006  SETMBR	R1	K3	R2
      0x88080104,  //  0007  GETMBR	R2	R0	K4
      0x90060802,  //  0008  SETMBR	R1	K4	R2
      0x88080104,  //  0009  GETMBR	R2	R0	K4
      0x90060A02,  //  000A  SETMBR	R1	K5	R2
      0x88080106,  //  000B  GETMBR	R2	R0	K6
      0x90060C02,  //  000C  SETMBR	R1	K6	R2
      0x88080106,  //  000D  GETMBR	R2	R0	K6
      0x90060E02,  //  000E  SETMBR	R1	K7	R2
      0x88080108,  //  000F  GETMBR	R2	R0	K8
      0x90061002,  //  0010  SETMBR	R1	K8	R2
      0x88080109,  //  0011  GETMBR	R2	R0	K9
      0x90061202,  //  0012  SETMBR	R1	K9	R2
      0x8808010A,  //  0013  GETMBR	R2	R0	K10
      0x90061402,  //  0014  SETMBR	R1	K10	R2
      0x8808010B,  //  0015  GETMBR	R2	R0	K11
      0x90061602,  //  0016  SETMBR	R1	K11	R2
      0xB80A1A00,  //  0017  GETNGBL	R2	K13
      0x90061802,  //  0018  SETMBR	R1	K12	R2
      0xB80A1E00,  //  0019  GETNGBL	R2	K15
      0x90061C02,  //  001A  SETMBR	R1	K14	R2
      0xB80A2200,  //  001B  GETNGBL	R2	K17
      0x90062002,  //  001C  SETMBR	R1	K16	R2
      0xB80A2600,  //  001D  GETNGBL	R2	K19
      0x90062402,  //  001E  SETMBR	R1	K18	R2
      0xB80A2A00,  //  001F  GETNGBL	R2	K21
      0x90062802,  //  0020  SETMBR	R1	K20	R2
      0xB80A2E00,  //  0021  GETNGBL	R2	K23
      0x90062C02,  //  0022  SETMBR	R1	K22	R2
      0xB80A3200,  //  0023  GETNGBL	R2	K25
      0x90063002,  //  0024  SETMBR	R1	K24	R2
      0x8C080302,  //  0025  GETMET	R2	R1	K2
      0x7C080200,  //  0026  CALL	R2	1
      0x4C080000,  //  0027  LDNIL	R2
      0x80040400,  //  0028  RET	1	R2
    })
  )
);
/*******************************************************************/

/* @const_object_info_begin
module lv_tasmota (scope: global) {
    init, closure(lv_tasmota_init_closure)

    start, func(lv0_start)
    splash, closure(lv_tasmota_splash_closure)
    splash_init, closure(lv_tasmota_splash_init_closure)

    font_montserrat, func(lv0_load_montserrat_font)
    montserrat_font, func(lv0_load_montserrat_font)
    font_seg7, func(lv0_load_seg7_font)
    seg7_font, func(lv0_load_seg7_font)
    font_embedded, func(lv0_load_font_embedded)
    register_button_encoder, func(lv0_register_button_encoder)
    screenshot, func(lv0_screenshot)

    load_freetype_font, func(lv0_load_freetype_font)
}
@const_object_info_end */
#include "be_fixed_lv_tasmota.h"

#endif // USE_LVGL