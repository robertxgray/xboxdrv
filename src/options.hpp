/*
**  Xbox360 USB Gamepad Userspace Driver
**  Copyright (C) 2010 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_XBOXDRV_OPTIONS_HPP
#define HEADER_XBOXDRV_OPTIONS_HPP

#include <string>
#include <map>
#include <vector>

#include "evdev_absmap.hpp"
#include "modifier.hpp"
#include "uinput_options.hpp"
#include "xpad_device.hpp"

#include "modifier/axismap_modifier.hpp"
#include "modifier/buttonmap_modifier.hpp"

class ControllerOptions
{
public:
  ControllerOptions();

  UInputOptions uinput;
  std::vector<ModifierPtr> modifier;

  // everything below gets later converted into modifier
  boost::shared_ptr<ButtonmapModifier> buttonmap;
  boost::shared_ptr<AxismapModifier>   axismap;

  int  deadzone;
  int  deadzone_trigger;
  bool square_axis;
  bool four_way_restrictor;
  int  dpad_rotation;

  std::map<XboxAxis, AxisFilterPtr> calibration_map;
  std::map<XboxAxis, AxisFilterPtr> sensitivity_map;
  std::map<XboxAxis, AxisFilterPtr> relative_axis_map;
  std::map<XboxButton, ButtonFilterPtr> autofire_map;
};

class Options
{
public:
  enum { RUN_DEFAULT,
         RUN_DAEMON, 
         RUN_LIST_CONTROLLER,
         RUN_LIST_SUPPORTED_DEVICES,
         RUN_LIST_SUPPORTED_DEVICES_XPAD,
         PRINT_VERSION,
         PRINT_HELP,
         PRINT_HELP_DEVICES,
         PRINT_ENUMS,
         PRINT_LED_HELP
  } mode;

  enum {
    LIST_ALL       = ~0,
    LIST_ABS       = (1<<0),
    LIST_REL       = (1<<1),
    LIST_KEY       = (1<<2),
    LIST_X11KEYSYM = (1<<3),
    LIST_AXIS      = (1<<4),
    LIST_BUTTON    = (1<<5)
  };

  // General program options
  bool verbose;
  bool silent;
  bool quiet;
  bool rumble;
  int  led;
  int  rumble_l;
  int  rumble_r;
  int  rumble_gain;
  int  controller_id;
  int  wireless_id;
  bool instant_exit;
  bool no_uinput;
  bool detach_kernel_driver;
  int  timeout;

  GamepadType gamepad_type;
  
  // device options
  std::string busid;
  std::string devid;

  int vendor_id;
  int product_id;

  std::string evdev_device;
  EvdevAbsMap evdev_absmap;
  bool evdev_grab;
  bool evdev_debug;
  std::map<int, XboxButton> evdev_keymap;

  // controller options
  typedef std::map<int, ControllerOptions> ControllerConfigs;
  typedef std::map<int, ControllerConfigs> ControllerSlots;
  ControllerSlots controller_slots;

  // chatpad options
  bool chatpad;
  bool chatpad_no_init;
  bool chatpad_debug;

  // headset options
  bool headset;
  bool headset_debug;
  std::string headset_dump;
  std::string headset_play;

  // daemon options
  bool detach;
  std::string pid_file;
  std::string on_connect;
  std::string on_disconnect;

  std::vector<std::string> exec;

  uint32_t list_enums;

  XboxButton config_toggle_button;

  int controller_slot;
  int config_slot;

  bool extra_devices;

public:
  Options();

  ControllerConfigs& get_controller_slot();
  const ControllerConfigs& get_controller_slot() const;
  
  /** Returns the currently active configuration */
  ControllerOptions& get_controller_options();
  const ControllerOptions& get_controller_options() const;

  void next_controller();
  void next_config();

  void set_device_name(const std::string& name);
  void set_mouse();
  void set_guitar();
  void set_trigger_as_button();
  void set_trigger_as_zaxis();
  void set_dpad_as_button();
  void set_dpad_only();
  void set_force_feedback();
  void set_mimic_xpad();
};

extern Options* g_options;

#endif

/* EOF */
