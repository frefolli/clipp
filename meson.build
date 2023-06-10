project('clipp', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20', 'optimization=3'])

include_dir = include_directories('include')

clipp = library(
  'clipp', [
    'src/utils.cc',
    'src/hypermap.cc',
    'src/hyperint.cc',
    'src/hyperbool.cc',
    'src/hyperstring.cc',
    'src/hyperobject.cc',
    'src/flag.cc',
    'src/arg.cc',
    'src/menu.cc'
  ], install: false, 
  include_directories: include_dir)

main = executable(
  'main', [
    'src/main.cc',
  ], install : false,
  link_with: clipp,
  include_directories: include_dir)

