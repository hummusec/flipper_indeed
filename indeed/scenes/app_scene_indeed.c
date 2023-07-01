
#include "../indeed.h"
// #include <assets_icons.h>

#define TAG "app_scene_indeed"

const char* deed_labels[] = {
    "DolphinDeedSubGhzReceiverInfo",
    "DolphinDeedSubGhzSave",
    "DolphinDeedSubGhzRawRec",
    "DolphinDeedSubGhzAddManually",
    "DolphinDeedSubGhzSend",
    "DolphinDeedSubGhzFrequencyAnalyzer",
    "DolphinDeedRfidRead",
    "DolphinDeedRfidReadSuccess",
    "DolphinDeedRfidSave",
    "DolphinDeedRfidEmulate",
    "DolphinDeedRfidAdd",
    "DolphinDeedNfcRead",
    "DolphinDeedNfcReadSuccess",
    "DolphinDeedNfcSave",
    "DolphinDeedNfcDetectReader",
    "DolphinDeedNfcEmulate",
    "DolphinDeedNfcMfcAdd",
    "DolphinDeedNfcAddSave",
    "DolphinDeedNfcAddEmulate",
    "DolphinDeedIrSend",
    "DolphinDeedIrLearnSuccess",
    "DolphinDeedIrSave",
    "DolphinDeedIbuttonRead",
    "DolphinDeedIbuttonReadSuccess",
    "DolphinDeedIbuttonSave",
    "DolphinDeedIbuttonEmulate",
    "DolphinDeedIbuttonAdd",
    "DolphinDeedBadUsbPlayScript",
    "DolphinDeedU2fAuthorized",
    "DolphinDeedGpioUartBridge",
    "DolphinDeedPluginStart",
    "DolphinDeedPluginGameStart",
    "DolphinDeedPluginGameWin"};

void app_scene_indeed_widget_callback(GuiButtonType result, InputType type, void* context) {
    // Callback for the widget buttons
    App* app = context;
    if(type == InputTypeShort) {
        view_dispatcher_send_custom_event(app->view_dispatcher, result);
    }
}

void app_scene_indeed_update_widgets(App* app) {
    char deed_label[70];
    snprintf(deed_label, 70, "Current Deed:\n%s", deed_labels[app->deed]);

    // Clear the widget
    widget_reset(app->widget);

    widget_add_text_scroll_element(app->widget, 0, 0, 128, 52, deed_label);

    widget_add_icon_element(app->widget, -10, 23, &I_DolphinWait_61x59);
    widget_add_icon_element(app->widget, 41, 26, &I_unknown_10px);

    widget_add_button_element(
        app->widget, GuiButtonTypeRight, "Deed", app_scene_indeed_widget_callback, app);
    widget_add_button_element(
        app->widget, GuiButtonTypeCenter, "Feed", app_scene_indeed_widget_callback, app);
}

void app_scene_indeed_on_enter(void* context) {
    App* app = context;

    // Initialize the widget
    app_scene_indeed_update_widgets(app);
    view_dispatcher_switch_to_view(app->view_dispatcher, AppViewWidget);
}

bool app_scene_indeed_on_event(void* context, SceneManagerEvent event) {
    App* app = context;
    SceneManager* scene_manager = app->scene_manager;
    bool consumed = false;

    switch(event.event) {
    case EventGuiButtonTypeRight:
        consumed = true;
        app->deed = rand() % 34;
        app_scene_indeed_update_widgets(app);
        break;

    case EventGuiButtonTypeCenter:
        consumed = true;
        DOLPHIN_DEED(app->deed);
        notification_message(app->notifications, &sequence_success);

        break;

    default:
        break;
    }

    UNUSED(scene_manager);
    return consumed;
}

void app_scene_indeed_on_exit(void* context) {
    App* app = context;
    widget_reset(app->widget);
}