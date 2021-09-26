#- embedded class for LVGL globals -#

class LVGL_glob
  var cb_obj                # mapping between LVGL native pointer (int) and Berry object
  var cb_event_closure      # mapping for event closures per LVGL native pointer (int)
  var event_cb              # native callback for lv_event
  var null_cb                     # cb called if type is not supported

  var widget_ctor_cb
  var widget_dtor_cb
  var widget_event_cb
  var widget_struct_default
  var widget_struct_by_class

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

  def widget_ctor_impl(cl_ptr, obj)
    import introspect
    var cl = lv_obj_class(cl_ptr)
    if self.cb_obj.find(obj)  obj = self.cb_obj[obj]  end
    print("widget_ctor_impl", cl, obj)
    if type(obj) == 'instance' && introspect.get(obj, 'widget_constructor')
      obj.widget_constructor(cl)
    end
  end
  def widget_dtor_impl(cl_ptr, obj)
    import introspect
    var cl = lv_obj_class(cl_ptr)
    if self.cb_obj.find(obj)  obj = self.cb_obj[obj]  end
    print("widget_dtor_impl", cl, obj)
    if type(obj) == 'instance' && introspect.get(obj, 'widget_destructor')
      obj.widget_destructor(cl)
    end
  end
  def widget_event_impl(cl_ptr, e_ptr)
    import introspect
    var cl = lv_obj_class(cl_ptr)
    var event = lv_event(e_ptr)
    var obj = event.target
    if self.cb_obj.find(obj)  obj = self.cb_obj[obj]  end
    if type(obj) == 'instance' && introspect.get(obj, 'widget_event')
      obj.widget_event(cl, event)
    end
    print("widget_event_impl", cl, obj, event)
  end


  def widget_cb()
    if self.widget_ctor_cb == nil           self.widget_ctor_cb = tasmota.gen_cb(/ cl, obj -> self.widget_ctor_impl(cl, obj)) end
    if self.widget_dtor_cb == nil           self.widget_dtor_cb = tasmota.gen_cb(/ cl, obj -> self.widget_dtor_impl(cl, obj)) end
    if self.widget_event_cb == nil          self.widget_event_cb = tasmota.gen_cb(/ cl, e -> self.widget_event_impl(cl, e)) end

    if self.widget_struct_default == nil
      self.widget_struct_default = lv_obj_class(lv_obj._class).copy()
      self.widget_struct_default.base_class = lv_obj._class               # by default, inherit from base class `lv_obj`, this can be overriden
      self.widget_struct_default.constructor_cb = self.widget_ctor_cb     # set the berry cb dispatchers
      self.widget_struct_default.destructor_cb = self.widget_dtor_cb
      self.widget_struct_default.event_cb = self.widget_event_cb
    end
  end

  #- deregister all information linked to a specific LVGL native object (int) -#
  def deregister(obj)
    self.cb_obj.remove(obj)
    self.cb_event_closure.remove(obj)
  end

  #- initialize a custom widget -#
  #- arg must be a subclass of lv_obj -#
  def create_custom_widget(obj, parent)
    import introspect

    if !isinstance(obj, lv_obj)   raise "value_error", "arg must be a subclass of lv_obj" end
    if self.widget_struct_by_class == nil     self.widget_struct_by_class = {} end
    if self.cb_obj == nil                     self.cb_obj = {} end

    var obj_classname = classname(obj)
    var obj_class_struct = self.widget_struct_by_class.find(obj_classname)
    #- not already built, create a new one for this class -#
    if obj_class_struct == nil
      self.widget_cb()    # set up all structures
      obj_class_struct = self.widget_struct_default.copy()    # get a copy of the structure with pre-defined callbacks
      obj_class_struct.base_class = obj._class
      if introspect.get(obj, 'widget_width_def')     obj_class_struct.width_def = obj.widget_width_def          end
      if introspect.get(obj, 'widget_height_def')    obj_class_struct.height_def = obj.widget_height_def        end
      if introspect.get(obj, 'widget_editable')      obj_class_struct.editable = obj.widget_editable            end
      if introspect.get(obj, 'widget_group_def')     obj_class_struct.group_def = obj.widget_group_def          end
      if introspect.get(obj, 'widget_instance_size') obj_class_struct.instance_size = obj.widget_instance_size  end

      #- keep a copy of the structure to avoid GC and reuse if needed -#
      self.widget_struct_by_class[obj_classname] = obj_class_struct
    end

    var lv_obj_ptr = lv.obj_class_create_obj(obj_class_struct, parent)
    obj._p = lv_obj_ptr._p
    self.cb_obj[int(lv_obj_ptr._p)] = obj     # register the mapping between the native LVGL object as int and Berry object
    obj.class_init_obj()
  end
end

_lvgl = LVGL_glob()

class lv_custom_widget : lv_obj
  var _class
  static widget_width_def
  static widget_height_def
  static widget_editable
  static widget_group_def
  static widget_instance_size

  def init(parent)
    _lvgl.create_custom_widget(self, parent)
  end

  def widget_constructor(cl)
    print("widget_constructor", cl)
  end

  def widget_destructor(cl)
    print("widget_destructor", cl)
  end

  def widget_event(cl, e)
    print("widget_event", cl, e)
    var res = lv.obj_event_base(cl, e)
    print("widget_event res=", res)
  end
end

w = lv_custom_widget(scr)

# typedef struct _lv_obj_class_t {
#     const struct _lv_obj_class_t * base_class;
#     void (*constructor_cb)(const struct _lv_obj_class_t * class_p, struct _lv_obj_t * obj);
#     void (*destructor_cb)(const struct _lv_obj_class_t * class_p, struct _lv_obj_t * obj);
# #if LV_USE_USER_DATA
#     void * user_data;
# #endif
#     void (*event_cb)(const struct _lv_obj_class_t * class_p, struct _lv_event_t * e);  /**< Widget type specific event function*/
#     lv_coord_t width_def;
#     lv_coord_t height_def;
#     uint32_t editable : 2;             /**< Value from ::lv_obj_class_editable_t*/
#     uint32_t group_def : 2;            /**< Value from ::lv_obj_class_group_def_t*/
#     uint32_t instance_size : 16;
# }lv_obj_class_t;


# struct _lv_obj_t * lv_obj_class_create_obj(const struct _lv_obj_class_t * class_p, struct _lv_obj_t * parent)

