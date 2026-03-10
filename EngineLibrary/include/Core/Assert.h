/*!
 * @file Assert.h
 * @brief アサートマクロ定義
 */

#pragma once

#include <cassert>
#include "Core/BuildConfig.h"
#include "Core/Macros.h"

/*!
 * @brief アサートマクロ
 *
 * デバッグビルド時に条件を評価し、
 * false の場合はブレークを発生させる。
 *
 * @param expr 評価する式
 */
#if REMIAYLE_DEBUG

#define REMIAYLE_ASSERT(expr)               \
        do                                  \
        {                                   \
            if (!(expr))                    \
            {                               \
                REMIAYLE_DEBUG_BREAK();     \
                assert(expr);               \
            }                               \
        } while (0)

#else

#define REMIAYLE_ASSERT(expr) ((void)0)

#endif
