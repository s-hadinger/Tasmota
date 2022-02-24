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
    16,                          /* nstack */
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
        0,                          /* has upvals */
        NULL,                       /* no upvals */
        0,                          /* has sup protos */
        NULL,                       /* no sub protos */
        1,                          /* has constants */
        ( &(const bvalue[ 5]) {     /* constants */
        /* K0   */  be_nested_str(lv),
        /* K1   */  be_nested_str(scr_act),
        /* K2   */  be_nested_str(get_user_data),
        /* K3   */  be_const_int(1399876712),
        /* K4   */  be_nested_str(start),
        }),
        &be_const_str_remove_splash,
        &be_const_str_solidified,
        ( &(const binstruction[11]) {  /* code */
          0xB8020000,  //  0000  GETNGBL	R0	K0
          0x8C000101,  //  0001  GETMET	R0	R0	K1
          0x7C000200,  //  0002  CALL	R0	1
          0x8C000102,  //  0003  GETMET	R0	R0	K2
          0x7C000200,  //  0004  CALL	R0	1
          0x1C000103,  //  0005  EQ	R0	R0	K3
          0x78020002,  //  0006  JMPF	R0	#000A
          0xB8020000,  //  0007  GETNGBL	R0	K0
          0x8C000104,  //  0008  GETMET	R0	R0	K4
          0x7C000200,  //  0009  CALL	R0	1
          0x80000000,  //  000A  RET	0
        })
      ),
    }),
    1,                          /* has constants */
    ( &(const bvalue[33]) {     /* constants */
    /* K0   */  be_nested_str(global),
    /* K1   */  be_nested_str(display),
    /* K2   */  be_nested_str(started),
    /* K3   */  be_nested_str(lv),
    /* K4   */  be_nested_str(start),
    /* K5   */  be_nested_str(get_hor_res),
    /* K6   */  be_nested_str(get_ver_res),
    /* K7   */  be_nested_str(scr_act),
    /* K8   */  be_nested_str(montserrat_font),
    /* K9   */  be_nested_str(color),
    /* K10  */  be_nested_str(COLOR_WHITE),
    /* K11  */  be_nested_str(set_style_bg_color),
    /* K12  */  be_const_int(0),
    /* K13  */  be_nested_str(set_user_data),
    /* K14  */  be_const_int(1399876712),
    /* K15  */  be_nested_str(img),
    /* K16  */  be_nested_str(set_tasmota_logo),
    /* K17  */  be_nested_str(set_zoom),
    /* K18  */  be_nested_str(set_style_img_recolor_opa),
    /* K19  */  be_nested_str(set_style_img_recolor),
    /* K20  */  be_nested_str(set_align),
    /* K21  */  be_nested_str(ALIGN_LEFT_MID),
    /* K22  */  be_nested_str(set_x),
    /* K23  */  be_nested_str(label),
    /* K24  */  be_nested_str(set_style_text_color),
    /* K25  */  be_nested_str(set_text),
    /* K26  */  be_nested_str(TASMOTA),
    /* K27  */  be_nested_str(set_style_text_font),
    /* K28  */  be_nested_str(driver_name),
    /* K29  */  be_nested_str(ALIGN_BOTTOM_MID),
    /* K30  */  be_const_int(16777215),
    /* K31  */  be_nested_str(tasmota),
    /* K32  */  be_nested_str(set_timer),
    }),
    &be_const_str_splash,
    &be_const_str_solidified,
    ( &(const binstruction[120]) {  /* code */
      0xA4020000,  //  0000  IMPORT	R0	K0
      0xA4060200,  //  0001  IMPORT	R1	K1
      0x8C080302,  //  0002  GETMET	R2	R1	K2
      0x7C080200,  //  0003  CALL	R2	1
      0x740A0000,  //  0004  JMPT	R2	#0006
      0x80000400,  //  0005  RET	0
      0xB80A0600,  //  0006  GETNGBL	R2	K3
      0x8C080504,  //  0007  GETMET	R2	R2	K4
      0x7C080200,  //  0008  CALL	R2	1
      0xB80A0600,  //  0009  GETNGBL	R2	K3
      0x8C080505,  //  000A  GETMET	R2	R2	K5
      0x7C080200,  //  000B  CALL	R2	1
      0xB80E0600,  //  000C  GETNGBL	R3	K3
      0x8C0C0706,  //  000D  GETMET	R3	R3	K6
      0x7C0C0200,  //  000E  CALL	R3	1
      0xB8120600,  //  000F  GETNGBL	R4	K3
      0x8C100907,  //  0010  GETMET	R4	R4	K7
      0x7C100200,  //  0011  CALL	R4	1
      0xB8160600,  //  0012  GETNGBL	R5	K3
      0x8C140B08,  //  0013  GETMET	R5	R5	K8
      0x541E001B,  //  0014  LDINT	R7	28
      0x7C140400,  //  0015  CALL	R5	2
      0xB81A0600,  //  0016  GETNGBL	R6	K3
      0x8C180D09,  //  0017  GETMET	R6	R6	K9
      0xB8220600,  //  0018  GETNGBL	R8	K3
      0x8820110A,  //  0019  GETMBR	R8	R8	K10
      0x7C180400,  //  001A  CALL	R6	2
      0x8C1C090B,  //  001B  GETMET	R7	R4	K11
      0xB8260600,  //  001C  GETNGBL	R9	K3
      0x8C241309,  //  001D  GETMET	R9	R9	K9
      0x542E0065,  //  001E  LDINT	R11	102
      0x7C240400,  //  001F  CALL	R9	2
      0x5828000C,  //  0020  LDCONST	R10	K12
      0x7C1C0600,  //  0021  CALL	R7	3
      0x8C1C090D,  //  0022  GETMET	R7	R4	K13
      0x5824000E,  //  0023  LDCONST	R9	K14
      0x7C1C0400,  //  0024  CALL	R7	2
      0xB81E0600,  //  0025  GETNGBL	R7	K3
      0x8C1C0F0F,  //  0026  GETMET	R7	R7	K15
      0x5C240800,  //  0027  MOVE	R9	R4
      0x7C1C0400,  //  0028  CALL	R7	2
      0x8C200F10,  //  0029  GETMET	R8	R7	K16
      0x7C200200,  //  002A  CALL	R8	1
      0x8C200F11,  //  002B  GETMET	R8	R7	K17
      0x542A0095,  //  002C  LDINT	R10	150
      0x7C200400,  //  002D  CALL	R8	2
      0x8C200F12,  //  002E  GETMET	R8	R7	K18
      0x542A00FE,  //  002F  LDINT	R10	255
      0x582C000C,  //  0030  LDCONST	R11	K12
      0x7C200600,  //  0031  CALL	R8	3
      0x8C200F13,  //  0032  GETMET	R8	R7	K19
      0x5C280C00,  //  0033  MOVE	R10	R6
      0x582C000C,  //  0034  LDCONST	R11	K12
      0x7C200600,  //  0035  CALL	R8	3
      0x8C200F14,  //  0036  GETMET	R8	R7	K20
      0xB82A0600,  //  0037  GETNGBL	R10	K3
      0x88281515,  //  0038  GETMBR	R10	R10	K21
      0x7C200400,  //  0039  CALL	R8	2
      0x8C200F16,  //  003A  GETMET	R8	R7	K22
      0x5429FFF3,  //  003B  LDINT	R10	-12
      0x7C200400,  //  003C  CALL	R8	2
      0xB8220600,  //  003D  GETNGBL	R8	K3
      0x8C201117,  //  003E  GETMET	R8	R8	K23
      0x5C280800,  //  003F  MOVE	R10	R4
      0x7C200400,  //  0040  CALL	R8	2
      0x8C241118,  //  0041  GETMET	R9	R8	K24
      0x5C2C0C00,  //  0042  MOVE	R11	R6
      0x5830000C,  //  0043  LDCONST	R12	K12
      0x7C240600,  //  0044  CALL	R9	3
      0x8C241119,  //  0045  GETMET	R9	R8	K25
      0x582C001A,  //  0046  LDCONST	R11	K26
      0x7C240400,  //  0047  CALL	R9	2
      0x4C240000,  //  0048  LDNIL	R9
      0x20240A09,  //  0049  NE	R9	R5	R9
      0x78260003,  //  004A  JMPF	R9	#004F
      0x8C24111B,  //  004B  GETMET	R9	R8	K27
      0x5C2C0A00,  //  004C  MOVE	R11	R5
      0x5830000C,  //  004D  LDCONST	R12	K12
      0x7C240600,  //  004E  CALL	R9	3
      0x8C241114,  //  004F  GETMET	R9	R8	K20
      0xB82E0600,  //  0050  GETNGBL	R11	K3
      0x882C1715,  //  0051  GETMBR	R11	R11	K21
      0x7C240400,  //  0052  CALL	R9	2
      0x8C241116,  //  0053  GETMET	R9	R8	K22
      0x542E0029,  //  0054  LDINT	R11	42
      0x7C240400,  //  0055  CALL	R9	2
      0x8C24031C,  //  0056  GETMET	R9	R1	K28
      0x7C240200,  //  0057  CALL	R9	1
      0x4C280000,  //  0058  LDNIL	R10
      0x602C000C,  //  0059  GETGBL	R11	G12
      0x5C301200,  //  005A  MOVE	R12	R9
      0x7C2C0200,  //  005B  CALL	R11	1
      0x242C170C,  //  005C  GT	R11	R11	K12
      0x782E0012,  //  005D  JMPF	R11	#0071
      0xB82E0600,  //  005E  GETNGBL	R11	K3
      0x8C2C1717,  //  005F  GETMET	R11	R11	K23
      0x5C340800,  //  0060  MOVE	R13	R4
      0x7C2C0400,  //  0061  CALL	R11	2
      0x5C281600,  //  0062  MOVE	R10	R11
      0x8C2C1514,  //  0063  GETMET	R11	R10	K20
      0xB8360600,  //  0064  GETNGBL	R13	K3
      0x88341B1D,  //  0065  GETMBR	R13	R13	K29
      0x7C2C0400,  //  0066  CALL	R11	2
      0x8C2C1518,  //  0067  GETMET	R11	R10	K24
      0xB8360600,  //  0068  GETNGBL	R13	K3
      0x8C341B09,  //  0069  GETMET	R13	R13	K9
      0x583C001E,  //  006A  LDCONST	R15	K30
      0x7C340400,  //  006B  CALL	R13	2
      0x5838000C,  //  006C  LDCONST	R14	K12
      0x7C2C0600,  //  006D  CALL	R11	3
      0x8C2C1519,  //  006E  GETMET	R11	R10	K25
      0x5C341200,  //  006F  MOVE	R13	R9
      0x7C2C0400,  //  0070  CALL	R11	2
      0x842C0000,  //  0071  CLOSURE	R11	P0
      0xB8323E00,  //  0072  GETNGBL	R12	K31
      0x8C301920,  //  0073  GETMET	R12	R12	K32
      0x543A1387,  //  0074  LDINT	R14	5000
      0x5C3C1600,  //  0075  MOVE	R15	R11
      0x7C300600,  //  0076  CALL	R12	3
      0x80000000,  //  0077  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(lv_tasmota_init,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[28]) {     /* constants */
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
    /* K26  */  be_nested_str(display),
    /* K27  */  be_nested_str(started),
    }),
    &be_const_str_init,
    &be_const_str_solidified,
    ( &(const binstruction[45]) {  /* code */
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
      0xA40A3400,  //  0025  IMPORT	R2	K26
      0x8C0C051B,  //  0026  GETMET	R3	R2	K27
      0x7C0C0200,  //  0027  CALL	R3	1
      0x780E0001,  //  0028  JMPF	R3	#002B
      0x8C0C0302,  //  0029  GETMET	R3	R1	K2
      0x7C0C0200,  //  002A  CALL	R3	1
      0x4C0C0000,  //  002B  LDNIL	R3
      0x80040600,  //  002C  RET	1	R3
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