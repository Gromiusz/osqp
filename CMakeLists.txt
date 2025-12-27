cmake_minimum_required(VERSION 3.16)
project(osqp_px4 C)

# PX4-oriented build of OSQP with builtin algebra and FetchContent QDLDL.
include(FetchContent)

set(OSQP_ALGEBRA_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/algebra)
# If available, use prefetched qdldl sources; otherwise fall back to FetchContent.
set(QDLDL_LOCAL_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/algebra/_common/lin_sys/qdldl)
if(EXISTS ${QDLDL_LOCAL_ROOT}/qdldl.c AND EXISTS ${QDLDL_LOCAL_ROOT}/qdldl.h)
	set(qdldl_SOURCE_DIR ${QDLDL_LOCAL_ROOT})
	set(qdldl_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/qdldl_local)
	file(MAKE_DIRECTORY ${qdldl_BINARY_DIR}/include)
	if(EXISTS ${QDLDL_LOCAL_ROOT}/qdldl_version.h.in)
		configure_file(${QDLDL_LOCAL_ROOT}/qdldl_version.h.in ${qdldl_BINARY_DIR}/include/qdldl_version.h @ONLY)
	elseif(EXISTS ${QDLDL_LOCAL_ROOT}/qdldl_version.h)
		file(COPY ${QDLDL_LOCAL_ROOT}/qdldl_version.h DESTINATION ${qdldl_BINARY_DIR}/include)
	endif()
	add_library(qdldlobject OBJECT
		${QDLDL_LOCAL_ROOT}/qdldl.c
		${QDLDL_LOCAL_ROOT}/qdldl_interface.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_aat.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_1.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_2.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_aat.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_control.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_defaults.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_info.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_order.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_postorder.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_post_tree.c
		${QDLDL_LOCAL_ROOT}/amd/src/amd_preprocess.c
		${QDLDL_LOCAL_ROOT}/amd/src/SuiteSparse_config.c
	)
	target_include_directories(qdldlobject PRIVATE
		${QDLDL_LOCAL_ROOT}
		${CMAKE_CURRENT_SOURCE_DIR}/algebra/_common
		${QDLDL_LOCAL_ROOT}/amd/include
		${CMAKE_CURRENT_SOURCE_DIR}/algebra/builtin
		${CMAKE_CURRENT_SOURCE_DIR}/include/public
		${CMAKE_CURRENT_SOURCE_DIR}/include/private
		${qdldl_BINARY_DIR}/include
	)
else()
	include(${OSQP_ALGEBRA_ROOT}/_common/lin_sys/qdldl/qdldl.cmake)
endif()

set(osqp_src
	src/auxil.c
	src/codegen.c
	src/error.c
	src/interrupt_unix.c
	src/osqp_api.c
	src/polish.c
	src/scaling.c
	src/timing_linux.c
	src/util.c
	algebra/_common/lin_sys/qdldl/qdldl_interface.c

	algebra/_common/csc_math.c
	algebra/_common/csc_utils.c
	algebra/_common/kkt.c
	algebra/_common/reduced_kkt.c

	algebra/builtin/algebra_libs.c
	algebra/builtin/matrix.c
	algebra/builtin/vector.c
)

add_library(osqp STATIC ${osqp_src} $<TARGET_OBJECTS:qdldlobject>)

target_include_directories(osqp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include/public
		${CMAKE_CURRENT_SOURCE_DIR}/include/private
		${CMAKE_CURRENT_SOURCE_DIR}/algebra/builtin
		${CMAKE_CURRENT_SOURCE_DIR}/algebra/_common
		${qdldl_SOURCE_DIR}/include
		${qdldl_BINARY_DIR}/include
		${OSQP_ALGEBRA_ROOT}/_common/lin_sys/qdldl
		${OSQP_ALGEBRA_ROOT}/_common/lin_sys/qdldl/amd/include
)

target_compile_options(osqp PRIVATE
	-Wno-float-equal
	-Wno-unused-function
	-Wno-strict-prototypes
	-Wno-implicit-function-declaration
	-Wno-empty-body
	-Wno-nested-externs
	-Wno-format-nonliteral
	-Wno-format-security
)

target_compile_options(qdldlobject PRIVATE
	-Wno-float-equal
	-Wno-unused-function
	-Wno-strict-prototypes
	-Wno-implicit-function-declaration
	-Wno-empty-body
	-Wno-nested-externs
	-Wno-format-nonliteral
	-Wno-format-security
)
