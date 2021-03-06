/*
 * Copyright (C) 2004-2005 William Jon McCann
 * Copyright (C) 2016 Alberts Muktupāvels
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
 * Authors:
 *     Alberts Muktupāvels <alberts.muktupavels@gmail.com>
 *     William Jon McCann <mccann@jhu.edu>
 */

#ifndef GF_WATCHER_H
#define GF_WATCHER_H

#include <glib-object.h>

G_BEGIN_DECLS

#define GF_TYPE_WATCHER gf_watcher_get_type ()
G_DECLARE_FINAL_TYPE (GfWatcher, gf_watcher, GF, WATCHER, GObject)

GfWatcher   *gf_watcher_new                (void);

void         gf_watcher_set_enabled        (GfWatcher *watcher,
                                            gboolean   enabled);

gboolean     gf_watcher_get_enabled        (GfWatcher *watcher);

void         gf_watcher_set_active         (GfWatcher *watcher,
                                            gboolean   active);

gboolean     gf_watcher_get_active         (GfWatcher *watcher);

const gchar *gf_watcher_get_status_message (GfWatcher *watcher);

G_END_DECLS

#endif
