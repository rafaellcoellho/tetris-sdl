install_headers('game.h', 'input.h', 'board.h')

src = ['main.c', 'game.c', 'input.c', 'board.c']

sdl2 = dependency('SDL2', version: '>=2.0')
sdl2_image = dependency('SDL2_image', version: '>=2.0')

deps = [sdl2, sdl2_image]

executable('main', sources: src, dependencies: deps)