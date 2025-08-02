/* Solidification of extensions_manager.h */
/********************************************************************\
* Generated code, don't edit                                         *
\********************************************************************/
#include "be_constobj.h"

/********************************************************************
** Solidified function: _anonymous_
********************************************************************/
be_local_closure(_anonymous_,   /* name */
  be_nested_proto(
    3,                          /* nstack */
    1,                          /* argc */
    0,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    ( &(const bvalue[ 1]) {     /* constants */
    /* K0   */  be_nested_str(Extensions_manager),
    }),
    &be_const_str__anonymous_,
    &be_const_str_solidified,
    ( &(const binstruction[ 3]) {  /* code */
      0x8C040100,  //  0000  GETMET	R1	R0	K0
      0x7C040200,  //  0001  CALL	R1	1
      0x80040200,  //  0002  RET	1	R1
    })
  )
);
/*******************************************************************/

extern const bclass be_class_Extensions_manager;
// compact class 'Extensions_manager' ktab size: 111, total: 171 (saved 480 bytes)
static const bvalue be_ktab_class_Extensions_manager[111] = {
  /* K0   */  be_nested_str(webserver),
  /* K1   */  be_nested_str(string),
  /* K2   */  be_nested_str(json),
  /* K3   */  be_nested_str(content_start),
  /* K4   */  be_nested_str(Extensions_X20Store),
  /* K5   */  be_nested_str(content_send_style),
  /* K6   */  be_nested_str(content_send),
  /* K7   */  be_nested_str_long(_X3Cscript_X3Efunction_X20toggleDesc_X28id_X29_X20_X7Bvar_X20desc_X20_X3D_X20document_X2EgetElementById_X28_X27desc_X2D_X27_X20_X2B_X20id_X29_X3Bvar_X20arrow_X20_X3D_X20document_X2EgetElementById_X28_X27arrow_X2D_X27_X20_X2B_X20id_X29_X3Bif_X20_X28desc_X2Estyle_X2Edisplay_X20_X3D_X3D_X3D_X20_X27none_X27_X20_X7C_X7C_X20desc_X2Estyle_X2Edisplay_X20_X3D_X3D_X3D_X20_X27_X27_X29_X20_X7Bdesc_X2Estyle_X2Edisplay_X20_X3D_X20_X27block_X27_X3Barrow_X2EinnerHTML_X20_X3D_X20_X27_XE2_X96_XBC_X27_X3B_X7D_X20else_X20_X7Bdesc_X2Estyle_X2Edisplay_X20_X3D_X20_X27none_X27_X3Barrow_X2EinnerHTML_X20_X3D_X20_X27_XE2_X96_XB6_X27_X3B_X7D_X7Dfunction_X20filterExtensions_X28query_X29_X20_X7Bvar_X20items_X20_X3D_X20document_X2EgetElementsByClassName_X28_X27ext_X2Dstore_X2Ditem_X27_X29_X3Bquery_X20_X3D_X20query_X2EtoLowerCase_X28_X29_X3Bfor_X20_X28var_X20i_X20_X3D_X200_X3B_X20i_X20_X3C_X20items_X2Elength_X3B_X20i_X2B_X2B_X29_X20_X7Bvar_X20name_X20_X3D_X20items_X5Bi_X5D_X2EgetElementsByClassName_X28_X27ext_X2Dname_X27_X29_X5B0_X5D_X2EtextContent_X2EtoLowerCase_X28_X29_X3Bvar_X20desc_X20_X3D_X20items_X5Bi_X5D_X2EgetElementsByClassName_X28_X27ext_X2Ddesc_X27_X29_X5B0_X5D_X2EtextContent_X2EtoLowerCase_X28_X29_X3Bif_X20_X28name_X2Eincludes_X28query_X29_X20_X7C_X7C_X20desc_X2Eincludes_X28query_X29_X29_X20_X7Bitems_X5Bi_X5D_X2Estyle_X2Edisplay_X20_X3D_X20_X27block_X27_X3B_X7D_X20else_X20_X7Bitems_X5Bi_X5D_X2Estyle_X2Edisplay_X20_X3D_X20_X27none_X27_X3B_X7D_X7D_X7D_X3C_X2Fscript_X3E),
  /* K8   */  be_nested_str_long(_X3Cstyle_X3E_X2Estore_X2Dheader_X7Bdisplay_X3Aflex_X3Bjustify_X2Dcontent_X3Aspace_X2Dbetween_X3Balign_X2Ditems_X3Acenter_X3Bmargin_X2Dbottom_X3A10px_X3B_X7D_X2Estore_X2Dstats_X7Bfont_X2Dsize_X3A0_X2E9em_X3Bcolor_X3Avar_X28_X2D_X2Dc_in_X29_X3B_X7D_X2Eext_X2Dstore_X2Ditem_X7Bbackground_X3Avar_X28_X2D_X2Dc_bg_X29_X3Bborder_X2Dradius_X3A0_X2E3em_X3Bmargin_X2Dbottom_X3A5px_X3Bpadding_X3A0_X200_X204px_X200_X3B_X7D_X2Eext_X2Dheader_X7Bdisplay_X3Aflex_X3Bjustify_X2Dcontent_X3Aspace_X2Dbetween_X3Balign_X2Ditems_X3Acenter_X3Bcursor_X3Apointer_X3Buser_X2Dselect_X3Anone_X3Bpadding_X3A0_X205px_X3B_X7D_X2Eext_X2Dtitle_X7Bdisplay_X3Aflex_X3Balign_X2Ditems_X3Acenter_X3Bgap_X3A6px_X3Bflex_X3A1_X3B_X7D_X2Eext_X2Dname_X7Bfont_X2Dweight_X3Abold_X3B_X7D_X2Eext_X2Dversion_X7Bfont_X2Dsize_X3A0_X2E8em_X3B_X7D_X2Eext_X2Darrow_X7Bcolor_X3Avar_X28_X2D_X2Dc_in_X29_X3Bfont_X2Dsize_X3A0_X2E8em_X3B_X7D_X2Eext_X2Dbadges_X7B_X7D_X2Eext_X2Ddetails_X7Bwidth_X3Amin_X2Dcontent_X3Bmin_X2Dwidth_X3A100_X25_X3Bpadding_X2Dleft_X3A0_X3Bpadding_X3A3px_X200_X3Bdisplay_X3Anone_X3Bmargin_X2Dtop_X3A3px_X3Bpadding_X2Dtop_X3A3px_X3Bborder_X2Dtop_X3A1px_X20solid_X20var_X28_X2D_X2Dc_frm_X29_X3B_X7D_X2Eext_X2Ddesc_X7Bcolor_X3Avar_X28_X2D_X2Dc_in_X29_X3Bfont_X2Dsize_X3A0_X2E8em_X3Bline_X2Dheight_X3A1_X2E4_X3Bdisplay_X3Ablock_X3Bword_X2Dwrap_X3Abreak_X2Dword_X3Boverflow_X2Dwrap_X3Abreak_X2Dword_X3Bwhite_X2Dspace_X3Anormal_X3B_X7D_X2Eext_X2Dactions_X7Bdisplay_X3Aflex_X3Bgap_X3A8px_X3Bpadding_X3A0_X205px_X3B_X7D_X2Ebtn_X2Daction_X7Bpadding_X3A0_X2012px_X3Bline_X2Dheight_X3A1_X2E8em_X3Bfont_X2Dsize_X3A0_X2E9em_X3Bflex_X3A1_X3B_X7D_X2Einstalled_X2Dbadge_X7Bbackground_X3Avar_X28_X2D_X2Dc_btnsv_X29_X3Bpadding_X3A2px_X206px_X3Bborder_X2Dradius_X3A3px_X3Bfont_X2Dsize_X3A0_X2E8em_X3B_X7D_X2Eupdate_X2Dbadge_X7Bbackground_X3Avar_X28_X2D_X2Dc_btnhvr_X29_X3Bpadding_X3A2px_X206px_X3Bborder_X2Dradius_X3A3px_X3Bfont_X2Dsize_X3A0_X2E8em_X3Banimation_X3Apulse_X202s_X20infinite_X3B_X7D_X40keyframes_X20pulse_X7B0_X25_X7Bopacity_X3A1_X3B_X7D50_X25_X7Bopacity_X3A0_X2E7_X3B_X7D100_X25_X7Bopacity_X3A1_X3B_X7D_X7D_X3C_X2Fstyle_X3E),
  /* K9   */  be_nested_str(_X3Cp_X3E_X3Csmall_X3E_X26nbsp_X3B_X28This_X20feature_X20requires_X20an_X20internet_X20connection_X29_X3C_X2Fsmall_X3E_X3C_X2Fp_X3E),
  /* K10  */  be_nested_str_long(_X3Cfieldset_X3E_X3Clegend_X3E_X3Cb_X3E_X26nbsp_X3BAvailable_X20Extensions_X26nbsp_X3B_X3C_X2Fb_X3E_X3C_X2Flegend_X3E_X3Cdiv_X20class_X3D_X27store_X2Dheader_X27_X3E_X3Cspan_X3EBrowse_X20Extensions_X3C_X2Fspan_X3E_X3Cspan_X20class_X3D_X27store_X2Dstats_X27_X3E24_X20available_X3C_X2Fspan_X3E_X3C_X2Fdiv_X3E_X3Cinput_X20type_X3D_X27text_X27_X20placeholder_X3D_X27Search_X20extensions_X2E_X2E_X2E_X27_X20onkeyup_X3D_X27filterExtensions_X28this_X2Evalue_X29_X27_X3E_X3Cp_X3E_X3C_X2Fp_X3E),
  /* K11  */  be_nested_str_long(_X7B_X22name_X22_X3A_X20_X22Leds_X20Panel_X22_X2C_X22version_X22_X3A_X20_X220x02010001_X22_X2C_X22description_X22_X3A_X20_X22Real_X2Dtime_X20display_X20of_X20WS2812_X20LEDs_X20in_X20browser_X20with_X20smooth_X20animations_X20and_X20pattern_X20editor_X2E_X22_X2C_X22author_X22_X3A_X20_X22Stephan_X20Hadinger_X22_X7D_X0A_X7B_X22name_X22_X3A_X20_X22Partition_X20Wizard_X22_X2C_X22version_X22_X3A_X20_X220x01020300_X22_X2C_X22description_X22_X3A_X20_X22Wizard_X20for_X20resizing_X20partitions_X20and_X20converting_X20to_X20safeboot_X20layout_X2E_X22_X2C_X22author_X22_X3A_X20_X22Stephan_X20Hadinger_X22_X7D_X0A_X7B_X22name_X22_X3A_X20_X22Energy_X20Monitor_X22_X2C_X22version_X22_X3A_X20_X220x03000100_X22_X2C_X22description_X22_X3A_X20_X22Real_X2Dtime_X20energy_X20consumption_X20monitoring_X20with_X20daily_X2Fmonthly_X20statistics_X2E_X20Supports_X20multiple_X20energy_X20meters_X20and_X20cost_X20calculation_X2E_X5CnIncludes_X20export_X20to_X20CSV_X20and_X20graphical_X20consumption_X20trends_X2E_X22_X2C_X22author_X22_X3A_X20_X22Stephan_X20Hadinger_X22_X7D),
  /* K12  */  be_const_int(1),
  /* K13  */  be_const_int(0),
  /* K14  */  be_nested_str(find),
  /* K15  */  be_nested_str(_X0A),
  /* K16  */  be_nested_str(load),
  /* K17  */  be_nested_str(log),
  /* K18  */  be_nested_str(EXT_X3A_X20json_line_X3D_X25s_X20item_X3D_X25s),
  /* K19  */  be_const_int(3),
  /* K20  */  be_nested_str_long(_X3Cdiv_X20class_X3D_X27ext_X2Dstore_X2Ditem_X27_X3E_X3Cdiv_X20class_X3D_X27ext_X2Dheader_X27_X20onclick_X3D_X27toggleDesc_X28_X22_X25s_X22_X29_X27_X3E_X3Cdiv_X20class_X3D_X27ext_X2Dtitle_X27_X3E_X3Cspan_X20class_X3D_X27ext_X2Dname_X27_X3E_X25s_X3C_X2Fspan_X3E_X3Cspan_X20class_X3D_X27ext_X2Dversion_X27_X3E_X3Csmall_X3E_X25s_X3C_X2Fsmall_X3E_X3C_X2Fspan_X3E_X3C_X2Fdiv_X3E_X3Cdiv_X20class_X3D_X27ext_X2Dbadges_X27_X3E_X3Cspan_X20class_X3D_X27update_X2Dbadge_X27_X3EUpgrade_X3C_X2Fspan_X3E_X3C_X2Fdiv_X3E_X3Cspan_X20id_X3D_X27arrow_X2D_X25s_X27_X20class_X3D_X27ext_X2Darrow_X27_X3E_XE2_X96_XB6_X3C_X2Fspan_X3E_X3C_X2Fdiv_X3E_X3Cdiv_X20id_X3D_X27desc_X2D_X25s_X27_X20class_X3D_X27ext_X2Ddetails_X27_X3E_X3Cdiv_X20class_X3D_X27ext_X2Ddesc_X27_X3E_X25s_X3Cbr_X3Ev1_X2E8_X2E0_X20_XE2_X86_X92_X20_X25s_X3C_X2Fdiv_X3E_X3Cform_X20action_X3D_X27_X2Fstore_X27_X20method_X3D_X27post_X27_X20class_X3D_X27ext_X2Dactions_X27_X3E_X3Cdiv_X20style_X3D_X27width_X3A30_X25_X25_X27_X3E_X3C_X2Fdiv_X3E_X3Cbutton_X20type_X3D_X27submit_X27_X20class_X3D_X27btn_X2Daction_X27_X20name_X3D_X27u_X2FLeds_Panel_X2Etapp_X27_X20onclick_X3D_X27return_X20confirmAction_X28_X27update_X27_X2C_X20_X27Leds_X20Panel_X27_X29_X27_X3EUpgrade_X3C_X2Fbutton_X3E_X3Cbutton_X20type_X3D_X27submit_X27_X20class_X3D_X27btn_X2Daction_X20bred_X27_X20name_X3D_X27d_X2FLeds_Panel_X2Etapp_X27_X20onclick_X3D_X27return_X20confirmAction_X28_X27delete_X27_X2C_X20_X27Leds_X20Panel_X27_X29_X27_X3EDelete_X3C_X2Fbutton_X3E_X3C_X2Fform_X3E_X3C_X2Fdiv_X3E_X3C_X2Fdiv_X3E),
  /* K21  */  be_nested_str(html_escape),
  /* K22  */  be_nested_str(name),
  /* K23  */  be_nested_str(version_string),
  /* K24  */  be_nested_str(version),
  /* K25  */  be_nested_str(replace),
  /* K26  */  be_nested_str(description),
  /* K27  */  be_nested_str(_X3Cbr_X3E),
  /* K28  */  be_nested_str(_X7B_X22name_X22_X3A_X20_X22Leds_X20Panel_X22_X2C_X22version_X22_X3A_X20_X220x02010001_X22_X2C_X22description_X22_X3A_X20_X22Real_X2Dtime_X20display_X20of_X20WS2812_X20LEDs_X20in_X20browser_X20with_X20smooth_X20animations_X20and_X20pattern_X20editor_X2E_X22_X2C_X22author_X22_X3A_X20_X22Stephan_X20Hadinger_X22_X2C_X22min_tasmota_X22_X3A_X20_X220x0E060001_X22_X2C_X22features_X22_X3A_X20_X22_X22_X7D),
  /* K29  */  be_const_int(2),
  /* K30  */  be_nested_str(_X7B_X22name_X22_X3A_X20_X22Partition_X20Wizard_X22_X2C_X22version_X22_X3A_X20_X220x01020300_X22_X2C_X22description_X22_X3A_X20_X22Wizard_X20for_X20resizing_X20partitions_X20and_X20converting_X20to_X20safeboot_X20layout_X2E_X22_X2C_X22author_X22_X3A_X20_X22Stephan_X20Hadinger_X22_X2C_X22min_tasmota_X22_X3A_X20_X220x0E060001_X22_X2C_X22features_X22_X3A_X20_X22_X22_X7D),
  /* K31  */  be_nested_str_long(_X3Cdiv_X20class_X3D_X27ext_X2Dstore_X2Ditem_X27_X3E_X3Cdiv_X20class_X3D_X27ext_X2Dheader_X27_X20onclick_X3D_X27toggleDesc_X28_X22_X25s_X22_X29_X27_X3E_X3Cdiv_X20class_X3D_X27ext_X2Dtitle_X27_X3E_X3Cspan_X20class_X3D_X27ext_X2Dname_X27_X3E_X25s_X3C_X2Fspan_X3E_X3Cspan_X20class_X3D_X27ext_X2Dversion_X27_X3E_X3Csmall_X3E_X25s_X3C_X2Fsmall_X3E_X3C_X2Fspan_X3E_X3C_X2Fdiv_X3E_X3Cdiv_X20class_X3D_X27ext_X2Dbadges_X27_X3E_X3Cspan_X20class_X3D_X27installed_X2Dbadge_X27_X3EInstalled_X3C_X2Fspan_X3E_X3C_X2Fdiv_X3E_X3Cspan_X20id_X3D_X27arrow_X2D_X25s_X27_X20class_X3D_X27ext_X2Darrow_X27_X3E_XE2_X96_XB6_X3C_X2Fspan_X3E_X3C_X2Fdiv_X3E_X3Cdiv_X20id_X3D_X27desc_X2D_X25s_X27_X20class_X3D_X27ext_X2Ddetails_X27_X3E_X3Cdiv_X20class_X3D_X27ext_X2Ddesc_X27_X3E_X25s_X3C_X2Fdiv_X3E_X3Cform_X20action_X3D_X27_X2Fstore_X27_X20method_X3D_X27post_X27_X20class_X3D_X27ext_X2Dactions_X27_X3E_X3Cdiv_X20style_X3D_X27width_X3A30_X25_X25_X27_X3E_X3C_X2Fdiv_X3E_X3Cbutton_X20type_X3D_X27submit_X27_X20class_X3D_X27btn_X2Daction_X20bred_X27_X20name_X3D_X27d_X2FLeds_Panel_X2Etapp_X27_X20onclick_X3D_X27return_X20confirmAction_X28_X27delete_X27_X2C_X20_X27Leds_X20Panel_X27_X29_X27_X3EDelete_X3C_X2Fbutton_X3E_X3C_X2Fform_X3E_X3C_X2Fdiv_X3E_X3C_X2Fdiv_X3E),
  /* K32  */  be_nested_str_long(_X3Cdiv_X20class_X3D_X27ext_X2Dstore_X2Ditem_X27_X3E_X3Cdiv_X20class_X3D_X27ext_X2Dheader_X27_X20onclick_X3D_X27toggleDesc_X28_X223_X22_X29_X27_X3E_X3Cdiv_X20class_X3D_X27ext_X2Dtitle_X27_X3E_X3Cspan_X20class_X3D_X27ext_X2Dname_X27_X3EEnergy_X20Monitor_X3C_X2Fspan_X3E_X3Cspan_X20class_X3D_X27ext_X2Dversion_X27_X3Ev3_X2E0_X2E1_X3C_X2Fspan_X3E_X3C_X2Fdiv_X3E_X3Cspan_X20id_X3D_X27arrow_X2D3_X27_X20class_X3D_X27ext_X2Darrow_X27_X3E_XE2_X96_XB6_X3C_X2Fspan_X3E_X3C_X2Fdiv_X3E_X3Cdiv_X20id_X3D_X27desc_X2D3_X27_X20class_X3D_X27ext_X2Ddetails_X27_X3E_X3Cdiv_X20class_X3D_X27ext_X2Ddesc_X27_X3EReal_X2Dtime_X20energy_X20consumption_X20monitoring_X20with_X20daily_X2Fmonthly_X20statistics_X2E_X20Supports_X20multiple_X20energy_X20meters_X20and_X20cost_X20calculation_X2E_X3Cbr_X3EIncludes_X20export_X20to_X20CSV_X20and_X20graphical_X20consumption_X20trends_X2E_X3C_X2Fdiv_X3E_X3Cform_X20action_X3D_X27_X2Fstore_X27_X20method_X3D_X27post_X27_X20class_X3D_X27ext_X2Dactions_X27_X3E_X3Cdiv_X20style_X3D_X27width_X3A30_X25_X27_X3E_X3C_X2Fdiv_X3E_X3Cbutton_X20type_X3D_X27submit_X27_X20class_X3D_X27btn_X2Daction_X20bgrn_X27_X20name_X3D_X27i_X2FEnergy_Monitor_X2Etapp_X27_X3EInstall_X3C_X2Fbutton_X3E_X3C_X2Fform_X3E_X3C_X2Fdiv_X3E_X3C_X2Fdiv_X3E),
  /* K33  */  be_nested_str(_X3Cp_X3E_X3C_X2Fp_X3E_X3C_X2Ffieldset_X3E_X3Cp_X3E_X3C_X2Fp_X3E),
  /* K34  */  be_nested_str(_X3Cdiv_X20style_X3D_X27display_X3A_X20block_X3B_X27_X3E_X3C_X2Fdiv_X3E_X3Cp_X3E_X3C_X2Fp_X3E_X3Cform_X20style_X3D_X27display_X3A_X20block_X3B_X27_X20action_X3D_X27ext_X27_X20method_X3D_X27get_X27_X3E_X3Cbutton_X20name_X3D_X27_X27_X3EExtensions_X3C_X2Fbutton_X3E_X3C_X2Fform_X3E),
  /* K35  */  be_nested_str(content_stop),
  /* K36  */  be_nested_str(tasmota),
  /* K37  */  be_nested_str(add_driver),
  /* K38  */  be_const_class(be_class_Extensions_manager),
  /* K39  */  be_nested_str(v_X25s_X2E_X25s_X2E_X25s_X2E_X25s),
  /* K40  */  be_nested_str(_X3Cform_X20id_X3Dbut_part_mgr_X20style_X3D_X27display_X3A_X20block_X3B_X27_X20action_X3D_X27ext_X27_X20method_X3D_X27get_X27_X3E_X3Cbutton_X3EExtensions_X3C_X2Fbutton_X3E_X3C_X2Fform_X3E_X3Cp_X3E_X3C_X2Fp_X3E),
  /* K41  */  be_nested_str(on),
  /* K42  */  be_nested_str(_X2Fext),
  /* K43  */  be_nested_str(HTTP_GET),
  /* K44  */  be_nested_str(HTTP_POST),
  /* K45  */  be_nested_str(check_privileged_access),
  /* K46  */  be_nested_str(has_arg),
  /* K47  */  be_nested_str(store),
  /* K48  */  be_nested_str(page_extensions_store),
  /* K49  */  be_nested_str(page_extensions_mgr),
  /* K50  */  be_nested_str(path),
  /* K51  */  be_nested_str(listdir),
  /* K52  */  be_nested_str(EXT_FOLDER),
  /* K53  */  be_nested_str(endswith),
  /* K54  */  be_nested_str(_X2Etapp),
  /* K55  */  be_nested_str(_X2E_tapp),
  /* K56  */  be_nested_str(push),
  /* K57  */  be_nested_str(stop_iteration),
  /* K58  */  be_nested_str(_ext),
  /* K59  */  be_nested_str(keys),
  /* K60  */  be_nested_str(arg_name),
  /* K61  */  be_const_int(2147483647),
  /* K62  */  be_nested_str(r),
  /* K63  */  be_nested_str(),
  /* K64  */  be_nested_str(s),
  /* K65  */  be_nested_str(unload_extension),
  /* K66  */  be_nested_str(a),
  /* K67  */  be_nested_str(A),
  /* K68  */  be_nested_str(_tapp),
  /* K69  */  be_nested_str(tapp),
  /* K70  */  be_nested_str(rename),
  /* K71  */  be_nested_str(EXT_X3A_X20rename_X20_X27_X25s_X27_X20to_X20_X27_X25s_X20success_X3D_X25s),
  /* K72  */  be_nested_str(contains),
  /* K73  */  be_nested_str(remove),
  /* K74  */  be_nested_str(EXT_X3A_X20wrong_X20action_X20_X27_X25s_X27),
  /* K75  */  be_nested_str(d),
  /* K76  */  be_nested_str(EXT_X3A_X20delete_X20_X27_X25s_X27_X20success_X3D_X25s),
  /* K77  */  be_nested_str(redirect),
  /* K78  */  be_nested_str(CFG_X3A_X20Exception_X3E_X20_X27_X25s_X27_X20_X2D_X20_X25s),
  /* K79  */  be_nested_str(Parameter_X20error),
  /* K80  */  be_nested_str(_X3Cp_X20style_X3D_X27width_X3A340px_X3B_X27_X3E_X3Cb_X3EException_X3A_X3C_X2Fb_X3E_X3Cbr_X3E_X27_X25s_X27_X3Cbr_X3E_X25s_X3C_X2Fp_X3E),
  /* K81  */  be_nested_str(content_button),
  /* K82  */  be_nested_str(BUTTON_CONFIGURATION),
  /* K83  */  be_nested_str(Extensions_X20Manager),
  /* K84  */  be_nested_str_long(_X3Cfieldset_X3E_X3Cstyle_X3E_X2Eext_X2Ditem_X7Bwidth_X3Amin_X2Dcontent_X3Bmin_X2Dwidth_X3A100_X25_X3B_X7D_X2Eext_X2Ditem_X20small_X7Bdisplay_X3Ablock_X3Bword_X2Dwrap_X3Abreak_X2Dword_X3Boverflow_X2Dwrap_X3Abreak_X2Dword_X3Bwhite_X2Dspace_X3Anormal_X3Bpadding_X2Dright_X3A5px_X3Bpadding_X2Dtop_X3A0px_X3B_X7D_X2Eext_X2Dcontrols_X7Bdisplay_X3Aflex_X3Bgap_X3A8px_X3Balign_X2Ditems_X3Acenter_X3Bmargin_X2Dtop_X3A8px_X3Bpadding_X3A0px_X7D_X2Ebtn_X2Dsmall_X7Bpadding_X3A0_X206px_X3Bline_X2Dheight_X3A1_X2E8rem_X3Bfont_X2Dsize_X3A0_X2E9rem_X3Bmin_X2Dwidth_X3Aauto_X3Bwidth_X3Aauto_X3Bflex_X2Dshrink_X3A0_X3B_X7Dform_X7Bpadding_X2Dtop_X3A0px_X3Bpadding_X2Dbottom_X3A0px_X3B_X7D_X2Erunning_X2Dindicator_X7Bdisplay_X3Ainline_X2Dblock_X3Bwidth_X3A8px_X3Bheight_X3A8px_X3Bborder_X2Dradius_X3A50_X25_X3Bmargin_X2Dright_X3A8px_X3Bbackground_X3Avar_X28_X2D_X2Dc_btn_X29_X3Banimation_X3Apulse_X201_X2E5s_X20infinite_X3B_X7D_X40keyframes_X20pulse_X7B0_X25_X7Bopacity_X3A1_X3B_X7D50_X25_X7Bopacity_X3A0_X2E5_X3B_X7D100_X25_X7Bopacity_X3A1_X3B_X7D_X7D_X3C_X2Fstyle_X3E_X3Clegend_X3E_X3Cb_X20title_X3D_X27Running_X20extensions_X27_X3E_X26nbsp_X3BInstalled_X20extensions_X3C_X2Fb_X3E_X3C_X2Flegend_X3E),
  /* K85  */  be_nested_str(list_extensions_in_fs),
  /* K86  */  be_nested_str(_X3Chr_X3E),
  /* K87  */  be_nested_str(get_by_index),
  /* K88  */  be_nested_str(read_extension_manifest),
  /* K89  */  be_nested_str(_X20_X3Cspan_X20class_X3D_X27running_X2Dindicator_X27_X20title_X3D_X27Running_X27_X3E_X3C_X2Fspan_X3E),
  /* K90  */  be_nested_str(autorun),
  /* K91  */  be_nested_str(style_X3D_X27background_X3Avar_X28_X2D_X2Dc_btnoff_X29_X3B_X27),
  /* K92  */  be_nested_str(_X3Cdiv_X20class_X3D_X27ext_X2Ditem_X27_X3E),
  /* K93  */  be_nested_str(_X3Cspan_X20title_X3D_X27path_X3A_X20_X25s_X27_X3E_X3Cb_X3E_X25s_X3C_X2Fb_X3E_X25s_X3C_X2Fspan_X3E_X3Cbr_X3E),
  /* K94  */  be_nested_str(_X3Csmall_X3E_X25s_X3C_X2Fsmall_X3E),
  /* K95  */  be_nested_str(_X3Cdiv_X20class_X3D_X27ext_X2Dcontrols_X27_X20style_X3D_X27padding_X2Dtop_X3A0px_X3Bpadding_X2Dbottom_X3A0px_X3B_X27_X3E),
  /* K96  */  be_nested_str(_X3Cform_X20action_X3D_X27_X2Fext_X27_X20method_X3D_X27post_X27_X20class_X3D_X27ext_X2Dcontrols_X27_X3E),
  /* K97  */  be_nested_str(_X3Cbutton_X20type_X3D_X27submit_X27_X20class_X3D_X27btn_X2Dsmall_X27_X20_X25s_X20name_X3D_X27_X25s_X25s_X27_X3E_X25s_X3C_X2Fbutton_X3E),
  /* K98  */  be_nested_str(Running),
  /* K99  */  be_nested_str(Stopped),
  /* K100 */  be_nested_str(_X3Cbutton_X20type_X3D_X27submit_X27_X20class_X3D_X27btn_X2Dsmall_X27_X20_X25s_X20name_X3D_X27_X25s_X25s_X27_X3EAuto_X2Drun_X3A_X20_X25s_X3C_X2Fbutton_X3E),
  /* K101 */  be_nested_str(ON),
  /* K102 */  be_nested_str(OFF),
  /* K103 */  be_nested_str(_X3Cbutton_X20type_X3D_X27submit_X27_X20class_X3D_X27btn_X2Dsmall_X27_X20style_X3D_X27background_X2Dcolor_X3Avar_X28_X2D_X2Dc_btnoff_X29_X3Bborder_X2Dcolor_X3Avar_X28_X2D_X2Dc_btnrst_X29_X3Bborder_X2Dwidth_X3A3px_X3Bborder_X2Dstyle_X3Asolid_X3B_X27_X20name_X3D_X27d_X25s_X27_X20onclick_X3D_X27return_X20confirm_X28_X22Confirm_X20deletion_X20of_X20_X25s_X22_X29_X27_X3EUninstall_X3C_X2Fbutton_X3E),
  /* K104 */  be_nested_str(_X3C_X2Fform_X3E_X3C_X2Fdiv_X3E_X3C_X2Fdiv_X3E),
  /* K105 */  be_nested_str(_X3Cdiv_X3E_X3Csmall_X3E_X3Ci_X3ENo_X20installed_X20extension_X2E_X3C_X2Fi_X3E_X3C_X2Fsmall_X3E_X3C_X2Fp_X3E),
  /* K106 */  be_nested_str(_X3Cdiv_X20style_X3D_X27display_X3A_X20block_X3B_X27_X3E_X3C_X2Fdiv_X3E_X3Cp_X3E_X3C_X2Fp_X3E_X3Cform_X20style_X3D_X27display_X3A_X20block_X3B_X27_X20action_X3D_X27ext_X27_X20method_X3D_X27get_X27_X3E_X3Cbutton_X20name_X3D_X27store_X27_X3EExtension_X20Store_X3C_X2Fbutton_X3E_X3C_X2Fform_X3E),
  /* K107 */  be_nested_str(BUTTON_MANAGEMENT),
  /* K108 */  be_nested_str(sortedmap),
  /* K109 */  be_nested_str(list_extensions),
  /* K110 */  be_nested_str(EXT_X3A_X20unable_X20to_X20read_X20details_X20from_X20_X27_X25s_X27),
};


