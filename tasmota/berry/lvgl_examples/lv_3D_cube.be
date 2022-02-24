# lv_3D_cube
#
# ported and adapted from https://github.com/mrt-prodz/ATmega328-Tiny-3D-Engine

class lv_3D_cube
  var nodes_proj    # projected nodes (avoid reallocation each time)

  # ################################################################################
  # 3D Cube description
  # ################################################################################
  # nodes for a rectangle parallelepiped
  static nodes = [
    [ 12,  12, -6],
    [ 12, -12, -6],
    [-12, -12, -6],
    [-12,  12, -6],
    [ 12,  12,  6],
    [-12,  12,  6],
    [-12, -12,  6],
    [ 12, -12,  6]
  ]

  # edges for a cube
  static edges = [
    [0, 1, 2],
    [2, 3, 0],
    [4, 5, 6],
    [6, 7, 4],
    [0, 4, 7],
    [7, 1, 0],
    [1, 7, 6],
    [6, 2, 1],
    [2, 6, 5],
    [5, 3, 2],
    [4, 0, 3],
    [3, 5, 4],
  ]

  # ################################################################################
  # Fast trigonometrics using LVGL included functions
  # ################################################################################
  def sin(angle)
    return (lv.trigo_sin(angle)+1)/2
  end

  def cos(angle)
    return (lv.trigo_cos(angle)+1)/2
  end

  # ################################################################################
  # Shoelace algorithm to get the surface
  # ################################################################################
  def shoelace(n, index)
    var surface = 0
    for t:0..2
      # (x1y2 - y1x2) + (x2y3 - y2x3) ...
      surface += n[self.edges[index][t]][0]         * n[self.edges[index][t<2?t+1:0]][1] -
                 n[self.edges[index][t<2?t+1:0]][0] * n[self.edges[index][t]][1]
    end
    return surface / 2
  end

  # ################################################################################
  # Shoelace algorithm for triangle visibility
  # 
  # This formula gives the surface and the orientation.
  # If positive, the facet is facing us hence rendered
  # ################################################################################
  def is_hidden(n, index)
    var is_hidden
    # (x1y2 - y1x2) + (x2y3 - y2x3) ...
    var edge = self.edges[index]
    var e0 = n[edge[0]]
    var e1 = n[edge[1]]
    var e2 = n[edge[2]]
    var e0x = e0[0]
    var e0y = e0[1]
    var e1x = e1[0]
    var e1y = e1[1]
    var e2x = e2[0]
    var e2y = e2[1]
    is_hidden = ( e0x * e1y -
                  e1x * e0y ) +
                ( e1x * e2y -
                  e2x * e1y ) +
                ( e2x * e0y -
                  e0x * e2y )
    # is_hidden = ( n[self.edges[index][0]][0] * n[self.edges[index][1]][1] -
    #               n[self.edges[index][1]][0] * n[self.edges[index][0]][1] ) +
    #             ( n[self.edges[index][1]][0] * n[self.edges[index][2]][1] -
    #               n[self.edges[index][2]][0] * n[self.edges[index][1]][1] ) +
    #             ( n[self.edges[index][2]][0] * n[self.edges[index][0]][1] -
    #               n[self.edges[index][0]][0] * n[self.edges[index][2]][1] )
    return is_hidden >= 0
  end

  # ################################################################################
  # Methods
  # ################################################################################
  def init()
    self.nodes_proj = []
    for i:0..size(self.edges)-1
      self.nodes_proj.push([0,0])
    end
  end

  def project(ay, az)
    var nodes = self.nodes
    var nodes_proj = self.nodes_proj

    #- complete formula including yaw (if needed) - below is simplified with yaw=0
    var cosa = self.cos(ax)
    var sina = self.sin(ax)
    var cosb = self.cos(ay)
    var sinb = self.sin(ay)
    var cosc = self.cos(az)
    var sinc = self.sin(az)

    var w00 = (cosa * cosb) >> 14
    var w10 = ((((cosa * sinb) >> 14) * sinc) >> 14) - ((sina * cosc) >> 14)
    var w20 = ((((cosa * sinb) >> 14) * cosc) >> 14) + ((sina * sinc) >> 14)
    var w01 = (sina * cosb) >> 14
    var w11 = ((((sina * sinb) >> 14) * sinc) >> 14) + ((cosa * cosc) >> 14)
    var w21 = ((((sina * sinb) >> 14) * cosc) >> 14) - ((cosa * sinc) >> 14)
    var w02 = -sinb
    var w12 = (cosb * sinc) >> 14
    var w22 = (cosb * cosc) >> 14
    -#
    var cosb = self.cos(ay)
    var sinb = self.sin(ay)
    var cosc = self.cos(az)
    var sinc = self.sin(az)

    var w00 = cosb
    var w10 = (sinb * sinc) >> 14
    var w20 = (sinb * cosc) >> 14
    var w01 = 0
    var w11 = cosc
    var w21 = - sinc
    var w02 = -sinb
    var w12 = (cosb * sinc) >> 14
    var w22 = (cosb * cosc) >> 14

    for i:0..size(self.nodes)-1
      var nn = nodes[i]
      var ni0 = nn[0]
      var ni1 = nn[1]
      var ni2 = nn[2]
      var x,y,z
      x = (w00 * ni0 +
           w10 * ni1 +
           w20 * ni2) / 16384

      y = (w01 * ni0 +
           w11 * ni1 +
           w21 * ni2) / 16384

      z = (w02 * ni0 +
           w12 * ni1 +
           w22 * ni2) / 16384
      # store projected node
      nodes_proj[i][0] = (64 * x) / (64 + z)
      nodes_proj[i][1] = (64 * y) / (64 + z)
    end
    return nodes_proj
  end
  
end

return lv_3D_cube
