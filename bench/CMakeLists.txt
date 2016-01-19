cmake_minimum_required (VERSION 2.8.11)
project (bench)

include(bench)

add_executable(       benchCmplAbs benchCmplAbs.cpp)
target_link_libraries(benchCmplAbs debug     ${BENCHMARK_LIBS_DEBUG})
target_link_libraries(benchCmplAbs optimized ${BENCHMARK_LIBS_OPT})

add_executable(       benchIndexVar benchIndexVar.cpp)
target_link_libraries(benchIndexVar debug     ${BENCHMARK_LIBS_DEBUG})
target_link_libraries(benchIndexVar optimized ${BENCHMARK_LIBS_OPT})

add_executable(       benchFloatInit benchFloatInit.cpp)
target_link_libraries(benchFloatInit debug     ${BENCHMARK_LIBS_DEBUG})
target_link_libraries(benchFloatInit optimized ${BENCHMARK_LIBS_OPT})

add_executable(       benchArithmOps benchArithmOps.cpp)
target_link_libraries(benchArithmOps debug     ${BENCHMARK_LIBS_DEBUG})
target_link_libraries(benchArithmOps optimized ${BENCHMARK_LIBS_OPT})
