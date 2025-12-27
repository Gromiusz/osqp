#ifndef OSQP_CONFIGURE_H
#define OSQP_CONFIGURE_H

/* Minimal manually-generated config for PX4 build */

/* OSQP_ENABLE_DEBUG */
/* #undef OSQP_ENABLE_DEBUG */

/* Operating system */
#ifndef IS_LINUX
#define IS_LINUX
#endif

/* Algebra backend */
#define OSQP_ALGEBRA_BUILTIN
/* #undef OSQP_ALGEBRA_MKL */
/* #undef OSQP_ALGEBRA_CUDA */

/* Codegen / profiler options */
/* #undef OSQP_CODEGEN */
/* #undef OSQP_PROFILER_ANNOTATIONS */
/* #undef OSQP_ENABLE_DERIVATIVES */

/* Embedded mode */
/* #undef OSQP_EMBEDDED_MODE */

/* Custom allocators / printing */
/* #undef OSQP_CUSTOM_MEMORY */
/* #undef OSQP_ENABLE_PRINTING */
/* #undef OSQP_CUSTOM_PRINTING */

/* Profiling / interrupt */
/* #undef OSQP_ENABLE_PROFILING */
/* #undef OSQP_ENABLE_INTERRUPT */

/* Precision / integer size */
/* #undef OSQP_USE_FLOAT */
/* #undef OSQP_USE_LONG */

/* #undef OSQP_PACK_SETTINGS */

#endif /* OSQP_CONFIGURE_H */
