project('mixed_pkg', 'c', license: 'MIT', license_files: 'LICENSE', version: '0.12')

py = import('python').find_installation(pure: false)

install_headers('factors.h')

py.extension_module(
    'c_helpers',
    'c_helpersmodule.c',
    'factors.c',
    install: true,
    subdir: 'mixed_pkg'
)

py.install_sources(
    'src/mixed_pkg/__init__.py',
    subdir: 'mixed_pkg'
)
