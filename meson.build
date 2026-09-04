project('raylib-boilerplate', 'c',
  version: '0.2.0',
  default_options: [
    'c_std=c99',
    'warning_level=2',
    'buildtype=debugoptimized',
  ],
)

cc = meson.get_compiler('c')

host_os = host_machine.system()
message('Host OS: @0@'.format(host_os))

# Raylib dependency - try system, fall back to vendored
raylib_dep = dependency('raylib', required: false)
if not raylib_dep.found()
  raylib_lib = cc.find_library('raylib',
    dirs: meson.current_source_dir() / 'lib' / 'raylib',
    required: true)
  raylib_inc = include_directories('lib/raylib')
  raylib_dep = declare_dependency(dependencies: raylib_lib, include_directories: raylib_inc)
endif

# Common dependencies
m_dep = cc.find_library('m', required: false)
pthread_dep = cc.find_library('pthread', required: false)

# Platform-specific dependencies
if host_os == 'linux'
  rt_dep = cc.find_library('rt', required: false)
  dl_dep = cc.find_library('dl', required: false)
  x11_dep = cc.find_library('X11', required: false)
  platform_deps = [m_dep, pthread_dep, rt_dep, dl_dep, x11_dep]
elif host_os == 'darwin'
  platform_deps = [m_dep, pthread_dep]
elif host_os == 'windows'
  platform_deps = [m_dep]
else
  platform_deps = [m_dep, pthread_dep]
endif

# Include directories
vendor_inc = include_directories('vendor')
vendor_utils_inc = include_directories('vendor/utils')
vendor_scene_inc = include_directories('vendor/scene')
vendor_object_inc = include_directories('vendor/object')
vendor_helpers_inc = include_directories('vendor/helpers')
cjson_inc = include_directories('lib/cJSON')
unity_inc = include_directories('lib/unity')
src_inc = include_directories('src')

all_includes = [
  vendor_inc,
  vendor_utils_inc,
  vendor_scene_inc,
  vendor_object_inc,
  vendor_helpers_inc,
  cjson_inc,
  unity_inc,
  src_inc,
]

# Vendor sources
vendor_sources = files(
  'vendor/utils/logger.c',
  'vendor/utils/assert.c',
  'vendor/utils/linked_list.c',
  'vendor/utils/hashmap.c',
  'vendor/scene/core.c',
  'vendor/object/core.c',
  'vendor/status.c',
  'vendor/global.c',
)

# cJSON
cjson_sources = files('lib/cJSON/cJSON.c')

# Game executable
executable('raylib-boilerplate',
  files('main.c'),
  'src/game.c',
  'src/scenes/game.c',
  'src/scenes/menu.c',
  vendor_sources,
  cjson_sources,
  dependencies: [raylib_dep, platform_deps],
  include_directories: all_includes,
  install: true,
)

# Tests
if get_option('build_tests')
  unity_sources = files('lib/unity/unity.c')

  test_exe = executable('test_runner',
    files('test/test_runner.c'),
    'test/utils/linked_list_test.c',
    'test/utils/hashmap_test.c',
    'test/utils/logger_test.c',
    'test/utils/assert_test.c',
    'test/scene/core_test.c',
    'test/object/core_test.c',
    unity_sources,
    vendor_sources,
    cjson_sources,
    dependencies: [raylib_dep, platform_deps],
    include_directories: all_includes,
  )

  test('unit_tests', test_exe)
endif
