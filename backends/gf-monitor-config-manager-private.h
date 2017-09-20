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
 * - src/backends/meta-monitor-config-manager.h
 */

#ifndef GF_MONITOR_CONFIG_MANAGER_PRIVATE_H
#define GF_MONITOR_CONFIG_MANAGER_PRIVATE_H

#include "gf-monitor-manager-private.h"
#include "gf-monitor-private.h"

G_BEGIN_DECLS

typedef struct
{
  GfMonitorSpec     *monitor_spec;
  GfMonitorModeSpec *mode_spec;
  gboolean           enable_underscanning;
} GfMonitorConfig;

typedef struct
{
  GfRectangle         layout;
  GList              *monitor_configs;
  GfMonitorTransform  transform;
  gfloat              scale;
  gboolean            is_primary;
  gboolean            is_presentation;
} GfLogicalMonitorConfig;

G_END_DECLS

#endif