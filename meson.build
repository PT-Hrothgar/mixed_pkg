project('mixed_pkg', 'c', license: 'MIT', license_files: 'LICENSE', version: '0.12')

py = import('python').find_installation(pure: false)

install_headers('src/mixed_pkg/factors.h')

py.extension_module(
    'c_helpers',
    'src/mixed_pkg/c_helpersmodule.c',
    'src/mixed_pkg/factors.c',
    install: true,
    subdir: 'mixed_pkg'
)

py.install_sources(
    'src/mixed_pkg/__init__.py',
    subdir: 'mixed_pkg'
)
