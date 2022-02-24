# lv_3D_cube
#
# ported and adapted from https://github.com/mrt-prodz/ATmega328-Tiny-3D-Engine

import lv_3D_cube

class lv_3D_cube_widget : lv.obj
  var mpu
  
  var points
  var cube
  var nodes       # projected nodes
  var point_style
  var col_red, col_black
  # drawing
  var area
  var rect_dsc
  var line_dsc
  var triangle
  # following are structures for drawing callback
  var roll, pitch
  var h2, w2
  var draw_ctx      # temporary store draw context
  var x_ofs, y_ofs  # offset of object when drawing

  var faces_colors  # base color for each cube face

  static angle_tolerance = 2    # minimum difference in degrees before updating cube

  def init(parent, accelerator)
    self.mpu = accelerator
    # init widget
    super(self).init(parent)

    # init drawing structures
    self.area = lv.area()
    self.rect_dsc = lv.draw_rect_dsc()
    self.line_dsc = lv.draw_line_dsc()
    self.triangle = [lv.point(), lv.point(), lv.point()]    # for lv.point_arr
    self.col_black = lv.color(0x000000)
    self.col_red = lv.color(0xFF0000)

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

    lv.draw_line_dsc_init(self.line_dsc)                  # initialize lv_draw_line_dsc structure
    self.init_draw_line_dsc(lv.PART_MAIN, self.line_dsc)  # copy the current values
    self.line_dsc.opa = 255
    self.line_dsc.width = 3

    self.add_event_cb( / obj, evt -> self.draw_cb(obj, evt), lv.EVENT_DRAW_POST, 0)

    # init 3D cube
    self.cube = lv_3D_cube()

    self.set_size(40,40)
    self.set_style_pad_all(0, lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_bg_opa(0, lv.PART_MAIN | lv.STATE_DEFAULT)
    # self.set_style_bg_color(lv.color(0x000000), lv.PART_MAIN | lv.STATE_DEFAULT)
    # self.set_style_bg_opa(100, lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_border_color(lv.color(0x0099EE), lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_border_width(1, lv.PART_MAIN | lv.STATE_DEFAULT)
    #self.set_style_border_opa(200, lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_radius(0, lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_pad_all(2, lv.PART_MAIN | lv.STATE_DEFAULT)

    # colors for each cube face
    self.faces_colors = [ lv.color(0x1fa3ec),       # face Tasmota Blue
                          lv.color(0xFFFF00),       # bottom - Yellow
                          lv.color(0x00FF00),       # right side Green
                          lv.color(0x33FFFF),       # front light blue
                          lv.color(0xFF0000),       # left side Red
                          lv.color(0xFFFF00),       # rear side Yellow
                        ]

    tasmota.add_driver(self)
    self.pitch = -999
    self.roll = -999    # force update
    self.loop()   # run it at least once
  end

  def del()
    tasmota.remove_driver(self)
    super(self).del()
  end

  # def draw_line(x0,y0, x1,y1, col)
  #   var x_ofs = self.area.x1
  #   var y_ofs = self.area.y1

  #   var p0 = self.triangle[0]
  #   p0.x = x0 + x_ofs
  #   p0.y = y0 + y_ofs

  #   var p1 = self.triangle[1]
  #   p1.x = x1 + x_ofs
  #   p1.y = y1 + y_ofs

  #   self.line_dsc.width = 1
  #   self.line_dsc.opa = 255
  #   self.line_dsc.color = col
  #   self.line_dsc.round_start = 0
  #   self.line_dsc.round_end = 0
  #   # print("draw_line", p0.x, p0.y, p1.x, p1.y)
  #   lv.draw_line(self.draw_ctx, self.line_dsc, p0, p1)
  # end

  # def draw_triangle(x0,y0,x1,y1,x2,y2, col)
  #   var x_ofs = self.area.x1
  #   var y_ofs = self.area.y1

  #   var p0 = self.triangle[0]
  #   p0.x = x0 + x_ofs
  #   p0.y = y0 + y_ofs

  #   var p1 = self.triangle[1]
  #   p1.x = x1 + x_ofs
  #   p1.y = y1 + y_ofs

  #   var p2 = self.triangle[2]
  #   p2.x = x2 + x_ofs
  #   p2.y = y2 + y_ofs

  #   # select correct color
  #   self.rect_dsc.bg_color = col

  #   # draw triangle
  #   var tr = lv.point_arr(self.triangle)
  #   lv.draw_triangle(self.draw_ctx, self.rect_dsc, tr)
  # end

  def draw_cb(obj, event)
    # print(event.code)
    var code = event.code
  
    if code == lv.EVENT_DRAW_POST
      var t1 = tasmota.millis()
      self.draw_ctx = lv.draw_ctx(event.param)
      # get coordinates of object
      self.get_coords(self.area)
      var x_ofs = self.area.x1
      var y_ofs = self.area.y1
      
      self.h2 = self.get_height() / 2
      self.w2 = self.get_width() / 2
  
      var w2 = self.w2
      var h2 = self.h2

      var tri = self.cube.edges
      var nodes = self.nodes
      var t2 = tasmota.millis()

      var col_red = self.col_red
      var col_black = self.col_black
      # allocated 4 points for square
      var p0 = lv.point()
      var p1 = lv.point()
      var p2 = lv.point()
      var p3 = lv.point()
      var pts4_arr = [p0, p1, p2, p3]

      var i = size(tri) - 2
      while i >= 0
        if !self.cube.is_hidden(nodes, i)
          # print("show i:", i)
          # we group triangle in pairs to 4-polygon
          var tri_i = tri[i]
          var n0 = nodes[tri_i[0]]
          var n1 = nodes[tri_i[1]]
          var n2 = nodes[tri_i[2]]
          var n3 = nodes[tri[i+1][1]]   # grab the 4th corner in the middle of the next triangle
          # var x0 = n0[0] + w2
          # var y0 = n0[1] + h2
          # var x1 = n1[0] + w2
          # var y1 = n1[1] + h2
          # var x2 = n2[0] + w2
          # var y2 = n2[1] + h2
          # var x3 = n3[0] + w2
          # var y3 = n3[1] + h2

          p0.x = n0[0] + w2 + x_ofs
          p0.y = n0[1] + h2 + y_ofs
          p1.x = n1[0] + w2 + x_ofs
          p1.y = n1[1] + h2 + y_ofs
          p2.x = n2[0] + w2 + x_ofs
          p2.y = n2[1] + h2 + y_ofs
          p3.x = n3[0] + w2 + x_ofs
          p3.y = n3[1] + h2 + y_ofs
          var pts4 = lv.point_arr(pts4_arr)

          # self.draw_line(x0,y0, x1,y1, col)
          # self.draw_line(x1,y1, x2,y2, col)
          # self.draw_line(x2,y2, x3,y3, col)
          # self.draw_line(x3,y3, x0,y0, col)
          # self.draw_line(x2,y2, x0,y0, lv.color(0x000000))

          # select correct color
          self.rect_dsc.bg_color = self.faces_colors[i / 2]
          lv.draw_polygon(self.draw_ctx, self.rect_dsc, pts4, 4)
        end
        i -= 2
      end
      var t3 = tasmota.millis()
      # print("draw",t2-t1, t3-t1, "ms")
      # print("Pitch",self.pitch,"Roll",self.roll)
    end
  end
  
  def loop()
    def abs(i) return i >= 0 ? i : -i end

    var t = tasmota.millis()
    var accel = self.mpu.read_accel()
    var ax = accel[0]
    var ay = accel[1]
    var az = accel[2]
    # import json
    # var coords = json.load(tasmota.read_sensors()).find("MPU9250")
    # var ax = coords.find("AX", 0)
    # var ay = coords.find("AY", 0)
    # var az = coords.find("AZ", 0)

    import math
    var pitch = int(math.deg(math.atan2(ay, math.sqrt(ax*ax + az*az))) + 0.5)
    var roll = int(math.deg(math.atan2(ax, math.sqrt(ay*ay + az*az))) + 0.5)
    if az < 0   # TODO
      pitch = 180 - pitch
      roll = 180 - roll
    end
    # print("Roll", self.roll, "Pitch", self.pitch)

    if abs(self.pitch - pitch) > self.angle_tolerance || abs(self.roll - roll) > self.angle_tolerance
      self.pitch = pitch
      self.roll = roll
      self.nodes = self.cube.project(-self.roll, -self.pitch)
      # print("time rendering: ", tasmota.millis()-t, "ms")

      self.h2 = self.get_height() / 2
      self.w2 = self.get_width() / 2
      self.invalidate()
    end
  end

  def every_100ms()
    self.loop()
  end
end

return lv_3D_cube_widget

#-

import lv_3D_cube_widget
var c = lv_3D_cube_widget(scr)
c.set_pos(0,150)

-#

#-

def do_loop()
  c.loop()
  tasmota.set_timer(25, do_loop)
end
do_loop()

-#