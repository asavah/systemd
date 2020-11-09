/* SPDX-License-Identifier: LGPL-2.1-or-later */
#pragma once

#include "sd-bus.h"

#include "bus-unit-util.h"
#include "format-table.h"
#include "systemctl.h"

typedef enum BusFocus {
        BUS_FULL,      /* The full bus indicated via --system or --user */
        BUS_MANAGER,   /* The manager itself, possibly directly, possibly via the bus */
        _BUS_FOCUS_MAX
} BusFocus;

int acquire_bus(BusFocus focus, sd_bus **ret);
void release_busses(void);

void ask_password_agent_open_maybe(void);
void polkit_agent_open_maybe(void);

int translate_bus_error_to_exit_status(int r, const sd_bus_error *error);

int get_state_one_unit(sd_bus *bus, const char *name, UnitActiveState *ret_active_state);
int get_unit_list(sd_bus *bus, const char *machine, char **patterns, UnitInfo **unit_infos, int c, sd_bus_message **ret_reply);
int expand_unit_names(sd_bus *bus, char **names, const char* suffix, char ***ret, bool *ret_expanded);

int check_triggering_units(sd_bus *bus, const char *unit);

int need_daemon_reload(sd_bus *bus, const char *unit);

void warn_unit_file_changed(const char *unit);

int append_unit_dependencies(sd_bus *bus, char **names, char ***ret);
int maybe_extend_with_unit_dependencies(sd_bus *bus, char ***list);

int unit_file_find_path(LookupPaths *lp, const char *unit_name, char **ret_unit_path);
int unit_find_paths(sd_bus *bus, const char *unit_name, LookupPaths *lp, bool force_client_side, Hashmap **cached_id_map, Hashmap **cached_name_map, char **ret_fragment_path, char ***ret_dropin_paths);

int unit_is_masked(sd_bus *bus, LookupPaths *lp, const char *name);
int unit_exists(LookupPaths *lp, const char *unit);

int unit_get_dependencies(sd_bus *bus, const char *name, char ***ret);

const char* unit_type_suffix(const char *unit);
bool output_show_unit(const UnitInfo *u, char **patterns);

bool install_client_side(void);

int output_table(Table *table);

bool show_preset_for_state(UnitFileState state);

int mangle_names(const char *operation, char **original_names, char ***ret_mangled_names);

UnitFileFlags unit_file_flags_from_args(void);

int halt_now(enum action a);
