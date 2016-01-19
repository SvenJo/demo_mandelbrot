#pragma once

#ifdef _MSC_VER
#define _SCL_SECURE_NO_WARNINGS
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif

#include <algorithm>
#include <vector>
#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include <cassert>

#include <config.h>

#ifdef __SSE__
#include <xmmintrin.h>
#endif

#ifdef  _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127 4244)
#endif

#ifdef VECTORCLASS_FOUND
#include <vectorclass.h>
#endif

#ifdef  _MSC_VER
#pragma warning(pop)
#endif

#ifdef OPENMP_FOUND
#include <omp.h>

#define OPENMP_ENABLED
#endif

#ifdef  PPL_ENABLED
#include <ppl.h>
#include <concurrent_vector.h>
#endif

#ifdef AMP_ENABLED
#include <amp.h>
#endif

#ifdef  _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4267)
#endif

#ifdef TBB_FOUND
#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>
#define TBB_ENABLED
#endif

#ifdef  _MSC_VER
#pragma warning(pop)
#endif

#ifdef BOOST_FOUND
#include <boost/program_options.hpp>
#endif // BOOST_FOUND


#ifdef  _MSC_VER
#pragma warning(disable: 4512)
#endif
