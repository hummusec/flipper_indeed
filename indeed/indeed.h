#pragma once

#include <furi.h>
#include <furi_hal.h>
#include <furi/core/log.h>
#include <furi_hal_gpio.h>
#include <furi_hal_resources.h>

#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <notification/notification_messages.h>

#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>
#include <gui/modules/popup.h>
#include <gui/modules/loading.h>
#include <gui/modules/text_input.h>
#include <gui/modules/widget.h>
#include <gui/modules/variable_item_list.h>

#include <dolphin/dolphin.h>
#include <dolphin/dolphin_i.h>

#include <dialogs/dialogs.h>
#include <storage/storage.h>
#include <flipper_format/flipper_format.h>

#include "scenes/app_scene.h"

#include "indeed_icons.h"

typedef struct {
    ViewDispatcher* view_dispatcher;
    Gui* gui;
    NotificationApp* notifications;
    SceneManager* scene_manager;
    Widget* widget;

    int deed;
} App;

typedef enum {
    AppViewSubmenu,
    AppViewDialogEx,
    AppViewPopup,
    AppViewLoading,
    AppViewWidget,
    AppViewVariableItemList,
    AppViewTextInput,
} AppViews;

typedef enum {
    EvnetGuiButtonTypeLeft,
    EventGuiButtonTypeCenter,
    EventGuiButtonTypeRight
} CustomEvents;