extern const bclass be_class_Extensions_manager;

/********************************************************************
** Solidified function: page_extensions_store
********************************************************************/
be_local_closure(class_Extensions_manager_page_extensions_store,   /* name */
  be_nested_proto(
    24,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_page_extensions_store,
    &be_const_str_solidified,
    ( &(const binstruction[152]) {  /* code */
      0xA4060000,  //  0000  IMPORT	R1	K0
      0xA40A0200,  //  0001  IMPORT	R2	K1
      0xA40E0400,  //  0002  IMPORT	R3	K2
      0x8C100303,  //  0003  GETMET	R4	R1	K3
      0x58180004,  //  0004  LDCONST	R6	K4
      0x7C100400,  //  0005  CALL	R4	2
      0x8C100305,  //  0006  GETMET	R4	R1	K5
      0x7C100200,  //  0007  CALL	R4	1
      0x8C100306,  //  0008  GETMET	R4	R1	K6
      0x58180007,  //  0009  LDCONST	R6	K7
      0x7C100400,  //  000A  CALL	R4	2
      0x8C100306,  //  000B  GETMET	R4	R1	K6
      0x58180008,  //  000C  LDCONST	R6	K8
      0x7C100400,  //  000D  CALL	R4	2
      0x8C100306,  //  000E  GETMET	R4	R1	K6
      0x58180009,  //  000F  LDCONST	R6	K9
      0x7C100400,  //  0010  CALL	R4	2
      0x8C100306,  //  0011  GETMET	R4	R1	K6
      0x5818000A,  //  0012  LDCONST	R6	K10
      0x7C100400,  //  0013  CALL	R4	2
      0x5810000B,  //  0014  LDCONST	R4	K11
      0x5814000C,  //  0015  LDCONST	R5	K12
      0x5818000D,  //  0016  LDCONST	R6	K13
      0x601C000C,  //  0017  GETGBL	R7	G12
      0x5C200800,  //  0018  MOVE	R8	R4
      0x7C1C0200,  //  0019  CALL	R7	1
      0x141C0C07,  //  001A  LT	R7	R6	R7
      0x781E003A,  //  001B  JMPF	R7	#0057
      0x8C1C050E,  //  001C  GETMET	R7	R2	K14
      0x5C240800,  //  001D  MOVE	R9	R4
      0x5828000F,  //  001E  LDCONST	R10	K15
      0x5C2C0C00,  //  001F  MOVE	R11	R6
      0x7C1C0800,  //  0020  CALL	R7	4
      0x14200F0D,  //  0021  LT	R8	R7	K13
      0x78220003,  //  0022  JMPF	R8	#0027
      0x6020000C,  //  0023  GETGBL	R8	G12
      0x5C240800,  //  0024  MOVE	R9	R4
      0x7C200200,  //  0025  CALL	R8	1
      0x5C1C1000,  //  0026  MOVE	R7	R8
      0x40200C07,  //  0027  CONNECT	R8	R6	R7
      0x94200808,  //  0028  GETIDX	R8	R4	R8
      0x8C240710,  //  0029  GETMET	R9	R3	K16
      0x5C2C1000,  //  002A  MOVE	R11	R8
      0x7C240400,  //  002B  CALL	R9	2
      0xB82A2200,  //  002C  GETNGBL	R10	K17
      0x602C0018,  //  002D  GETGBL	R11	G24
      0x58300012,  //  002E  LDCONST	R12	K18
      0x5C341000,  //  002F  MOVE	R13	R8
      0x5C381200,  //  0030  MOVE	R14	R9
      0x7C2C0600,  //  0031  CALL	R11	3
      0x58300013,  //  0032  LDCONST	R12	K19
      0x7C280400,  //  0033  CALL	R10	2
      0x4C280000,  //  0034  LDNIL	R10
      0x2028120A,  //  0035  NE	R10	R9	R10
      0x782A001C,  //  0036  JMPF	R10	#0054
      0x8C280306,  //  0037  GETMET	R10	R1	K6
      0x60300018,  //  0038  GETGBL	R12	G24
      0x58340014,  //  0039  LDCONST	R13	K20
      0x5C380A00,  //  003A  MOVE	R14	R5
      0x8C3C0315,  //  003B  GETMET	R15	R1	K21
      0x94441316,  //  003C  GETIDX	R17	R9	K22
      0x7C3C0400,  //  003D  CALL	R15	2
      0x8C400117,  //  003E  GETMET	R16	R0	K23
      0x60480009,  //  003F  GETGBL	R18	G9
      0x944C1318,  //  0040  GETIDX	R19	R9	K24
      0x7C480200,  //  0041  CALL	R18	1
      0x7C400400,  //  0042  CALL	R16	2
      0x5C440A00,  //  0043  MOVE	R17	R5
      0x5C480A00,  //  0044  MOVE	R18	R5
      0x8C4C0519,  //  0045  GETMET	R19	R2	K25
      0x8C540315,  //  0046  GETMET	R21	R1	K21
      0x945C131A,  //  0047  GETIDX	R23	R9	K26
      0x7C540400,  //  0048  CALL	R21	2
      0x5858000F,  //  0049  LDCONST	R22	K15
      0x585C001B,  //  004A  LDCONST	R23	K27
      0x7C4C0800,  //  004B  CALL	R19	4
      0x8C500117,  //  004C  GETMET	R20	R0	K23
      0x60580009,  //  004D  GETGBL	R22	G9
      0x945C1318,  //  004E  GETIDX	R23	R9	K24
      0x7C580200,  //  004F  CALL	R22	1
      0x7C500400,  //  0050  CALL	R20	2
      0x7C301000,  //  0051  CALL	R12	8
      0x7C280400,  //  0052  CALL	R10	2
      0x00140B0C,  //  0053  ADD	R5	R5	K12
      0x00280F0C,  //  0054  ADD	R10	R7	K12
      0x5C181400,  //  0055  MOVE	R6	R10
      0x7001FFBF,  //  0056  JMP		#0017
      0x581C001C,  //  0057  LDCONST	R7	K28
      0x8C200710,  //  0058  GETMET	R8	R3	K16
      0x5C280E00,  //  0059  MOVE	R10	R7
      0x7C200400,  //  005A  CALL	R8	2
      0x8C240306,  //  005B  GETMET	R9	R1	K6
      0x602C0018,  //  005C  GETGBL	R11	G24
      0x58300014,  //  005D  LDCONST	R12	K20
      0x5C340A00,  //  005E  MOVE	R13	R5
      0x8C380315,  //  005F  GETMET	R14	R1	K21
      0x94401116,  //  0060  GETIDX	R16	R8	K22
      0x7C380400,  //  0061  CALL	R14	2
      0x8C3C0117,  //  0062  GETMET	R15	R0	K23
      0x60440009,  //  0063  GETGBL	R17	G9
      0x94481118,  //  0064  GETIDX	R18	R8	K24
      0x7C440200,  //  0065  CALL	R17	1
      0x7C3C0400,  //  0066  CALL	R15	2
      0x5C400A00,  //  0067  MOVE	R16	R5
      0x5C440A00,  //  0068  MOVE	R17	R5
      0x8C480315,  //  0069  GETMET	R18	R1	K21
      0x9450111A,  //  006A  GETIDX	R20	R8	K26
      0x7C480400,  //  006B  CALL	R18	2
      0x8C4C0117,  //  006C  GETMET	R19	R0	K23
      0x60540009,  //  006D  GETGBL	R21	G9
      0x94581118,  //  006E  GETIDX	R22	R8	K24
      0x7C540200,  //  006F  CALL	R21	1
      0x7C4C0400,  //  0070  CALL	R19	2
      0x7C2C1000,  //  0071  CALL	R11	8
      0x7C240400,  //  0072  CALL	R9	2
      0x5814001D,  //  0073  LDCONST	R5	K29
      0x581C001E,  //  0074  LDCONST	R7	K30
      0x8C240710,  //  0075  GETMET	R9	R3	K16
      0x5C2C0E00,  //  0076  MOVE	R11	R7
      0x7C240400,  //  0077  CALL	R9	2
      0x5C201200,  //  0078  MOVE	R8	R9
      0x8C240306,  //  0079  GETMET	R9	R1	K6
      0x602C0018,  //  007A  GETGBL	R11	G24
      0x5830001F,  //  007B  LDCONST	R12	K31
      0x5C340A00,  //  007C  MOVE	R13	R5
      0x8C380315,  //  007D  GETMET	R14	R1	K21
      0x94401116,  //  007E  GETIDX	R16	R8	K22
      0x7C380400,  //  007F  CALL	R14	2
      0x8C3C0117,  //  0080  GETMET	R15	R0	K23
      0x60440009,  //  0081  GETGBL	R17	G9
      0x94481118,  //  0082  GETIDX	R18	R8	K24
      0x7C440200,  //  0083  CALL	R17	1
      0x7C3C0400,  //  0084  CALL	R15	2
      0x5C400A00,  //  0085  MOVE	R16	R5
      0x5C440A00,  //  0086  MOVE	R17	R5
      0x8C480315,  //  0087  GETMET	R18	R1	K21
      0x9450111A,  //  0088  GETIDX	R20	R8	K26
      0x7C480400,  //  0089  CALL	R18	2
      0x7C2C0E00,  //  008A  CALL	R11	7
      0x7C240400,  //  008B  CALL	R9	2
      0x8C240306,  //  008C  GETMET	R9	R1	K6
      0x582C0020,  //  008D  LDCONST	R11	K32
      0x7C240400,  //  008E  CALL	R9	2
      0x8C240306,  //  008F  GETMET	R9	R1	K6
      0x582C0021,  //  0090  LDCONST	R11	K33
      0x7C240400,  //  0091  CALL	R9	2
      0x8C240306,  //  0092  GETMET	R9	R1	K6
      0x582C0022,  //  0093  LDCONST	R11	K34
      0x7C240400,  //  0094  CALL	R9	2
      0x8C240323,  //  0095  GETMET	R9	R1	K35
      0x7C240200,  //  0096  CALL	R9	1
      0x80000000,  //  0097  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: init
********************************************************************/
be_local_closure(class_Extensions_manager_init,   /* name */
  be_nested_proto(
    4,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_init,
    &be_const_str_solidified,
    ( &(const binstruction[ 5]) {  /* code */
      0xB8064800,  //  0000  GETNGBL	R1	K36
      0x8C040325,  //  0001  GETMET	R1	R1	K37
      0x5C0C0000,  //  0002  MOVE	R3	R0
      0x7C040400,  //  0003  CALL	R1	2
      0x80000000,  //  0004  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: version_string
********************************************************************/
be_local_closure(class_Extensions_manager_version_string,   /* name */
  be_nested_proto(
    8,                          /* nstack */
    1,                          /* argc */
    12,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_version_string,
    &be_const_str_solidified,
    ( &(const binstruction[19]) {  /* code */
      0x58040026,  //  0000  LDCONST	R1	K38
      0x60080018,  //  0001  GETGBL	R2	G24
      0x580C0027,  //  0002  LDCONST	R3	K39
      0x54120017,  //  0003  LDINT	R4	24
      0x3C100004,  //  0004  SHR	R4	R0	R4
      0x541600FE,  //  0005  LDINT	R5	255
      0x2C100805,  //  0006  AND	R4	R4	R5
      0x5416000F,  //  0007  LDINT	R5	16
      0x3C140005,  //  0008  SHR	R5	R0	R5
      0x541A00FE,  //  0009  LDINT	R6	255
      0x2C140A06,  //  000A  AND	R5	R5	R6
      0x541A0007,  //  000B  LDINT	R6	8
      0x3C180006,  //  000C  SHR	R6	R0	R6
      0x541E00FE,  //  000D  LDINT	R7	255
      0x2C180C07,  //  000E  AND	R6	R6	R7
      0x541E00FE,  //  000F  LDINT	R7	255
      0x2C1C0007,  //  0010  AND	R7	R0	R7
      0x7C080A00,  //  0011  CALL	R2	5
      0x80040400,  //  0012  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: web_add_button
********************************************************************/
be_local_closure(class_Extensions_manager_web_add_button,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_web_add_button,
    &be_const_str_solidified,
    ( &(const binstruction[ 5]) {  /* code */
      0xA4060000,  //  0000  IMPORT	R1	K0
      0x8C080306,  //  0001  GETMET	R2	R1	K6
      0x58100028,  //  0002  LDCONST	R4	K40
      0x7C080400,  //  0003  CALL	R2	2
      0x80000000,  //  0004  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: web_add_handler
********************************************************************/
be_local_closure(class_Extensions_manager_web_add_handler,   /* name */
  be_nested_proto(
    7,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    1,                          /* has sup protos */
    ( &(const struct bproto*[ 2]) {
      be_nested_proto(
        2,                          /* nstack */
        0,                          /* argc */
        0,                          /* varg */
        1,                          /* has upvals */
        ( &(const bupvaldesc[ 1]) {  /* upvals */
          be_local_const_upval(1, 0),
        }),
        0,                          /* has sup protos */
        NULL,                       /* no sub protos */
        1,                          /* has constants */
        ( &(const bvalue[ 1]) {     /* constants */
        /* K0   */  be_nested_str(page_extensions_mgr_dispatcher),
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
      be_nested_proto(
        2,                          /* nstack */
        0,                          /* argc */
        0,                          /* varg */
        1,                          /* has upvals */
        ( &(const bupvaldesc[ 1]) {  /* upvals */
          be_local_const_upval(1, 0),
        }),
        0,                          /* has sup protos */
        NULL,                       /* no sub protos */
        1,                          /* has constants */
        ( &(const bvalue[ 1]) {     /* constants */
        /* K0   */  be_nested_str(page_extensions_ctl),
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
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_web_add_handler,
    &be_const_str_solidified,
    ( &(const binstruction[13]) {  /* code */
      0xA4060000,  //  0000  IMPORT	R1	K0
      0x8C080329,  //  0001  GETMET	R2	R1	K41
      0x5810002A,  //  0002  LDCONST	R4	K42
      0x84140000,  //  0003  CLOSURE	R5	P0
      0x8818032B,  //  0004  GETMBR	R6	R1	K43
      0x7C080800,  //  0005  CALL	R2	4
      0x8C080329,  //  0006  GETMET	R2	R1	K41
      0x5810002A,  //  0007  LDCONST	R4	K42
      0x84140001,  //  0008  CLOSURE	R5	P1
      0x8818032C,  //  0009  GETMBR	R6	R1	K44
      0x7C080800,  //  000A  CALL	R2	4
      0xA0000000,  //  000B  CLOSE	R0
      0x80000000,  //  000C  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: page_extensions_mgr_dispatcher
********************************************************************/
be_local_closure(class_Extensions_manager_page_extensions_mgr_dispatcher,   /* name */
  be_nested_proto(
    5,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_page_extensions_mgr_dispatcher,
    &be_const_str_solidified,
    ( &(const binstruction[18]) {  /* code */
      0xA4060000,  //  0000  IMPORT	R1	K0
      0x8C08032D,  //  0001  GETMET	R2	R1	K45
      0x7C080200,  //  0002  CALL	R2	1
      0x740A0001,  //  0003  JMPT	R2	#0006
      0x4C080000,  //  0004  LDNIL	R2
      0x80040400,  //  0005  RET	1	R2
      0x8C08032E,  //  0006  GETMET	R2	R1	K46
      0x5810002F,  //  0007  LDCONST	R4	K47
      0x7C080400,  //  0008  CALL	R2	2
      0x780A0003,  //  0009  JMPF	R2	#000E
      0x8C080130,  //  000A  GETMET	R2	R0	K48
      0x7C080200,  //  000B  CALL	R2	1
      0x80040400,  //  000C  RET	1	R2
      0x70020002,  //  000D  JMP		#0011
      0x8C080131,  //  000E  GETMET	R2	R0	K49
      0x7C080200,  //  000F  CALL	R2	1
      0x80040400,  //  0010  RET	1	R2
      0x80000000,  //  0011  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: list_extensions
********************************************************************/
be_local_closure(class_Extensions_manager_list_extensions,   /* name */
  be_nested_proto(
    10,                          /* nstack */
    0,                          /* argc */
    12,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_list_extensions,
    &be_const_str_solidified,
    ( &(const binstruction[57]) {  /* code */
      0x58000026,  //  0000  LDCONST	R0	K38
      0xA4066400,  //  0001  IMPORT	R1	K50
      0xA40A0200,  //  0002  IMPORT	R2	K1
      0x600C0012,  //  0003  GETGBL	R3	G18
      0x7C0C0000,  //  0004  CALL	R3	0
      0x60100010,  //  0005  GETGBL	R4	G16
      0x8C140333,  //  0006  GETMET	R5	R1	K51
      0x881C0134,  //  0007  GETMBR	R7	R0	K52
      0x7C140400,  //  0008  CALL	R5	2
      0x7C100200,  //  0009  CALL	R4	1
      0xA8020010,  //  000A  EXBLK	0	#001C
      0x5C140800,  //  000B  MOVE	R5	R4
      0x7C140000,  //  000C  CALL	R5	0
      0x8C180535,  //  000D  GETMET	R6	R2	K53
      0x5C200A00,  //  000E  MOVE	R8	R5
      0x58240036,  //  000F  LDCONST	R9	K54
      0x7C180600,  //  0010  CALL	R6	3
      0x741A0004,  //  0011  JMPT	R6	#0017
      0x8C180535,  //  0012  GETMET	R6	R2	K53
      0x5C200A00,  //  0013  MOVE	R8	R5
      0x58240037,  //  0014  LDCONST	R9	K55
      0x7C180600,  //  0015  CALL	R6	3
      0x781A0003,  //  0016  JMPF	R6	#001B
      0x8C180738,  //  0017  GETMET	R6	R3	K56
      0x88200134,  //  0018  GETMBR	R8	R0	K52
      0x00201005,  //  0019  ADD	R8	R8	R5
      0x7C180400,  //  001A  CALL	R6	2
      0x7001FFEE,  //  001B  JMP		#000B
      0x58100039,  //  001C  LDCONST	R4	K57
      0xAC100200,  //  001D  CATCH	R4	1	0
      0xB0080000,  //  001E  RAISE	2	R0	R0
      0xB8124800,  //  001F  GETNGBL	R4	K36
      0x8810093A,  //  0020  GETMBR	R4	R4	K58
      0x78120015,  //  0021  JMPF	R4	#0038
      0x60100010,  //  0022  GETGBL	R4	G16
      0xB8164800,  //  0023  GETNGBL	R5	K36
      0x88140B3A,  //  0024  GETMBR	R5	R5	K58
      0x8C140B3B,  //  0025  GETMET	R5	R5	K59
      0x7C140200,  //  0026  CALL	R5	1
      0x7C100200,  //  0027  CALL	R4	1
      0xA802000B,  //  0028  EXBLK	0	#0035
      0x5C140800,  //  0029  MOVE	R5	R4
      0x7C140000,  //  002A  CALL	R5	0
      0x8C18070E,  //  002B  GETMET	R6	R3	K14
      0x5C200A00,  //  002C  MOVE	R8	R5
      0x7C180400,  //  002D  CALL	R6	2
      0x4C1C0000,  //  002E  LDNIL	R7
      0x1C180C07,  //  002F  EQ	R6	R6	R7
      0x781A0002,  //  0030  JMPF	R6	#0034
      0x8C180738,  //  0031  GETMET	R6	R3	K56
      0x5C200A00,  //  0032  MOVE	R8	R5
      0x7C180400,  //  0033  CALL	R6	2
      0x7001FFF3,  //  0034  JMP		#0029
      0x58100039,  //  0035  LDCONST	R4	K57
      0xAC100200,  //  0036  CATCH	R4	1	0
      0xB0080000,  //  0037  RAISE	2	R0	R0
      0x80040600,  //  0038  RET	1	R3
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: page_extensions_ctl
********************************************************************/
be_local_closure(class_Extensions_manager_page_extensions_ctl,   /* name */
  be_nested_proto(
    15,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_page_extensions_ctl,
    &be_const_str_solidified,
    ( &(const binstruction[155]) {  /* code */
      0xA4060000,  //  0000  IMPORT	R1	K0
      0xA40A6400,  //  0001  IMPORT	R2	K50
      0xA40E0200,  //  0002  IMPORT	R3	K1
      0x8C10032D,  //  0003  GETMET	R4	R1	K45
      0x7C100200,  //  0004  CALL	R4	1
      0x74120001,  //  0005  JMPT	R4	#0008
      0x4C100000,  //  0006  LDNIL	R4
      0x80040800,  //  0007  RET	1	R4
      0xA802006F,  //  0008  EXBLK	0	#0079
      0x8C10033C,  //  0009  GETMET	R4	R1	K60
      0x5818000D,  //  000A  LDCONST	R6	K13
      0x7C100400,  //  000B  CALL	R4	2
      0x9414090D,  //  000C  GETIDX	R5	R4	K13
      0x401A193D,  //  000D  CONNECT	R6	K12	K61
      0x94180806,  //  000E  GETIDX	R6	R4	R6
      0x1C1C0B3E,  //  000F  EQ	R7	R5	K62
      0x781E0006,  //  0010  JMPF	R7	#0018
      0x201C0D3F,  //  0011  NE	R7	R6	K63
      0x781E0003,  //  0012  JMPF	R7	#0017
      0xB81E4800,  //  0013  GETNGBL	R7	K36
      0x8C1C0F10,  //  0014  GETMET	R7	R7	K16
      0x5C240C00,  //  0015  MOVE	R9	R6
      0x7C1C0400,  //  0016  CALL	R7	2
      0x7002005B,  //  0017  JMP		#0074
      0x1C1C0B40,  //  0018  EQ	R7	R5	K64
      0x781E0004,  //  0019  JMPF	R7	#001F
      0xB81E4800,  //  001A  GETNGBL	R7	K36
      0x8C1C0F41,  //  001B  GETMET	R7	R7	K65
      0x5C240C00,  //  001C  MOVE	R9	R6
      0x7C1C0400,  //  001D  CALL	R7	2
      0x70020054,  //  001E  JMP		#0074
      0x1C1C0B42,  //  001F  EQ	R7	R5	K66
      0x741E0001,  //  0020  JMPT	R7	#0023
      0x1C1C0B43,  //  0021  EQ	R7	R5	K67
      0x781E0041,  //  0022  JMPF	R7	#0065
      0x4C1C0000,  //  0023  LDNIL	R7
      0x1C200B42,  //  0024  EQ	R8	R5	K66
      0x7822000A,  //  0025  JMPF	R8	#0031
      0x8C200735,  //  0026  GETMET	R8	R3	K53
      0x5C280C00,  //  0027  MOVE	R10	R6
      0x582C0036,  //  0028  LDCONST	R11	K54
      0x7C200600,  //  0029  CALL	R8	3
      0x78220005,  //  002A  JMPF	R8	#0031
      0x5421FFFA,  //  002B  LDINT	R8	-5
      0x40221A08,  //  002C  CONNECT	R8	K13	R8
      0x94200C08,  //  002D  GETIDX	R8	R6	R8
      0x00201144,  //  002E  ADD	R8	R8	K68
      0x5C1C1000,  //  002F  MOVE	R7	R8
      0x7002000B,  //  0030  JMP		#003D
      0x1C200B43,  //  0031  EQ	R8	R5	K67
      0x78220009,  //  0032  JMPF	R8	#003D
      0x8C200735,  //  0033  GETMET	R8	R3	K53
      0x5C280C00,  //  0034  MOVE	R10	R6
      0x582C0037,  //  0035  LDCONST	R11	K55
      0x7C200600,  //  0036  CALL	R8	3
      0x78220004,  //  0037  JMPF	R8	#003D
      0x5421FFF9,  //  0038  LDINT	R8	-6
      0x40221A08,  //  0039  CONNECT	R8	K13	R8
      0x94200C08,  //  003A  GETIDX	R8	R6	R8
      0x00201145,  //  003B  ADD	R8	R8	K69
      0x5C1C1000,  //  003C  MOVE	R7	R8
      0x781E001F,  //  003D  JMPF	R7	#005E
      0x8C200546,  //  003E  GETMET	R8	R2	K70
      0x5C280C00,  //  003F  MOVE	R10	R6
      0x5C2C0E00,  //  0040  MOVE	R11	R7
      0x7C200600,  //  0041  CALL	R8	3
      0xB8262200,  //  0042  GETNGBL	R9	K17
      0x60280018,  //  0043  GETGBL	R10	G24
      0x582C0047,  //  0044  LDCONST	R11	K71
      0x5C300C00,  //  0045  MOVE	R12	R6
      0x5C340E00,  //  0046  MOVE	R13	R7
      0x5C381000,  //  0047  MOVE	R14	R8
      0x7C280800,  //  0048  CALL	R10	4
      0x582C0013,  //  0049  LDCONST	R11	K19
      0x7C240400,  //  004A  CALL	R9	2
      0x78220010,  //  004B  JMPF	R8	#005D
      0xB8264800,  //  004C  GETNGBL	R9	K36
      0x8824133A,  //  004D  GETMBR	R9	R9	K58
      0x8C241348,  //  004E  GETMET	R9	R9	K72
      0x5C2C0C00,  //  004F  MOVE	R11	R6
      0x7C240400,  //  0050  CALL	R9	2
      0x7826000A,  //  0051  JMPF	R9	#005D
      0xB8264800,  //  0052  GETNGBL	R9	K36
      0x8824133A,  //  0053  GETMBR	R9	R9	K58
      0xB82A4800,  //  0054  GETNGBL	R10	K36
      0x8828153A,  //  0055  GETMBR	R10	R10	K58
      0x94281406,  //  0056  GETIDX	R10	R10	R6
      0x98240E0A,  //  0057  SETIDX	R9	R7	R10
      0xB8264800,  //  0058  GETNGBL	R9	K36
      0x8824133A,  //  0059  GETMBR	R9	R9	K58
      0x8C241349,  //  005A  GETMET	R9	R9	K73
      0x5C2C0C00,  //  005B  MOVE	R11	R6
      0x7C240400,  //  005C  CALL	R9	2
      0x70020005,  //  005D  JMP		#0064
      0xB8222200,  //  005E  GETNGBL	R8	K17
      0x60240018,  //  005F  GETGBL	R9	G24
      0x5828004A,  //  0060  LDCONST	R10	K74
      0x5C2C0800,  //  0061  MOVE	R11	R4
      0x7C240400,  //  0062  CALL	R9	2
      0x7C200200,  //  0063  CALL	R8	1
      0x7002000E,  //  0064  JMP		#0074
      0x1C1C0B4B,  //  0065  EQ	R7	R5	K75
      0x781E000C,  //  0066  JMPF	R7	#0074
      0x201C0D3F,  //  0067  NE	R7	R6	K63
      0x781E000A,  //  0068  JMPF	R7	#0074
      0x8C1C0549,  //  0069  GETMET	R7	R2	K73
      0x5C240C00,  //  006A  MOVE	R9	R6
      0x7C1C0400,  //  006B  CALL	R7	2
      0xB8222200,  //  006C  GETNGBL	R8	K17
      0x60240018,  //  006D  GETGBL	R9	G24
      0x5828004C,  //  006E  LDCONST	R10	K76
      0x5C2C0C00,  //  006F  MOVE	R11	R6
      0x5C300E00,  //  0070  MOVE	R12	R7
      0x7C240600,  //  0071  CALL	R9	3
      0x58280013,  //  0072  LDCONST	R10	K19
      0x7C200400,  //  0073  CALL	R8	2
      0x8C1C034D,  //  0074  GETMET	R7	R1	K77
      0x5824002A,  //  0075  LDCONST	R9	K42
      0x7C1C0400,  //  0076  CALL	R7	2
      0xA8040001,  //  0077  EXBLK	1	1
      0x70020020,  //  0078  JMP		#009A
      0xAC100002,  //  0079  CATCH	R4	0	2
      0x7002001D,  //  007A  JMP		#0099
      0xB81A2200,  //  007B  GETNGBL	R6	K17
      0x601C0018,  //  007C  GETGBL	R7	G24
      0x5820004E,  //  007D  LDCONST	R8	K78
      0x5C240800,  //  007E  MOVE	R9	R4
      0x5C280A00,  //  007F  MOVE	R10	R5
      0x7C1C0600,  //  0080  CALL	R7	3
      0x5820001D,  //  0081  LDCONST	R8	K29
      0x7C180400,  //  0082  CALL	R6	2
      0x8C180303,  //  0083  GETMET	R6	R1	K3
      0x5820004F,  //  0084  LDCONST	R8	K79
      0x7C180400,  //  0085  CALL	R6	2
      0x8C180305,  //  0086  GETMET	R6	R1	K5
      0x7C180200,  //  0087  CALL	R6	1
      0x8C180306,  //  0088  GETMET	R6	R1	K6
      0x60200018,  //  0089  GETGBL	R8	G24
      0x58240050,  //  008A  LDCONST	R9	K80
      0x8C280315,  //  008B  GETMET	R10	R1	K21
      0x5C300800,  //  008C  MOVE	R12	R4
      0x7C280400,  //  008D  CALL	R10	2
      0x8C2C0315,  //  008E  GETMET	R11	R1	K21
      0x5C340A00,  //  008F  MOVE	R13	R5
      0x7C2C0400,  //  0090  CALL	R11	2
      0x7C200600,  //  0091  CALL	R8	3
      0x7C180400,  //  0092  CALL	R6	2
      0x8C180351,  //  0093  GETMET	R6	R1	K81
      0x88200352,  //  0094  GETMBR	R8	R1	K82
      0x7C180400,  //  0095  CALL	R6	2
      0x8C180323,  //  0096  GETMET	R6	R1	K35
      0x7C180200,  //  0097  CALL	R6	1
      0x70020000,  //  0098  JMP		#009A
      0xB0080000,  //  0099  RAISE	2	R0	R0
      0x80000000,  //  009A  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: page_extensions_mgr
********************************************************************/
be_local_closure(class_Extensions_manager_page_extensions_mgr,   /* name */
  be_nested_proto(
    20,                          /* nstack */
    1,                          /* argc */
    10,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_page_extensions_mgr,
    &be_const_str_solidified,
    ( &(const binstruction[150]) {  /* code */
      0xA4060000,  //  0000  IMPORT	R1	K0
      0xA40A0200,  //  0001  IMPORT	R2	K1
      0x8C0C0303,  //  0002  GETMET	R3	R1	K3
      0x58140053,  //  0003  LDCONST	R5	K83
      0x7C0C0400,  //  0004  CALL	R3	2
      0x8C0C0305,  //  0005  GETMET	R3	R1	K5
      0x7C0C0200,  //  0006  CALL	R3	1
      0x8C0C0306,  //  0007  GETMET	R3	R1	K6
      0x58140054,  //  0008  LDCONST	R5	K84
      0x7C0C0400,  //  0009  CALL	R3	2
      0x8C0C0155,  //  000A  GETMET	R3	R0	K85
      0x7C0C0200,  //  000B  CALL	R3	1
      0x6010000C,  //  000C  GETGBL	R4	G12
      0x5C140600,  //  000D  MOVE	R5	R3
      0x7C100200,  //  000E  CALL	R4	1
      0x2410090D,  //  000F  GT	R4	R4	K13
      0x78120075,  //  0010  JMPF	R4	#0087
      0x5810000D,  //  0011  LDCONST	R4	K13
      0x6014000C,  //  0012  GETGBL	R5	G12
      0x5C180600,  //  0013  MOVE	R6	R3
      0x7C140200,  //  0014  CALL	R5	1
      0x14140805,  //  0015  LT	R5	R4	R5
      0x7816006E,  //  0016  JMPF	R5	#0086
      0x2414090D,  //  0017  GT	R5	R4	K13
      0x78160002,  //  0018  JMPF	R5	#001C
      0x8C140306,  //  0019  GETMET	R5	R1	K6
      0x581C0056,  //  001A  LDCONST	R7	K86
      0x7C140400,  //  001B  CALL	R5	2
      0x8C140757,  //  001C  GETMET	R5	R3	K87
      0x5C1C0800,  //  001D  MOVE	R7	R4
      0x7C140400,  //  001E  CALL	R5	2
      0x8C180315,  //  001F  GETMET	R6	R1	K21
      0x5C200A00,  //  0020  MOVE	R8	R5
      0x7C180400,  //  0021  CALL	R6	2
      0xB81E4800,  //  0022  GETNGBL	R7	K36
      0x8C1C0F58,  //  0023  GETMET	R7	R7	K88
      0x5C240A00,  //  0024  MOVE	R9	R5
      0x7C1C0400,  //  0025  CALL	R7	2
      0xB8224800,  //  0026  GETNGBL	R8	K36
      0x8820113A,  //  0027  GETMBR	R8	R8	K58
      0x78220005,  //  0028  JMPF	R8	#002F
      0xB8224800,  //  0029  GETNGBL	R8	K36
      0x8820113A,  //  002A  GETMBR	R8	R8	K58
      0x8C201148,  //  002B  GETMET	R8	R8	K72
      0x5C280A00,  //  002C  MOVE	R10	R5
      0x7C200400,  //  002D  CALL	R8	2
      0x70020000,  //  002E  JMP		#0030
      0x50200000,  //  002F  LDBOOL	R8	0	0
      0x78220001,  //  0030  JMPF	R8	#0033
      0x58240059,  //  0031  LDCONST	R9	K89
      0x70020000,  //  0032  JMP		#0034
      0x5824003F,  //  0033  LDCONST	R9	K63
      0x8C280F0E,  //  0034  GETMET	R10	R7	K14
      0x5830005A,  //  0035  LDCONST	R12	K90
      0x50340000,  //  0036  LDBOOL	R13	0	0
      0x7C280600,  //  0037  CALL	R10	3
      0x582C005B,  //  0038  LDCONST	R11	K91
      0x8C300306,  //  0039  GETMET	R12	R1	K6
      0x5838005C,  //  003A  LDCONST	R14	K92
      0x7C300400,  //  003B  CALL	R12	2
      0x8C300306,  //  003C  GETMET	R12	R1	K6
      0x60380018,  //  003D  GETGBL	R14	G24
      0x583C005D,  //  003E  LDCONST	R15	K93
      0x5C400C00,  //  003F  MOVE	R16	R6
      0x8C440315,  //  0040  GETMET	R17	R1	K21
      0x944C0F16,  //  0041  GETIDX	R19	R7	K22
      0x7C440400,  //  0042  CALL	R17	2
      0x5C481200,  //  0043  MOVE	R18	R9
      0x7C380800,  //  0044  CALL	R14	4
      0x7C300400,  //  0045  CALL	R12	2
      0x8C300306,  //  0046  GETMET	R12	R1	K6
      0x60380018,  //  0047  GETGBL	R14	G24
      0x583C005E,  //  0048  LDCONST	R15	K94
      0x8C400315,  //  0049  GETMET	R16	R1	K21
      0x94480F1A,  //  004A  GETIDX	R18	R7	K26
      0x7C400400,  //  004B  CALL	R16	2
      0x7C380400,  //  004C  CALL	R14	2
      0x7C300400,  //  004D  CALL	R12	2
      0x8C300306,  //  004E  GETMET	R12	R1	K6
      0x5838005F,  //  004F  LDCONST	R14	K95
      0x7C300400,  //  0050  CALL	R12	2
      0x8C300306,  //  0051  GETMET	R12	R1	K6
      0x58380060,  //  0052  LDCONST	R14	K96
      0x7C300400,  //  0053  CALL	R12	2
      0x8C300306,  //  0054  GETMET	R12	R1	K6
      0x60380018,  //  0055  GETGBL	R14	G24
      0x583C0061,  //  0056  LDCONST	R15	K97
      0x78220001,  //  0057  JMPF	R8	#005A
      0x5840003F,  //  0058  LDCONST	R16	K63
      0x70020000,  //  0059  JMP		#005B
      0x5C401600,  //  005A  MOVE	R16	R11
      0x78220001,  //  005B  JMPF	R8	#005E
      0x58440040,  //  005C  LDCONST	R17	K64
      0x70020000,  //  005D  JMP		#005F
      0x5844003E,  //  005E  LDCONST	R17	K62
      0x5C480C00,  //  005F  MOVE	R18	R6
      0x78220001,  //  0060  JMPF	R8	#0063
      0x584C0062,  //  0061  LDCONST	R19	K98
      0x70020000,  //  0062  JMP		#0064
      0x584C0063,  //  0063  LDCONST	R19	K99
      0x7C380A00,  //  0064  CALL	R14	5
      0x7C300400,  //  0065  CALL	R12	2
      0x8C300306,  //  0066  GETMET	R12	R1	K6
      0x60380018,  //  0067  GETGBL	R14	G24
      0x583C0064,  //  0068  LDCONST	R15	K100
      0x782A0001,  //  0069  JMPF	R10	#006C
      0x5840003F,  //  006A  LDCONST	R16	K63
      0x70020000,  //  006B  JMP		#006D
      0x5C401600,  //  006C  MOVE	R16	R11
      0x782A0001,  //  006D  JMPF	R10	#0070
      0x58440042,  //  006E  LDCONST	R17	K66
      0x70020000,  //  006F  JMP		#0071
      0x58440043,  //  0070  LDCONST	R17	K67
      0x5C480C00,  //  0071  MOVE	R18	R6
      0x782A0001,  //  0072  JMPF	R10	#0075
      0x584C0065,  //  0073  LDCONST	R19	K101
      0x70020000,  //  0074  JMP		#0076
      0x584C0066,  //  0075  LDCONST	R19	K102
      0x7C380A00,  //  0076  CALL	R14	5
      0x7C300400,  //  0077  CALL	R12	2
      0x8C300306,  //  0078  GETMET	R12	R1	K6
      0x60380018,  //  0079  GETGBL	R14	G24
      0x583C0067,  //  007A  LDCONST	R15	K103
      0x5C400C00,  //  007B  MOVE	R16	R6
      0x8C440315,  //  007C  GETMET	R17	R1	K21
      0x5C4C0A00,  //  007D  MOVE	R19	R5
      0x7C440400,  //  007E  CALL	R17	2
      0x7C380600,  //  007F  CALL	R14	3
      0x7C300400,  //  0080  CALL	R12	2
      0x8C300306,  //  0081  GETMET	R12	R1	K6
      0x58380068,  //  0082  LDCONST	R14	K104
      0x7C300400,  //  0083  CALL	R12	2
      0x0010090C,  //  0084  ADD	R4	R4	K12
      0x7001FF8B,  //  0085  JMP		#0012
      0x70020002,  //  0086  JMP		#008A
      0x8C100306,  //  0087  GETMET	R4	R1	K6
      0x58180069,  //  0088  LDCONST	R6	K105
      0x7C100400,  //  0089  CALL	R4	2
      0x8C100306,  //  008A  GETMET	R4	R1	K6
      0x58180021,  //  008B  LDCONST	R6	K33
      0x7C100400,  //  008C  CALL	R4	2
      0x8C100306,  //  008D  GETMET	R4	R1	K6
      0x5818006A,  //  008E  LDCONST	R6	K106
      0x7C100400,  //  008F  CALL	R4	2
      0x8C100351,  //  0090  GETMET	R4	R1	K81
      0x8818036B,  //  0091  GETMBR	R6	R1	K107
      0x7C100400,  //  0092  CALL	R4	2
      0x8C100323,  //  0093  GETMET	R4	R1	K35
      0x7C100200,  //  0094  CALL	R4	1
      0x80000000,  //  0095  RET	0
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified function: list_extensions_in_fs
********************************************************************/
be_local_closure(class_Extensions_manager_list_extensions_in_fs,   /* name */
  be_nested_proto(
    10,                          /* nstack */
    0,                          /* argc */
    12,                          /* varg */
    0,                          /* has upvals */
    NULL,                       /* no upvals */
    0,                          /* has sup protos */
    NULL,                       /* no sub protos */
    1,                          /* has constants */
    &be_ktab_class_Extensions_manager,     /* shared constants */
    &be_const_str_list_extensions_in_fs,
    &be_const_str_solidified,
    ( &(const binstruction[36]) {  /* code */
      0x58000026,  //  0000  LDCONST	R0	K38
      0xA4060200,  //  0001  IMPORT	R1	K1
      0xB80AD800,  //  0002  GETNGBL	R2	K108
      0x7C080000,  //  0003  CALL	R2	0
      0x600C0010,  //  0004  GETGBL	R3	G16
      0x8C10016D,  //  0005  GETMET	R4	R0	K109
      0x7C100200,  //  0006  CALL	R4	1
      0x7C0C0200,  //  0007  CALL	R3	1
      0xA8020016,  //  0008  EXBLK	0	#0020
      0x5C100600,  //  0009  MOVE	R4	R3
      0x7C100000,  //  000A  CALL	R4	0
      0xB8164800,  //  000B  GETNGBL	R5	K36
      0x8C140B58,  //  000C  GETMET	R5	R5	K88
      0x5C1C0800,  //  000D  MOVE	R7	R4
      0x7C140400,  //  000E  CALL	R5	2
      0x4C180000,  //  000F  LDNIL	R6
      0x20180A06,  //  0010  NE	R6	R5	R6
      0x781A0005,  //  0011  JMPF	R6	#0018
      0x8C180B0E,  //  0012  GETMET	R6	R5	K14
      0x58200016,  //  0013  LDCONST	R8	K22
      0x7C180400,  //  0014  CALL	R6	2
      0x781A0000,  //  0015  JMPF	R6	#0017
      0x98080C04,  //  0016  SETIDX	R2	R6	R4
      0x70020006,  //  0017  JMP		#001F
      0xB81A2200,  //  0018  GETNGBL	R6	K17
      0x601C0018,  //  0019  GETGBL	R7	G24
      0x5820006E,  //  001A  LDCONST	R8	K110
      0x5C240800,  //  001B  MOVE	R9	R4
      0x7C1C0400,  //  001C  CALL	R7	2
      0x58200013,  //  001D  LDCONST	R8	K19
      0x7C180400,  //  001E  CALL	R6	2
      0x7001FFE8,  //  001F  JMP		#0009
      0x580C0039,  //  0020  LDCONST	R3	K57
      0xAC0C0200,  //  0021  CATCH	R3	1	0
      0xB0080000,  //  0022  RAISE	2	R0	R0
      0x80040400,  //  0023  RET	1	R2
    })
  )
);
/*******************************************************************/


/********************************************************************
** Solidified class: Extensions_manager
********************************************************************/
be_local_class(Extensions_manager,
    0,
    NULL,
    be_nested_map(11,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key(version_string, -1), be_const_static_closure(class_Extensions_manager_version_string_closure) },
        { be_const_key(page_extensions_mgr, 7), be_const_closure(class_Extensions_manager_page_extensions_mgr_closure) },
        { be_const_key(page_extensions_store, 0), be_const_closure(class_Extensions_manager_page_extensions_store_closure) },
        { be_const_key(web_add_button, 6), be_const_closure(class_Extensions_manager_web_add_button_closure) },
        { be_const_key(web_add_handler, -1), be_const_closure(class_Extensions_manager_web_add_handler_closure) },
        { be_const_key(page_extensions_mgr_dispatcher, -1), be_const_closure(class_Extensions_manager_page_extensions_mgr_dispatcher_closure) },
        { be_const_key(EXT_FOLDER, -1), be_nested_str(_X2F_X2Eextensions_X2F) },
        { be_const_key(list_extensions, 5), be_const_static_closure(class_Extensions_manager_list_extensions_closure) },
        { be_const_key(page_extensions_ctl, -1), be_const_closure(class_Extensions_manager_page_extensions_ctl_closure) },
        { be_const_key(init, 1), be_const_closure(class_Extensions_manager_init_closure) },
        { be_const_key(list_extensions_in_fs, -1), be_const_static_closure(class_Extensions_manager_list_extensions_in_fs_closure) },
    })),
    (bstring*) &be_const_str_Extensions_manager
);

/********************************************************************
** Solidified module: extensions
********************************************************************/
be_local_module(extensions,
    "extensions",
    be_nested_map(2,
    ( (struct bmapnode*) &(const bmapnode[]) {
        { be_const_key(Extensions_manager, -1), be_const_class(be_class_Extensions_manager) },
        { be_const_key(init, 0), be_const_closure(_anonymous__closure) },
    }))
);
BE_EXPORT_VARIABLE be_define_const_native_module(extensions);
/********************************************************************/
/********************************************************************/
/* End of solidification */
