/*
 * Copyright (C) 2016 Red Hat
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
 * - src/backends/meta-logical-monitor.h
 */

#include "config.h"
#include "gf-crtc-private.h"
#include "gf-logical-monitor-private.h"
#include "gf-output-private.h"

typedef struct
{
  GfMonitorManager *monitor_manager;
  GfLogicalMonitor *logical_monitor;
} AddMonitorFromConfigData;

G_DEFINE_TYPE (GfLogicalMonitor, gf_logical_monitor, G_TYPE_OBJECT)

static void
add_monitor_from_config (GfMonitorConfig          *monitor_config,
                         AddMonitorFromConfigData *data)
{
  GfMonitorSpec *monitor_spec;
  GfMonitor *monitor;

  monitor_spec = monitor_config->monitor_spec;
  monitor = gf_monitor_manager_get_monitor_from_spec (data->monitor_manager, monitor_spec);

  gf_logical_monitor_add_monitor (data->logical_monitor, monitor);
}

static GfMonitor *
get_first_monitor (GfMonitorManager *monitor_manager,
                   GList            *monitor_configs)
{
  GfMonitorConfig *first_monitor_config;
  GfMonitorSpec *first_monitor_spec;

  first_monitor_config = g_list_first (monitor_configs)->data;
  first_monitor_spec = first_monitor_config->monitor_spec;

  return gf_monitor_manager_get_monitor_from_spec (monitor_manager, first_monitor_spec);
}

static GfMonitorTransform
derive_monitor_transform (GfMonitor *monitor)
{
  GfOutput *main_output;

  main_output = gf_monitor_get_main_output (monitor);

  return main_output->crtc->transform;
}

static void
gf_logical_monitor_class_init (GfLogicalMonitorClass *logical_monitor_class)
{
}

static void
gf_logical_monitor_init (GfLogicalMonitor *logical_monitor)
{
}

GfLogicalMonitor *
gf_logical_monitor_new (GfMonitorManager       *monitor_manager,
                        GfLogicalMonitorConfig *logical_monitor_config,
                        gint                    monitor_number)
{
  GfLogicalMonitor *logical_monitor;
  GList *monitor_configs;
  GfMonitor *first_monitor;
  GfOutput *main_output;
  AddMonitorFromConfigData data;

  logical_monitor = g_object_new (GF_TYPE_LOGICAL_MONITOR, NULL);

  monitor_configs = logical_monitor_config->monitor_configs;
  first_monitor = get_first_monitor (monitor_manager, monitor_configs);
  main_output = gf_monitor_get_main_output (first_monitor);

  logical_monitor->number = monitor_number;
  logical_monitor->winsys_id = main_output->winsys_id;
  logical_monitor->scale = logical_monitor_config->scale;
  logical_monitor->transform = logical_monitor_config->transform;
  logical_monitor->in_fullscreen = -1;
  logical_monitor->rect = logical_monitor_config->layout;

  logical_monitor->is_presentation = TRUE;

  data.monitor_manager = monitor_manager;
  data.logical_monitor = logical_monitor;

  g_list_foreach (monitor_configs, (GFunc) add_monitor_from_config, &data);

  return logical_monitor;
}

GfLogicalMonitor *
gf_logical_monitor_new_derived (GfMonitorManager *monitor_manager,
                                GfMonitor        *monitor,
                                GfRectangle      *layout,
                                gfloat            scale,
                                gint              monitor_number)
{
  GfLogicalMonitor *logical_monitor;
  GfMonitorTransform transform;
  GfOutput *main_output;

  logical_monitor = g_object_new (GF_TYPE_LOGICAL_MONITOR, NULL);

  transform = derive_monitor_transform (monitor);
  main_output = gf_monitor_get_main_output (monitor);

  logical_monitor->number = monitor_number;
  logical_monitor->winsys_id = main_output->winsys_id;
  logical_monitor->scale = scale;
  logical_monitor->transform = transform;
  logical_monitor->in_fullscreen = -1;
  logical_monitor->rect = *layout;

  logical_monitor->is_presentation = TRUE;

  gf_logical_monitor_add_monitor (logical_monitor, monitor);

  return logical_monitor;
}

void
gf_logical_monitor_add_monitor (GfLogicalMonitor *logical_monitor,
                                GfMonitor        *monitor)
{
  gboolean is_presentation;
  GList *l;

  is_presentation = logical_monitor->is_presentation;
  logical_monitor->monitors = g_list_append (logical_monitor->monitors, monitor);

  for (l = logical_monitor->monitors; l; l = l->next)
    {
      GfMonitor *l_monitor;
      GList *outputs;
      GList *l_output;

      l_monitor = l->data;
      outputs = gf_monitor_get_outputs (l_monitor);

      for (l_output = outputs; l_output; l_output = l_output->next)
        {
          GfOutput *output;

          output = l_output->data;
          is_presentation = is_presentation && output->is_presentation;

          if (output->crtc)
            output->crtc->logical_monitor = logical_monitor;
        }
    }

  logical_monitor->is_presentation = is_presentation;
}

gboolean
gf_logical_monitor_is_primary (GfLogicalMonitor *logical_monitor)
{
  return logical_monitor->is_primary;
}

void
gf_logical_monitor_make_primary (GfLogicalMonitor *logical_monitor)
{
  logical_monitor->is_primary = TRUE;
}

gfloat
gf_logical_monitor_get_scale (GfLogicalMonitor *logical_monitor)
{
  return logical_monitor->scale;
}

GfMonitorTransform
gf_logical_monitor_get_transform (GfLogicalMonitor *logical_monitor)
{
  return logical_monitor->transform;
}

GfRectangle
gf_logical_monitor_get_layout (GfLogicalMonitor *logical_monitor)
{
  return logical_monitor->rect;
}

GList *
gf_logical_monitor_get_monitors (GfLogicalMonitor *logical_monitor)
{
  return logical_monitor->monitors;
}
