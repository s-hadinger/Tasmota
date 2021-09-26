#- embedded class for LVGL globals -#

class LVGL_glob
  var cb_obj                # mapping between LVGL native pointer (int) and Berry object
  var cb_event_closure      # mapping for event closures per LVGL native pointer (int)
  var event_cb              # native callback for lv_event
  var null_cb                     # cb called if type is not supported

  var widget_ctor_cb
  var widget_dtor_cb
  var widget_event_cb
  var widget_struct

  static cb_do_nothing = def() print("LVL: call to unsupported callback") end

  def lvgl_event_dispatch(event_ptr)
    import introspect

    var event = lv_event(introspect.toptr(event_ptr))

    var target = event.target
    var f = self.cb_event_closure[target]
    var obj = self.cb_obj[target]
    #print('>> lvgl_event_dispatch', f, obj, event)
    f(obj, event)
  end

  def gen_cb(name, f, obj, ptr)
    #print('>> gen_cb', name, obj, ptr)
    # record the object, whatever the callback
    if self.cb_obj == nil             self.cb_obj = {} end
  
    if name  == "lv_event_cb"
      if self.cb_event_closure == nil   self.cb_event_closure = {} end
      if self.event_cb == nil			     self.event_cb = tasmota.gen_cb(/ event_ptr -> self.lvgl_event_dispatch(event_ptr)) end  # encapsulate 'self' in closure
    
      self.cb_obj[ptr] = obj
      self.cb_event_closure[ptr] = f
      return self.event_cb
    # elif name == "<other_cb>"
    else
      if self.null_cb == nil                  self.null_cb = tasmota.gen_cb(self.cb_do_nothing) end
      return self.null_cb
    end
  end

  def widget_ctor_impl(cl, obj)
  end
  def widget_dtor_impl(cl, obj)
  end
  def widget_event_impl(cl, obj)
  end


  def widget_cb()
    if self.widget_ctor_cb == nil           self.widget_ctor_cb = tasmota.gen_cb(/ cl, obj -> self.widget_ctor_impl(cl, obj)) end
    if self.widget_dtor_cb == nil           self.widget_dtor_cb = tasmota.gen_cb(/ cl, obj -> self.widget_dtor_impl(cl, obj)) end
    if self.widget_event_cb == nil          self.widget_event_cb = tasmota.gen_cb(/ cl, obj -> self.widget_event_impl(cl, obj)) end

    if self.widget_struct == nil
      self.widget_struct = lv_obj_class(lv_obj._class).copy()
      self.widget_struct.base_class = lv_obj._class               # by default, inherit from base class `lv_obj`, this can be overriden
      self.widget_struct.constructor_cb = self.widget_ctor_cb     # set the berry cb dispatchers
      self.widget_struct.destructor_cb = self.widget_dtor_cb
      self.widget_struct.event_cb = self.widget_event_cb
    end
  end

  #- deregister all information linked to a specific LVGL native object (int) -#
  def deregister(obj)
    self.cb_obj.remove(obj)
    self.cb_event_closure.remove(obj)
  end

end

_lvgl = LVGL_glob()
