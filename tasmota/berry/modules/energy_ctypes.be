#
# ctype buidings for Tasmota Energy driver
#
# To generate C bindings, do:
# > compile("energy_ctypes.be","file")()
#
# and copy/paste output in C format
#
import ctypes

ctypes.print_types()


energy_struct = [
    [lv_coord, "x"],
    [lv_coord, "y"],
]
energy_struct = ctypes.structure(energy_struct, "energy_struct")

# struct ENERGY {
#   float voltage[ENERGY_MAX_PHASES];             // 123.1 V
#   float current[ENERGY_MAX_PHASES];             // 123.123 A
#   float active_power[ENERGY_MAX_PHASES];        // 123.1 W
#   float apparent_power[ENERGY_MAX_PHASES];      // 123.1 VA
#   float reactive_power[ENERGY_MAX_PHASES];      // 123.1 VAr
#   float power_factor[ENERGY_MAX_PHASES];        // 0.12
#   float frequency[ENERGY_MAX_PHASES];           // 123.1 Hz
# #if defined(SDM630_IMPORT) || defined(SDM72_IMPEXP)
#   float import_active[ENERGY_MAX_PHASES];       // 123.123 kWh
# #endif  // SDM630_IMPORT || SDM72_IMPEXP
#   float export_active[ENERGY_MAX_PHASES];       // 123.123 kWh

#   float start_energy;                           // 12345.12345 kWh total previous
#   float daily;                                  // 123.123 kWh
#   float total;                                  // 12345.12345 kWh total energy

#   unsigned long kWhtoday_delta;                 // 1212312345 Wh 10^-5 (deca micro Watt hours) - Overflows to Energy.kWhtoday (HLW and CSE only)
#   unsigned long kWhtoday_offset;                // 12312312 Wh * 10^-2 (deca milli Watt hours) - 5764 = 0.05764 kWh = 0.058 kWh = Energy.daily
#   unsigned long kWhtoday;                       // 12312312 Wh * 10^-2 (deca milli Watt hours) - 5764 = 0.05764 kWh = 0.058 kWh = Energy.daily
#   unsigned long period;                         // 12312312 Wh * 10^-2 (deca milli Watt hours) - 5764 = 0.05764 kWh = 0.058 kWh = Energy.daily

#   uint8_t fifth_second;
#   uint8_t command_code;
#   uint8_t data_valid[ENERGY_MAX_PHASES];

#   uint8_t phase_count;                          // Number of phases active
#   bool voltage_common;                          // Use single voltage
#   bool frequency_common;                        // Use single frequency
#   bool use_overtemp;                            // Use global temperature as overtemp trigger on internal energy monitor hardware
#   bool kWhtoday_offset_init;

#   bool voltage_available;                       // Enable if voltage is measured
#   bool current_available;                       // Enable if current is measured

#   bool type_dc;
#   bool power_on;

# #ifdef USE_ENERGY_MARGIN_DETECTION
#   uint16_t power_history[ENERGY_MAX_PHASES][3];
#   uint8_t power_steady_counter;                 // Allow for power on stabilization
#   bool min_power_flag;
#   bool max_power_flag;
#   bool min_voltage_flag;
#   bool max_voltage_flag;
#   bool min_current_flag;
#   bool max_current_flag;

# #ifdef USE_ENERGY_POWER_LIMIT
#   uint16_t mplh_counter;
#   uint16_t mplw_counter;
#   uint8_t mplr_counter;
#   uint8_t max_energy_state;
# #endif  // USE_ENERGY_POWER_LIMIT
# #endif  // USE_ENERGY_MARGIN_DETECTION
# } Energy;




