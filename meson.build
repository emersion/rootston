project(
	'rootston',
	'c',
	version: '0.6.0',
	license: 'MIT',
	meson_version: '>=0.48.0',
	default_options: [
		'c_std=c11',
		'warning_level=2',
		'werror=true',
	],
)

add_project_arguments([
	'-DWLR_USE_UNSTABLE',
], language: 'c')

cc = meson.get_compiler('c')

add_project_arguments(cc.get_supported_arguments([
	'-Wundef',
	'-Wlogical-op',
	'-Wmissing-include-dirs',
	'-Wold-style-definition',
	'-Wpointer-arith',
	'-Winit-self',
	'-Wstrict-prototypes',
	'-Wimplicit-fallthrough=2',
	'-Wendif-labels',
	'-Wstrict-aliasing=2',
	'-Woverflow',

	'-Wno-missing-braces',
	'-Wno-missing-field-initializers',
	'-Wno-unused-parameter',
]), language: 'c')

sources = [
	'bindings.c',
	'config.c',
	'cursor.c',
	'desktop.c',
	'ini.c',
	'input.c',
	'keyboard.c',
	'layer_shell.c',
	'main.c',
	'output.c',
	'render.c',
	'seat.c',
	'switch.c',
	'text_input.c',
	'view.c',
	'virtual_keyboard.c',
	'xdg_shell_v6.c',
	'xdg_shell.c',
]

wayland_server = dependency('wayland-server')
wayland_protos = dependency('wayland-protocols', version: '>=1.17')
pixman         = dependency('pixman-1')
libinput       = dependency('libinput')
xkbcommon      = dependency('xkbcommon')
math           = cc.find_library('m')

# Try first to find wlroots as a subproject, then as a system dependency
wlroots_version = ['>=0.10.0', '<0.11.0']
wlroots_proj = subproject(
	'wlroots',
	default_options: ['rootston=false', 'examples=false'],
	required: false,
	version: wlroots_version,
)
if wlroots_proj.found()
	wlroots = wlroots_proj.get_variable('wlroots')
	wlroots_conf = wlroots_proj.get_variable('conf_data')
	have_xwayland = wlroots_conf.get('WLR_HAS_XWAYLAND') == 1
else
	wlroots = dependency('wlroots', version: wlroots_version)
	have_xwayland = cc.get_define('WLR_HAS_XWAYLAND', prefix: '#include <wlr/config.h>', dependencies: wlroots) == '1'
endif

if get_option('xwayland').enabled() and not have_xwayland
	error('Cannot enable Xwayland: wlroots has been built without Xwayland support')
endif

if have_xwayland
	sources += 'xwayland.c'
endif

subdir('protocol')

rootston_inc = include_directories('.', 'include')

executable(
	'rootston',
	sources,
	include_directories: rootston_inc,
	dependencies: [wlroots, protos, pixman, wayland_server, libinput, xkbcommon, math],
)
