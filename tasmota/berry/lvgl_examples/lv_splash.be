#- start LVGL and display splash -#

def lv_splash()
  import global
  import display

  if !display.started() return end

  lv.start()

  var hres = lv.get_hor_res()       # should be 320
  var vres = lv.get_ver_res()       # should be 240

  var scr = lv.scr_act()            # default screean object
  var f28 = lv.montserrat_font(28)  # load embedded Montserrat 20
  var white = lv.color(lv.COLOR_WHITE)

  scr.set_style_bg_color(lv.color(0x000066), 0) # lv.PART_MAIN | lv.STATE_DEFAULT
  # 0x53706C68 = 'Splh' indicating the screen is Splash screen
  scr.set_user_data(0x53706C68)

  var tas_logo = lv.img(scr)
  tas_logo.set_tasmota_logo()
  tas_logo.set_zoom(150)
  tas_logo.set_style_img_recolor_opa(255, 0)  # lv.PART_MAIN | lv.STATE_DEFAULT
  tas_logo.set_style_img_recolor(white, 0)    # lv.PART_MAIN | lv.STATE_DEFAULT
  tas_logo.set_align(lv.ALIGN_LEFT_MID)
  tas_logo.set_x(-12)

  var tas = lv.label(scr)
  # tas.set_style_bg_opa(lv.OPA_TRANSP, lv.PART_MAIN | lv.STATE_DEFAULT)
  tas.set_style_text_color(white, 0)          # lv.PART_MAIN | lv.STATE_DEFAULT
  tas.set_text("TASMOTA")
  if f28 != nil tas.set_style_text_font(f28, 0) end
  tas.set_align(lv.ALIGN_LEFT_MID)
  tas.set_x(42)

  var driver_name = display.driver_name()
  var disp
  if size(driver_name) > 0
    disp = lv.label(scr)
    disp.set_align(lv.ALIGN_BOTTOM_MID)
    # disp.set_style_bg_opa(lv.OPA_TRANSP, lv.PART_MAIN | lv.STATE_DEFAULT)
    disp.set_style_text_color(lv.color(0xFFFFFF), 0)    # lv.PART_MAIN | lv.STATE_DEFAULT
    disp.set_text(driver_name)
  end

  # inner function to remove splash screen after a while
  def remove_splash()
    if lv.scr_act().get_user_data() == 0x53706C68
      lv.start()    # reinit only if the splash screen is still on display
    end
  end

  tasmota.set_timer(5000, remove_splash)
end

lv_splash()