lv_style_int = ctypes.i16
lv_color = [ctypes.u16, "lv_color"]        # cast to the class instance, constructor is called with 2 args: (nil, value)
lv_grad_dir = ctypes.u8
lv_opa = ctypes.u8
lv_blend_mode = ctypes.u8
lv_align = ctypes.u8
lv_coord = ctypes.i16
lv_bidi_dir = ctypes.u8
lv_txt_flag = ctypes.u8
lv_text_decor = ctypes.u8
lv_font = ctypes.u32
uint8_t_1 = ctypes.bf_1
uint8_t_2 = ctypes.bf_2
uint8_t = ctypes.u8
uint16_t = ctypes.u16
uint32_t = ctypes.u32
int32_t = ctypes.i32
ptr = ctypes.u32

lv_point = [
    [lv_coord, "x"],
    [lv_coord, "y"],
]
lv_point = ctypes.structure(lv_point, "lv_point")

lv_area = [
    [lv_coord, "x1"],
    [lv_coord, "y1"],
    [lv_coord, "x2"],
    [lv_coord, "y2"],
]
lv_area = ctypes.structure(lv_area, "lv_area")

# test_t = [
#     [lv_area, "a"],
#     [lv_area, "b"]
# ]
# test_t = ctypes.structure(test_t, "test_t")

lv_draw_rect_dsc = [
    [lv_style_int, "radius"],

    #/*Background*/
    [lv_color, "bg_color"],
    [lv_color, "bg_grad_color"],
    [lv_grad_dir, "bg_grad_dir"],
    [lv_style_int, "bg_main_color_stop"],
    [lv_style_int, "bg_grad_color_stop"],
    [lv_opa, "bg_opa"],
    [lv_blend_mode, "bg_blend_mode"],

    #/*Border*/
    [lv_color, "border_color"],
    [lv_style_int, "border_width"],
    [lv_style_int, "border_side"],
    [lv_opa, "border_opa"],
    [lv_blend_mode, "border_blend_mode"],
    [uint8_t_1, "border_post"],

    #/*Outline*/
    [lv_color, "outline_color"],
    [lv_style_int, "outline_width"],
    [lv_style_int, "outline_pad"],
    [lv_opa, "outline_opa"],
    [lv_blend_mode, "outline_blend_mode"],

    #/*Shadow*/
    [lv_color, "shadow_color"],
    [lv_style_int, "shadow_width"],
    [lv_style_int, "shadow_ofs_x"],
    [lv_style_int, "shadow_ofs_y"],
    [lv_style_int, "shadow_spread"],
    [lv_opa, "shadow_opa"],
    [lv_blend_mode, "shadow_blend_mode"],

    #/*Pattern*/
    [ptr, "pattern_image"],
    [ptr, "pattern_font"],
    [lv_color, "pattern_recolor"],
    [lv_opa, "pattern_opa"],
    [lv_opa, "pattern_recolor_opa"],
    [uint8_t_1, "pattern_repeat"],
    [lv_blend_mode, "pattern_blend_mode"],

    #/*Value*/
    [ptr, "value_str"],
    [ptr, "value_font"],
    [lv_opa, "value_opa"],
    [lv_color, "value_color"],
    [lv_style_int, "value_ofs_x"],
    [lv_style_int, "value_ofs_y"],
    [lv_style_int, "value_letter_space"],
    [lv_style_int, "value_line_space"],
    [lv_align, "value_align"],
    [lv_blend_mode, "value_blend_mode"],
]
lv_draw_rect_dsc = ctypes.structure(lv_draw_rect_dsc, "lv_draw_rect_dsc")

lv_draw_line_dsc = [
    [lv_color, "color"],
    [lv_style_int, "width"],
    [lv_style_int, "dash_width"],
    [lv_style_int, "dash_gap"],
    [lv_opa, "opa"],
    [uint8_t_2, "blend_mode"],
    [uint8_t_1, "round_start"],
    [uint8_t_1, "round_end"],
    [uint8_t_1, "raw_end"],
]
lv_draw_line_dsc = ctypes.structure(lv_draw_line_dsc, "lv_draw_line_dsc")

