/*
 * Copyright (C) 2001, 2002 Havoc Pennington
 * Copyright (C) 2002, 2003 Red Hat Inc.
 * Some ICCCM manager selection code derived from fvwm2,
 * Copyright (C) 2001 Dominik Vogt, Matthias Clasen, and fvwm2 team
 * Copyright (C) 2003 Rob Adams
 * Copyright (C) 2004-2006 Elijah Newren
 * Copyright (C) 2013 Red Hat Inc.
 * Copyright (C) 2017 Alberts Muktupāvels
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Adapted from mutter:
 * - src/backends/x11/meta-monitor-manager-xrandr.c
 */

#include "config.h"
#include "gf-monitor-manager-xrandr-private.h"

struct _GfMonitorManagerXrandr
{
  GfMonitorManager parent;
};

G_DEFINE_TYPE (GfMonitorManagerXrandr, gf_monitor_manager_xrandr, GF_TYPE_MONITOR_MANAGER)

static void
gf_monitor_manager_xrandr_read_current (GfMonitorManager *manager)
{
}

static GBytes *
gf_monitor_manager_xrandr_read_edid (GfMonitorManager *manager,
                                     GfOutput         *output)
{
  return NULL;
}

static void
gf_monitor_manager_xrandr_ensure_initial_config (GfMonitorManager *manager)
{
}

static gboolean
gf_monitor_manager_xrandr_apply_monitors_config (GfMonitorManager        *manager,
                                                 GfMonitorsConfig        *config,
                                                 GfMonitorsConfigMethod   method,
                                                 GError                 **error)
{
  g_set_error (error, G_IO_ERROR, G_IO_ERROR_FAILED, "Not implemented");
  return FALSE;
}

static void
gf_monitor_manager_xrandr_set_power_save_mode (GfMonitorManager *manager,
                                               GfPowerSave       mode)
{
}

static void
gf_monitor_manager_xrandr_change_backlight (GfMonitorManager *manager,
                                            GfOutput         *output,
                                            gint              value)
{
}

static void
gf_monitor_manager_xrandr_get_crtc_gamma (GfMonitorManager  *manager,
                                          GfCrtc            *crtc,
                                          gsize             *size,
                                          gushort          **red,
                                          gushort          **green,
                                          gushort          **blue)
{
}

static void
gf_monitor_manager_xrandr_set_crtc_gamma (GfMonitorManager *manager,
                                          GfCrtc           *crtc,
                                          gsize             size,
                                          gushort          *red,
                                          gushort          *green,
                                          gushort          *blue)
{
}

static void
gf_monitor_manager_xrandr_tiled_monitor_added (GfMonitorManager *manager,
                                               GfMonitor        *monitor)
{
}

static void
gf_monitor_manager_xrandr_tiled_monitor_removed (GfMonitorManager *manager,
                                                 GfMonitor        *monitor)
{
}

static gboolean
gf_monitor_manager_xrandr_is_transform_handled (GfMonitorManager   *manager,
                                                GfCrtc             *crtc,
                                                GfMonitorTransform  transform)
{
  return FALSE;
}

static gfloat
gf_monitor_manager_xrandr_calculate_monitor_mode_scale (GfMonitorManager *manager,
                                                        GfMonitor        *monitor,
                                                        GfMonitorMode    *monitor_mode)
{
  return 1.0;
}

static gfloat *
gf_monitor_manager_xrandr_calculate_supported_scales (GfMonitorManager           *manager,
                                                      GfLogicalMonitorLayoutMode  layout_mode,
                                                      GfMonitor                  *monitor,
                                                      GfMonitorMode              *monitor_mode,
                                                      gint                       *n_supported_scales)
{
  *n_supported_scales = 0;
  return NULL;
}

static GfMonitorManagerCapability
gf_monitor_manager_xrandr_get_capabilities (GfMonitorManager *manager)
{
  return GF_MONITOR_MANAGER_CAPABILITY_NONE;
}

static gboolean
gf_monitor_manager_xrandr_get_max_screen_size (GfMonitorManager *manager,
                                               gint             *max_width,
                                               gint             *max_height)
{
  return FALSE;
}

static GfLogicalMonitorLayoutMode
gf_monitor_manager_xrandr_get_default_layout_mode (GfMonitorManager *manager)
{
  return GF_LOGICAL_MONITOR_LAYOUT_MODE_PHYSICAL;
}

static void
gf_monitor_manager_xrandr_class_init (GfMonitorManagerXrandrClass *xrandr_class)
{
  GfMonitorManagerClass *manager_class;

  manager_class = GF_MONITOR_MANAGER_CLASS (xrandr_class);

  manager_class->read_current = gf_monitor_manager_xrandr_read_current;
  manager_class->read_edid = gf_monitor_manager_xrandr_read_edid;
  manager_class->ensure_initial_config = gf_monitor_manager_xrandr_ensure_initial_config;
  manager_class->apply_monitors_config = gf_monitor_manager_xrandr_apply_monitors_config;
  manager_class->set_power_save_mode = gf_monitor_manager_xrandr_set_power_save_mode;
  manager_class->change_backlight = gf_monitor_manager_xrandr_change_backlight;
  manager_class->get_crtc_gamma = gf_monitor_manager_xrandr_get_crtc_gamma;
  manager_class->set_crtc_gamma = gf_monitor_manager_xrandr_set_crtc_gamma;
  manager_class->tiled_monitor_added = gf_monitor_manager_xrandr_tiled_monitor_added;
  manager_class->tiled_monitor_removed = gf_monitor_manager_xrandr_tiled_monitor_removed;
  manager_class->is_transform_handled = gf_monitor_manager_xrandr_is_transform_handled;
  manager_class->calculate_monitor_mode_scale = gf_monitor_manager_xrandr_calculate_monitor_mode_scale;
  manager_class->calculate_supported_scales = gf_monitor_manager_xrandr_calculate_supported_scales;
  manager_class->get_capabilities = gf_monitor_manager_xrandr_get_capabilities;
  manager_class->get_max_screen_size = gf_monitor_manager_xrandr_get_max_screen_size;
  manager_class->get_default_layout_mode = gf_monitor_manager_xrandr_get_default_layout_mode;
}

static void
gf_monitor_manager_xrandr_init (GfMonitorManagerXrandr *xrandr)
{
}

gboolean
gf_monitor_manager_xrandr_handle_xevent (GfMonitorManagerXrandr *xrandr,
                                         XEvent                 *event)
{
  return FALSE;
}