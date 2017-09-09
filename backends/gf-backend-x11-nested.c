/*
 * Copyright (C) 2017 Alberts Muktupāvels
 * Copyright (C) 2017 Red Hat
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
 * - src/backends/x11/nested/meta-backend-x11-nested.c
 */

#include "config.h"
#include "gf-backend-x11-nested-private.h"

struct _GfBackendX11Nested
{
  GfBackendX11 parent;
};

G_DEFINE_TYPE (GfBackendX11Nested, gf_backend_x11_nested, GF_TYPE_BACKEND_X11)

static void
gf_backend_x11_nested_class_init (GfBackendX11NestedClass *x11_nested_class)
{
}

static void
gf_backend_x11_nested_init (GfBackendX11Nested *x11_nested)
{
}