lv_draw_img_dsc = [
    [lv_opa, "opa"],
    [uint16_t, "angle"],
    [lv_point, "pivot"],
    [uint16_t, "zoom"],
    [lv_opa, "recolor_opa"],
    [lv_color, "recolor"],
    [lv_blend_mode, "blend_mode"],
    [uint8_t_1, "antialias"],
]
lv_draw_img_dsc = ctypes.structure(lv_draw_img_dsc, "lv_draw_img_dsc")

lv_draw_label_dsc = [
    [lv_color, "color"],
    [lv_color, "sel_color"],
    [lv_color, "sel_bg_color"],
    [lv_font, "font"],
    [lv_opa, "opa"],
    [lv_style_int, "line_space"],
    [lv_style_int, "letter_space"],
    [uint32_t, "sel_start"],
    [uint32_t, "sel_end"],
    [lv_coord, "ofs_x"],
    [lv_coord, "ofs_y"],
    [lv_bidi_dir, "bidi_dir"],
    [lv_txt_flag, "flag"],
    [lv_text_decor, "decor"],
    [lv_blend_mode, "blend_mode"],
]
lv_draw_label_dsc = ctypes.structure(lv_draw_label_dsc, "lv_draw_label_dsc")

#- --------- lv_mask --------- -#
lv_draw_mask_xcb = ptr    # callback
lv_draw_mask_type = ctypes.u8
lv_draw_mask_line_side = ctypes.u8

lv_draw_mask_common_dsc = [
    [lv_draw_mask_xcb, "cb"],
    [lv_draw_mask_type, "type"],
]
lv_draw_mask_common_dsc = ctypes.structure(lv_draw_mask_common_dsc, "lv_draw_mask_common_dsc")

lv_draw_mask_line_param_cfg = [
    #/*First point */
    [lv_point, "p1"],

    #/*Second point*/
    [lv_point, "p2"],

    #/*Which side to keep?*/
    [uint8_t_2, "side"],
]
lv_draw_mask_line_param_cfg = ctypes.structure(lv_draw_mask_line_param_cfg, "lv_draw_mask_line_param_cfg")

lv_draw_mask_line_param = [
    #/*The first element must be the common descriptor*/
    [lv_draw_mask_common_dsc, "dsc"],
    [lv_draw_mask_line_param_cfg, "cfg"],
    #/*A point of the line*/
    [lv_point, "origo"],
    #/* X / (1024*Y) steepness (X is 0..1023 range). What is the change of X in 1024 Y?*/
    [int32_t, "xy_steep"],
    #/* Y / (1024*X) steepness (Y is 0..1023 range). What is the change of Y in 1024 X?*/
    [int32_t, "yx_steep"],
    #/*Helper which stores yx_steep for flat lines and xy_steep for steep (non flat) lines */
    [int32_t, "steep"],
    #/*Steepness in 1 px in 0..255 range. Used only by flat lines. */
    [int32_t, "spx"],
    #/*1: It's a flat line? (Near to horizontal)*/
    [uint8_t_1, "flat"],
    #/* Invert the mask. The default is: Keep the left part.
    # * It is used to select left/right/top/bottom*/
    [uint8_t_1, "inv"],
]
lv_draw_mask_line_param = ctypes.structure(lv_draw_mask_line_param, "lv_draw_mask_line_param")

lv_draw_mask_angle_param_cfg = [
    [lv_point, "vertex_p"],
    [lv_coord, "start_angle"],
    [lv_coord, "end_angle"],
]
lv_draw_mask_angle_param_cfg = ctypes.structure(lv_draw_mask_angle_param_cfg, "lv_draw_mask_angle_param_cfg")

