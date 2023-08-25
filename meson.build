project('tetris', 'cpp',
  default_options: [
    'prefix=~/Projects/tetris/',
    'cpp_std=c++17'
  ]
)
add_project_link_arguments('-lstdc++', '-lsfml-graphics',
  '-lsfml-window','-lsfml-system','-lsfml-audio', language: 'cpp')
subdir('src')
sfml_path = '/usr/include/SFML'
sfml_lib = library('libsfml-dev', sources: [sfml_path+'/Config.hpp'])
executable('exe', sources,
  include_directories: ['include'],
  link_with: sfml_lib,
  install: true)
