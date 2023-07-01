

#include "indeed.h"

#define TAG "indeed_app"

static bool app_custom_event_callback(void* context, uint32_t event) {
    furi_assert(context);
    App* app = context;
    return scene_manager_handle_custom_event(app->scene_manager, event);
}

static bool app_back_event_callback(void* context) {
    furi_assert(context);
    App* app = context;
    return scene_manager_handle_back_event(app->scene_manager);
}

static App* app_alloc() {
    App* app = malloc(sizeof(App));

    // Initialize view dispatcher and scene manager
    app->view_dispatcher = view_dispatcher_alloc();
    app->scene_manager = scene_manager_alloc(&app_scene_handlers, app);
    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_set_custom_event_callback(app->view_dispatcher, app_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(app->view_dispatcher, app_back_event_callback);

    // Open GUI record
    app->gui = furi_record_open(RECORD_GUI);

    // Open Notification record
    app->notifications = furi_record_open(RECORD_NOTIFICATION);

    // Widget
    app->widget = widget_alloc();
    view_dispatcher_add_view(app->view_dispatcher, AppViewWidget, widget_get_view(app->widget));

    // Random deed, random number from 0 to DolphinDeedMAX.
    app->deed = rand() % DolphinDeedMAX;

    return app;
}

static void app_free(App* app) {
    furi_assert(app);

    // Widget
    view_dispatcher_remove_view(app->view_dispatcher, AppViewWidget);
    widget_free(app->widget);

    // View Dispatcher
    view_dispatcher_free(app->view_dispatcher);

    // Scene Manager
    scene_manager_free(app->scene_manager);

    // GUI
    furi_record_close(RECORD_GUI);
    app->gui = NULL;

    // Notifications
    furi_record_close(RECORD_NOTIFICATION);
    app->notifications = NULL;

    free(app);
}

// AC Control - Entry Point
int32_t indeed_app(void* p) {
    App* app = app_alloc();
    UNUSED(p);

    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);

    scene_manager_next_scene(app->scene_manager, AppSceneIndeed);

    view_dispatcher_run(app->view_dispatcher);

    app_free(app);

    return 0;
}