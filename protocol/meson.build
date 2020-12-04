wl_protocol_dir = wayland_protos.get_pkgconfig_variable('pkgdatadir')

wayland_scanner_dep = dependency('wayland-scanner', required: false, native: true)
if wayland_scanner_dep.found()
	wayland_scanner = find_program(
		wayland_scanner_dep.get_pkgconfig_variable('wayland_scanner'),
		native: true,
	)
else
	wayland_scanner = find_program('wayland-scanner', native: true)
endif

protocols = [
	[wl_protocol_dir, 'stable/xdg-shell/xdg-shell.xml'],
	[wl_protocol_dir, 'unstable/pointer-constraints/pointer-constraints-unstable-v1.xml'],
	[wl_protocol_dir, 'unstable/tablet/tablet-unstable-v2.xml'],
	'wlr-layer-shell-unstable-v1.xml',
]

protos_src = []
protos_headers = []

foreach p : protocols
	xml = join_paths(p)
	protos_src += custom_target(
		xml.underscorify() + '_server_c',
		input: xml,
		output: '@BASENAME@-protocol.c',
		command: [wayland_scanner, 'private-code', '@INPUT@', '@OUTPUT@'],
	)
	protos_headers += custom_target(
		xml.underscorify() + '_server_h',
		input: xml,
		output: '@BASENAME@-protocol.h',
		command: [wayland_scanner, 'server-header', '@INPUT@', '@OUTPUT@'],
	)
endforeach

lib_protos = static_library(
	'wl_protos',
	protos_src + protos_headers,
	dependencies: wayland_server.partial_dependency(compile_args: true),
)

protos = declare_dependency(
	link_with: lib_protos,
	sources: protos_headers,
)