lv_draw_mask_angle_param = [
    #/*The first element must be the common descriptor*/
    [lv_draw_mask_common_dsc, "dsc"],
    [lv_draw_mask_angle_param_cfg, "cfg"],

    [lv_draw_mask_line_param, "start_line"],
    [lv_draw_mask_line_param, "end_line"],
    [uint16_t, "delta_deg"],
]
lv_draw_mask_angle_param = ctypes.structure(lv_draw_mask_angle_param, "lv_draw_mask_angle_param")


lv_draw_mask_radius_param_cfg = [
    [lv_area, "rect"],
    [lv_coord, "radius"],
    [uint8_t_1, "outer"],
]
lv_draw_mask_radius_param_cfg = ctypes.structure(lv_draw_mask_radius_param_cfg, "lv_draw_mask_radius_param_cfg")

lv_sqrt_res = [
    [uint16_t, "i"],
    [uint16_t, "f"],
]
lv_sqrt_res = ctypes.structure(lv_sqrt_res, "lv_sqrt_res")

lv_draw_mask_radius_param = [
    #/*The first element must be the common descriptor*/
    [lv_draw_mask_common_dsc, "dsc"],
    [lv_draw_mask_radius_param_cfg, "cfg"],
    [int32_t, "y_prev"],
    [lv_sqrt_res, "y_prev_x"],
]
lv_draw_mask_radius_param = ctypes.structure(lv_draw_mask_radius_param, "lv_draw_mask_radius_param")


lv_draw_mask_fade_param_cfg = [
    [lv_area, "coords"],
    [lv_coord, "y_top"],
    [lv_coord, "y_bottom"],
    [lv_opa, "opa_top"],
    [lv_opa, "opa_bottom"],
]
lv_draw_mask_fade_param_cfg = ctypes.structure(lv_draw_mask_fade_param_cfg, "lv_draw_mask_fade_param_cfg")

lv_draw_mask_fade_param = [
    # /*The first element must be the common descriptor*/
    [lv_draw_mask_common_dsc, "dsc"],
    [lv_draw_mask_fade_param_cfg, "cfg"],
]
lv_draw_mask_fade_param = ctypes.structure(lv_draw_mask_fade_param, "lv_draw_mask_fade_param")


lv_draw_mask_map_param_cfg = [
    [lv_area, "coords"],
    [ptr, "map"],
]
lv_draw_mask_map_param_cfg = ctypes.structure(lv_draw_mask_map_param_cfg, "lv_draw_mask_map_param_cfg")

lv_draw_mask_map_param = [
    #/*The first element must be the common descriptor*/
    [lv_draw_mask_common_dsc, "dsc"],
    [lv_draw_mask_map_param_cfg, "cfg"],
]
lv_draw_mask_map_param = ctypes.structure(lv_draw_mask_map_param, "lv_draw_mask_map_param")

lv_draw_mask_saved = [
    [ptr, "param"],
    [ptr, "custom_id"],
]
lv_draw_mask_saved = ctypes.structure(lv_draw_mask_saved, "lv_draw_mask_saved")

#
ctypes.print_classes()

# Ex:
# bb = ctypes.buffer(test_t, bytes("0101020203030404FFFFFEFEFCFC8080"))

# Ex:
# bb = ctypes.buffer(lv_draw_rect)

#- Ex

bb=ctypes.buffer(lv_draw_line_dsc)
bb.color
bb.blend_mode

bb.color = -1
- bytes('FFFF0000000000000003')

bb.blend_mode=3
- bytes('FFFF0000000000000003')

bb.raw_end = 1
- bytes('FFFF0000000000000013')

bb.blend_mode=0
- bytes('FFFF0000000000000010')

lv_draw_line_dsc = [
    [lv_color, "color"],
    [lv_style_int, "width"],
    [lv_style_int, "dash_width"],
    [lv_style_int, "dash_gap"],
    [lv_opa, "opa"],
    [uint8_t_2, "blend_mode"],
    [uint8_t_1, "round_start"],
    [uint8_t_1, "round_end"],
    [uint8_t_1, "raw_end"],
]

-#