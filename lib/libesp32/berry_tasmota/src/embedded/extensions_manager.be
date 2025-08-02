#  extensions manager module for Berry
#
#

#@ solidify:extensions

var extensions = module("extensions")


class Extensions_manager
  static var EXT_FOLDER = "/.extensions/"
  # var _archive
  # var _error

  def init()
    tasmota.add_driver(self)
  end

  #####################################################################################################
  # version_string(v)
  #
  # Convert 32 bits version to "a.b.c.d" where version is 0xAABBCCDD
  #####################################################################################################
  static def version_string(v)
    return f"v{(v >> 24) & 0xFF}.{(v >> 16) & 0xFF}.{(v >> 8) & 0xFF}.{v & 0xFF}"
  end

  #####################################################################################################
  # Init web handlers
  #####################################################################################################
  # Displays a "Autoconf" button on the configuration page
  def web_add_button()
    import webserver
      webserver.content_send(
      "<form id=but_part_mgr style='display: block;' action='ext' method='get'><button>Extensions</button></form><p></p>")
  end

  # Returns the list of enabled and disabled extensions
  # i.e. scan files in ".extensions" folder and keep files ending with ".tapp" and "._tapp"
  static def list_extensions()
    import path
    import string
    var l = []
    # read from fs
    for d: path.listdir(_class.EXT_FOLDER)
      if string.endswith(d, ".tapp") || string.endswith(d, "._tapp")
        l.push(_class.EXT_FOLDER + d)
      end
    end
    # complement with running extension
    if tasmota._ext
      for d: tasmota._ext.keys()
        if (l.find(d) == nil)
          l.push(d)
        end
      end
    end
    # finish
    return l
  end

  # List all extensions in file-system, whether they are running or not
  # Returns a `sortedmap` with Name of App as key, and following map:
  #   name, description, version (int), autorun (bool)
  static def list_extensions_in_fs()
    import string
    var sm = sortedmap()
    for ext: _class.list_extensions()
      var details = tasmota.read_extension_manifest(ext)
      if (details != nil)
        var name = details.find("name")
        if (name)
          sm[name] = ext
        end
      else
        log(f"EXT: unable to read details from '{ext}'", 3)
      end
    end
    return sm
  end

  #####################################################################################################
  # This HTTP GET manager controls which web controls are displayed
  #####################################################################################################
  def page_extensions_mgr_dispatcher()
    import webserver
    if !webserver.check_privileged_access() return nil end

    if (webserver.has_arg("store"))
      return self.page_extensions_store()
    else
      return self.page_extensions_mgr()
    end
  end

  #####################################################################################################
  # This HTTP GET manager controls which web controls are displayed
  #####################################################################################################
  def page_extensions_mgr()
    import webserver
    import string

    webserver.content_start('Extensions Manager')
    webserver.content_send_style()
    # webserver.content_send("<p><small>&nbsp;(This feature requires an internet connection)</small></p>")
    
    webserver.content_send("<fieldset>"
                           "<style>"
                           # Fix for small text - the key is width: min-content on parent */
                           ".ext-item{width:min-content;min-width:100%;}"
                           ".ext-item small{display:block;word-wrap:break-word;overflow-wrap:break-word;white-space:normal;padding-right:5px;padding-top:0px;}"
                           # Control bar styles
                           ".ext-controls{display:flex;gap:8px;align-items:center;margin-top:8px;padding:0px}"
                           # Small action buttons
                           ".btn-small{padding:0 6px;line-height:1.8rem;font-size:0.9rem;min-width:auto;width:auto;flex-shrink:0;}"
                           # form
                           "form{padding-top:0px;padding-bottom:0px;}"
                           # Running indicator
                           ".running-indicator{display:inline-block;width:8px;height:8px;border-radius:50%;margin-right:8px;background:var(--c_btn);animation:pulse 1.5s infinite;}"
                           "@keyframes pulse{0%{opacity:1;}50%{opacity:0.5;}100%{opacity:1;}}"
                           "</style>"
                           "<legend><b title='Running extensions'>&nbsp;Installed extensions</b></legend>")
    var installed_ext = self.list_extensions_in_fs()
    if size(installed_ext) > 0
      var ext_nb = 0
      while ext_nb < size(installed_ext)
        if (ext_nb > 0)       webserver.content_send("<hr>")   end
        var ext_path = installed_ext.get_by_index(ext_nb)   # ex: '/.extensions/Partition_Wizard.tapp'
        var ext_path_html = webserver.html_escape(ext_path)
        var details = tasmota.read_extension_manifest(ext_path)
        var running = tasmota._ext ? tasmota._ext.contains(ext_path) : false
        var running_indicator = running ? " <span class='running-indicator' title='Running'></span>" : ""
        var autorun = details.find("autorun", false)
        var dark_blue = "style='background:var(--c_btnoff);'"
        webserver.content_send("<div class='ext-item'>")
        webserver.content_send(f"<span title='path: {ext_path_html}'><b>{webserver.html_escape(details['name'])}</b>{running_indicator}</span><br>")
        webserver.content_send(f"<small>{webserver.html_escape(details['description'])}</small>")

        webserver.content_send("<div class='ext-controls' style='padding-top:0px;padding-bottom:0px;'>")
        webserver.content_send("<form action='/ext' method='post' class='ext-controls'>")
        webserver.content_send(f"<button type='submit' class='btn-small' {running ? '' :: dark_blue} name='{running ? 's' :: 'r'}{ext_path_html}'>{running ? 'Running' :: 'Stopped'}</button>")
        webserver.content_send(f"<button type='submit' class='btn-small' {autorun ? '' :: dark_blue} name='{autorun ? 'a' :: 'A'}{ext_path_html}'>Auto-run: {autorun ? 'ON' :: 'OFF'}</button>")
        webserver.content_send(f"<button type='submit' class='btn-small' style='background-color:var(--c_btnoff);border-color:var(--c_btnrst);border-width:3px;border-style:solid;' name='d{ext_path_html}' onclick='return confirm(\"Confirm deletion of {webserver.html_escape(ext_path)}\")'>Uninstall</button>")
        webserver.content_send("</form></div></div>")

        ext_nb += 1
      end
    else
      # no installed extensions
      webserver.content_send("<div><small><i>No installed extension.</i></small></p>")
    end

    webserver.content_send("<p></p></fieldset><p></p>")

    webserver.content_send("<div style='display: block;'></div>"
                           "<p></p><form style='display: block;' action='ext' method='get'><button name='store'>Extension Store</button></form>")

    webserver.content_button(webserver.BUTTON_MANAGEMENT) #- button back to management page -#
    webserver.content_stop()
  end

  #####################################################################################################
  # Extension Store
  #####################################################################################################
  def page_extensions_store()
    import webserver
    import string
    import json

    webserver.content_start('Extensions Store')
    webserver.content_send_style()

    webserver.content_send("<script>"
                              "function toggleDesc(id) {"
                                "var desc = document.getElementById('desc-' + id);"
                                "var arrow = document.getElementById('arrow-' + id);"
                                "if (desc.style.display === 'none' || desc.style.display === '') {"
                                  "desc.style.display = 'block';"
                                  "arrow.innerHTML = '▼';"
                                "} else {"
                                  "desc.style.display = 'none';"
                                  "arrow.innerHTML = '▶';"
                                "}"
                              "}"
                              # Simple filtering functions (optional enhancement)
                              "function filterExtensions(query) {"
                                "var items = document.getElementsByClassName('ext-store-item');"
                                "query = query.toLowerCase();"
                                "for (var i = 0; i < items.length; i++) {"
                                  "var name = items[i].getElementsByClassName('ext-name')[0].textContent.toLowerCase();"
                                  "var desc = items[i].getElementsByClassName('ext-desc')[0].textContent.toLowerCase();"
                                  "if (name.includes(query) || desc.includes(query)) {"
                                    "items[i].style.display = 'block';"
                                  "} else {"
                                    "items[i].style.display = 'none';"
                                  "}"
                                "}"
                              "}"
                            "</script>")

    webserver.content_send("<style>"
                          # /* Extension Store specific styles */
                          ".store-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:10px;}"
                          ".store-stats{font-size:0.9em;color:var(--c_in);}"
                          ".ext-store-item{background:var(--c_bg);border-radius:0.3em;margin-bottom:5px;padding:0 0 4px 0;}"
                          ".ext-header{display:flex;justify-content:space-between;align-items:center;cursor:pointer;user-select:none;padding:0 5px;}"
                          ".ext-title{display:flex;align-items:center;gap:6px;flex:1;}"
                          ".ext-name{font-weight:bold;}"
                          ".ext-version{font-size:0.8em;}"
                          ".ext-arrow{color:var(--c_in);font-size:0.8em;}"
                          ".ext-badges{}"
                          # ".ext-badges{margin-left:auto;gap:8px;align-items:center;}"
                          ".ext-details{width:min-content;min-width:100%;padding-left:0;padding:3px 0;display:none;margin-top:3px;padding-top:3px;border-top:1px solid var(--c_frm);}"
                          ".ext-desc{color:var(--c_in);font-size:0.8em;line-height:1.4;display:block;word-wrap:break-word;overflow-wrap:break-word;white-space:normal;}"

                          ".ext-actions{display:flex;gap:8px;padding:0 5px;}"
                          ".btn-action{padding:0 12px;line-height:1.8em;font-size:0.9em;flex:1;}"
                          ".installed-badge{background:var(--c_btnsv);padding:2px 6px;border-radius:3px;font-size:0.8em;}"
                          ".update-badge{background:var(--c_btnhvr);padding:2px 6px;border-radius:3px;font-size:0.8em;animation:pulse 2s infinite;}"
                          "@keyframes pulse{0%{opacity:1;}50%{opacity:0.7;}100%{opacity:1;}}"
                          # ".category-filter{display:flex;gap:5px;margin-bottom:15px;overflow-x:auto;padding:5px 0;}"
                          # ".cat-btn{padding:5px 12px;background:#3a3a3a;border:1px solid var(--c_frm);border-radius:15px;color:#aaa;font-size:0.9em;white-space:nowrap;cursor:pointer;transition:all 0.2s;}"
                          # ".cat-btn:hover{background:#4a4a4a;color:var(--c_btntxt);}"
                          # ".cat-btn.active{background:#1fa3ec;color:var(--c_btntxt);border-color:var(--c_btn);}"
                          # ".search-box{width:100%;box-sizing:border-box;padding:8px;border:0;color:var(--c_txt);margin-bottom:10px;border-radius:0.3em;}"
                          # ".search-box::placeholder{color:var(--c_frm);}"
                          "</style>")

    webserver.content_send("<p><small>&nbsp;(This feature requires an internet connection)</small></p>")

    webserver.content_send("<fieldset>"

                            "<legend><b>&nbsp;Available Extensions&nbsp;</b></legend>"
                            
                            "<div class='store-header'>"
                              "<span>Browse Extensions</span>"
                              "<span class='store-stats'>24 available</span>"
                            "</div>"
                            
                            "<input type='text' placeholder='Search extensions...' onkeyup='filterExtensions(this.value)'>"
                            "<p></p>")
                            
                            # "<div class='category-filter'>"
                            #   "<span class='cat-btn active' onclick='filterCategory('all')'>All</span>"
                            #   "<span class='cat-btn' onclick='filterCategory('display')'>Display</span>"
                            #   "<span class='cat-btn' onclick='filterCategory('sensors')'>Sensors</span>"
                            #   "<span class='cat-btn' onclick='filterCategory('automation')'>Automation</span>"
                            #   "<span class='cat-btn' onclick='filterCategory('tools')'>Tools</span>"
                            # "</div>"
    var item_jsonl=
    '{'
      '"name": "Leds Panel",'
      '"version": "0x02010001",'
      '"description": "Real-time display of WS2812 LEDs in browser with smooth animations and pattern editor.",'
      '"author": "Stephan Hadinger"'
    '}'
    '\n'
    '{'
      '"name": "Partition Wizard",'
      '"version": "0x01020300",'
      '"description": "Wizard for resizing partitions and converting to safeboot layout.",'
      '"author": "Stephan Hadinger"'
    '}'
    '\n'
    '{'
      '"name": "Energy Monitor",'
      '"version": "0x03000100",'
      '"description": "Real-time energy consumption monitoring with daily/monthly statistics. Supports multiple energy meters and cost calculation.'
      '\\nIncludes export to CSV and graphical consumption trends.",'
      '"author": "Stephan Hadinger"'
    '}'
    var item_idx = 1
    var json_pos = 0       # starting char to parse JSONL
    while (json_pos < size(item_jsonl))   # item_idx negative means that we have nothing more to display
      var lf_pos = string.find(item_jsonl, "\n", json_pos)
      if (lf_pos < 0)   lf_pos = size(item_jsonl)   end       # go to end of string
      var json_line = item_jsonl[json_pos .. lf_pos]
      var item = json.load(json_line)
      log(f"EXT: {json_line=} {item=}", 3)

      if (item != nil)

        webserver.content_send(f"<div class='ext-store-item'>"
                                  "<div class='ext-header' onclick='toggleDesc(\"{item_idx}\")'>"
                                    "<div class='ext-title'>"
                                      "<span class='ext-name'>{webserver.html_escape(item['name'])}</span>"
                                      "<span class='ext-version'><small>{self.version_string(int(item['version']))}</small></span>"
                                    "</div>"
                                    "<div class='ext-badges'>"
                                        "<span class='update-badge'>Upgrade</span>"
                                    "</div>"
                                    "<span id='arrow-{item_idx}' class='ext-arrow'>▶</span>"
                                  "</div>"
                                  "<div id='desc-{item_idx}' class='ext-details'>"
                                    "<div class='ext-desc'>"
                                      "{string.replace(webserver.html_escape(item['description']), '\\n', '<br>')}"
                                      "<br>v1.8.0 → {self.version_string(int(item['version']))}"
                                    "</div>"
                                    "<form action='/store' method='post' class='ext-actions'>"
                                      "<div style='width:30%'></div>"
                                      "<button type='submit' class='btn-action' name='u/Leds_Panel.tapp' onclick='return confirmAction('update', 'Leds Panel')'>Upgrade</button>"
                                      "<button type='submit' class='btn-action bred' name='d/Leds_Panel.tapp' onclick='return confirmAction('delete', 'Leds Panel')'>Delete</button>"
                                    "</form>"
                                  "</div>"
                                "</div>")

        item_idx += 1
      end

      json_pos = lf_pos + 1
    end

    var item_json =
    '{'
      '"name": "Leds Panel",'
      '"version": "0x02010001",'
      '"description": "Real-time display of WS2812 LEDs in browser with smooth animations and pattern editor.",'
      '"author": "Stephan Hadinger",'
      '"min_tasmota": "0x0E060001",'
      '"features": ""'
    '}'
    var item = json.load(item_json)
    webserver.content_send(f"<div class='ext-store-item'>"
                              "<div class='ext-header' onclick='toggleDesc(\"{item_idx}\")'>"
                                "<div class='ext-title'>"
                                  "<span class='ext-name'>{webserver.html_escape(item['name'])}</span>"
                                  "<span class='ext-version'><small>{self.version_string(int(item['version']))}</small></span>"
                                "</div>"
                                "<div class='ext-badges'>"
                                    "<span class='update-badge'>Upgrade</span>"
                                "</div>"
                                "<span id='arrow-{item_idx}' class='ext-arrow'>▶</span>"
                              "</div>"
                              "<div id='desc-{item_idx}' class='ext-details'>"
                                "<div class='ext-desc'>"
                                  "{webserver.html_escape(item['description'])}"
                                  "<br>v1.8.0 → {self.version_string(int(item['version']))}"
                                "</div>"
                                "<form action='/store' method='post' class='ext-actions'>"
                                  "<div style='width:30%'></div>"
                                  "<button type='submit' class='btn-action' name='u/Leds_Panel.tapp' onclick='return confirmAction('update', 'Leds Panel')'>Upgrade</button>"
                                  "<button type='submit' class='btn-action bred' name='d/Leds_Panel.tapp' onclick='return confirmAction('delete', 'Leds Panel')'>Delete</button>"
                                "</form>"
                              "</div>"
                            "</div>")
       
    item_idx = 2
    item_json =
    '{'
      '"name": "Partition Wizard",'
      '"version": "0x01020300",'
      '"description": "Wizard for resizing partitions and converting to safeboot layout.",'
      '"author": "Stephan Hadinger",'
      '"min_tasmota": "0x0E060001",'
      '"features": ""'
    '}'

    item = json.load(item_json)
    webserver.content_send(f"<div class='ext-store-item'>"
                              "<div class='ext-header' onclick='toggleDesc(\"{item_idx}\")'>"
                                "<div class='ext-title'>"
                                  "<span class='ext-name'>{webserver.html_escape(item['name'])}</span>"
                                  "<span class='ext-version'><small>{self.version_string(int(item['version']))}</small></span>"
                                "</div>"
                                "<div class='ext-badges'>"
                                    "<span class='installed-badge'>Installed</span>"
                                "</div>"
                                "<span id='arrow-{item_idx}' class='ext-arrow'>▶</span>"
                              "</div>"
                              "<div id='desc-{item_idx}' class='ext-details'>"
                                "<div class='ext-desc'>"
                                  "{webserver.html_escape(item['description'])}"
                                "</div>"
                                "<form action='/store' method='post' class='ext-actions'>"
                                  "<div style='width:30%'></div>"
                                  "<button type='submit' class='btn-action bred' name='d/Leds_Panel.tapp' onclick='return confirmAction('delete', 'Leds Panel')'>Delete</button>"
                                "</form>"
                              "</div>"
                            "</div>")
    webserver.content_send(
                            # # <!-- Extension 1 - Update Available -->
                            # "<div class='ext-store-item'>"
                            #   "<div class='ext-header' onclick='toggleDesc(\"1\")'>"
                            #     "<div class='ext-title'>"
                            #       "<span class='ext-name'>Leds Panel</span>"
                            #       "<span class='ext-version'>v2.1.0</span>"
                            #       "<span class='update-badge'>Update Available</span>"
                            #     "</div>"
                            #     "<span id='arrow-1' class='ext-arrow'>▶</span>"
                            #   "</div>"
                            #   "<div id='desc-1' class='ext-details'>"
                            #     "<div class='ext-desc'>"
                            #       "Realtime display of WS2812 LEDs in browser with advanced controls. Supports up to 1024 LEDs with smooth animations and pattern editor."
                            #       "<br>Current version: v1.8.0 → New version: v2.1.0"
                            #     "</div>"
                            #     "<form action='/store' method='post' class='ext-actions'>"
                            #       "<button type='submit' class='btn-action borange' name='u/Leds_Panel.tapp' onclick='return confirmAction('update', 'Leds Panel')'>Update</button>"
                            #       "<button type='submit' class='btn-action bred' name='d/Leds_Panel.tapp' onclick='return confirmAction('delete', 'Leds Panel')'>Delete</button>"
                            #     "</form>"
                            #   "</div>"
                            # "</div>"

                            #<!-- Extension 2 - Installed -->
                            # "<div class='ext-store-item'>"
                            #     "<div class='ext-header' onclick='toggleDesc(\"2\")'>"
                            #         "<div class='ext-title'>"
                            #             "<span class='ext-name'>Partition Wizard</span>"
                            #             "<span class='ext-version'>v1.2.3</span>"
                            #             "<span class='installed-badge'>Installed</span>"
                            #         "</div>"
                            #         "<span id='arrow-2' class='ext-arrow'>▶</span>"
                            #     "</div>"
                            #     "<div id='desc-2' class='ext-details'>"
                            #         "<div class='ext-desc'>"
                            #             "Wizard for resizing partitions and converting to safeboot layout. "
                            #             "Includes backup/restore functionality and partition health checks.<br>"
                            #             "Safe mode prevents accidental partition damage."
                            #         "</div>"
                            #         "<form action='/store' method='post' class='ext-actions'>"
                            #             "<button type='submit' class='btn-action bred' name='d/Partition_Wizard.tapp' onclick='return confirmAction(\"delete\", \"Partition Wizard\")'>Delete</button>"
                            #         "</form>"
                            #     "</div>"
                            # "</div>"
                            
                            #<!-- Extension 3 - Not Installed -->
                            "<div class='ext-store-item'>"
                                "<div class='ext-header' onclick='toggleDesc(\"3\")'>"
                                    "<div class='ext-title'>"
                                        "<span class='ext-name'>Energy Monitor</span>"
                                        "<span class='ext-version'>v3.0.1</span>"
                                    "</div>"
                                    "<span id='arrow-3' class='ext-arrow'>▶</span>"
                                "</div>"
                                "<div id='desc-3' class='ext-details'>"
                                    "<div class='ext-desc'>"
                                        "Real-time energy consumption monitoring with daily/monthly statistics. "
                                        "Supports multiple energy meters and cost calculation.<br>"
                                        "Includes export to CSV and graphical consumption trends."
                                    "</div>"
                                    "<form action='/store' method='post' class='ext-actions'>"
                                        "<div style='width:30%'></div>"
                                        "<button type='submit' class='btn-action bgrn' name='i/Energy_Monitor.tapp'>Install</button>"
                                    "</form>"
                                "</div>"
                            '</div>'
                            
                          )
            
    webserver.content_send("<p></p></fieldset><p></p>")

    webserver.content_send("<div style='display: block;'></div>"
                           "<p></p><form style='display: block;' action='ext' method='get'><button name=''>Extensions</button></form>")
    webserver.content_stop()
  end
    
  #####################################################################################################
  # Web controller
  #
  # Applies the changes and restart
  #####################################################################################################
  # This HTTP POST manager handles the submitted web form data
  def page_extensions_ctl()
    import webserver
    import path
    import string
    if !webserver.check_privileged_access() return nil end

    try
      # log(f">>> {webserver.arg_name(0)=} {webserver.arg(0)=} {webserver.arg_size()=}")

      var btn_name = webserver.arg_name(0)
      var action = btn_name[0]          # first character
      var action_path = btn_name[1..]   # remove first character

      if (action == "r")                # button "Run"
        if (action_path != "")
          tasmota.load(action_path)
        end
      elif (action == "s")              # button "Stop"
        tasmota.unload_extension(action_path)
      elif (action == "a") || (action == "A")             # button "Autorun", "A" enable, "a" disable
        var new_name
        if (action == "a") && string.endswith(action_path, ".tapp")     # Autorun is enabled, disable it
          new_name = action_path[0..-5] + "_tapp"
        elif (action == "A") && string.endswith(action_path, "._tapp")
          new_name = action_path[0..-6] + "tapp"
        end
        if new_name
          var success = path.rename(action_path, new_name)
          log(f"EXT: rename '{action_path}' to '{new_name} {success=}", 3)
          if (success)                  # update any running extension with its new name
            if tasmota._ext.contains(action_path)
              tasmota._ext[new_name] = tasmota._ext[action_path]
              tasmota._ext.remove(action_path)
            end
          end
        else
          log(f"EXT: wrong action '{btn_name}'")
        end
      elif (action == 'd')              # button "Delete"
        if (action_path != "")
          var success = path.remove(action_path)
          log(f"EXT: delete '{action_path}' {success=}", 3)
        end
      end

      webserver.redirect("/ext")
    except .. as e, m
      log(f"CFG: Exception> '{e}' - {m}", 2)
      #- display error page -#
      webserver.content_start("Parameter error")           #- title of the web page -#
      webserver.content_send_style()                  #- send standard Tasmota styles -#

      webserver.content_send(f"<p style='width:340px;'><b>Exception:</b><br>'{webserver.html_escape(e)}'<br>{webserver.html_escape(m)}</p>")

      webserver.content_button(webserver.BUTTON_CONFIGURATION) #- button back to management page -#
      webserver.content_stop()                        #- end of web page -#
    end
  end

  # Add HTTP POST and GET handlers
  def web_add_handler()
    import webserver
    webserver.on('/ext', / -> self.page_extensions_mgr_dispatcher(), webserver.HTTP_GET)
    webserver.on('/ext', / -> self.page_extensions_ctl(), webserver.HTTP_POST)
  end
end

extensions.Extensions_manager = Extensions_manager
extensions.init = def (m)

  return m.Extensions_manager()    # return an instance of this class
end
