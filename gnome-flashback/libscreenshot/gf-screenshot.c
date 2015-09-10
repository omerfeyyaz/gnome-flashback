/*
 * Copyright (C) 2015 Alberts Muktupāvels
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
 */

#include "config.h"

#include <gtk/gtk.h>

#include "gf-dbus-screenshot.h"
#include "gf-screenshot.h"
#include "gf-select-area.h"

#define SCREENSHOT_DBUS_NAME "org.gnome.Shell.Screenshot"
#define SCREENSHOT_DBUS_PATH "/org/gnome/Shell/Screenshot"

struct _GfScreenshot
{
  GObject           parent;

  gint              bus_name;
  GfDBusScreenshot *dbus_screenshot;
};

G_DEFINE_TYPE (GfScreenshot, gf_screenshot, G_TYPE_OBJECT)

static gboolean
handle_screenshot (GfDBusScreenshot      *dbus_screenshot,
                   GDBusMethodInvocation *invocation,
                   gboolean               include_cursor,
                   gboolean               flash,
                   const gchar           *filename,
                   gpointer               user_data)
{
  g_warning ("screenshot: screenshot");
  gf_dbus_screenshot_complete_screenshot (dbus_screenshot, invocation,
                                          FALSE, "");

  return TRUE;
}

static gboolean
handle_screenshot_window (GfDBusScreenshot      *dbus_screenshot,
                          GDBusMethodInvocation *invocation,
                          gboolean               include_frame,
                          gboolean               include_cursor,
                          gboolean               flash,
                          const gchar           *filename,
                          gpointer               user_data)
{
  g_warning ("screenshot: screenshot-window");
  gf_dbus_screenshot_complete_screenshot_window (dbus_screenshot, invocation,
                                                 FALSE, "");

  return TRUE;
}

static gboolean
handle_screenshot_area (GfDBusScreenshot      *dbus_screenshot,
                        GDBusMethodInvocation *invocation,
                        gint                   x,
                        gint                   y,
                        gint                   width,
                        gint                   height,
                        const gchar           *file_template,
                        GVariant              *options,
                        gpointer               user_data)
{
  g_warning ("screenshot: screenshot-area");
  gf_dbus_screenshot_complete_screenshot_area (dbus_screenshot, invocation,
                                               FALSE, "");

  return TRUE;
}

static gboolean
handle_flash_area (GfDBusScreenshot      *dbus_screenshot,
                   GDBusMethodInvocation *invocation,
                   gint                   x,
                   gint                   y,
                   gint                   width,
                   gint                   height,
                   gpointer               user_data)
{
  g_warning ("screenshot: flash-area");
  gf_dbus_screenshot_complete_flash_area (dbus_screenshot, invocation);

  return TRUE;
}

static gboolean
handle_select_area (GfDBusScreenshot      *dbus_screenshot,
                    GDBusMethodInvocation *invocation,
                    gpointer               user_data)
{
  GfSelectArea *select_area;
  gint x;
  gint y;
  gint width;
  gint height;

  select_area = gf_select_area_new ();
  x = y = width = height = 0;

  if (gf_select_area_select (select_area, &x, &y, &width, &height))
    {
      gf_dbus_screenshot_complete_select_area (dbus_screenshot, invocation,
                                               x, y, width, height);
    }
  else
    {
      g_dbus_method_invocation_return_error (invocation, G_IO_ERROR,
                                             G_IO_ERROR_CANCELLED,
                                             "Operation was cancelled");
    }

  g_object_unref (select_area);

  return TRUE;
}

static void
bus_acquired_handler (GDBusConnection *connection,
                      const gchar     *name,
                      gpointer         user_data)
{
  GfScreenshot *screenshot;
  GfDBusScreenshot *dbus_screenshot;
  GDBusInterfaceSkeleton *skeleton;
  GError *error;
  gboolean exported;

  screenshot = GF_SCREENSHOT (user_data);

  dbus_screenshot = screenshot->dbus_screenshot;
  skeleton = G_DBUS_INTERFACE_SKELETON (dbus_screenshot);

  g_signal_connect (dbus_screenshot, "handle-screenshot",
                    G_CALLBACK (handle_screenshot), screenshot);
  g_signal_connect (dbus_screenshot, "handle-screenshot-window",
                    G_CALLBACK (handle_screenshot_window), screenshot);
  g_signal_connect (dbus_screenshot, "handle-screenshot-area",
                    G_CALLBACK (handle_screenshot_area), screenshot);
  g_signal_connect (dbus_screenshot, "handle-flash-area",
                    G_CALLBACK (handle_flash_area), screenshot);
  g_signal_connect (dbus_screenshot, "handle-select-area",
                    G_CALLBACK (handle_select_area), screenshot);

  error = NULL;
  exported = g_dbus_interface_skeleton_export (skeleton, connection,
                                               SCREENSHOT_DBUS_PATH,
                                               &error);

  if (!exported)
    {
      g_warning ("Failed to export interface: %s", error->message);
      g_error_free (error);
      return;
    }
}

static void
gf_screenshot_dispose (GObject *object)
{
  GfScreenshot *screenshot;
  GDBusInterfaceSkeleton *skeleton;

  screenshot = GF_SCREENSHOT (object);

  if (screenshot->dbus_screenshot)
    {
      skeleton = G_DBUS_INTERFACE_SKELETON (screenshot->dbus_screenshot);

      g_dbus_interface_skeleton_unexport (skeleton);
      g_clear_object (&screenshot->dbus_screenshot);
    }

  if (screenshot->bus_name)
    {
      g_bus_unown_name (screenshot->bus_name);
      screenshot->bus_name = 0;
    }

  G_OBJECT_CLASS (gf_screenshot_parent_class)->dispose (object);
}

static void
gf_screenshot_class_init (GfScreenshotClass *screenshot_class)
{
  GObjectClass *object_class;

  object_class = G_OBJECT_CLASS (screenshot_class);

  object_class->dispose = gf_screenshot_dispose;
}

static void
gf_screenshot_init (GfScreenshot *screenshot)
{
  screenshot->dbus_screenshot = gf_dbus_screenshot_skeleton_new ();
  screenshot->bus_name = g_bus_own_name (G_BUS_TYPE_SESSION,
                                         SCREENSHOT_DBUS_NAME,
                                         G_BUS_NAME_OWNER_FLAGS_ALLOW_REPLACEMENT |
                                         G_BUS_NAME_OWNER_FLAGS_REPLACE,
                                         (GBusAcquiredCallback) bus_acquired_handler,
                                         NULL, NULL, screenshot, NULL);
}

GfScreenshot *
gf_screenshot_new (void)
{
  return g_object_new (GF_TYPE_SCREENSHOT, NULL);
}
