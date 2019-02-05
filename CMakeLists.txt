cmake_minimum_required(VERSION 3.13)
project(lastlock C)

set(CMAKE_C_STANDARD 11)

include_directories(mongoose/build/gen)
include_directories(zephyr/boards/arm/qca4020)

add_executable(lastlock
        mongoose/build/gen/build_info.c
        mongoose/build/gen/ffi_exports.c
        mongoose/build/gen/mg_build_info.c
        mongoose/build/gen/mgos_config.c
        mongoose/build/gen/mgos_config.h
        mongoose/build/gen/mgos_deps_init.c
        mongoose/build/gen/mgos_ro_vars.c
        mongoose/build/gen/mgos_ro_vars.h
        mongoose/src/main.c
        zephyr/boards/arm/qca4020/board.h
        zephyr/boards/arm/qca4020/dts_fixup.h
        zephyr/boards/arm/qca4020/pinmux.c
        zephyr/src/main.c)
