
class test : lv.obj
  var area
  var rect_dsc
  var line_dsc
  var triangle
  # following are structures for drawing callback
  var draw_ctx      # temporary store draw context
  var x_ofs, y_ofs  # offset of object when drawing

  def init(parent)
    super(self).init(parent)
    self.area = lv.area()
    self.rect_dsc = lv.draw_rect_dsc()
    self.line_dsc = lv.draw_line_dsc()
    self.triangle = [lv.point(), lv.point(), lv.point()]    # for lv.point_arr

    lv.draw_rect_dsc_init(self.rect_dsc)                  # initialize lv.draw_line_dsc structure
    self.init_draw_rect_dsc(lv.PART_MAIN, self.rect_dsc)  # copy the current values

    self.rect_dsc.bg_opa = 255
    self.rect_dsc.bg_color = lv.color(0x0000FF)
    self.rect_dsc.radius = 0
    self.rect_dsc.border_width = 0
    self.rect_dsc.border_opa = 0
    self.rect_dsc.border_color = lv.color(0x000000)
    self.rect_dsc.outline_width = 0
    self.rect_dsc.outline_pad = 0
    self.rect_dsc.shadow_width = 0

    self.add_event_cb( / obj, evt -> self.draw_cb(obj, evt), lv.EVENT_DRAW_POST, 0)
  end

  def draw_triangle(x0,y0,x1,y1,x2,y2, col)
    var x_ofs = self.area.x1
    var y_ofs = self.area.y1

    var p0 = self.triangle[0]
    p0.x = x0 + x_ofs
    p0.y = y0 + y_ofs

    var p1 = self.triangle[1]
    p1.x = x1 + x_ofs
    p1.y = y1 + y_ofs

    var p2 = self.triangle[2]
    p2.x = x2 + x_ofs
    p2.y = y2 + y_ofs

    # select correct color
    self.rect_dsc.bg_color = col

    # draw triangle
    var tr = lv.point_arr(self.triangle)
    lv.draw_triangle(self.draw_ctx, self.rect_dsc, tr)
  end

  def draw_cb(obj, event)
    # print(event.code)
    var code = event.code
  
    if code == lv.EVENT_DRAW_POST
      self.draw_ctx = lv.draw_ctx(event.param)
      # get coordinates of object
      self.get_coords(self.area)
      # self.x_ofs = self.area.x1
      # self.y_ofs = self.area.y1
      
      # lv.draw_rect_dsc_init(self.rect_dsc)                  # initialize lv.draw_line_dsc structure
      # self.init_draw_rect_dsc(lv.PART_MAIN, self.rect_dsc)  # copy the current values

      # lv.draw_line_dsc_init(self.line_dsc)                  # initialize lv_draw_line_dsc structure
      # self.init_draw_line_dsc(lv.PART_MAIN, self.line_dsc)  # copy the current values

      self.draw_triangle(10,10, 10,60, 50,60, lv.color(0xFF0000))
      self.draw_triangle(10,10, 50,60, 50,10, lv.color(0x0000FF))
    end
  end
  
end



t = test(scr)
t.set_size(150,150)
t.set_pos(30,30)
# t.set_style_bg_opa(0,0)