cmake_minimum_required(VERSION 3.16)
project(osqp_px4 C)

# Minimal PX4-oriented build of OSQP using builtin algebra and generated configure header.

set(osqp_src
	src/auxil.c
	src/codegen.c
	src/derivative.c
	src/error.c
	src/interrupt_unix.c
	src/osqp_api.c
	src/polish.c
	src/profilers.c
	src/profilers_impl.c
	src/profilers_terminal.c
	src/scaling.c
	src/timing_linux.c
	src/util.c

	algebra/_common/csc_math.c
	algebra/_common/csc_utils.c
	algebra/_common/kkt.c
	algebra/_common/reduced_kkt.c

	algebra/builtin/algebra_libs.c
	algebra/builtin/matrix.c
	algebra/builtin/vector.c
)

add_library(osqp STATIC ${osqp_src})

target_include_directories(osqp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include/public
		${CMAKE_CURRENT_SOURCE_DIR}/include/private
		${CMAKE_CURRENT_SOURCE_DIR}/algebra/builtin
		${CMAKE_CURRENT_SOURCE_DIR}/algebra/_common
)

target_compile_definitions(osqp PUBLIC IS_LINUX OSQP_ALGEBRA_BUILTIN)
