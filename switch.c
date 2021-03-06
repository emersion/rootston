#include <stdlib.h>
#include <wlr/util/log.h>
#include "bindings.h"

void roots_switch_handle_toggle(struct roots_switch *switch_device,
		struct wlr_event_switch_toggle *event) {
	struct wl_list *bound_switches =
		&switch_device->seat->input->server->config->switches;
	struct roots_switch_config *sc;
	wl_list_for_each(sc, bound_switches, link) {
		if ((sc->name != NULL && strcmp(event->device->name, sc->name) != 0) &&
				(sc->name == NULL && event->switch_type != sc->switch_type)) {
			continue;
		}
		if (sc->switch_state != WLR_SWITCH_STATE_TOGGLE &&
				event->switch_state != sc->switch_state) {
			continue;
		}
		execute_binding_command(switch_device->seat,
			switch_device->seat->input, sc->command);
	}
}
